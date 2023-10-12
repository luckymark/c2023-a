project(level2)

add_executable(GA GA/main.c)

add_executable(NeuralNetworks NeuralNetworks/main.c NeuralNetworks/extract_methods.c NeuralNetworks NeuralNetworks/Network.c NeuralNetworks/Network.h)

add_executable(PI PI/main.cpp)

add_executable(SkipList SkipList/main.c)

