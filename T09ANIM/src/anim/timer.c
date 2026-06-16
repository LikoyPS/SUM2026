/* FILE NAME: mth.h
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: IK1
 * DATE: 09.06.2026
 */
#include <time.h>
#include <windows.h>
#include "anim.h"

typedef unsigned long long UINT64;

DOUBLE GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
  IK1_Time, IK1_DeltaTime,             /* Time with pause and interframe interval */
  IK1_FPS;                         /* Frames per second value */
BOOL
  IK1_IsPause;                     /* Pause flag */

static UINT64
  StartTime,    /* Start program time */
  OldTime,      /* Previous frame time */
  OldTimeFPS,   /* Old time FPS measurement */
  PauseTime,    /* Time during pause period */
  TimePerSec,   /* Timer resolution */
  FrameCounter; /* Frames counter */

VOID IK1_TimerInit( VOID )
{
  StartTime = OldTime = OldTimeFPS = clock();
  PauseTime = 0;
  FrameCounter = 0;
  IK1_IsPause = FALSE;
  IK1_Time = IK1_DeltaTime = 0;
  IK1_FPS = 30;
} 

VOID IK1_TimerResponse( VOID )
{
  LARGE_INTEGER t;
 
  QueryPerformanceCounter(&t);
 
  /* Global time */
  IK1_Anim.Time = (DOUBLE)(t.QuadPart - StartTime) / TimePerSec;
  IK1_Anim.DeltaTime = (DOUBLE)(t.QuadPart - OldTime) / TimePerSec;

  IK1_Anim.Time = clock();
  
  /* Time with pause */
  if (!IK1_IsPause)
  {
    IK1_Anim.Time = (DOUBLE)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
    IK1_Anim.DeltaTime = GlobalDeltaTime;
  }
  else
  {
    IK1_Anim.DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
 
  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > 3 * TimePerSec)
  {
    IK1_Anim.FPS = FrameCounter * TimePerSec / (DOUBLE)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
}