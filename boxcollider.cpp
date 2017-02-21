#include "boxcollider.h"
#include "graphics.h"
#include "sprite.h"

BoxCollider::BoxCollider() {}

BoxCollider::BoxCollider(float posX, float posY, int width, int height, unsigned int colliderId, Sprite* parent)
  : Collider(posX, posY), _w(width), _h(height), _parent(parent)
{
  _colliderId = colliderId;
}

BoxCollider::~BoxCollider() {}

void BoxCollider::SetPosition(float x, float y)
{
  _x = x;
  _y = y;
}

bool BoxCollider::CheckCollision(const BoxCollider other)
{
  float otherX = other.GetX();
  float otherY = other.GetY();
  int otherW = other.GetW();
  int otherH = other.GetH();

  float otherXW = otherX + (float)otherW;
  float otherYH = otherY + (float)otherH;

  float thisX = this->GetGlobalX();
  float thisY = this->GetGlobalY();
  float thisXW = this->_x + (float)this->_w;
  float thisYH = this->_y + (float)this->_h;

  return (otherXW <= thisXW && otherXW >= thisX && ((otherY >= thisY && otherY <= thisYH) || (otherYH >= thisY && otherYH <= thisYH))) ||
         (otherX <= thisXW && otherX >= thisX && ((otherY >= thisY && otherY <= thisYH) || (otherYH >= thisY && otherYH <= thisYH)));
}

void BoxCollider::DrawCollider()
{
  SDL_Rect colliderRect;
  colliderRect.x = this->_x;
  colliderRect.y = this->_y;
  colliderRect.w = this->_w;
  colliderRect.h = this->_h;

  SDL_SetRenderDrawColor(_graphics->GetRenderer(), 200, 0, 0, 255);
  SDL_RenderDrawRect(_graphics->GetRenderer(), &colliderRect);
}
