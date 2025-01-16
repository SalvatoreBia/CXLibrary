#include <iostream>
#include <chrono>
#include "../include/CXLibrary.h"

int main() {
    using namespace cx_lib;
    
    // 1. Basic complex number operations
    std::cout << "Complex Number Operations:\n";
    cx a(1, 2);    // 1 + 2i
    cx b(2, -1);   // 2 - i
    std::cout << "a = " << a << "\nb = " << b << std::endl;
    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "a * b = " << a * b << std::endl;
    std::cout << "magnitude of a = " << a.mod() << std::endl;

    // 2. Vector operations
    std::cout << "\nVector Operations:\n";
    cx_vector v1({cx(1,0), cx(0,1), cx(1,1), cx(1,0), cx(0,1), cx(1,1), cx(1,0), cx(0,1), cx(1,1), cx(1,0), cx(0,1), cx(1,1)});
    cx_vector v2({cx(2,0), cx(0,2), cx(2,2), cx(2,0), cx(0,2), cx(2,2), cx(2,0), cx(0,2), cx(2,2), cx(2,0), cx(0,2), cx(2,2)});
    std::cout << "v1 + v2 = " << v1 + v2 << std::endl;
    std::cout << "dot product = " << v1.dot(v2) << std::endl;

    // 3. Matrix operations with multithreading
    std::cout << "\nMatrix Operations:\n";
    cx_matrix m1(2, 2, cx(1,1));
    cx_matrix m2(2, 2, cx(2,0));
    
    auto start = std::chrono::high_resolution_clock::now();
    auto m3 = matmul(m1, m2);
    auto end = std::chrono::high_resolution_clock::now();
    
    std::cout << "Matrix multiplication result:\n" << m3 << std::endl;
    std::cout << "Time: " 
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() 
              << " μs\n";

    // 4. Tensor operations and broadcasting
    std::cout << "\nTensor Operations:\n";
    cx_tensor t1({2, 2}, cx(1,0));
    cx_tensor t2({2, 2}, cx(0,1));
    auto t3 = t1 + t2;
    std::cout << "First element of tensor sum: " << t3[0] << std::endl;

    // 5. Performance comparison (single vs multi-threaded)
    std::cout << "\nPerformance Comparison:\n";
    cx_matrix large1(100, 100, cx(1,1));
    cx_matrix large2(100, 100, cx(2,2));

    enable_multithreading(false);
    start = std::chrono::high_resolution_clock::now();
    matmul(large1, large2);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Single-threaded: " 
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() 
              << " μs\n";

    enable_multithreading(true);
    start = std::chrono::high_resolution_clock::now();
    matmul(large1, large2);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Multi-threaded: " 
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() 
              << " μs\n";

    return 0;
}