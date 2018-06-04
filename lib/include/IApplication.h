#ifndef __I_APP__
#define __I_APP__
#include "Events.h"
#include ""

class IApplicationConfigurator
{
public:
    virtual void accept(ConfigurableApplicationAccessor&) = 0;
};

class IApplication
{
public:
  virtual void requestConfigAccess(IApplicationConfigurator*) = 0;
  virtual Dispatcher* getDispatcher() = 0;
};
#endif
