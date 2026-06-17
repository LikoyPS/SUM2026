#include "anim/rnd/rnd.h"

ik1MATERIAL IK1_RndMaterials[IK1_MAX_MATERIALS];
INT IK1_RndMaterialsSize;


ik1MATERIAL IK1_RndMtlGetDef( VOID )
{
  ik1MATERIAL def_mtl =
  {
    "Default",
    {0.1, 0.1, 0.1},
    {0.90, 0.90, 0.90},
    {0.30, 0.30, 0.30},
    30, 1,
    {-1, -1, -1, -1, -1, -1, -1, -1},
    0
  };
 
  return def_mtl;
}

INT IK1_RndMtlAdd( ik1MATERIAL *Mtl ) 
{
  if (IK1_RndMaterialsSize >= IK1_MAX_MATERIALS)
    return 0;
  IK1_RndMaterials[IK1_RndMaterialsSize] = *Mtl;
  return IK1_RndMaterialsSize++;
}

VOID IK1_RndMtlInit( VOID )
{
  ik1MATERIAL def = IK1_RndMtlGetDef();
 
  IK1_RndMaterialsSize = 0;
  IK1_RndMtlAdd(&def);
}

VOID IK1_RndMtlClose( VOID )
{
}

UINT IK1_RndMtlApply( INT MtlNo )
{
  INT prg;
  ik1MATERIAL *mtl;
  INT loc;
 
  /* Set material pointer */
  if (MtlNo < 0 || MtlNo >= IK1_RndMaterialsSize)
    MtlNo = 0;
  mtl = &IK1_RndMaterials[MtlNo];
 
  /* Set shader program Id */
  prg = mtl->ShdNo;
  if (prg < 0 || prg >= IK1_RndShadersSize)
    prg = 0;
  prg = IK1_RndShaders[prg].ProgId;
 
  if (prg == 0)
    return 0;
  glUseProgram(prg);

 
  /* Set shading parameters */
  if ((loc = glGetUniformLocation(prg, "Ka")) != -1)
    glUniform3fv(loc, 1, &mtl->Ka.X);
  if ((loc = glGetUniformLocation(prg, "Kd")) != -1)
    glUniform3fv(loc, 1, &mtl->Kd.X);
  if ((loc = glGetUniformLocation(prg, "Ks")) != -1)
    glUniform3fv(loc, 1, &mtl->Ks.X);
  if ((loc = glGetUniformLocation(prg, "Ph")) != -1)
    glUniform1f(loc, mtl->Ph);
  if ((loc = glGetUniformLocation(prg, "Trans")) != -1)
    glUniform1f(loc, mtl->Trans);
  return prg;
}