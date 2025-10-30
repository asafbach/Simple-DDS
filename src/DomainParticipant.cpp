#include <dds/core/DomainParticipant.hpp>
#include <dds/core/qos/QosProfiles.hpp>
#include <algorithm>
#include <mutex>

namespace dds {
namespace core {

DomainParticipant::DomainParticipant(DomainId_t domain_id, const DomainParticipantQos& qos)
    : domain_id_(domain_id), qos_(qos),
      default_publisher_qos_(get_default_publisher_qos()), // Initialize defaults from global defaults
      default_subscriber_qos_(get_default_subscriber_qos()),
      default_topic_qos_(default_topic_qos())
{ }

void DomainParticipant::enable()
{
    std::lock_guard<std::mutex> lock(mtx_);
    enabled_ = true;
}

DomainId_t DomainParticipant::get_domain_id() const
{
    return domain_id_;
}

bool DomainParticipant::set_qos(const DomainParticipantQos& qos){
    std::lock_guard<std::mutex> lock(mtx_);
        // Add validation later (e.g., cannot change immutable policies if enabled)

    qos_ = qos;
    return true;
}

DomainParticipantQos DomainParticipant::get_qos() const{
    std::lock_guard<std::mutex> lock(mtx_);
    return qos_;
}

std::shared_ptr<Publisher> DomainParticipant::create_publisher(const PublisherQos& qos)
{
    auto publisher = std::shared_ptr<Publisher>(new Publisher(shared_from_this(),qos));
    publishers_.push_back(publisher);
    return publisher;
}

std::shared_ptr<Publisher> DomainParticipant::create_publisher()
{
    return create_publisher(get_default_publisher_qos());
}

bool DomainParticipant::delete_publisher(std::shared_ptr<Publisher>& publisher){
    if(!publisher || publisher->get_participant().get() !=  this ){
        return false;
    }
    std::lock_guard<std::mutex> lock(mtx_);
    auto it = std::remove(publishers_.begin(), publishers_.end(), publisher);
    publishers_.erase(it, publishers_.end());
    publisher.reset(); 
    return true;
}

std::shared_ptr<Subscriber> DomainParticipant::create_subscriber(const SubscriberQos& qos)
{
    auto subscriber = std::shared_ptr<Subscriber>(new Subscriber(shared_from_this(),qos));
    subscribers_.push_back(subscriber);
    return subscriber;
}

std::shared_ptr<Subscriber> DomainParticipant::create_subscriber()
{
    return create_subscriber(get_default_subscriber_qos());
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

std::shared_ptr<Topic> DomainParticipant::create_topic(const std::string& topic_name, const std::string& type_name, const TopicQos& qos)
{
    auto topic = std::shared_ptr<Topic>(new Topic(topic_name, type_name, shared_from_this(),qos));
    topics_.push_back(topic);
    return topic;
}

std::shared_ptr<Topic> DomainParticipant::create_topic(const std::string& topic_name, const std::string& type_name)
{
    return create_topic(topic_name, type_name, get_default_topic_qos());
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
    
// --- Default QoS Management for child entities ---
bool DomainParticipant::set_default_publisher_qos(const PublisherQos& qos) {
    std::lock_guard<std::mutex> lock(mtx_);
    // Add validation later
    default_publisher_qos_ = qos;
    return true;
}

PublisherQos DomainParticipant::get_default_publisher_qos() const {
    std::lock_guard<std::mutex> lock(mtx_);
    return default_publisher_qos_;
}

bool DomainParticipant::set_default_subscriber_qos(const SubscriberQos& qos) {
    std::lock_guard<std::mutex> lock(mtx_);
    default_subscriber_qos_ = qos;
    return true;
}

SubscriberQos DomainParticipant::get_default_subscriber_qos() const {
    std::lock_guard<std::mutex> lock(mtx_);
    return default_subscriber_qos_;
}

bool DomainParticipant::set_default_topic_qos(const TopicQos& qos) {
    std::lock_guard<std::mutex> lock(mtx_);
    default_topic_qos_ = qos;
    return true;
}

TopicQos DomainParticipant::get_default_topic_qos() const {
    std::lock_guard<std::mutex> lock(mtx_);
    return default_topic_qos_;
}


} // namespace core
} // namespace dds
