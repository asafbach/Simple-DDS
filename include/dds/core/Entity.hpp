#pragma once

namespace dds {
namespace core {

// Forward declare QoS profiles
// struct DomainParticipantQos;
// struct PublisherQos;
// struct SubscriberQos;
// struct TopicQos;
// struct DataWriterQos; 
// struct DataReaderQos; 

class Entity {
public:

    virtual ~Entity() = default;

    virtual void enable() = 0;

protected:
    // Protected constructor to make it an abstract class.
    Entity() = default;
};

} // namespace core
} // namespace dds

