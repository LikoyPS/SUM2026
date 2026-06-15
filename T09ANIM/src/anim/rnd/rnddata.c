/* FILE NAME: rnddata.C
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: IK1
 * DATE: 09.06.2026
 */

#include <windows.h>
#include "def.h"

#include "rnd.h"
HWND IK1_hRndWnd;        /* Work window handle */
HDC IK1_hRndDC;                   /* Work window memory device context  */
INT IK1_RndFrameW, IK1_RndFrameH; /* Work window size */
HGLRC IK1_hRndGLRC;

DBL
  IK1_RndProjSize = 0.1,     /* Project plane fit square */
  IK1_RndProjDist = 0.1,     /* Distance to project plane from viewer (near) */
  IK1_RndProjFarClip = 300;  /* Distance to project far clip plane (far) */
 
MATR
  IK1_RndMatrView, /* View coordinate system matrix */
  IK1_RndMatrProj, /* Projection coordinate system matrix */
  IK1_RndMatrVP;   /* Stored (View * Proj) matrix */