#include <algorithm>
#include "ApplicationBuilder.h"

/////////////////////////
// Application Builder //
/////////////////////////
ApplicationBuilder::ApplicationBuilder(){

}

ApplicationBuilder::~ApplicationBuilder()
{
  auto ownedPtrAllocators = this->getEngineAllocators();
  std::for_each(ownedPtrAllocators.begin(), ownedPtrAllocators.end(), [](IEngineAllocator* alloc) {
    delete alloc;
  });
  ownedPtrAllocators.clear();
}

Application* ApplicationBuilder::construct()
{
  Application* app = new Application();
  app->requestConfigAccess(this);
  return app;
}

ApplicationBuilder* ApplicationBuilder::addEngine(IEngineAllocator* ownedPtrAllocator)
{
  auto ownedPtrAllocators = this->getEngineAllocators();
  ownedPtrAllocators.push_back(ownedPtrAllocator);
  return this;
}

void ApplicationBuilder::accept(ConfigurableApplicationAccessor& accessor)
{
  auto params = ConstructEngineParameters(accessor.getApplication());
  // Build the engines
  auto refEngineAllocators = this->getEngineAllocators();
  std::for_each(refEngineAllocators.begin(), refEngineAllocators.end(), [&](IEngineAllocator* alloc) {
    accessor.addEngine(alloc->construct(params));
  });
}

ApplicationBuilder::EngineAllocators_t& ApplicationBuilder::getEngineAllocators()
{
  return this->m_ownedPtr_EngineAllocators;
}
