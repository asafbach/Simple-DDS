#include <gtest/gtest.h>
#include <dds/core/DomainParticipantFactory.hpp>



class DomainParticipantFactoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Code here will be called before each test.
        factory = &dds::core::DomainParticipantFactory::get_instance();
    }

    dds::core::DomainParticipantFactory* factory;
};

// Test case to verify participant creation and deletion.
TEST_F(DomainParticipantFactoryTest, CreateAndDeletesParticipant) {
    const dds::core::DomainId_t domain_id = 0;

    // Create a participant
    auto participant = factory->create_participant(domain_id);
    ASSERT_NE(participant, nullptr);
    ASSERT_EQ(participant->get_domain_id(), domain_id);

    // Try to create another one in the same domain, should fail
    auto participant2 = factory->create_participant(domain_id);
    ASSERT_EQ(participant2, nullptr);

    // Delete the participant
    bool deleted = factory->delete_participant(participant);
    ASSERT_TRUE(deleted);

    // Try to create it again, should succeed now
    auto participant3 = factory->create_participant(domain_id);
    ASSERT_NE(participant3, nullptr);
}

// Test case to verify the singleton nature of the factory.
TEST_F(DomainParticipantFactoryTest, IsSingleton) {
    auto& instance1 = dds::core::DomainParticipantFactory::get_instance();
    auto& instance2 = dds::core::DomainParticipantFactory::get_instance();
    ASSERT_EQ(&instance1, &instance2);
}