/*******************************************************************************
** global.c (global variables)
*******************************************************************************/

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entity.h"
#include "global.h"

entity*       G_player;

int           G_game_mode;
int           G_story_scene;

unsigned char G_game_state_flags;

unsigned char G_lever_flags;
unsigned char G_spin_switch_flags;
unsigned char G_number_switch_flags;

int           G_current_level_index;
int           G_next_level_index;

int           G_room_transition_frame;
int           G_silver_cursor_frame;
int           G_cursor_position;

int           G_music_volume;
int           G_sfx_volume;

unsigned char G_current_episode;
unsigned char G_current_world;
unsigned char G_current_floor;
unsigned char G_current_room;

int           G_time_elapsed_ms;
int           G_par_time_ms;

int           G_vials_remaining;
int           G_bat_transforms;
int           G_blue_mana;
int           G_green_mana;

int           G_theme;

char*         G_path_base;
char*         G_path_gfx_data;
char*         G_path_sfx_data;
char*         G_path_world_data;
char*         G_path_shader_data;
char*         G_path_ost;
char*         G_path_pref;
char*         G_path_save_game_1;
char*         G_path_save_game_2;
char*         G_path_save_game_3;

/*******************************************************************************
** globals_init()
*******************************************************************************/
short int globals_init()
{
  G_player = NULL;

  G_game_mode = GAME_MODE_TITLE_SCREEN;
  G_story_scene = STORY_SCENE_PRELUDE;

  G_game_state_flags = GLOBAL_GAME_STATE_FLAGS_CLEAR;

  G_lever_flags = GLOBAL_LEVER_FLAGS_CLEAR;
  G_spin_switch_flags = GLOBAL_SPIN_SWITCH_FLAGS_CLEAR;
  G_number_switch_flags = GLOBAL_NUMBER_SWITCH_FLAGS_CLEAR;

  G_current_level_index = 0;
  G_next_level_index = 0;

  G_room_transition_frame = 0;
  G_silver_cursor_frame = 0;
  G_cursor_position = 0;

  G_music_volume = 128;
  G_sfx_volume = 128;

  G_current_episode = 0;
  G_current_world = 0;
  G_current_floor = 0;
  G_current_room = 0;

  G_time_elapsed_ms = 0;
  G_par_time_ms = 0;

  G_vials_remaining = 0;
  G_bat_transforms = 0;
  G_blue_mana = 0;
  G_green_mana = 0;

  G_theme = THEME_FOYER;

  return 0;
}

/*******************************************************************************
** globals_deinit()
*******************************************************************************/
short int globals_deinit()
{
  G_player = NULL;

  G_game_mode = GAME_MODE_TITLE_SCREEN;
  G_story_scene = STORY_SCENE_PRELUDE;

  G_game_state_flags = GLOBAL_GAME_STATE_FLAGS_CLEAR;

  G_lever_flags = GLOBAL_LEVER_FLAGS_CLEAR;
  G_spin_switch_flags = GLOBAL_SPIN_SWITCH_FLAGS_CLEAR;
  G_number_switch_flags = GLOBAL_NUMBER_SWITCH_FLAGS_CLEAR;

  G_current_level_index = 0;
  G_next_level_index = 0;

  G_room_transition_frame = 0;
  G_silver_cursor_frame = 0;
  G_cursor_position = 0;

  G_music_volume = 128;
  G_sfx_volume = 128;

  G_current_episode = 0;
  G_current_world = 0;
  G_current_floor = 0;
  G_current_room = 0;

  G_time_elapsed_ms = 0;
  G_par_time_ms = 0;

  G_vials_remaining = 0;
  G_bat_transforms = 0;
  G_blue_mana = 0;
  G_green_mana = 0;

  G_theme = THEME_FOYER;

  return 0;
}

/*******************************************************************************
** globals_init_paths()
*******************************************************************************/
short int globals_init_paths()
{
  G_path_base = NULL;
  G_path_gfx_data = NULL;
  G_path_sfx_data = NULL;
  G_path_world_data = NULL;
  G_path_shader_data = NULL;
  G_path_ost = NULL;
  G_path_pref = NULL;
  G_path_save_game_1 = NULL;
  G_path_save_game_2 = NULL;
  G_path_save_game_3 = NULL;

  return 0;
}

