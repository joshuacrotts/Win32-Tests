#ifndef MAIN_H
#define MAIN_H

#include "commons.h"
#include "player.h"
#include "render.h"
#include "screen.h"

#define WINDOW_WIDTH  1280
#define WINDOW_HEIGHT 720

extern struct RenderState renderState;
extern struct Player      player;
extern struct Input       input;

extern void initMessageHandler( MSG msg, HWND hwnd, struct Input *input );

extern void initUpdates( float dt );

extern void initRenderer( HDC hdc );

#endif // MAIN_H
