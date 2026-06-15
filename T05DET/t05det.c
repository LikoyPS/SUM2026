#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define MAX 3
typedef DOUBLE DBL;
DBL A[MAX][MAX];
INT N, Det, prod;

INT perm[MAX];
BOOL IsParity;

BOOL LoadMatrix( CHAR *FileName )
{
  FILE *F;
  INT i, j;
  N = 0;
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;
  fscanf(F, "%d", &N);
  if (N > MAX)
    N = MAX;
  else
    if (N < 0)
      N = 0;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      fscanf(F, "%lf", &A[i][j]);
  fclose(F);
  return TRUE;
}

VOID Swap( INT* a, INT* b )
{
  INT c = *a;
  *a = *b;
  *b = c;
}

VOID Store( VOID )
{
  INT i;
  FILE *F;
  F = fopen("cout.txt", "a");
  if (F == NULL)
    return;
  for (i = 0; i < MAX - 1; i++)
    fprintf(F, "%d", perm[i]);
  fprintf(F, "%d - parity:%s\n", perm[MAX - 1], IsParity ? "yes" : "no");
  fprintf(F, "%d", Det);
  fclose(F);
}
VOID f( INT Pos )
{
  INT i;
  LoadMatrix("cinp.txt");
  if (Pos == MAX)
  {
    Store();
    return;
  }
  else
  {
    for (i = Pos; i < MAX; i++)
    {
      Swap(&perm[Pos], &perm[i]);
      IsParity = !IsParity;
      f(Pos + 1);
      Swap(&perm[Pos], &perm[i]);
    }
  IsParity = !IsParity;  
  }
  if (Pos == N)
  {
    for (prod = 1, i = 0; i < N; i++)
      prod *= A[i][perm[i]];
    Det += prod * (IsParity ? 1 : -1);
  }
}
VOID main ( VOID )
{
  /*INT i;
  for (i = 0; i < MAX; i++)
    perm[i] = i + 1; */
  f(0);
}
