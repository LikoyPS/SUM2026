/* FILE NAME: rndprim.C
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: IK1
 * DATE: 09.06.2026
 */

#include <stdio.h>

#include "anim/anim.h"

VOID IK1_RndPrimCreate( ik1PRIM *Pr, ik1PRIM_TYPE Type,
                        ik1VERTEX *V, INT NoofV, INT *Ind, INT NoofI )
{
  memset(Pr, 0, sizeof(ik1PRIM));
  Pr->Trans = MatrIdentity();
  Pr->Type = Type;
 
  glGenVertexArrays(1, &Pr->VA);
 
  /* Vertex data */
  if (V != NULL && NoofV != 0)
  {
    glBindVertexArray(Pr->VA);
    glGenBuffers(1, &Pr->VBuf);
    glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ik1VERTEX) * NoofV, V, GL_STATIC_DRAW);
 
    glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(ik1VERTEX),
                          (VOID *)0); /* position */
    glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(ik1VERTEX),
                          (VOID *)sizeof(VEC)); /* texture coordinates */
    glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(ik1VERTEX),
                          (VOID *)(sizeof(VEC) + sizeof(VEC2))); /* normal */
    glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(ik1VERTEX),
                          (VOID *)(sizeof(VEC) * 2 + sizeof(VEC2))); /* color */
 
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
 
    glBindVertexArray(0);
 
    /* Obtain BB */
    if (NoofV > 0)
    {
      INT i;
 
      Pr->MinBB = Pr->MaxBB = V[0].P;
      for (i = 1; i < NoofV; i++)
      {
        Pr->MinBB = VecMinVec(Pr->MinBB, V[i].P);
        Pr->MaxBB = VecMaxVec(Pr->MaxBB, V[i].P);
      }
    }
  }
 
  /* Index data */
  if (Ind != NULL && NoofI != 0)
  {
    glGenBuffers(1, &Pr->IBuf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NoofI, Ind, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
 
    Pr->NumOfElements = NoofI;
  }
  else
    Pr->NumOfElements = NoofV;
} /* End of 'IK1_RndPrimCreate' function */


/* Primitive free function.
 * ARGUMENTS:
 *   - primitive to be free:
 *       ik1PRIM *Pr;
 * RETURNS: None.
 */
VOID IK1_RndPrimFree( ik1PRIM *Pr )
{
  glDeleteVertexArrays(1, &Pr->VA);
  glDeleteBuffers(1, &Pr->VBuf);
  glDeleteBuffers(1, &Pr->IBuf);
  memset(Pr, 0, sizeof(ik1PRIM));
} /* End of 'IK1_RndPrimFree' function */
 
