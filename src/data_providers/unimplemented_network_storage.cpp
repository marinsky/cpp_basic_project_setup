#include <stdexcept>
#include "data_providers/unimplemented_network_storage.h"

namespace cpp_example_project {
namespace data_providers {

UnimplementedNetworkStorage::UnimplementedNetworkStorage() {
    // acquire network resource
    // initialize connection
}

UnimplementedNetworkStorage::~UnimplementedNetworkStorage() {
    // close connection
    // release network resource
}

std::vector<int> UnimplementedNetworkStorage::read_all_data() {
    throw std::logic_error("not implemented");
}

void UnimplementedNetworkStorage::write_data_element(const int element) {
    (void)element;  // to prevent unused parameter warning
    throw std::logic_error("not implemented");
}

void UnimplementedNetworkStorage::remove_all_available_data() {
    throw std::logic_error("not implemented");
}

}  // namespace data_providers
}  // namespace cpp_example_project
