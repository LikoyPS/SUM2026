#include <windows.h>
#include "globe.h"
#include <time.h>

#define pi 3.14159265358979323846

static VEC GLB_Geom[GLB_GRID_H][GLB_GRID_W];
static INT GLB_Ws, GLB_Hs, GLB_Ws, GLB_Hs;


VOID GLB_Draw( HDC hDC )
{
  INT i, j, s = 2;
  static POINT pnts[GLB_GRID_H][GLB_GRID_W];

  SetDCBrushColor(hDC, RGB(255, 0, 0));

  for (i = 0; i < GLB_GRID_H; i++)
    for (j = 0; j < GLB_GRID_W; j++)
    {
      pnts[i][j].x = (INT)(GLB_Ws / 2 + GLB_Geom[i][j].X); /*  * GLB_Ws / GLB_Wp */
      pnts[i][j].y = (INT)(GLB_Hs / 2 - GLB_Geom[i][j].Y); /* * GLB_Hs / GLB_Hp */
    }
  for (i = 0; i < GLB_GRID_H; i++)
  {
    MoveToEx(hDC, pnts[i][0].x, pnts[i][0].y, NULL);
    for (j = 0; j < GLB_GRID_W; j++)
    {
      LineTo(hDC, pnts[i][j].x, pnts[i][j].y);
    }
  }
  for (j = 0; j < GLB_GRID_W; j++)  
  {  
    MoveToEx(hDC, pnts[0][j].x, pnts[0][j].y, NULL);
    for (i = 0; i < GLB_GRID_H; i++)
      {
         LineTo(hDC, pnts[i][j].x, pnts[i][j].y);
      }
  }

}

VOID GLB_Resize( INT Ws, INT Hs )
{
  DBL ProjSize = 1, Wp, Hp;
  GLB_Ws = Ws;
  GLB_Hs = Hs;
  if (Ws >= Hs)
  {  
    Wp = ProjSize * Ws / Hs;
    Hp = ProjSize;
  }
  else
  {
    Wp = ProjSize;
    Hp = ProjSize * Hs / Ws;
  }
}

/* Rotate vector around Z axis function.
 * ARGUMENTS:
 *   - vector coordinates:
 *       VEC P;
 *   - rotation angle in degrees:
 *       DBL Angle;
 * RETURNS:
 *   (VEC) rotated vector.
 */
VEC RotateZ( VEC P, DBL Angle )
{
  VEC NewP;
  DBL a = Angle * pi / 180, si = sin(a), co = cos(a);
 
  NewP.X = P.X * co - P.Y * si;
  NewP.Y = P.X * si + P.Y * co;
  NewP.Z = P.Z;
  return NewP;
}

/* Rotate vector around X axis function.
 * ARGUMENTS:
 *   - vector coordinates:
 *       VEC P;
 *   - rotation angle in degrees:
 *       DBL Angle;
 * RETURNS:
 *   (VEC) rotated vector.
 */
VEC RotateX( VEC P, DBL Angle )
{
  VEC NewP;
  DBL a = Angle * pi / 180, si = sin(a), co = cos(a);
 
  NewP.X = P.X;
  NewP.Y = P.Y * co - P.Z * si;
  NewP.Z = P.Y * si + P.Z * co;
  return NewP;
} /* End of 'RotateX' function */
 
/* Rotate vector around Y axis function.
 * ARGUMENTS:
 *   - vector coordinates:
 *       VEC P;
 *   - rotation angle in degrees:
 *       DBL Angle;
 * RETURNS:
 *   (VEC) rotated vector.
 */
VEC RotateY( VEC P, DBL Angle )
{
  VEC NewP;
  DBL a = Angle * pi / 180, si = sin(a), co = cos(a);
 
  NewP.X = P.Z * si + P.X * co;
  NewP.Y = P.Y;
  NewP.Z = P.Z * co - P.X * si;
  return NewP;
} /* End of 'RotateY' function */


VOID GLB_Init ( DBL R )
{
  DBL t;
  INT i, j;

  for (i = 0; i < GLB_GRID_H; i++)  
  {
    DBL theta = i * pi / (GLB_GRID_H - 1);
    for (j = 0; j < GLB_GRID_W; j++)
    {
      DBL phi = j * 2 * pi / (GLB_GRID_W - 1);
      t = clock() / (DBL)CLOCKS_PER_SEC;
      GLB_Geom[i][j].X = R * sin(theta) * sin(phi);
      GLB_Geom[i][j].Y = R * cos(theta);
      GLB_Geom[i][j].Z = R * sin(theta) * cos(phi);
      GLB_Geom[i][j] = RotateZ( GLB_Geom[i][j], 90 * t);
      GLB_Geom[i][j] = RotateX( GLB_Geom[i][j], 90 * t);
      GLB_Geom[i][j] = RotateY( GLB_Geom[i][j], 90 * t);
    }
  }
}

