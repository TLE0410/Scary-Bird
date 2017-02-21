#include "input.h"


void Input::BeginNewFrame()
{
  this->_pressedKeys.clear();
  this->_releasedKeys.clear();
}

void Input::KeyUpEvent(const SDL_Event& event)
{
  this->_pressedKeys[event.key.keysym.scancode] = false;
  this->_heldKeys[event.key.keysym.scancode] = false;
}

void Input::KeyDownEvent(const SDL_Event& event)
{
  this->_pressedKeys[event.key.keysym.scancode] = true;
  this->_heldKeys[event.key.keysym.scancode] = false;
}

bool Input::WasKeyPressed(SDL_Scancode key)
{
  return this->_pressedKeys[key];
}

bool Input::WasKeyReleased(SDL_Scancode key)
{
  return this->_releasedKeys[key];
}

bool Input::IsKeyHeld(SDL_Scancode key)
{
  return this->_heldKeys[key];
}
