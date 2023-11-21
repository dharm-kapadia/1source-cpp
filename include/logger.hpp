#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

/**
 * @file logger.cpp
 *
 * @brief Simple Logger class to create local logs
 *
 * @author EquiLend
 * Contact: Dharm Kapadia <dharm.kapadia@equilend.com>
 *
 */

#include <fmt/chrono.h>
#include <format>
#include <fstream>
#include <iostream>
#include <utility>

enum LogLevel
{
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL
};

class Logger
{
private:
    bool console_output;
    LogLevel logLevel;
    std::string filename;

public:
    // Default constructor
    Logger(std::string filename, LogLevel logLevel = LOG_INFO, bool console_output = false)
    {
        this->filename = std::move(filename);
        this->logLevel = logLevel;
        this->console_output = console_output;
    }

    // Default destructor
    ~Logger() = default;

    static std::string getFormattedTime()
    {
        const auto now = std::chrono::system_clock::now();
        return fmt::format("{:%d-%m-%Y %H:%M:%OS}", now);
    }

    void log(LogLevel level, const std::string& msg, bool console = false)
    {
        std::string time_str = getFormattedTime();

        if (level >= this->logLevel) {
            std::ofstream file(this->filename, std::ios_base::app);

            // Log msg to log file
            file << time_str << "\t" << msg << std::endl;

            file.close();
        }

        // Log to console if flag is true
        if (this->console_output || console)
        {
            std::cout << time_str << "\t" << msg << std::endl;
        }
    }

    void DEBUG(const std::string& msg, bool console = false)
    {
        this->log(LOG_FATAL, "[DEBUG]\t" + msg, console);
    }

    void INFO(const std::string& msg, bool console = false)
    {
        this->log(LOG_FATAL, "[INFO]\t" + msg, console);
    }

    void WARN(const std::string& msg, bool console = false)
    {
        this->log(LOG_FATAL, "[WARN]\t" + msg, console);
    }

    void ERR(const std::string& msg, bool console = false)
    {
        this->log(LOG_FATAL, "[ERROR]\t" + msg, console);
    }

    void FATAL(const std::string& msg, bool console = false)
    {
        this->log(LOG_FATAL, "[FATAL]\t" + msg, console);
    }
};

#endif
