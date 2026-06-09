#include "rnd.h"

VOID IK1_RndInit( HWND hWnd )
{
  IK1_hRndWnd = hWnd;                                    
  IK1_hRndDCFrame = CreateCompatibleDC(GetDC(hWnd));     
  IK1_hRndWnd = NULL;                                    

  IK1_RndCamSet(VecSet1(5), VecSet1(0), VecSet(0, 1, 0));
}

__inline VOID VG4_RndClose( VOID )
{
    ReleaseDC(IK1_hRndWnd, IK1_hRndDCFrame);  
}

__inline VOID IK1_RndResize( INT W, INT H )
{
  HDC hDC = GetDC(IK1_hRndWnd);
 
  if (IK1_hRndBmFrame != NULL)
    DeleteObject(IK1_hRndBmFrame);
  IK1_hRndBmFrame = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(IK1_hRndWnd, hDC);		
 
  SelectObject(IK1_hRndDCFrame, IK1_hRndBmFrame);
 
  IK1_RndFrameW = W;
  IK1_RndFrameH = H;
 

  IK1_RndProjSet();
}

__inline VOID IK1_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, IK1_RndFrameW, IK1_RndFrameH,
    IK1_hRndDCFrame, 0, 0, SRCCOPY);
}

__inline VOID IK1_RndStart( VOID )
{
  Rectangle(IK1_hRndDCFrame, 0, 0, IK1_RndFrameW, IK1_RndFrameH);
  SetDCBrushColor(IK1_hRndDCFrame, GetStockObject(DC_BRUSH));
  SelectObject(IK1_hRndDCFrame, RGB(0, 255, 0));
  Ellipse(IK1_hRndDCFrame, 0, 0, IK1_RndFrameW / 2, IK1_RndFrameH / 2);
} 

__inline VOID IK1_RndEnd( VOID )
{
}

__inline VOID IK1_RndProjSet( VOID )
{
  DBL rx, ry;
 
  rx = ry = IK1_RndProjSize;
  /* Correct aspect ratio */
  if (IK1_RndFrameW > IK1_RndFrameH)
    rx *= (DBL)IK1_RndFrameW / IK1_RndFrameH;
  else
    ry *= (DBL)IK1_RndFrameH / IK1_RndFrameW;
  IK1_RndMatrProj =
    MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
      IK1_RndProjDist, IK1_RndProjFarClip);
  IK1_RndMatrVP = MatrMulMatr(IK1_RndMatrView, IK1_RndMatrProj);
}
 
 
__inline VOID IK1_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  IK1_RndMatrView = MatrView(Loc, At, Up);
  IK1_RndMatrVP = MatrMulMatr(IK1_RndMatrView, IK1_RndMatrProj);
}
