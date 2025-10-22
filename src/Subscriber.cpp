#include <dds/core/Subscriber.hpp>
#include <dds/core/DomainParticipant.hpp>
#include <iostream>

namespace dds {
namespace core {

Subscriber::Subscriber(std::shared_ptr<DomainParticipant> participant) : participant_(participant) {}

void Subscriber::enable() {
    // In the future, this will involve network resources.
    std::cout << "Subscriber enabled." << std::endl;
}

std::shared_ptr<DomainParticipant> Subscriber::get_participant() const {
    // .lock() is used to safely convert the weak_ptr to a shared_ptr
    return participant_.lock();
}

} // namespace core
} // namespace dds
