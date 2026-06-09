#include <windows.h>
#include "globe.h"
#include <time.h>
#include "MTH.h"

#define GLB_MIN(A, B) ((A) < (B) ? (A) : (B))
#define GLB_MAX(A, B) ((A) > (B) ? (A) : (B))

static VEC GLB_Geom[GLB_GRID_H][GLB_GRID_W];
static INT GLB_Ws, GLB_Hs;
static DBL GLB_ProjSize = 1, GLB_Wp, GLB_Hp, GLB_ProjDist = 1;

/* color conver func */
COLORREF ColorTo255( VEC Color )
{
  INT R = (INT)(Color.X * 255), G = (INT)(Color.Y * 255), B = (INT)(Color.Z * 255);
    /*if (R < 0)
      R = 0;
    else
      if (R > 255)
        R = 255;*/

  R = GLB_MIN(255, (GLB_MAX(0, R)));
  G = GLB_MIN(255, (GLB_MAX(0, G)));
  B = GLB_MIN(255, (GLB_MAX(0, B)));
  return RGB(R, G, B);
} 

VOID GLB_Draw( HDC hDC )
{
  DBL t;
  DBL xp, yp, len;
  INT i, j, s = 2;
  static POINT pnts[GLB_GRID_H][GLB_GRID_W];
  POINT pts[4];
  VEC P;
  VEC L;
  MATR m;

  
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
    
    
  SetDCPenColor(hDC, RGB(255, 255, 255));
  SelectObject(hDC, GetStockObject(DC_PEN));
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
  
  L.X = 1;
  L.Y = 1;
  L.Z = 1;
  len = sqrt(L.X * L.X + L.Y * L.Y + L.Z * L.Z);
  L.X /= len;
  L.Y /= len;
  L.Z /= len;

  t = clock() / (DBL)CLOCKS_PER_SEC;
  m = MatrMulMatr3(MatrRotateX(t * 60), MatrRotateY(t * 10), MatrRotateZ(t * 30));

  for (i = 0; i < GLB_GRID_H - 1; i++)
  {
    for (j = 0; j < GLB_GRID_W - 1; j++)
    {
      VEC N = GLB_GeomN[i][j];
      DBL nl;
      VEC C = {0.1, 0.1, 0.90};
      
      N = VecMulMatr(N, m);
      nl = N.X * L.X + N.Y * L.Y + N.Z * L.Z;
      C.X *= nl;
      C.Y *= nl;
      C.Z *= nl;


      SetDCPenColor(hDC, RGB(255, 255, 255));
      SetDCBrushColor(hDC, RGB(0, 20, 150));
      SelectObject(hDC, GetStockObject(DC_PEN));
      SelectObject(hDC, GetStockObject(DC_BRUSH));
  
      pts[0] = pnts[i][j];
      pts[1] = pnts[i][j + 1];
      pts[2] = pnts[i + 1][j + 1];
      pts[3] = pnts[i + 1][j];
      
      SetDCBrushColor(hDC, ColorTo255(C));
      SelectObject(hDC, GetStockObject(DC_BRUSH));
      Polygon(hDC, pts, 4);
  
      SetDCBrushColor(hDC, RGB(0, 0, 0));
      SelectObject(hDC, GetStockObject(DC_BRUSH));
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




VOID GLB_Init( DBL R )
{
  DBL t;
  INT i, j;
  MATR m;

  t = clock() / (DBL)CLOCKS_PER_SEC;
  m = MatrMulMatr3(MatrRotateX(t * 60), MatrRotateY(t * 10), MatrRotateZ(t * 30));

  for (i = 0; i < GLB_GRID_H; i++)  
  {
    DBL theta = i * pi / (GLB_GRID_H - 1);
    for (j = 0; j < GLB_GRID_W; j++)
    {
      DBL phi = j * 2 * pi / (GLB_GRID_W - 1);

      GLB_GeomN[i][j].X = sin(theta) * sin(phi);
      GLB_GeomN[i][j].Y = cos(theta);
      GLB_GeomN[i][j].Z = sin(theta) * cos(phi);
      
      GLB_Geom[i][j].X = R * sin(theta) * sin(phi);
      GLB_Geom[i][j].Y = R * cos(theta);
      GLB_Geom[i][j].Z = R * sin(theta) * cos(phi);
      
      GLB_Geom[i][j] = VecMulMatr(GLB_Geom[i][j], m);
    }
  }
}

