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
#define IK1_MAX_TEXTURES 300
extern ik1TEXTURE IK1_RndTextures[IK1_MAX_TEXTURES];
extern INT IK1_RndTexturesSize;

VOID IK1_RndTexInit( VOID );
VOID IK1_RndTexClose( VOID );
INT IK1_RndTexAdd( CHAR *FileName );
INT IK1_RndTexAddImg( CHAR *FileName, INT W, INT H, DWORD *Bits );




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

static struct
{
  char *Name;
  float amb[3], dif[3], spec[3], shin;
} MatLib[] =
{
  {"Black Plastic", {0.0, 0.0, 0.0},             {0.01, 0.01, 0.01},           {0.5, 0.5, 0.5},               32},
  {"Brass",         {0.329412,0.223529,0.027451}, {0.780392,0.568627,0.113725}, {0.992157,0.941176,0.807843}, 27.8974},
  {"Bronze",        {0.2125,0.1275,0.054},       {0.714,0.4284,0.18144},       {0.393548,0.271906,0.166721},  25.6},
  {"Chrome",        {0.25, 0.25, 0.25},          {0.4, 0.4, 0.4},              {0.774597, 0.774597, 0.774597}, 76.8},
  {"Copper",        {0.19125,0.0735,0.0225},     {0.7038,0.27048,0.0828},      {0.256777,0.137622,0.086014},  12.8},
  {"Gold",          {0.24725,0.1995,0.0745},     {0.75164,0.60648,0.22648},    {0.628281,0.555802,0.366065},  51.2},
  {"Peweter",       {0.10588,0.058824,0.113725}, {0.427451,0.470588,0.541176}, {0.3333,0.3333,0.521569},      9.84615},
  {"Silver",        {0.19225,0.19225,0.19225},   {0.50754,0.50754,0.50754},    {0.508273,0.508273,0.508273},  51.2},
  {"Polished Silver", {0.23125,0.23125,0.23125}, {0.2775,0.2775,0.2775},       {0.773911,0.773911,0.773911},  89.6},
  {"Turquoise",     {0.1, 0.18725, 0.1745},      {0.396, 0.74151, 0.69102},    {0.297254, 0.30829, 0.306678}, 12.8},
  {"Ruby",          {0.1745, 0.01175, 0.01175},  {0.61424, 0.04136, 0.04136},  {0.727811, 0.626959, 0.626959}, 76.8},
  {"Polished Gold", {0.24725, 0.2245, 0.0645},   {0.34615, 0.3143, 0.0903},    {0.797357, 0.723991, 0.208006}, 83.2},
  {"Polished Bronze", {0.25, 0.148, 0.06475},    {0.4, 0.2368, 0.1036},        {0.774597, 0.458561, 0.200621}, 76.8},
  {"Polished Copper", {0.2295, 0.08825, 0.0275}, {0.5508, 0.2118, 0.066},      {0.580594, 0.223257, 0.0695701}, 51.2},
  {"Jade",          {0.135, 0.2225, 0.1575},     {0.135, 0.2225, 0.1575},      {0.316228, 0.316228, 0.316228}, 12.8},
  {"Obsidian",      {0.05375, 0.05, 0.06625},    {0.18275, 0.17, 0.22525},     {0.332741, 0.328634, 0.346435}, 38.4},
  {"Pearl",         {0.25, 0.20725, 0.20725},    {1.0, 0.829, 0.829},          {0.296648, 0.296648, 0.296648}, 11.264},
  {"Emerald",       {0.0215, 0.1745, 0.0215},    {0.07568, 0.61424, 0.07568},  {0.633, 0.727811, 0.633},       76.8},
  {"Black Plastic", {0.0, 0.0, 0.0},             {0.01, 0.01, 0.01},           {0.5, 0.5, 0.5},                32.0},
  {"Black Rubber",  {0.02, 0.02, 0.02},          {0.01, 0.01, 0.01},           {0.4, 0.4, 0.4},                10.0},
};

#define MAT_N (sizeof(MatLib) / sizeof(MatLib[0]))

#endif __rndres_h_