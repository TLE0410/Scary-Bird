#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <string>
#include "globals.h"

class Graphics;

class Sprite
{
public:
  Sprite();
  Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY);

  virtual ~Sprite();
  virtual void Update();
  void Draw(Graphics &graphics, int x, int y);

  void MoveHorizontal(float speed);

  int GetX() { return _x; }
  int GetY() { return _y; }
  void SetX(float x) { _x = x; }
  void SetY(float y) { _y = y; }

  int GetScaledWidth() { return _sourceRect.w * globals::SPRITE_SCALE; }
  int GetScaledHeight() { return _sourceRect.h * globals::SPRITE_SCALE; }

  SDL_Rect GetSourceRect() { return _sourceRect; };

protected:
  SDL_Rect _sourceRect;
  SDL_Texture* _spriteSheet;
  float _x, _y;

private:


};

#endif
