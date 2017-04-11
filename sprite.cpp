#include "sprite.h"
#include "graphics.h"
#include "globals.h"

Sprite::Sprite() : _x(0), _y(0){}

Sprite::Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float scale)
  :_x(posX), _y(posY)
{
  this->_sourceRect.x = sourceX;
  this->_sourceRect.y = sourceY;
  this->_sourceRect.w = width;
  this->_sourceRect.h = height;

  _visible = true;
  _scale = scale;

  this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.GetRenderer(), graphics.LoadImage(filePath));

  if (_spriteSheet == NULL)
  {
    perror("\nError: Image couldn't be loaded.\n");
  }
}

Sprite::~Sprite()
{

}

void Sprite::Update()
{

}

void Sprite::Draw(Graphics &graphics, int x, int y, float scale)
{
  SDL_Rect destinationRectangle = {x, y, (int)(this->_sourceRect.w * globals::SPRITE_SCALE * scale), (int)(this->_sourceRect.h * globals::SPRITE_SCALE * scale) };
  graphics.BlitSurface(this->_spriteSheet, &this->_sourceRect, &destinationRectangle);
}

void Sprite::MoveHorizontal(float speed)
{
  this->_x += speed;
}
