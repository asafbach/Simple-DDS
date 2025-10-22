#include <dds/core/Topic.hpp>
#include <dds/core/DomainParticipant.hpp>
#include <iostream>

namespace dds {
namespace core {


Topic::Topic(const std::string& topic_name, const std::string& type_name,
          std::shared_ptr<DomainParticipant> participant)
           : topic_name_(topic_name), type_name_(type_name), participant_(participant) {}

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


} // namespace core
} // namespace dds