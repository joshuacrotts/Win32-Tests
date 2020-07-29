#include "../include/main.h"

struct RenderState renderState;
struct Input       input;

static void clearInput( struct Input *input );

/**
 *
 */
int WINAPI
WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int32_t nCmdShow ) {
  LPCSTR     windowTitle = "Windows 32 API Test";
  WNDCLASSEX wc;
  HWND       hwnd;
  MSG        msg;
  HDC        hdc;

  /* Make sure this is always true or the program will end immediately! */
  renderState.isRunning = true;

  /* First step is to initialize the window class. */
  initWindowClass( &wc, hInstance, windowTitle );

  /* Next step is to initialize the window (screen) itself. */
  hwnd = initWindow( &wc, windowTitle, WINDOW_WIDTH, WINDOW_HEIGHT );

  /* Now show and update the HWND. */
  ShowWindow( hwnd, nCmdShow );
  UpdateWindow( hwnd );
  hdc = GetDC( hwnd );

  /* Manage framerate. */
  float dt = 1 / 60.0f;
  float performanceFrequency;
  {
    LARGE_INTEGER perf;
    QueryPerformanceFrequency( &perf );
    performanceFrequency = perf.QuadPart;
  }
  LARGE_INTEGER frameBeginTime;
  QueryPerformanceCounter( &frameBeginTime );

  /* Init game objects. */
  initPlayer();

  /* Finally, the event loop. */
  while ( renderState.isRunning ) {
    clearInput( &input );
    initMessageHandler( msg, hwnd, &input );
    initUpdates( dt );
    initRenderer( hdc );

    LARGE_INTEGER frameEndTime;
    QueryPerformanceCounter( &frameEndTime );

    dt = ( float ) ( frameEndTime.QuadPart - frameBeginTime.QuadPart ) / performanceFrequency;
    frameBeginTime = frameEndTime;
  }

  return msg.wParam;
}

/**
 *
 */
void
initUpdates( float dt ) {
  clearScreen( 0xff8c00 );
  updatePlayer( dt );
  drawRect( player.x, player.y, 0.05f, 0.05f, 0xff0000 );
}

/**
 *
 */
void
initRenderer( HDC hdc ) {
  StretchDIBits( hdc, 0, 0, renderState.bufferWidth, renderState.bufferHeight, 0, 0,
                 renderState.bufferWidth, renderState.bufferHeight, renderState.bufferMemory,
                 &renderState.bitmapInfo, DIB_RGB_COLORS, SRCCOPY );
}

/**
 *
 */
void
initMessageHandler( MSG msg, HWND hwnd, struct Input *input ) {
  while ( PeekMessage( &msg, hwnd, 0, 0, PM_REMOVE ) ) {
    /* If the event is a key-related event, handle it here. */
    if ( msg.message == WM_KEYUP || msg.message == WM_KEYDOWN ) {
      DWORD vkCode                     = ( DWORD ) msg.wParam;
      input->buttons[vkCode].isDown    = msg.message == WM_KEYDOWN;
      input->buttons[vkCode].isChanged = true;
    }

    /* These must always be called throughout the loop to the callback Win32 function. */
    TranslateMessage( &msg );
    DispatchMessage( &msg );
  }
}

/**
 *
 */
static void
clearInput( struct Input *input ) {
  for ( int i = 0; i < BUTTON_COUNT; i++ ) {
    input->buttons[i].isChanged = false;
  }
}