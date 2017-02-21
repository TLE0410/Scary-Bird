#ifndef PLAYER_H
#define PLAYER_H

#include "animatedsprite.h"
#include "globals.h"
#include "boxcollider.h"

class Graphics;

class Player : public AnimatedSprite
{
public:
  Player();
  Player(Graphics &graphics, Vector2 spawnPoint);

  ~Player();

  void Draw(Graphics &graphics);
  void Update(float DeltaTime);
  void Jump();

  void Restart();

	virtual void AnimationDone(std::string currentAnimation);
	virtual void SetupAnimations();

  BoxCollider GetPlayerCollider() { return _boxCollider; }

private:
  float _dy;
  BoxCollider _boxCollider;

};

#endif
