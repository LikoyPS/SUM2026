/* FILE NAME: rnd.h
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: IK1
 * DATE: 09.06.2026
 */

#ifndef __rnd_h_
#define __rnd_h_

#include "res/rndres.h"


extern HWND IK1_hRndWnd;        /* Work window handle */
extern HDC IK1_hRndDC;     /* Work window memory device context  */
extern INT IK1_RndFrameW, IK1_RndFrameH; /* Work window size */

extern DBL
  IK1_RndProjSize,     /* Project plane fit square */
  IK1_RndProjDist,     /* Distance to project plane from viewer (near) */
  IK1_RndProjFarClip;  /* Distance to project far clip plane (far) */
 
extern MATR
  IK1_RndMatrView, /* View coordinate system matrix */
  IK1_RndMatrProj, /* Projection coordinate system matrix */
  IK1_RndMatrVP;   /* Stored (View * Proj) matrix */

extern HGLRC IK1_hRndGLRC;


/* structure of vertex */
typedef struct tagik1VERTEX
 {
  VEC P;   /* Position */
  VEC2 T;  /* Texture Coordinate */
  VEC N;   /* norval */
  VEC4 C;  /* color (r,g,b,a) */
} ik1VERTEX;

/* Primitive type */
typedef enum tagik1PRIM_TYPE
{
  IK1_RND_PRIM_POINTS,   /* Array of points  – GL_POINTS */
  IK1_RND_PRIM_LINES,    /* Line segments (by 2 points) – GL_LINES */
  IK1_RND_PRIM_TRIMESH,  /* Triangle mesh - array of triangles – GL_TRIANGLES */
} ik1PRIM_TYPE;
 
 
/* Primitive representation type */
typedef struct tagik1PRIM
{
  ik1PRIM_TYPE Type; /* Primitive type */
 
  INT
    VA,              /* Vertex array Id */
    VBuf,            /* Vertex buffer Id */
    IBuf;            /* Index buffer Id (if 0 - use only vertex buffer) */
 
  INT NumOfElements; /* Number of indices/vecrtices */
 
  VEC MinBB, MaxBB;  /* Bound box */
 
  MATR Trans;        /* Additional transformation matrix */
} ik1PRIM;

VOID IK1_RndPrimCreate( ik1PRIM *Pr, ik1PRIM_TYPE Type, ik1VERTEX *V, INT NoofV, INT *Ind, INT NoofI );
VOID IK1_RndPrimFree( ik1PRIM *Pr );
VOID IK1_RndPrimDraw( ik1PRIM *Pr, MATR World );
BOOL IK1_RndPrimLoad( ik1PRIM *Pr, CHAR *FileName );
BOOL IK1_RndPrimCreateSphere( ik1PRIM *Pr, DBL R, INT W, INT H );

VOID IK1_RndInit( HWND hWnd );
VOID IK1_RndClose( VOID );
VOID IK1_RndResize( INT W, INT H );
VOID IK1_RndCopyFrame( VOID );
VOID IK1_RndStart( VOID );
VOID IK1_RndEnd( VOID );
VOID IK1_RndProjSet( VOID );
VOID IK1_RndCamSet( VEC Loc, VEC At, VEC Up );
VOID IK1_RndPrimTriMeshAutoNormals( ik1VERTEX *V, INT NumOfV, INT *Ind, INT NumOfI );


#include "def.h"

#endif /* __rnd_h_ */