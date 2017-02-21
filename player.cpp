#include "player.h"
#include "graphics.h"
#include <math.h>

namespace player_stats
{
  const float JUMP_SPEED = .183f * globals::SPRITE_SCALE;

  const float JUMP_END_SPEED = .000666667f * globals::SPRITE_SCALE;
  const float FALL_SPEED = .33333f * globals::SPRITE_SCALE;
}

Player::Player() {}

Player::Player(Graphics &graphics, Vector2 spawnPoint)
  : AnimatedSprite(graphics, "Content/Sprite.png", 52, 256, 18, 15, spawnPoint.x, spawnPoint.y, 125), _dy(0)
{
  graphics.LoadImage("Content/Sprite.png");

  this->SetupAnimations();
  this->PlayAnimation("BirdFly");

  this->_boxCollider = BoxCollider(this->_x, this->_y, this->GetScaledWidth() - 5 * globals::SPRITE_SCALE, this->GetScaledHeight() - 5 * globals::SPRITE_SCALE, ColliderId++, this);
}

Player::~Player() {}

void Player::Draw(Graphics &graphics)
{
  AnimatedSprite::Draw(graphics, this->_x, this->_y);
  //this->_boxCollider.DrawCollider();
}

void Player::Update(float DeltaTime)
{
  AnimatedSprite::Update(DeltaTime);

  if (this->_dy <= player_stats::FALL_SPEED) this->_dy += player_stats::JUMP_END_SPEED * DeltaTime * cos(this->_dy);
  this->_y += this->_dy * DeltaTime;

  _boxCollider.SetPosition(this->_x + 2.5 * globals::SPRITE_SCALE, this->_y + 2.5 * globals::SPRITE_SCALE);
}

void Player::SetupAnimations()
{
  this->AddAnimation(3, 52, 256, "BirdFly", 18, 15, Vector2(0, 0));
}


void Player::AnimationDone(std::string currentAnimation)
{

}

void Player::Jump()
{
  if(this->_dy >= -player_stats::JUMP_SPEED) this->_dy = -player_stats::JUMP_SPEED;
}

void Player::Restart()
{
  _dy = 0;
}
