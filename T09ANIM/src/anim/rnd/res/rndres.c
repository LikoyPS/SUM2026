#include "rndres.h"
#include "anim/rnd/rnd.h"

/* Shader storage initialize function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID IK1_RndResInit( VOID )
{
  IK1_RndShdAdd("default");
} /* End of 'IK1_RndShdInit' function */
 
/* Shader storage deinitialize function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID IK1_RndResClose( VOID )
{
  INT i;
 
  for (i = 0; i < IK1_RndShadersSize; i++)
    IK1_RndShdFree(IK1_RndShaders[i].ProgId);
  IK1_RndShadersSize = 0;
} /* End of 'IK1_RndShdClose' function */