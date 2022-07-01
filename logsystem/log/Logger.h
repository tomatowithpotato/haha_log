#ifndef __HAHA_LOGGER_H__
#define __HAHA_LOGGER_H__

#include <memory>
#include <list>
#include "base/Mutex.h"
#include "base/Thread.h"
#include "log/LogInfo.h"
#include "log/LogAppender.h"

namespace haha{

// 日志器
class Logger : public std::enable_shared_from_this<Logger>{
public:
    typedef std::shared_ptr<Logger> ptr;
    typedef SpinLock MutexType;

    Logger(const std::string &name = "root"):name_(name),level_(LogLevel::DEBUG){}

    virtual ~Logger() {}

    virtual void log(LogInfo::ptr info) = 0;

    virtual void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);
    void clearAppenders();
    LogLevel::Level getLevel() const {return level_;}
    void setLevel(LogLevel::Level val){level_ = val;}
    std::string getName() const {return name_;}

    void setFormatter(LogFormatter::ptr val);
    void setFormatter(const std::string &val);
    LogFormatter::ptr getFormatter();

    std::string toYamlString();

protected:
    std::string name_;                         // 日志名称
    LogLevel::Level level_;                    // 日志级别
    MutexType mutex_;
    std::list<LogAppender::ptr> appenders_;    // Appender集合
    LogAppender::ptr defaultAppender_;
    LogFormatter::ptr formatter_;
};

// 同步日志器
class SyncLogger : public Logger{
public:
    SyncLogger(const std::string &name);
    void log(LogInfo::ptr info) override;
};

// 异步日志器
class AsyncLogger : public Logger{
public:
    typedef MutexLock MutexType;
    typedef ConditionVariable<MutexType>::ptr Condition;

    AsyncLogger(const std::string &name, int flushInterval);
    ~AsyncLogger(){
        running_ = false;
        cond_->notify_all();
    }

    void log(LogInfo::ptr info) override;
    void addAppender(LogAppender::ptr appender) override;

private:
    void task();

private:
    const int flushInterval_;
    MutexType mutex_;
    Condition cond_;
    std::atomic<bool> running_;
    Thread::ptr thread_;
};

}

#endif