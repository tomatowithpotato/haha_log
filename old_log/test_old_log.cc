#include "Log.h"
#include "base/ThreadPool.h"
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <atomic>

static const int NUM = 10000 * 10;

std::atomic<int> cnt = 0;

haha::ThreadPool &pool = haha::ThreadPool::getInstance();

void work(int id){
    HAHA_LOG_INFO(HAHA_LOG_ROOT()) << "work: " << id << " start";
    // int nothing = 1;
    // for(int i = 0; i < 10000; ++i){
    //     nothing += i;
    // }
    HAHA_LOG_INFO(HAHA_LOG_ROOT()) << "work: " << id << " done";
    ++cnt;
}


int main(){
    pool.start();
    auto t = clock();
    for(int i = 0; i < NUM; ++i){
        pool.addTask(std::bind(work, i));
    }
    while(cnt < NUM);
    std::cout << cnt.load() << std::endl;
    std::cout << (double)(clock() - t) / CLOCKS_PER_SEC << std::endl;
    return 0;
}