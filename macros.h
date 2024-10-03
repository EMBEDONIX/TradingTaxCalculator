//
// Created by Saeid Yazdani on 10/3/2024.
//

#pragma once

#ifdef __BENCHMARK__
#include <embedonix/simplelibs/utilities/benchmark.h>
// Starts a timer
#define __BENCHMARK_TIMER_START(MY_TIMER) \
    std::chrono::time_point<std::chrono::high_resolution_clock> MY_TIMER; \
    embedonix::simplelibs::utilities::benchmark::measure::start_timer(MY_TIMER);

#define __BENCHMARK_TIMER_STOP(timer) \
    puts(std::format("Function {} took {}", \
                     __func__, \
                     embedonix::simplelibs::utilities::benchmark::measure::format_duration( \
                             embedonix::simplelibs::utilities::benchmark::measure::stop_timer(timer)).c_str() \
         ).c_str() \
    );
#else
#define ENABLE_BENCHMARKS
#define __BENCHMARK_TIMER_START(timer)
#define __BENCHMARK_TIMER_STOP(timer)
#endif






