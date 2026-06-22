/* FILE NAME  : rndprims.c
 * PROGRAMMER : IK1
 * LAST UPDATE: 18.06.2026
 * PURPOSE    : 3D animation project.
 *              Rendering primitives handle module.
 */
 
#include <stdio.h>
#include <string.h>
 
#include "anim/anim.h"
 
/***
 * Primitives support
 ***/
 
/* Load model transformation matrix */
MATR IK1_RndPrimsLoadTransform =
{
  {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }
};

/* Create array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       vg4PRIMS *Prs;
 *   - number of primitives to be add:
 *       INT NumOfPrims;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL IK1_RndPrimsCreate( ik1PRIMS *Prs, INT NumOfPrims )
{
  memset(Prs, 0, sizeof(ik1PRIMS));
  if ((Prs->Prims = malloc(sizeof(ik1PRIM) * NumOfPrims)) == NULL)
    return FALSE;
  memset(Prs->Prims, 0, sizeof(ik1PRIM) * NumOfPrims);
  Prs->NumOfPrims = NumOfPrims;
  Prs->Trans = MatrIdentity();
  return TRUE;
} /* End of 'IK1_RndPrimsCreate' function */
 
/* Delete array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       ik1PRIMS *Prs;
 * RETURNS: None.
 */
VOID IK1_RndPrimsFree( ik1PRIMS *Prs )
{
  INT i;
 
  if (Prs->Prims != NULL)
  {
    for (i = 0; i < Prs->NumOfPrims; i++)
      IK1_RndPrimFree(&Prs->Prims[i]);
    free(Prs->Prims);
  }
  memset(Prs, 0, sizeof(ik1PRIMS));
} /* End of 'IK1_RndPrimsFree' function */
 
/* Draw array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       ik1PRIMS *Prs;
 *   - global transformation matrix:
 *       MATR World;
 * RETURNS: None.
 */
VOID IK1_RndPrimsDraw( ik1PRIMS *Prs, MATR World )
{
  INT i;
  MATR m = MatrMulMatr(Prs->Trans, World);
 
  IK1_RndShdAddonI[0] = Prs->NumOfPrims;
  /* Draw all nontransparent primitives */ 
  for (i = 0; i < Prs->NumOfPrims; i++)
    if (IK1_RndMtlGet(Prs->Prims[i].MtlNo).Trans == 1)
      IK1_RndShdAddonI[1] = i, IK1_RndPrimDraw(&Prs->Prims[i], m);
 
  /* Draw all transparent primitives */ 
  glEnable(GL_CULL_FACE);
 
  /* Draw all front-face-culling */ 
  glCullFace(GL_FRONT);
  for (i = 0; i < Prs->NumOfPrims; i++)
    if (IK1_RndMtlGet(Prs->Prims[i].MtlNo).Trans != 1)
      IK1_RndShdAddonI[1] = i, IK1_RndPrimDraw(&Prs->Prims[i], m);
 
  /* Draw all back-face-culling */ 
  glCullFace(GL_BACK);
  for (i = 0; i < Prs->NumOfPrims; i++)
    if (IK1_RndMtlGet(Prs->Prims[i].MtlNo).Trans != 1)
      IK1_RndShdAddonI[1] = i, IK1_RndPrimDraw(&Prs->Prims[i], m);
  glDisable(GL_CULL_FACE);
} /* End of 'IK1_RndPrimsDraw' function */
 
