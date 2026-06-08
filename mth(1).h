/**/
#ifndef __mth_h_
#define __mth_h_

#include <math.h>
#define pi 3.14159265358979323846

#define D2R(A) ((A) * (pi / 180.0))
#define Degree2Radian(a) D2R(a)

typedef double DBL;
typedef float FLT;

typedef struct tagVEC
{
  DBL X, Y, Z;
} VEC;

typedef struct tagMATR
{
  DBL A[4][4];
} MATR;

static MATR UnitMatrix =
{
  {                
    {1, 0, 0, 0},  
    {0, 1, 0, 0},  
    {0, 0, 1, 0},  
    {0, 0, 0, 1},   
  } 
};

/* функции реализации */
__inline VEC VecSet( DBL X, DBL Y, DBL Z )
{
  VEC v;
 
  v.X = X;
  v.Y = Y;
  v.Z = Z;
  return v;
} /* End of 'VecSet' function */

__inline VEC VecSet1( DBL A )
{
  VEC r = {A, A, A};
 
  return r;
}

__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  VEC v;
 
  v.X = V1.X + V2.X;
  v.Y = V1.Y + V2.Y;
  v.Z = V1.Z + V2.Z;
  return v;
}

__inline VEC VecSubVec( VEC V1, VEC V2 )
{
  VEC v;

  v.X = V1.X - V2.X;
  v.Y = V1.Y - V2.Y;
  v.Z = V1.Z - V2.Z;
  return v;
}

__inline VEC VecMulNum( VEC V1, DBL N )
{
  VEC v;

  v.X = V1.X * N;
  v.Y = V1.Y * N;
  v.Z = V1.Z * N;
  return v;
}

__inline VEC VecDivNum( VEC V1, DBL N )
{
  VEC v;

  v.X = V1.X / N;
  v.Y = V1.Y / N;
  v.Z = V1.Z / N;
  return v;
}

__inline VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
}

__inline DBL VecDotVec( VEC V1, VEC V2 )
{
   return sqrt((V1.X + V2.X) * (V1.X + V2.X) + (V1.Y + V2.Y) * (V1.Y + V2.Y) + (V1.Z + V2.Z) * (V1.Z + V2.Z));
}

__inline DBL VecLen2( VEC V )
{
   return VecDotVec(V, V);
}

__inline DBL VecLen( VEC V )
{
  DBL len = VecDotVec(V, V);
 
  if (len == 1 || len == 0)
    return len;
  return sqrt(len);
}

__inline VEC VecNormalize( VEC V )   /*V/|V|*/
{
  DBL len = VecDotVec(V, V);
 
  if (len == 1 || len == 0)
    return V;
  return VecDivNum(V, sqrt(len));
}

__inline VEC VectorTransform( VEC V, MATR M )
{
  return VecSet(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0],
                V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1],
                V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2]);
}

__inline VEC PointTransform( VEC V, MATR M )
{
  return VecSet(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0],
                V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1],
                V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]);
}

__inline VEC VecMulMatr( VEC V, MATR M )
{
  DBL w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3] + M.A[3][3];
 
  return VecSet((V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0]) / w,
                (V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1]) / w,
                (V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]) / w);
}

__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  VEC v;
  v.X = V1.Y * V2.Z - V1.Z * V2.Y;
  v.Y = V1.Z * V2.X - V1.X * V2.Z;
  v.Z = V1.X * V2.Y - V1.Y * V2.X;
  return v;
}

__inline MATR MatrSet( DBL A00, DBL A01, DBL A02, DBL A03,
              DBL A10, DBL A11, DBL A12, DBL A13,
              DBL A20, DBL A21, DBL A22, DBL A23,
              DBL A30, DBL A31, DBL A32, DBL A33 )
{
  MATR m =
  {
    {
      {A00, A01, A02, A03},
      {A10, A11, A12, A13},
      {A20, A21, A22, A23},
      {A30, A31, A32, A33},
    }
  };
 
  return m;
}

__inline MATR MatrSet3x3( DBL A00, DBL A01, DBL A02,
              DBL A10, DBL A11, DBL A12,
              DBL A20, DBL A21, DBL A22 )
{
  MATR m =
  {
    {
      {A00, A01, A02},
      {A10, A11, A12},
      {A20, A21, A22},
    }
  };
 
  return m;
}