/* Start of IK1_RndPrimDraw function */
VOID IK1_RndPrimDraw( ik1PRIM *Pr, MATR World )
{
  MATR
    w = MatrMulMatr(Pr->Trans, World),
    winv = MatrTranspose(MatrInverse(w)),
    wvp = MatrMulMatr(w, IK1_RndMatrVP);
  UINT ProgId;
  INT loc;
  INT prim_type =
    Pr->Type == IK1_RND_PRIM_LINES ? GL_LINES :
    Pr->Type == IK1_RND_PRIM_TRIMESH ? GL_TRIANGLES :
    Pr->Type == IK1_RND_PRIM_TRISTRIP ? GL_TRIANGLE_STRIP:
    GL_POINTS;
 
  
  /* glUseProgram(ProgId); */
  if ((ProgId = IK1_RndMtlApply(Pr->MtlNo)) == 0)
    return;

  if ((loc = glGetUniformLocation(ProgId, "MatrWVP")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, wvp.A[0]);
  if ((loc = glGetUniformLocation(ProgId, "Time")) != -1)
    glUniform1f(loc, IK1_Anim.Time);
  if ((loc = glGetUniformLocation(ProgId, "MatrWInv")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, winv.A[0]);
 /* if ((loc = glGetUniformLocation(ProgId, "CamLoc")) != -1)
    glUniform3fv(loc, 1, &IK1_RndCamLoc.X);*/ 
 
  glBindVertexArray(Pr->VA);
  if (Pr->IBuf == 0)
    glDrawArrays(prim_type, 0, Pr->NumOfElements);
  else
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glDrawElements(prim_type, Pr->NumOfElements, GL_UNSIGNED_INT, NULL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);

  glUseProgram(0);
} /* End of 'IK1_RndPrimDraw' function */

VOID IK1_RndPrimTriMeshAutoNormals(ik1VERTEX *V, INT nv, INT *Ind, INT nf)
{
  INT i;

  for (i = 0; i < nv; i++)
    V[i].N = VecSet(0, 0, 0);
  for (i = 0; i < nf; i += 3)
  {
    VEC
      p0 = V[Ind[i]].P,
      p1 = V[Ind[i + 1]].P,
      p2 = V[Ind[i + 2]].P,
      N = VecNormalize(VecCrossVec(VecSubVec(p1, p0), VecSubVec(p2, p0)));
 
    V[Ind[i]].N = VecAddVec(V[Ind[i]].N, N);
    V[Ind[i + 1]].N = VecAddVec(V[Ind[i + 1]].N, N);
    V[Ind[i + 2]].N = VecAddVec(V[Ind[i + 2]].N, N);
  }
  for (i = 0; i < nv; i++)
      V[i].N = VecNormalize(V[i].N);
}

BOOL IK1_RndPrimLoad( ik1PRIM *Pr, CHAR *FileName )
{
  FILE *F;
  VEC L = VecNormalize(VecSet(1, 1, 1));
  INT i, size;
  INT nv = 0, nf = 0;
  ik1VERTEX *V;
  INT *Ind;
  static CHAR Buf[3000];
 
  memset(Pr, 0, sizeof(ik1PRIM));
 
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Count vertices and indices */
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0;
      CHAR *ptr = Buf + 2, oldc = ' ';
 
      while (*ptr != 0)
      {
        if (*ptr != ' ' && oldc == ' ')
          n++;
        oldc = *ptr++;
      }
 
      nf += n - 2;
    }
  }
 
  size = sizeof(ik1VERTEX) * nv + sizeof(INT) * nf * 3;
  if ((V = malloc(size)) == NULL)
  {
    fclose(F);
    return FALSE;
  }
  Ind = (INT *)(V + nv);
  memset(V, 0, size);
  
 
  /* Load model */
  rewind(F);
  nv = 0;
  nf = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;
 
      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      V[nv++].P = VecSet(x / 50, y / 50, z / 50);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n, n1, n2, n3;
      INT fvn = 0;
      CHAR *ptr = Buf + 2, oldc = ' ';
 
      while (*ptr != 0)
      {
        if (*ptr != ' ' && oldc == ' ')
        {
          sscanf(ptr, "%d", &n);
          if (n > 0)
            n--;
          else
            if (n < 0)
              n = nv + n;
 
          if (fvn == 0)
            n1 = n;
          else if (fvn == 1)
            n2 = n;
          else
          {
            n3 = n;
 
            Ind[nf++] = n1;
            Ind[nf++] = n2;
            Ind[nf++] = n3;
 
            n2 = n3;
          }
          fvn++;
        }
        oldc = *ptr++;
      }
    }
  }
  fclose(F);
  IK1_RndPrimTriMeshAutoNormals(V, nv, Ind, nf);
  
  for (i = 0; i < nv; i++)
  {
    FLT nl = VecDotVec(L, V[i].N);
    if (nl < 0.1)
      nl = 0.1;
    V[i].C = Vec4Set3(VecMulNum(VecSet(0.8, 0.3, 0.4), nl * 1.3));
  }
  
  IK1_RndPrimCreate(Pr, IK1_RND_PRIM_TRIMESH, V, nv, Ind, nf);
  free(V);
  return TRUE;
} /* End of 'IK1_RndPrimLoad' function */

BOOL IK1_RndPrimCreateSphere( ik1PRIM *Pr, DBL R, INT W, INT H )
{
  INT i, j, k;
  DBL theta, phi, nl;
  VEC L = VecNormalize(VecSet(1, 1, 1));
  VEC C = VecSet(Rnd0(), Rnd0(), Rnd0());
  ik1VERTEX *V;
  INT *Ind, size;
  
  memset(Pr, 0, sizeof(ik1PRIM));
  size = sizeof(ik1PRIM) * W * H + sizeof(INT) * (H - 1) * (W - 1) * 2 * 3;

  if ((V = malloc(size)) == NULL)
     return FALSE;
  Ind = (INT *)(V + W * H);
  
 
  /* Fill vertex array */
  for (k = 0, i = 0, theta = 0; i < H; i++, theta += PI / (H - 1))
    for (j = 0, phi = 0; j < W; j++, phi += 2 * PI / (W - 1))
    {
      V[k].N = VecSet(sin(theta) * sin(phi),
                      cos(theta),
                      sin(theta) * cos(phi));
      nl = VecDotVec(L, V[k].N);
      if (nl < 0.1)
        nl = 0.1;
      V[k].C = Vec4Set3(VecMulNum(C, nl));
      V[k++].P = VecSet(R * sin(theta) * sin(phi),
                        R * cos(theta),
                        R * sin(theta) * cos(phi));
    }

  /* Fill vertex array */
  for (k = 0, i = 0; i < H - 1; i++)
    for (j = 0; j < W - 1; j++)
    {
      /* bottom-left */
      Ind[k++] = i * W + j;
      Ind[k++] = i * W + j + 1;
      Ind[k++] = (i + 1) * W + j;
      /* top-right */
      Ind[k++] = (i + 1) * W + j;
      Ind[k++] = i * W + j + 1;
      Ind[k++] = (i + 1) * W + j + 1;
    }

    IK1_RndPrimCreate(Pr, IK1_RND_PRIM_TRIMESH, V, W * H, Ind, (H - 1) * (W - 1) * 2 * 3);
    free(V);
    return TRUE;
} /* End of 'IK1_RndPrimCreateSphere' function */
