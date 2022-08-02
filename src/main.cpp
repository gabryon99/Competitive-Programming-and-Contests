#include "utility/utility.hpp"

#include "exercises/array_leaders.hpp"

auto main() -> int {

    auto sol = cpc::exercises::ArrayLeaders::solve<int>({16,17,4,3,5,2});
    cpc::assertEquality(sol, {2, 5, 17});

    return 0;
}
