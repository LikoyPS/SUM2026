/* start of "u_tex.c" */
#include "units.h"

typedef struct tagik1UNIT_TEX
{
  IK1_UNIT_BASE_FIELDS;
  ik1PRIM Pr;/* primitive sample */
  INT MtlNo, TexId;
} ik1UNIT_TEX;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ik1UNIT_BALL *Uni;
 *   - animation context:
 *       ik1ANIM *Ani;
 * RETURNS: None.
 */
static VOID IK1_UnitInit( ik1UNIT_TEX *Uni, ik1ANIM *Ani )
{
  vg4VERTEX V[] =
  {
    {{0, 0, 0}, {0, 0}, {0, 0, 1}, {1, 1, 1, 1}},
    {{1, 0, 0}, {1, 0}, {0, 0, 1}, {1, 1, 1, 1}},
    {{0, 1, 0}, {0, 1}, {0, 0, 1}, {1, 1, 1, 1}},
    {{1, 1, 0}, {1, 1}, {0, 0, 1}, {1, 1, 1, 1}},
  };
 
  FLT t[2][2] =
  {
    {0.8, 1},
    {1, 0.3}
  };

  ik1MATERIAL mtl = IK1_RndMtlGetDef();

  strncpy(mtl.Name, "texture sample", IK1_STR_MAX - 1);
  mtl.ShdNo = IK1_RndShdAdd("tex");
  Uni->MtlNo = IK1_RndMtlAdd(&mtl);
 
  glGenTextures(1, &Uni->TexId);
  glBindTexture(GL_TEXTURE_2D, Uni->TexId);
  glTexImage2D(GL_TEXTURE_2D, 0, 1, 2, 2, 0, GL_LUMINANCE, GL_FLOAT, t);
  
  IK1_RndPrimCreate(&Uni->Pr, IK1_RND_PRIM_TRIMESH, V, 4, NULL, 0);
} /* End of 'IK1_UnitInit' function */
 
/* Unit deinitialization function.
 * ARGUMENTS:        
 *   - self-pointer to unit object:
 *       ik1UNIT_BALL *Uni;
 *   - animation context:
 *       ik1ANIM *Ani;
 * RETURNS: None.
 */
static VOID IK1_UnitClose( ik1UNIT_TEX *Uni, ik1ANIM *Ani )
{
  glDeleteTextures(1, Uni->TexId);
  IK1_RndPrimFree(&Uni->Pr);
} /* End of 'IK1_UnitClose' function */
 
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ik1UNIT_BALL *Uni;
 *   - animation context:
 *       ik1ANIM *Ani;
 * RETURNS: None.
 */
static VOID IK1_UnitResponse( ik1UNIT_TEX *Uni, ik1ANIM *Ani )
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
static VOID IK1_UnitRender( ik1UNIT_TEX *Uni, ik1ANIM *Ani )
{
  glActiveTexture(GL_TEXTURE0 + 1);
  glBindTexture(GL_TEXTURE_2D, Uni->TexId);
  IK1_RndPrimDraw(&Uni->Pr, MatrIdentity);
} /* End of 'IK1_UnitRender' function */
 
/* Texture unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ik1UNIT *) pointer to created unit.
 */
ik1UNIT * IK1_UnitCreateTexture( VOID )
{
  ik1UNIT *Uni;
 
  if ((Uni = IK1_AnimUnitCreate(sizeof(ik1UNIT_TEX))) == NULL)
    return NULL;
 
  /* Setup unit methods */
  Uni->Init = (VOID *)IK1_UnitInit;
  Uni->Close = (VOID *)IK1_UnitClose;
  Uni->Response = (VOID *)IK1_UnitResponse;
  Uni->Render = (VOID *)IK1_UnitRender;
 
  return Uni;
} /* End of 'IK1_UniteCreateTex' function */
/* end of "u_tex.c" */