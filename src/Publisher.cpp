#include <dds/core/Publisher.hpp>
#include <dds/core/DomainParticipant.hpp>
#include <iostream>
#include <mutex>

namespace dds {
namespace core {

Publisher::Publisher(std::shared_ptr<DomainParticipant> participant, const PublisherQos& qos) 
: participant_(participant), qos_(qos) {}

void Publisher::enable() {
    // In the future, this will involve network resources.
    std::cout << "Publisher enabled." << std::endl;
}

std::shared_ptr<DomainParticipant> Publisher::get_participant() const {
    // .lock() is used to safely convert the weak_ptr to a shared_ptr
    return participant_.lock();
}

PublisherQos Publisher::get_qos() const{
    std::lock_guard<std::mutex> lock(mtx_);
    return qos_;

}

bool Publisher::set_qos(const PublisherQos& qos){
    std::lock_guard<std::mutex> lock(mtx_);
    qos_ = qos;
    return true;
}

} // namespace core
} // namespace dds
