#include "business_logic/temperature_monitor.h"

#include <gtest/gtest.h>
#include <memory>
#include <vector>

#include "test/mocks.h"

namespace {

using ::cpp_example_project::data_providers::DataStorage;
using ::cpp_example_project::business_logic::TemperatureMonitor;
using ::testing::AnyOf;
using ::testing::Return;
using ::testing::_;

class TemperatureMonitorTest : public ::testing::Test {
 public:
    TemperatureMonitorTest()
        : mock_data_storage_(std::make_shared<MockDataStorage>()),
          temperature_monitor_(mock_data_storage_) {
        auto elem = 10;
        EXPECT_CALL(*mock_data_storage_.get(), write_data_element(elem)).Times(1);
        temperature_monitor_.store_new_temperature(elem);
    }

 protected:
    std::shared_ptr<MockDataStorage> mock_data_storage_;
    TemperatureMonitor temperature_monitor_;
};

//////////////
// TESTSUIT //
//////////////
TEST_F(TemperatureMonitorTest, Delete) {
    EXPECT_CALL(*mock_data_storage_.get(), remove_all_available_data()).Times(1);
    temperature_monitor_.delete_all_stored_temperatures();
}

TEST_F(TemperatureMonitorTest, Storing) {
    // expect write_data_element to always be called with celcius data
    EXPECT_CALL(*mock_data_storage_.get(), write_data_element(AnyOf(30, 40, 50)))
        .Times(3);
    temperature_monitor_.store_new_temperature(86, true);
    temperature_monitor_.store_new_temperature(40, false);
    temperature_monitor_.store_new_temperature(122, true);
}

TEST_F(TemperatureMonitorTest, Reading) {
    // set mock to always return celsius_data, but expect fahrenheit_data if
    // true flag is passed to get_all_saved_temperatures
    std::vector<int> celsius_data = {10, 20, 30, 40, 50};
    std::vector<int> fahrenheit_data = {50, 68, 86, 104, 122};
    EXPECT_CALL(*mock_data_storage_.get(), read_all_data())
        .Times(2)
        .WillRepeatedly(Return(celsius_data));
    EXPECT_EQ(celsius_data, temperature_monitor_.get_all_saved_temperatures());
    EXPECT_EQ(fahrenheit_data, temperature_monitor_.get_all_saved_temperatures(true));
}

}  // namespace
