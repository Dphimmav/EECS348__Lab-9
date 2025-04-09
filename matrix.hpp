#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <cstdint>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <fstream>

template <typename T>
class Matrix {
private:
    std::size_t N;
    std::vector<std::vector<T>> data;

public:
    Matrix(std::size_t size) : N(size), data(size, std::vector<T>(size)) {}
    
    Matrix(const std::vector<std::vector<T>>& nums) : N(nums.size()), data(nums) {
        for (const auto& row : nums) {
            if (row.size() != N) {
                throw std::invalid_argument("Input is not a square matrix");
            }
        }
    }

    Matrix operator+(const Matrix &rhs) const {
        if (N != rhs.N) {
            throw std::invalid_argument("Matrix sizes don't match for addition");
        }
        
        Matrix result(N);
        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = 0; j < N; ++j) {
                result.data[i][j] = data[i][j] + rhs.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix &rhs) const {
        if (N != rhs.N) {
            throw std::invalid_argument("Matrix sizes don't match for multiplication");
        }
        
        Matrix result(N);
        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = 0; j < N; ++j) {
                T sum = 0;
                for (std::size_t k = 0; k < N; ++k) {
                    sum += data[i][k] * rhs.data[k][j];
                }
                result.data[i][j] = sum;
            }
        }
        return result;
    }

    void set_value(std::size_t i, std::size_t j, T n) {
        if (i >= N || j >= N) {
            throw std::out_of_range("Index out of bounds");
        }
        data[i][j] = n;
    }

    T get_value(std::size_t i, std::size_t j) const {
        if (i >= N || j >= N) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[i][j];
    }

    std::size_t get_size() const {
        return N;
    }

    T sum_diagonal_major() const {
        T sum = 0;
        for (std::size_t i = 0; i < N; ++i) {
            sum += data[i][i];
        }
        return sum;
    }

    T sum_diagonal_minor() const {
        T sum = 0;
        for (std::size_t i = 0; i < N; ++i) {
            sum += data[i][N - 1 - i];
        }
        return sum;
    }

    void swap_rows(std::size_t r1, std::size_t r2) {
        if (r1 >= N || r2 >= N) {
            throw std::out_of_range("Row index out of bounds");
        }
        std::swap(data[r1], data[r2]);
    }

    void swap_cols(std::size_t c1, std::size_t c2) {
        if (c1 >= N || c2 >= N) {
            throw std::out_of_range("Column index out of bounds");
        }
        for (std::size_t i = 0; i < N; ++i) {
            std::swap(data[i][c1], data[i][c2]);
        }
    }

    void print_matrix() const {
        for (const auto& row : data) {
            for (const auto& val : row) {
                std::cout << std::setw(8) << val;
            }
            std::cout << std::endl;
        }
    }

    static Matrix<T> read_from_file(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file");
        }

        std::size_t size;
        int type_flag;
        file >> size >> type_flag;

        Matrix<T> matrix(size);
        
        for (std::size_t i = 0; i < size; ++i) {
            for (std::size_t j = 0; j < size; ++j) {
                T val;
                file >> val;
                matrix.set_value(i, j, val);
            }
        }

        return matrix;
    }
};

#endif // __MATRIX_HPP__
