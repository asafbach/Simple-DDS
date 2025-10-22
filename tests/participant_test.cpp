#include <gtest/gtest.h>
#include <dds/core/DomainParticipantFactory.hpp>
#include <dds/core/DomainParticipant.hpp>
#include <dds/core/Publisher.hpp>

using namespace dds::core;

class ParticipantTest : public ::testing::Test {
protected:
    void SetUp() override {
        participant = DomainParticipantFactory::get_instance().create_participant(0);
        ASSERT_NE(participant, nullptr);
    }

    void TearDown() override {
        DomainParticipantFactory::get_instance().delete_participant(participant);
    }

    std::shared_ptr<DomainParticipant> participant;
};

TEST_F(ParticipantTest, CreateDeletePublisher) {
    auto publisher = participant->create_publisher();
    ASSERT_NE(publisher, nullptr);
    EXPECT_EQ(publisher->get_participant(), participant);

    bool deleted = participant->delete_publisher(publisher);
    EXPECT_TRUE(deleted);
    EXPECT_EQ(publisher, nullptr); // delete_publisher should reset the shared_ptr
}

TEST_F(ParticipantTest, CreateDeleteSubscriber) {
    auto subscriber = participant->create_subscriber();
    ASSERT_NE(subscriber, nullptr);
    EXPECT_EQ(subscriber->get_participant(), participant);

    bool deleted = participant->delete_subscriber(subscriber);
    EXPECT_TRUE(deleted);
    EXPECT_EQ(subscriber, nullptr);
}

TEST_F(ParticipantTest, CreateDeleteTopic) {
    auto topic = participant->create_topic("TestTopic", "TestType");
    ASSERT_NE(topic, nullptr);
    EXPECT_EQ(topic->get_participant(), participant);
    EXPECT_EQ(topic->get_topic_name(), "TestTopic");
    EXPECT_EQ(topic->get_type_name(), "TestType");

    bool deleted = participant->delete_topic(topic);
    EXPECT_TRUE(deleted);
    EXPECT_EQ(topic, nullptr);
}

TEST_F(ParticipantTest, DeleteNonExistentEntity) {
    auto publisher1 = participant->create_publisher();
    auto participant2 = DomainParticipantFactory::get_instance().create_participant(1);
    
    // Try to delete a publisher that belongs to another participant
    bool deleted = participant2->delete_publisher(publisher1);
    EXPECT_FALSE(deleted);
    EXPECT_NE(publisher1, nullptr); // The original shared_ptr should not be reset

    // Cleanup
    participant->delete_publisher(publisher1);
    DomainParticipantFactory::get_instance().delete_participant(participant2);
}