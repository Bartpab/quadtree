#ifndef __I_ENGINE__
#define __I_ENGINE__

#include "Events.h"
#include "ConstructEngineParameters.h"

class IEngine {
public:
  virtual void init()   = 0;
  virtual void start()  = 0;
  virtual void step()   = 0;
  virtual void stop()   = 0;
};

class IEngineAllocator {
public:
  virtual IEngine* construct(ConstructEngineParameters&) = 0;
};
#endif
