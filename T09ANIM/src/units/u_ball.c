/* start of "u_ball.c" */
#include "units.h"

typedef struct tagik1UNIT_BALL
{
  IK1_UNIT_BASE_FIELDS;
  VEC Pos;
  ik1PRIM Ball;
} ik1UNIT_BALL;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ik1UNIT_BALL *Uni;
 *   - animation context:
 *       ik1ANIM *Ani;
 * RETURNS: None.
 */
static VOID IK1_UnitInit( ik1UNIT_BALL *Uni, ik1ANIM *Ani )
{
  Uni->Pos = VecSet(0, 1, 0);
  IK1_RndPrimCreateSphere(&Uni->Ball, 1, 10, 10);
} /* End of 'IK1_UnitInit' function */
 
/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ik1UNIT_BALL *Uni;
 *   - animation context:
 *       ik1ANIM *Ani;
 * RETURNS: None.
 */
static VOID IK1_UnitClose( ik1UNIT_BALL *Uni, ik1ANIM *Ani )
{
  IK1_RndPrimFree(&Uni->Ball);
} /* End of 'IK1_UnitClose' function */
 
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ik1UNIT_BALL *Uni;
 *   - animation context:
 *       ik1ANIM *Ani;
 * RETURNS: None.
 */
static VOID IK1_UnitResponse( ik1UNIT_BALL *Uni, ik1ANIM *Ani )
{
  
} /* End of 'IK1_UnitResponse' function */
 
/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ik1UNIT_BALL *Uni;
 *   - animation context:
 *       ik1ANIM *Ani;
 * RETURNS: None.
 */
static VOID IK1_UnitRender( ik1UNIT_BALL *Uni, ik1ANIM *Ani )
{
  IK1_RndPrimDraw(&Uni->Ball, MatrIdentity());
} /* End of 'IK1_UnitRender' function */
 
/* Ball unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ik1UNIT *) pointer to created unit.
 */
ik1UNIT * IK1_UnitCreateBall( VOID )
{
  ik1UNIT *Uni;
 
  if ((Uni = IK1_AnimUnitCreate(sizeof(ik1UNIT_BALL))) == NULL)
    return NULL;
 
  /* Setup unit methods */
  Uni->Init = (VOID *)IK1_UnitInit;
  Uni->Close = (VOID *)IK1_UnitClose;
  Uni->Response = (VOID *)IK1_UnitResponse;
  Uni->Render = (VOID *)IK1_UnitRender;
 
  return Uni;
} /* End of 'IK1_UniteCreateBall' function */
/* end of "u_ball.c" */