#include "ui_text.h"
#include <string>
#include "graphics.h"
#include "globals.h"

Text::Text() {}

Text::Text(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float scale)
  : UI(graphics, filePath, sourceX, sourceY, width, height, posX, posY)
{
  _initialSourceX = sourceX;
  _initialSourceY = sourceY;
  _initialSourceW = width;
  _initialSourceH = height;

  _scale = scale;

  _x = posX;
  _y = posY;
}

Text::~Text()
{}

void Text::Draw(Graphics &graphics)
{
  size_t textSpriteVectorSize = UI_textSprites.size();
  for (size_t i = 0; i < textSpriteVectorSize; i++)
  {
    UI_textSprites[i].Draw(graphics, UI_textSprites[i].GetX(), UI_textSprites[i].GetY(), _scale);
  }
}

void Text::SetText(std::string text)
{
  _text = text;
  size_t textLength = text.size();
  for (size_t i = 0; i < textLength; i++)
  {
    if(UI_textSprites.size() <= i)
    {
      UI_textSprites.push_back(Sprite(*_graphics, "Content/Sprite.png"
                                      , characterSpriteLocations[text.c_str()[i]].x, characterSpriteLocations[text.c_str()[i]].y
                                      , _initialSourceW, _initialSourceH, _x, _y));
      AlignToCenter();
    }
    else
    {
      UI_textSprites[i].SetSourceRectXY(characterSpriteLocations[text.c_str()[i]].x, characterSpriteLocations[text.c_str()[i]].y);
    }
  }
}

void Text::AlignToCenter()
{
  size_t textSpritesSize = UI_textSprites.size();
  UI_textSprites[0].SetX(_x - ((GetScaledWidth() * _scale / 2) * textSpritesSize));

  for (size_t i = 1; i < textSpritesSize; i++)
  {
    UI_textSprites[i].SetX(UI_textSprites[i - 1].GetX() + (UI_textSprites[i - 1].GetScaledWidth() * _scale));
  }
}

void Text::Reset()
{
  UI_textSprites.clear();
  _text = "";
}
