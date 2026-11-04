#!/usr/bin/env bash
# install-schedule.sh —— 把“每天 22:30 自动提交”写进当前用户的 crontab
#
#   ./scripts/install-schedule.sh          安装/更新（重复执行不会产生重复条目）
#   ./scripts/install-schedule.sh --remove 移除该条目
#
# 安装前会先读取现有 crontab；只要读不到就中止，绝不覆盖你已有的定时任务。
set -uo pipefail

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
TARGET="$SCRIPT_DIR/nightly-commit.sh"
MARKER="# My-Code 每天22:30自动提交（scripts/install-schedule.sh 管理）"
LINE="30 22 * * * /usr/bin/env bash '$TARGET'"

[ -f "$TARGET" ] || { printf '找不到脚本: %s\n' "$TARGET" >&2; exit 1; }
command -v crontab >/dev/null 2>&1 || { printf '系统里没有 crontab 命令\n' >&2; exit 1; }

err=$(mktemp) || exit 1
trap 'rm -f "$err"' EXIT

if ! current=$(crontab -l 2>"$err"); then
	if grep -qi 'no crontab' "$err"; then
		current=""
	else
		printf '无法读取现有 crontab，为避免覆盖已有任务，安装中止。\n原因: %s\n' "$(tr '\n' ' ' <"$err")" >&2
		printf '\n可以手动在 crontab -e 里加入下面两行：\n%s\n%s\n' "$MARKER" "$LINE" >&2
		exit 1
	fi
fi

filtered=$(printf '%s\n' "$current" | grep -vF "$MARKER" | grep -vF "$TARGET" || true)

if [ "${1:-}" = "--remove" ]; then
	printf '%s\n' "$filtered" | crontab - || { printf '写入 crontab 失败\n' >&2; exit 1; }
	printf '已移除 My-Code 自动提交任务。\n'
	exit 0
fi

{
	printf '%s\n' "$filtered"
	printf '%s\n' "$MARKER"
	printf '%s\n' "$LINE"
} | crontab - || {
	printf '写入 crontab 失败（可能是权限或沙箱限制）。\n' >&2
	printf '可以手动在 crontab -e 里加入下面两行：\n%s\n%s\n' "$MARKER" "$LINE" >&2
	exit 1
}

printf '已安装，每天 22:30 自动提交。当前相关条目：\n'
crontab -l 2>/dev/null | grep -F -e "$MARKER" -e "$TARGET"
