#ifndef GAME_H
#define GAME_H

#include <map>

#include "player.h"
#include "pipe.h"
#include "ui_text.h"
#include "globals.h"

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
  Sprite _gameOverSprite;

  /* Restart Sprite will be changed with Button class */
  Sprite _restartSprite;

  Pipe _pipe1;
  Pipe _pipe2;
  Pipe _pipe3;

  Text _scoreText;

  bool _gameIsRunning;

  int pipeSpace;
  Vector2 playerSpawnPoint;

  int _score;

  unsigned int _triggeredColliderId;
  unsigned int _newTriggeredColliderId;

};


#endif
