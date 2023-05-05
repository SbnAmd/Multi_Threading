//
// Created by Sbn on 5/5/2023.
//

#include "common.h"

unsigned short identify_hardware_threads(){
    auto real_thread_count = (unsigned short)std::thread::hardware_concurrency();
    if (real_thread_count > 0){
        std::cout << "Your CPU threads = " << real_thread_count << std::endl;
    } else{
        real_thread_count = 2;
        std::cout << "Failed to get hardware thread, assuming at least 2 threads" << std::endl;
    }

    return real_thread_count;
}