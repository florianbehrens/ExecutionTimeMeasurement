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

#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <chrono>
#include <functional>
#include <iostream>

class measurement
{
public:
    measurement(std::function<void()> callable, std::chrono::milliseconds minimum_duration);

    void operator()();

    void print_report(std::ostream &out = std::cout);

private:
    std::function<void()> callable_;
    std::chrono::milliseconds min_duration_;

    std::chrono::high_resolution_clock::duration avg_duration_;
    size_t actual_execution_count_;
};

#endif // MEASUREMENT_H
