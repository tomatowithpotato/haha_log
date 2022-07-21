#include "log/Log.h"
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>

#define TEST_LOGGERER_WAPPER(logger) \
    haha::log::LogInfoWrapper(logger, haha::log::LogInfo::ptr(new haha::log::LogInfo(logger->getName(), \
                            haha::log::LogLevel::Level::DEBUG, \
                            __FILE__, __LINE__, 0, haha::GetThreadId(), \
                            std::chrono::system_clock::now())))

#define TEST_LOGGERINFO(logger) \
    haha::log::LogInfo::ptr(new haha::log::LogInfo(logger->getName(), \
                            haha::log::LogLevel::Level::DEBUG, \
                            __FILE__, __LINE__, 0, haha::GetThreadId(), \
                            std::chrono::system_clock::now()))

static const int NUM = 10000 * 100;

double compute_timediff(const struct timeval &tvBegin, const struct timeval &tvEnd){
    return (tvEnd.tv_sec - tvBegin.tv_sec) + ((tvEnd.tv_usec - tvBegin.tv_usec) / 1000.0) / 1000.0;
}

// class FormatItem{
// public:
//     typedef std::shared_ptr<FormatItem> ptr;
//     typedef haha::log::LogStream outStream;
//     virtual ~FormatItem(){}
//     virtual void format(outStream& os, haha::log::LogInfo &info) = 0;
// };

// class NewLineItem : public FormatItem{
//     void format(outStream& os, haha::log::LogInfo &info) override{
//         os << '\n';
//     }
// };

// std::function<void(haha::log::LogStream&, haha::log::LogInfo &info)> g_func;
// void newlinefunc(haha::log::LogStream& stream, haha::log::LogInfo &info){
//     stream << '\n';
// }

int main(){
    struct timeval tvBegin, tvEnd;

    gettimeofday(&tvBegin, NULL);
    std::string msg(80, 'h');
    // std::string fuck_format("%n%n%n%n%n%n%n%n%n%n%n%n%n%n%n%n%n%n%n%n");
    // haha::log::LogFormatter fmt(fuck_format);
    // FormatItem::ptr fitem = std::shared_ptr<FormatItem>(new NewLineItem);
    // g_func = newlinefunc;

    // auto logger = HAHA_LOG_ASYNC_ROOT();
    // auto info = TEST_LOGGERINFO(logger);
    
    for(int i = 0; i < NUM; ++i){
        HAHA_LOG_INFO(HAHA_LOG_ASYNC_ROOT()) << "work: " << i << " done";
        // HAHA_LOG_INFO(HAHA_LOG_ASYNC_ROOT()) << msg;
        // HAHA_LOG_INFO(HAHA_LOG_ASYNC_ROOT());
        // HAHA_LOG_ASYNC_ROOT()->getName();
        // haha::GetThreadId();
        // auto s = __FILE__;
        // auto l = __LINE__;
        // if(s);
        // if(l);
        // std::chrono::system_clock::now();
        // HAHA_LOG_ASYNC_ROOT();
        // TEST_LOGGERINFO(HAHA_LOG_ASYNC_ROOT());
        // haha::log::LogStream stream;
        // fmt.format(stream, info);
        // for(int i = 0; i < 20; ++i){
        //     // stream << '\n';
        //     fitem->format(stream, *info);
        //     // g_func(stream, *info);
        //     // newlinefunc(stream, *info);
        // }
    }
    gettimeofday(&tvEnd, NULL);
    std::cout << "task count: " << NUM << std::endl;
    std::cout << "time cost: " << compute_timediff(tvBegin, tvEnd) << " seconds" << std::endl;
    return 0;
}