#include "logging.h"
#include <mutex>
#include <chrono>
namespace big
{
    static std::mutex critical; // unseeable in other files

    static std::ostream *infoOutStream = &std::cout;

    static std::ostream *warnOutStream = &std::cout;

    static std::ostream *errorOutStream = &std::cerr;

    static std::ostream *debugOutStream = &std::cout;

    //! Change this to control actual logging level
    static LoggingLeve sLoggingLevel = LoggingLeve::All;

    /// @brief Return a relate ostream with level.
    /// @param level
    /// @return relate ostream
    inline std::ostream *levelToStream(LoggingLeve level)
    {
        switch (level)
        {
        case LoggingLeve::Info:
            return infoOutStream;
        case LoggingLeve::Warn:
            return warnOutStream;
        case LoggingLeve::Error:
            return errorOutStream;
        case LoggingLeve::Debug:
            return debugOutStream;
        default:
            return infoOutStream;
        }
    }
    /// @brief
    /// @param level
    /// @return
    inline std::string levelToString(LoggingLeve level)
    {
        switch (level)
        {
        case LoggingLeve::Info:
            return "INFO";
        case LoggingLeve::Warn:
            return "WARN";
        case LoggingLeve::Error:
            return "ERROR";
        case LoggingLeve::Debug:
            return "DEBUG";
        default:
            return "";
        }
    }

    inline bool isLeq(LoggingLeve a, LoggingLeve b)
    {
        return static_cast<uint8_t>(a) <= static_cast<uint8_t>(b);
    }

    Logger::Logger(LoggingLeve level)
        : _level(level)
    {
    }

    Logger::~Logger()
    {
        //! Ensure the _buffer is flushing in order.
        std::lock_guard<std::mutex> lock(critical);
        if (isLeq(sLoggingLevel, _level)) // Always True????
        {
            auto strm = levelToStream(_level);
            (*strm) << _buffer.str() << std::endl;
            strm->flush();
        }
    }

    void Logging::setInfoStream(std::ostream *strm)
    {
        infoOutStream = strm;
    }
    void Logging::setWarnStream(std::ostream *strm)
    {
        warnOutStream = strm;
    }

    void Logging::setErrorStream(std::ostream *strm)
    {
        errorOutStream = strm;
    }

    void Logging::setDebugStream(std::ostream *strm)
    {
        debugOutStream = strm;
    }

    void Logging::setAllStream(std::ostream *strm)
    {
        setInfoStream(strm);

        setWarnStream(strm);

        setErrorStream(strm);

        setDebugStream(strm);
    }

    std::string Logging::getHeader(LoggingLeve level)
    {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        char timeStr[20];
        strftime(timeStr, sizeof(timeStr), "%F %T", std::localtime(&now));

        char header[256];
        snprintf(header, sizeof(header), "[%s] %s ", levelToString(level).c_str(), timeStr);

        return header;
    }

    void Logging::setLevel(LoggingLeve level)
    {
        sLoggingLevel = level;
    }

    void Logging::mute()
    {
        setLevel(LoggingLeve::Off);
    }

    void Logging::unmute()
    {
        setLevel(LoggingLeve::All);
    }

}