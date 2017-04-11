#ifndef UI_TEXT_H
#define UI_TEXT_H

#include "ui.h"
#include <vector>

class Text : public UI
{
public:
  Text();
  Text(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float scale = 1.0f);
  ~Text();

  void SetText(std::string text);
  std::string GetText() { return _text; }

  void Draw(Graphics &graphics);
  void AlignToCenter();

  void Reset();

private:
  std::string _text;
  std::vector<Sprite> UI_textSprites;

  float _scale;

  int _initialSourceX;
  int _initialSourceY;
  int _initialSourceW;
  int _initialSourceH;

};

#endif
