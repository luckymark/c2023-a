project(level2)

add_executable(GA GA/main.c)

add_executable(NeuralNetworks NeuralNetworks/main.c NeuralNetworks/extract_methods.c NeuralNetworks NeuralNetworks/Full_Connected.c NeuralNetworks/Full_Connected.h NeuralNetworks/CNN.c NeuralNetworks/CNN.h)

add_executable(PI PI/main.c)

add_executable(SkipList SkipList/main.c)

