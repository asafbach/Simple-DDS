    #ifndef DDS_CORE_QOS_PROFILES_HPP
    #define DDS_CORE_QOS_PROFILES_HPP

    #include <dds/core/qos/QosPolicies.hpp>
    // Include other policies as they are defined

    namespace dds {
    namespace core {

    // --- QoS Profile Structs for Entities ---

    struct DomainParticipantQos {
        // Currently empty, but will hold policies like:
        // UserDataQosPolicy user_data;
        // EntityFactoryQosPolicy entity_factory;
    };
    struct PublisherQos {
        // Currently empty, but will hold policies like:
        // UserDataQosPolicy user_data;
        // EntityFactoryQosPolicy entity_factory;
    };
    struct SubscriberQos {
        // Currently empty, but will hold policies like:
        // UserDataQosPolicy user_data;
        // EntityFactoryQosPolicy entity_factory;
    };
    struct TopicQos {
        DurabilityQosPolicy durability;
        ReliabilityQosPolicy reliability;
        HistoryQosPolicy history;
        ResourceLimitsQosPolicy resource;
    };

    // --- Forward Declaration for Default QoS Accessor ---
    const DomainParticipantQos& default_participant_qos();
    const TopicQos& default_topic_qos();
    // ... other defaults ...

    } // namespace core
    } // namespace dds

    #endif // DDS_CORE_QOS_PROFILES_HPP
