#pragma once

#include <dds/core/Entity.hpp>
#include <dds/core/Types.hpp>
#include <dds/core/Publisher.hpp>
#include <dds/core/Subscriber.hpp>
#include <dds/core/Topic.hpp>
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

///
/// @class DomainParticipant
/// @brief Acts as a container for all other Entity objects and represents the
///        participation of the application on a communication plane (domain).
///
class DomainParticipant : public Entity, public std::enable_shared_from_this<DomainParticipant>{
public:
    /// @brief Enables the DomainParticipant.
    void enable() override;

    /// @brief Gets the domain ID this participant belongs to.
    /// @return The domain ID.
    DomainId_t get_domain_id() const;

    /// @brief Factory Methods for Publisher, Subscriber, Topic
    std::shared_ptr<Publisher> create_publisher();
    bool delete_publisher(std::shared_ptr<Publisher>& publisher);
    
    std::shared_ptr<Subscriber> create_subscriber();
    bool delete_subscriber(std::shared_ptr<Subscriber>& subscriber);
    
    std::shared_ptr<Topic> create_topic(const std::string& topic_name, const std::string& type_name);
    bool delete_topic(std::shared_ptr<Topic>& topic);

private:
    // Private constructor, can only be created by the factory.
    friend class DomainParticipantFactory;
    explicit DomainParticipant(DomainId_t domain_id);

    DomainId_t domain_id_;
    bool enabled_ = false;

    std::vector<std::shared_ptr<Publisher>> publishers_;
    std::vector<std::shared_ptr<Subscriber>> subscribers_;
    std::vector<std::shared_ptr<Topic>> topics_;
};

} // namespace core
} // namespace dds

