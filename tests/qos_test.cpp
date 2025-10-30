
#include <gtest/gtest.h>
#include <dds/core/DomainParticipantFactory.hpp>
#include <dds/core/DomainParticipant.hpp>
#include <dds/core/Publisher.hpp>
#include <dds/core/Subscriber.hpp>
#include <dds/core/Topic.hpp>
#include <dds/core/qos/QosPolicies.hpp>
#include <dds/core/qos/QosProfiles.hpp>

using namespace dds::core;

class QosTest : public ::testing::Test {
protected:
    void SetUp() override {
        factory = &DomainParticipantFactory::get_instance();
        participant = factory->create_participant(0); // Uses default participant QoS
        ASSERT_NE(participant, nullptr);
    }

    void TearDown() override {
         factory->delete_participant(participant);
    }

    DomainParticipantFactory* factory;
    std::shared_ptr<DomainParticipant> participant;
};

TEST_F(QosTest, DefaultParticipantQos) {
    // Check factory default
    DomainParticipantQos factory_default_qos = factory->get_default_participant_qos();
    // Add checks here if DomainParticipantQos gets members later

    // Check participant was created with default
    DomainParticipantQos participant_qos = participant->get_qos();
    // Add checks here comparing participant_qos to factory_default_qos
}

TEST_F(QosTest, SetGetParticipantQos) {
    DomainParticipantQos new_qos;
    // Modify new_qos if it has members, e.g., new_qos.user_data.value = {1, 2};

    EXPECT_TRUE(participant->set_qos(new_qos));
    DomainParticipantQos current_qos = participant->get_qos();
    // Add checks here comparing current_qos to new_qos
}


TEST_F(QosTest, DefaultTopicQos) {
    // Check participant's default for topics
    TopicQos participant_default_topic_qos = participant->get_default_topic_qos();
    EXPECT_EQ(participant_default_topic_qos.durability.kind, DurabilityKind::VOLATILE);
    EXPECT_EQ(participant_default_topic_qos.reliability.kind, ReliabilityKind::BEST_EFFORT);
    EXPECT_EQ(participant_default_topic_qos.history.kind, HistoryKind::KEEP_LAST);
    //EXPECT_EQ(participant_default_topic_qos.history.depth, 1);

    // Create topic with participant's default
    auto topic = participant->create_topic("DefaultTopic", "Type");
    ASSERT_NE(topic, nullptr);
    TopicQos topic_qos = topic->get_qos();

    EXPECT_EQ(topic_qos.durability.kind, participant_default_topic_qos.durability.kind);
    EXPECT_EQ(topic_qos.reliability.kind, participant_default_topic_qos.reliability.kind);
    EXPECT_EQ(topic_qos.history.kind, participant_default_topic_qos.history.kind);
    EXPECT_EQ(topic_qos.history.depth, participant_default_topic_qos.history.depth);
}

TEST_F(QosTest, SpecificTopicQos) {
    TopicQos specific_qos;
    specific_qos.durability.kind = DurabilityKind::VOLATILE;
    specific_qos.reliability.kind = ReliabilityKind::RELIABLE;
    specific_qos.history.kind = HistoryKind::KEEP_ALL;
    specific_qos.history.depth = 10; // Depth is ignored for KEEP_ALL but we set it anyway
    //specific_qos.resource_limits.max_samples_per_instance = 100;

    auto topic = participant->create_topic("SpecificTopic", "Type", specific_qos);
    ASSERT_NE(topic, nullptr);
    TopicQos topic_qos = topic->get_qos();

    EXPECT_EQ(topic_qos.durability.kind, DurabilityKind::VOLATILE);
    EXPECT_EQ(topic_qos.reliability.kind, ReliabilityKind::RELIABLE);
    EXPECT_EQ(topic_qos.history.kind, HistoryKind::KEEP_ALL);
    EXPECT_EQ(topic_qos.history.depth, 10);
    //EXPECT_EQ(topic_qos.resource_limits.max_samples_per_instance, 100);
}

TEST_F(QosTest, SetGetTopicQos) {
    auto topic = participant->create_topic("SetGetTopic", "Type");
    ASSERT_NE(topic, nullptr);

    TopicQos original_qos = topic->get_qos();
    EXPECT_EQ(original_qos.reliability.kind, ReliabilityKind::BEST_EFFORT); // Should be default

    TopicQos new_qos;
    new_qos.reliability.kind = ReliabilityKind::RELIABLE;
    //new_qos.reliability.max_blocking_time = {1, 0}; // 1 second

    EXPECT_TRUE(topic->set_qos(new_qos));

    TopicQos current_qos = topic->get_qos();
    EXPECT_EQ(current_qos.reliability.kind, ReliabilityKind::RELIABLE);
    //EXPECT_EQ(current_qos.reliability.max_blocking_time.sec, 1);
    //EXPECT_EQ(current_qos.reliability.max_blocking_time.nanosec, 0);

    // Check that durability (which wasn't in new_qos) is still default
    EXPECT_EQ(current_qos.durability.kind, DurabilityKind::VOLATILE);
}

TEST_F(QosTest, SetParticipantDefaultTopicQos) {
     TopicQos new_default_qos;
     new_default_qos.durability.kind = DurabilityKind::VOLATILE;

     EXPECT_TRUE(participant->set_default_topic_qos(new_default_qos));

     TopicQos retrieved_default = participant->get_default_topic_qos();
     EXPECT_EQ(retrieved_default.durability.kind, DurabilityKind::VOLATILE);

     // Create a new topic using the NEW default
     auto topic = participant->create_topic("NewDefaultTopic", "Type");
     ASSERT_NE(topic, nullptr);
     TopicQos topic_qos = topic->get_qos();
     EXPECT_EQ(topic_qos.durability.kind, DurabilityKind::VOLATILE);
}