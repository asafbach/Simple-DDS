#include <dds/core/DomainParticipant.hpp>

namespace dds {
namespace core {

DomainParticipant::DomainParticipant(DomainId_t domain_id)
    : domain_id_(domain_id)
{
}

void DomainParticipant::enable()
{
    enabled_ = true;
}

DomainId_t DomainParticipant::get_domain_id() const
{
    return domain_id_;
}

} // namespace core
} // namespace dds
