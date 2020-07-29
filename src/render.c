#include "../include/render.h"

/**
 * Draws a rectangle in pixels on the screen.
 */
void
drawRectInPixels( int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color ) {
  Stds_ClampInt( &x0, 0, renderState.bufferWidth );
  Stds_ClampInt( &x1, 0, renderState.bufferWidth );
  Stds_ClampInt( &y0, 0, renderState.bufferHeight );
  Stds_ClampInt( &y1, 0, renderState.bufferHeight );
  
  for ( int y = y0; y < y1; y++ ) {
    uint32_t *pixel = ( uint32_t * ) renderState.bufferMemory + x0 + y * renderState.bufferWidth;
    for ( int x = x0; x < x1; x++ ) {
      *pixel++ = color;
    }
  }
}

/**
 * Draws a rectangle with the floating coordinate system to scale with a resizable window.
 * The center is located at (0, 0), and the corners of the screen are (-1, -1) for the top-left,
 * and (1, 1) for the bottom-right).
 */
void
drawRect( float x, float y, float halfSizeX, float halfSizeY, uint32_t color ) {
  x *= renderState.bufferHeight;
  y *= renderState.bufferHeight;
  halfSizeX *= renderState.bufferHeight;
  halfSizeY *= renderState.bufferHeight;

  x += renderState.bufferWidth / 2.f;
  y += renderState.bufferHeight / 2.f;

  /* Change to pixels. */
  int32_t x0 = ( int32_t )( x - halfSizeX );
  int32_t x1 = ( int32_t )( x + halfSizeX );
  int32_t y0 = ( int32_t )( y - halfSizeY );
  int32_t y1 = ( int32_t )( y + halfSizeY );

  drawRectInPixels( x0, y0, x1, y1, color );
}

/**
 * Clears the screen with a certain color to erase whatever was previously on the screen.
 */
void
clearScreen( uint32_t clearColor ) {
  uint32_t *pixel = ( uint32_t * ) renderState.bufferMemory;

  for ( uint32_t y = 0; y < renderState.bufferWidth; y++ ) {
    for ( uint32_t x = 0; x < renderState.bufferHeight; x++ ) {
      *pixel = clearColor;
      pixel++; /* Advance it to the next pointer. */
    }
  }
}