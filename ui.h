#ifndef UI_H
#define UI_H

#include "sprite.h"

class UI : public Sprite
{
public:
  UI();
  UI(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY);
  ~UI();

protected:
  float _x, _y;
};


#endif
