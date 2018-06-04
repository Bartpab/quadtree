#ifndef __APP__
#define __APP__
#include <vector>
#include "Events.h"
#include "Engine.h"
#include "IApplication.h"

class ConfigurableApplicationAccessor;
class Application: public IApplication
{
  friend class ConfigurableApplicationAccessor;

  public:
    typedef std::vector<IEngine*> Engines_t;

  public:
    Application();
    ~Application();

  // Build methods
  public:
      void requestConfigAccess(IApplicationConfigurator*);

  private:
      void addEngine(IEngine*);

  public:
    Dispatcher* getDispatcher();

  // Engine process flow controls
  private:
    void deleteEngines();
    void initEngines();
    void startEngines();
    void stopEngines();

  public:
    void init();
    void start();
    void stop();

  private:
    std::vector<IEngine*>& getEngines();

  private:
    Dispatcher m_Dispatcher;

  private:
    std::vector<IEngine*> m_ownedPtr_Engines;
};
#endif
