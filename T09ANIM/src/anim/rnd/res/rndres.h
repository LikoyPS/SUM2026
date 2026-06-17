#ifndef __rndres_h_
#define __rndres_h_
#include "def.h"

#define IK1_STR_MAX 40
 
typedef struct tagik1SHADER
{
  CHAR Name[IK1_STR_MAX]; /* Shader filename prefix */
  UINT ProgId;            /* Shader program Id */
} ik1SHADER;

typedef struct tagik1MATERIAL
{
  CHAR Name[IK1_STR_MAX]; /* Material name */
 
  /* Illumination coefficients */    
  VEC Ka, Kd, Ks;           /* Ambient, diffuse, specular coefficients */
  FLT Ph;                   /* Phong power coefficient */
 
  FLT Trans;                /* Transparency factor */
 
  INT Tex[8];               /* Texture references from texture table (or -1) */
 
  INT ShdNo;                /* Shader number in shader table */
} ik1MATERIAL;

typedef struct tagik1TEXTURE
{
  CHAR Name[IK1_STR_MAX]; /* Texture name */
  INT W, H;               /* Texture size in pixels */
  UINT TexId;             /* OpenGL texture Id */ 
} ik1TEXTURE;


/***
* shaders handle
***/
#define IK1_MAX_SHADERS 30
extern ik1SHADER IK1_RndShaders[IK1_MAX_SHADERS];
extern INT IK1_RndShadersSize;

VOID IK1_RndShdInit( VOID );
VOID IK1_RndShdClose( VOID );
INT IK1_RndShdAdd( CHAR *ShaderFileNamePrefix );
VOID IK1_RndShdUpdate( VOID );
VOID IK1_RndShdFree( UINT ProgId );
CHAR * IK1_RndLoadTextFromFile( CHAR *FileName );
VOID IK1_RndShdLog( CHAR *FileNamePrefix, CHAR *ShaderName, CHAR *Text );

/***
* texturies handle
***/
#define IK1_MAX_TEX 300
extern ik1TEXTURE IK1_RndTextures[IK1_MAX_TEX];
extern INT IK1_RndTexturesSize;

VOID IK1_RndTexInit( VOID );
VOID IK1_RndTexClose( VOID );



/***
* materials handle
***/
#define IK1_MAX_MATERIALS 300
extern ik1MATERIAL IK1_RndMaterials[IK1_MAX_MATERIALS];
extern INT IK1_RndMaterialsSize;

VOID IK1_RndMtlInit( VOID );
VOID IK1_RndMtlClose( VOID );
ik1MATERIAL IK1_RndMtlGetDef( VOID );
INT IK1_RndMtlAdd( ik1MATERIAL *Mtl );
UINT IK1_RndMtlApply( INT MtlNo );


VOID IK1_RndResInit( VOID );
VOID IK1_RndResClose( VOID );



#endif __rndres_h_