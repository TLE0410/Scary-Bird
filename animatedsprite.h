#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <map>
#include <vector>
#include <string>

#include "sprite.h"
#include "globals.h"

class AnimatedSprite : public Sprite
{
public:
  AnimatedSprite();
  AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float timeToUpdate);

  void PlayAnimation(std::string animation, bool once = false);
  void Update(float DeltaTime);
  void Draw(Graphics &graphics, int x, int y);

protected:
  double _timeToUpdate;
  bool _currentAnimationOnce;
  std::string _currentAnimation;

  void AddAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);
  void ResetAnimations();
  void StopAnimation();
  void SetVisible(bool visible);

  virtual void AnimationDone(std::string currentAnimation) = 0;

	virtual void SetupAnimations() = 0;

private:
  std::map<std::string, std::vector<SDL_Rect> > _animations;
  std::map<std::string, Vector2> _offsets;

  unsigned int _frameIndex;
  double _timeElapsed;
  bool _visible;
};

#endif
