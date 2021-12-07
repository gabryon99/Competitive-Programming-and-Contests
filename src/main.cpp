#include <iostream>
#include "dynamic_programming/integer_replacement.hpp"

auto main() -> int {

    auto problem = cpc::dp::IntegerReplacement{7};
    problem.solve();

    return 0;
}
