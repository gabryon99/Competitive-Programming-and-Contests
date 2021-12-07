#include <iostream>
#include "dynamic_programming/minimum_cost_path.hpp"

auto main() -> int {


    auto grid = cpc::utility::Matrix<int>{3, 4};
    grid(0, 0) = 1; grid(0, 1) = 2; grid(0, 2) = 6; grid(0, 3) = 9;
    grid(1, 0) = 0; grid(1, 1) = 0; grid(1, 2) = 3; grid(1, 3) = 1;
    grid(2, 0) = 2; grid(2, 1) = 7; grid(2, 2) = 7; grid(2, 3) = 2;

    auto problem = cpc::dp::MinimumCostPath{grid};
    problem.solve();

    return 0;
}
