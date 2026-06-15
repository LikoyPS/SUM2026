/**/
#ifndef __timer_h_
#define __timer_h_
#include <time.h>
#include <windows.h>

typedef unsigned long long UINT64;

DOUBLE
  GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
  Time, DeltaTime,             /* Time with pause and interframe interval */
  FPS;                         /* Frames per second value */
BOOL GLB_IsPause;                     /* Pause flag */

#endif