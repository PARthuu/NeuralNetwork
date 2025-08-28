cmake_minimum_required(VERSION 3.10)
project(NeuralNet)

# Enable compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_library(NeuralNet STATIC ${SOURCES})

add_executable(train examples/train.cpp)
target_link_libraries(train NeuralNet)

add_executable(run_nn examples/run_nn.cpp)
target_link_libraries(run_nn NeuralNet)

add_executable(test_network tests/test_network.cpp)
target_link_libraries(test_network NeuralNet)

