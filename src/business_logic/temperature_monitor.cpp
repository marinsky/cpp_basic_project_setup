#include <algorithm>

#include "business_logic/temperature_monitor.h"
#include "data_providers/unimplemented_network_storage.h"

using ::cpp_example_project::data_providers::DataStorage;
using ::cpp_example_project::data_providers::UnimplementedNetworkStorage;

namespace cpp_example_project {
namespace business_logic {

TemperatureMonitor::TemperatureMonitor()
    : storage_(std::make_shared<UnimplementedNetworkStorage>()) {
}

TemperatureMonitor::TemperatureMonitor(const std::shared_ptr<DataStorage>& storage) {
    storage_ = storage;
}

void TemperatureMonitor::delete_all_stored_temperatures() {
    storage_->remove_all_available_data();
}

void TemperatureMonitor::store_new_temperature(const int temperature,
                                               const bool fahrenheit) {
    int temperature_in_celsius = fahrenheit ?
        get_celsius_from_fahrenheit(temperature) : temperature;
    storage_->write_data_element(temperature_in_celsius);
}

std::vector<int> TemperatureMonitor::get_all_saved_temperatures(
        const bool in_fahrenheits) {
    auto all_saved = storage_->read_all_data();
    if (in_fahrenheits) {
        std::for_each(
            all_saved.begin(),
            all_saved.end(),
            [](auto& elem) {
                elem = TemperatureMonitor::get_fahrenheit_from_celius(elem);
            });
    }
    return all_saved;
}

int TemperatureMonitor::get_celsius_from_fahrenheit(const int fahrenheit) {
    return (fahrenheit - 32) * 5 / 9;
}

int TemperatureMonitor::get_fahrenheit_from_celius(const int celsius) {
    return celsius * 9 / 5 + 32;
}

}  // namespace business_logic
}  // namespace cpp_example_project
