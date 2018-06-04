#ifndef __CONSTRUCT_ENG_PARAM__
#define __CONSTRUCT_ENG_PARAM__
#include "Events.h"
#include "IApplication.h"
class ConstructEngineParameters
{
public:
 ConstructEngineParameters(IApplication*);
public:
 Dispatcher* getDispatcher();
private:
 IApplication* getApplication();
private:
  IApplication* m_weakPtr_app;
};
#endif
