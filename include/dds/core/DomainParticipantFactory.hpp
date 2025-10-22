#pragma once

#include <dds/core/DomainParticipant.hpp>
#include <dds/core/Types.hpp>
#include <memory>
#include <mutex>
#include <map>

namespace dds {
namespace core {

///
/// @class DomainParticipantFactory
/// @brief A singleton factory for creating and managing DomainParticipant objects.
///
class DomainParticipantFactory {
public:
    /// @brief Gets the singleton instance of the factory.
    /// @return Reference to the singleton factory instance.
    static DomainParticipantFactory& get_instance();

    /// @brief Creates a new DomainParticipant object.
    /// @param domain_id The ID of the domain to join.
    /// @return Shared pointer to the DomainParticipant.
    std::shared_ptr<DomainParticipant> create_participant(DomainId_t domain_id);
 

    /// @brief Deletes an existing DomainParticipant.
    /// @param participant The participant to delete.
    /// @return True on success, false otherwise.
    bool delete_participant(std::shared_ptr<DomainParticipant>& participant);

    // Disable copy and move operations for the singleton.
    DomainParticipantFactory(const DomainParticipantFactory&) = delete;
    DomainParticipantFactory& operator=(const DomainParticipantFactory&) = delete;

private:
    DomainParticipantFactory() = default;

    std::mutex mtx_;
    std::map<DomainId_t, std::weak_ptr<DomainParticipant>> participants_;
};

} // namespace core
} // namespace dds
