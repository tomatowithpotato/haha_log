#include "log/Log.h"
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <sys/time.h>

static const int NUM = 10000 * 100;

double compute_timediff(const struct timeval &tvBegin, const struct timeval &tvEnd){
    return (tvEnd.tv_sec - tvBegin.tv_sec) + ((tvEnd.tv_usec - tvBegin.tv_usec) / 1000.0) / 1000.0;
}

int main(){
    struct timeval tvBegin, tvEnd;

    gettimeofday(&tvBegin, NULL);
    for(int i = 0; i < NUM; ++i){
        HAHA_LOG_INFO(HAHA_LOG_SYNC_ROOT()) << "work: " << i << " done";
    }
    gettimeofday(&tvEnd, NULL);
    std::cout << "time cost: " << compute_timediff(tvBegin, tvEnd) << " seconds" << std::endl;
    return 0;
}