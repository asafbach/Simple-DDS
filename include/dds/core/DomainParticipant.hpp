#pragma once

#include <dds/core/Entity.hpp>
#include <dds/core/Types.hpp>
#include <dds/core/Publisher.hpp>
#include <dds/core/Subscriber.hpp>
#include <dds/core/Topic.hpp>
#include <dds/core/qos/QosProfiles.hpp>
#include <vector>


// // Forward declarations for the classes this participant will create
// namespace dds {
// namespace core {
// class Publisher;
// class Subscriber;
// class Topic;
// }
// }

namespace dds {
namespace core {


class DomainParticipant : public Entity, public std::enable_shared_from_this<DomainParticipant>{
public:
    
    void enable() override;

    bool set_qos(const DomainParticipantQos& qos);
    DomainParticipantQos get_qos() const;

    DomainId_t get_domain_id() const;

    std::shared_ptr<Publisher> create_publisher();
    std::shared_ptr<Publisher> create_publisher(const PublisherQos& qos);
    bool delete_publisher(std::shared_ptr<Publisher>& publisher);
    
    std::shared_ptr<Subscriber> create_subscriber();
    std::shared_ptr<Subscriber> create_subscriber(const SubscriberQos& qos);
    bool delete_subscriber(std::shared_ptr<Subscriber>& subscriber);
    
    std::shared_ptr<Topic> create_topic(const std::string& topic_name, const std::string& type_name);
    std::shared_ptr<Topic> create_topic(const std::string& topic_name, const std::string& type_name
        ,const TopicQos& qos);
    bool delete_topic(std::shared_ptr<Topic>& topic);

    // --- Default QoS Management ---
    bool set_default_publisher_qos(const PublisherQos& qos);
    PublisherQos get_default_publisher_qos() const;

    bool set_default_subscriber_qos(const SubscriberQos& qos);
    SubscriberQos get_default_subscriber_qos() const;

    bool set_default_topic_qos(const TopicQos& qos);
    TopicQos get_default_topic_qos() const;

private:
    // Private constructor, can only be created by the factory.
    friend class DomainParticipantFactory;
    explicit DomainParticipant(DomainId_t domain_id, const DomainParticipantQos& qos);
    DomainId_t domain_id_;
    bool enabled_ = false;
    DomainParticipantQos qos_;

    // Default QoS profiles for entities created by this participant
    PublisherQos default_publisher_qos_;
    SubscriberQos default_subscriber_qos_;
    TopicQos default_topic_qos_;

    std::vector<std::shared_ptr<Publisher>> publishers_;
    std::vector<std::shared_ptr<Subscriber>> subscribers_;
    std::vector<std::shared_ptr<Topic>> topics_;

    mutable std::mutex mtx_; // Protect access to QoS and entity lists

};

} // namespace core
} // namespace dds
