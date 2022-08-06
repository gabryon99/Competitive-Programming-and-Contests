#define DEBUG

#include "utility/utility.hpp"
#include "utility/ds/fenwick_tree.hpp"

auto main() -> int {

    using FenwickTree = cpc::ds::FenwickTree<int>;
    auto tree = FenwickTree::fromVector({3, 2, -1, 5, 7, -3, 2, 1});

    std::cout << tree.rangeSum(2, 5);

    return 0;
}
