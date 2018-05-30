#include <SDL2/SDL.h>
#include "Engine.h"

class GraphicEngine: public IEngine {
public:
  GraphicEngine();
  ~GraphicEngine();

  void init();
  void start();
  void stop();

  // Accessors
  SDL_Window*   getWindow();
  SDL_Renderer* getRenderer();

private:
  void setWindow(SDL_Window*);
  void setRenderer(SDL_Renderer*);

private:
  SDL_Renderer* m_Renderer;
  SDL_Window* m_Window;
};
