project(gobang)

set(EasyX_DIR D:/EasyX)
include_directories(${EasyX_DIR}/include)
link_directories(${EasyX_DIR}/lib64)

link_libraries(libEasyX.a libgdi32.a libole32.a)
add_executable(gobang main.cpp)
