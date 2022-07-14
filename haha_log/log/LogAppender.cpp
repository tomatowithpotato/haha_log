#include "log/LogAppender.h"
#include "base/TimeStamp.h"
#include <iostream>
#include <assert.h>

namespace haha{

namespace log{

void LogAppender::setFormatter(LogFormatter::ptr val){
    MutexType::RAIILock lock(m_mutex);
    m_formatter = val;
}

LogFormatter::ptr LogAppender::getFormatter(){
    MutexType::RAIILock lock(m_mutex);
    return m_formatter;
}


// ################################################### 同步 ###################################################


void StdoutSyncLogAppender::append(LogInfo::ptr info){
    auto level = info->getLevel();
    if(level >= m_level){
        MutexType::RAIILock lock(m_mutex);
        std::cout << m_formatter->format(info);
    }
}


FileSyncLogAppender::FileSyncLogAppender(const std::string &filepath, off_t rollSize)
    :filepath_(filepath),
    rollSize_(rollSize)
{
    file_ = std::make_unique<LogFile>(filepath_, rollSize_, false);
}

void FileSyncLogAppender::append(LogInfo::ptr info){
    auto level = info->getLevel();
    if(level >= m_level){
        MutexType::RAIILock lock(m_mutex);
        auto logline = m_formatter->format(info);
        file_->append(logline.data(), logline.size());
    }
}


// ################################################### 异步 ###################################################


AsyncLogAppender::AsyncLogAppender()
    :currentBuffer_(std::make_unique<Buffer>()),
    nextBuffer_(std::make_unique<Buffer>()),
    newBuffer1(std::make_unique<Buffer>()),
    newBuffer2(std::make_unique<Buffer>())
{
    newBuffer1->bzero();
    newBuffer2->bzero();
    buffersToWrite.reserve(16);
}


// StdoutAsyncLogAppender::StdoutAsyncLogAppender(off_t rollSize,
//                                                 int flushInterval)
//     :AsyncLogAppender(rollSize, flushInterval)
// {

// }


FileAsyncLogAppender::FileAsyncLogAppender(const std::string &filepath,
                                            off_t rollSize)
    :filepath_(filepath),
    rollSize_(rollSize)
{
    file_ = std::make_unique<LogFile>(filepath_, rollSize_, false);
}



void FileAsyncLogAppender::append(LogInfo::ptr info){
    auto level = info->getLevel();
    if(level >= m_level){
        auto logline = m_formatter->format(info);
        auto len = logline.size();
        MutexType::RAIILock lock(mutex_);
        if (static_cast<size_t>(currentBuffer_->avail()) > len)
        {
            currentBuffer_->append(logline.c_str(), len);
        }
        else
        {
            buffers_.push_back(std::move(currentBuffer_));

            if (nextBuffer_)
            {
                currentBuffer_ = std::move(nextBuffer_);
            }
            else
            {
                currentBuffer_.reset(new Buffer); // Rarely happens
            }
            currentBuffer_->append(logline.c_str(), len);

            // 唤醒日志线程
            if(notify_func_){
                notify_func_();
            }
        }
    }
}


void FileAsyncLogAppender::flush(){
    assert(newBuffer1 && newBuffer1->length() == 0);
    assert(newBuffer2 && newBuffer2->length() == 0);
    assert(buffersToWrite.empty());
    
    {
        MutexType::RAIILock lock(mutex_);
        buffers_.push_back(std::move(currentBuffer_));
        currentBuffer_ = std::move(newBuffer1);
        buffersToWrite.swap(buffers_);
        if (!nextBuffer_)
        {
            nextBuffer_ = std::move(newBuffer2);
        }
    }


    assert(!buffersToWrite.empty());

    if (buffersToWrite.size() > 25)
    {
        char buf[256];
        snprintf(buf, sizeof(buf), "Dropped log messages at %s, %zd larger buffers\n",
                TimeStamp::now().toFormattedString().c_str(),
                buffersToWrite.size()-2);
        fputs(buf, stderr);
        file_->append(buf, static_cast<int>(strlen(buf)));
        buffersToWrite.erase(buffersToWrite.begin()+2, buffersToWrite.end());
    }

    for (const auto& buffer : buffersToWrite)
    {
        // FIXME: use unbuffered stdio FILE ? or use ::writev ?
        file_->append(buffer->data(), buffer->length());
    }

    if (buffersToWrite.size() > 2)
    {
        // drop non-bzero-ed buffers, avoid trashing
        buffersToWrite.resize(2);
    }

    if (!newBuffer1)
    {
        assert(!buffersToWrite.empty());
        newBuffer1 = std::move(buffersToWrite.back());
        buffersToWrite.pop_back();
        newBuffer1->reset();
    }

    if (!newBuffer2)
    {
        assert(!buffersToWrite.empty());
        newBuffer2 = std::move(buffersToWrite.back());
        buffersToWrite.pop_back();
        newBuffer2->reset();
    }

    buffersToWrite.clear();
    file_->flush();
}

}

}