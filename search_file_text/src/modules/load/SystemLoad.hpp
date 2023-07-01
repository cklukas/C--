#include <string>
#include <vector>
#include "../SystemInfo.hpp"

/**
 * @brief A class for retrieving system load information.
 */
class SystemLoad: public ISystemInfo
{
public:
    /**
     * @brief Default constructor.
     */
    SystemLoad() = default;

    /**
     * @brief Returns the last system load value.
     * @return The last system load value.
     */
    double getLastValue() const override;

    /**
     * @brief Returns the maximum system load value.
     * @return The maximum system load value.
     */
    double getMaxValue() const override;

    /**
     * @brief Returns a vector of system load values.
     * @return A vector of system load values.
     */
    const std::vector<double>& getInfoValues() const override;

    /**
     * @brief Returns the title of the system load information.
     * @param maxSize The maximum size of the title.
     * @return The title of the system load information.
     */
    std::string getTitle(short maxSize) const override;

    /**
     * @brief Retrieves system load information.
     * @param max_entries_needed The maximum number of entries needed.
     */
    void idle(int max_entries_needed) override;

private:
    std::vector<double> infoValues1;
    std::vector<double> infoValues2;
    std::vector<double> infoValues3;

    /**
     * @brief Returns a tuple of system load values.
     * @return A tuple of system load values.
     */
    std::tuple<double, double, double> getSystemLoad() const;
};