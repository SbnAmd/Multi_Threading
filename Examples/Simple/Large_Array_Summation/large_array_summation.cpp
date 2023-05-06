//
// Created by Sbn on 5/5/2023.
//

#include "large_array_summation.h"

template<typename T>
void fill_random(T* ptr, long long& length){
    for(long long j = 0; j < length; ++j)
        ptr[j] = (rand() % 10);
}

std::chrono::time_point<std::chrono::high_resolution_clock> get_time(){
    return std::chrono::high_resolution_clock::now();
}

template<typename T, typename T2>
void sum_func_normal(T* arr, long long length, T2* sum){

    for(long long j = 0; j < length; ++j){
        *sum += (T2)arr[j];
    }
}

template<typename T>
void init_array(T* array, const long long& length, bool multi_thread = false){

    auto thread_count = std::thread::hardware_concurrency();
    long long sub_arr_length = 0;
    std::vector<std::thread> thread_vector(thread_count-1);
    std::chrono::time_point<std::chrono::high_resolution_clock> t1, t2;

    if (length % thread_count == 0)
        sub_arr_length = length / thread_count;

    if (multi_thread && sub_arr_length!=0){
        std::cout<< "Initializing array with multi-thread\n" ;
        t1 = get_time();
        for(int j = 1; j < thread_count; ++j){
            thread_vector[j-1] = std::thread(fill_random<T>, &array[j * sub_arr_length], std::ref(sub_arr_length));
            thread_vector[j-1].join();
        }
        fill_random(array, (long long&)sub_arr_length);
        t2 = get_time();
    } else{
        std::cout<< "Initializing array with single-thread\n" ;
        t1 = get_time();
        fill_random(array, (long long&)length);
        t2 = get_time();

    }

    auto time_res = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
    std::cout << "initialization took " << time_res << " mili Seconds" <<std::endl << std::endl;
}

template<typename T>
void single_thread_summation(T* array, const long long& length){

    using T2 = typename std::conditional<std::is_same<T, double>::value, double, long long>::type;
    T2 sum = 0;
    std::chrono::time_point<std::chrono::high_resolution_clock> t1, t2;

    t1 = get_time();
    for(long long j=0; j < length; j++){
        sum += (T2)array[j];
    }
    t2 = get_time();

    auto time_res = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
    std::cout << "Single thread summation took " << time_res << " mili Seconds & result = " << sum <<std::endl << std::endl;

}

//
//void sum_func(double* arr, long long length, partial_sum_struct* sum){
//
//    for(long long j = 0; j < length; ++j){
//        sum->sum += arr[j];
//    }
//}

template<typename T>
void multi_thread_summation(T* array, const long long& length){
    auto thread_count = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(thread_count-1);
    long long sub_arr_length = 0;
    using T2 = typename std::conditional<std::is_same<T, double>::value, double, long long>::type;
    auto partial_sum = new T2[thread_count];
    T2 sum = 0;
    std::chrono::time_point<std::chrono::high_resolution_clock> t1, t2;

    if (length % thread_count == 0){
        sub_arr_length = length / thread_count;
        for(int j=0; j < thread_count; ++j)
            partial_sum[j] = 0;

        t1 = get_time();

        for(int j = 1; j < thread_count; ++j){
            threads[j-1] = std::thread(sum_func_normal<T,T2>, &array[j * sub_arr_length], sub_arr_length, &partial_sum[j]);
            threads[j-1].join();
        }


        sum_func_normal(array, sub_arr_length, partial_sum);

        for(int j=0; j < thread_count; ++j)
            sum += partial_sum[j];

        delete[] partial_sum;

        t2 = get_time();
        auto time_res = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
        std::cout << "Multi-thread summation took " << time_res << " mS & result = " << sum <<std::endl << std::endl;
    }


}

//
//void multi_thread_summation_modified_cache_access(double* array, const long long& length){
//    auto thread_count = identify_hardware_threads();
//    std::vector<std::thread> threads(thread_count);
//    auto part_length = (long long)(length/thread_count);
//    auto partial_sum = new partial_sum_struct[thread_count];
//    double sum = 0;
//
//    for(unsigned short j=0; j < thread_count; ++j)
//        partial_sum[j].sum = 0;
//
//    auto t1 = std::chrono::high_resolution_clock::now();
//
//    for(unsigned short j = 1; j < thread_count; ++j){
//        threads[j] = std::thread(sum_func, &array[j*part_length], part_length, &partial_sum[j]);
//        threads[j].join();
//    }
//
////    for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
//
//    sum_func(array, part_length, partial_sum);
//
//    for(unsigned short j=0; j < thread_count; ++j)
//        sum += partial_sum[j].sum;
//
//    delete[] partial_sum;
//
//    auto t2 = std::chrono::high_resolution_clock::now();
//
//    std::cout << "Multi-thread array summation = " << sum << std::endl;
//    std::cout << "Multi-thread summation with improved cache access done in " << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() << " mS" << std::endl << std::endl;
//
//}

void run_test(long long arr_length){
//    using T = int;
    using T = double;

    auto arr = new T[arr_length];
    if(arr != nullptr){

        init_array<T>(arr, (const long long&)arr_length, true);
        single_thread_summation<T>(arr, (const long long&)arr_length);
        multi_thread_summation<T>(arr, (const long long&)arr_length);
        delete[] arr;

    } else{
        std::cout << "Allocation unsuccessful";
    }

}