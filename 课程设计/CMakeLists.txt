add_definitions(-DNOMINMAX)
project(gobang)

# 设置 C++17 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置 libtorch 的路径
set(TORCH_PATH "D:/libtorch")

# 包含 libtorch 的头文件
include_directories(${TORCH_PATH}/include)
include_directories(${TORCH_PATH}/include/torch/csrc/api/include)

# 链接 libtorch 的库
link_directories(${TORCH_PATH}/lib)


#配置EasyX
set(EasyX_INC D:\\EasyX_VS\\include)
set(EasyX_LINK D:\\EasyX_VS\\lib\\VC2015\\x64)
include_directories(${EasyX_INC})
link_directories(${EasyX_LINK})
link_libraries(EasyXa)
link_libraries(EasyXw)

add_executable(gobang main.cpp board_paint.cpp board_paint.h MCTS.cpp MCTS.h board.c board.h CNN.cpp CNN.h GobangCNN.cpp ValuePolicyLoss.cpp)

target_link_libraries(gobang torch torch_cpu torch_cuda c10 c10_cuda)