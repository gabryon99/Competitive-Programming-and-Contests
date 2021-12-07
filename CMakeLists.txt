cmake_minimum_required(VERSION 3.20)
project(cpc)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpc src/main.cpp src/utility/matrix.hpp src/dynamic_programming/knapsack01.hpp src/utility/solution.hpp src/dynamic_programming/subset_sum_problem.hpp)
