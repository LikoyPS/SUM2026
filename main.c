 /* t07globe   IK1   06.06.2026*/
#include "def.h"

#define WND_CLASS_NAME "something"
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

/*VOID FlipFullScreen( VOID )
{
  static BOOl IsFullScreen = FALSE;
  static RECT SaveRect;

  if (!IsFullScreen)
  {
    HMONITOR hmon;
    HMONITOTINFOEX moninfo;
    RECT rc;

    GetWindowRect( hWnd, &SaveRect );

    hmon = MonitorFromWindow(hWnd, MONITOR);

    moninfo.cbSize = sizeof(moninfo);

    GetMonitorInfo( hmon, (MONITORINFO *)&moninfo);

    rc.left = 0;
    rc.top = 0;
  }
}
*/
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  SetDbgMemHooks();

    /* window class register */
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
  wc.hInstance = hInstance;
  wc.lpszMenuName = NULL;
  wc.lpszClassName = WND_CLASS_NAME;
  wc.lpfnWndProc = MyWindowFunc;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error", "ERROR", MB_ICONERROR);
    return 0;
  }
   /* create window */ 
   CreateWindowA(WND_CLASS_NAME, "text", WS_CLIPCHILDREN|WS_OVERLAPPEDWINDOW|WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL); 
   /* main program loop  */
  while (TRUE)
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
    SendMessage(hWnd,WM_TIMER, 30, 0); 
  return 30;
}


LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  static HBITMAP hBm;
  static HDC hMemDC;
  static BITMAP bm;
  PAINTSTRUCT ps;
  HDC hDC;
  static INT W, H;
                                  
  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 30, 1, NULL);
    return 0;

  case WM_ERASEBKGND:
    return 1;

  case WM_SIZE:
    W = LOWORD(lParam);
    H = HIWORD(lParam);
    
    SendMessage(hWnd, WM_TIMER, 0, 0);  

    return 0;
  case WM_TIMER:   
    return 0;
  
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    EndPaint(hWnd, &ps);
    return 0;
  
  case WM_DESTROY:
    KillTimer(hWnd, 30);
    PostMessage(NULL, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}
