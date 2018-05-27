#include <SDL2/SDL.h>
#include "GraphicEngine.h"
void GraphicEngine::setWindow(SDL_Window* win)
{
  this->m_Window = win;
}

SDL_Window* GraphicEngine::getWindow()
{
  return this->m_Window;
}

GraphicEngine::~GraphicEngine()
{

  if (this->m_Window != NULL) {
    SDL_DestroyWindow(this->m_Window);
    this->m_Window = NULL;
  }

  SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
void GraphicEngine::init()
{
  if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
  {
    throw SDL_GetError();
  }
}
