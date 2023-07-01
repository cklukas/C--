/*
 * File: modules/load/SystemLoad.cpp
 * -----------------------------------------------------------------------------
 * This file is part of the File Search Program - (c) 2023 by C. Klukas
 * 
 * Licensed under the MIT License and the GNU General Public License, Version 3.
 * 
 * For details, see the accompanying COPYING file or visit:
 * - MIT License: https://opensource.org/licenses/MIT
 * - GPLv3: https://www.gnu.org/licenses/gpl-3.0.html
 *
 * Project repository: https://github.com/cklukas/C--
 *
 * Author: Christian Klukas
 */
#include <string>
#include <vector>
#include <tuple>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include "SystemLoad.hpp"

/// @brief  Returns the last value of the system load.
/// @return 
double SystemLoad::getLastValue() const
{
    if (!infoValues1.empty())
        return infoValues1.back();
    else
        throw std::out_of_range("No values in system load vector.");
}

/// @brief  Returns the maximum value of the system load.
/// @return 
double SystemLoad::getMaxValue() const
{
    // iterate through infoValues1, infoValues2, infoValues3 and return the maximum value
    double max = -1.0;
    for (auto it = infoValues1.begin(); it != infoValues1.end(); ++it)
    {
        if (*it > max)
            max = *it;
    }
    for (auto it = infoValues2.begin(); it != infoValues2.end(); ++it)
    {
        if (*it > max)
            max = *it;
    }
    for (auto it = infoValues3.begin(); it != infoValues3.end(); ++it)
    {
        if (*it > max)
            max = *it;
    }
    
    max = std::ceil(max);
    return max;
}

/// @brief get the values of the system load (last minute stats).
/// @return 
const std::vector<double> &SystemLoad::getInfoValues() const
{
    return infoValues1;
}

/// @brief Returns the title of the system load module.
/// @param maxSize 
/// @return 
std::string SystemLoad::getTitle(short maxSize) const
{
    if (infoValues1.empty() || maxSize < 0)
        return "System Load";
    else
    {
        double load1 = infoValues1.back();
        double load2 = infoValues2.back();
        double load3 = infoValues3.back();
        std::stringstream ss;
        ss << "System Load (" << 
            std::fixed << std::setprecision(2) << load1 << ", " << load2 << ", " << load3 << ")";

        // if length of ss is > maxSize, then truncate it and add "..." to the end
        if (ss.str().length() > maxSize)
        {
            std::string truncated = ss.str().substr(0, maxSize - 3);
            truncated += "...";
            return ss.str();
        }
        else
            return ss.str();
    }
}

/// @brief store the system load values in the infoValues vectors.
/// @param max_entries_needed limit the number of entries in the infoValues vectors to this value
void SystemLoad::idle(int max_entries_needed) {
    auto load = getSystemLoad();
    if (std::get<0>(load) >= -2.0)
    {
        infoValues1.push_back(static_cast<double>(std::get<0>(load)));
        infoValues2.push_back(static_cast<double>(std::get<1>(load)));
        infoValues3.push_back(static_cast<double>(std::get<2>(load)));
        
        if (infoValues1.size() > max_entries_needed) {
            infoValues1.erase(infoValues1.begin());
            infoValues2.erase(infoValues2.begin());
            infoValues3.erase(infoValues3.begin());
        }
    }
}


#ifdef __linux__
// Linux-specific code
#elif __APPLE__
// macOS-specific code
#include <sys/sysctl.h>

#endif

/// @brief This function is used to fetch the system load depending on the operating system in use.
std::tuple<double, double, double> SystemLoad::getSystemLoad() const
{
    struct loadavg load;

#ifdef __linux__
    // Linux-specific code
    std::ifstream loadavg("/proc/loadavg");
    if (loadavg >> load)
    {
        return load;
    }
#elif __APPLE__
    // macOS-specific code

    int mib[2];
    size_t len = sizeof(load);
    mib[0] = CTL_VM;
    mib[1] = VM_LOADAVG;

    if (sysctl(mib, 2, &load, &len, nullptr, 0) != -1)
    {
        return std::make_tuple(
                load.ldavg[0] / (double)load.fscale,
                load.ldavg[1] / (double)load.fscale,
                load.ldavg[2] / (double)load.fscale
                );
    }
#endif

    // Error reading load average or unsupported platform
    return std::make_tuple(-1.0, -1.0, -1.0);
}