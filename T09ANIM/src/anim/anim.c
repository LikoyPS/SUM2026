/* start of "anim.c" file   IK1 */
#include "anim.h"

ik1ANIM IK1_Anim;

VOID IK1_AnimInit( HWND hWnd )
{  
  IK1_Anim.hWnd = hWnd;
  IK1_RndInit(hWnd);
  IK1_Anim.hDC = IK1_hRndDC;

  IK1_Anim.W = IK1_RndFrameW;
  IK1_Anim.H = IK1_RndFrameH;
  IK1_TimerInit();
}

VOID IK1_AnimClose( VOID )
{  
  INT i;
  
  for (i = 0; i < IK1_Anim.NumOfUnits; i++)
  {
    IK1_Anim.Units[i]->Close(IK1_Anim.Units[i], &IK1_Anim);
    free(IK1_Anim.Units[i]);
  }
  IK1_Anim.NumOfUnits = 0;
  IK1_RndClose();
}

VOID IK1_AnimResize( INT W, INT H )
{  
  IK1_RndResize(W, H);
  IK1_Anim.W = W;
  IK1_Anim.H = H;
}

VOID IK1_AnimCopyFrame( VOID )
{  
  IK1_RndCopyFrame();
}

VOID IK1_AnimRender( VOID )
{  
  INT i;

  /*timer*/
  IK1_TimerResponse();

  for (i = 0; i < IK1_Anim.NumOfUnits; i++)
    IK1_Anim.Units[i]->Response(IK1_Anim.Units[i], &IK1_Anim);
  IK1_RndStart();
  for (i = 0; i < IK1_Anim.NumOfUnits; i++)
    IK1_Anim.Units[i]->Render(IK1_Anim.Units[i], &IK1_Anim);
  IK1_RndEnd();
}

VOID IK1_AnimUnitAdd( ik1UNIT *Uni )
{  
  if (IK1_Anim.NumOfUnits < IK1_MAX_UNITS)
    IK1_Anim.Units[IK1_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &IK1_Anim);
}
/* end of "anim.c" file */