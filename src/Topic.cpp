#include <dds/core/Topic.hpp>
#include <dds/core/DomainParticipant.hpp>
#include <iostream>

namespace dds {
namespace core {


Topic::Topic(const std::string& topic_name, const std::string& type_name,
          std::shared_ptr<DomainParticipant> participant, const TopicQos& qos)
           : topic_name_(topic_name), type_name_(type_name), participant_(participant), qos_(qos) {}

void Topic::enable(){
    // In the future, this will register the topic with the network discovery service.
    std::cout << "Topic '" << topic_name_ << "' enabled." << std::endl;
}

std::shared_ptr<DomainParticipant> Topic::get_participant() const {
    return participant_.lock();
}


const std::string& Topic::get_topic_name() const {
    return topic_name_;
}

const std::string& Topic::get_type_name() const {
    return type_name_;
}

TopicQos Topic::get_qos() const{
    std::lock_guard<std::mutex> lock(mtx_);
    return qos_;

}

bool Topic::set_qos(const TopicQos& qos){
    std::lock_guard<std::mutex> lock(mtx_);
    qos_ = qos;
    return true;
}

} // namespace core
} // namespace dds