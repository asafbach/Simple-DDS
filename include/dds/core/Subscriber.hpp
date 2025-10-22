#pragma once

#include <dds/core/Entity.hpp>
#include <memory>

namespace dds {
namespace core {

class DomainParticipant; // Forward declaration
///
/// @class Subscriber
///
class Subscriber : public Entity, public std::enable_shared_from_this<Subscriber> {
public:
    // This class is part of the factory pattern.
    // It can only be created by its friend, the DomainParticipant.
    friend class DomainParticipant;

    void enable() override;
    
    std::shared_ptr<DomainParticipant> get_participant() const;

private:
    explicit Subscriber(std::shared_ptr<DomainParticipant> participant);
    std::weak_ptr<DomainParticipant> participant_;
};

} // namespace core
} // namespace dds
