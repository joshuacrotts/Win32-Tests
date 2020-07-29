#ifndef PLAYER_H
#define PLAYER_H

#include "commons.h"

struct Player {
  float x;
  float y;

  float dx;
  float dy;

  float velocity;
  float deceleration;
};

extern struct Player player;
extern struct Input  input;

extern void initPlayer( void );

extern void updatePlayer( float dt );

#endif // PLAYER_H