/* IK1 t05det.c */
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

typedef DOUBLE DBL;

#define MAX 3
DBL A[MAX][MAX];
INT N;
INT P[MAX];
BOOL IsParity;
DBL Det;

BOOL LoadMatrix( CHAR *FileName )
{
  FILE *F;
  INT i, j;

  N = 0;
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  fscanf(F, "%d", &N);
  if (N < 0)
    N = 0;
  else
    if (N > MAX)
      N = MAX;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      fscanf(F, "%lf", &A[i][j]);

  fclose(F);
  return TRUE;
}

VOID Swap( INT *a, INT *b )
{
  INT t;

  t = *b;
  *b = *a;
  *a = t;
}

VOID GO( INT Pos )
{
  INT i;
  DBL prod;

  if (Pos == N)
  {
    for (prod = 1, i = 0; i < N; i++)
      prod *= A[i][P[i]];
    Det += prod * (IsParity ? 1 : -1);
    return;
  }
  else
  {
    for (i = Pos; i < N; i++)
    {
      if (i != Pos)
      {
        Swap(&P[Pos], &P[i]);
        IsParity = !IsParity;
      }
      GO(Pos + 1);
      if (i != Pos)
      {
        Swap(&P[Pos], &P[i]);
        IsParity = !IsParity;
      }
    }
  }
}

DBL Determ( VOID )
{
  INT i;

  for (i = 0; i < MAX; i++)
    P[i] = i;

  IsParity = TRUE;
  Det = 0;
  GO(0);
  return Det;
}


VOID main( VOID )
{
  INT i;
  FILE *F;

  if (!LoadMatrix("IN.TXT"))
  {
    printf("error");
    return;
    _getch();
  }
  F = fopen("cout.txt", "a");
  if (F == NULL)
  {
    printf("ERROR");
    return;
  }
  for (i = 0; i < MAX; i++)
    P[i] = i;

  fprintf(F, "%lf", Determ());
  fclose(F);
}