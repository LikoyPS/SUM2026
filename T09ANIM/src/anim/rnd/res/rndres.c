#include "rndres.h"
#include "anim/rnd/rnd.h"

/* Shader storage initialize function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID IK1_RndResInit( VOID )
{
  IK1_RndShdInit();
  IK1_RndTexInit();
  IK1_RndMtlInit();
} /* End of 'IK1_RndShdInit' function */
 
/* Shader storage deinitialize function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID IK1_RndResClose( VOID )
{
  IK1_RndMtlClose();
  IK1_RndShdClose();
  IK1_RndTexClose();  
} /* End of 'IK1_RndShdClose' function */