#include "LoggerManager.h"

namespace haha
{
    
namespace log
{

LoggerManager::LoggerManager() 
{
    sync_root_ = std::make_shared<SyncLogger>("sync_root");
    sync_root_->addAppender(LogAppender::ptr(new StdoutSyncLogAppender));

    async_root_ = std::make_shared<AsyncLogger>("async_root");
    async_root_->addAppender(LogAppender::ptr(new FileAsyncLogAppender(default_log_file, default_roll_size)));

    loggers_[sync_root_->getName()] = sync_root_;
    loggers_[async_root_->getName()] = async_root_;
}

Logger::ptr LoggerManager::getLogger(const std::string& name) {
    MutexType::RAIILock lock(mutex_);
    auto it = loggers_.find(name);
    if(it != loggers_.end()) {
        return it->second;
    }
    return nullptr;
}

} // namespace log

} // namespace haha
