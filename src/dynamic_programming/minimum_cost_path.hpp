//
// Created by Gabriele Pappalardo on 07/12/21.
//

#ifndef CPC_MINIMUM_COST_PATH_HPP
#define CPC_MINIMUM_COST_PATH_HPP

#include <iostream>
#include "../utility/matrix.hpp"
#include "../utility/solution.hpp"

namespace cpc::dp {

    /***
     * Given a matrix M (n * m) containing integers, compute the path of minimum cost
     * from (1, 1) to (n, m) by moving down or right.
     */
    class MinimumCostPath : public cpc::Solution {

        cpc::utility::Matrix<int>& grid;

    public:
        explicit MinimumCostPath(cpc::utility::Matrix<int>& g) {
            grid = g;
        }

        void solve() override {

            auto W = cpc::utility::Matrix<int>{grid.rows, grid.columns};

            for (std::size_t i = 0; i < W.rows; i++) {
                for (std::size_t j = 0; j < W.columns; j++) {

                    if (i == 0 && j == 0) {
                        W(i, j) = grid(i, j);
                    }
                    else if (i == 0 && j > 0) {
                        W(i, j) = grid(i, j) + W(i, j - 1);
                    }
                    else if (j == 0 && i > 0) {
                        W(i, j) = grid(i, j) + W(i - 1, j);
                    }
                    else {
                        W(i, j) = grid(i, j) + std::min(W(i - 1, j), W(i, j - 1));
                    }

                }
            }

            std::cout << "Minimum Cost: " << W(W.rows - 1, W.columns - 1) << "\n";
        }
    };
}

#endif //CPC_MINIMUM_COST_PATH_HPP