/* Load primitives from '*.G3DM' file function.
 * ARGUMENTS:
 *   - pointer to primitives to create:
 *       ik1PRIMS *Prs;
 *   - '*.G3DM' file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL IK1_RndPrimsLoad( ik1PRIMS *Prs, CHAR *FileName )
{
  FILE *F;
  INT flen;
  UINT p, m, t;
  BYTE *mem, *ptr;
  DWORD Sign; /* == "G3DM" */
  DWORD NumOfPrims;
  DWORD NumOfMaterials;
  DWORD NumOfTextures;
  struct tagG3DM_MATERIAL
  {
    CHAR Name[300]; /* Material name */
    /* Illumination coefficients */
    VEC Ka, Kd, Ks;     /* Ambient, diffuse, specular coefficients */
    FLT Ph;             /* Phong power coefficient – shininess */
    FLT Trans;          /* Transparency factor */
    DWORD Tex[8];       /* Texture references 
                        * (8 time: texture number in G3DM file, -1 if no texture) */
    /* Shader information */
    CHAR ShaderString[300]; /* Additional shader information */
    DWORD Shader;       /* Shader number (uses after load into memory) */
  } *mtls;
  MATR trans_m = IK1_RndPrimsLoadTransform, trans_minv = MatrTranspose(MatrInverse(trans_m));
 
  IK1_RndPrimsLoadTransform = MatrIdentity();
 
  /* Read whole file to memory */
  memset(Prs, 0, sizeof(ik1PRIMS));
  if ((F = fopen(FileName, "rb")) == NULL)
    return FALSE;
  fseek(F, 0, SEEK_END);
  flen = ftell(F);
 
  if ((mem = malloc(flen)) == NULL)
  {
    fclose(F);
    return FALSE;
  }
  rewind(F);
  fread(mem, 1, flen, F);
  fclose(F);
 
  ptr = mem;
  Sign = *(DWORD *)ptr;
  ptr += 4;
  if (Sign != *(DWORD *)"G3DM")
  {
    free(mem);
    fclose(F);
    return FALSE;
  }
  NumOfPrims = *(DWORD *)ptr;
  ptr += 4;
  NumOfMaterials = *(DWORD *)ptr;
  ptr += 4;
  NumOfTextures = *(DWORD *)ptr;
  ptr += 4;
 
  if (!IK1_RndPrimsCreate(Prs, NumOfPrims))
  {
    free(mem);
    fclose(F);
    return FALSE;
  }
 
  /* Primitives */
  for (p = 0; p < NumOfPrims; p++)
  {
    DWORD NumOfVertexes;
    DWORD NumOfFacetIndexes;
    DWORD MtlNo;
    ik1VERTEX *V;
    INT *Ind;
    UINT i;
 
    NumOfVertexes = *(DWORD *)ptr;
    ptr += 4;
    NumOfFacetIndexes = *(DWORD *)ptr;
    ptr += 4;
    MtlNo = *(DWORD *)ptr;
    ptr += 4;
    V = (ik1VERTEX *)ptr;
    ptr += sizeof(ik1VERTEX) * NumOfVertexes;
    Ind = (INT *)ptr;
    ptr += sizeof(INT) * NumOfFacetIndexes;
 
    for (i = 0; i < NumOfVertexes; i++)
    {
      V[i].P = PointTransform(V[i].P, trans_m);
      V[i].N = VectorTransform(V[i].N, trans_minv);
    }
 
    IK1_RndPrimCreate(&Prs->Prims[p], IK1_RND_PRIM_TRIMESH, V, NumOfVertexes, Ind, NumOfFacetIndexes);
    Prs->Prims[p].MtlNo = IK1_RndMaterialsSize + MtlNo;
  }
 
  /* Materials */
  mtls = (VOID *)ptr;
  ptr += sizeof(*mtls) * NumOfMaterials;
  for (m = 0; m < NumOfMaterials; m++)
  {
    ik1MATERIAL mtl = IK1_RndMtlGetDef();
 
    mtl.Ka = VecMinVec(mtls[m].Ka, VecSet1(0.1));
    mtl.Kd = mtls[m].Kd;
    mtl.Ks = mtls[m].Ks;
    mtl.Ph = mtls[m].Ph;
    mtl.Trans = mtls[m].Trans;
    for (t = 0; t < 8; t++)
      if (mtls[m].Tex[t] != -1 && mtls[m].Tex[t] >= 0 && mtls[m].Tex[t] < NumOfTextures)
        mtl.Tex[t] = IK1_RndTexturesSize + mtls[m].Tex[t];
    IK1_RndMtlAdd(&mtl);
  }
 
  /* Textures */
  for (t = 0; t < NumOfTextures; t++)
  {
    CHAR *Name = (CHAR *)ptr;
    DWORD W, H, C;
 
    ptr += 300;
    W = *(DWORD *)ptr;
    ptr += 4;
    H = *(DWORD *)ptr;
    ptr += 4;
    C = *(DWORD *)ptr;
    ptr += 4;
    IK1_RndTexAddImg(Name, W, H, C, ptr);
    ptr += W * H * C;
  }
  free(mem);
  return TRUE;
} /* End of 'IK1_RndPrimsDraw' function */
 
/* END OF 'rndprims.c' FILE */