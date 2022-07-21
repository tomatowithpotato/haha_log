#include "log/Log.h"
#include "base/ThreadPool.h"
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <atomic>
#include <sys/time.h>

static const int NUM = 10000 * 100;

std::atomic<int> cnt = 0;

haha::ThreadPool &pool = haha::ThreadPool::getInstance();

void work(int id){
    HAHA_LOG_INFO(HAHA_LOG_SYNC_ROOT()) << "work: " << id;
    ++cnt;
}

double compute_timediff(const struct timeval &tvBegin, const struct timeval &tvEnd){
    return (tvEnd.tv_sec - tvBegin.tv_sec) + ((tvEnd.tv_usec - tvBegin.tv_usec) / 1000.0) / 1000.0;
}


int main(){
    pool.start();
    struct timeval tvBegin, tvEnd;

    gettimeofday(&tvBegin, NULL);
    for(int i = 0; i < NUM; ++i){
        pool.addTask(std::bind(work, i));
    }
    while(cnt < NUM);
    std::cout << "task count: " << cnt.load() << std::endl;
    gettimeofday(&tvEnd, NULL);
    std::cout << "time cost: " << compute_timediff(tvBegin, tvEnd) << " seconds" << std::endl;
    return 0;
}