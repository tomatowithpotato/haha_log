#include "log/Log.h"
#include <unistd.h>
#include <time.h>
#include <iostream>

static const int NUM = 10000 * 100;

int main(){
    auto t = clock();
    for(int i = 0; i < NUM; ++i){
        HAHA_LOG_INFO(HAHA_LOG_ASYNC_ROOT()) << "work: " << i << " done";
    }
    std::cout << "time cost: " << (double)(clock() - t) / CLOCKS_PER_SEC << " seconds" << std::endl;
    return 0;
}