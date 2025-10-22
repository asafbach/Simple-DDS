#include <dds/core/DomainParticipant.hpp>
#include <algorithm>

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

std::shared_ptr<Publisher> DomainParticipant::create_publisher()
{
    auto publisher = std::shared_ptr<Publisher>(new Publisher(shared_from_this()));
    publishers_.push_back(publisher);
    return publisher;
}

bool DomainParticipant::delete_publisher(std::shared_ptr<Publisher>& publisher){
    if(!publisher || publisher->get_participant().get() !=  this ){
        return false;
    }
    auto it = std::remove(publishers_.begin(), publishers_.end(), publisher);
    publishers_.erase(it, publishers_.end());
    publisher.reset(); 
    return true;
}

std::shared_ptr<Subscriber> DomainParticipant::create_subscriber()
{
    auto subscriber = std::shared_ptr<Subscriber>(new Subscriber(shared_from_this()));
    subscribers_.push_back(subscriber);
    return subscriber;
}

bool DomainParticipant::delete_subscriber(std::shared_ptr<Subscriber>& subscriber){
    if(!subscriber || subscriber->get_participant().get() !=  this ){
        return false;
    }
    auto it = std::remove(subscribers_.begin(), subscribers_.end(), subscriber);
    subscribers_.erase(it, subscribers_.end());
    subscriber.reset(); 
    return true;
}

std::shared_ptr<Topic> DomainParticipant::create_topic(const std::string& topic_name, const std::string& type_name)
{
    auto topic = std::shared_ptr<Topic>(new Topic(topic_name, type_name, shared_from_this()));
    topics_.push_back(topic);
    return topic;
}

bool DomainParticipant::delete_topic(std::shared_ptr<Topic>& topic){
    if(!topic || topic->get_participant().get() !=  this ){
        return false;
    }
    auto it = std::remove(topics_.begin(), topics_.end(), topic);
    topics_.erase(it, topics_.end());
    topic.reset(); 
    return true;
}
    



} // namespace core
} // namespace dds
