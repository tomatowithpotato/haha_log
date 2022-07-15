#ifndef __HAHA_LOG_LOGFORMATTER_H__
#define __HAHA_LOG_LOGFORMATTER_H__

#include <string>
#include <vector>
#include <ostream>
#include <memory>

#include "log/LogInfo.h"
#include "log/LogStream.h"

namespace haha{

namespace log{

// 日志格式器

class LogFormatter{
public:
    typedef std::shared_ptr<LogFormatter> ptr;
    typedef LogStream outStream;

    LogFormatter(const std::string &pattern);
    void format(outStream&, LogInfo::ptr info);
    // outStream format(LogInfo::ptr info);

    class FormatItem{
    public:
        typedef std::shared_ptr<FormatItem> ptr;
        typedef LogFormatter::outStream outStream;

        // FormatItem(const std::string &fmt = ""){}
        virtual ~FormatItem(){}
        virtual void format(outStream& os, LogInfo::ptr info) = 0;
    };
    void init();

    bool isError() const {return m_error;}
    const std::string getPattern() const {return m_pattern;}

private:
    std::string m_pattern;
    std::vector<FormatItem::ptr> m_items;
    bool m_error = false;
};


class MessageFormatItem : public LogFormatter::FormatItem{
public:
    MessageFormatItem(const std::string &fmt = ""){}
    void format(outStream &os, LogInfo::ptr info) override{
        os << info->getContent();
    }
};


class LevelFormatItem : public LogFormatter::FormatItem{
public:
    LevelFormatItem(const std::string &fmt = ""){}
    void format(outStream &os, LogInfo::ptr info) override{
        os << LogLevel::toString(info->getLevel());
    }
};


class ElapseFormatItem : public LogFormatter::FormatItem{
public:
    ElapseFormatItem(const std::string &fmt = ""){}
    void format(outStream &os, LogInfo::ptr info) override{
        os << info->getElapse();
    }
};


class NameFormatItem : public LogFormatter::FormatItem{
public:
    NameFormatItem(const std::string &fmt = ""){}
    void format(outStream &os, LogInfo::ptr info) override{
        os << info->getLoggerName();
    }
};


class ThreadIdFormatItem : public LogFormatter::FormatItem{
public:
    ThreadIdFormatItem(const std::string &fmt = ""){}
    void format(outStream &os, LogInfo::ptr info) override{
        os << info->getThreadId();
    }
};


// class FiberIdFormatItem : public LogFormatter::FormatItem{
// public:
//     FiberIdFormatItem(const std::string &fmt = ""){}
//     void format(outStream &os, LogInfo::ptr info) override{
//         os << info->getFiberId();
//     }
// };


class ThreadNameFormatItem : public LogFormatter::FormatItem {
public:
    ThreadNameFormatItem(const std::string& str = "") {}
    void format(outStream& os, LogInfo::ptr info) override {
        os << info->getThreadName();
    }
};


class DateTimeFormatItem : public LogFormatter::FormatItem{
public:
    DateTimeFormatItem(const std::string &format = "%Y-%m-%d %H:%M:%S"):m_format(format){
        if(m_format.empty()){
            m_format = "%Y-%m-%d %H:%M:%S";
        }
    }
    void format(outStream &os, LogInfo::ptr info) override{
        struct tm tm;
        time_t time = info->getTime();
        localtime_r(&time, &tm);
        char buf[64];
        strftime(buf, sizeof(buf), m_format.c_str(), &tm);
        os << buf;
    }
private:
    std::string m_format;
};


class FilenameFormatItem : public LogFormatter::FormatItem{
public:
    FilenameFormatItem(const std::string &fmt = ""){}
    void format(outStream &os, LogInfo::ptr info) override{
        os << info->getFile();
    }
};


class LineFormatItem : public LogFormatter::FormatItem{
public:
    LineFormatItem(const std::string &fmt = ""){}
    void format(outStream &os, LogInfo::ptr info) override{
        os << info->getLine();
    }
};


class NewLineFormatItem : public LogFormatter::FormatItem{
public:
    NewLineFormatItem(const std::string &fmt = ""){}
    void format(outStream &os, LogInfo::ptr info) override{
        // os << std::endl;
        os << '\n';
    }
};


class StringFormatItem : public LogFormatter::FormatItem{
public:
    StringFormatItem(const std::string &str):m_string(str){}
    void format(outStream &os, LogInfo::ptr info) override{
        os << m_string;
    }
private:
    std::string m_string;
};


class TabFormatItem : public LogFormatter::FormatItem{
public:
    TabFormatItem(const std::string &str = ""):m_string(str){}
    void format(outStream &os, LogInfo::ptr info) override{
        os << "\t";
    }
private:
    std::string m_string;
};

}

}

#endif