__inline MATR MatrTranslate( VEC T )
{
  MATR m = UnitMatrix;
 
  m.A[3][0] = T.X;
  m.A[3][1] = T.Y;
  m.A[3][2] = T.Z;
  return m;
}

__inline MATR MatrIdentity( VOID )
{
  return UnitMatrix;
}

__inline MATR MatrMulMatr( MATR M1, MATR M2 )
{
  MATR r = {{{0}}};
  INT i, j, k;
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (k = 0; k < 4; k++)
        r.A[i][j] += M1.A[i][k] * M2.A[k][j];
  return r;
}

__inline MATR MatrMulMatr3( MATR M1, MATR M2, MATR M3 )
{
  return (M1, MatrMulMatr(M2, M3));
}

__inline MATR MatrMulMatr4( MATR M1, MATR M2, MATR M3, MATR M4 )
{
  return (M1, MatrMulMatr3(M2, M3, M4));
}


__inline DBL MatrDeterm3x3( DBL A11, DBL A12, DBL A13,
                   DBL A21, DBL A22, DBL A23,
                   DBL A31, DBL A32, DBL A33 )
{
  return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 - A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
}

__inline MATR MatrTranspose( MATR M )
{
  MATR res;
  INT i, j;
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
    {
      res.A[i][j] = M.A[j][i];
    }
  return res;
}

__inline DBL MatrDeterm( MATR M )
{
  return
    M.A[0][0] * MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                              M.A[2][1], M.A[2][2], M.A[2][3],
                              M.A[3][1], M.A[3][2], M.A[3][3]) +
    -M.A[0][1] * MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                               M.A[2][0], M.A[2][2], M.A[2][3],
                               M.A[3][0], M.A[3][2], M.A[3][3]) +
    M.A[0][2] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                              M.A[2][0], M.A[2][1], M.A[2][3],
                              M.A[3][0], M.A[3][1], M.A[3][3]) +
    -M.A[0][2] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                               M.A[2][0], M.A[2][1], M.A[2][2],
                               M.A[3][0], M.A[3][1], M.A[3][2]);
}

__inline MATR MatrInverse( MATR M )
{
  DBL det = MatrDeterm(M);
  MATR r;
  INT i, j;
  INT sign[2] = {1, -1}, P[4][3] = {{1, 2, 3}, {0, 2, 3}, {0, 1, 3}, {0, 1, 2}};
 
  if (det == 0)
    return MatrIdentity();
 
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      r.A[j][i] = sign[(i + j) % 2] *
        MatrDeterm3x3(M.A[P[i][0]][P[j][0]], M.A[P[i][0]][P[j][1]], M.A[P[i][0]][P[j][2]],
                      M.A[P[i][1]][P[j][0]], M.A[P[i][1]][P[j][1]], M.A[P[i][1]][P[j][2]],
                      M.A[P[i][2]][P[j][0]], M.A[P[i][2]][P[j][1]], M.A[P[i][2]][P[j][2]]) / det;
  return r;
}

__inline MATR MatrRotateZ( DBL AngleInDegree )
{
  MATR m = UnitMatrix;
  DBL a = D2R(AngleInDegree), s = sin(a), c = cos(a);

  m.A[0][0] = c;
  m.A[1][0] = -s;
  m.A[0][1] = s;
  m.A[1][1] = c;
  return m;
}

__inline MATR MatrRotateX( DBL AngleInDegree )
{
  MATR m = UnitMatrix;
  DBL a = D2R(AngleInDegree), s = sin(a), c = cos(a);

  m.A[1][2] = s;
  m.A[2][1] = -s;
  m.A[2][2] = c;
  m.A[1][1] = c;
  return m;
}

__inline MATR MatrRotateY( DBL AngleInDegree )
{
  MATR m = UnitMatrix;
  DBL a = D2R(AngleInDegree), s = sin(a), c = cos(a);

  m.A[0][0] = c;
  m.A[0][2] = -s;
  m.A[2][0] = s;
  m.A[2][2] = c;
  return m;
}

#endif /* __mth_h_ */
