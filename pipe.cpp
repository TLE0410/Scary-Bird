#include "pipe.h"
#include "globals.h"
#include "graphics.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>

Pipe::Pipe() {}

Pipe::Pipe(Graphics &graphics, int posX, int posY) : Sprite(graphics, "Content/Sprite.png", 512, 512, 26, 0, posX, posY)
{
  _pipeGap = 220 * globals::SPRITE_SCALE;

  _pipeUp = Sprite(graphics, "Content/Sprite.png", 0, 256, 26, 160, this->GetX(), this->GetY());
  _pipeDown = Sprite(graphics, "Content/Sprite.png", 26, 256, 26, 160, _pipeUp.GetX(), _pipeUp.GetY() + 70 * globals::SPRITE_SCALE);

  this->_pipeUpBoxCollider = new BoxCollider(_pipeUp.GetX(), _pipeUp.GetY(), _pipeUp.GetScaledWidth(), _pipeUp.GetScaledHeight(), ColliderId++, &_pipeUp);
  _boxColliders.push_back(_pipeUpBoxCollider);

  this->_pipeDownBoxCollider = new BoxCollider(_pipeDown.GetX(), _pipeDown.GetY(), _pipeDown.GetScaledWidth(), _pipeDown.GetScaledHeight(), ColliderId++, &_pipeDown);
  _boxColliders.push_back(_pipeDownBoxCollider);

  int _pipeRawGap = 220 * globals::SPRITE_SCALE - _pipeUp.GetScaledHeight();
  this->_scoreBoxTrigger = new BoxCollider(0, 0, _pipeUp.GetScaledWidth(), _pipeRawGap, ColliderId++, this);
  _boxTriggers.push_back(_scoreBoxTrigger);

}

Pipe::~Pipe()
{

}

void Pipe::Draw(Graphics &graphics)
{
  _pipeUp.SetX(this->GetX());
  _pipeUp.SetY(this->GetY());

  _pipeDown.SetX(this->_pipeUp.GetX());
  _pipeDown.SetY(this->_pipeUp.GetY() + _pipeGap);

  _pipeUp.Draw(graphics, _pipeUp.GetX(), _pipeUp.GetY());
  _pipeDown.Draw(graphics, _pipeDown.GetX(), _pipeDown.GetY());

  //_pipeUpBoxCollider->DrawCollider();
  //_pipeDownBoxCollider->DrawCollider();
  //_scoreBoxTrigger->DrawCollider();
}

void Pipe::Update(float DeltaTime)
{
  _pipeUpBoxCollider->SetPosition(this->_x, _pipeUp.GetY());
  _pipeDownBoxCollider->SetPosition(this->_x, _pipeDown.GetY());
  _scoreBoxTrigger->SetPosition(this->_x, _pipeUp.GetY() + _pipeUp.GetScaledHeight());
}

void Pipe::MoveHorizontal(float speed)
{
  Sprite::MoveHorizontal(speed);
  _pipeUp.SetX(this->GetX());
  _pipeUp.SetY(this->GetY());

  _pipeDown.SetX(this->GetX());
  _pipeDown.SetY(this->GetY() + _pipeGap);

  _pipeUpBoxCollider->SetGlobalX(this->GetX());
  _pipeUpBoxCollider->SetGlobalY(this->GetY());
  _pipeDownBoxCollider->SetGlobalX(this->GetX());
  _pipeDownBoxCollider->SetGlobalY((this->GetY() + _pipeGap));
  _scoreBoxTrigger->SetGlobalX(this->GetX() + _pipeUp.GetScaledWidth());
  _scoreBoxTrigger->SetGlobalY(this->GetY() + _pipeUp.GetScaledHeight());

  this->Draw(*_graphics);
}
