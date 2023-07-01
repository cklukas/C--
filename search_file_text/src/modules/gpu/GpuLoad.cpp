/*
 * File: modules/load/GpuLoad.cpp
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
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include "GpuLoad.hpp"

// constructor
GpuLoad::GpuLoad() noexcept
{
    GPUCount = getNumGPUs();
}

double GpuLoad::getLastValue() const
{
    if (!infoValues.empty())
        return infoValues.back();
    else
        throw std::out_of_range("No values in system load vector.");
}

double GpuLoad::getMaxValue() const
{
    // find max of infoValues
    double max = 0.0;
    for (double value : infoValues)
    {
        if (value > max)
            max = value;
    }
    if (max < 10)
        return 10.0;
    
    if (max < 25)
        return 25.0;

    if (max < 50)
        return 50.0;
    
    return 100.0;
}

const std::vector<double> &GpuLoad::getInfoValues() const
{
    return infoValues;
}

std::string GpuLoad::getTitle(short maxSize) const
{
    if (infoValues.empty() || maxSize < 0)
        return "GPU Load";
    else
    {
        double load = infoValues.back();
        std::stringstream ss;
        ss << GPUCount << " GPUs ("  << std::fixed << std::setprecision(0) << load << "% busy)";

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
void GpuLoad::idle(int max_entries_needed) {
    float load = 10.0;
    if (load >= -2.0)
    {
        infoValues.push_back(static_cast<double>(load));
        
        if (infoValues.size() > max_entries_needed)
            infoValues.erase(infoValues.begin());
    }
}


#ifdef __linux__
// Linux-specific code
#elif __APPLE__
// macOS-specific code
#include <mach/mach_init.h>
#include <mach/mach_error.h>
#include <mach/mach_host.h>
#include <mach/vm_map.h>
#include <sys/sysctl.h>


static unsigned long long _previousTotalTicks = 0;
static unsigned long long _previousIdleTicks = 0;

int GpuLoad::getNumGPUs() const {
    return 1;
}

#endif

float CalculateGpuLoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
  unsigned long long totalTicksSinceLastTime = totalTicks-_previousTotalTicks;
  unsigned long long idleTicksSinceLastTime  = idleTicks-_previousIdleTicks;
  float ret = 1.0f-((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime)/totalTicksSinceLastTime : 0);
  _previousTotalTicks = totalTicks;
  _previousIdleTicks  = idleTicks;
  return ret;
}
