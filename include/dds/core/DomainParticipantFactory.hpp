#pragma once

#include <dds/core/DomainParticipant.hpp>
#include <dds/core/qos/QosProfiles.hpp>
#include <dds/core/Types.hpp>
#include <memory>
#include <mutex>
#include <map>

namespace dds {
namespace core {


class DomainParticipantFactory {
public:

    static DomainParticipantFactory& get_instance();

    std::shared_ptr<DomainParticipant> create_participant(DomainId_t domain_id, const DomainParticipantQos qos);
 
    std::shared_ptr<DomainParticipant> create_participant(DomainId_t domain_id);

    bool delete_participant(std::shared_ptr<DomainParticipant>& participant);

    // std::shared_ptr<DomainParticipant> lookup_participant(DomainId_t domain_id);

    bool set_default_participant_qos(const DomainParticipantQos& qos);
    DomainParticipantQos get_default_participant_qos() const;

    // Disable copy/move semantics for Singleton
    DomainParticipantFactory(const DomainParticipantFactory&) = delete;
    DomainParticipantFactory& operator=(const DomainParticipantFactory&) = delete;
    DomainParticipantFactory(DomainParticipantFactory&&) = delete;
    DomainParticipantFactory& operator=(DomainParticipantFactory&&) = delete;

private:
    
    DomainParticipantFactory() = default; 
    ~DomainParticipantFactory() = default; 

    mutable std::mutex mtx_;
    std::map<DomainId_t, std::weak_ptr<DomainParticipant>> participants_;
    DomainParticipantQos default_participant_qos_;
};

} // namespace core
} // namespace dds
