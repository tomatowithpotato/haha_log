#ifndef __HAHA_LOGGERMANAGER__
#define __HAHA_LOGGERMANAGER__

#include <map>
#include "base/Mutex.h"
#include "Logger.h"

namespace haha{

class LogInfoWrap{
public:
    LogInfoWrap(LogInfo::ptr info):info_(info){}
    ~LogInfoWrap(){
        
    }

private:
    LogInfo::ptr info_;
};

class LoggerManager{
public:
    typedef SpinLock MutexType;
    LoggerManager();
    Logger::ptr getLogger(const std::string &name);
    void init();
    Logger::ptr getRoot() const {return m_root;}

    std::string toYamlString();
private:
    MutexType m_mutex;
    std::map<std::string, Logger::ptr> m_loggers;
    Logger::ptr m_root;
};

}

#endif