#ifndef __mth_h_
#include "def.h"

extern HWND IK1_hRndWnd;                  
extern HDC IK1_hRndDCFrame;               
extern HBITMAP IK1_hRndBmFrame;           
extern INT IK1_RndFrameW, IK1_RndFrameH;  

extern DBL
  IK1_RndProjSize,     
  IK1_RndProjDist,     
  IK1_RndProjFarClip;  
 
extern MATR
  IK1_RndMatrView, 
  IK1_RndMatrProj, 
  IK1_RndMatrVP;   

/* init functions */
VOID IK1_RndCopyFrame( HDC hDC );
VOID IK1_RndStart( VOID );
VOID IK1_RndEnd( VOID );
VOID IK1_RndProjSet( VOID );
VOID IK1_RndCamSet( VEC Loc, VEC At, VEC Up );

#endif
