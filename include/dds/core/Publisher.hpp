#pragma once

#include <dds/core/qos/QosProfiles.hpp>
#include <dds/core/Entity.hpp>
#include <memory>
#include <mutex>

namespace dds {
namespace core {

class DomainParticipant; // Forward declaration

class Publisher : public Entity, public std::enable_shared_from_this<Publisher> {
public:

    friend class DomainParticipant;
    
    void enable() override;

    std::shared_ptr<DomainParticipant> get_participant() const;
    PublisherQos get_qos() const;
    bool set_qos(const PublisherQos& qos);


private:
    explicit Publisher(std::shared_ptr<DomainParticipant> participant, const PublisherQos& qos);
    std::weak_ptr<DomainParticipant> participant_;
    PublisherQos qos_; 
    mutable std::mutex mtx_;

};

} // namespace core
} // namespace dds
