/*
 * Copyright (c) 2015 Florian Behrens
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "measurement.h"

#include <cmath>

namespace {

void print_duration(std::ostream &out, const std::chrono::high_resolution_clock::duration &d)
{
    if (d < std::chrono::microseconds(1))
        out << std::chrono::duration_cast<std::chrono::duration<float, std::nano>>(d).count() << " ns";
    else if (d < std::chrono::milliseconds(1))
        out << std::chrono::duration_cast<std::chrono::duration<float, std::micro>>(d).count() << " µs";
    else if (d < std::chrono::seconds(1))
        out << std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(d).count() << " ms";
    else if (d < std::chrono::minutes(1))
        out << std::chrono::duration_cast<std::chrono::duration<float>>(d).count() << " s";
    else if (d < std::chrono::hours(1))
        out << std::chrono::duration_cast<std::chrono::duration<float, std::ratio<60>>>(d).count() << " min";
    else
        out << std::chrono::duration_cast<std::chrono::duration<float, std::ratio<3600>>>(d).count() << " hrs";
}

} // anonymous namespace

measurement::measurement(std::function<void ()> callable, std::chrono::milliseconds minimum_duration) :
    callable_(callable), min_duration_(minimum_duration)
{}

void measurement::operator()()
{
    size_t execution_count;
    std::chrono::high_resolution_clock::duration total_execution_time;

    for (size_t execution_count_pow = 0;; ++execution_count_pow) {
        size_t nominal_execution_count = 1 << execution_count_pow;

        // Carry out measurement
        auto begin = std::chrono::high_resolution_clock::now();
        for (execution_count = 0; execution_count < nominal_execution_count; ++execution_count)
            callable_();
        total_execution_time = std::chrono::high_resolution_clock::now() - begin;

        if (total_execution_time > min_duration_)
            break;
    }

    // Evaluate results
    avg_duration_ = total_execution_time / execution_count;
    actual_execution_count_ = execution_count;
}

void measurement::print_report(std::ostream &out)
{
    out << "Execution count: " << actual_execution_count_ << "\n";
    out << "Average execution time: ";
    print_duration(out, avg_duration_);
    out << std::endl;
}
