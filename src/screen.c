#include "../include/screen.h"

/**
 *
 */
LRESULT CALLBACK
WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
  switch ( msg ) {
  case WM_CLOSE: {
    renderState.isRunning = false;
    DestroyWindow( hwnd );
    break;
  }
  case WM_DESTROY: {
    renderState.isRunning = false;
    PostQuitMessage( 0 );
    break;
  }
  case WM_SIZE: {
    RECT rect;
    GetClientRect( hwnd, &rect );
    renderState.bufferWidth  = rect.right - rect.left;
    renderState.bufferHeight = rect.bottom - rect.top;
    int32_t buffer_size = renderState.bufferWidth * renderState.bufferHeight * sizeof( uint32_t );

    /* If we already resized it previously, free the preexisting memory */
    if ( renderState.bufferMemory ) {
      VirtualFree( renderState.bufferMemory, 0, MEM_RELEASE );
    }

    /* Now reallocate the new memory for the resized window. */
    renderState.bufferMemory =
        VirtualAlloc( 0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );

    /* Create the BITMAPINFO struct. */
    renderState.bitmapInfo.bmiHeader.biSize        = sizeof( renderState.bitmapInfo.bmiHeader );
    renderState.bitmapInfo.bmiHeader.biWidth       = renderState.bufferWidth;
    renderState.bitmapInfo.bmiHeader.biHeight      = renderState.bufferHeight;
    renderState.bitmapInfo.bmiHeader.biPlanes      = 1;
    renderState.bitmapInfo.bmiHeader.biBitCount    = 32;
    renderState.bitmapInfo.bmiHeader.biCompression = BI_RGB;
    break;
  }
  default: {
    return DefWindowProc( hwnd, msg, wParam, lParam );
    break;
  }
  }
  return 0;
}

/**
 *
 */
void
initWindowClass( WNDCLASSEX *wc, const HINSTANCE hInstance, LPCSTR windowClassName ) {
  wc->cbSize        = sizeof( WNDCLASSEX );
  wc->style         = 0;
  wc->lpfnWndProc   = WndProc;   /* Callback function for events. */
  wc->cbClsExtra    = 0;         /* Extra data allocated for this class. */
  wc->cbWndExtra    = 0;         /* Extra data allocated for memory per window. */
  wc->hInstance     = hInstance; /* HINSTANCE from main function. */
  wc->hIcon         = LoadIcon( NULL, IDI_APPLICATION ); /* Alt-tab icon. */
  wc->hCursor       = LoadCursor( NULL, IDC_ARROW );
  wc->hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 ); /* Sets color of window. */
  wc->lpszMenuName  = NULL;
  wc->lpszClassName = windowClassName;
  wc->hIconSm       = LoadIcon( NULL, IDI_APPLICATION ); /* Small icon. */

  if ( !RegisterClassEx( wc ) ) {
    MessageBox( NULL, "Window class registration failed!", "Error!", MB_ICONEXCLAMATION | MB_OK );
    exit( EXIT_FAILURE );
  }
}

/**
 * Creates the default WIN32 window to use. The window is placed on the center
 * of the screen.
 *
 * @param const WNDCLASSEX * pointer to the window class used.
 * @param const LPCSTR window title string.
 * @param const uint32_t width of window.
 * @param const uint32_t height of window.
 *
 * @param pointer to HWND.
 */
HWND
initWindow( const WNDCLASSEX *wc, const LPCSTR windowTitle, const uint32_t width,
            const uint32_t height ) {

  /* Compute the center coordinates of the screen by subtracting/dividing an offset
     based on what the user wants the window size to be. */
  const uint32_t SCREEN_CENTER_X = ( GetSystemMetrics( SM_CXSCREEN ) - width ) >> 1;
  const uint32_t SCREEN_CENTER_Y = ( GetSystemMetrics( SM_CYSCREEN ) - height ) >> 1;

  HWND hwnd = CreateWindowEx( WS_EX_CLIENTEDGE, wc->lpszClassName, windowTitle, WS_OVERLAPPEDWINDOW,
                              SCREEN_CENTER_X, SCREEN_CENTER_Y, width, height, NULL, NULL,
                              wc->hInstance, NULL );

  /* Check to make sure the HWND pointer is not null. */
  if ( hwnd == NULL ) {
    MessageBox( NULL, "Window creation failed!", "Error!", MB_ICONEXCLAMATION | MB_OK );
    exit( EXIT_FAILURE );
  }

  return hwnd;
}

