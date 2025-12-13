# FiveInARow

一个用 C++ 编写的命令行五子棋游戏。

## 功能特性

- 采用命令行界面

- 支持人人对战和人机对战

## AI 技术细节

- 搜索算法：Alpha-Beta 剪枝

- 搜索深度：2 层
- 评估函数：基于棋型打分（活四、冲四、活三等）
- 优化策略：只搜索已落子周围的位置，提升搜索效率
- 响应时间：1-2 秒

## 运行环境

- Windows 系统

### 注意

- 文件采用 GB2312 编码，若阅读源码时出现乱码，请切换至 GB2312 编码查看
- 将终端颜色切换为白色会更有利于显示

## 如何使用

### 直接运行

1. 前往 [Releases](../../releases) 页面
2. 下载最新版本的 `FiveInARow.exe`
3. 双击运行

### 从源码编译

1. 克隆仓库

```bash
git clone https://github.com/Sisyphus0218/FiveInARow.git
```

2. 编译并运行程序

若使用 Visual Studio（作者采用 Visual Studio 2022），打开 `FiveInARow.sln`，按 `Ctrl+F5` 进行编译并运行程序。

若使用 g++，进入 `src` 文件夹，执行以下命令，进行编译并运行程序：

```bash
g++ -o FiveInARow.exe *.cpp
./FiveInARow.exe
```

