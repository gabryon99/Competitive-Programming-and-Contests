#ifndef CPC_FENWICKTREE_HPP
#define CPC_FENWICKTREE_HPP

#include "../utility.hpp"

namespace cpc::ds {
    template <typename TypeValue>
    class FenwickTree {

    private:
        std::vector<TypeValue> m_data{};

        explicit FenwickTree() {}
        explicit FenwickTree(std::size_t size): m_data(size, 0) {}

    public:
        explicit FenwickTree(std::initializer_list<TypeValue> values) {

            auto n = values.size() + 1;
            m_data = std::vector<TypeValue>(n, 0);

            for (std::size_t i = 1; i < n; i++) {
                add(i, m_data[i - 1]);
            }
        }

        static auto fromVector(const std::vector<TypeValue>& v) -> FenwickTree<TypeValue> {

            auto n = v.size() + 1;
            FenwickTree<TypeValue> tree(n);

            for (std::size_t i = 1; i < n; i++) {
                tree.add(i, v[i - 1]);
            }

            return tree;
        }

        auto add(std::size_t idx, TypeValue value) -> void {
            auto n = m_data.size();
            while (idx <= n) {
                m_data[idx] += value;
                idx += idx & (-idx);
            }
        }

        auto sum(std::size_t idx) -> TypeValue {

            TypeValue s{};

            while (idx != 0) {
                s += m_data[idx];
                idx -= idx & (-idx);
            }

            return s;
        }

        /***
         * Compute the range sum between the interval [left, right]
         * @param left
         * @param right
         * @return
         */
        auto rangeSum(std::size_t left, std::size_t right) -> TypeValue {
            return sum(right + 1) - sum(left - 1);
        }

        auto size() {
            return m_data.size() - 1;
        }

        auto operator[](std::size_t idx) -> TypeValue {
            return m_data[idx] - sum(idx - 1);
        }

    };
}
#endif //CPC_FENWICKTREE_HPP
