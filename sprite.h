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
  Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float scale = 1.0f);

  virtual ~Sprite();
  virtual void Update();
  void Draw(Graphics &graphics, int x, int y, float scale = 1.0f);

  void MoveHorizontal(float speed);

  int GetX() { return _x; }
  int GetY() { return _y; }
  void SetX(float x) { _x = x; }
  void SetY(float y) { _y = y; }

  int GetScaledWidth() { return _sourceRect.w * _scale * globals::SPRITE_SCALE; }
  int GetScaledHeight() { return _sourceRect.h * _scale * globals::SPRITE_SCALE; }

  SDL_Rect GetSourceRect() { return _sourceRect; };
  void SetSourceRectXY(int x, int y){_sourceRect.x = x; _sourceRect.y = y;}

  void SetVisibility(bool visible){ _visible = visible; }
  bool GetVisibility(){ return _visible; }

  void SetScale(float scale){ _scale = scale; }
  float GetScale(){ return _scale; }

protected:
  SDL_Texture* _spriteSheet;
  float _x, _y;
  SDL_Rect _sourceRect;
  bool _visible;
  float _scale = 1.f;

private:


};

#endif
