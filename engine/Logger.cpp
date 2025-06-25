#include "Logger.hpp"

Logger &Logger::Instance()
{
    static Logger instance;
    return instance;
}

Logger::Logger() = default;
Logger::~Logger()
{
    if (logFile.is_open())
        logFile.close();
}

void Logger::SetLogFile(const std::string &filename)
{
    std::lock_guard<std::mutex> lock(mtx);
    if (logFile.is_open())
        logFile.close();
    logFile.open(filename, std::ios::app);
}

void Logger::SetLevel(LogLevel level)
{
    minLevel = level;
}

void Logger::Log(LogLevel level, const std::string &msg)
{
    if (level < minLevel)
        return;
    std::lock_guard<std::mutex> lock(mtx);
    std::ostringstream oss;
    oss << "[" << Timestamp() << "] [" << LevelToString(level) << "] " << msg << "\n";
    std::string out = oss.str();
    std::cout << out;
    if (logFile.is_open())
        logFile << out;
}

void Logger::Debug(const std::string &msg) { Log(LogLevel::Debug, msg); }
void Logger::Info(const std::string &msg) { Log(LogLevel::Info, msg); }
void Logger::Warning(const std::string &msg) { Log(LogLevel::Warning, msg); }
void Logger::Error(const std::string &msg) { Log(LogLevel::Error, msg); }

std::string Logger::LevelToString(LogLevel level) const
{
    switch (level)
    {
    case LogLevel::Debug:
        return "DEBUG";
    case LogLevel::Info:
        return "INFO";
    case LogLevel::Warning:
        return "WARN";
    case LogLevel::Error:
        return "ERROR";
    }
    return "UNKNOWN";
}

std::string Logger::Timestamp() const
{
    std::time_t t = std::time(nullptr);
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&t));
    return buf;
}