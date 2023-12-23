## 实验题目：五子棋AI

## GUI
- [raylib](https://github.com/raysan5/raylib)
- [EasyX](https://easyx.cn/)
- [SFML](https://www.sfml-dev.org/)


## AI算法参考

- [五子棋AI算法](https://blog.csdn.net/lihongxun945/category_6089493.html)
- [蒙特卡洛树搜索 MCTS 入门](http://nooverfit.com/wp/%E8%92%99%E7%89%B9%E5%8D%A1%E6%B4%9B%E6%A0%91%E6%90%9C%E7%B4%A2-mcts-%E5%85%A5%E9%97%A8/)
- [面向初学者的蒙特卡洛树搜索MCTS详解及其实现](https://www.daimajiaoliu.com/daima/4795138e3900404)

##  Gobang AI 简介
### 目录
- Former Codes
    - 一些函数的历史版本
    - 注：可忽略
- Logs
    - 是一些程序调试的简单日志
    - 曾用于错误分析，以及性能分析和优化
    - 注：可忽略
- Work
    - 图形界面是gui.c，也相当于整个程序的main.c，运行时选择gui.c这个目标。
    - test.c是递归函数
    - 其他文件是各个类型的函数，包括估值系统、栈、哈希表、着点生成、梅森旋转算法、Zobrist键值计算。
    - linked_hash_value_list.c是被抛弃的功能，速度过慢，只在初期尝试的时候被使用过，不影响整体功能。
- 课程设计的介绍PPT
    - PPT 简介
### 备注
- raylib图形库已引入，若不能运行，尝试配置好Clion工具链

``-DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake``

- 默认编译为Release模式
- 感谢指导，完美结课