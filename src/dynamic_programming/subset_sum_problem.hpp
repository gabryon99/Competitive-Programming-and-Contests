//
// Created by Gabriele Pappalardo on 07/12/21.
//

#ifndef CPC_SUBSET_SUM_PROBLEM_HPP
#define CPC_SUBSET_SUM_PROBLEM_HPP

#include <iostream>
#include "../utility/matrix.hpp"
#include "../utility/solution.hpp"

namespace cpc::dp {

    /***
     * Given a set S of integers and a target value v, is there any subset of S with sum v?
     */
    class SubsetSubProblem : public Solution {

        long target_sum;
        std::vector<long> set{};

    public:
        SubsetSubProblem(std::vector<long> s, long t) : set{std::move(s)}, target_sum{t} {}

        void solve() override {

            auto M = cpc::utility::Matrix<int>{set.size() + 1, static_cast<std::size_t>(target_sum) + 1};

            for (std::size_t i = 0; i < M.rows; i++) {
                for (std::size_t j = 0; j < M.columns; j++) {

                    if (i == 0 && j == 0) {
                        M(i, j) = 1;
                    }
                    else if (i == 0 && j >= 1) {
                        M(i, j) = 0;
                    }
                    else {

                        auto si = set[i - 1];
                        auto diff = static_cast<long>(j) - si;

                        if (diff >= 0) {
                            M(i, j) = M(i - 1, j) || M(i - 1, diff);
                        }
                        else {
                            M(i, j) = M(i - 1, j);
                        }
                    }
                }
            }

            std::cout << "Is there a subset? " << ((M(M.rows - 1, M.columns - 1) == 1) ? "Yes ✅" : "No ❌") << "\n";
        }
    };
}
#endif //CPC_SUBSET_SUM_PROBLEM_HPP
