#ifndef CPC_SEARCHING_HPP
#define CPC_SEARCHING_HPP

#include <cmath>

#include "../utility/utility.hpp"

namespace cpc::searching {

    auto binarySearch(const std::vector<int>& numbers, int key, int l, int r) -> int {

        if (l <= r) {

            int middle = (r + l) / 2;

            if (numbers[middle] == key) {
                return middle;
            }

            if (numbers[middle] > key) {
                return binarySearch(numbers, key, l, middle - 1);
            }
            else {
                return binarySearch(numbers, key, middle + 1, r);
            }
        }

        return -1;
    }

    auto exponentialSearch(const std::vector<int>& numbers, int key) -> int {

        if (numbers[0] == key) return 0;

        int power = 1;
        int size = numbers.size();

        while (power < size && numbers[power] <= key) {
            power *= 2;
        }

        int left = power / 2;
        int right = std::min(power, static_cast<int>(size - 1));

        return binarySearch(numbers, key, left, right);
    }

}

#endif //CPC_SEARCHING_HPP
