#pragma once

#include <memory>
#include <vector>

#include "data_providers/data_storage.h"

namespace cpp_example_project {
namespace business_logic {

/**
 * @brief      Very simple business logic class,
 *             which needs to work with DataStorage.
 */
class TemperatureMonitor {
 public:
    // Default ctor - intializes a data provider itself
    TemperatureMonitor();
    // More generic ctor - gets a data provider
    explicit TemperatureMonitor(
        const std::shared_ptr<data_providers::DataStorage>& storage);

    void delete_all_stored_temperatures();

    void store_new_temperature(int temperature, bool fahrenheit = false);

    std::vector<int> get_all_saved_temperatures(bool in_fahrenheits = false);

 private:
    static int get_celsius_from_fahrenheit(int fahrenheit);
    static int get_fahrenheit_from_celius(int celsius);

    std::shared_ptr<data_providers::DataStorage> storage_;
};

}  // namespace business_logic
}  // namespace cpp_example_project
