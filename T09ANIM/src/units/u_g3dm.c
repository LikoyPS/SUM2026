/* start of "u_g3dm.c" */
#include "units.h"

typedef struct tagik1UNIT_G3DM
{
  IK1_UNIT_BASE_FIELDS;
  VEC Pos;
  ik1PRIMS Model;
} ik1UNIT_G3DM;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ik1UNIT_G3DM *Uni;
 *   - animation context:
 *       ik1ANIM *Ani;
 * RETURNS: None.
 */
static VOID IK1_UnitInit( ik1UNIT_G3DM *Uni, ik1ANIM *Ani )
{
  IK1_RndPrimsLoad(&Uni->Model, "bin/models/bike.g3dm");
  Uni->Pos = VecSet(100, 100, 100);
} /* End of 'IK1_UnitInit' function */
 
/* Unit deinitialization function.
 * ARGUMENTS:        
 *   - self-pointer to unit object:
 *       ik1UNIT_G3DM *Uni;
 *   - animation context:
 *       ik1ANIM *Ani;
 * RETURNS: None.
 */
static VOID IK1_UnitClose( ik1UNIT_G3DM *Uni, ik1ANIM *Ani )
{
  IK1_RndPrimsFree(&Uni->Model);
} /* End of 'IK1_UnitClose' function */
 
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ik1UNIT_G3DM *Uni;
 *   - animation context:
 *       ik1ANIM *Ani;
 * RETURNS: None.
 */
static VOID IK1_UnitResponse( ik1UNIT_G3DM *Uni, ik1ANIM *Ani )
{
} /* End of 'IK1_UnitResponse' function */
 
/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ik1UNIT_G3DM *Uni;
 *   - animation context:
 *       ik1ANIM *Ani;
 * RETURNS: None.
 */
static VOID IK1_UnitRender( ik1UNIT_G3DM *Uni, ik1ANIM *Ani )
{
  IK1_RndPrimsDraw(&Uni->Model, MatrIdentity());
} /* End of 'IK1_UnitRender' function */
 
/* G3DM model unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ik1UNIT *) pointer to created unit.
 */
ik1UNIT * IK1_UnitCreateG3DM( VOID )
{
  ik1UNIT *Uni;
 
  if ((Uni = IK1_AnimUnitCreate(sizeof(ik1UNIT_G3DM))) == NULL)
    return NULL;
 
  /* Setup unit methods */
  Uni->Init = (VOID *)IK1_UnitInit;
  Uni->Close = (VOID *)IK1_UnitClose;
  Uni->Response = (VOID *)IK1_UnitResponse;
  Uni->Render = (VOID *)IK1_UnitRender;
 
  return Uni;
} /* End of 'IK1_UnitCreateG3DM' function */
/* end of "u_g3dm.c" */