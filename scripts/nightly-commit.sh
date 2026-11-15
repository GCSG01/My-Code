#!/usr/bin/env bash
# nightly-commit.sh —— 每天 22:30 把 My-Code 的改动提交为当天日期（YYYYMMDD）
#
# 行为：
#   1. git add -A 暂存全部改动（.gitignore 仍然生效）
#   2. 有改动则以当天日期为提交信息提交（无改动就跳过提交）
#   3. 可选地 fetch 远端并合并；合并出现冲突时保留本地版本（ours）
#   4. 可选地 push；push 失败只记日志，不影响本地提交
#
# 可用环境变量（都可以不设）：
#   REPO=路径        仓库目录，默认脚本所在目录的上一级
#   BRANCH=main      同步的分支
#   REMOTE=origin    远端名
#   SYNC=1           1 = fetch + 合并远端；0 = 只做本地提交
#   PUSH=1           1 = 同步成功后推送；0 = 不推送
#   TIMEOUT=60       单次网络操作超时（秒）
#   DRY_RUN=0        1 = 只打印将要做的事，不改动仓库
#   QUIET=0          1 = 不往终端输出（cron 下默认静默）
set -uo pipefail

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
REPO=${REPO:-$SCRIPT_DIR/..}
BRANCH=${BRANCH:-main}
REMOTE=${REMOTE:-origin}
SYNC=${SYNC:-1}
PUSH=${PUSH:-1}
TIMEOUT=${TIMEOUT:-60}
DRY_RUN=${DRY_RUN:-0}
QUIET=${QUIET:-$([ -t 1 ] && echo 0 || echo 1)}

REPO=$(cd -- "$REPO" 2>/dev/null && pwd) || {
	printf 'nightly-commit: 仓库目录不存在: %s\n' "${REPO}" >&2
	exit 1
}
MSG=$(date +%Y%m%d)
LOG=${LOG:-}

ts() { date '+%F %T'; }
log() {
	if [ -n "$LOG" ]; then
		printf '%s %s\n' "$(ts)" "$*" >>"$LOG" 2>/dev/null
	fi
	[ "$QUIET" = 1 ] || printf '%s\n' "$*"
}
die() {
	log "错误: $*"
	printf 'nightly-commit: %s\n' "$*" >&2
	exit 1
}

cd -- "$REPO" || die "无法进入 $REPO"
command -v git >/dev/null 2>&1 || die "找不到 git 命令（cron 的 PATH 是否缺少 /usr/bin？）"
git rev-parse --git-dir >/dev/null 2>&1 || die "$REPO 不是 git 仓库"

# 极简环境（如某些 cron）可能没有 timeout，退化为直接执行
if ! command -v timeout >/dev/null 2>&1; then
	timeout() { shift; "$@"; }
fi

GIT_DIR_ABS=$(git rev-parse --absolute-git-dir)
LOG=${LOG:-$GIT_DIR_ABS/nightly-commit.log}

# 日志只保留最近一代，超过 1MB 就轮转
if [ -f "$LOG" ] && [ "$(stat -c %s "$LOG" 2>/dev/null || echo 0)" -gt 1048576 ]; then
	mv -f "$LOG" "$LOG.1"
fi

# 上一次异常中断留下的合并/变基状态不自动处理，避免误伤
for state in MERGE_HEAD CHERRY_PICK_HEAD REVERT_HEAD rebase-merge rebase-apply; do
	if [ -e "$GIT_DIR_ABS/$state" ]; then
		die "仓库里有未完成的 git 操作（$state），本次跳过，请先手动处理"
	fi
done

# 防止两次运行重叠
exec 9>"$GIT_DIR_ABS/nightly-commit.lock"
if command -v flock >/dev/null 2>&1; then
	flock -n 9 || die "已有另一个实例在运行，本次跳过"
fi

# ---------- 1. 暂存并提交 ----------
if [ "$DRY_RUN" = 1 ]; then
	log "[dry-run] 提交信息: $MSG"
	git status --short | sed 's/^/  /' | tee -a "$LOG"
	[ -z "$(git status --porcelain)" ] && log "[dry-run] 当前没有改动，运行时会直接跳过提交"
	exit 0
