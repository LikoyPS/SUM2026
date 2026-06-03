 /* FILE NAME: t03clock
 fwin.c
 * PROGRAMMER: IK1
 * DATE: 03.06.2026*/
#include <windows.h>
#include <math.h>

#define WND_CLASS_NAME "something"

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  MSG msg;

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
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return 30;
}

void arrow(HWND hWnd, HDC hDC, INT XC, INT YC)
{
  POINT pt;
  static INT W, H;
  INT i;
  FLOAT len, co, si;
  POINT pnts[3] = {{40, 50}, {10, 10}, {70, 30}};
  POINT pnts_res[sizeof(pnts)/sizeof(pnts[0])];
  
  GetCursorPos(&pt);
  /*MoveToEx(hDC, XC, YC, NULL);*/
  ScreenToClient(hWnd, &pt);
  len = _hypot((pt.x - XC), (pt.y - YC));   /*len = sqrt((pt.x - XC) * (pt.x - XC) + (pt.y - YC) * (pt.y - YC)); */
  si = (pt.x - XC) / len;  
  co = (pt.y - YC) / len;
  for (i = 0; i < sizeof(pnts)/sizeof(pnts[0]); i++)  
  {  
    pnts_res[i].x = (pnts[i].x) * co + (pnts[i].y) * si + XC;
    pnts_res[i].y = (pnts[i].y) * co - (pnts[i].x) * si + YC;
  }
    /*LineTo(hDC, pt.x, pt.y);*/
  Polygon(hDC, pnts_res, sizeof(pnts)/sizeof(pnts[0]));
  /*MoveTo(hDC, )*/
}
                    
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  static HBITMAP hBm;
  static HBITMAP hBmClock;
  static HDC hMemDC;
  static HDC hMemDCClock;
  static BITMAP bm;
  PAINTSTRUCT ps;
  SYSTEMTIME st;
  HDC hDC;
  static INT W, H;
  INT i;
                                  
  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 30, 1, NULL);
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    hMemDCClock = CreateCompatibleDC(hMemDC);
    hBmClock = LoadImage(NULL, "Clock.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    ReleaseDC(hWnd, hDC); 
    hBm = NULL;
    return 0;
  case WM_ERASEBKGND:
    return 1;
  /*case WM_MOUSEMOVE:
    InvalidateRect(hWnd, NULL, TRUE);*/
    return 0;
  case WM_SIZE:
    W = LOWORD(lParam);
    H = HIWORD(lParam);
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, W, H);
    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDC, hBm);
    
    SendMessage(hWnd, WM_TIMER, 0, 0);  

    return 0;
  case WM_TIMER:   
      /*рисуем*/
    SelectObject(hMemDCClock, hBmClock);
    GetObject(hBmClock, sizeof(BITMAP), &bm);
    SetDCBrushColor(hMemDC, GetDCBrushColor(WHITE_BRUSH));
    Rectangle(hMemDC, 0, 0, W, H);
    hDC = GetDC(hWnd);
    BitBlt(hDC, (W - bm.bmWidth) / 2, (H - bm.bmWidth) / 2, bm.bmWidth, bm.bmHeight, hMemDCClock, 0, 0, SRCCOPY);
    ReleaseDC(hWnd, hDC);                  
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hMemDC, (W - bm.bmWidth) / 2, (H - bm.bmHeight) / 2, W, H, hMemDCClock, 0, 0, SRCCOPY);
    //StretchBlt(hMemDC, 0, 0, W, H, hMemDCClock, 0, 0, (W - bm.bmWidth) / 2, (H - bm.bmHeight) / 2, SRCCOPY);  
    StretchBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, (W - bm.bmWidth) / 2, (H - bm.bmHeight) / 2, SRCCOPY);  
    EndPaint(hWnd, &ps);
    return 0;
  case WM_DESTROY:
    if (hBm != NULL)
      DeleteObject(hBm);
    DeleteDC(hMemDC);
    KillTimer(hWnd, 30);
    PostMessage(NULL, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}