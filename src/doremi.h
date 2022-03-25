/*******************************************************************************
** doremi.h (sound and music)
*******************************************************************************/

#ifndef DOREMI_H
#define DOREMI_H

#ifdef VT2_MAC_OSX
  #include <SDL2_mixer/SDL_mixer.h>
#else
  #include <SDL2/SDL_mixer.h>
#endif

enum
{
  SFX_INDEX_BALLISTA_CAST = 0,
  SFX_INDEX_BRIDGE_CRACK,
  SFX_INDEX_CANDLE_LIGHT,
  SFX_INDEX_COBWEB_CLEAR,
  SFX_INDEX_DICE_APPEAR,
  SFX_INDEX_EIGHT_BALL_HIT,
  SFX_INDEX_ENEMY_DEATH,
  SFX_INDEX_ENTITY_DESTROYED,
  SFX_INDEX_EVIL_EYE_CAST,
  SFX_INDEX_FIRE_SPELL_CAST,
  SFX_INDEX_FLOPPY_DISK_OBTAINED,
  SFX_INDEX_FREEZING,
  SFX_INDEX_FROG_ACTIVATE,
  SFX_INDEX_GLASS_BREAK,
  SFX_INDEX_ICE_SPELL_CAST,
  SFX_INDEX_JIANGSHI_STOP,
  SFX_INDEX_KABOOM,
  SFX_INDEX_LASER_SHOT_CAST,
  SFX_INDEX_LEVEL_COMPLETE,
  SFX_INDEX_MAHJONG_MATCH,
  SFX_INDEX_MENU_SELECT,
  SFX_INDEX_MUMMY_COLLAPSE,
  SFX_INDEX_NEUTRAL_SPELL_CAST,
  SFX_INDEX_PAUSE,
  SFX_INDEX_PICKUP,
  SFX_INDEX_PLAYER_DEATH,
  SFX_INDEX_PORTCULLIS_OPENING,
  SFX_INDEX_REFLECT,
  SFX_INDEX_SOLOMONS_SEAL_ACTIVATE,
  SFX_INDEX_SPELL_HITTING_WALL,
  SFX_INDEX_SPIKE_BREAK,
  SFX_INDEX_SPIKE_LOWER,
  SFX_INDEX_SPIKE_RAISE,
  SFX_INDEX_TOGGLE_DOWN,
  SFX_INDEX_TOGGLE_UP,
  SFX_INDEX_TRANSFORM_TO_BAT,
  SFX_INDEX_TRANSFORM_TO_VAMPIRE,
  SFX_INDEX_VENUSIAN_APPEAR,
  SFX_INDEX_WARP_ACTIVATE,
  SFX_INDEX_WARP_SPELL_CAST,
  SFX_INDEX_WATER_SPLASH,
  SFX_INDEX_WISP_ANGERED,
  SFX_INDEX_WORLD_COMPLETE,
  SFX_INDEX_YIN_YANG_ACTIVATE,
  SFX_NUM_INDICES
};

enum
{
  MUSIC_TYPE_MAIN_MENU,
  MUSIC_TYPE_STORY_01,
  MUSIC_TYPE_STORY_02,
  MUSIC_TYPE_STORY_03,
  MUSIC_TYPE_STORY_04,
  MUSIC_TYPE_STORY_05,
  MUSIC_TYPE_STORY_06,
  MUSIC_TYPE_WORLD
};

extern Mix_Chunk  G_sfx_all[SFX_NUM_INDICES];
extern Mix_Music  *G_music;

/* function declarations */
short int doremi_init_all_sfx();
short int doremi_deinit_all_sfx();
short int doremi_load_all_sfx_from_file(char* filename);
short int doremi_play_sfx(int type);
short int doremi_set_sfx_volume();
short int doremi_init_music();
short int doremi_deinit_music();
short int doremi_play_music(int type);
short int doremi_pause_music();
short int doremi_unpause_music();
short int doremi_set_music_volume();

#endif
