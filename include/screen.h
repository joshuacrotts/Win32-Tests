#ifndef SCREEN_H
#define SCREEN_H

#include "commons.h"

struct RenderState {
  bool       isRunning;
  void *     bufferMemory;
  int32_t    bufferWidth;
  int32_t    bufferHeight;
  BITMAPINFO bitmapInfo;
};

extern struct RenderState renderState;

extern void initWindowClass( WNDCLASSEX *wc, const HINSTANCE hInstance, LPCSTR windowClassName );

extern HWND initWindow( const WNDCLASSEX *wc, LPCSTR windowTitle, uint32_t width, uint32_t height );

extern void clearScreen( uint32_t clearColor );

#endif // SCREEN_H
