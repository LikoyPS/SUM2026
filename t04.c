#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define MAX 3

INT perm[MAX];
BOOL IsParity;

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
  fclose(F);
}
VOID f( INT Pos)
{
  INT i;
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
}
VOID main ( VOID )
{
  INT i;
  for (i = 0; i < MAX; i++)
    perm[i] = i + 1;
  f(0);
}
