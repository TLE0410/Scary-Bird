#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include "map"
#include <string>

struct SDL_Window;
struct SDL_Renderer;

class Graphics
{
public:
	Graphics();
	~Graphics();

	SDL_Surface* LoadImage(const std::string &filePath);

	void BlitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);

	void Flip();

	void Clear();

	SDL_Renderer* GetRenderer() const;

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	std::map<std::string, SDL_Surface*> _spriteSheets;

};

extern Graphics* _graphics;
extern unsigned int ColliderId;

#endif
