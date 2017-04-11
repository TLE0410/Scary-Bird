#include "ui.h"

UI::UI() {}

UI::UI(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY)
  : Sprite(graphics, filePath, sourceX, sourceY, width, height, posX, posY), _x(posX), _y(posY)
{

}

UI::~UI()
{

}
