#ifndef MULTI_THREADING_LARGE_ARRAY_SUMMATION_H
#define MULTI_THREADING_LARGE_ARRAY_SUMMATION_H

#include <vector>
#include <thread>
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <type_traits>
#include <functional>
#include "common.h"

struct __attribute__ ((packed)) partial_sum_struct{
    double sum;
    unsigned short pad[28];
};


void run_test(long long);

#endif //MULTI_THREADING_LARGE_ARRAY_SUMMATION_H
