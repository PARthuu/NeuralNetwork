cmake_minimum_required(VERSION 3.10)
project(NeuralNet)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_library(NeuralNet STATIC ${SOURCES})

add_executable(xor_example examples/xor_example.cpp)
target_link_libraries(xor_example NeuralNet)

add_executable(test_network tests/test_network.cpp)
target_link_libraries(test_network NeuralNet)
