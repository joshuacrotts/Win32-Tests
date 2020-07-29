#include "../include/player.h"

struct Player player;

static void checkInputs( float dt );
static void playerDecelerate( void );

void
initPlayer( void ) {
  player.x            = 0.f;
  player.y            = 0.f;
  player.velocity     = 1.0f;
  player.deceleration = 0.95f;
}

/**
 *
 */
void
updatePlayer( float dt ) {
  checkInputs( dt );

  player.x += player.dx;
  player.y += player.dy;

  playerDecelerate();
}

/**
 *
 */
static void
playerDecelerate( void ) {
  player.dx *= player.deceleration;
  player.dy *= player.deceleration;
}

/**
 *
 */
static void
checkInputs( float dt ) {
  if ( isButtonDown( VK_RIGHT ) ) {
    player.dx = player.velocity * dt;
  }
  if ( isButtonDown( VK_LEFT ) ) {
    player.dx = -player.velocity * dt;
  }
  if ( isButtonDown( VK_UP ) ) {
    player.dy = player.velocity * dt;
  }
  if ( isButtonDown( VK_DOWN ) ) {
    player.dy = -player.velocity * dt;
  }
}