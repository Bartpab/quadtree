#include <SDL2/SDL.h>
#include <string>

#include "GraphicEngine.h"

///////////////
// Allocator //
///////////////
IEngine* GraphicEngineAllocator::construct(ConstructEngineParameters& params)
{
  auto gfxEngine = new GraphicEngine(params.getDispatcher());
  return (IEngine*)gfxEngine;
}

////////////
// Engine //
////////////

void GraphicEngine::setWindow(SDL_Window* win)
{
  this->m_Window = win;
}
SDL_Window* GraphicEngine::getWindow()
{
  return this->m_Window;
}

void GraphicEngine::setRenderer(SDL_Renderer *renderer)
{
  this->m_Renderer = renderer;
}
SDL_Renderer* GraphicEngine::getRenderer()
{
  return this->m_Renderer;
}

GraphicEngine::~GraphicEngine()
{
  this->stop();
}

void GraphicEngine::init()
{
  if (SDL_WasInit(SDL_INIT_VIDEO) != 0) {
    return;
  }

  if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
  {
    throw SDL_GetError();
  }
}

void GraphicEngine::start()
{
  this->setWindow(SDL_CreateWindow("QuadTree" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 600 , 600 , SDL_WINDOW_RESIZABLE));
  if (this->getWindow() == nullptr) {
    throw std::string("Cannot create a window.");
  }

  this->setRenderer(SDL_CreateRenderer(this->getWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

  if (this->getRenderer() == nullptr) {
    throw std::string("Cannot create a renderer.");
  }
}

void GraphicEngine::stop()
{
  if (this->getWindow() != nullptr) {
    SDL_DestroyWindow(this->getWindow());
    this->setWindow(nullptr);
  }

  if (SDL_WasInit(SDL_INIT_VIDEO) != 0)
  {
      SDL_QuitSubSystem(SDL_INIT_VIDEO);
  }
}
