#include "graphics.h"
#include <SDL.h>
#include <SDL2/SDL_image.h>

#include "globals.h"

Graphics::Graphics()
{
  SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, SDL_WINDOW_OPENGL, &this->_window, &this->_renderer);
  SDL_SetWindowTitle(this->_window, "Scary Bird");
}

Graphics::~Graphics()
{
  SDL_DestroyWindow(this->_window);
}

SDL_Surface* Graphics::LoadImage(const std::string &filePath)
{
  if (this->_spriteSheets.count(filePath) == 0)
  {
    this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
  }

  return this->_spriteSheets[filePath];
}

void Graphics::BlitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle)
{
  SDL_RenderCopy(this->_renderer, source, sourceRectangle, destinationRectangle);
}

void Graphics::Flip()
{
  SDL_RenderPresent(this->_renderer);
}

void Graphics::Clear()
{
  SDL_RenderClear(this->_renderer);
}

SDL_Renderer* Graphics::GetRenderer() const
{
  return this->_renderer;
}
