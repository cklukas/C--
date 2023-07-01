#ifndef ISYSTEMINFO_H
#define ISYSTEMINFO_H

#include <string>
#include <vector>

class ISystemInfo {
public:
    virtual ~ISystemInfo() = default;

    // returns the last value
    virtual double getLastValue() const = 0;
    
    // returns the maximum value that can be returned by getLastValue(), or -1 if no maximum
    virtual double getMaxValue() const = 0;

    // returns the full vector of values captured by the idle function
    virtual const std::vector<double>& getInfoValues() const = 0;

    // returns the intended title of the window
    virtual std::string getTitle(short maxSize) const = 0;

    // update the internal state of the system info
    virtual void idle(int max_entries_needed) = 0;
};

#endif // ISYSTEMINFO_H