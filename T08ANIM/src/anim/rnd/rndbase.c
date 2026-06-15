/* FILE NAME: rndbase.C
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: IK1
 * DATE: 09.06.2026
 */

#include "rnd.h"

VOID IK1_RndInit( HWND hWnd )
{
  HDC hDC;

  IK1_hRndWnd = hWnd;
  hDC = GetDC(hWnd);
  IK1_hRndDCFrame = CreateCompatibleDC(hDC);
  ReleaseDC(hWnd, hDC);
    
  IK1_hRndBmFrame = NULL;

  IK1_RndResize(47, 47);
  IK1_RndCamSet(VecSet1(8), VecSet1(0), VecSet(0, 1, 0));
}

VOID IK1_RndClose( VOID )
{
  DeleteObject(IK1_hRndBmFrame);
  DeleteDC(IK1_hRndDCFrame);
}

VOID IK1_RndResize( INT W, INT H )
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

VOID IK1_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, IK1_RndFrameW, IK1_RndFrameH,
    IK1_hRndDCFrame, 0, 0, SRCCOPY);
}


VOID IK1_RndStart( VOID )
{
  SelectObject(IK1_hRndDCFrame, GetStockObject(DC_BRUSH));
  SetDCBrushColor(IK1_hRndDCFrame, RGB(0, 0, 0));
  Rectangle(IK1_hRndDCFrame, 0, 0, IK1_RndFrameW, IK1_RndFrameH);
}

VOID IK1_RndEnd( VOID )
{

}

VOID IK1_RndProjSet( VOID )
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
  
VOID IK1_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  IK1_RndMatrView = MatrView(Loc, At, Up);
  IK1_RndMatrVP = MatrMulMatr(IK1_RndMatrView, IK1_RndMatrProj);
}