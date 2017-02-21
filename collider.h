#ifndef COLLIDER_H
#define COLLIDER_H

class Collider
{
public:
  Collider();
  Collider(float posX, float posY);
  ~Collider();

  //bool CheckCollision(Collider other);
  void SetPosition(float posX, float posY);
  bool CheckCollision(const Collider other);
  float GetX() const { return _x; }
  float GetY() const { return _y; }

  void SetGlobalX(float globalX) { _globalX = globalX; }
  void SetGlobalY(float globalY) { _globalY = globalY; }
  float GetGlobalX() const { return _globalX; }
  float GetGlobalY() const { return _globalY; }
  unsigned int GetColliderId() { return _colliderId; }

protected:
  float _x, _y;
  float _globalX, _globalY;
  unsigned int _colliderId;

private:

};

#endif
