#include "units.h"
#include <stdio.h>

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ik6UNIT_CONTROL *Uni;
 *   - animation context:
 *       IK1ANIM *Ani;
 * RETURNS: None.
 */
  static VOID IK1_UnitInit( ik1UNIT_CONTROL *Uni, ik1ANIM *Ani )
{
  Uni->CamLoc = VecSet(8, 8, 8);
  Uni->CamAt = VecSet(0, 0, 0);
  Uni->Speed = 1;
} /* End of 'IK1_UnitInit' function */
 
/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ik6UNIT_CONTROL *Uni;
 *   - animation context:
 *       IK1_ANIM *Ani;
 * RETURNS: None.
 */
static VOID IK1_UnitClose( ik1UNIT_CONTROL *Uni, ik1ANIM *Ani )
{
} /* End of 'IK1_UnitClose' function */
 
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ik6UNIT_CONTROL *Uni;
 *   - animation context:
 *       IK1_ANIM *Ani;
 * RETURNS: None.
 */
 static VOID IK1_UnitResponse( ik1UNIT_CONTROL *Uni, ik1ANIM *Ani )
{
  VEC d;
  INT modes[2];
 
  /*if (Ani->KeysClick['P'])
    Ani->IsPause = !Ani->IsPause;*/

  if (Ani->Keys[VK_SHIFT] && Ani->KeysClick['W'])
  {
    glGetIntegerv(GL_POLYGON_MODE, modes);

    if (modes[0] == GL_FILL)
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
  }

  if (Ani->KeysClick[VK_ESCAPE])
    IK1_AnimDoExit();

  d = VecNormalize(VecSubVec(Uni->CamAt, Uni->CamLoc));;

  Uni->CamLoc = 
    VecAddVec(Uni->CamLoc,
      VecMulNum(d, Ani->GlobalDeltaTime * (Ani->Mdz)));

  Uni->CamLoc =
    PointTransform(Uni->CamLoc,
      MatrRotateY(Ani->Keys[VK_LBUTTON] * 
        Ani->Mdx));

  IK1_RndCamSet(Uni->CamLoc, Uni->CamAt, VecSet(0, 1, 0));
} /* End of 'IK1_UnitResponse' function */
 
/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ik6UNIT_CONTROL *Uni;
 *   - animation context:
 *       IK1_ANIM *Ani;
 * RETURNS: None.
 */
static VOID IK1_UnitRender( ik1UNIT_CONTROL *Uni, ik1ANIM *Ani )
{
  CHAR Buf[102];
  static DBL OldTime;
  
  if (Ani->GlobalTime - OldTime < 2)
  {
    sprintf(Buf, "FPS: %.3f", Ani->FPS);
    SetWindowText(Ani->hWnd, Buf);
    OldTime = Ani->GlobalTime;
  }
} /* End of 'IK1_UnitRender' function */
 
/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (ik6UNIT *) pointer to created unit.
 */
 ik1UNIT * IK1_UnitCreateControl( VOID )
{
  ik1UNIT_CONTROL *Uni;

  if (( Uni = (ik1UNIT_CONTROL *)IK1_AnimUnitCreate(sizeof(ik1UNIT_CONTROL))) == NULL)
    return NULL;
  Uni->Init = (VOID *)IK1_UnitInit;                      
  Uni->Response = (VOID *)IK1_UnitResponse;
  Uni->Render = (VOID *)IK1_UnitRender;
  return (ik1UNIT *)Uni;
} /* End of 'IK1_AnimUnitCreate' function */  