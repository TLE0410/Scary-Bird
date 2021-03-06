#ifndef GLOBALS_H
#define GLOBALS_H

#include <map>

namespace globals
{
  const int SPRITE_SCALE = 3.0f;

  const int SCREEN_WIDTH = 144 * SPRITE_SCALE;
  const int SCREEN_HEIGHT = 256 * SPRITE_SCALE;

  const float GAME_SPEED = .066666667f * SPRITE_SCALE;

}

struct Vector2
{
  int x, y;

  Vector2() : x(0), y(0) {}

  Vector2(int x, int y) : x(x), y(y) {}

  Vector2 zero()
  {
    return Vector2(0, 0);
  }
};

extern std::map<char, Vector2> characterSpriteLocations;

#endif
