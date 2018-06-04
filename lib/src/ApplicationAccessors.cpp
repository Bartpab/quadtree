#include <algorithm>
#include "ApplicationAccessors.h"

//////////////////////////
// Application Accessor //
//////////////////////////

ConfigurableApplicationAccessor::ConfigurableApplicationAccessor(IApplication* weakPtrApp): m_WeakPtrApplication(weakPtrApp)
{}

IApplication* ConfigurableApplicationAccessor::getApplication()
{
  return m_WeakPtrApplication;
}
void ConfigurableApplicationAccessor::addEngine(IEngine *engine)
{
  this->getApplication()->addEngine(engine);
}
