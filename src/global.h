/*******************************************************************************
** global.h (global variables)
*******************************************************************************/

#ifndef GLOBAL_H
#define GLOBAL_H

#include "entity.h"

#define GLOBAL_GAME_STATE_FLAGS_CLEAR             0x00
#define GLOBAL_GAME_STATE_FLAG_STARTED            0x01
#define GLOBAL_GAME_STATE_FLAG_DEAD               0x02
#define GLOBAL_GAME_STATE_FLAG_BLOOD_LOST         0x04
#define GLOBAL_GAME_STATE_FLAG_EVIL_EYE_CAST      0x08
#define GLOBAL_GAME_STATE_FLAG_LEVEL_COMPLETE     0x10
#define GLOBAL_GAME_STATE_FLAG_FLOPPY_COLLECTED   0x20

#define GLOBAL_LEVER_FLAGS_CLEAR              0x00
#define GLOBAL_LEVER_FLAG_WHITE_OFF           0x01
#define GLOBAL_LEVER_FLAG_WHITE_ON            0x02
#define GLOBAL_LEVER_FLAG_CYAN_OFF            0x04
#define GLOBAL_LEVER_FLAG_CYAN_ON             0x08
#define GLOBAL_LEVER_FLAG_MAGENTA_OFF         0x10
#define GLOBAL_LEVER_FLAG_MAGENTA_ON          0x20

#define GLOBAL_SPIN_SWITCH_FLAGS_CLEAR        0x00
#define GLOBAL_SPIN_SWITCH_FLAG_RED_CCW       0x01
#define GLOBAL_SPIN_SWITCH_FLAG_RED_CW        0x02
#define GLOBAL_SPIN_SWITCH_FLAG_GREEN_CCW     0x04
#define GLOBAL_SPIN_SWITCH_FLAG_GREEN_CW      0x08
#define GLOBAL_SPIN_SWITCH_FLAG_BROWN_CCW     0x10
#define GLOBAL_SPIN_SWITCH_FLAG_BROWN_CW      0x20

#define GLOBAL_NUMBER_SWITCH_FLAGS_CLEAR      0x00
#define GLOBAL_NUMBER_SWITCH_FLAG_1           0x01
#define GLOBAL_NUMBER_SWITCH_FLAG_2           0x02
#define GLOBAL_NUMBER_SWITCH_FLAG_3           0x04
#define GLOBAL_NUMBER_SWITCH_FLAG_4           0x08
#define GLOBAL_NUMBER_SWITCH_FLAG_5           0x10
#define GLOBAL_NUMBER_SWITCH_FLAG_6           0x20

enum
{
  GAME_MODE_TITLE_SCREEN,
  GAME_MODE_CREDITS,
  GAME_MODE_WORLD_SELECT,
  GAME_MODE_STORY_SELECT,
  GAME_MODE_STORY_SCENE,
  GAME_MODE_INTERMISSION,
  GAME_MODE_PLAYING,
  GAME_MODE_PAUSED,
  GAME_MODE_ROOM_TRANSITION,
  GAME_MODE_ROOM_SELECT_PANEL,
  GAME_MODE_OPTIONS_PANEL,
  GAME_MODE_HELP_SCREEN,
  GAME_MODE_TRY_AGAIN_PANEL,
  GAME_MODE_MENU_PANEL,
  GAME_MODE_QUIT
};

enum
{
  STORY_SCENE_PRELUDE,
  STORY_SCENE_WORLD_01,
  STORY_SCENE_WORLD_02,
  STORY_SCENE_WORLD_03,
  STORY_SCENE_WORLD_04,
  STORY_SCENE_WORLD_05,
  STORY_SCENE_WORLD_06,
  STORY_SCENE_WORLD_07,
  STORY_SCENE_WORLD_08,
  STORY_SCENE_WORLD_09,
  STORY_SCENE_WORLD_10,
  STORY_SCENE_WORLD_11,
  STORY_SCENE_WORLD_12,
  STORY_SCENE_WORLD_13,
  STORY_SCENE_WORLD_14,
  STORY_SCENE_WORLD_15,
  STORY_SCENE_WORLD_16,
  STORY_SCENE_WORLD_17,
  STORY_SCENE_WORLD_18,
  STORY_SCENE_AFTERWORD
};

