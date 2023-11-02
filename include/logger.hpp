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

#include <chrono>
#include <format>
#include <fstream>
#include <iostream>

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
        this->filename = filename;
        this->logLevel = logLevel;
        this->console_output = console_output;
    }

    // Default destructor
    ~Logger() {}

    void log(LogLevel logLevel, std::string msg, bool console = false)
    {
        std::string time_str = getFormattedTime();
        std::ofstream file(this->filename, std::ios_base::app);

        // Log msg to log file
        file << time_str << "\t" << msg << std::endl;

        // Log to console if flag is true
        if (this->console_output || console)
        {
            std::cout << time_str << "\t" << msg << std::endl;
        }

        file.close();
    }

    std::string getFormattedTime()
    {
        const auto now = std::chrono::system_clock::now();
        return std::format("{:%d-%m-%Y %H:%M:%OS}", now);
    }

    void DEBUG(std::string msg, bool console = false)
    {
        this->log(LOG_FATAL, "[DEBUG]\t" + msg, console);
    }

    void INFO(std::string msg, bool console = false)
    {
        this->log(LOG_FATAL, "[INFO]\t" + msg, console);
    }

    void WARN(std::string msg, bool console = false)
    {
        this->log(LOG_FATAL, "[WARN]\t" + msg, console);
    }

    void ERR(std::string msg, bool console = false)
    {
        this->log(LOG_FATAL, "[ERROR]\t" + msg, console);
    }

    void FATAL(std::string msg, bool console = false)
    {
        this->log(LOG_FATAL, "[FATAL]\t" + msg, console);
    }
};

#endif
