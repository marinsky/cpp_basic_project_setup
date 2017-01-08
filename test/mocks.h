#pragma once

#include <vector>
#include "gmock/gmock.h"

#include "data_providers/data_storage.h"

class MockDataStorage :
    public ::cpp_example_project::data_providers::DataStorage {
 public:
    MOCK_METHOD0(read_all_data, std::vector<int>());
    MOCK_METHOD1(write_data_element, void(int));
    MOCK_METHOD0(remove_all_available_data, void());
};
