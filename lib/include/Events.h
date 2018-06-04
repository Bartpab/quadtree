#ifndef __EVENTS__
#define __EVENTS__
#include <functional>
#include <map>
#include <vector>
#include "TypeDescriptor.h"
#include "Container.h"

class Dispatcher;

class IEventReceiver
{
public:
  typedef typeid_t TypeDescriptor;

public:
  virtual void unsubscribe()    = 0;
  virtual TypeDescriptor type() = 0;
  virtual const char* topic()   = 0;
};

template <typename T> class EventReceiver: IEventReceiver
{
  public:
    using callee_t = std::function<void (const char*, T)>;
  public:
    EventReceiver(Dispatcher* weakRefDispatcher, callee_t weakRefCallback, const char* topic);
    ~EventReceiver();

    /**
     * Unsubscribe this receiver
     */
    virtual void unsubscribe();

    /**
     * Send the event to the callee
     * @param event The event to pass to the callee
     */
    void propagate(T event);
    /**
     * Returns the type descriptor of the event
     * @return The type descriptor of the event
     */
    virtual TypeDescriptor type();

    /**
     * Returns the topic
     * @return Topic
     */
    virtual const char* topic();

  private:
    Container<Dispatcher*>* ptr_weakRef_wrapped_Dispatcher;
    Container<callee_t>*    ptr_weakRef_wrapped_callee;
    const char* m_topic;
};

class Dispatcher
{
public:
  typedef std::vector<IEventReceiver*> Receivers_t;
  typedef std::map<IEventReceiver::TypeDescriptor, Receivers_t> ReceiversByType_t;

public:
  Dispatcher();
  ~Dispatcher();

  template <typename T> void publish(const char* topic, T event);
  template <typename T> EventReceiver<T>* subscribe(const char* topic, std::function<void (const char*, T)>);

  void removeReceiver(IEventReceiver*);
private:
  void addReceiver(IEventReceiver*);
  Receivers_t& getReceivers(const char* topic, IEventReceiver::TypeDescriptor type);
  template <typename T> ReceiversByType_t& getReceiversByType(const char* topic);
private:
  std::map<const char*, ReceiversByType_t> m_db;
};

#endif
