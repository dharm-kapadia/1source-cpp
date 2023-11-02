#ifndef __UTILITIES_H__
#define __UTILITIES_H__

/**
 * @file utilities.cpp
 *
 * @brief Class to contain small utilties
 *
 * @author EquiLend
 * Contact: Dharm Kapadia <dharm.kapadia@equilend.com>
 *
 */

#include <iostream>
#include <string>
#include <time.h>

namespace Utilities
{
    // Get current date/time, format is YYYY-MM-DD.HH:mm:ss
    const std::string CurrentDateTime()
    {
        time_t now = time(NULL);
        struct tm tstruct;
        char buf[80];
        localtime_s(&tstruct, &now);
        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
        return buf;
    }
}

#endif
