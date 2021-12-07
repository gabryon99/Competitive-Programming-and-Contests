#include <iostream>
#include "dynamic_programming/subset_sum_problem.hpp"

auto main() -> int {

    auto values = std::vector<long>{3, 2, 5, 1};
    auto problem = cpc::dp::SubsetSubProblem{values, 6};

    problem.solve();

    return 0;
}
