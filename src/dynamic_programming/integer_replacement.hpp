//
// Created by Gabriele Pappalardo on 07/12/21.
//

#include <unordered_map>
#include <iostream>
#include "../utility/solution.hpp"

#ifndef CPC_INTEGER_REPLACEMENT_HPP
#define CPC_INTEGER_REPLACEMENT_HPP

namespace cpc::dp {

    /***
     * Given a positive integer n, you can apply one of the following operations:
     * 1. If n is even, replace n with n / 2.
     * 2. If n is odd, replace n with either n + 1 or n - 1.
     * If n is odd, replace n with either n + 1 or n - 1.
     *
     * See: https://leetcode.com/problems/integer-replacement/
     */
    class IntegerReplacement : public cpc::Solution {

        long n = 0;
        std::unordered_map<long, long> mem_table;

        long integerReplacement(long n0) {

            if (n0 == 0 || n0 == 1) return 0;
            if (mem_table.contains(n0)) return mem_table[n0];

            long temp = 1;

            if (n0 % 2 == 0) {
                temp += integerReplacement(n0 / 2);
            }
            else {
                temp += std::min(integerReplacement(n0 + 1), integerReplacement(n0 - 1));
            }

            mem_table[n0] = temp;

            return temp;
        }

    public:

        explicit IntegerReplacement(long n) : n{n} {}

        void solve() override {
            std::cout << "For the number " << n << ", we need: " << integerReplacement(n) << " steps.\n";
        }

    };
}

#endif //CPC_INTEGER_REPLACEMENT_HPP
