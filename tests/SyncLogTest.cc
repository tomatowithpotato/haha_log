#include "log/Log.h"
#include <time.h>
#include <iostream>

int main(){
    auto t = clock();
    for(int i = 0; i < 100000; ++i){
        HAHA_LOG_INFO(HAHA_LOG_SYNC_ROOT()) << "XIXI: " << i;
    }
    std::cout << clock() - t << std::endl;
    return 0;
}