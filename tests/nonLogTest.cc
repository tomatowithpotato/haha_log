#include "log/Log.h"
#include "base/ThreadPool.h"
#include <unistd.h>
#include <time.h>
#include <iostream>

haha::ThreadPool &pool = haha::ThreadPool::getInstance();

void work(int id){
    int nothing = 1;
    for(int i = 0; i < 10000; ++i){
        nothing += i;
    }
}


int main(){
    pool.start();
    auto t = clock();
    for(int i = 0; i < 100; ++i){
        for(int j = 0; j < 1000; ++j){
            pool.addTask(std::bind(work, j));
        }
    }
    std::cout << (double)(clock() - t) / CLOCKS_PER_SEC << std::endl;
    return 0;
}