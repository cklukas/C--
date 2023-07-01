#include <string>
#include <vector>
#include "../SystemInfo.hpp"

/// @brief CpuLoad class that implements the ISystemInfo interface to provide CPU load information.
class CpuLoad: public ISystemInfo
{
public:
    /// @brief Constructor for the CpuLoad class.
    CpuLoad() noexcept;

    /// @brief Returns the last CPU load value.
    /// @return A double representing the last CPU load value.
    double getLastValue() const override;

    /// @brief Returns the maximum CPU load value.
    /// @return A double representing the maximum CPU load value.
    double getMaxValue() const override;

    /// @brief Returns a vector of CPU load values.
    /// @return A vector of doubles representing the CPU load values.
    const std::vector<double>& getInfoValues() const override;

    /// @brief Returns the title of the CPU load information.
    /// @param maxSize The maximum size of the title.
    /// @return A string representing the title of the CPU load information.
    std::string getTitle(short maxSize) const override;

    /// @brief store the system load values in the infoValues vectors.
    /// @param max_entries_needed limit the number of entries in the infoValues vectors to this value
    void idle(int max_entries_needed) override;

private:
    std::vector<double> infoValues; ///< A vector of doubles representing the CPU load values.
    double getSystemLoad() const; ///< Returns the system load.
    int getNumCpus() const; ///< Returns the number of CPUs.
    int cpuCount = 0; ///< The number of CPUs.
};