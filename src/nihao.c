/*******************************************************************************
** nihao.c (startup functions)
*******************************************************************************/

#include <SDL2/SDL.h>

#ifdef VT2_MAC_OSX
  #include <SDL2_mixer/SDL_mixer.h>
#else
  #include <SDL2/SDL_mixer.h>
#endif

#include <glad/glad.h>

#include <stdio.h>

#include "grafx.h"

/*******************************************************************************
** nihao_window()
*******************************************************************************/
short int nihao_window()
{
  /* set opengl attributes */
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  /* set opengl version to 3.3 */
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  /* initialize fullscreen flag */
  G_fullscreen_flag = 0x00;

  /* initialize window size */
  G_window_w = GRAFX_WINDOW_WIDTH_OPTION_1;
  G_window_h = GRAFX_WINDOW_HEIGHT_OPTION_1;

  /* set up viewport width and height */
  G_viewport_w = G_window_w;
  G_viewport_h = G_window_h;

  /* create window */
  G_sdl_window = SDL_CreateWindow("Vampiric Tower 2",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  G_window_w,
                                  G_window_h,
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

  if (G_sdl_window == NULL)
  {
    printf("Failed to create window: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  /* determine desktop resolution */
  if (grafx_check_desktop_resolution())
    return 1;

  grafx_setup_desktop_resolution();

  /* testing: output available display modes */
  /*
  for (i = 0; i < SDL_GetNumDisplayModes(0); i++)
  {
    SDL_GetDisplayMode(0, i, &mode);
    fprintf(stdout, "Display Mode %d: %dx%d\n", i, mode.w, mode.h);
  }
  */

  return 0;
}

/*******************************************************************************
** nihao_mixer()
*******************************************************************************/
short int nihao_mixer()
{
  int initialized_flags;

  /* initialize sdl mixer */
  initialized_flags = Mix_Init(MIX_INIT_MOD);

  if ((initialized_flags & MIX_INIT_MOD) != MIX_INIT_MOD)
  {
    printf("Failed to initialize SDL_mixer MOD: %s\n", Mix_GetError());
    return 1;
  }

  if (Mix_OpenAudio(22050, AUDIO_S16LSB, 2, 512) != 0)
  {
    printf("Failed to initialize SDL_mixer API: %s\n", Mix_GetError());
    return 1;
  }

  return 0;
}

/*******************************************************************************
** nihao_opengl()
*******************************************************************************/
short int nihao_opengl()
{
  SDL_GLContext context;

  /* create opengl context */
  context = SDL_GL_CreateContext(G_sdl_window);

  if (context == NULL)
  {
    printf("Failed to create OpenGL context: %s\n", SDL_GetError());
    return 1;
  }

  SDL_GL_MakeCurrent(G_sdl_window, context);

  /* setup vsync */
  if (SDL_GL_SetSwapInterval(1) != 0)
  {
    printf("Failed to set vsync: %s\n", SDL_GetError());
  }

  /* obtain opengl function pointers with glad */
  if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress))
  {
    printf("Failed to obtain OpenGL function pointers.\n");
    return 1;
  }

  /* opengl settings initialization */
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glFrontFace(GL_CCW);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);

  return 0;
}

