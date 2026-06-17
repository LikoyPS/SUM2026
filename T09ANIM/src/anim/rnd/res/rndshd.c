#include <stdio.h>
#include <time.h>
 
#include "anim/rnd/res/rndres.h"
 
ik1SHADER IK1_RndShaders[IK1_MAX_SHADERS];
INT IK1_RndShadersSize;

/***
 * Base shaders functions
 ***/
 
/* Save log to file function.
 * ARGUMENTS:
 *   - shader prefix:
 *       CHAR *FileNamePrefix;
 *   - shader name:
 *       CHAR *ShaderName;
 *   - error text:
 *       CHAR *Text;
 * RETURNS: None.
 */
VOID IK1_RndShdLog( CHAR *FileNamePrefix, CHAR *ShaderName, CHAR *Text )
{
  FILE *F;
 
  if ((F = fopen("bin/shaders/shd{30}ik1.log", "a")) == NULL)
    return;
  fprintf(F, "%s : %s\n%s\n\n", FileNamePrefix, ShaderName, Text);
  fclose(F);
} /* End of 'IK1_RndLoadTextFromFile' function */

/* Load shader text from file function.
 * ARGUMENTS:
 *   - text file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (CHAR *) load text.
 */
CHAR * IK1_RndLoadTextFromFile( CHAR *FileName )
{
  FILE *F;
  INT flen;
  CHAR *txt;
 
  if ((F = fopen(FileName, "rb")) == NULL)
    return NULL;
 
  /* Measure file length */
  fseek(F, 0, SEEK_END);
  flen = ftell(F);
 
  /* Allocate memory */
  if ((txt = malloc(flen + 1)) == NULL)
  {
    fclose(F);
    return NULL;
  }
  memset(txt, 0, flen + 1);
 
  /* Load text */
  rewind(F);
  fread(txt, 1, flen, F);
 
  fclose(F);
  return txt;
} /* End of 'IK1_RndLoadTextFromFile' function */

/* Load shader program function.
 * ARGUMENTS:
 *   - shader folder prefix (in 'BIN/SHADERS/***'):
 *       CHAR *FileNamePrefix;
 * RETUNS:
 *   (UINT) load shader program Id.
 */
static UINT IK1_RndShdLoad( CHAR *FileNamePrefix )
{
  CHAR *txt;
  struct
  {
    CHAR *Name;  /* Shader name (e.g. "VERT") */
    INT Type;    /* Shader type (e.g. GL_VERTEX_SHADER) */
    INT Id;      /* Created shader Id */
  } shd[] =
  {
    {"VERT", GL_VERTEX_SHADER, 0},
    {"FRAG", GL_FRAGMENT_SHADER, 0},
  };
  INT res, i, NoofS = sizeof(shd) / sizeof(shd[0]);
  UINT prg;
  BOOL is_ok = TRUE;
  static CHAR Buf[10000];
 
  for (i = 0; i < NoofS; i++)
  {
    /* Build shader name */
    sprintf(Buf, "bin/shaders/%s/%s.glsl", FileNamePrefix, shd[i].Name);
 
    /* Load shader text from file */
    txt = IK1_RndLoadTextFromFile(Buf);
    if (txt == NULL)
    {
      IK1_RndShdLog(FileNamePrefix, shd[i].Name, "Error load file");
      is_ok = FALSE;
      break;
    }
    /* Create shader */
    shd[i].Id = glCreateShader(shd[i].Type);
    if (shd[i].Id == 0)
    {
      free(txt);
      IK1_RndShdLog(FileNamePrefix, shd[i].Name, "Error shader create");
      is_ok = FALSE;
      break;
    }
    /* Send shader source text to OpenGL */
    glShaderSource(shd[i].Id, 1, &txt, NULL);
    free(txt);
 
    /* Compile shader */
    glCompileShader(shd[i].Id);
 
    /* Errors handle */
    glGetShaderiv(shd[i].Id, GL_COMPILE_STATUS, &res);
    if (res != 1)
    {
      glGetShaderInfoLog(shd[i].Id, sizeof(Buf), &res, Buf);
      IK1_RndShdLog(FileNamePrefix, shd[i].Name, Buf);
      is_ok = FALSE;
      break;
    }
  }
 
  /* Create program */
  if (is_ok)
    if ((prg = glCreateProgram()) == 0)
    {
      IK1_RndShdLog(FileNamePrefix, "PROG", "Error create program");
      is_ok = FALSE;
    }
    else
    {
      /* Attach shader programs */
      for (i = 0; i < NoofS; i++)
        if (shd[i].Id != 0)
          glAttachShader(prg, shd[i].Id);
      /* Link program */
      glLinkProgram(prg);
      /* Errors handle */
      glGetProgramiv(shd[i].Id, GL_LINK_STATUS, &res);
      if (res != 1)
      {
        glGetProgramInfoLog(shd[i].Id, sizeof(Buf), &res, Buf);
        IK1_RndShdLog(FileNamePrefix, "PROG", Buf);
        is_ok = FALSE;
      }
    }
 
  /* Handle errors */
  if (!is_ok)
  {
    /* Delete all shaders */
    for (i = 0; i < NoofS; i++)
      if (shd[i].Id != 0)
      {
        if (prg != 0)
          glDetachShader(prg, shd[i].Id);
        glDeleteShader(shd[i].Id);
      }
    /* Delete program */
    if (prg != 0)
      glDeleteProgram(prg);
    prg = 0;
  }
  return prg;
} /* End of 'IK1_RndShdLoad' function */

