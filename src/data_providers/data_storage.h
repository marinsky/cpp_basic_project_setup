#pragma once

#include <vector>

namespace cpp_example_project {
namespace data_providers {

/**
 * @brief      Interface for a simple data storage class.
 *             Real implementation may include operations with file, network,
 *             database, in-memory etc.
 */
class DataStorage {
 public:
    // Distructor should be virtual, since we're going to inherit this class!
    virtual ~DataStorage() {}

    /**
     * @brief      Reads data from the provider
     *
     * @return     Returns an empty array if there is no data, otherwise
     *             returns data array.
     */
    virtual std::vector<int> read_all_data() = 0;

    /**
     * @brief      Writes data to data provider buffer.
     *
     * @param[in]  data  data to write
     */
    virtual void write_data_element(int element) = 0;

    /**
     * @brief      Removes all available data from provider's buffer.
     */
    virtual void remove_all_available_data() = 0;
};

}  // namespace data_providers
}  // namespace cpp_example_project