/*******************************************************************************
** globals_obtain_base_paths()
*******************************************************************************/
short int globals_obtain_base_paths()
{
  G_path_base = SDL_GetBasePath();

  if (G_path_base == NULL)
  {
    return 1;
  }

  G_path_gfx_data = malloc(sizeof(char) * (strlen(G_path_base) + 10 + 1));
  strcpy(G_path_gfx_data, G_path_base);
  strcpy(G_path_gfx_data + strlen(G_path_base), "vt2gfx.dat");

  G_path_sfx_data = malloc(sizeof(char) * (strlen(G_path_base) + 10 + 1));
  strcpy(G_path_sfx_data, G_path_base);
  strcpy(G_path_sfx_data + strlen(G_path_base), "vt2sfx.dat");

  G_path_world_data = malloc(sizeof(char) * (strlen(G_path_base) + 12 + 1));
  strcpy(G_path_world_data, G_path_base);
  strcpy(G_path_world_data + strlen(G_path_base), "vt2world.dat");

  G_path_shader_data = malloc(sizeof(char) * (strlen(G_path_base) + 13 + 1));
  strcpy(G_path_shader_data, G_path_base);
  strcpy(G_path_shader_data + strlen(G_path_base), "vt2shader.dat");

  G_path_ost = malloc(sizeof(char) * (strlen(G_path_base) + 3 + 1));
  strcpy(G_path_ost, G_path_base);
  strcpy(G_path_ost + strlen(G_path_base), "xm");
  G_path_ost[strlen(G_path_base) + 2] = G_path_ost[strlen(G_path_base) - 1];
  G_path_ost[strlen(G_path_base) + 3] = '\0';

  return 0;
}

/*******************************************************************************
** globals_obtain_preferences_path()
*******************************************************************************/
short int globals_obtain_preferences_path()
{
  G_path_pref = SDL_GetPrefPath("Michael Behrens", "Vampiric Tower 2");

  if (G_path_pref == NULL)
  {
    return 1;
  }

  G_path_save_game_1 = malloc(sizeof(char) * (strlen(G_path_pref) + 6 + 1));
  strcpy(G_path_save_game_1, G_path_pref);
  strcpy(G_path_save_game_1 + strlen(G_path_pref), "01.sav");

  G_path_save_game_2 = malloc(sizeof(char) * (strlen(G_path_pref) + 6 + 1));
  strcpy(G_path_save_game_2, G_path_pref);
  strcpy(G_path_save_game_2 + strlen(G_path_pref), "02.sav");

  G_path_save_game_3 = malloc(sizeof(char) * (strlen(G_path_pref) + 6 + 1));
  strcpy(G_path_save_game_3, G_path_pref);
  strcpy(G_path_save_game_3 + strlen(G_path_pref), "03.sav");

  return 0;
}

/*******************************************************************************
** globals_free_paths()
*******************************************************************************/
short int globals_free_paths()
{
  if (G_path_base != NULL)
  {
    SDL_free(G_path_base);
    G_path_base = NULL;
  }

  if (G_path_gfx_data != NULL)
  {
    free(G_path_gfx_data);
    G_path_gfx_data = NULL;
  }

  if (G_path_sfx_data != NULL)
  {
    free(G_path_sfx_data);
    G_path_sfx_data = NULL;
  }

  if (G_path_world_data != NULL)
  {
    free(G_path_world_data);
    G_path_world_data = NULL;
  }

  if (G_path_shader_data != NULL)
  {
    free(G_path_shader_data);
    G_path_shader_data = NULL;
  }

  if (G_path_ost != NULL)
  {
    free(G_path_ost);
    G_path_ost = NULL;
  }

  if (G_path_pref != NULL)
  {
    SDL_free(G_path_pref);
    G_path_pref = NULL;
  }

  if (G_path_save_game_1 != NULL)
  {
    free(G_path_save_game_1);
    G_path_save_game_1 = NULL;
  }

  if (G_path_save_game_2 != NULL)
  {
    free(G_path_save_game_2);
    G_path_save_game_2 = NULL;
  }

  if (G_path_save_game_3 != NULL)
  {
    free(G_path_save_game_3);
    G_path_save_game_3 = NULL;
  }

  return 0;
}

/*******************************************************************************
** globals_set_episode_world_floor_room()
*******************************************************************************/
short int globals_set_episode_world_floor_room(int index)
{
  if ((index < 0) || (index >= 330))
  {
    G_current_episode = 0;
    G_current_world = 0;
    G_current_floor = 0;
    G_current_room = 0;
  }
  else
  {
    G_current_episode = (index / 45) + 1;
    G_current_world = ((index / 15) % 3) + 1;
    G_current_floor = ((index / 5) % 3) + 1;
    G_current_room = (index % 5) + 1;

    if ((G_current_episode == 8) && (G_current_world == 1))
    {
      G_current_episode = 7;
      G_current_world = 4;
    }
  }

  return 0;
}

