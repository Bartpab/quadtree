#include <vector>
#include "Engine.h"

class Application {
  public:
    void init();
    void start();
  private:
    std::vector<IEngine*> m_ownedPtr_Engines;
};
