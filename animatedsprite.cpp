#include "animatedsprite.h"
#include "graphics.h"

AnimatedSprite::AnimatedSprite() {}

AnimatedSprite::AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float timeToUpdate)
  : Sprite(graphics, filePath, sourceX, sourceY, width, height, posX, posY),
  _timeToUpdate(timeToUpdate),
  _currentAnimationOnce(false),
  _currentAnimation(""),
  _frameIndex(0),
  _visible(true)
{

}


void AnimatedSprite::PlayAnimation(std::string animation, bool once)
{
  this->_currentAnimationOnce = once;

  if (this->_currentAnimation != animation)
  {
    this->_currentAnimation = animation;
    this->_frameIndex = 0;
  }
}

void AnimatedSprite::Update(float DeltaTime)
{
  Sprite::Update();
  this->_timeElapsed += DeltaTime;

  if (this->_timeElapsed > this->_timeToUpdate)
  {
    this->_timeElapsed -= this->_timeToUpdate;
    if (this->_frameIndex < this->_animations[this->_currentAnimation].size() - 1)
    {
      this->_frameIndex++;
    }
    else
    {
      if (this->_currentAnimationOnce == true)
      {
        this->SetVisible(false);
      }
      this->_frameIndex = 0;
      this->AnimationDone(this->_currentAnimation);
    }
  }
}

void AnimatedSprite::Draw(Graphics &graphics, int x, int y)
{
  if (this->_visible)
  {
    SDL_Rect destinationRectangle;
    destinationRectangle.x = x + this->_offsets[this->_currentAnimation].x;
    destinationRectangle.y = y + this->_offsets[this->_currentAnimation].y;
    destinationRectangle.w = this->_sourceRect.w * globals::SPRITE_SCALE;
    destinationRectangle.h = this->_sourceRect.h * globals::SPRITE_SCALE;

    SDL_Rect sourceRectangle = this->_animations[this->_currentAnimation][this->_frameIndex];
    graphics.BlitSurface(this->_spriteSheet, &sourceRectangle, &destinationRectangle);
  }
}

void AnimatedSprite::AddAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset)
{
  std::vector<SDL_Rect> rectangles;
  for (int i = 0; i < frames; i++)
  {
    SDL_Rect newRect = { x + (i * width), y, width, height};
    rectangles.push_back(newRect);
  }

  this->_animations.insert( std::pair<std::string, std::vector<SDL_Rect> >(name, rectangles) );
  this->_offsets.insert( std::pair<std::string, Vector2>(name, offset) );
}

void AnimatedSprite::ResetAnimations()
{
  this->_animations.clear();
  this->_offsets.clear();
}

void AnimatedSprite::StopAnimation()
{
  this->_frameIndex = 0;
  this->AnimationDone(this->_currentAnimation);
}

void AnimatedSprite::SetVisible(bool visible)
{
  this->_visible = visible;
}
