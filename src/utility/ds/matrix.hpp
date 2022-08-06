#include <vector>
#include <iostream>

#ifndef CPC_MATRIX_H
#define CPC_MATRIX_H

namespace cpc::utility {
    template<class T>
    struct Matrix {

        std::size_t rows;
        std::size_t columns;

        explicit Matrix() {}

        Matrix(std::size_t r, std::size_t c) noexcept : rows{r}, columns{c} {
            data.resize(r * c);
        }

        T& operator()(std::size_t x, std::size_t y) {

            std::size_t index = std::max(rows, columns) * x + y;
            if (index >= data.size()) {
                std::cerr << "x: " << x << ", y: " << y << "\n";
                throw std::out_of_range("Invalid matrix access!");
            }

            return data[index];
        }

        typename std::vector<T>::iterator begin() {
            return data.begin();
        }

        typename std::vector<T>::iterator end() {
            return data.end();
        }

        void dump() {
            for (std::size_t i = 0; i < rows; i++) {
                for (std::size_t j = 0; j < columns; j++) {
                    std::cout << this->operator()(i, j) << " ";
                }
                std::cout << "\n";
            }
        }

    private:
        std::vector<T> data;

    };
}

#endif //CPC_MATRIX_H
