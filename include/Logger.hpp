#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <mutex>

enum class LogLevel
{
    Debug,
    Info,
    Warning,
    Error
};

class Logger
{
public:
    static Logger &Instance();

    void SetLogFile(const std::string &filename);
    void SetLevel(LogLevel level);

    void Log(LogLevel level, const std::string &msg);

    // Conveniență
    void Debug(const std::string &msg);
    void Info(const std::string &msg);
    void Warning(const std::string &msg);
    void Error(const std::string &msg);

private:
    Logger();
    ~Logger();
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

    std::ofstream logFile;
    LogLevel minLevel = LogLevel::Debug;
    std::mutex mtx;

    std::string LevelToString(LogLevel level) const;
    std::string Timestamp() const;
};

// Macro-uri pentru logare rapidă
#define LOG_DEBUG(msg) Logger::Instance().Debug(msg)
#define LOG_INFO(msg) Logger::Instance().Info(msg)
#define LOG_WARN(msg) Logger::Instance().Warning(msg)
#define LOG_ERROR(msg) Logger::Instance().Error(msg)