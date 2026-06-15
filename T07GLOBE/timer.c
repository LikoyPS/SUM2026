#include <time.h>
#include <windows.h>
#include "timer.h"

static UINT64
  StartTime,    /* Start program time */
  OldTime,      /* Previous frame time */
  OldTimeFPS,   /* Old time FPS measurement */
  PauseTime,    /* Time during pause period */
  TimePerSec,   /* Timer resolution */
  FrameCounter; /* Frames counter */

VOID TimerInit( VOID )
{
  StartTime = OldTime = OldTimeFPS = clock();
  PauseTime = 0;
  FrameCounter = 0;
  GLB_IsPause = FALSE;
  Time = DeltaTime = 0;
  FPS = 30;
}

VOID TimerResponse( VOID )
{
  LARGE_INTEGER t;
 
  QueryPerformanceCounter(&t);
 
  /* Global time */
  GlobalTime = (DOUBLE)(t.QuadPart - StartTime) / TimePerSec;
  GlobalDeltaTime = (DOUBLE)(t.QuadPart - OldTime) / TimePerSec;
  /* Time with pause */
  if (!GLB_IsPause)
  {
    Time = (DOUBLE)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
    DeltaTime = GlobalDeltaTime;
  }
  else
  {
    DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
 
  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > 3 * TimePerSec)
  {
    FPS = FrameCounter * TimePerSec / (DOUBLE)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
}