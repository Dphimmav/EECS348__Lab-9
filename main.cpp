#include <iostream>
#include <fstream>
#include <stdexcept>
#include "matrix.hpp"

using namespace std;

// Helper function to print test results
void print_test_result(const string& test_name, bool passed) {
    cout << test_name << ": " << (passed ? "PASSED" : "FAILED") << endl;
}

// Test matrix construction and size
void test_construction() {
    bool passed = true;
    
    Matrix<int> m1({{1, 2}, {3, 4}});
    if (m1.get_size() != 2) passed = false;
    
    Matrix<int> m2(0);
    if (m2.get_size() != 0) passed = false;
    
    print_test_result("Construction and Size", passed);
}

// Test element access
void test_element_access() {
    bool passed = true;
    Matrix<int> m({{1, 2}, {3, 4}});
    
    if (m.get_value(0, 0) != 1) passed = false;
    if (m.get_value(1, 1) != 4) passed = false;
    
    // Test out of bounds
    try {
        m.get_value(2, 2);
        passed = false; // Should throw exception
    } catch (const out_of_range&) {}
    
    print_test_result("Element Access", passed);
}

// Test matrix addition
void test_addition() {
    bool passed = true;
    Matrix<int> m1({{1, 2}, {3, 4}});
    Matrix<int> m2({{4, 3}, {2, 1}});
    
    auto result = m1 + m2;
    if (result.get_value(0, 0) != 5 ||
        result.get_value(0, 1) != 5 ||
        result.get_value(1, 0) != 5 ||
        result.get_value(1, 1) != 5) {
        passed = false;
    }
    
    print_test_result("Matrix Addition", passed);
}

// Test matrix multiplication
void test_multiplication() {
    bool passed = true;
    Matrix<int> m1({{1, 2}, {3, 4}});
    Matrix<int> m2({{5, 6}, {7, 8}});
    
    auto result = m1 * m2;
    if (result.get_value(0, 0) != 19 ||
        result.get_value(0, 1) != 22 ||
        result.get_value(1, 0) != 43 ||
        result.get_value(1, 1) != 50) {
        passed = false;
    }
    
    print_test_result("Matrix Multiplication", passed);
}

// Test diagonal sums
void test_diagonal_sums() {
    bool passed = true;
    Matrix<int> m({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    
    if (m.sum_diagonal_major() != 15) passed = false;
    if (m.sum_diagonal_minor() != 15) passed = false;
    
    print_test_result("Diagonal Sums", passed);
}

// Test row and column swapping
void test_swapping() {
    bool passed = true;
    Matrix<int> m({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    
    // Test row swap
    m.swap_rows(0, 1);
    if (m.get_value(0, 0) != 4 || m.get_value(1, 0) != 1) passed = false;
    
    // Test column swap
    m.swap_cols(1, 2);
    if (m.get_value(0, 1) != 6 || m.get_value(0, 2) != 5) passed = false;
    
    // Test invalid swaps
    try {
        m.swap_rows(0, 3);
        passed = false;
    } catch (const out_of_range&) {}
    
    print_test_result("Row/Column Swapping", passed);
}

// Test file reading
void test_file_reading() {
    bool passed = true;
    
    // Create test file
    ofstream out("test_matrix.txt");
    out << "2 0\n1 2\n3 4\n5 6\n7 8\n";
    out.close();
    
    try {
        auto m = Matrix<int>::read_from_file("test_matrix.txt");
        if (m.get_size() != 2 ||
            m.get_value(0, 0) != 1 ||
            m.get_value(1, 1) != 4) {
            passed = false;
        }
    } catch (...) {
        passed = false;
    }
    
    remove("test_matrix.txt");
    print_test_result("File Reading", passed);
}

// Test double precision matrices
void test_double_matrix() {
    bool passed = true;
    Matrix<double> m1({{1.5, 2.5}, {3.5, 4.5}});
    Matrix<double> m2({{0.5, 1.5}, {2.5, 3.5}});
    
    auto sum = m1 + m2;
    if (sum.get_value(0, 0) != 2.0 ||
        sum.get_value(1, 1) != 8.0) {
        passed = false;
    }
    
    print_test_result("Double Precision Matrices", passed);
}

int main() {
    cout << "Running Matrix Tests...\n";
    cout << "----------------------\n";
    
    test_construction();
    test_element_access();
    test_addition();
    test_multiplication();
    test_diagonal_sums();
    test_swapping();
    test_file_reading();
    test_double_matrix();
    
    cout << "----------------------\n";
    cout << "Tests complete.\n";
    
    return 0;
}
