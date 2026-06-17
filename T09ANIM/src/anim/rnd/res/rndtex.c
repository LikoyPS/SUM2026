#include "rndres.h"

ik1TEXTURE IK1_RndTextures[IK1_MAX_TEX];
INT IK1_RndTexturesSize;

VOID IK1_RndTexInit( VOID )
{
  IK1_RndTexturesSize = 0;
}

VOID IK1_RndTexClose( VOID )
{
  IK1_RndTexturesSize = 0;
}

