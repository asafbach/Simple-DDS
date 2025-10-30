#include <dds/core/DomainParticipantFactory.hpp>
#include <iostream>

namespace dds{
namespace core{

    
DomainParticipantFactory& DomainParticipantFactory::get_instance(){
    static DomainParticipantFactory instance;
    return instance;
}

std::shared_ptr<DomainParticipant> DomainParticipantFactory::create_participant(DomainId_t domain_id, DomainParticipantQos qos)
{
    std::lock_guard<std::mutex> lock(mtx_);
    auto it = participants_.find(domain_id);
    if ( it != participants_.end())
    {
        return nullptr;
        if (auto existing = it->second.lock())
        {
            return existing;
        }
    }

    //auto participant = std::make_shared<DomainParticipant>(domain_id);
    auto participant = std::shared_ptr<DomainParticipant>(new DomainParticipant(domain_id, qos));
    participants_[domain_id] = participant;
    return participant;
}
std::shared_ptr<DomainParticipant> DomainParticipantFactory::create_participant(DomainId_t domain_id)
{
    return create_participant(domain_id, get_default_participant_qos());
}

bool DomainParticipantFactory::delete_participant(std::shared_ptr<DomainParticipant>& participant){
    if(participant == nullptr) return false;
    std::lock_guard<std::mutex> lock(mtx_);
    auto domain_id = participant->get_domain_id();
    auto it = participants_.find(domain_id);
    if(it != participants_.end()){
        if (it->second.lock() == participant) {
            participants_.erase(domain_id);
            std::cout << "Participant for domain " << domain_id << " deleted." << std::endl;
            return true;
        }
    }
    

    return false;
}

bool DomainParticipantFactory::set_default_participant_qos(const DomainParticipantQos& qos) {
    std::lock_guard<std::mutex> lock(mtx_);
    // Later add validation here if needed
    default_participant_qos_ = qos;
    return true;
}


DomainParticipantQos DomainParticipantFactory::get_default_participant_qos() const{
    std::lock_guard<std::mutex> lock(mtx_);
    return default_participant_qos_;
}

} // namespace core

    
} // namespace dds
