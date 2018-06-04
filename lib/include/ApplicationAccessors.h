#ifndef __APP_ACCESSORS__
#define __APP_ACCESSORS__

#include "Engine.h"
#include "IApplication.h"

/**
 * Give access to private functions to configure the application
 */
class ConfigurableApplicationAccessor
{
public:
  ConfigurableApplicationAccessor(IApplication*);
public:
  void addEngine(IEngine*);
  IApplication* getApplication();
private:
  IApplication* m_WeakPtrApplication;
};
#endif
