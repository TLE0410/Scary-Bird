#include <SDL.h>
#include <iostream>
#include <string>

#include <tr1/random>

#include "game.h"
#include "graphics.h"
#include "input.h"
#include "globals.h"
#include "boxcollider.h"

unsigned int ColliderId = 1;
std::map<char, Vector2> characterSpriteLocations;

namespace
{
  const int FPS = 60;
  const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Graphics* _graphics;
std::vector<BoxCollider*> _boxColliders;
std::vector<BoxCollider*> _boxTriggers;

Game::Game()
{
  SDL_Init(SDL_INIT_EVERYTHING);
  _gameIsRunning = true;
  _score = 0;
  _triggeredColliderId = 0;
  _newTriggeredColliderId = 0;

  characterSpriteLocations['0'] = Vector2(144, 55);
  characterSpriteLocations['1'] = Vector2(150, 55);
  characterSpriteLocations['2'] = Vector2(156, 55);
  characterSpriteLocations['3'] = Vector2(162, 55);
  characterSpriteLocations['4'] = Vector2(168, 55);
  characterSpriteLocations['5'] = Vector2(174, 55);
  characterSpriteLocations['6'] = Vector2(180, 55);
  characterSpriteLocations['7'] = Vector2(186, 55);
  characterSpriteLocations['8'] = Vector2(192, 55);
  characterSpriteLocations['9'] = Vector2(198, 55);

  this->GameLoop();
}

Game::~Game()
{

}

void Game::GameLoop()
{
  Graphics graphics;
  SDL_Event event;
  Input input;

  _graphics = &graphics;

/********************************************************************************************/
  this->_backgroundSprite = Sprite(graphics, "Content/Sprite.png", 0, 0, 144, 256, 100, 100);
/********************************************************************************************/

/********************************************************************************************/
  playerSpawnPoint = Vector2(globals::SCREEN_WIDTH / 2 - 33 * globals::SPRITE_SCALE, globals::SCREEN_HEIGHT / 2);
  this->_player = Player(graphics, playerSpawnPoint);
/********************************************************************************************/

/********************************************************************************************/
  pipeSpace = (26 + 60) * globals::SPRITE_SCALE;

  this->_pipe1 = Pipe(graphics, globals::SCREEN_WIDTH + 100, GetRandomPositionForPipes());
//  SDL_Delay(500);
  this->_pipe2 = Pipe(graphics, _pipe1.GetX() + pipeSpace, GetRandomPositionForPipes());
//  SDL_Delay(500);
  this->_pipe3 = Pipe(graphics, _pipe2.GetX() + pipeSpace, GetRandomPositionForPipes());
/********************************************************************************************/

/********************************************************************************************/
  this->_floor = Sprite(graphics, "Content/Sprite.png", 144, 0, 168, 56, 0, 203 * globals::SPRITE_SCALE);
  this->_floor2 = Sprite(graphics, "Content/Sprite.png", 144, 0, 168, 56, _floor.GetX() + _floor.GetScaledWidth(), _floor.GetY());
/********************************************************************************************/

  this->_scoreText = Text(graphics, "Content/Sprite.png", 144, 55, 6, 8, globals::SCREEN_WIDTH / 2, 1.1 * globals::SCREEN_HEIGHT / 6, 1.5f);
  this->_scoreText.SetText("0");
/********************************************************************************************/

  this->_gameOverSprite = Sprite(graphics, "Content/Sprite.png", 144, 63, 36, 27, globals::SCREEN_WIDTH / 2 - 18 * 3 * globals::SPRITE_SCALE, globals::SCREEN_HEIGHT / 2 - 25 * 3 * globals::SPRITE_SCALE, 3.0f);
  this->_gameOverSprite.SetVisibility(false);

  /* Restart Sprite will be changed with Button class */
  this->_restartSprite = Sprite(graphics, "Content/Sprite.png", 144, 90, 47, 16, globals::SCREEN_WIDTH / 2 - 23 * 2 * globals::SPRITE_SCALE, _gameOverSprite.GetY() + 50 * 2 * globals::SPRITE_SCALE, 2.0f);
  this->_restartSprite.SetVisibility(false);

  int LAST_UPDATE_TIME = SDL_GetTicks();

  while (true)
  {
    input.BeginNewFrame();

    if(SDL_PollEvent(&event))
    {
      if(event.type == SDL_KEYDOWN)
      {
        if (event.key.repeat == 0)
        {
          input.KeyDownEvent(event);
        }
      }

      else if(event.type == SDL_KEYUP)
      {
        input.KeyUpEvent(event);
      }

      else if(event.type == SDL_QUIT)
      {
        return;
      }
    }

    if(input.WasKeyPressed(SDL_SCANCODE_SPACE) == true)
    {
      if(_player.GetY() > 0) _player.Jump();
    }

    if(input.WasKeyPressed(SDL_SCANCODE_R) == true && !_gameIsRunning)
    {
      Restart();
    }

    if(input.WasKeyPressed(SDL_SCANCODE_ESCAPE) == true)
    {
      return;
    }

    const int CURRENT_TIME_MS = SDL_GetTicks();
    int DELTA_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

    this->Update(std::min(DELTA_TIME_MS, MAX_FRAME_TIME));

    LAST_UPDATE_TIME = CURRENT_TIME_MS;

    this->Draw(graphics);
  }
}

void Game::Draw(Graphics &graphics)
{
  graphics.Clear();

  this->_backgroundSprite.Draw(graphics, 0, 0);
  this->_player.Draw(graphics);

  this->_pipe1.Draw(graphics);
  this->_pipe2.Draw(graphics);
  this->_pipe3.Draw(graphics);

  this->_floor.Draw(graphics, _floor.GetX(), _floor.GetY());
  this->_floor2.Draw(graphics, _floor2.GetX(), _floor2.GetY());

  this->_scoreText.Draw(graphics);

  if (_gameOverSprite.GetVisibility())
  {
    this->_gameOverSprite.Draw(graphics, _gameOverSprite.GetX(), _gameOverSprite.GetY(), 3.0f);
    this->_restartSprite.Draw(graphics, _restartSprite.GetX(), _restartSprite.GetY(), 2.0f);
  }
  graphics.Flip();
}

void Game::Update(float DeltaTime)
{
  if(_player.GetY() + _player.GetScaledWidth() - 10 * globals::SPRITE_SCALE >= _floor.GetY())
  {
    _gameIsRunning = false;
    this->_gameOverSprite.SetVisibility(true);
    this->_restartSprite.SetVisibility(true);
  }

/***************************************************************************************************************************************************/
  if (_gameIsRunning)
  {
    this->_player.Update(DeltaTime);

    this->_pipe1.Update();
    this->_pipe2.Update();
    this->_pipe3.Update();

    if(this->_floor.GetX() > -1 * this->_floor.GetScaledWidth()) this->_floor.MoveHorizontal(-1 * DeltaTime * globals::GAME_SPEED);
    else _floor.SetX(_floor2.GetX() + _floor2.GetScaledWidth());

    if(this->_floor2.GetX() > -1 * this->_floor2.GetScaledWidth()) this->_floor2.MoveHorizontal(-1 * DeltaTime * globals::GAME_SPEED);
    else _floor2.SetX(_floor.GetX() + _floor.GetScaledWidth());
/***************************************************************************************************************************************************/

    if(this->_pipe1.GetX() > -1 * this->_pipe1.GetScaledWidth()) this->_pipe1.MoveHorizontal(-1 * DeltaTime * globals::GAME_SPEED);
    else
    {
      _pipe1.SetX(_pipe3.GetX() + _pipe3.GetScaledWidth() + 60 * globals::SPRITE_SCALE);
      _pipe1.SetY(GetRandomPositionForPipes());
    }

    if(this->_pipe2.GetX() > -1 * this->_pipe2.GetScaledWidth()) this->_pipe2.MoveHorizontal(-1 * DeltaTime * globals::GAME_SPEED);
    else
    {
      _pipe2.SetX(_pipe1.GetX() + _pipe1.GetScaledWidth() + 60 * globals::SPRITE_SCALE);
      _pipe2.SetY(GetRandomPositionForPipes());
    }

    if(this->_pipe3.GetX() > -1 * this->_pipe3.GetScaledWidth()) this->_pipe3.MoveHorizontal(-1 * DeltaTime * globals::GAME_SPEED);
    else
    {
      _pipe3.SetX(_pipe2.GetX() + _pipe2.GetScaledWidth() + 60 * globals::SPRITE_SCALE);
      _pipe3.SetY(GetRandomPositionForPipes());
    }
  }

  if(_gameIsRunning)
  {
    size_t colliderCount = _boxColliders.size();
    BoxCollider playerCollider = this->_player.GetPlayerCollider();
    for (size_t i = 0; i < colliderCount; i++)
    {
      bool checkResult = _boxColliders[i]->CheckCollision(playerCollider);
      if(checkResult)
      {
        _gameIsRunning = false;
        this->_gameOverSprite.SetVisibility(true);
        this->_restartSprite.SetVisibility(true);
      }
    }


/*********************************************************************/
    size_t triggerCount = _boxTriggers.size();

    static BoxCollider* triggeredObject = nullptr;

    bool checkResult;

    for (size_t i = 0; i < triggerCount; i++)
    {
      checkResult = _boxTriggers[i]->CheckCollision(playerCollider);
      if(checkResult)
      {
        triggeredObject = _boxTriggers[i];
        _triggeredColliderId = triggeredObject->GetColliderId();
        break;
      }
    }

    if(triggeredObject != nullptr)
    {
      checkResult = triggeredObject->CheckCollision(playerCollider);

      if(!checkResult)
      {
        if(_triggeredColliderId != _newTriggeredColliderId)
        {
          _score++;
          _newTriggeredColliderId = _triggeredColliderId;
          _scoreText.SetText(std::to_string(_score));
        }
      }
    }
/*********************************************************************/
  }

/***************************************************************************************************************************************************/

}

int Game::GetRandomPositionForPipes()
{
  return GetRandomInt(-140, 110) * globals::SPRITE_SCALE;
}

/*
  Returns a random integer value between start and start + interval
*/

int Game::GetRandomInt(int start, int interval)
{
  int randomInt;
  randomInt = start + rand() % interval;

  return randomInt;
}

void Game::Restart()
{
  _score = 0;
  _scoreText.Reset();
  _scoreText.SetText("0");

  _player.SetX(playerSpawnPoint.x);
  _player.SetY(playerSpawnPoint.y);
  _player.Restart();

  int randPos = GetRandomPositionForPipes();

  _pipe1.SetX(globals::SCREEN_WIDTH + 100);
  _pipe1.SetY(randPos);

//  int temp = randPos;
//  while(randPos == temp) randPos = GetRandomPositionForPipes();

  _pipe2.SetX(_pipe1.GetX() + pipeSpace);
  _pipe2.SetY(randPos);

//  temp = randPos;
//  while(randPos == temp) randPos = GetRandomPositionForPipes();

  _pipe3.SetX(_pipe2.GetX() + pipeSpace);
  _pipe3.SetY(randPos);

  _triggeredColliderId = 0;
  _newTriggeredColliderId = 0;
  this->_gameOverSprite.SetVisibility(false);
  this->_restartSprite.SetVisibility(false);
  _gameIsRunning = true;
}
