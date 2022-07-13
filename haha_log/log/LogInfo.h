#ifndef __HAHA_LOG_LOGINFO_H__
#define __HAHA_LOG_LOGINFO_H__

#include <string>
#include <sstream>
#include <memory>

namespace haha{

namespace log{

// 日志级别
class LogLevel{
public:
    enum Level{
        UNKNOW = 0,
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };

    static const char* toString(LogLevel::Level level);
    static LogLevel::Level FromString(const std::string &str);
};

// 日志事件
class LogInfo{
public:
    typedef std::shared_ptr<LogInfo> ptr;
    LogInfo(std::string loggerName,
            LogLevel::Level level, 
            const char *file, 
            int32_t line, 
            uint32_t elapse,
            uint32_t thread_id, 
            // uint32_t fiber_id, 
            uint64_t time,
            const std::string &thread_name);

    std::string getLoggerName() const {return loggerName_;}
    const char * getFile() const {return file_;}      
    int32_t getLine() const {return line_;}         
    uint32_t getElapse() const {return elapse_;}    
    uint32_t getThreadId() const {return threadId_;}    
    // uint32_t getFiberId() const {return m_fiberId;}            
    uint64_t getTime() const {return time_;}     
    const std::string& getThreadName() const { return threadName_;}          
    std::string getContent() const {return ss_.str();}  
    LogLevel::Level getLevel() const {return level_;}

    std::stringstream& getSS() {return ss_;}
    void format(const char* fmt, ...);
    void format(const char* fmt, va_list al);
       
private:
    std::string loggerName_;             // 日志器名称
    const char * file_ = nullptr;      // 文件名
    int32_t line_ = 0;                 // 行号
    uint32_t elapse_ = 0;              // 启动到现在的毫秒数
    uint32_t threadId_ = 0;            // 线程ID
    // uint32_t m_fiberId = 0;             // 协程ID
    uint64_t time_;                    // 时间戳
    std::string threadName_;           // 线程名
    std::stringstream ss_;             // 事件内容

    LogLevel::Level level_;
};

}

}

#endif