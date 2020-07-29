#ifndef PLATFORM_COMMONS_H
#define PLATFORM_COMMONS_H

#include "commons.h"

#define BUTTON_COUNT 300

struct ButtonState {
  bool isDown;
  bool isChanged;
};

struct Input {
  struct ButtonState buttons[BUTTON_COUNT];
};

extern struct Input input;

extern bool isButtonDown( uint32_t keyCode );

extern bool isButtonPressed( uint32_t keyCode );

extern bool isButtonReleased( uint32_t keyCode );

#endif // PLATFORM_COMMONS_H