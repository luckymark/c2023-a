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
  - raylib库已引入，若不能运行，尝试配置好Clion工具链

  ``-DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake``
  
  - 默认编译为Release模式
  - 感谢指导，完美结课