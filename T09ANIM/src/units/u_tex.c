/* start of "u_tex.c" */
#include "units.h"
#include <stdio.h>

typedef struct tagik1UNIT_TEX
{
  IK1_UNIT_BASE_FIELDS;
  ik1PRIM Pr;/* primitive sample */
  UINT MtlNo, TexId[2];
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
  ik1VERTEX V[] =
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
  FILE *F;
  
  strncpy(mtl.Name, "texture sample", IK1_STR_MAX - 1);
  mtl.ShdNo = IK1_RndShdAdd("tex");
  Uni->MtlNo = IK1_RndMtlAdd(&mtl);
 
  glGenTextures(2, Uni->TexId);
  glBindTexture(GL_TEXTURE_2D, Uni->TexId[0]);
  glTexImage2D(GL_TEXTURE_2D, 0, 1, 2, 2, 0, GL_LUMINANCE, GL_FLOAT, t);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
  IK1_RndPrimCreate(&Uni->Pr, IK1_RND_PRIM_TRISTRIP, V, 4, NULL, 0);
  Uni->Pr.MtlNo = Uni->MtlNo;

  if ((F = fopen("Z:\\SUM2026\\T09ANIM\\A.g24", "rb")) != NULL)
  {
    INT w = 0, h = 0;
    VOID *mem;

    fread(&w, 2, 1, F);
    fread(&h, 2, 1, F);

    if ((mem = malloc(w * h * 3)) != NULL)
    {
      fread(mem, 3, w * h, F);

      glBindTexture(GL_TEXTURE_2D, Uni->TexId[1]);
      glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, mem);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

      free(mem);  
    }

    fclose(F);  
  }
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
  glDeleteTextures(2, Uni->TexId);
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
  INT i;

  for (i = 0; i < 2; i++)
  {
    if (Ani->KeysClick['T'])
    {
      
      glBindTexture(GL_TEXTURE_2D, Uni->TexId[i]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    else if (Ani->KeysClick['Y'])
    {
      
      glBindTexture(GL_TEXTURE_2D, Uni->TexId[i]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else if (Ani->KeysClick['Y'])
    {
      
      glBindTexture(GL_TEXTURE_2D, Uni->TexId[i]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }
  }       
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
  glActiveTexture(GL_TEXTURE0 + 5);
  glBindTexture(GL_TEXTURE_2D, Uni->TexId[0]);

  glActiveTexture(GL_TEXTURE0 + 2);
  glBindTexture(GL_TEXTURE_2D, Uni->TexId[1]);

  IK1_RndPrimDraw(&Uni->Pr, MatrIdentity());
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