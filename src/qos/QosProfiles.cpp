#include <dds/core/qos/QosProfiles.hpp>

namespace dds {
namespace core {

// Define the actual default QoS constants
// According to DDS Spec Table in Section 2.2.3

const DomainParticipantQos PARTICIPANT_QOS_DEFAULT; // Default constructor is fine for now

const PublisherQos PUBLISHER_QOS_DEFAULT; // Default constructor is fine for now

const SubscriberQos SUBSCRIBER_QOS_DEFAULT; // Default constructor is fine for now

const TopicQos TOPIC_QOS_DEFAULT = [] {
    TopicQos qos;
    qos.durability.kind = DurabilityKind::VOLATILE;
    qos.reliability.kind = ReliabilityKind::BEST_EFFORT; // Default for Topic
    qos.history.kind = HistoryKind::KEEP_LAST;
    qos.history.depth = 1;
    // Initialize other TopicQos members to their defaults if needed
    return qos;
}();

// Define accessors
const DomainParticipantQos& default_participant_qos() { return PARTICIPANT_QOS_DEFAULT; }
const PublisherQos& default_publisher_qos() { return PUBLISHER_QOS_DEFAULT; }
const SubscriberQos& default_subscriber_qos() { return SUBSCRIBER_QOS_DEFAULT; }
const TopicQos& default_topic_qos() { return TOPIC_QOS_DEFAULT; }


} // namespace core
} // namespace dds
