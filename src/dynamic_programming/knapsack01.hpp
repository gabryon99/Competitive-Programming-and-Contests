//
// Created by Gabriele Pappalardo on 07/12/21.
//

#include <iostream>
#include <vector>

#include "../utility/solution.hpp"
#include "../utility/matrix.hpp"

namespace cpc::dp {
    /***
     * We have n items. For each item i we have a value v_i and a weight w_i. The goial is to
     * select a subset of items with total weight <= C (max capacity) that maximize
     * the overall revenue.
     */
    class Knapsack01 : public cpc::Solution {

        long max_capacity;
        std::vector<long> values;
        std::vector<long> weights;

    public:
        Knapsack01(std::vector<long> v, std::vector<long> w, long c) : values{std::move(v)}, weights{std::move(w)},
                                                                       max_capacity{c} {}

        /***
         * The following solution uses a Dynamic Programming top-down approach.
         * K(i, j):
         *      - select item i then = K(i - 1, j - wi) + vi
         *      - do not select item i then = K(i - 1, j)
         */
        void solve() override {

            auto K = cpc::utility::Matrix<long>{values.size() + 1, static_cast<size_t>(max_capacity + 1)};

            for (std::size_t i = 0; i < K.rows; i++) {
                for (std::size_t j = 0; j < K.columns; j++) {

                    if (i == 0) {
                        K(i, j) = 0;
                    }
                    else {

                        auto vi = values[i - 1];
                        auto wi = weights[i - 1];

                        long diff = static_cast<long>(j) - wi;

                        if (diff >= 0) {
                            K(i, j) = std::max(K(i - 1, j - wi) + vi, K(i - 1, j));
                        }
                        else {
                            K(i, j) = K(i - 1, j);
                        }
                    }
                }
            }

            std::cout << "Best Value: " << K(K.rows - 1, K.columns - 1) << "\n";

        }
    };
}