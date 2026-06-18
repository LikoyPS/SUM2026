#include "rndres.h"

ik1TEXTURE IK1_RndTextures[IK1_MAX_TEXTURES];
INT IK1_RndTexturesSize;

VOID IK1_RndTexInit( VOID )
{
  IK1_RndTexturesSize = 0;
}

VOID IK1_RndTexClose( VOID )
{
  IK1_RndTexturesSize = 0;
}

/* save to textures array */
INT IK1_RndTexAdd( CHAR *FileName )
{
  return 0;
}

/* textures from pic. */
INT IK1_RndTexAddImg( CHAR *FileName, INT W, INT H, DWORD *Bits )
{
 /* if (IK1_RndTexturesSize >= IK1_MAX_TEXTURES)
    return -1;

  glGenTextures(1, &IK1_RndTextures[IK1_RndTexturesSize].TexId);
  glBindTexture(GL_TEXTURE_2D, IK1_RndTextures[IK1_RndTexturesSize].TexId);
  mips = log(W > H ? W : H) / log(2);
  mips = mips < 1 ? 1 : mips;
  glTexStorage2D(GL_TEXTURE_2D, mips, GL_BGR8, W, H);

  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, W, H, GL_BGR, GL_UNSIGNED_BYTE, mem);
  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXRURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXRURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXRURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXRURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  strcpy(IK1_RndTextures[IK1_RndTexturesSize].Name, Name, IK1_STR_MAX - 1);
  IK1_RndTextures[IK1_RndTexturesSize].W = W;
  IK1_RndTextures[IK1_RndTexturesSize].H = H;

  glBindTexture(GL_TEXTURE_2D, 0);
  return IK1_RndTexturesSize++;   */
  return 0;
}
