#ifndef CPC_TRAPPING_WATER_HPP
#define CPC_TRAPPING_WATER_HPP

#include <vector>
#include <numeric>
#include <iostream>

#include "../utility/solution.hpp"

namespace cpc::exercises {

    /***
     * Given n numbers representing an elevation map, we would like to compute how much water
     * it's able to trap.
     */
    class TrappingWater : public cpc::Solution {

    private:
        std::vector<int> input;

    public:

        explicit TrappingWater(std::vector<int> input) : input(std::move(input)) {}

        void quadraticSolution() {

            auto size = input.size();
            auto water = 0;

            for (std::size_t i = 0; i < size; i++) {

                auto leftSide = input[i];
                for (std::size_t j = 0; j < i; j++) leftSide = std::max(leftSide, input[j]);

                auto rightSide = input[i];
                for (std::size_t j = i + 1; j < size; j++) rightSide = std::max(rightSide, input[j]);

                water += std::min(leftSide, rightSide) - input[i];
            }

            std::cout << "Solution: " << water << "\n";
        }

        void linearSolution() {

            auto size = input.size();
            auto water = 0;

            std::vector<int> trappedWater(size);
            std::vector<int> ll(size); // Left leaders
            std::vector<int> rr(size); // Right leaders

            ll[0] = input[0];
            for (int i = 1; i < size; i++) ll[i] = std::max(ll[i - 1], input[i]);

            rr[size - 1] = input[size - 1];
            for (int i = size - 2; i >= 0; i--) rr[i] = std::max(rr[i + 1], input[i]);

            for (std::size_t i = 0; i < size; i++) {
                water += std::min(ll[i], rr[i]) - input[i];
            }

            std::cout << "Solution: " << water << "\n";
        }

        void solve() override {
            quadraticSolution();
            linearSolution();
        }
    };
}

#endif //CPC_TRAPPING_WATER_HPP
