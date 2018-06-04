#include <SDL2/SDL.h>
#include "Events.h"
#include "Engine.h"

class GraphicEngineAllocator: public IEngineAllocator
{
public:
    IEngine* construct(ConstructEngineParameters&);
};

class GraphicEngine: public IEngine {
public:
  GraphicEngine(Dispatcher* weakPtrDispatcher);
  ~GraphicEngine();

  void init();
  void start();
  void step();
  void stop();

  // Accessors
  SDL_Window*   getWindow();
  SDL_Renderer* getRenderer();

private:
  void setWindow(SDL_Window*);
  void setRenderer(SDL_Renderer*);

private:
  SDL_Renderer* m_Renderer;
  SDL_Window*   m_Window;

private:
  Dispatcher* m_WeakPtrDispatcher;
};