enum
{
  THEME_FOYER,
  THEME_CRYPT,
  THEME_WATERS,
  THEME_PERISTYLE,
  THEME_LIBRARY,
  THEME_GARDENS,
  THEME_DUNGEON,
  THEME_SHRINE,
  THEME_LABYRINTH,
  THEME_BALLROOM,
  THEME_PENTOMINO,
  THEME_ARMORY,
  THEME_YGGDRASIL,
  THEME_HEAVEN,
  THEME_FUTURE,
  THEME_ALCHEMY,
  THEME_ARENA,
  THEME_APOGEE,
  THEME_PAGAN,
  THEME_TIBET,
  THEME_GOLDEN,
  THEME_DESSERTS
};

#define STORY_SCENE_HAS_3_PAGES()                                              \
  (G_story_scene == STORY_SCENE_WORLD_01) ||                                   \
  (G_story_scene == STORY_SCENE_WORLD_02) ||                                   \
  (G_story_scene == STORY_SCENE_WORLD_04) ||                                   \
  (G_story_scene == STORY_SCENE_WORLD_05) ||                                   \
  (G_story_scene == STORY_SCENE_WORLD_07) ||                                   \
  (G_story_scene == STORY_SCENE_WORLD_08) ||                                   \
  (G_story_scene == STORY_SCENE_WORLD_10) ||                                   \
  (G_story_scene == STORY_SCENE_WORLD_11) ||                                   \
  (G_story_scene == STORY_SCENE_WORLD_13) ||                                   \
  (G_story_scene == STORY_SCENE_WORLD_14) ||                                   \
  (G_story_scene == STORY_SCENE_WORLD_16) ||                                   \
  (G_story_scene == STORY_SCENE_WORLD_17)

#define STORY_SCENE_HAS_4_PAGES()                                              \
  (G_story_scene == STORY_SCENE_PRELUDE)  ||                                   \
  (G_story_scene == STORY_SCENE_WORLD_03) ||                                   \
  (G_story_scene == STORY_SCENE_WORLD_06) ||                                   \
  (G_story_scene == STORY_SCENE_WORLD_09) ||                                   \
  (G_story_scene == STORY_SCENE_WORLD_12) ||                                   \
  (G_story_scene == STORY_SCENE_WORLD_15) ||                                   \
  (G_story_scene == STORY_SCENE_WORLD_18) ||                                   \
  (G_story_scene == STORY_SCENE_AFTERWORD)

extern entity*        G_player;

extern int            G_game_mode;
extern int            G_story_scene;

extern unsigned char  G_game_state_flags;

extern unsigned char  G_lever_flags;
extern unsigned char  G_spin_switch_flags;
extern unsigned char  G_number_switch_flags;

extern int            G_current_level_index;
extern int            G_next_level_index;

extern int            G_room_transition_frame;
extern int            G_silver_cursor_frame;
extern int            G_cursor_position;

extern int            G_music_volume;
extern int            G_sfx_volume;

extern unsigned char  G_current_episode;
extern unsigned char  G_current_world;
extern unsigned char  G_current_floor;
extern unsigned char  G_current_room;

extern int            G_time_elapsed_ms;
extern int            G_par_time_ms;

extern int            G_vials_remaining;
extern int            G_bat_transforms;
extern int            G_blue_mana;
extern int            G_green_mana;

extern int            G_theme;

extern char*          G_path_base;
extern char*          G_path_gfx_data;
extern char*          G_path_sfx_data;
extern char*          G_path_world_data;
extern char*          G_path_shader_data;
extern char*          G_path_ost;
extern char*          G_path_pref;
extern char*          G_path_save_game_1;
extern char*          G_path_save_game_2;
extern char*          G_path_save_game_3;

/* function declarations */
short int globals_init();
short int globals_deinit();
short int globals_init_paths();
short int globals_obtain_base_paths();
short int globals_obtain_preferences_path();
short int globals_free_paths();
short int globals_set_episode_world_floor_room(int index);

#endif
