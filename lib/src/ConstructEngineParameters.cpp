#include "ConstructEngineParameters.h"

ConstructEngineParameters::ConstructEngineParameters(IApplication* weakPtrApp): m_weakPtr_app(weakPtrApp){}

Dispatcher* ConstructEngineParameters::getDispatcher(){
  return this->getApplication()->getDispatcher();
}

IApplication* ConstructEngineParameters::getApplication()
{
  return this->m_weakPtr_app;
}
