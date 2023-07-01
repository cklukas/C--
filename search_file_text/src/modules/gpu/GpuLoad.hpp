#include <string>
#include <vector>
#include "../SystemInfo.hpp"

/// @brief GpuLoad class that implements the ISystemInfo interface to provide GPU load information.
class GpuLoad: public ISystemInfo
{
public:
    /// @brief Constructor for the GpuLoad class.
    GpuLoad() noexcept;

    /// @brief Returns the last GPU load value.
    /// @return A double representing the last GPU load value.
    double getLastValue() const override;

    /// @brief Returns the maximum GPU load value.
    /// @return A double representing the maximum GPU load value.
    double getMaxValue() const override;

    /// @brief Returns a vector of GPU load values.
    /// @return A vector of doubles representing the GPU load values.
    const std::vector<double>& getInfoValues() const override;

    /// @brief Returns the title of the GPU load information.
    /// @param maxSize The maximum size of the title.
    /// @return A string representing the title of the GPU load information.
    std::string getTitle(short maxSize) const override;

    /// @brief store the system load values in the infoValues vectors.
    /// @param max_entries_needed limit the number of entries in the infoValues vectors to this value
    void idle(int max_entries_needed) override;

private:
    std::vector<double> infoValues; ///< A vector of doubles representing the GPU load values.
    double getSystemLoad() const; ///< Returns the system load.
    int getNumGPUs() const; ///< Returns the number of GPUs.
    int GPUCount = 0; ///< The number of GPUs.
};