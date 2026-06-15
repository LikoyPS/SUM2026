/* FILE NAME: main.C
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: IK1
 * DATE: 10.06.2026
 */

#include "units/units.h"

/* Window class name */
#define WND_CLASS_NAME "210 IK1 Window Class"

/* Forward declaration */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

/* Main startup program function.
 * ARGUMENTS:
 *   - application instance handle:
 *       HINSTANCE hInstance;
 *   - previouse application instance handle
 *     (not used, alway NULL):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - command line window show parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) system error level value.
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                    CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  MSG msg;
  HWND hWnd;

  SetDbgMemHooks();

  /* Window class register */
  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszMenuName = NULL;
  wc.lpszClassName = WND_CLASS_NAME;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error", "ERROR", MB_ICONERROR | MB_OK);
    return 0;
  }
  
  /* Create window */
  hWnd = CreateWindowA(WND_CLASS_NAME, "anim", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    100, 100, 700, 700, NULL, NULL, hInstance, NULL);

  /*** Units creation ***/
  IK1_AnimUnitAdd(IK1_UniteCreateBall());

  /* Message loop */
  while (TRUE)
  if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
  {
    if (msg.message == WM_QUIT)
      break;
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  else
    SendMessage(hWnd, WM_TIMER, 47, 0);
  return msg.wParam;
} /* End of 'WinMain' function */

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  HDC hDC;
  PAINTSTRUCT ps;
  
  switch (Msg)
  {  
  case WM_CREATE:
    IK1_AnimInit(hWnd);
    SetTimer(hWnd, 3, 8, NULL);
    return 0;

  case WM_SIZE:
    IK1_AnimResize(LOWORD(lParam), HIWORD(lParam));
    SendMessage(hWnd, WM_TIMER, 47, 0);
    return 0;

  case WM_TIMER:
    IK1_AnimRender();

    hDC = GetDC(hWnd);
    IK1_AnimCopyFrame(hDC);
    ReleaseDC(hWnd, hDC);
    return 0;

  case WM_ERASEBKGND:
    return 1;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    IK1_AnimCopyFrame(hDC);
    EndPaint(hWnd, &ps);
    return 0;

  case WM_DESTROY:
    IK1_AnimClose();
    KillTimer(hWnd, 30);
    PostMessage(NULL, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}/* End of 'MyWindowFunc' function */
    
/* END OF 'main.c' FILE */