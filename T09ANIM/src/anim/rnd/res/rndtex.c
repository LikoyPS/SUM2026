#include "rndres.h"
#include <stdio.h>

ik1TEXTURE IK1_RndTextures[IK1_MAX_TEXTURES];
INT IK1_RndTexturesSize;

VOID IK1_RndTexInit( VOID )
{
  IK1_RndTexturesSize = 0;
}

VOID IK1_RndTexClose( VOID )
{
  INT i;

  for (i = 0; i < IK1_RndTexturesSize; i++)
    glDeleteTextures(1, &IK1_RndTextures[i].TexId);
  IK1_RndTexturesSize = 0;
}


/* textures from pic. */
INT IK1_RndTexAddImg( CHAR *FileName, INT W, INT H, INT C, DWORD *Bits )
{
  INT mips;
 
  if (IK1_RndTexturesSize >= IK1_MAX_TEXTURES)
    return -1;
 
  /* Setup OpenGL texture */
  glGenTextures(1, &IK1_RndTextures[IK1_RndTexturesSize].TexId);
  glBindTexture(GL_TEXTURE_2D, IK1_RndTextures[IK1_RndTexturesSize].TexId);
 
 
  mips = log(W > H ? W : H) / log(2);
  mips = mips < 1 ? 1 : mips;
 
  glTexStorage2D(GL_TEXTURE_2D, mips, C == 4 ? GL_RGBA8 : C == 3 ? GL_RGB8 : GL_R8, W, H);
 
  if (Bits != NULL)
  {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, W, H,
                    C == 4 ? GL_BGRA : C == 3 ? GL_BGR : GL_RED, GL_UNSIGNED_BYTE, Bits);
  }
  glGenerateMipmap(GL_TEXTURE_2D);
 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
 
  return IK1_RndTexturesSize++;
}

INT IK1_RndTexAddFromFile( CHAR *FileName )
{
  INT ret = -1;
  HBITMAP hBm;
  FILE *F;
 
  if ((hBm = LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION)) != NULL)
  {
    BITMAP Bm;
 
    GetObject(hBm, sizeof(BITMAP), &Bm);
    if (Bm.bmBitsPixel == 24 || Bm.bmBitsPixel == 32 || Bm.bmBitsPixel == 8)
      ret = IK1_RndTexAddImg(FileName, Bm.bmWidth, Bm.bmHeight, Bm.bmBitsPixel >> 3, Bm.bmBits); 
    DeleteObject(hBm);
    return ret;
  }
  if ((F = fopen(FileName, "rb")) != NULL)
  {
    INT w = 0, h = 0, flen, components = -1;
    VOID *mem;
 
    fread(&w, 2, 1, F);
    fread(&h, 2, 1, F);
 
    fseek(F, 0, SEEK_END);
    flen = ftell(F);
    fseek(F, 4, SEEK_END);
 
    if (w * h * 4 + 4 == flen)
      components = 4;
    else if (w * h * 3 + 4 == flen)
      components = 3;
    else if (w * h * 1 + 4 == flen)
      components = 1;
 
    if (components != -1)
      if ((mem = malloc(w * h * components)) != NULL)
      {
        fread(mem, components, w * h, F);
        ret = IK1_RndTexAddImg(FileName, w, h, components, mem); 
        free(mem);
      }
    fclose(F);
  }
  return ret;
} /* End of 'IK1_RndTexAddFromFile' function */
