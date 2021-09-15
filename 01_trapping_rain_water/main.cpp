/**
 * @brief Given n non-negative integers representing an elevation map where the width of each bar is 1, 
 * compute how much water it can trap after raining.
 */

#include <cstdio>
#include <vector>
#include <numeric>
#include <algorithm>

auto brute_force(const std::vector<int>& heights) -> int {

    auto sum = 0;

    for (std::size_t i = 0; i < heights.size(); i++) {

        auto max_on_left = *std::max_element(std::begin(heights), std::begin(heights) + i + 1);
        auto max_on_right = *std::max_element(std::begin(heights) + i, std::end(heights));

        sum += std::min(max_on_left, max_on_right) - heights[i];
    }

    return sum;
}

auto main(int argc, char** argv) -> int {
    
    auto heights = std::vector<int>{4, 2, 0, 3, 2, 5};
    std::fprintf(stdout, "%d\n", brute_force(heights));

    return 0;
}