fi

git add -A >>"$LOG" 2>&1 || die "git add -A 失败（请查看 $LOG）"

if git diff --cached --quiet; then
	log "没有需要提交的改动（$MSG）"
else
	count=$(git diff --cached --name-only | wc -l | tr -d ' ')
	if git commit -q -m "$MSG" >>"$LOG" 2>&1; then
		log "已提交 $MSG：$count 个文件，提交号 $(git rev-parse --short HEAD)"
	else
		die "git commit 失败（请查看 $LOG，可能是钩子或身份配置问题）"
	fi
fi

# ---------- 2. 合并远端：冲突时保留本地 ----------
# 当前分支和 BRANCH 不一致（切到别的分支、detached HEAD）时只做本地提交，不同步
current_branch=$(git rev-parse --abbrev-ref HEAD)
if [ "$SYNC" = 1 ] && [ "$current_branch" != "$BRANCH" ]; then
	log "当前分支为 $current_branch，与 BRANCH=$BRANCH 不一致，跳过同步"
	SYNC=0
fi

merged_ok=0
if [ "$SYNC" = 1 ] && git remote get-url "$REMOTE" >/dev/null 2>&1; then
	if timeout "$TIMEOUT" env GIT_TERMINAL_PROMPT=0 git fetch --prune --quiet "$REMOTE" "$BRANCH" >>"$LOG" 2>&1; then
		merged_ok=1
		upstream="$REMOTE/$BRANCH"
		if git rev-parse --verify --quiet "$upstream" >/dev/null; then
			if git merge-base --is-ancestor "$upstream" HEAD; then
				log "远端没有新提交"
			else
				log "远端有新提交，合并 $upstream（冲突保留本地）"
				if git merge --no-edit -m "$MSG" -X ours "$upstream" >>"$LOG" 2>&1; then
					log "合并完成（提交号 $(git rev-parse --short HEAD)）"
				elif [ -e "$GIT_DIR_ABS/MERGE_HEAD" ]; then
					# -X ours 处理不了 modify/delete、add/add 等情况，这里统一取本地
					while IFS= read -r -d '' f; do
						if git cat-file -e ":2:$f" 2>/dev/null; then
							git checkout --ours -- "$f" >>"$LOG" 2>&1 &&
								git add -- "$f" >>"$LOG" 2>&1 &&
								log "冲突取本地: $f"
						else
							# 本地没有这个路径（本地删除），保留本地结果
							git rm -q --ignore-unmatch -- "$f" >>"$LOG" 2>&1
							log "冲突保留本地删除: $f"
						fi
					done < <(git diff --name-only -z --diff-filter=U)

					if [ -n "$(git diff --name-only --diff-filter=U)" ]; then
						git merge --abort >>"$LOG" 2>&1
						die "仍有冲突无法自动取本地，已中止本次合并"
					fi
					if git commit -q -m "$MSG" >>"$LOG" 2>&1; then
						log "冲突已按本地解决并提交 $MSG"
					else
						die "提交合并结果失败（请查看 $LOG）"
					fi
				else
					log "警告: 合并失败（非冲突原因），已跳过同步"
				fi
			fi
		else
			log "远端还没有 $BRANCH 分支，跳过合并"
		fi
	else
		log "警告: fetch 失败（网络/凭据），跳过同步，本地提交已保留"
	fi
fi

# ---------- 3. 推送 ----------
if [ "$PUSH" = 1 ] && [ "$merged_ok" = 1 ]; then
	upstream="$REMOTE/$BRANCH"
	if git rev-parse --verify --quiet "$upstream" >/dev/null &&
		git merge-base --is-ancestor HEAD "$upstream"; then
		log "远端已包含全部提交，无需推送"
	elif timeout "$TIMEOUT" env GIT_TERMINAL_PROMPT=0 git push --quiet "$REMOTE" "HEAD:$BRANCH" >>"$LOG" 2>&1; then
		log "已推送到 $REMOTE/$BRANCH"
	else
		log "警告: push 失败（网络/凭据），本地提交已保留，下次运行会再试"
	fi
fi

exit 0
