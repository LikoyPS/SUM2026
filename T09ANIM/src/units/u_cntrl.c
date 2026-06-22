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
  Uni->CamLoc = VecSet(1, 1, 0);
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
  VEC d, NewLoc, dv;
  INT modes[2];
  DBL cosT, sinT, cosP, sinP, plen;
  DBL Azimuth, Elevator, Wp, Hp, sx, sy;
  FLT Dist;

  Dist = VecLen(VecSubVec(IK1_RndCamAt, IK1_RndCamLoc));

  cosT = (IK1_RndCamLoc.Y - IK1_RndCamAt.Y) / Dist;
  sinT = sqrt(1 - cosT * cosT);

  plen = Dist * sinT;
  cosP = (IK1_RndCamLoc.Z - IK1_RndCamAt.Z) / plen;
  sinP = (IK1_RndCamLoc.X - IK1_RndCamAt.X) / plen;

  Azimuth = R2D(atan2(sinP, cosP));
  Elevator = R2D(atan2(sinT, cosT));

  Azimuth -= Ani->GlobalDeltaTime * 47 * 0.0001 * (Ani->Keys[VK_LEFT] - Ani->Keys[VK_RIGHT]) 
    - 30 * Ani->Keys[VK_LBUTTON] * 0.03 * Ani->Mdx;

  Elevator -= Ani->GlobalDeltaTime * 47 * 0.0001 * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]) 
    - 30 * Ani->Keys[VK_LBUTTON] * 0.03 * Ani->Mdy;

  Dist += Ani->GlobalDeltaTime * (Ani->Mdz + 8 * (1 + Ani->Keys[VK_SHIFT] * 30) 
    * (Ani->Keys[VK_NEXT] - Ani->Keys[VK_PRIOR]));

  if (Dist < 0.01)
    Dist = 0.01;
  if (Elevator > 178)
    Elevator = 178;
  if (Elevator < 0.08)
    Elevator = 0.08;

  NewLoc =
  PointTransform(VecSet(0, Dist, 0),
    MatrMulMatr(MatrRotateX(Elevator),
                MatrRotateY(Azimuth)));

  Wp = IK1_RndProjSize;
  Hp = IK1_RndProjSize;

  if (Ani->W > Ani->H)
    Wp *= (FLT)Ani->W / Ani->H;
  else
    Hp *= (FLT)Ani->H / Ani->W;
 
  sx = Ani->Keys[VK_RBUTTON] * 2 * Ani->Mdx * Wp / Ani->W * Dist / IK1_RndProjDist;
  sy = Ani->Keys[VK_RBUTTON] * 2 * -Ani->Mdy * Hp / Ani->H * Dist / IK1_RndProjDist;
 
  dv = VecAddVec(VecMulNum(IK1_RndCamRight, sx),
                   VecMulNum(IK1_RndCamUp, sy));
  IK1_RndCamAt = VecAddVec(IK1_RndCamAt, dv);
  IK1_RndCamLoc = VecAddVec(IK1_RndCamLoc, dv);


  /* keyboard binds */
  if (Ani->Keys[VK_SHIFT] && Ani->KeysClick['W'])
  {
    glGetIntegerv(GL_POLYGON_MODE, modes);
    if (modes[0] == GL_FILL)
    {  
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      sndPlaySound("bin/sounds/balls.wav", SND_ASYNC);
    }
    else
    {    
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      sndPlaySound("bin/sounds/balls.wav", SND_ASYNC);
    }
  }

  if (Ani->KeysClick[VK_ESCAPE])
    IK1_AnimDoExit();

  d = VecNormalize(VecSubVec(Uni->CamAt, Uni->CamLoc));;

  NewLoc = PointTransform(VecSet(0, Dist, 0),
                        MatrMulMatr(MatrRotateX(Elevator),
                                    MatrRotateY(Azimuth)));
 
  IK1_RndCamSet(PointTransform(VecSet(0, Dist, 0),
                             MatrMulMatr3(MatrRotateX(Elevator),
                                          MatrRotateY(Azimuth),
                                          MatrTranslate(IK1_RndCamAt))), IK1_RndCamAt, VecSet(0, 1, 0));
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