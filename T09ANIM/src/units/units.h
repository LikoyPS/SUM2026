#include "anim\anim.h"

typedef struct tagik1UINT_CONTROL
{
  IK1_UNIT_BASE_FIELDS;
  VEC CamLoc, CamAt;
  DBL Speed;
} ik1UNIT_CONTROL;

ik1UNIT * IK1_UnitCreateBall( VOID );
ik1UNIT * IK1_UnitCreateControl( VOID );
ik1UNIT * IK1_UnitCreateTexture( VOID );

extern IK1_MouseWheel;

/* prototipes func  */