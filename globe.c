#include <windows.h>
#include "globe.h"
#include <time.h>

#define pi 3.14159265358979323846

static VEC GLB_Geom[GLB_GRID_H][GLB_GRID_W];
static INT GLB_Ws, GLB_Hs;
static DBL GLB_ProjSize = 1, GLB_Wp, GLB_Hp, GLB_ProjDist = 1;


VOID GLB_Draw( HDC hDC )
{
  DBL xp, yp;
  INT i, j, s = 2;
  static POINT pnts[GLB_GRID_H][GLB_GRID_W];
  VEC P;
  SetDCBrushColor(hDC, RGB(255, 0, 0));

  for (i = 0; i < GLB_GRID_H; i++)
    for (j = 0; j < GLB_GRID_W; j++)
    {
      P = GLB_Geom[i][j];
      
      P.Z -= 1;
      
      xp = P.X * GLB_ProjDist / (-P.Z);
      yp = P.Y * GLB_ProjDist / (-P.Z);
      
      pnts[i][j].x = (INT)(xp * GLB_Ws / GLB_Wp + GLB_Ws / 2); /*  * GLB_Ws / GLB_Wp */
      pnts[i][j].y = (INT)(-yp * GLB_Hs / GLB_Hp + GLB_Hs / 2); /* * GLB_Hs / GLB_Hp */
    }
  
    /* paraleles and meridianes */
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
  DBL Wp, Hp;
  GLB_Ws = Ws;
  GLB_Hs = Hs;
  if (GLB_Ws >= GLB_Hs)
  {  
    GLB_Wp = GLB_ProjSize * GLB_Ws / GLB_Hs;
    GLB_Hp = GLB_ProjSize;
  }
  else
  {
    Wp = GLB_ProjSize;
    Hp = GLB_ProjSize * Hs / Ws;
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
      /*GLB_Geom[i][j] = RotateZ( GLB_Geom[i][j], 90 * t);
      GLB_Geom[i][j] = RotateX( GLB_Geom[i][j], 90 * t);
      GLB_Geom[i][j] = RotateY( GLB_Geom[i][j], 90 * t);*/
    }
  }
}
