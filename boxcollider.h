#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <SDL.h>
#include <vector>

#include "collider.h"
#include "globals.h"

class BoxCollider : public Collider
{
public:
  BoxCollider();
  BoxCollider(float posX, float posY, int width, int height, unsigned int colliderId, class Sprite* parent);
  ~BoxCollider();

  void SetPosition(float x, float y);

  bool CheckCollision(const BoxCollider other);// override;
  void DrawCollider();

  int GetW() const { return _w; }
  int GetH() const { return _h; }

  class Sprite* GetParent() { return _parent; }

private:
  int _w;
  int _h;
  class Sprite* _parent;
};

extern std::vector<BoxCollider*> _boxColliders;
extern std::vector<BoxCollider*> _boxTriggers;

#endif
