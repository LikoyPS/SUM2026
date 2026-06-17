#include "rndres.h"

ik1TEXTURE IK1_RndTex[IK1_MAX_TEX];
INT IK1_RndTexSize;

VOID IK1_RndTexInit( VOID )
{
  IK1_RndTexSize = 0;
}

VOID IK1_RndTexClose( VOID )
{
  IK1_RndTexSize = 0;
}

