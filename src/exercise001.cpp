/*
 * Performance Optimization Exercise
 *
 * Goal:
 * This project is intended as a hands-on exercise for identifying and
 * removing performance bottlenecks in existing code.
 *
 * Problem:
 * Given a collection of integers, compute the sum of the squares of all
 * even numbers.
 *
 * Example:
 * Input:  [1, 2, 3, 4, 5]
 * Output: 20
 * Reason: 2² + 4² = 4 + 16 = 20
 *
 * The project intentionally contains two implementations:
 *
 * 1) slow_even_square_sum()
 *    A deliberately inefficient implementation that still produces the
 *    correct result. It includes several common performance issues such as:
 *      - unnecessary copies
 *      - poor cache locality
 *      - redundant data transformations
 *      - dynamic allocations inside hot loops
 *      - excessive computational complexity
 *
 * 2) new_version_faster_even_square_sum()
 *    A progressively optimized version that removes those bottlenecks while
 *    preserving correctness.
 *
 * The objective is not only to make the code faster, but also to understand:
 *      - algorithmic complexity
 *      - memory access patterns
 *      - cache behavior
 *      - unnecessary allocations
 *      - compiler optimizations
 *      - benchmarking methodology
 *
 * All test cases are executed against both implementations and timed using
 * std::chrono for comparison.
*/

#include <list>
#include <chrono>
#include <vector>
#include <iostream>

long long slow_even_square_sum(std::vector<int> values) {
    std::list<int> temporary;

    for (auto value : values) {
        temporary.push_back(value);
    }

    long long result = 0;

    for (auto it = temporary.begin(); it != temporary.end(); ++it) {
        int value = *it;

        std::string number_as_string = std::to_string(value);

        int reconstructed = 0;

        for (char c : number_as_string) {
            reconstructed *= 10;
            reconstructed += (c - '0');
        }

        if (reconstructed % 2 == 0) {
            long square = 0;

            for (int i = 0; i < reconstructed; ++i) {
                square += reconstructed;
            }

            std::vector<long> useless_buffer;

            useless_buffer.reserve(100);

            for (int k = 0; k < 100; ++k) {
                useless_buffer.push_back(square + k);
            }

            result += useless_buffer.front();
        }
    }

    return result;
}

/* New version with improvements */
auto new_version_faster_even_square_sum(const std::vector<int>& values) {
    long long result = 0;

    for (const auto& it : values) {
        if ((it & 1) == 0) {
                result += 1LL * it * it;
        }
    }

    return result;
}

int main()
{
    {
        const std::vector test{1, 2, 3, 4, 5};

        const auto start_old = std::chrono::high_resolution_clock::now();
        const auto result_old = slow_even_square_sum(test);
        const auto end_old = std::chrono::high_resolution_clock::now();

        const auto start_new = std::chrono::high_resolution_clock::now();
        const auto result_new = new_version_faster_even_square_sum(test);
        const auto end_new = std::chrono::high_resolution_clock::now();

        std::cout << "\n===== TEST 1 =====\n";
        std::cout << "Expected: 20\n";

        std::cout << "Old Result: " << result_old
                  << " | Time: "
                  << std::chrono::duration_cast<std::chrono::nanoseconds>(
                         end_old - start_old)
                         .count()
                  << " ns\n";

        std::cout << "New Result: " << result_new
                  << " | Time: "
                  << std::chrono::duration_cast<std::chrono::nanoseconds>(
                         end_new - start_new)
                         .count()
                  << " ns\n";
    }

    {
        const std::vector test{2, 4, 6};

        const auto start_old = std::chrono::high_resolution_clock::now();
        const auto result_old = slow_even_square_sum(test);
        const auto end_old = std::chrono::high_resolution_clock::now();

        const auto start_new = std::chrono::high_resolution_clock::now();
        const auto result_new = new_version_faster_even_square_sum(test);
        const auto end_new = std::chrono::high_resolution_clock::now();

        std::cout << "\n===== TEST 2 =====\n";
        std::cout << "Expected: 56\n";

        std::cout << "Old Result: " << result_old
                  << " | Time: "
                  << std::chrono::duration_cast<std::chrono::nanoseconds>(
                         end_old - start_old)
                         .count()
                  << " ns\n";

        std::cout << "New Result: " << result_new
                  << " | Time: "
                  << std::chrono::duration_cast<std::chrono::nanoseconds>(
                         end_new - start_new)
                         .count()
                  << " ns\n";
    }

    {
        const std::vector test{1, 3, 5, 7, 9};

        const auto start_old = std::chrono::high_resolution_clock::now();
        const auto result_old = slow_even_square_sum(test);
        const auto end_old = std::chrono::high_resolution_clock::now();

        const auto start_new = std::chrono::high_resolution_clock::now();
        const auto result_new = new_version_faster_even_square_sum(test);
        const auto end_new = std::chrono::high_resolution_clock::now();

        std::cout << "\n===== TEST 3 =====\n";
        std::cout << "Expected: 0\n";

        std::cout << "Old Result: " << result_old
                  << " | Time: "
                  << std::chrono::duration_cast<std::chrono::nanoseconds>(
                         end_old - start_old)
                         .count()
                  << " ns\n";

        std::cout << "New Result: " << result_new
                  << " | Time: "
                  << std::chrono::duration_cast<std::chrono::nanoseconds>(
                         end_new - start_new)
                         .count()
                  << " ns\n";
    }

    {
        const std::vector test(100000, 10000);

        const auto start_old = std::chrono::high_resolution_clock::now();
        const auto result_old = slow_even_square_sum(test);
        const auto end_old = std::chrono::high_resolution_clock::now();

        const auto start_new = std::chrono::high_resolution_clock::now();
        const auto result_new = new_version_faster_even_square_sum(test);
        const auto end_new = std::chrono::high_resolution_clock::now();

        std::cout << "\n===== TEST 4 (STRESS TEST) =====\n";

        std::cout << "Old Result: " << result_old
                  << " | Time: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(
                         end_old - start_old)
                         .count()
                  << " ms\n";

        std::cout << "New Result: " << result_new
                  << " | Time: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(
                         end_new - start_new)
                         .count()
                  << " ms\n";
    }

    return 0;
}