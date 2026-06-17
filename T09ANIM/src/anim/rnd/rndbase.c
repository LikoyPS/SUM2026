/* FILE NAME: rndbase.C
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: IK1
 * DATE: 09.06.2026
 */

#include "rnd.h"

#include <wglew.h>
#include <gl/wglext.h>

#pragma comment(lib, "opengl32")


VOID IK1_RndInit( HWND hWnd )
{
  INT nums = 0;
  INT i;
  PIXELFORMATDESCRIPTOR pfd = {0};
  HGLRC hRC;
  INT PixelAttribs[] =
  {
    WGL_DRAW_TO_WINDOW_ARB, TRUE,
    WGL_SUPPORT_OPENGL_ARB, TRUE,
    WGL_DOUBLE_BUFFER_ARB, TRUE,
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_DEPTH_BITS_ARB, 32,
    0
  };
  INT ContextAttribs[] =
  {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
    WGL_CONTEXT_MINOR_VERSION_ARB, 6,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
                                  /* WGL_CONTEXT_CORE_PROFILE_BIT_ARB, */
    0
  };

  IK1_hRndWnd = hWnd;
 
  /* Prepare frame compatible device contesxt */
  IK1_hRndDC = GetDC(hWnd);
 
  /* OpenGL init: pixel format setup */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(IK1_hRndDC, &pfd);
 
  DescribePixelFormat(IK1_hRndDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(IK1_hRndDC, i, &pfd);

   /* OpenGL init: rendering context setup */
  IK1_hRndGLRC = wglCreateContext(IK1_hRndDC);
  wglMakeCurrent(IK1_hRndDC, IK1_hRndGLRC);

  if (glewInit() != GLEW_OK)
    exit(0);

  wglChoosePixelFormatARB(IK1_hRndDC, PixelAttribs, NULL, 1, &i, &nums); /* nums - ? */
  hRC = wglCreateContextAttribsARB(IK1_hRndDC, NULL, ContextAttribs);
 
  wglMakeCurrent(NULL, NULL);                                           
  wglDeleteContext(IK1_hRndGLRC);
 
  IK1_hRndGLRC = hRC;
  wglMakeCurrent(IK1_hRndDC, IK1_hRndGLRC); 

#ifndef NDEBUG
  OutputDebugString(glGetString(GL_VERSION));
  OutputDebugString("\n");
  OutputDebugString(glGetString(GL_VENDOR));
  OutputDebugString("\n");
  OutputDebugString(glGetString(GL_RENDERER));
  OutputDebugString("\n");

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(glDebugOutput, NULL);
#endif /* NDEBUG */
    
  /* Render parameters setup */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_PRIMITIVE_RESTART);
  wglSwapIntervalEXT(0);

  IK1_RndProjSize = 0.1;
  IK1_RndProjDist = IK1_RndProjSize;
  IK1_RndProjFarClip = 3000;
  IK1_RndFrameW = 47;
  IK1_RndFrameH = 47;
  IK1_RndCamSet(VecSet(5, 5, 5), VecSet(0, 0, 0), VecSet(0, 1, 0));


  IK1_RndResize(47, 47);
  IK1_RndCamSet(VecSet1(8), VecSet1(0), VecSet(0, 1, 0));

  IK1_RndResInit();
}

VOID IK1_RndClose( VOID )
{
  IK1_RndResClose();
  
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(IK1_hRndGLRC);
  ReleaseDC(IK1_hRndWnd, IK1_hRndDC);
}

VOID IK1_RndResize( INT W, INT H )
{
  glViewport(0, 0, W, H);
  
  IK1_RndFrameW = W;
  IK1_RndFrameH = H;
 
  IK1_RndProjSet();
}

VOID IK1_RndCopyFrame( VOID )
{
  SwapBuffers(IK1_hRndDC);
}


VOID IK1_RndStart( VOID )
{
  VEC4 ClearColor = {0.30, 0.47, 0.8, 1};
  FLT DepthClearValue = 1;

  IK1_RndShdUpdate();

  /* Clear frame */
  glClearBufferfv(GL_COLOR, 0, &ClearColor.X);
  glClearBufferfv(GL_DEPTH, 0, &DepthClearValue);
}

VOID IK1_RndEnd( VOID )
{
  glFinish();
}

VOID IK1_RndProjSet( VOID )
{
  DBL rx, ry;
 
  rx = ry = IK1_RndProjSize;
  /* Correct aspect ratio */
  if (IK1_RndFrameW > IK1_RndFrameH)
    rx *= (DBL)IK1_RndFrameW / IK1_RndFrameH;
  else
    ry *= (DBL)IK1_RndFrameH / IK1_RndFrameW;
  IK1_RndMatrProj =
    MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
      IK1_RndProjDist, IK1_RndProjFarClip);
  IK1_RndMatrVP = MatrMulMatr(IK1_RndMatrView, IK1_RndMatrProj);
}
  
VOID IK1_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  IK1_RndMatrView = MatrView(Loc, At, Up);
  IK1_RndMatrVP = MatrMulMatr(IK1_RndMatrView, IK1_RndMatrProj);
}