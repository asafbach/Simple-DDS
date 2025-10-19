#pragma once

#include <dds/core/Entity.hpp>
#include <dds/core/types.hpp>

namespace dds {
namespace core {

///
/// @class DomainParticipant
/// @brief Acts as a container for all other Entity objects and represents the
///        participation of the application on a communication plane (domain).
///
class DomainParticipant : public Entity {
public:
    /// @brief Enables the DomainParticipant.
    void enable() override;

    /// @brief Gets the domain ID this participant belongs to.
    /// @return The domain ID.
    DomainId_t get_domain_id() const;

private:
    // Private constructor, can only be created by the factory.
    friend class DomainParticipantFactory;
    explicit DomainParticipant(DomainId_t domain_id);

    DomainId_t domain_id_;
    bool enabled_ = false;
};

} // namespace core
} // namespace dds

