/* start of "unit.c" file  IK1  */

#include "anim.h"

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ik1UNIT *Uni;
 *   - animation context:
 *       ik1ANIM *Ani;
 * RETURNS: None.
 */
static VOID IK1_UnitInit( ik1UNIT *Uni, ik1ANIM *Ani )
{
} /* End of 'IK1_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ik1UNIT *Uni;
 *   - animation context:
 *       ik1ANIM *Ani;
 * RETURNS: None.
 */
static VOID IK1_UnitClose( ik1UNIT *Uni, ik1ANIM *Ani )
{
} /* End of 'IK1_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ik1UNIT *Uni;
 *   - animation context:
 *       ik1ANIM *Ani;
 * RETURNS: None.
 */
static VOID IK1_UnitResponse( ik1UNIT *Uni, ik1ANIM *Ani )
{
} /* End of 'IK1_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ik1UNIT *Uni;
 *   - animation context:
 *       ik1ANIM *Ani;
 * RETURNS: None.
 */
static VOID IK1_UnitRender( ik1UNIT *Uni, ik1ANIM *Ani )
{
} /* End of 'IK1_UnitRender' function */

ik1UNIT * IK1_AnimUnitCreate( INT Size )
{  
  ik1UNIT *Uni;
  
  if (Size < sizeof(ik1UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);
  Uni->Init = IK1_UnitInit;
  Uni->Close = IK1_UnitClose;
  Uni->Response = IK1_UnitResponse;
  Uni->Render = IK1_UnitRender;
  return Uni;
}

 /* end of "unit.c" file  IK1  */