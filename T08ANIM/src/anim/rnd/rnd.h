/* FILE NAME: rnd.h
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: IK1
 * DATE: 09.06.2026
 */

#ifndef __rnd_h_
#define __rnd_h_

#include "def.h"

extern HWND IK1_hRndWnd;        /* Work window handle */
extern HDC IK1_hRndDCFrame;     /* Work window memory device context  */
extern HBITMAP IK1_hRndBmFrame; /* Work window background bitmap handle */
extern INT IK1_RndFrameW, IK1_RndFrameH; /* Work window size */

extern DBL
  IK1_RndProjSize,     /* Project plane fit square */
  IK1_RndProjDist,     /* Distance to project plane from viewer (near) */
  IK1_RndProjFarClip;  /* Distance to project far clip plane (far) */
 
extern MATR
  IK1_RndMatrView, /* View coordinate system matrix */
  IK1_RndMatrProj, /* Projection coordinate system matrix */
  IK1_RndMatrVP;   /* Stored (View * Proj) matrix */


VOID IK1_RndInit( HWND hWnd );
VOID IK1_RndClose( VOID );
VOID IK1_RndResize( INT W, INT H );
VOID IK1_RndCopyFrame( HDC hDC );
VOID IK1_RndStart( VOID );
VOID IK1_RndEnd( VOID );
VOID IK1_RndProjSet( VOID );
VOID IK1_RndCamSet( VEC Loc, VEC At, VEC Up );

/*** Primitive handle ***/
typedef struct tagIK1VERTEX
{
  VEC P;  /* Vertex position */
} IK1VERTEX;

typedef struct tagik1PRIM
{
  IK1VERTEX *V; /* Vertex attributes array */
  INT NumOfV;   /* Number of vertices */
 
  INT *I;       /* Index array (for trimesh – by 3 ones) */
  INT NumOfI;   /* Number of indices */
 
  MATR Trans;   /* Additional transformation matrix */
} ik1PRIM;

BOOL IK1_RndPrimCreate( ik1PRIM *Pr, INT NoofV, INT NoofI );
VOID IK1_RndPrimFree( ik1PRIM *Pr );
VOID IK1_RndPrimDraw( ik1PRIM *Pr, MATR World );
BOOL IK1_RndPrimLoad( ik1PRIM *Pr, CHAR *FileName );
BOOL IK1_RndPrimCreateSphere( ik1PRIM *Pr, DBL R, INT W, INT H );



#include "def.h"

#endif /* __rnd_h_ */