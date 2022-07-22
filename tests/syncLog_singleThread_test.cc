#include "log/Log.h"
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <sys/time.h>
#include "base/util.h"

static const int NUM = 10000 * 100;

double compute_timediff(const struct timeval &tvBegin, const struct timeval &tvEnd){
    return (tvEnd.tv_sec - tvBegin.tv_sec) + ((tvEnd.tv_usec - tvBegin.tv_usec) / 1000.0) / 1000.0;
}

int main(){
    struct timeval tvBegin, tvEnd;

    gettimeofday(&tvBegin, NULL);
    for(int i = 0; i < NUM; ++i){
        HAHA_LOG_INFO(HAHA_LOG_SYNC_FILE_ROOT()) << "work: " << i << " done";
    }
    gettimeofday(&tvEnd, NULL);
    std::cout << "task count: " << NUM << std::endl;
    std::cout << "time cost: " << compute_timediff(tvBegin, tvEnd) << " seconds" << std::endl;

    // time_t tz_offset = haha::get_TZoffset();
    // char date[64];
    // // auto now = std::chrono::system_clock::now();
    // const auto now = std::chrono::system_clock::now();
    // auto in_time_t = std::chrono::system_clock::to_time_t(now);
    // struct tm tm_res;
    // gmtime_r(&in_time_t, &tm_res);
    // std::strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", &tm_res);
    // std::cout << date << std::endl;

    // auto in_time_t1 = in_time_t + tz_offset;
    // gmtime_r(&in_time_t1, &tm_res);
    // std::strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", &tm_res);
    // std::cout << date << std::endl;
    return 0;
}