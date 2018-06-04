#include <SDL2/SDL.h>
#include <algorithm>

#include "Application.h"
#include "ApplicationAccessors.h"

/////////////////
// Application //
/////////////////
Application::Application()
{
  
}
Application::~Application()
{
  this->deleteEngines();
}

void Application::init()
{
  SDL_Init(0);
  this->initEngines();
}

void Application::start()
{
  this->startEngines();
}

void Application::stop()
{
  this->stopEngines();
}

void Application::requestConfigAccess(IApplicationConfigurator* weakRefAppBuilder)
{
  auto accessor = ConfigurableApplicationAccessor(this);
  weakRefAppBuilder->accept(accessor);
}

void Application::initEngines()
{
  auto ref_Engines = this->getEngines();
  std::for_each(ref_Engines.begin(), ref_Engines.end(), [] (IEngine* refEngine) {
    refEngine->init();
  });
}

void Application::startEngines()
{
  auto ref_Engines = this->getEngines();
  std::for_each(ref_Engines.begin(), ref_Engines.end(), [] (IEngine* refEngine) {
    refEngine->start();
  });
}

void Application::stopEngines()
{
  auto ref_Engines = this->getEngines();
  std::for_each(ref_Engines.begin(), ref_Engines.end(), [] (IEngine* refEngine) {
    refEngine->stop();
  });
}

void Application::deleteEngines()
{
  auto ref_Engines = this->getEngines();
  Application::Engines_t::iterator it;

  for (it = ref_Engines.begin(); it != ref_Engines.end(); it++) {
    delete (*it);
  }

  ref_Engines.clear();
}

Application::Engines_t& Application::getEngines()
{
  return this->m_ownedPtr_Engines;
}
