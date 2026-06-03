/* FILE NAME: t01fwin.c
 * PROGRAMMER: IK1
 * DATE: 02.06.2026*/
#include <windows.h>

#define WND_CLASS_NAME "something"

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  MSG msg;

    /* window class register */
  wc.style = 0;
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
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return 30;
}

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  SYSTEMTIME st;
  PAINTSTRUCT ps;
  HDC hDC;
  HPEN hpen;
  HPEN hpentwo;
  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 30, 50, NULL);
  case WM_TIMER:
    InvalidateRect(hWnd, NULL, TRUE);
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    
    SelectObject(hDC, GetStockObject(WHITE_BRUSH));
    Ellipse(hDC, 2000, 3000, 250, 350);
    
    SetDCBrushColor(hDC, RGB(0, 0, 255));
    SelectObject(hDC, GetStockObject(DC_BRUSH));
    Ellipse(hDC, 200, 200, 500, 500);
    
    hpen = CreatePen(PS_SOLID, 10, RGB(0, 0, 128));
    hpentwo = CreatePen(PS_SOLID, 10, RGB(0, 128, 0));
    SelectObject(hDC, hpen);
    LineTo(hDC, 500, 500);
    LineTo(hDC, 1000, 0);
    LineTo(hDC, 1500, 500);
    SelectObject(hDC, hpentwo);
    LineTo(hDC, 0, 500);
    DeleteObject(hpen);
    DeleteObject(hpentwo);

    EndPaint(hWnd, &ps);
    return 0;
  case WM_DESTROY:
    KillTimer(hWnd, 30);
    PostMessage(NULL, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}