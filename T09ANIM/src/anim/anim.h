/* start of "anim.h" file   IK1 */

#ifndef __anim_h_
#define __anim_h_

#include <time.h>

#include "rnd/rnd.h"

#define IK1_MAX_UNITS 3000

typedef struct tagik1UNIT ik1UNIT;
typedef struct tagik1ANIM ik1ANIM;

struct tagik1ANIM
{
  HWND hWnd;                      
  HDC hDC;                        
  INT W, H;                       
 
  ik1UNIT * Units[IK1_MAX_UNITS]; 
  INT NumOfUnits;                 
 
  DBL
    GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    Time, DeltaTime,             /* Time with pause and interframe interval */
    FPS;                         /* Frames per second value */
  BOOL
    IsPause;                      /* Pause flag */
  BOOL IsActive;

  BYTE Keys[256];      /* Keyboard press states */
  BYTE KeysClick[256]; /* Keyboard click states */
  INT Mx, My, Mz, Mdx, Mdy, Mdz;
};

extern ik1ANIM IK1_Anim;

#define IK1_UNIT_BASE_FIELDS \
  VOID (*Init)( ik1UNIT *Uni, ik1ANIM *Ani ); \
  VOID (*Close)( ik1UNIT *Uni, ik1ANIM *Ani ); \
  VOID (*Response)( ik1UNIT *Uni, ik1ANIM *Ani ); \
  VOID (*Render)( ik1UNIT *Uni, ik1ANIM *Ani )

struct tagik1UNIT
{
  IK1_UNIT_BASE_FIELDS;
};

VOID IK1_AnimInit( HWND hWnd );
VOID IK1_AnimClose( VOID );
VOID IK1_AnimResize( INT W, INT H );
VOID IK1_AnimCopyFrame( VOID );
VOID IK1_AnimRender( VOID );
VOID IK1_AnimDoExit( VOID );

VOID IK1_AnimUnitAdd( ik1UNIT *Uni );
ik1UNIT * IK1_AnimUnitCreate( INT Size );

VOID IK1_KeyboardInit( VOID );
VOID IK1_KeyboardResponse( VOID );
VOID IK1_AnimInputInit( VOID );
VOID IK1_AnimInputResponse( VOID );

typedef unsigned long long UINT64;

extern DOUBLE GlobalTime, GlobalDeltaTime, Time, DeltaTime, FPS;
extern BOOL
  IsPause;

/* VOID Timer( VOID ); */

VOID IK1_TimerInit( VOID );

VOID IK1_TimerResponse( VOID );

#endif __anim_h_
/* start of "anim.h" file */
