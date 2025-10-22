#include <dds/core/Publisher.hpp>
#include <dds/core/DomainParticipant.hpp>
#include <iostream>

namespace dds {
namespace core {

Publisher::Publisher(std::shared_ptr<DomainParticipant> participant) : participant_(participant) {}

void Publisher::enable() {
    // In the future, this will involve network resources.
    std::cout << "Publisher enabled." << std::endl;
}

std::shared_ptr<DomainParticipant> Publisher::get_participant() const {
    // .lock() is used to safely convert the weak_ptr to a shared_ptr
    return participant_.lock();
}

} // namespace core
} // namespace dds
