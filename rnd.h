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

typedef struct tagvgIK1ERTEX
{
  VEC P;  /* Vertex position */
} ik1VERTEX;
 
typedef struct tagik1PRIM
{
  ik1VERTEX *V; /* Vertex attributes array */
  INT NumOfV;   /* Number of vertices */
 
  INT *I;       /* Index array (for trimesh – by 3 ones) */
  INT NumOfI;   /* Number of indices */
 
  MATR Trans;   /* Additional transformation matrix */
} ik1PRIM;

VOID IK1_RndPrimFree( ik1PRIM *Pr );
BOOL IK1_RndPrimCreate( ik1PRIM *Pr, INT NoofV, INT NoofI );
VOID IK1_RndPrimDraw( ik1PRIM *Pr, MATR World )

#endif