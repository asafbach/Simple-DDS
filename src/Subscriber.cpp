#include <dds/core/Subscriber.hpp>
#include <dds/core/DomainParticipant.hpp>
#include <iostream>
#include <mutex>

namespace dds {
namespace core {

Subscriber::Subscriber(std::shared_ptr<DomainParticipant> participant,const SubscriberQos& qos)
 : participant_(participant), qos_(qos) {}

void Subscriber::enable() {
    // In the future, this will involve network resources.
    std::cout << "Subscriber enabled." << std::endl;
}

std::shared_ptr<DomainParticipant> Subscriber::get_participant() const {
    // .lock() is used to safely convert the weak_ptr to a shared_ptr
    return participant_.lock();
}

SubscriberQos Subscriber::get_qos() const{
    std::lock_guard<std::mutex> lock(mtx_);
    return qos_;

}

bool Subscriber::set_qos(const SubscriberQos& qos){
    std::lock_guard<std::mutex> lock(mtx_);
    qos_ = qos;
    return true;
}

} // namespace core
} // namespace dds
