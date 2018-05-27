#include <algorithm>

#include "Events.h"
#include "TypeDescriptor.h"

template <typename T> EventReceiver<T>::EventReceiver(Dispatcher* weakRefDispatcher,
  callee_t weakRefCallback,
  const char* topic): m_topic(topic) {
    this->ptr_weakRef_wrapped_Dispatcher = new Container<Dispatcher*>(weakRefDispatcher);
    this->ptr_weakRef_wrapped_callee = new Container<callee_t>(weakRefCallback);
}

template <typename T> void EventReceiver<T>::propagate(T event)
{
  if (this->ptr_weakRef_wrapped_callee != nullptr) {
    callee_t callee = (*this->ptr_weakRef_wrapped_callee)();
    callee(this->topic(), event);
  }
}

template <typename T> EventReceiver<T>::~EventReceiver()
{
  this->unsubscribe();
}

template <typename T> void EventReceiver<T>::unsubscribe()
{
  if (this->ptr_weakRef_wrapped_Dispatcher != nullptr) {
    (*this->ptr_weakRef_wrapped_Dispatcher)()->removeReceiver(this);
    delete this->ptr_weakRef_wrapped_Dispatcher;
    this->ptr_weakRef_wrapped_Dispatcher = nullptr;
  }
  if (this->ptr_weakRef_wrapped_callee != nullptr) {
    delete this->ptr_weakRef_wrapped_callee;
    this->ptr_weakRef_wrapped_callee = nullptr;
  }
}

////////////////
// Dispatcher //
////////////////

Dispatcher::~Dispatcher()
{
    std::map<const char*, ReceiversByType_t>::iterator it_1;
    ReceiversByType_t::iterator it_2;
    Receivers_t::iterator it_3;

    for (it_1 = this->m_db.begin(); it_1 != this->m_db.end(); it_1++) {
      ReceiversByType_t& recs_by_type = (*it_1).second;
      for (it_2 = recs_by_type.begin(); it_2 != recs_by_type.end(); it_2++) {
        Receivers_t& recs = (*it_2).second;
        for(it_3 = recs.begin(); it_3 != recs.end(); it_3++) {
          (*it_3)->unsubscribe();
        }
      }
    }
}

template <typename T> EventReceiver<T>* Dispatcher::subscribe(
  const char* topic,
  std::function<void (const char*, T)> callee)
{
  auto receiver = new EventReceiver<T>(this, callee, topic);
  this->addReceiver(receiver);
  return receiver;
}

template <typename T> void Dispatcher::publish(const char* topic, T event)
{
  IEventReceiver::TypeDescriptor type = type_id<T>();
  Receivers_t::iterator it;
  auto recs = this->getReceivers(topic, type);
  for(it = recs.begin(); it != recs.end(); ++it) {
    static_cast<EventReceiver<T>*>((*it))->propagate(event);
  }
}

template <typename T> Dispatcher::ReceiversByType_t& Dispatcher::getReceiversByType(const char* topic)
{
  return this->m_db[topic];
}

Dispatcher::Receivers_t& Dispatcher::getReceivers(const char* topic, IEventReceiver::TypeDescriptor type)
{
  return this->m_db[topic][type];
}

void Dispatcher::addReceiver(IEventReceiver* rec)
{
  Dispatcher::Receivers_t& recs = this->getReceivers(rec->topic(), rec->type());
  auto result_it = std::find(recs.begin(), recs.end(), rec);
  if (result_it == recs.end()) {
    recs.push_back(rec);
  }
}

void Dispatcher::removeReceiver(IEventReceiver* rec)
{
  Dispatcher::Receivers_t& recs = this->getReceivers(rec->topic(), rec->type());
  recs.erase(
    std::remove_if(
      recs.begin(), recs.end(), [&] (IEventReceiver* stored) {
        return stored == rec;
      }
    ), recs.end()
  );
}
