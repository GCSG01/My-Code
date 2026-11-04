# 每天 22:30 自动提交 My-Code

把仓库里的改动以「当天日期」为提交信息提交，例如 `20261104`。
与远端同步时如果出现冲突，一律保留本地版本。

## 文件

| 文件 | 作用 |
| --- | --- |
| `nightly-commit.sh` | 真正的例行任务：暂存 → 提交 → 合并远端（冲突取本地）→ 推送 |
| `install-schedule.sh` | 把任务写进当前用户的 crontab（可重复执行，不会重复添加；`--remove` 移除） |

## 已经装好的定时任务

```
30 22 * * * /usr/bin/env bash '/home/kre/学习资料/My-Code/scripts/nightly-commit.sh'
```

查看：`crontab -l`　移除：`bash scripts/install-schedule.sh --remove`

## 手动跑一次

```bash
bash scripts/nightly-commit.sh            # 正常执行
DRY_RUN=1 bash scripts/nightly-commit.sh  # 只看会提交哪些文件，不改动仓库
SYNC=0 bash scripts/nightly-commit.sh     # 只做本地提交，不连远端
```

## 行为细节

1. `git add -A` 暂存全部改动（`.gitignore` 照常生效）。
2. 没有改动就跳过提交，不会产生空提交。
3. 若有改动，提交信息为 `date +%Y%m%d`。
4. 拉取远端：`git fetch` 后 `git merge -X ours`，冲突内容保留本地；`-X ours` 处理不了的
   新增同名文件、远端改而本地删这类冲突，脚本会逐个取本地版本（本地删除的保持删除）。
5. 推送失败（网络、凭据）只记日志，本地提交照常保留，第二天会再试。
6. 仓库里存在未完成的合并 / 变基，或当前分支不是 `main` 时，脚本会跳过同步，只做本地提交。

## 可调参数（环境变量）

| 变量 | 默认 | 说明 |
| --- | --- | --- |
| `REPO` | 脚本上一级目录 | 仓库路径 |
| `BRANCH` | `main` | 同步的分支 |
| `REMOTE` | `origin` | 远端名 |
| `SYNC` | `1` | 是否 fetch + 合并远端 |
| `PUSH` | `1` | 是否推送 |
| `TIMEOUT` | `60` | 单次网络操作超时秒数 |
| `DRY_RUN` | `0` | 只预览不执行 |

## 日志

`<仓库>/.git/nightly-commit.log`，超过 1MB 自动轮转为 `.log.1`。

## 注意

- cron 用的是系统时区（当前为 Asia/Shanghai），所以提交日期和本机日期一致。
- 推送需要凭据。若远端是私有仓库且没配凭据，push 会失败并记录警告，本地提交不受影响；
  可以配置 `git config credential.helper store` 或改用 SSH 地址。
