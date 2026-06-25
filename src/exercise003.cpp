#include <list>
#include <string>
#include <vector>
#include <chrono>
#include <numeric>
#include <iostream>
#include <algorithm>

/*
 * Performance Optimization Exercise #3
 *
 * Problem:
 *
 * Given a sequence of events sorted by timestamp, compute, for every event,
 * the sum of all event values that fall within a sliding time window.
 *
 * An event j belongs to the window of event i if:
 *
 *     timestamp[i] - timestamp[j] <= window
 *
 * and
 *
 *     timestamp[j] <= timestamp[i]
 *
 * Example:
 *
 * Window = 10
 *
 * Events:
 *
 * (1, 5)
 * (3, 2)
 * (8, 4)
 * (15, 3)
 *
 * Expected Output:
 *
 * [5, 7, 11, 7]
 *
 * Explanation:
 *
 * Event 1:
 *   [5]
 *
 * Event 2:
 *   [5 + 2]
 *
 * Event 3:
 *   [5 + 2 + 4]
 *
 * Event 4:
 *   [4 + 3]
 *
 * Goal:
 *
 * This exercise is intended to develop the ability to identify
 * algorithmic bottlenecks and memory inefficiencies.
 *
 * The baseline implementation is intentionally inefficient while
 * still producing correct results.
 *
 * Areas of optimization include:
 *
 * - Unnecessary copies
 * - Poor cache locality
 * - Redundant computations
 * - Dynamic allocations in hot loops
 * - Inefficient containers
 * - Algorithmic complexity
 *
 * The biggest optimization opportunity is recognizing that this
 * problem can be solved using a Sliding Window / Two Pointers
 * approach instead of repeatedly scanning previous elements.
 */

struct Event
{
    long long timestamp;
    int value;
};

/*
 * Intentionally inefficient implementation.
 */
std::vector<long long>
slow_window_aggregation(std::vector<Event> events, long long window) {
    std::list<Event> buffer;

    for (const auto& e : events) {
        buffer.push_back(e);
    }

    std::vector<long long> result;

    for (auto outer = buffer.begin(); outer != buffer.end(); ++outer) {
        long long sum = 0;

        for (auto inner = buffer.begin(); inner != buffer.end(); ++inner) {
            if (inner->timestamp > outer->timestamp) {
                continue;
            }

            long long delta =
                outer->timestamp -
                inner->timestamp;

            if (delta <= window) {
                std::string text =
                    std::to_string(inner->value);

                int reconstructed = 0;

                for (char c : text) {
                    reconstructed *= 10;
                    reconstructed += c - '0';
                }

                std::vector<int> useless;

                useless.reserve(16);

                for (int k = 0; k < 16; ++k) {
                    useless.push_back(k);
                }

                sum += reconstructed;
            }
        }

        result.push_back(sum);
    }

    return result;
}

/*
 * New version.
 */
std::vector<long long>
faster_window_aggregation(const std::vector<Event>& events, const long long& window) {
    std::vector<long long> result;
    result.reserve(events.size());
    size_t left = 0;
    long long sum = 0;

    for (size_t right = 0; right < events.size(); ++ right) {
        sum += events[right].value;

        while (events[right].timestamp - events[left].timestamp > window) {
            sum -= events[left].value;
            ++left;
        }

        result.push_back(sum);
    }
    return result;
}

