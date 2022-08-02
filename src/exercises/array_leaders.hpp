#ifndef CPC_ARRAY_LEADERS_HPP
#define CPC_ARRAY_LEADERS_HPP

#include "../utility/utility.hpp"
#include "../utility/solution.hpp"

namespace cpc::exercises {
    class ArrayLeaders : public cpc::Solution {

    public:

        template<std::totally_ordered T>
        static std::vector<T> solve(std::vector<T> input) {

            auto size = input.size();

            std::vector<T> leaders{};
            T maxElement = input[size - 1];

            leaders.push_back(input[size - 1]);

            for (int i = size; i >= 0; i--) {
                if (input[i] > maxElement) {
                    maxElement = input[i];
                    leaders.push_back(maxElement);
                }
            }

            return leaders;
        }
    };
}

#endif //CPC_ARRAY_LEADERS_HPP
