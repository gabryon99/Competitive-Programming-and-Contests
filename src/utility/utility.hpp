#ifndef CPC_UTILITY_HPP
#define CPC_UTILITY_HPP

#include <concepts>
#include <vector>
#include <iostream>

namespace cpc {

    template<typename T>
    auto printVector(const std::vector<T>& v) {
        for (const auto& vi : v) std::cout << vi << " ";
        std::cout << "\n";
    }

    template<std::totally_ordered T>
    void assertEquality(const std::vector<T>& v1, const std::vector<T>& v2) {

        if (v1.size() != v2.size()) throw std::runtime_error("Vectors have different size.");
        for (std::size_t i = 0; i < v1.size(); i++) {
            if (v1[i] != v2[i]) throw std::runtime_error("Vectors are not equal.");
        }

    }

}
#endif //CPC_UTILITY_HPP
