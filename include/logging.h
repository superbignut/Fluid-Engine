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
    //! \brief it is a buffer, add something to it.
    //!
    class Logger final
    {
    public:
        explicit Logger(LoggingLeve level);

        /// @brief Flush when destruct;
        ~Logger();

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

    /// @brief A tool class
    class Logging
    {
    public:
        static void setInfoStream(std::ostream *strm);

        static void setWarnStream(std::ostream *strm);

        static void setErrorStream(std::ostream *strm);

        static void setDebugStream(std::ostream *strm);

        static void setAllStream(std::ostream *strm);

        static std::string getHeader(LoggingLeve level);

        static void setLevel(LoggingLeve level);

        static void mute();

        static void unmute();
    };

    // extern Logger infoLogger;

    // extern Logger warnLogger;

    // extern Logger errorLogger;

    // extern Logger debugLogger;  

#define BIG_INFO \
    (big::Logger(big::LoggingLeve::Info) << big::Logging::getHeader(big::LoggingLeve::Info) \
    << "[" << __FILE__ << ":" << __LINE__ << "(" << __func__ <<")} ")
#define BIG_WARN \
    (big::Logger(big::LoggingLeve::Warn) << big::Logging::getHeader(big::LoggingLeve::Warn) \
    << "[" << __FILE__ << ":" << __LINE__ << "(" << __func__ <<")} ")
#define BIG_ERROR \
    (big::Logger(big::LoggingLeve::Error) << big::Logging::getHeader(big::LoggingLeve::Error) \
    << "[" << __FILE__ << ":" << __LINE__ << "(" << __func__ <<")} ")
#define BIG_DEBUG \
    (big::Logger(big::LoggingLeve::Debug) << big::Logging::getHeader(big::LoggingLeve::Debug) \
    << "[" << __FILE__ << ":" << __LINE__ << "(" << __func__ <<")} ")
}

#endif