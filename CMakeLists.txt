cmake_minimum_required(VERSION 3.20)
project(cpc)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpc
        src/main.cpp
        src/utility/utility.hpp
        src/utility/ds/matrix.hpp
        src/utility/ds/binar_search_tree.hpp
        src/utility/ds/binary_search_tree_v.hpp
        src/utility/ds/fenwick_tree.hpp
        src/searching/searching.hpp
        src/exercises/inversion_count.hpp
        src/dynamic_programming/knapsack01.hpp
        src/utility/solution.hpp
        src/dynamic_programming/subset_sum_problem.hpp
        src/dynamic_programming/minimum_cost_path.hpp
        src/dynamic_programming/integer_replacement.hpp
        src/exercises/trapping_water.hpp
        src/exercises/sliding_window_maxima.hpp
        src/exercises/array_leaders.hpp)
