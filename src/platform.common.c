#include "../include/platform_commons.h"

/**
 * 
 */
inline bool
isButtonDown( uint32_t keyCode ) {
  return input.buttons[keyCode].isDown;
}

/**
 * 
 */
inline bool
isButtonPressed( uint32_t keyCode ) {
  return isButtonDown( keyCode ) && input.buttons[keyCode].isChanged;
}

/**
 * 
 */
inline bool
isButtonReleased( uint32_t keyCode ) {
  return !isButtonDown( keyCode ) && input.buttons[keyCode].isChanged;
}