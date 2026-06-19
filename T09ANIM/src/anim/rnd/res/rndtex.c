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
  INT mips, C;
 
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
