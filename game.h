#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "pipe.h"

class Graphics;

class Game
{
public:
  Game();
  ~Game();


private:
  void GameLoop();
  void Draw(Graphics &graphics);
  void Update(float DeltaTime);

  int GetRandomPositionForPipes();
  int GetRandomInt(int start, int end);

  void Restart();

  Player _player;

  Sprite _backgroundSprite;
  Sprite _floor;
  Sprite _floor2;

  Pipe _pipe1;
  Pipe _pipe2;
  Pipe _pipe3;

  bool _gameIsRunning;

  int pipeSpace;
  Vector2 playerSpawnPoint;

  int _score;

  unsigned int _triggeredColliderId;
  unsigned int _newTriggeredColliderId;

};

#endif
