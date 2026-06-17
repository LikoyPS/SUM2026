
#include "anim.h"

static BYTE KeysOld[256];

static VOID IK1_KeyboardInit( VOID )
{
  INT i;

  GetKeyboardState(IK1_Anim.Keys);
  for (i = 0; i < 256; i++)
  {
    IK1_Anim.Keys[i] >>= 7;
    IK1_Anim.KeysClick[i] = 0;
  }
  memcpy(KeysOld, IK1_Anim.Keys, 256);
}

static VOID IK1_KeyboardResponse( VOID )
{
  INT i;

  GetKeyboardState(IK1_Anim.Keys);
  for (i = 0; i < 256; i++)
  {
    IK1_Anim.Keys[i] >>= 7;
    IK1_Anim.KeysClick[i] = IK1_Anim.Keys[i] && !KeysOld[i];
  }
  memcpy(KeysOld, IK1_Anim.Keys, 256);
}

VOID IK1_AminInputInit( VOID )
{
  IK1_KeyboardInit();
}

VOID IK1_AminInputResponse( VOID )
{
  IK1_KeyboardResponse();
}
