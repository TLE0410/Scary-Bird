#ifndef PIPE_H
#define PIPE_H

#include "sprite.h"
#include "globals.h"
#include "boxcollider.h"

class Pipe : public Sprite
{
public:
  Pipe();
  Pipe(Graphics &graphics, int posX, int posY);
  ~Pipe();

  void Update(float DeltaTime = 0);
  void Draw(Graphics &graphics);
  void MoveHorizontal(float speed);

private:
  Sprite _pipeUp;
  Sprite _pipeDown;

  BoxCollider* _pipeUpBoxCollider;
  BoxCollider* _pipeDownBoxCollider;
  BoxCollider* _scoreBoxTrigger;

  float _pipeGap;

};


#endif
