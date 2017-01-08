#pragma once

#include <vector>
#include "data_providers/data_storage.h"

namespace cpp_example_project {
namespace data_providers {

/**
 * @brief      This is a network storage class, which is not implemented intentionally.
 *             Just to emulate something which we don't want to use for testing.
 */
class UnimplementedNetworkStorage final : public DataStorage {
 public:
    UnimplementedNetworkStorage();
    ~UnimplementedNetworkStorage();

    std::vector<int> read_all_data() override;
    void write_data_element(int element) override;
    void remove_all_available_data() override;
};

}  // namespace data_providers
}  // namespace cpp_example_project
