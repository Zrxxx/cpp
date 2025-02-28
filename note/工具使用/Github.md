# clone使用已有仓库





## 初始化仓库

创建一个目录，并将其作为git仓库，在该目录下`git init`。

如果执行成功，该目录下会生成`.git`目录，该目录下的内容我们称为“附属于该仓库的工作树"。文件的编辑等操作在工作树中进行，然后记录到仓库中，以此管理文件的历史快照。**如果想将文件恢复到原先的状态，可以从仓库中调取之前的快照。**

## 查看仓库状态

在工作树和仓库被操作过程中，状态会不断发生变化。可用`git status`	查看。

```shell
On branch master
Your branch is up-to-date with 'origin/master'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
	modified:   "\346\225\260\346\215\256\347\273\223\346\236\204\344\270\216\347\256\227\346\263\225.md"

Untracked files:
  (use "git add <file>..." to include in what will be committed)
	../practice/.threadsafe_stack.cpp.swp
	../practice/threadsafe_stack.cpp

no changes added to commit (use "git add" and/or "git commit -a")

```

显示我们在master分支下，没有可提交Commit的内容，提交是值“记录工作树中所有文件的当前状态”，没有可提交即这个仓库没有记录到任何文件的任何状态。

## 暂存区添加文件

如果只是Git仓库的工作树创建了文件，那么该文件不会被计入Git仓库的版本管理对象中（如 Untracked files中的文件一样），此时使用`git add`命令将文件添加到暂存区，暂存区属于提交之前的一个临时区域。

## 保存仓库记录

`git commit`将当前在暂存区中的文件实际保存到仓库的历史记录中，通过这些记录我们可以在工作树中恢复文件。

`git commit `后面可以加 -m 参数添加简短信息，若要详细信息不使用参数，此时关闭编译器或终端会终止提交。



## 查看提交日志

`git log`显示提交的相关日志

- 使用`--prety=short`可以让程序显示第一行简述信息
- 后面添加目录名，只显示该目录下的提交日志
- 后面添加文件吗，只显示该文件下的提交日志
- 使用`-p 文件名` 参数会显示文件前后改变的区别

## 查看更改前后的区别

`git diff`可以查看工作树、暂存区、最新提交之间的差别

- 查看工作树和暂存区的差别

  新加的行前面+号，删除的行前面-号

- 查看工作树和最新提交的差别

  `git diff HEAD` （HEAD 是指向当前分支中最新一次提交的指针）

不妨养成一个好习惯：在执行git commit之前先执行 git diff HEAD命令，查看本次提交于上次提交之间有什么差别，确认后再提交。

## 分支操作

在进行多个并行作业，我们会用到分支。在这类并行发开过程中，往往同时存在多个最新代码状态。

例如从master分支创建feature-A分支和fix-B分支后，每个分支都拥有自己的最新代码。其中master分支是Github默认创建的分支，因此基本上所有并发都是以这个分支为中心进行的，等分支的作业完成之后再与master分支合并。

### git branch—显示分支一览表

*号代表我们当前所在的分支，如果结果中没有显示其他分支名，表示本地仓库只存在master分支。

### git checkout -b—创建、切换分支

使用上面命令以当前的master分支为基础创建新的分支

`git checkout -b feature-A`创建并切换到分支feature-A

- git branch feature -A
- git checkout  feature-A

与这两条命令具有等价效果

我们创建的分支称为特性分支，与之对应的master为主干分支。

### git merge—合并分支

假设feature -A已经实现完毕，想要把他合并到主干分支master中。

1. 切换到主干分支
2. 合并分支，同时记录下本次分支合并(--no-ff)

- `git log --graph`以图表的形式输出提交日志

### git reset—回溯历史版本

Git的另一特征便是可以灵活操作历史版本。借助分散仓库的优势的优势，可以在不影响其他仓库的前提下对历史版本进行操作。

回溯到上面feature-A分支创建之前，创建一个名为fix-B的特性分支。

要让仓库的HEAD、暂存区、当前工作树回溯到指定状态，需要用到git reset --hard命令。只要提供目标时间点的哈希值，就可以完全恢复至该时间点的状态。

#### 推进至feature-A分支合并后的状态

`git log`只能查看以当前状态为终点的历史日志，所以这里要使用`git reflog`命令查看当前仓库的操作日志，找出回溯日志之前的哈希值。

在日志中可以看到commit, checkout, reset, merge等Git命令的执行记录。只要不进行Git的GC，就可以通过日志随意调取近期的历史状态。基本上开发者错误地执行了Git操作，基本也都可以利用git reflog命令恢复到原来的版本。

#### 消除冲突

fix-B合并时出现冲突，====上面是当前内容，====下面是要提交的内容，它们发生了冲突，我们应该修正让feature-A与fix-B的内容并存与文件之中，删除=== 和<<<<符号

### git commit --amend

修改上一条提交信息



### git rebase -i—压缩历史

在合并特性分支之前，如果发现已提交的内容中有些许拼写错误，不妨提交一个修改，然后把这个修改包含到前一个提交中，压缩成一个历史记录。

- 创建一个新分支 feature-C

- 文件A中一行拼写错误，`git commit -am "Add file to feature-C"`
- 再修改文件中拼写错误的一行，`git diff`可以看到区别
- 重新提交`git commit -am “Fix typo”`
- 更改历史`git rebase -i HEAD~2`，选定当前分支中包含HEAD在内的两个最新历史记录为对象，并在编辑器中打开
- 将第二次提交记录的`pick`改为`fix up`，保存并关闭
- 查看`git log --graph`时已经合并
- 最后将分支合并到master



## 推送至远程仓库