int main()
{
    auto benchmark =
        [](const std::vector<Event>& events,
           const long long window,
           const std::string& test_name)
    {
        constexpr int runs = 10;

        std::vector<long long> old_runs;
        std::vector<long long> new_runs;

        const auto old_output =
            slow_window_aggregation(events,
                                    window);

        const auto new_output =
            faster_window_aggregation(events,
                                      window);

        std::cout << "\n=================================\n";
        std::cout << test_name << '\n';
        std::cout << "=================================\n";

        std::cout << "\nOld Output: [";

        for (size_t i = 0;
             i < old_output.size();
             ++i)
        {
            std::cout << old_output[i];

            if (i + 1 != old_output.size())
            {
                std::cout << ", ";
            }
        }

        std::cout << "]\n";

        std::cout << "New Output: [";

        for (size_t i = 0;
             i < new_output.size();
             ++i)
        {
            std::cout << new_output[i];

            if (i + 1 != new_output.size())
            {
                std::cout << ", ";
            }
        }

        std::cout << "]\n";

        const bool outputs_match =
            old_output == new_output;

        std::cout << "Outputs Match: "
                  << std::boolalpha
                  << outputs_match
                  << '\n';

        for (int run = 0;
             run < runs;
             ++run)
        {
            const auto start_old =
                std::chrono::high_resolution_clock::now();

            volatile auto old_result =
                slow_window_aggregation(events,
                                        window);

            const auto end_old =
                std::chrono::high_resolution_clock::now();

            old_runs.push_back(
                std::chrono::duration_cast<
                    std::chrono::nanoseconds>(
                    end_old - start_old)
                    .count());

            const auto start_new =
                std::chrono::high_resolution_clock::now();

            volatile auto new_result =
                faster_window_aggregation(events,
                                          window);

            const auto end_new =
                std::chrono::high_resolution_clock::now();

            new_runs.push_back(
                std::chrono::duration_cast<
                    std::chrono::nanoseconds>(
                    end_new - start_new)
                    .count());
        }

        auto average =
            [](const std::vector<long long>& values)
        {
            return std::accumulate(
                       values.begin(),
                       values.end(),
                       0LL)
                   / static_cast<long long>(
                       values.size());
        };

        auto minimum =
            [](const std::vector<long long>& values)
        {
            return *std::min_element(
                values.begin(),
                values.end());
        };

        auto maximum =
            [](const std::vector<long long>& values)
        {
            return *std::max_element(
                values.begin(),
                values.end());
        };

        std::cout << "\nRun | Old(ns) | New(ns)\n";
        std::cout << "-------------------------\n";

        for (size_t i = 0;
             i < old_runs.size();
             ++i)
        {
            std::cout << i + 1
                      << " | "
                      << old_runs[i]
                      << " | "
                      << new_runs[i]
                      << '\n';
        }

        std::cout << "\nOld Implementation\n";
        std::cout << "Average: "
                  << average(old_runs)
                  << " ns\n";
        std::cout << "Min: "
                  << minimum(old_runs)
                  << " ns\n";
        std::cout << "Max: "
                  << maximum(old_runs)
                  << " ns\n";

        std::cout << "\nNew Implementation\n";
        std::cout << "Average: "
                  << average(new_runs)
                  << " ns\n";
        std::cout << "Min: "
                  << minimum(new_runs)
                  << " ns\n";
        std::cout << "Max: "
                  << maximum(new_runs)
                  << " ns\n";
    };

    /*
     * Expected:
     * [5, 7, 11, 7]
     */
    {
        const std::vector<Event> events =
        {
            {1, 5},
            {3, 2},
            {8, 4},
            {15, 3}
        };

        benchmark(events,
                  10,
                  "TEST 1");
    }

    /*
     * Expected:
     * [10, 30, 60, 90]
     */
    {
        const std::vector<Event> events =
        {
            {1, 10},
            {2, 20},
            {3, 30},
            {4, 40}
        };

        benchmark(events,
                  2,
                  "TEST 2");
    }

    /*
     * Expected:
     * [1, 3, 6, 10, 15]
     */
    {
        const std::vector<Event> events =
        {
            {100, 1},
            {200, 2},
            {300, 3},
            {400, 4},
            {500, 5}
        };

        benchmark(events,
                  1000,
                  "TEST 3");
    }

    /*
     * Stress Test
     */
    {
        std::vector<Event> events;

        events.reserve(10000);

        for (int i = 0; i < 10000; ++i) {
            events.push_back(
            {
                i,
                i % 100 + 1
            });
        }

        benchmark(events,
                  500,
                  "TEST 4 (STRESS TEST)");
    }

    return 0;
}