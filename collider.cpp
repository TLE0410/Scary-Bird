#include "collider.h"

Collider::Collider() {}

Collider::Collider(float posX, float posY) : _x(posX), _y(posY) {}

Collider::~Collider() {}

//bool Collider::CheckCollision(Collider collider) { return false; }

void Collider::SetPosition(float posX, float posY)
{
  this->_x = posX;
  this->_y = posY;
}
