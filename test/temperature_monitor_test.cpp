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
    TemperatureMonitorTest() {
        mock_ds_ = std::make_shared<MockDataStorage>();
        tm_ = std::make_shared<TemperatureMonitor>(mock_ds_);
        auto elem = 10;
        EXPECT_CALL(*mock_ds_.get(), write_data_element(elem)).Times(1);
        tm_->store_new_temperature(elem);
    }

 protected:
    std::shared_ptr<MockDataStorage> mock_ds_;
    std::shared_ptr<TemperatureMonitor> tm_;
};

//////////////
// TESTSUIT //
//////////////
TEST_F(TemperatureMonitorTest, Delete) {
    EXPECT_CALL(*mock_ds_.get(), remove_all_available_data()).Times(1);
    tm_->delete_all_stored_temperatures();
}

TEST_F(TemperatureMonitorTest, Storing) {
    // expect write_data_element to always be called with celcius data
    EXPECT_CALL(*mock_ds_.get(), write_data_element(AnyOf(30, 40, 50))).Times(3);
    tm_->store_new_temperature(86, true);
    tm_->store_new_temperature(40, false);
    tm_->store_new_temperature(122, true);
}

TEST_F(TemperatureMonitorTest, Reading) {
    // set mock to always return celsius_data, but expect fahrenheit_data if
    // true flag is passed to get_all_saved_temperatures
    std::vector<int> celsius_data = {10, 20, 30, 40, 50};
    std::vector<int> fahrenheit_data = {50, 68, 86, 104, 122};
    EXPECT_CALL(*mock_ds_.get(), read_all_data())
        .Times(2)
        .WillRepeatedly(Return(celsius_data));
    EXPECT_EQ(celsius_data, tm_->get_all_saved_temperatures());
    EXPECT_EQ(fahrenheit_data, tm_->get_all_saved_temperatures(true));
}

}  // namespace
