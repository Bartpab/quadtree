#ifndef __APP_BUILDER__
#define __APP_BUILDER__

#include "IApplication.h"
#include "ApplicationAccessors.h"
#include "ConstructEngineParameters.h"
#include "Engine.h"

class ApplicationBuilder : public IApplicationConfigurator
{
public:
  typedef std::vector<IEngineAllocator*> EngineAllocators_t;
public:
  ApplicationBuilder();
  ~ApplicationBuilder();
public:
  Application* construct();
  void accept(ConfigurableApplicationAccessor&);
public:
  ApplicationBuilder* addEngine(IEngineAllocator*);
private:
    EngineAllocators_t& getEngineAllocators();
private:
    EngineAllocators_t m_ownedPtr_EngineAllocators;
};
#endif
