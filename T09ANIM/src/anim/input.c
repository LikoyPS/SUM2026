
#include "anim.h"

static BYTE KeysOld[256];

VOID IK1_KeyboardInit( VOID )
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

VOID IK1_KeyboardResponse( VOID )
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

INT IK1_MouseWheel;

VOID IK1_MouseInit( VOID )
{
  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(IK1_Anim.hWnd, &pt);

  IK1_Anim.Mdx = 0;
  IK1_Anim.Mdy = 0;

  IK1_Anim.Mx = pt.x;
  IK1_Anim.My = pt.y;

  IK1_Anim.Mdz = IK1_MouseWheel;
  IK1_Anim.Mz += IK1_MouseWheel;
  
  IK1_MouseWheel = IK1_Anim.Mdz = IK1_Anim.Mz = 0;
}

VOID IK1_MouseResponse( VOID )
{
  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(IK1_Anim.hWnd, &pt);

  IK1_Anim.Mdx = (-pt.x + IK1_Anim.Mx) / 3;
  IK1_Anim.Mdy = (-pt.y + IK1_Anim.My) / 3;

  IK1_Anim.Mx = pt.x;
  IK1_Anim.My = pt.y;

  IK1_Anim.Mdz = IK1_MouseWheel;
  IK1_Anim.Mz += IK1_MouseWheel;
  IK1_MouseWheel = 0;
}

VOID IK1_AnimInputInit( VOID )
{
  IK1_KeyboardInit();
  IK1_MouseInit();
}

VOID IK1_AnimInputResponse( VOID )
{
  IK1_KeyboardResponse();
  IK1_MouseResponse();
}