/* Delete shader program function.
 * ARGUMENTS:
 *   - shader program Id:
 *       UINT ProgId;
 * RETUNS: None.
 */
VOID IK1_RndShdFree( UINT ProgId )
{
  INT shds[5], n, i;
 
  if (ProgId == 0 || !glIsProgram(ProgId))
    return;
 
  glGetAttachedShaders(ProgId, 5, &n, shds);
  for (i = 0; i < n; i++)
    if (glIsShader(shds[i]))
    {
      glDetachShader(ProgId, shds[i]);
      glDeleteShader(shds[i]);
    }
  glDeleteProgram(ProgId);
} /* End of 'IK1_RndShdFree' function */

/* Shaders initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID IK1_RndShdInit( VOID )
{
  IK1_RndShdAdd("default");
} /* End of 'IK1_RndResInit' function */
 
/* Shaders deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID IK1_RndShdClose( VOID )
{
  INT i;
 
  for (i = 0; i < IK1_RndShadersSize; i++)
    IK1_RndShdFree(IK1_RndShaders[i].ProgId);
  IK1_RndShadersSize = 0;
} /* End of 'IK1_RndResInit' function */
 
/* Update from file all load shaders function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID IK1_RndShdUpdate( VOID )
{
  INT t = clock(), i;
  static INT old_time;
 
  if (t - old_time > 2 * CLOCKS_PER_SEC)
  {
    for (i = 0; i < IK1_RndShadersSize; i++)
    {
      IK1_RndShdFree(IK1_RndShaders[i].ProgId);
      IK1_RndShaders[i].ProgId = IK1_RndShdLoad(IK1_RndShaders[i].Name);
    }
    /*
    IK1_RndShdFree(IK1_RndProgId);
    IK1_RndProgId = IK1_RndShdLoad("default");
    */
    old_time = t;
  }
} /* End of 'VG4_RndShdUpdate' function */

/* Add shader to stock from file function.
 * ARGUMENTS:
 *   - shader file path to load:
 *       CHAR *ShaderFileNamePrefix;
 * RETURNS:
 *   (INT) new shader stock number.
 */
INT IK1_RndShdAdd( CHAR *ShaderFileNamePrefix )
{
  INT i;
 
  for (i = 0; i < IK1_RndShadersSize; i++)
    if (strcmp(ShaderFileNamePrefix, IK1_RndShaders[i].Name) == 0)
      return i;
  if (IK1_RndShadersSize >= IK1_MAX_SHADERS)
    return 0;
  strncpy(IK1_RndShaders[IK1_RndShadersSize].Name, ShaderFileNamePrefix, IK1_STR_MAX - 1);
  IK1_RndShaders[IK1_RndShadersSize].ProgId = IK1_RndShdLoad(ShaderFileNamePrefix);
  return IK1_RndShadersSize++;
} /* End of 'IK1_RndShdAdd' function */