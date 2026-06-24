#include <list>
#include <cmath>
#include <string>
#include <chrono>
#include <vector>
#include <iostream>

/*
 * Problem:
 *
 * Given a vector of integers, return the sum of the absolute differences
 * between every unique pair of elements.
 *
 * Example:
 *
 * Input:  {1, 4, 7}
 *
 * Pairs:
 * |1 - 4| = 3
 * |1 - 7| = 6
 * |4 - 7| = 3
 *
 * Output:
 * 12
 *
 * This implementation is intentionally inefficient while still producing
 * the correct result.
 */

/* Old version */
long long slow_pairwise_distance_sum(std::vector<int> values)
{
    std::list<int> container;

    for (auto value : values)
    {
        container.push_back(value);
    }

    std::vector<int> reconstructed_values;

    for (const auto& value : container)
    {
        std::string text = std::to_string(value);

        int reconstructed = 0;

        for (char c : text)
        {
            reconstructed *= 10;
            reconstructed += (c - '0');
        }

        reconstructed_values.push_back(reconstructed);
    }

    long long result = 0;

    for (size_t i = 0; i < reconstructed_values.size(); ++i)
    {
        for (size_t j = 0; j < reconstructed_values.size(); ++j)
        {
            if (i == j)
            {
                continue;
            }

            int a = reconstructed_values[i];
            int b = reconstructed_values[j];

            std::vector<int> useless_buffer;

            useless_buffer.reserve(32);

            for (int k = 0; k < 32; ++k)
            {
                useless_buffer.push_back(a + b + k);
            }
            result += std::abs(a - b);
        }
    }

    return result / 2;
}

/* New version */
long long new_faster_pairwise_distance_sum(const std::vector<int>& values) {
    long long result = 0;

    for (size_t i = 0; i < values.size(); ++i) {
        for (size_t j = i + 1; j < values.size(); ++j) {

            result += std::abs(values[i] - values[j]);
        }
    }
    return result;
}

int main()
{
    {
        const std::vector<int> test{1, 4, 7};

        const auto start_old =
            std::chrono::high_resolution_clock::now();

        const auto result_old =
            slow_pairwise_distance_sum(test);

        const auto end_old =
            std::chrono::high_resolution_clock::now();

        const auto start_new =
            std::chrono::high_resolution_clock::now();

        const auto result_new =
            new_faster_pairwise_distance_sum(test);

        const auto end_new =
            std::chrono::high_resolution_clock::now();

        std::cout << "\n===== TEST 1 =====\n";
        std::cout << "Expected: 12\n";

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
        const std::vector<int> test{2, 4, 6};

        const auto start_old =
            std::chrono::high_resolution_clock::now();

        const auto result_old =
            slow_pairwise_distance_sum(test);

        const auto end_old =
            std::chrono::high_resolution_clock::now();

        const auto start_new =
            std::chrono::high_resolution_clock::now();

        const auto result_new =
            new_faster_pairwise_distance_sum(test);

        const auto end_new =
            std::chrono::high_resolution_clock::now();

        std::cout << "\n===== TEST 2 =====\n";
        std::cout << "Expected: 8\n";

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
        const std::vector<int> test{10, 20, 30, 40};

        const auto start_old =
            std::chrono::high_resolution_clock::now();

        const auto result_old =
            slow_pairwise_distance_sum(test);

        const auto end_old =
            std::chrono::high_resolution_clock::now();

        const auto start_new =
            std::chrono::high_resolution_clock::now();

        const auto result_new =
            new_faster_pairwise_distance_sum(test);

        const auto end_new =
            std::chrono::high_resolution_clock::now();

        std::cout << "\n===== TEST 3 =====\n";
        std::cout << "Expected: 100\n";

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
        std::vector<int> test(5000);

        for (int i = 0; i < 5000; ++i)
        {
            test[i] = i;
        }

        const auto start_old =
            std::chrono::high_resolution_clock::now();

        const auto result_old =
            slow_pairwise_distance_sum(test);

        const auto end_old =
            std::chrono::high_resolution_clock::now();

        const auto start_new =
            std::chrono::high_resolution_clock::now();

        const auto result_new =
            new_faster_pairwise_distance_sum(test);

        const auto end_new =
            std::chrono::high_resolution_clock::now();

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