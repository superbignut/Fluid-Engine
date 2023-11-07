#ifndef INCLUDE_BIG_LOGGING_H_
#define INCLUDE_BIG_LOGGING_H_

#include <sstream>
#include <iostream>
#include <string>

namespace big
{
    enum class LoggingLeve : uint8_t
    {
        All = 0,
        Debug = 1,
        Info = 2,
        Warn = 3,
        Error = 4,
        Off = 5
    };

    class Logger final
    {
    public:
        explicit Logger(LoggingLeve level);

        ~Logger() = default;

        template <typename T>
        const Logger &operator<<(const T &x) const
        {
            _buffer << x;
            return *this;
        }

    private:
        LoggingLeve _level;
        mutable std::stringstream _buffer;
    };
}

#endif