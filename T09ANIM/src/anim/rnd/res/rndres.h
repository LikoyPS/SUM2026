#ifndef __rndres_h_
#define __rndres_h_
#include "def.h"

#define IK1_MAX_SHADERS 30
#define IK1_STR_MAX 40
 
typedef struct tagik1SHADER
{
  CHAR Name[IK1_STR_MAX]; /* Shader filename prefix */
  UINT ProgId;            /* Shader program Id */
} ik1SHADER;

/* Array of shaders */
ik1SHADER IK1_RndShaders[IK1_MAX_SHADERS];
/* Shadres array store size */
INT IK1_RndShadersSize;



VOID IK1_RndResInit( VOID );
VOID IK1_RndResClose( VOID );

VOID IK1_RndShdInit( VOID );
VOID IK1_RndShdClose( VOID );
INT IK1_RndShdAdd( CHAR *ShaderFileNamePrefix );
VOID IK1_RndShdUpdate( VOID );
VOID IK1_RndShdFree( UINT ProgId );
CHAR * IK1_RndLoadTextFromFile( CHAR *FileName );
VOID IK1_RndShdLog( CHAR *FileNamePrefix, CHAR *ShaderName, CHAR *Text );

#endif __rndres_h_