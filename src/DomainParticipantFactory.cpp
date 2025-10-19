#include <dds/core/DomainParticipantFactory.hpp>
#include <iostream>

namespace dds{
namespace core{

    
DomainParticipantFactory& DomainParticipantFactory::get_instance(){
    static DomainParticipantFactory instance;
    return instance;
}

std::shared_ptr<DomainParticipant> DomainParticipantFactory::create_participant(DomainId_t domain_id)
{
    std::lock_guard<std::mutex> lock(mtx_);
    auto it = participants_.find(domain_id);
    if ( it != participants_.end())
    {
        return nullptr;
        // if (auto existing = it->second.lock())
        // {
        //     return existing;
        // }
    }

    //auto participant = std::make_shared<DomainParticipant>(domain_id);
    auto participant = std::shared_ptr<DomainParticipant>(new DomainParticipant(domain_id));
    participants_[domain_id] = participant;
    return participant;
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



} // namespace core

    
} // namespace dds
