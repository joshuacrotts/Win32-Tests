#ifndef RENDER_H
#define RENDER_H

#include "commons.h"
#include "screen.h"

extern struct RenderState renderState;

extern void clearScreen( uint32_t color );

extern void drawRect( float x0, float y0, float x1, float y1, uint32_t color );

extern void drawRectInPixels( int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color );

#endif // RENDER_H