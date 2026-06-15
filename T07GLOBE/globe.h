#include <math.h>
#include <windows.h>
#include "MTH.h"

#ifndef __globe_h_
#define __globe_h_ 

#define GLB_GRID_W 31
#define GLB_GRID_H 18

typedef DOUBLE DBL;
 
VOID GLB_Draw( HDC hDC );
VOID GLB_Resize( INT Ws, INT Hs );
VOID GLB_Init( DBL R );

static VEC GLB_GeomN[GLB_GRID_H][GLB_GRID_W];

#endif