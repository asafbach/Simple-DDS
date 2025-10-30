#pragma once

#include <dds/core/Entity.hpp>
#include <dds/core/Types.hpp>
#include <dds/core/qos/QosProfiles.hpp>
#include <string>
#include <memory>
#include <mutex>


namespace dds {
namespace core {

class DomainParticipant; // Forward declaration
// struct TopicQos;

class Topic : public Entity, public std::enable_shared_from_this<Topic> {
public:
    friend class DomainParticipant;

    void enable() override;

    std::shared_ptr<DomainParticipant> get_participant() const;
    const std::string& get_topic_name() const;
    const std::string& get_type_name() const;

    TopicQos get_qos() const;
    bool set_qos(const TopicQos& qos);

private:
    Topic(const std::string& topic_name, 
          const std::string& type_name,
          std::shared_ptr<DomainParticipant> participant, const TopicQos& qos);
    
    std::string topic_name_;
    std::string type_name_;
    std::weak_ptr<DomainParticipant> participant_;
    TopicQos qos_;
    mutable std::mutex mtx_;
};

} // namespace core
} // namespace dds
