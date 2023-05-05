//
// Created by Sbn on 5/5/2023.
//

#include "large_array_summation.h"


void init_array(double* array, const long long& length){
    auto t1 = std::chrono::high_resolution_clock::now();

    for(long long j=0; j <= length; j++){
        array[j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    }

    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "initialization done in " << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() << " mS" << std::endl << std::endl;
}

void single_thread_summation(double* array, const long long& length){

    double sum = 0;

    auto t1 = std::chrono::high_resolution_clock::now();

    for(long long j=0; j <= length; j++){
        sum += array[j];
    }

    auto t2 = std::chrono::high_resolution_clock::now();

    std::cout << "Total array summation = " << sum << std::endl;
    std::cout << "Summation done in " << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() << " mS" << std::endl << std::endl;

}

void sum_func(double* arr, long long length, partial_sum_struct* sum){

    for(long long j = 0; j < length; ++j){
        sum->sum += arr[j];
    }
}

void multi_thread_summation(double* array, const long long& length){
    auto thread_count = identify_hardware_threads();
    std::vector<std::thread> threads(thread_count);
    auto part_length = (long long)(length/thread_count);
    auto partial_sum = new partial_sum_struct[thread_count];
    double sum = 0;

    for(unsigned short j=0; j < thread_count; ++j)
        partial_sum[j].sum = 0;

    auto t1 = std::chrono::high_resolution_clock::now();

    for(unsigned short j = 1; j < thread_count; ++j){
        threads[j] = std::thread(sum_func, &array[j*part_length], part_length, &partial_sum[j]);
        threads[j].join();
    }

//    for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

    sum_func(array, part_length, partial_sum);

    for(unsigned short j=0; j < thread_count; ++j)
        sum += partial_sum[j].sum;

    delete[] partial_sum;

    auto t2 = std::chrono::high_resolution_clock::now();

    std::cout << "Multi-thread array summation = " << sum << std::endl;
    std::cout << "Multi-thread summation done in " << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() << " mS" << std::endl << std::endl;

}

void run_test(long long arr_length){


    auto arr = new double [arr_length];

    init_array(arr, (const long long&)arr_length);

    single_thread_summation(arr, (const long long&)arr_length);

    multi_thread_summation(arr, (const long long&)arr_length);

    delete[] arr;

}