#include <SDL2/SDL.h>

class GraphicEngine {
public:
  GraphicEngine();
  ~GraphicEngine();
  
  void init();
  void start();

  // Accessors
  SDL_Window* getWindow();

private:
  void setWindow(SDL_Window*);

private:
  SDL_Renderer* m_Renderer;
  SDL_Window* m_Window;
};
