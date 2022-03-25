/*******************************************************************************
** Vampiric Tower 2 - Michael Behrens 2017-2021
*******************************************************************************/

/*******************************************************************************
** main.c
*******************************************************************************/

#include <SDL2/SDL.h>

#ifdef VT2_MAC_OSX
  #include <SDL2_mixer/SDL_mixer.h>
#else
  #include <SDL2/SDL_mixer.h>
#endif

#include <glad/glad.h>

#include <stdio.h>

#include "collide.h"
#include "controls.h"
#include "doremi.h"
#include "global.h"
#include "grafx.h"
#include "level.h"
#include "logic.h"
#include "loop.h"
#include "nihao.h"
#include "pairtree.h"
#include "render.h"
#include "savegame.h"
#include "texture.h"
#include "world.h"

/*******************************************************************************
** main()
*******************************************************************************/
int main(int argc, char *argv[])
{
  int           i;
  SDL_Event     event;
  Uint32        ticks_last_update;
  Uint32        ticks_current;
  unsigned char minimization_flag;

  /* print command line arguments */
  for (i = 1; i < argc; i++)
  {
    fprintf(stdout, "Command line argument: %s\n", argv[i]);
  }

  /* initialize sdl */
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
  {
    printf("Failed to initialize SDL: %s\n", SDL_GetError());
    return 0;
  }

  /* load opengl library */
  if (SDL_GL_LoadLibrary(NULL))
  {
    printf("Failed to load OpenGL Library: %s\n", SDL_GetError());
    goto cleanup_sdl;
  }

  /* create window */
  if (nihao_window())
  {
    fprintf(stdout, "Failed to create window. Exiting...\n");
    goto cleanup_gl_library;
  }

  /* get paths */
  globals_init_paths();

  if (globals_obtain_base_paths())
  {
    fprintf(stdout, "Failed to obtain Base paths. Exiting...\n");
    goto cleanup_window;
  }

  if (globals_obtain_preferences_path())
  {
    fprintf(stdout, "Failed to obtain Preferences path. Exiting...\n");
    goto cleanup_paths;
  }

  /* initialize sdl mixer */
  if (nihao_mixer())
  {
    fprintf(stdout, "Failed to initialize SDL_mixer. Exiting...\n");
    goto cleanup_paths;
  }

  /* initialize opengl */
  if (nihao_opengl())
  {
    fprintf(stdout, "Failed to initialize OpenGL. Exiting...\n");
    goto cleanup_mixer;
  }

  /* initialize opengl objects */
  if (grafx_create_opengl_objects())
  {
    fprintf(stdout, "Failed to initialize OpenGL objects. Exiting...\n");
    goto cleanup_opengl;
  }

  /* initialize opengl textures */
  if (textures_init())
  {
    fprintf(stdout, "Failed to initialize textures. Exiting...\n");
    goto cleanup_opengl_objects;
  }

  /* initialize world */
  if (world_init())
  {
    fprintf(stdout, "Failed to initialize world. Exiting...\n");
    goto cleanup_textures;
  }

  /* initialize collision grid */
  if (collide_grid_init())
  {
    fprintf(stdout, "Failed to initialize collision grid. Exiting...\n");
    goto cleanup_world;
  }

  /* initialize pair trees and lists */
  if (pair_trees_and_lists_init())
  {
    fprintf(stdout, "Failed to initialize pair trees and lists. Exiting...\n");
    goto cleanup_collision_grid;
  }

  /* initialize globals */
  globals_init();

  /* initialize controller flags */
  controls_init();

  /* generate texture coordinate lookup tables */
  render_generate_tables();

  /* load all textures */
  if (texture_load_all_from_file(G_path_gfx_data))
  {
    fprintf(stdout, "Error loading gfx data. Exiting...\n");
    goto cleanup_all;
  }

  /* load all sfx data */
  doremi_init_all_sfx();

  if (doremi_load_all_sfx_from_file(G_path_sfx_data))
  {
    fprintf(stdout, "Error loading sfx data. Exiting...\n");
    goto cleanup_all;
  }

  /* initialze music */
  doremi_init_music();

  /* load all level data */
  if (level_load_all_from_file(G_path_world_data))
  {
    fprintf(stdout, "Error loading level data. Exiting...\n");
    goto cleanup_all;
  }

  /* initialize save game */
  save_game_init();

  /* initialize game mode */
  G_game_mode = GAME_MODE_TITLE_SCREEN;
  doremi_play_music(MUSIC_TYPE_MAIN_MENU);

  /* initialize ticks */
  ticks_current = SDL_GetTicks();
  ticks_last_update = ticks_current;

  /* initialize minimization flag */
  minimization_flag = 0x00;

  /* main loop */
  while (1)
  {
    /* process sdl events */
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        goto cleanup_all;
      }

      if (event.type == SDL_WINDOWEVENT)
      {
        if ((event.window.event == SDL_WINDOWEVENT_MINIMIZED) ||
            (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST))
        {
          doremi_pause_music();
          minimization_flag = 0x01;
        }

        if ((event.window.event == SDL_WINDOWEVENT_RESTORED) ||
            (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED))
        {
          doremi_unpause_music();
          minimization_flag = 0x00;
          ticks_last_update = SDL_GetTicks();
        }

        if (event.window.event == SDL_WINDOWEVENT_MOVED)
        {
          grafx_setup_desktop_resolution();
        }
      }
    }

    /* make sure the window is not minimized */
    if (minimization_flag == 0x01)
      continue;

    /* update ticks */
    ticks_current = SDL_GetTicks();

    /* check for tick wraparound (~49 days of hot vampire action!) */
    if (ticks_current < ticks_last_update)
      ticks_last_update = 0;

    /* check if a new frame has elapsed */
    if ((ticks_current - ticks_last_update) >= (1000 / 60))
    {
      /* quit */
      if (G_game_mode == GAME_MODE_QUIT)
      {
        goto cleanup_all;
      }

      /* read keyboard */
      controls_update_from_keyboard();

      /* toggle fullscreen */
      if ((G_current_hud_flags & CONTROLS_HUD_FLAG_FULLSCREEN) &&
          (!(G_last_hud_flags & CONTROLS_HUD_FLAG_FULLSCREEN)))
      {
        /* switch to windowed */
        if (G_fullscreen_flag == 0x01)
        {
          if (SDL_SetWindowFullscreen(G_sdl_window, 0) == 0)
          {
            SDL_SetWindowSize(G_sdl_window, G_window_w, G_window_h);
            SDL_ShowCursor(SDL_ENABLE);
            G_fullscreen_flag = 0x00;
            grafx_setup_windowed();
          }
        }
        /* switch to fullscreen */
        else if (grafx_check_desktop_resolution() == 0)
        {
          if (SDL_SetWindowFullscreen(G_sdl_window, SDL_WINDOW_FULLSCREEN_DESKTOP) == 0)
          {
            SDL_ShowCursor(SDL_DISABLE);
            G_fullscreen_flag = 0x01;
            grafx_setup_fullscreen();
          }
        }
      }

      /* process frame */
      loop_process_frame();

      /* update time elapsed */
      if ((G_game_mode == GAME_MODE_PLAYING) &&
          (G_game_state_flags & GLOBAL_GAME_STATE_FLAG_STARTED) && 
          (!(G_game_state_flags & GLOBAL_GAME_STATE_FLAG_DEAD)) &&
          (!(G_game_state_flags & GLOBAL_GAME_STATE_FLAG_BLOOD_LOST)) &&
          (!(G_game_state_flags & GLOBAL_GAME_STATE_FLAG_EVIL_EYE_CAST)) &&
          (!(G_game_state_flags & GLOBAL_GAME_STATE_FLAG_LEVEL_COMPLETE)))
      {
        /* update time elapsed */
        if (G_time_elapsed_ms < 255000)
          G_time_elapsed_ms += ticks_current - ticks_last_update;

        /* bound time elapsed */
        if (G_time_elapsed_ms > 255000)
          G_time_elapsed_ms = 255000;
      }

      /* rendering (first pass - sprites and particles to vga texture) */
      if (G_game_mode == GAME_MODE_TITLE_SCREEN)
      {
        render_title_screen();
      }
      else if (G_game_mode == GAME_MODE_CREDITS)
      {
        render_credits_screen();
      }
      else if (G_game_mode == GAME_MODE_WORLD_SELECT)
      {
        render_world_select_screen();
      }
      else if (G_game_mode == GAME_MODE_STORY_SELECT)
      {
        render_story_select_screen();
      }
      else if ( (G_game_mode == GAME_MODE_STORY_SCENE)  ||
                (G_game_mode == GAME_MODE_INTERMISSION))
      {
        render_story_screen();
      }
      else if (G_game_mode == GAME_MODE_PLAYING)
      {
        render_scene();
      }
      else if (G_game_mode == GAME_MODE_PAUSED)
      {
        render_scene();
        render_pause_panel();
      }
      else if (G_game_mode == GAME_MODE_ROOM_TRANSITION)
      {
        render_scene();
        render_room_transition();
      }
      else if (G_game_mode == GAME_MODE_ROOM_SELECT_PANEL)
      {
        render_scene();
        render_room_select_panel();
      }
      else if (G_game_mode == GAME_MODE_OPTIONS_PANEL)
      {
        render_scene();
        render_options_panel();
      }
      else if (G_game_mode == GAME_MODE_HELP_SCREEN)
      {
        render_help_screen();
      }
      else if (G_game_mode == GAME_MODE_TRY_AGAIN_PANEL)
      {
        render_scene();
        render_try_again_panel();
      }
      else if (G_game_mode == GAME_MODE_MENU_PANEL)
      {
        render_scene();
        render_menu_panel();
      }

      /* rendering (second pass - from vga texture to window) */
      render_vga_to_window();

      /* update window */
      SDL_GL_SwapWindow(G_sdl_window);

      /* store this update time */
      ticks_last_update = ticks_current;
    }
  }

  /* cleanup window and quit */
cleanup_all:
  if (G_save_game_percentage != 255)
    save_game_write();

  save_game_deinit();
  doremi_deinit_all_sfx();
  doremi_deinit_music();
  pair_trees_and_lists_deinit();
cleanup_collision_grid:
  collide_grid_deinit();
cleanup_world:
  world_deinit();
cleanup_textures:
  textures_deinit();
cleanup_opengl_objects:
  grafx_destroy_opengl_objects();
cleanup_opengl:
  SDL_GL_DeleteContext(SDL_GL_GetCurrentContext());
cleanup_mixer:
  Mix_CloseAudio();

  while (Mix_Init(0))
    Mix_Quit();

cleanup_paths:
  globals_free_paths();
cleanup_window:
  SDL_DestroyWindow(G_sdl_window);
cleanup_gl_library:
  SDL_GL_UnloadLibrary();
cleanup_sdl:
  SDL_Quit();

  return 0;
}
