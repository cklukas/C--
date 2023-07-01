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

    virtual bool* getCoverFlags(int endIndex, int len, double threshold) const {
        bool* flags = new bool[len];
        auto infoVals = this->getInfoValues();
        // if length of infoVals < endIndex, make copy of infoVals and append zeros at start
        if (infoVals.size() < endIndex) {
            std::vector<double> infoValsCopy = infoVals;
            infoValsCopy.insert(infoValsCopy.begin(), endIndex - infoVals.size(), 0.0);
            infoVals = infoValsCopy;
        }
         
        for (int i = 0; i < len; i++) {
            if (i < infoVals.size())
                flags[i] = (infoVals[i] >= threshold);
            else
                flags[i] = false;
        }
        return flags;
    }
};

#endif // ISYSTEMINFO_H