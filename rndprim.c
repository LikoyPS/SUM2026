/* IK1 */
#include "rnd.h"
#include <string.h>


VOID IK1_RndPrimFree( ik1PRIM *Pr )
{
  free(Pr->V);
  memset(Pr, 0, sizeof(ik1VERTEX));   /* <-- <string.h>, WinAPI, ZeroMemory */
}

BOOL IK1_RndPrimCreate( ik1PRIM *Pr, INT NoofV, INT NoofI )
{
  INT size;
 
  memset(Pr, 0, sizeof(ik1PRIM));
  size = sizeof(ik1VERTEX) * NoofV + sizeof(INT) * NoofI;
 
  if ((Pr->V = malloc(size)) == NULL)
    return FALSE;
  Pr->I = (INT *)(Pr->V + NoofV);
  Pr->NumOfV = NoofV;
  Pr->NumOfI = NoofI;
  Pr->Trans = MatrIdentity();
  memset(Pr->V, 0, size);
  return TRUE;
}

