/*******************************************************************************
** loop.c (main loop)
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "collide.h"
#include "controls.h"
#include "doremi.h"
#include "global.h"
#include "grafx.h"
#include "level.h"
#include "logic.h"
#include "loop.h"
#include "pairtree.h"
#include "savegame.h"
#include "world.h"

/*******************************************************************************
** loop_process_frame()
*******************************************************************************/
short int loop_process_frame()
{
  unsigned char current_world_flags;
  unsigned char new_world_flags;

  current_world_flags = G_save_game_flags[G_current_level_index / 15];

  /* room transition */
  if (G_game_mode == GAME_MODE_ROOM_TRANSITION)
  {
    if (G_room_transition_frame == 30)
    {
      G_current_level_index = G_next_level_index;
      level_load_to_world(&G_levels_all[G_current_level_index]);
      logic_setup_level();

      /* update world */
      world_update_animations();

      /* light pumpkins, etc */
      logic_set_enemy_animations_based_on_player_position();

      G_game_state_flags = GLOBAL_GAME_STATE_FLAGS_CLEAR;
      G_time_elapsed_ms = 0;
    }

    G_room_transition_frame -= 1;

    if (G_room_transition_frame < 0)
      G_game_mode = GAME_MODE_PLAYING;

    return 0;
  }

  /* if level is completed, cycle to next level */
  if (G_game_state_flags & GLOBAL_GAME_STATE_FLAG_LEVEL_COMPLETE)
  {
    /* set save game flags */
    save_game_mark_current_level_complete();

    if (G_game_state_flags & GLOBAL_GAME_STATE_FLAG_FLOPPY_COLLECTED)
      save_game_mark_current_floppy_obtained();

    if ((G_time_elapsed_ms / 1000) < 1)
      save_game_record_best_time(1);
    else if ((G_time_elapsed_ms / 1000) > 255)
      save_game_record_best_time(255);
    else
      save_game_record_best_time(G_time_elapsed_ms / 1000);

    /* compute completion percentage and floppy disk counts */
    save_game_compute_completion_percentage_and_floppy_counts();

    /* determine next level */
    new_world_flags = G_save_game_flags[G_current_level_index / 15];

    /* if a new room was not completed, just cycle through this world */
    if ((current_world_flags & SAVE_GAME_MASK_ROOMS) == 
        (new_world_flags & SAVE_GAME_MASK_ROOMS))
    {
      if ((G_current_level_index % 15) < 14)
        G_next_level_index = G_current_level_index + 1;
      else
        G_next_level_index = (G_current_level_index / 15) * 15;
    }
    /* if floor 2 was unlocked, move to floor 2 room 1 */
    else if ( ((current_world_flags & SAVE_GAME_MASK_FLOORS) ^ 
              (new_world_flags & SAVE_GAME_MASK_FLOORS)) == 
              SAVE_GAME_FLAG_FLOOR_1)
    {
      if (G_current_level_index < 325)
        G_next_level_index = ((G_current_level_index + 5) / 5) * 5;
      else
        G_next_level_index = G_current_level_index;
    }
    /* if all rooms completed (including floor 3), cycle back to room 1 */
    else if ( (current_world_flags != new_world_flags) &&
              ((new_world_flags & SAVE_GAME_MASK_FLOORS) == SAVE_GAME_MASK_FLOORS) &&
              ((new_world_flags & SAVE_GAME_MASK_ROOMS) == SAVE_GAME_MASK_ROOMS))
    {
      G_next_level_index = (G_current_level_index / 15) * 15;
    }
    /* if floor 3 was unlocked, move to next world */
    else if ( ((current_world_flags & SAVE_GAME_MASK_FLOORS) ^ 
              (new_world_flags & SAVE_GAME_MASK_FLOORS)) == 
              SAVE_GAME_FLAG_FLOOR_2)
    {
      /* normal worlds: move to story intermission scene */
      if (((G_current_level_index >= 0) && (G_current_level_index < 270)) ||
          ((G_current_level_index >= 315) && (G_current_level_index < 330)))
      {
        /* set story scene */
        if ((G_current_level_index >= 0) && (G_current_level_index < 15))
          G_story_scene = STORY_SCENE_WORLD_01;
        else if ((G_current_level_index >= 15) && (G_current_level_index < 30))
          G_story_scene = STORY_SCENE_WORLD_02;
        else if ((G_current_level_index >= 30) && (G_current_level_index < 45))
          G_story_scene = STORY_SCENE_WORLD_03;
        else if ((G_current_level_index >= 45) && (G_current_level_index < 60))
          G_story_scene = STORY_SCENE_WORLD_04;
        else if ((G_current_level_index >= 60) && (G_current_level_index < 75))
          G_story_scene = STORY_SCENE_WORLD_05;
        else if ((G_current_level_index >= 75) && (G_current_level_index < 90))
          G_story_scene = STORY_SCENE_WORLD_06;
        else if ((G_current_level_index >= 90) && (G_current_level_index < 105))
          G_story_scene = STORY_SCENE_WORLD_07;
        else if ((G_current_level_index >= 105) && (G_current_level_index < 120))
          G_story_scene = STORY_SCENE_WORLD_08;
        else if ((G_current_level_index >= 120) && (G_current_level_index < 135))
          G_story_scene = STORY_SCENE_WORLD_09;
        else if ((G_current_level_index >= 135) && (G_current_level_index < 150))
          G_story_scene = STORY_SCENE_WORLD_10;
        else if ((G_current_level_index >= 150) && (G_current_level_index < 165))
          G_story_scene = STORY_SCENE_WORLD_11;
        else if ((G_current_level_index >= 165) && (G_current_level_index < 180))
          G_story_scene = STORY_SCENE_WORLD_12;
        else if ((G_current_level_index >= 180) && (G_current_level_index < 195))
          G_story_scene = STORY_SCENE_WORLD_13;
        else if ((G_current_level_index >= 195) && (G_current_level_index < 210))
          G_story_scene = STORY_SCENE_WORLD_14;
        else if ((G_current_level_index >= 210) && (G_current_level_index < 225))
          G_story_scene = STORY_SCENE_WORLD_15;
        else if ((G_current_level_index >= 225) && (G_current_level_index < 240))
          G_story_scene = STORY_SCENE_WORLD_16;
        else if ((G_current_level_index >= 240) && (G_current_level_index < 255))
          G_story_scene = STORY_SCENE_WORLD_17;
        else if ((G_current_level_index >= 255) && (G_current_level_index < 270))
          G_story_scene = STORY_SCENE_WORLD_18;
        else if ((G_current_level_index >= 315) && (G_current_level_index < 330))
          G_story_scene = STORY_SCENE_AFTERWORD;

        /* set music */
        if ((G_story_scene == STORY_SCENE_PRELUDE)  ||
            (G_story_scene == STORY_SCENE_WORLD_18) ||
            (G_story_scene == STORY_SCENE_AFTERWORD))
        {
          doremi_play_music(MUSIC_TYPE_STORY_01);
        }
        else if ( (G_story_scene == STORY_SCENE_WORLD_01) ||
                  (G_story_scene == STORY_SCENE_WORLD_09) ||
                  (G_story_scene == STORY_SCENE_WORLD_17))
        {
          doremi_play_music(MUSIC_TYPE_STORY_02);
        }
        else if ( (G_story_scene == STORY_SCENE_WORLD_02) ||
                  (G_story_scene == STORY_SCENE_WORLD_08) ||
                  (G_story_scene == STORY_SCENE_WORLD_10) ||
                  (G_story_scene == STORY_SCENE_WORLD_16))
        {
          doremi_play_music(MUSIC_TYPE_STORY_03);
        }
        else if ( (G_story_scene == STORY_SCENE_WORLD_03) ||
                  (G_story_scene == STORY_SCENE_WORLD_07) ||
                  (G_story_scene == STORY_SCENE_WORLD_11) ||
                  (G_story_scene == STORY_SCENE_WORLD_15))
        {
          doremi_play_music(MUSIC_TYPE_STORY_04);
        }
        else if ( (G_story_scene == STORY_SCENE_WORLD_04) ||
                  (G_story_scene == STORY_SCENE_WORLD_06) ||
                  (G_story_scene == STORY_SCENE_WORLD_12) ||
                  (G_story_scene == STORY_SCENE_WORLD_14))
        {
          doremi_play_music(MUSIC_TYPE_STORY_05);
        }
        else if ( (G_story_scene == STORY_SCENE_WORLD_05) ||
                  (G_story_scene == STORY_SCENE_WORLD_13))
        {
          doremi_play_music(MUSIC_TYPE_STORY_06);
        }
        else
          doremi_play_music(MUSIC_TYPE_STORY_01);

        /* play sfx */
        if (G_game_state_flags & GLOBAL_GAME_STATE_FLAG_FLOPPY_COLLECTED)
          doremi_play_sfx(SFX_INDEX_FLOPPY_DISK_OBTAINED);
        else
          doremi_play_sfx(SFX_INDEX_WORLD_COMPLETE);

        G_game_state_flags = GLOBAL_GAME_STATE_FLAGS_CLEAR;
        G_game_mode = GAME_MODE_INTERMISSION;
        G_cursor_position = 0;
      }
      /* secret worlds: just move to floor 3 room 1 */
      else
      {
        G_next_level_index = ((G_current_level_index / 15) * 15) + 10;

        globals_set_episode_world_floor_room(G_next_level_index);

        /* play sfx */
        if (G_game_state_flags & GLOBAL_GAME_STATE_FLAG_FLOPPY_COLLECTED)
          doremi_play_sfx(SFX_INDEX_FLOPPY_DISK_OBTAINED);
        else
          doremi_play_sfx(SFX_INDEX_WORLD_COMPLETE);

        G_game_state_flags = GLOBAL_GAME_STATE_FLAGS_CLEAR;
        G_game_mode = GAME_MODE_ROOM_TRANSITION;
        G_room_transition_frame = 60;
      }

      return 0;
    }
    /* otherwise, move to next incomplete room on this floor */
    else if ((G_current_level_index % 5) == 0)
    {
      if (!(new_world_flags & SAVE_GAME_FLAG_ROOM_2))
        G_next_level_index = ((G_current_level_index / 5) * 5) + 1;
      else if (!(new_world_flags & SAVE_GAME_FLAG_ROOM_3))
        G_next_level_index = ((G_current_level_index / 5) * 5) + 2;
      else if (!(new_world_flags & SAVE_GAME_FLAG_ROOM_4))
        G_next_level_index = ((G_current_level_index / 5) * 5) + 3;
      else if (!(new_world_flags & SAVE_GAME_FLAG_ROOM_5))
        G_next_level_index = ((G_current_level_index / 5) * 5) + 4;
      else
        G_next_level_index = ((G_current_level_index / 5) * 5) + 1;
    }
    else if ((G_current_level_index % 5) == 1)
    {
      if (!(new_world_flags & SAVE_GAME_FLAG_ROOM_3))
        G_next_level_index = ((G_current_level_index / 5) * 5) + 2;
      else if (!(new_world_flags & SAVE_GAME_FLAG_ROOM_4))
        G_next_level_index = ((G_current_level_index / 5) * 5) + 3;
      else if (!(new_world_flags & SAVE_GAME_FLAG_ROOM_5))
        G_next_level_index = ((G_current_level_index / 5) * 5) + 4;
      else if (!(new_world_flags & SAVE_GAME_FLAG_ROOM_1))
        G_next_level_index = ((G_current_level_index / 5) * 5) + 0;
      else
        G_next_level_index = ((G_current_level_index / 5) * 5) + 2;
    }
    else if ((G_current_level_index % 5) == 2)
    {
      if (!(new_world_flags & SAVE_GAME_FLAG_ROOM_4))
        G_next_level_index = ((G_current_level_index / 5) * 5) + 3;
      else if (!(new_world_flags & SAVE_GAME_FLAG_ROOM_5))
        G_next_level_index = ((G_current_level_index / 5) * 5) + 4;
      else if (!(new_world_flags & SAVE_GAME_FLAG_ROOM_1))
        G_next_level_index = ((G_current_level_index / 5) * 5) + 0;
      else if (!(new_world_flags & SAVE_GAME_FLAG_ROOM_2))
        G_next_level_index = ((G_current_level_index / 5) * 5) + 1;
      else
        G_next_level_index = ((G_current_level_index / 5) * 5) + 3;
    }
    else if ((G_current_level_index % 5) == 3)
    {
      if (!(new_world_flags & SAVE_GAME_FLAG_ROOM_5))
        G_next_level_index = ((G_current_level_index / 5) * 5) + 4;
      else if (!(new_world_flags & SAVE_GAME_FLAG_ROOM_1))
        G_next_level_index = ((G_current_level_index / 5) * 5) + 0;
      else if (!(new_world_flags & SAVE_GAME_FLAG_ROOM_2))
        G_next_level_index = ((G_current_level_index / 5) * 5) + 1;
      else if (!(new_world_flags & SAVE_GAME_FLAG_ROOM_3))
        G_next_level_index = ((G_current_level_index / 5) * 5) + 2;
      else
        G_next_level_index = ((G_current_level_index / 5) * 5) + 4;
    }
    else if ((G_current_level_index % 5) == 4)
    {
      if (!(new_world_flags & SAVE_GAME_FLAG_ROOM_1))
        G_next_level_index = ((G_current_level_index / 5) * 5) + 0;
      else if (!(new_world_flags & SAVE_GAME_FLAG_ROOM_2))
        G_next_level_index = ((G_current_level_index / 5) * 5) + 1;
      else if (!(new_world_flags & SAVE_GAME_FLAG_ROOM_3))
        G_next_level_index = ((G_current_level_index / 5) * 5) + 2;
      else if (!(new_world_flags & SAVE_GAME_FLAG_ROOM_4))
        G_next_level_index = ((G_current_level_index / 5) * 5) + 3;
      else
        G_next_level_index = ((G_current_level_index / 5) * 5) + 0;
    }
    else
      G_next_level_index = G_current_level_index;

    globals_set_episode_world_floor_room(G_next_level_index);

    /* play sfx */
    if (G_game_state_flags & GLOBAL_GAME_STATE_FLAG_FLOPPY_COLLECTED)
      doremi_play_sfx(SFX_INDEX_FLOPPY_DISK_OBTAINED);
    else
      doremi_play_sfx(SFX_INDEX_LEVEL_COMPLETE);

    G_game_state_flags = GLOBAL_GAME_STATE_FLAGS_CLEAR;
    G_game_mode = GAME_MODE_ROOM_TRANSITION;
    G_room_transition_frame = 60;

    return 0;
  }

  /* check hud keys based on mode */
  /* note: fullscreen toggle checked in main */
  /* title screen */
  if (G_game_mode == GAME_MODE_TITLE_SCREEN)
  {
    if ((G_current_hud_flags & CONTROLS_HUD_FLAG_CONFIRM) &&
        (!(G_last_hud_flags & CONTROLS_HUD_FLAG_CONFIRM)))
    {
      if (G_cursor_position == 0)
      {
        G_cursor_position = 3;
        G_save_game_number = 1;

        if (save_game_read())
        {
          save_game_reset();
          G_save_game_percentage = 255;
        }

        G_silver_cursor_frame = 0;
        doremi_play_sfx(SFX_INDEX_MENU_SELECT);
        return 0;
      }
      else if (G_cursor_position == 1)
      {
        G_game_mode = GAME_MODE_CREDITS;
        return 0;
      }
      else if (G_cursor_position == 2)
      {
        G_game_mode = GAME_MODE_QUIT;
        return 0;
      }
      else if ( (G_cursor_position == 3) ||
                (G_cursor_position == 4) ||
                (G_cursor_position == 5))
      {
        if (G_save_game_percentage == 255)
        {
          save_game_reset();
          save_game_write();
          G_game_mode = GAME_MODE_INTERMISSION;
          G_story_scene = STORY_SCENE_PRELUDE;
          G_cursor_position = 0;
          doremi_play_music(MUSIC_TYPE_STORY_01);
        }
        else
          G_cursor_position = 6;

        doremi_play_sfx(SFX_INDEX_MENU_SELECT);
        return 0;
      }
      else if (G_cursor_position == 6)
      {
        G_game_mode = GAME_MODE_WORLD_SELECT;
        G_cursor_position = 0;
        G_silver_cursor_frame = 0;
        doremi_play_sfx(SFX_INDEX_MENU_SELECT);
        return 0;
      }
      else if (G_cursor_position == 7)
      {
        G_game_mode = GAME_MODE_STORY_SELECT;
        G_cursor_position = 0;
        G_silver_cursor_frame = 0;
        doremi_play_sfx(SFX_INDEX_MENU_SELECT);
        return 0;
      }
    }
    else if ( (G_current_hud_flags & CONTROLS_HUD_FLAG_CANCEL) &&
              (!(G_last_hud_flags & CONTROLS_HUD_FLAG_CANCEL)))
    {
      if ((G_cursor_position >= 0) && (G_cursor_position <= 2))
      {
        G_cursor_position = 2;
        return 0;
      }
      else if ((G_cursor_position >= 3) && (G_cursor_position <= 5))
      {
        G_cursor_position = 0;
        return 0;
      }
      else if ((G_cursor_position >= 6) && (G_cursor_position <= 7))
      {
        if (G_save_game_number == 1)
          G_cursor_position = 3;
        else if (G_save_game_number == 2)
          G_cursor_position = 4;
        else if (G_save_game_number == 3)
          G_cursor_position = 5;
        else
          G_cursor_position = 3;

        return 0;
      }
    }
  }
  /* credits */
  else if (G_game_mode == GAME_MODE_CREDITS)
  {
    /* confirm / cancel */
    if ((G_current_hud_flags & CONTROLS_HUD_FLAG_CONFIRM) &&
        (!(G_last_hud_flags & CONTROLS_HUD_FLAG_CONFIRM)))
    {
      G_game_mode = GAME_MODE_TITLE_SCREEN;
      G_cursor_position = 1;
    }
    else if ( (G_current_hud_flags & CONTROLS_HUD_FLAG_CANCEL) &&
              (!(G_last_hud_flags & CONTROLS_HUD_FLAG_CANCEL)))
    {
      G_game_mode = GAME_MODE_TITLE_SCREEN;
      G_cursor_position = 1;
    }
  }
  /* world select */
  else if (G_game_mode == GAME_MODE_WORLD_SELECT)
  {
    /* select world */
    if ((G_current_hud_flags & CONTROLS_HUD_FLAG_CONFIRM) &&
        (!(G_last_hud_flags & CONTROLS_HUD_FLAG_CONFIRM)))
    {
      /* bound cursor */
      if (G_cursor_position < 0)
        G_cursor_position = 0;
      else if (G_cursor_position > 21)
        G_cursor_position = 21;

      /* select next incomplete room */
      G_next_level_index = 15 * G_cursor_position;

      if (!((G_save_game_flags[G_cursor_position] & SAVE_GAME_MASK_ROOMS) &&
            (G_save_game_flags[G_cursor_position] & SAVE_GAME_MASK_FLOORS)))
      {
        if ((G_save_game_flags[G_cursor_position] & SAVE_GAME_FLAG_FLOOR_1) &&
            (G_save_game_flags[G_cursor_position] & SAVE_GAME_FLAG_FLOOR_2))
        {
          G_next_level_index += 10;
        }
        else if (G_save_game_flags[G_cursor_position] & SAVE_GAME_FLAG_FLOOR_1)
          G_next_level_index += 5;

        if ((G_save_game_flags[G_cursor_position] & SAVE_GAME_FLAG_ROOM_1)  &&
            (G_save_game_flags[G_cursor_position] & SAVE_GAME_FLAG_ROOM_2)  &&
            (G_save_game_flags[G_cursor_position] & SAVE_GAME_FLAG_ROOM_3)  &&
            (G_save_game_flags[G_cursor_position] & SAVE_GAME_FLAG_ROOM_4))
        {
          G_next_level_index += 4;
        }
        else if ( (G_save_game_flags[G_cursor_position] & SAVE_GAME_FLAG_ROOM_1)  &&
                  (G_save_game_flags[G_cursor_position] & SAVE_GAME_FLAG_ROOM_2)  &&
                  (G_save_game_flags[G_cursor_position] & SAVE_GAME_FLAG_ROOM_3))
        {
          G_next_level_index += 3;
        }
        else if ( (G_save_game_flags[G_cursor_position] & SAVE_GAME_FLAG_ROOM_1)  &&
                  (G_save_game_flags[G_cursor_position] & SAVE_GAME_FLAG_ROOM_2))
        {
          G_next_level_index += 2;
        }
        else if (G_save_game_flags[G_cursor_position] & SAVE_GAME_FLAG_ROOM_1)
          G_next_level_index += 1;
      }

      G_current_level_index = G_next_level_index;

      globals_set_episode_world_floor_room(G_current_level_index);
      doremi_play_sfx(SFX_INDEX_MENU_SELECT);

      level_load_to_world(&G_levels_all[G_current_level_index]);
      logic_setup_level();

      /* update world */
      world_update_animations();

      /* light pumpkins, etc */
      logic_set_enemy_animations_based_on_player_position();

      G_game_state_flags = GLOBAL_GAME_STATE_FLAGS_CLEAR;
      G_time_elapsed_ms = 0;

      doremi_play_music(MUSIC_TYPE_WORLD);

      G_game_mode = GAME_MODE_PLAYING;
    }
    /* back to title screen */
    else if ( (G_current_hud_flags & CONTROLS_HUD_FLAG_CANCEL) &&
              (!(G_last_hud_flags & CONTROLS_HUD_FLAG_CANCEL)))
    {
      G_game_mode = GAME_MODE_TITLE_SCREEN;
      G_cursor_position = 6;
      G_silver_cursor_frame = 0;
      return 0;
    }
  }
  /* story select */
  else if (G_game_mode == GAME_MODE_STORY_SELECT)
  {
    /* select story scene */
    if ((G_current_hud_flags & CONTROLS_HUD_FLAG_CONFIRM) &&
        (!(G_last_hud_flags & CONTROLS_HUD_FLAG_CONFIRM)))
    {
      /* bound cursor */
      if (G_cursor_position < 0)
        G_cursor_position = 0;
      else if (G_cursor_position > 19)
        G_cursor_position = 19;

      /* set story scene */
      if (G_cursor_position == 0)
        G_story_scene = STORY_SCENE_PRELUDE;
      else if (G_cursor_position == 1)
        G_story_scene = STORY_SCENE_WORLD_01;
      else if (G_cursor_position == 2)
        G_story_scene = STORY_SCENE_WORLD_02;
      else if (G_cursor_position == 3)
        G_story_scene = STORY_SCENE_WORLD_03;
      else if (G_cursor_position == 4)
        G_story_scene = STORY_SCENE_WORLD_04;
      else if (G_cursor_position == 5)
        G_story_scene = STORY_SCENE_WORLD_05;
      else if (G_cursor_position == 6)
        G_story_scene = STORY_SCENE_WORLD_06;
      else if (G_cursor_position == 7)
        G_story_scene = STORY_SCENE_WORLD_07;
      else if (G_cursor_position == 8)
        G_story_scene = STORY_SCENE_WORLD_08;
      else if (G_cursor_position == 9)
        G_story_scene = STORY_SCENE_WORLD_09;
      else if (G_cursor_position == 10)
        G_story_scene = STORY_SCENE_WORLD_10;
      else if (G_cursor_position == 11)
        G_story_scene = STORY_SCENE_WORLD_11;
      else if (G_cursor_position == 12)
        G_story_scene = STORY_SCENE_WORLD_12;
      else if (G_cursor_position == 13)
        G_story_scene = STORY_SCENE_WORLD_13;
      else if (G_cursor_position == 14)
        G_story_scene = STORY_SCENE_WORLD_14;
      else if (G_cursor_position == 15)
        G_story_scene = STORY_SCENE_WORLD_15;
      else if (G_cursor_position == 16)
        G_story_scene = STORY_SCENE_WORLD_16;
      else if (G_cursor_position == 17)
        G_story_scene = STORY_SCENE_WORLD_17;
      else if (G_cursor_position == 18)
        G_story_scene = STORY_SCENE_WORLD_18;
      else if (G_cursor_position == 19)
        G_story_scene = STORY_SCENE_AFTERWORD;
      else
        G_story_scene = STORY_SCENE_PRELUDE;

      /* set music */
      if ((G_story_scene == STORY_SCENE_PRELUDE)  ||
          (G_story_scene == STORY_SCENE_WORLD_18) ||
          (G_story_scene == STORY_SCENE_AFTERWORD))
      {
        doremi_play_music(MUSIC_TYPE_STORY_01);
      }
      else if ( (G_story_scene == STORY_SCENE_WORLD_01) ||
                (G_story_scene == STORY_SCENE_WORLD_09) ||
                (G_story_scene == STORY_SCENE_WORLD_17))
      {
        doremi_play_music(MUSIC_TYPE_STORY_02);
      }
      else if ( (G_story_scene == STORY_SCENE_WORLD_02) ||
                (G_story_scene == STORY_SCENE_WORLD_08) ||
                (G_story_scene == STORY_SCENE_WORLD_10) ||
                (G_story_scene == STORY_SCENE_WORLD_16))
      {
        doremi_play_music(MUSIC_TYPE_STORY_03);
      }
      else if ( (G_story_scene == STORY_SCENE_WORLD_03) ||
                (G_story_scene == STORY_SCENE_WORLD_07) ||
                (G_story_scene == STORY_SCENE_WORLD_11) ||
                (G_story_scene == STORY_SCENE_WORLD_15))
      {
        doremi_play_music(MUSIC_TYPE_STORY_04);
      }
      else if ( (G_story_scene == STORY_SCENE_WORLD_04) ||
                (G_story_scene == STORY_SCENE_WORLD_06) ||
                (G_story_scene == STORY_SCENE_WORLD_12) ||
                (G_story_scene == STORY_SCENE_WORLD_14))
      {
        doremi_play_music(MUSIC_TYPE_STORY_05);
      }
      else if ( (G_story_scene == STORY_SCENE_WORLD_05) ||
                (G_story_scene == STORY_SCENE_WORLD_13))
      {
        doremi_play_music(MUSIC_TYPE_STORY_06);
      }
      else
        doremi_play_music(MUSIC_TYPE_STORY_01);

      G_game_mode = GAME_MODE_STORY_SCENE;
      G_cursor_position = 0;
      doremi_play_sfx(SFX_INDEX_MENU_SELECT);

      return 0;
    }
    /* back to title screen */
    else if ( (G_current_hud_flags & CONTROLS_HUD_FLAG_CANCEL) &&
              (!(G_last_hud_flags & CONTROLS_HUD_FLAG_CANCEL)))
    {
      G_game_mode = GAME_MODE_TITLE_SCREEN;
      G_cursor_position = 7;
      G_silver_cursor_frame = 0;
      return 0;
    }
  }
  /* story scene */
  else if (G_game_mode == GAME_MODE_STORY_SCENE)
  {
    /* back to story select screen */
    if ((G_current_hud_flags & CONTROLS_HUD_FLAG_CANCEL) &&
        (!(G_last_hud_flags & CONTROLS_HUD_FLAG_CANCEL)))
    {
      G_game_mode = GAME_MODE_STORY_SELECT;

      if (G_story_scene == STORY_SCENE_PRELUDE)
        G_cursor_position = 0;
      else if (G_story_scene == STORY_SCENE_WORLD_01)
        G_cursor_position = 1;
      else if (G_story_scene == STORY_SCENE_WORLD_02)
        G_cursor_position = 2;
      else if (G_story_scene == STORY_SCENE_WORLD_03)
        G_cursor_position = 3;
      else if (G_story_scene == STORY_SCENE_WORLD_04)
        G_cursor_position = 4;
      else if (G_story_scene == STORY_SCENE_WORLD_05)
        G_cursor_position = 5;
      else if (G_story_scene == STORY_SCENE_WORLD_06)
        G_cursor_position = 6;
      else if (G_story_scene == STORY_SCENE_WORLD_07)
        G_cursor_position = 7;
      else if (G_story_scene == STORY_SCENE_WORLD_08)
        G_cursor_position = 8;
      else if (G_story_scene == STORY_SCENE_WORLD_09)
        G_cursor_position = 9;
      else if (G_story_scene == STORY_SCENE_WORLD_10)
        G_cursor_position = 10;
      else if (G_story_scene == STORY_SCENE_WORLD_11)
        G_cursor_position = 11;
      else if (G_story_scene == STORY_SCENE_WORLD_12)
        G_cursor_position = 12;
      else if (G_story_scene == STORY_SCENE_WORLD_13)
        G_cursor_position = 13;
      else if (G_story_scene == STORY_SCENE_WORLD_14)
        G_cursor_position = 14;
      else if (G_story_scene == STORY_SCENE_WORLD_15)
        G_cursor_position = 15;
      else if (G_story_scene == STORY_SCENE_WORLD_16)
        G_cursor_position = 16;
      else if (G_story_scene == STORY_SCENE_WORLD_17)
        G_cursor_position = 17;
      else if (G_story_scene == STORY_SCENE_WORLD_18)
        G_cursor_position = 18;
      else if (G_story_scene == STORY_SCENE_AFTERWORD)
        G_cursor_position = 19;
      else
        G_cursor_position = 0;

      doremi_play_music(MUSIC_TYPE_MAIN_MENU);

      G_silver_cursor_frame = 0;
      return 0;
    }
  }
  /* intermission */
  else if (G_game_mode == GAME_MODE_INTERMISSION)
  {
    /* exit intermission */
    if (((G_current_hud_flags & CONTROLS_HUD_FLAG_CONFIRM)  &&
        (!(G_last_hud_flags & CONTROLS_HUD_FLAG_CONFIRM)))  ||
        ((G_current_hud_flags & CONTROLS_HUD_FLAG_CANCEL)   &&
        (!(G_last_hud_flags & CONTROLS_HUD_FLAG_CANCEL))))
    {
      if ((G_story_scene == STORY_SCENE_PRELUDE)  ||
          (G_story_scene == STORY_SCENE_WORLD_01) ||
          (G_story_scene == STORY_SCENE_WORLD_02) ||
          (G_story_scene == STORY_SCENE_WORLD_03) ||
          (G_story_scene == STORY_SCENE_WORLD_04) ||
          (G_story_scene == STORY_SCENE_WORLD_05) ||
          (G_story_scene == STORY_SCENE_WORLD_06) ||
          (G_story_scene == STORY_SCENE_WORLD_07) ||
          (G_story_scene == STORY_SCENE_WORLD_08) ||
          (G_story_scene == STORY_SCENE_WORLD_09) ||
          (G_story_scene == STORY_SCENE_WORLD_10) ||
          (G_story_scene == STORY_SCENE_WORLD_11) ||
          (G_story_scene == STORY_SCENE_WORLD_12) ||
          (G_story_scene == STORY_SCENE_WORLD_13) ||
          (G_story_scene == STORY_SCENE_WORLD_14) ||
          (G_story_scene == STORY_SCENE_WORLD_15) ||
          (G_story_scene == STORY_SCENE_WORLD_16) ||
          (G_story_scene == STORY_SCENE_WORLD_17))
      {
        if (G_story_scene == STORY_SCENE_PRELUDE)
          G_next_level_index = 0;
        else if (G_story_scene == STORY_SCENE_WORLD_01)
          G_next_level_index = 15;
        else if (G_story_scene == STORY_SCENE_WORLD_02)
          G_next_level_index = 30;
        else if (G_story_scene == STORY_SCENE_WORLD_03)
          G_next_level_index = 45;
        else if (G_story_scene == STORY_SCENE_WORLD_04)
          G_next_level_index = 60;
        else if (G_story_scene == STORY_SCENE_WORLD_05)
          G_next_level_index = 75;
        else if (G_story_scene == STORY_SCENE_WORLD_06)
          G_next_level_index = 90;
        else if (G_story_scene == STORY_SCENE_WORLD_07)
          G_next_level_index = 105;
        else if (G_story_scene == STORY_SCENE_WORLD_08)
          G_next_level_index = 120;
        else if (G_story_scene == STORY_SCENE_WORLD_09)
          G_next_level_index = 135;
        else if (G_story_scene == STORY_SCENE_WORLD_10)
          G_next_level_index = 150;
        else if (G_story_scene == STORY_SCENE_WORLD_11)
          G_next_level_index = 165;
        else if (G_story_scene == STORY_SCENE_WORLD_12)
          G_next_level_index = 180;
        else if (G_story_scene == STORY_SCENE_WORLD_13)
          G_next_level_index = 195;
        else if (G_story_scene == STORY_SCENE_WORLD_14)
          G_next_level_index = 210;
        else if (G_story_scene == STORY_SCENE_WORLD_15)
          G_next_level_index = 225;
        else if (G_story_scene == STORY_SCENE_WORLD_16)
          G_next_level_index = 240;
        else if (G_story_scene == STORY_SCENE_WORLD_17)
          G_next_level_index = 255;
        else
          G_next_level_index = 0;

        G_current_level_index = G_next_level_index;

        globals_set_episode_world_floor_room(G_current_level_index);

        level_load_to_world(&G_levels_all[G_current_level_index]);
        logic_setup_level();

        /* update world */
        world_update_animations();

        /* light pumpkins, etc */
        logic_set_enemy_animations_based_on_player_position();

        G_game_state_flags = GLOBAL_GAME_STATE_FLAGS_CLEAR;
        G_time_elapsed_ms = 0;

        doremi_play_music(MUSIC_TYPE_WORLD);

        G_game_mode = GAME_MODE_PLAYING;
      }
      else
      {
        G_game_mode = GAME_MODE_WORLD_SELECT;
        save_game_write();
        doremi_play_music(MUSIC_TYPE_MAIN_MENU);
        G_cursor_position = (G_current_level_index / 15) % 22;
        G_silver_cursor_frame = 0;
      }

      return 0;
    }
  }
  /* playing */
  else if (G_game_mode == GAME_MODE_PLAYING)
  {
    if ( (G_current_hud_flags & CONTROLS_HUD_FLAG_CANCEL) &&
              (!(G_last_hud_flags & CONTROLS_HUD_FLAG_CANCEL)))
    {
      G_game_mode = GAME_MODE_MENU_PANEL;
      G_cursor_position = 0;
      return 0;
    }
    else if ( (G_current_hud_flags & CONTROLS_HUD_FLAG_HELP) &&
              (!(G_last_hud_flags & CONTROLS_HUD_FLAG_HELP)))
    {
      G_game_mode = GAME_MODE_HELP_SCREEN;
      G_cursor_position = 0;
      return 0;
    }
    else if ( (G_current_hud_flags & CONTROLS_HUD_FLAG_ROOM_SELECT) &&
              (!(G_last_hud_flags & CONTROLS_HUD_FLAG_ROOM_SELECT)))
    {
      G_game_mode = GAME_MODE_ROOM_SELECT_PANEL;
      G_cursor_position = G_current_level_index % 15;
      return 0;
    }
    else if ( (G_current_hud_flags & CONTROLS_HUD_FLAG_PAUSE) &&
              (!(G_last_hud_flags & CONTROLS_HUD_FLAG_PAUSE)))
    {
      G_game_mode = GAME_MODE_PAUSED;
      doremi_play_sfx(SFX_INDEX_PAUSE);
      doremi_pause_music();
      return 0;
    }
    else if ( (G_current_hud_flags & CONTROLS_HUD_FLAG_RESTART) &&
              (!(G_last_hud_flags & CONTROLS_HUD_FLAG_RESTART)))
    {
      G_game_mode = GAME_MODE_TRY_AGAIN_PANEL;
      G_cursor_position = 0;
      return 0;
    }
    else if ( (G_current_hud_flags & CONTROLS_HUD_FLAG_OPTIONS) &&
              (!(G_last_hud_flags & CONTROLS_HUD_FLAG_OPTIONS)))
    {
      G_game_mode = GAME_MODE_OPTIONS_PANEL;
      G_cursor_position = 0;
      return 0;
    }
  }
  /* paused */
  else if (G_game_mode == GAME_MODE_PAUSED)
  {
    if ((G_current_hud_flags & CONTROLS_HUD_FLAG_CANCEL) &&
        (!(G_last_hud_flags & CONTROLS_HUD_FLAG_CANCEL)))
    {
      G_game_mode = GAME_MODE_PLAYING;
      doremi_play_sfx(SFX_INDEX_PAUSE);
      doremi_unpause_music();
      return 0;
    }
    else if ( (G_current_hud_flags & CONTROLS_HUD_FLAG_PAUSE) &&
              (!(G_last_hud_flags & CONTROLS_HUD_FLAG_PAUSE)))
    {
      G_game_mode = GAME_MODE_PLAYING;
      doremi_play_sfx(SFX_INDEX_PAUSE);
      doremi_unpause_music();
      return 0;
    }
  }
  /* room select panel */
  else if (G_game_mode == GAME_MODE_ROOM_SELECT_PANEL)
  {
    /* switch to new room */
    if ((G_current_hud_flags & CONTROLS_HUD_FLAG_CONFIRM) &&
        (!(G_last_hud_flags & CONTROLS_HUD_FLAG_CONFIRM)))
    {
      G_next_level_index = (G_current_level_index / 15) * 15;
      G_next_level_index += G_cursor_position;
      globals_set_episode_world_floor_room(G_next_level_index);
      doremi_play_sfx(SFX_INDEX_MENU_SELECT);

      G_game_mode = GAME_MODE_ROOM_TRANSITION;
      G_room_transition_frame = 60;
    }
    /* close panel */
    else if ( (G_current_hud_flags & CONTROLS_HUD_FLAG_CANCEL) &&
              (!(G_last_hud_flags & CONTROLS_HUD_FLAG_CANCEL)))
    {
      G_game_mode = GAME_MODE_PLAYING;
      return 0;
    }
    /* close panel */
    else if ( (G_current_hud_flags & CONTROLS_HUD_FLAG_ROOM_SELECT) &&
              (!(G_last_hud_flags & CONTROLS_HUD_FLAG_ROOM_SELECT)))
    {
      G_game_mode = GAME_MODE_PLAYING;
      return 0;
    }
  }
  /* options panel */
  else if (G_game_mode == GAME_MODE_OPTIONS_PANEL)
  {
    if ((G_current_hud_flags & CONTROLS_HUD_FLAG_CANCEL) &&
        (!(G_last_hud_flags & CONTROLS_HUD_FLAG_CANCEL)))
    {
      G_game_mode = GAME_MODE_PLAYING;
      return 0;
    }
    else if ( (G_current_hud_flags & CONTROLS_HUD_FLAG_OPTIONS) &&
              (!(G_last_hud_flags & CONTROLS_HUD_FLAG_OPTIONS)))
    {
      G_game_mode = GAME_MODE_PLAYING;
      return 0;
    }
  }
  /* help screen */
  else if (G_game_mode == GAME_MODE_HELP_SCREEN)
  {
    if ((G_current_hud_flags & CONTROLS_HUD_FLAG_CANCEL) &&
        (!(G_last_hud_flags & CONTROLS_HUD_FLAG_CANCEL)))
    {
      G_game_mode = GAME_MODE_PLAYING;
      return 0;
    }
    else if ( (G_current_hud_flags & CONTROLS_HUD_FLAG_HELP) &&
              (!(G_last_hud_flags & CONTROLS_HUD_FLAG_HELP)))
    {
      G_game_mode = GAME_MODE_PLAYING;
      return 0;
    }
  }
  /* try again panel */
  else if (G_game_mode == GAME_MODE_TRY_AGAIN_PANEL)
  {
    if ((G_current_hud_flags & CONTROLS_HUD_FLAG_CONFIRM) &&
        (!(G_last_hud_flags & CONTROLS_HUD_FLAG_CONFIRM)))
    {
      /* yes selected */
      if (G_cursor_position == 0)
      {
        level_load_to_world(&G_levels_all[G_current_level_index]);
        logic_setup_level();
        G_game_state_flags = GLOBAL_GAME_STATE_FLAGS_CLEAR;
        G_time_elapsed_ms = 0;

        /* update world */
        world_update_animations();

        /* light pumpkins, etc */
        logic_set_enemy_animations_based_on_player_position();

        G_game_mode = GAME_MODE_PLAYING;
        return 0;
      }
      /* no selected */
      else if (G_cursor_position == 1)
      {
        if ((G_game_state_flags & GLOBAL_GAME_STATE_FLAG_DEAD) ||
            (G_game_state_flags & GLOBAL_GAME_STATE_FLAG_BLOOD_LOST))
        {
          G_game_mode = GAME_MODE_WORLD_SELECT;
          save_game_write();
          doremi_play_music(MUSIC_TYPE_MAIN_MENU);
          G_cursor_position = (G_current_level_index / 15) % 22;
          G_silver_cursor_frame = 0;
          return 0;
        }
        else
        {
          G_game_mode = GAME_MODE_PLAYING;
          return 0;
        }
      }
    }
    else if ( (G_current_hud_flags & CONTROLS_HUD_FLAG_CANCEL) &&
              (!(G_last_hud_flags & CONTROLS_HUD_FLAG_CANCEL)))
    {
      if ((G_game_state_flags & GLOBAL_GAME_STATE_FLAG_DEAD) ||
          (G_game_state_flags & GLOBAL_GAME_STATE_FLAG_BLOOD_LOST))
      {
        G_game_mode = GAME_MODE_WORLD_SELECT;
        save_game_write();
        doremi_play_music(MUSIC_TYPE_MAIN_MENU);
        G_cursor_position = (G_current_level_index / 15) % 22;
        G_silver_cursor_frame = 0;
        return 0;
      }
      else
      {
        G_game_mode = GAME_MODE_PLAYING;
        return 0;
      }
    }
    else if ( (G_current_hud_flags & CONTROLS_HUD_FLAG_RESTART) &&
              (!(G_last_hud_flags & CONTROLS_HUD_FLAG_RESTART)))
    {
      if ((G_game_state_flags & GLOBAL_GAME_STATE_FLAG_DEAD) ||
          (G_game_state_flags & GLOBAL_GAME_STATE_FLAG_BLOOD_LOST))
      {
        G_game_mode = GAME_MODE_WORLD_SELECT;
        save_game_write();
        doremi_play_music(MUSIC_TYPE_MAIN_MENU);
        G_cursor_position = (G_current_level_index / 15) % 22;
        G_silver_cursor_frame = 0;
        return 0;
      }
      else
      {
        G_game_mode = GAME_MODE_PLAYING;
        return 0;
      }
    }
  }
  /* menu panel */
  else if (G_game_mode == GAME_MODE_MENU_PANEL)
  {
    if ((G_current_hud_flags & CONTROLS_HUD_FLAG_CONFIRM) &&
        (!(G_last_hud_flags & CONTROLS_HUD_FLAG_CONFIRM)))
    {
      /* back to game selected */
      if (G_cursor_position == 0)
      {
        G_game_mode = GAME_MODE_PLAYING;
        return 0;
      }
      /* retry room selected */
      else if (G_cursor_position == 1)
      {
        G_game_mode = GAME_MODE_TRY_AGAIN_PANEL;
        G_cursor_position = 0;
        return 0;
      }
      /* room select selected */
      else if (G_cursor_position == 2)
      {
        G_game_mode = GAME_MODE_ROOM_SELECT_PANEL;
        G_cursor_position = 0;
        return 0;
      }
      /* help screen selected */
      else if (G_cursor_position == 3)
      {
        G_game_mode = GAME_MODE_HELP_SCREEN;
        G_cursor_position = 0;
        return 0;
      }
      /* options panel selected */
      else if (G_cursor_position == 4)
      {
        G_game_mode = GAME_MODE_OPTIONS_PANEL;
        G_cursor_position = 0;
        return 0;
      }
      /* quit selected */
      else if (G_cursor_position == 5)
      {
        G_game_mode = GAME_MODE_WORLD_SELECT;
        save_game_write();
        doremi_play_music(MUSIC_TYPE_MAIN_MENU);
        G_cursor_position = (G_current_level_index / 15) % 22;
        G_silver_cursor_frame = 0;
        return 0;
      }
    }
    else if ( (G_current_hud_flags & CONTROLS_HUD_FLAG_CANCEL) &&
              (!(G_last_hud_flags & CONTROLS_HUD_FLAG_CANCEL)))
    {
      G_game_mode = GAME_MODE_PLAYING;
      return 0;
    }
  }

  /* update frame based on mode */
  /* paused */
  if (G_game_mode == GAME_MODE_PAUSED)
  {
    return 0;
  }
  /* title screen */
  else if (G_game_mode == GAME_MODE_TITLE_SCREEN)
  {
    /* update cursor frame */
    if (G_silver_cursor_frame <= 0)
      G_silver_cursor_frame = 47;
    else
      G_silver_cursor_frame -= 1;

    /* move cursor */
    if ((G_current_input_flags & CONTROLS_INPUT_FLAG_UP) &&
        (!(G_last_input_flags & CONTROLS_INPUT_FLAG_UP)))
    {
      if (((G_cursor_position > 0) && (G_cursor_position <= 2)) ||
          (G_cursor_position == 7))
      {
        G_cursor_position -= 1;
        doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
      }
    }
    else if ( (G_current_input_flags & CONTROLS_INPUT_FLAG_DOWN) &&
              (!(G_last_input_flags & CONTROLS_INPUT_FLAG_DOWN)))
    {
      if (((G_cursor_position >= 0) && (G_cursor_position < 2)) ||
          (G_cursor_position == 6))
      {
        G_cursor_position += 1;
        doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
      }
    }
    else if ( (G_current_input_flags & CONTROLS_INPUT_FLAG_LEFT) &&
              (!(G_last_input_flags & CONTROLS_INPUT_FLAG_LEFT)))
    {
      if ((G_cursor_position > 3) && (G_cursor_position <= 5))
      {
        G_cursor_position -= 1;
        G_save_game_number = G_cursor_position - 2;

        if (save_game_read())
        {
          save_game_reset();
          G_save_game_percentage = 255;
        }

        doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
      }
    }
    else if ( (G_current_input_flags & CONTROLS_INPUT_FLAG_RIGHT) &&
              (!(G_last_input_flags & CONTROLS_INPUT_FLAG_RIGHT)))
    {
      if ((G_cursor_position >= 3) && (G_cursor_position < 5))
      {
        G_cursor_position += 1;
        G_save_game_number = G_cursor_position - 2;

        if (save_game_read())
        {
          save_game_reset();
          G_save_game_percentage = 255;
        }

        doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
      }
    }
  }
  /* credits */
  else if (G_game_mode == GAME_MODE_CREDITS)
  {
    return 0;
  }
  /* world select */
  else if (G_game_mode == GAME_MODE_WORLD_SELECT)
  {
    /* update cursor frame */
    if (G_silver_cursor_frame <= 0)
      G_silver_cursor_frame = 47;
    else
      G_silver_cursor_frame -= 1;

    /* move cursor */
    if ((G_current_input_flags & CONTROLS_INPUT_FLAG_LEFT) &&
        (!(G_last_input_flags & CONTROLS_INPUT_FLAG_LEFT)))
    {
      if ((G_cursor_position >= 3) && (G_cursor_position < 18))
      {
        G_cursor_position = ((G_cursor_position - 3) / 3) * 3;
        doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
      }
      else if ((G_cursor_position >= 18) && (G_cursor_position <= 21))
      {
        if (SAVE_GAME_WORLD_IS_COMPLETE(14))
          G_cursor_position = 15;
        else if (SAVE_GAME_WORLD_IS_COMPLETE(11))
          G_cursor_position = 12;
        else if (SAVE_GAME_WORLD_IS_COMPLETE(8))
          G_cursor_position = 9;
        else if (SAVE_GAME_WORLD_IS_COMPLETE(5))
          G_cursor_position = 6;
        else if (SAVE_GAME_WORLD_IS_COMPLETE(2))
          G_cursor_position = 3;
        else
          G_cursor_position = 0;

        doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
      }
    }
    else if ( (G_current_input_flags & CONTROLS_INPUT_FLAG_RIGHT) &&
              (!(G_last_input_flags & CONTROLS_INPUT_FLAG_RIGHT)))
    {
      if ((G_cursor_position >= 0) && (G_cursor_position < 3))
      {
        if (SAVE_GAME_WORLD_IS_COMPLETE(2))
        {
          G_cursor_position = 3;
          doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
        }
        else if (G_save_game_3_and_1_2_floppies >= 6)
        {
          G_cursor_position = 18;
          doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
        }
      }
      else if ((G_cursor_position >= 3) && (G_cursor_position < 6))
      {
        if (SAVE_GAME_WORLD_IS_COMPLETE(5))
        {
          G_cursor_position = 6;
          doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
        }
        else if (G_save_game_3_and_1_2_floppies >= 6)
        {
          G_cursor_position = 18;
          doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
        }
      }
      else if ((G_cursor_position >= 6) && (G_cursor_position < 9))
      {
        if (SAVE_GAME_WORLD_IS_COMPLETE(8))
        {
          G_cursor_position = 9;
          doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
        }
        else if (G_save_game_3_and_1_2_floppies >= 6)
        {
          G_cursor_position = 18;
          doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
        }
      }
      else if ((G_cursor_position >= 9) && (G_cursor_position < 12))
      {
        if (SAVE_GAME_WORLD_IS_COMPLETE(11))
        {
          G_cursor_position = 12;
          doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
        }
        else if (G_save_game_3_and_1_2_floppies >= 6)
        {
          G_cursor_position = 18;
          doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
        }
      }
      else if ((G_cursor_position >= 12) && (G_cursor_position < 15))
      {
        if (SAVE_GAME_WORLD_IS_COMPLETE(14))
        {
          G_cursor_position = 15;
          doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
        }
        else if (G_save_game_3_and_1_2_floppies >= 6)
        {
          G_cursor_position = 18;
          doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
        }
      }
      else if ((G_cursor_position >= 15) && (G_cursor_position < 18))
      {
        if (G_save_game_3_and_1_2_floppies >= 6)
        {
          G_cursor_position = 18;
          doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
        }
      }
    }
    else if ( (G_current_input_flags & CONTROLS_INPUT_FLAG_UP) &&
              (!(G_last_input_flags & CONTROLS_INPUT_FLAG_UP)))
    {
      if ((G_cursor_position >= 0) && (G_cursor_position < 18) && 
          ((G_cursor_position % 3) > 0))
      {
        G_cursor_position -= 1;
        doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
      }
      else if ((G_cursor_position > 18) && (G_cursor_position <= 21))
      {
        G_cursor_position -= 1;
        doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
      }
    }
    else if ( (G_current_input_flags & CONTROLS_INPUT_FLAG_DOWN) &&
              (!(G_last_input_flags & CONTROLS_INPUT_FLAG_DOWN)))
    {
      if ((G_cursor_position >= 0) && (G_cursor_position < 18) && 
          ((G_cursor_position % 3) < 2))
      {
        if (SAVE_GAME_WORLD_IS_COMPLETE(G_cursor_position))
        {
          G_cursor_position += 1;
          doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
        }
      }
      else if ( (G_cursor_position == 18) && 
                (G_save_game_3_and_1_2_floppies >= 12))
      {
        G_cursor_position += 1;
        doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
      }
      else if ( (G_cursor_position == 19) && 
                (G_save_game_3_and_1_2_floppies == 18))
      {
        G_cursor_position += 1;
        doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
      }
      else if ( (G_cursor_position == 20) && 
                (G_save_game_5_and_1_4_floppies == 3))
      {
        G_cursor_position += 1;
        doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
      }
    }

    return 0;
  }
  /* story select */
  else if (G_game_mode == GAME_MODE_STORY_SELECT)
  {
    /* update cursor frame */
    if (G_silver_cursor_frame <= 0)
      G_silver_cursor_frame = 47;
    else
      G_silver_cursor_frame -= 1;

    /* move cursor */
    if ((G_current_input_flags & CONTROLS_INPUT_FLAG_LEFT) &&
        (!(G_last_input_flags & CONTROLS_INPUT_FLAG_LEFT)))
    {
      if ((G_cursor_position >= 10) && (G_cursor_position <= 19))
      {
        G_cursor_position = 0;
        doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
      }
    }
    else if ( (G_current_input_flags & CONTROLS_INPUT_FLAG_RIGHT) &&
              (!(G_last_input_flags & CONTROLS_INPUT_FLAG_RIGHT)))
    {
      if (((G_cursor_position >= 0) && (G_cursor_position <= 9))  &&
          (SAVE_GAME_WORLD_IS_COMPLETE(9)))
      {
        G_cursor_position = 10;
        doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
      }
    }
    else if ( (G_current_input_flags & CONTROLS_INPUT_FLAG_UP) &&
              (!(G_last_input_flags & CONTROLS_INPUT_FLAG_UP)))
    {
      if (((G_cursor_position > 0) && (G_cursor_position <= 9)) ||
          ((G_cursor_position > 10) && (G_cursor_position <= 19)))
      {
        if ((G_cursor_position == 19) && (!(SAVE_GAME_WORLD_IS_COMPLETE(17))))
          G_cursor_position -= 2;
        else
          G_cursor_position -= 1;

        doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
      }
    }
    else if ( (G_current_input_flags & CONTROLS_INPUT_FLAG_DOWN) &&
              (!(G_last_input_flags & CONTROLS_INPUT_FLAG_DOWN)))
    {
      if (((G_cursor_position == 0) && (SAVE_GAME_WORLD_IS_COMPLETE(0)))    ||
          ((G_cursor_position == 1) && (SAVE_GAME_WORLD_IS_COMPLETE(1)))    ||
          ((G_cursor_position == 2) && (SAVE_GAME_WORLD_IS_COMPLETE(2)))    ||
          ((G_cursor_position == 3) && (SAVE_GAME_WORLD_IS_COMPLETE(3)))    ||
          ((G_cursor_position == 4) && (SAVE_GAME_WORLD_IS_COMPLETE(4)))    ||
          ((G_cursor_position == 5) && (SAVE_GAME_WORLD_IS_COMPLETE(5)))    ||
          ((G_cursor_position == 6) && (SAVE_GAME_WORLD_IS_COMPLETE(6)))    ||
          ((G_cursor_position == 7) && (SAVE_GAME_WORLD_IS_COMPLETE(7)))    ||
          ((G_cursor_position == 8) && (SAVE_GAME_WORLD_IS_COMPLETE(8)))    ||
          ((G_cursor_position == 10) && (SAVE_GAME_WORLD_IS_COMPLETE(10)))  ||
          ((G_cursor_position == 11) && (SAVE_GAME_WORLD_IS_COMPLETE(11)))  ||
          ((G_cursor_position == 12) && (SAVE_GAME_WORLD_IS_COMPLETE(12)))  ||
          ((G_cursor_position == 13) && (SAVE_GAME_WORLD_IS_COMPLETE(13)))  ||
          ((G_cursor_position == 14) && (SAVE_GAME_WORLD_IS_COMPLETE(14)))  ||
          ((G_cursor_position == 15) && (SAVE_GAME_WORLD_IS_COMPLETE(15)))  ||
          ((G_cursor_position == 16) && (SAVE_GAME_WORLD_IS_COMPLETE(16)))  ||
          ((G_cursor_position == 17) && (SAVE_GAME_WORLD_IS_COMPLETE(17)))  ||
          ((G_cursor_position == 18) && (SAVE_GAME_WORLD_IS_COMPLETE(21))))
      {
        G_cursor_position += 1;
        doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
      }
      else if ((G_cursor_position == 17) && (SAVE_GAME_WORLD_IS_COMPLETE(21)))
      {
        G_cursor_position += 2;
        doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
      }
    }

    return 0;
  }
  /* story scene, intermission */
  else if ( (G_game_mode == GAME_MODE_STORY_SCENE)  ||
            (G_game_mode == GAME_MODE_INTERMISSION))
  {
    /* change page */
    if ((G_current_input_flags & CONTROLS_INPUT_FLAG_LEFT) &&
        (!(G_last_input_flags & CONTROLS_INPUT_FLAG_LEFT)))
    {
      if (STORY_SCENE_HAS_3_PAGES())
      {
        if ((G_cursor_position > 0) && (G_cursor_position <= 2))
        {
          G_cursor_position -= 1;
          doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
        }
      }
      else if (STORY_SCENE_HAS_4_PAGES())
      {
        if ((G_cursor_position > 0) && (G_cursor_position <= 3))
        {
          G_cursor_position -= 1;
          doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
        }
      }
    }
    else if ( (G_current_input_flags & CONTROLS_INPUT_FLAG_RIGHT) &&
              (!(G_last_input_flags & CONTROLS_INPUT_FLAG_RIGHT)))
    {
      if (STORY_SCENE_HAS_3_PAGES())
      {
        if ((G_cursor_position >= 0) && (G_cursor_position < 2))
        {
          G_cursor_position += 1;
          doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
        }
      }
      else if (STORY_SCENE_HAS_4_PAGES())
      {
        if ((G_cursor_position >= 0) && (G_cursor_position < 3))
        {
          G_cursor_position += 1;
          doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
        }
      }
    }

    return 0;
  }
  /* room select panel */
  else if (G_game_mode == GAME_MODE_ROOM_SELECT_PANEL)
  {
    /* move cursor */
    if ((G_current_input_flags & CONTROLS_INPUT_FLAG_LEFT) &&
        (!(G_last_input_flags & CONTROLS_INPUT_FLAG_LEFT)))
    {
      if ((G_cursor_position % 5) > 0)
      {
        G_cursor_position -= 1;
        doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
      }
    }
    else if ( (G_current_input_flags & CONTROLS_INPUT_FLAG_RIGHT) &&
              (!(G_last_input_flags & CONTROLS_INPUT_FLAG_RIGHT)))
    {
      if ((G_cursor_position % 5) < 4)
      {
        G_cursor_position += 1;
        doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
      }
    }
    else if ( (G_current_input_flags & CONTROLS_INPUT_FLAG_UP) &&
              (!(G_last_input_flags & CONTROLS_INPUT_FLAG_UP)))
    {
      if ((((G_cursor_position / 5) == 1) && 
          (current_world_flags & SAVE_GAME_FLAG_FLOOR_2)) ||
          (((G_cursor_position / 5) == 0) && 
          (current_world_flags & SAVE_GAME_FLAG_FLOOR_1)))
      {
        G_cursor_position += 5;
        doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
      }
    }
    else if ( (G_current_input_flags & CONTROLS_INPUT_FLAG_DOWN) &&
              (!(G_last_input_flags & CONTROLS_INPUT_FLAG_DOWN)))
    {
      if ((G_cursor_position / 5) > 0)
      {
        G_cursor_position -= 5;
        doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
      }
    }

    return 0;
  }
  /* options panel */
  else if (G_game_mode == GAME_MODE_OPTIONS_PANEL)
  {
    /* move cursor */
    if ((G_current_input_flags & CONTROLS_INPUT_FLAG_UP) &&
        (!(G_last_input_flags & CONTROLS_INPUT_FLAG_UP)))
    {
      if ((G_cursor_position > 0) && (G_cursor_position <= 2))
      {
        G_cursor_position -= 1;
        doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
      }
    }
    else if ( (G_current_input_flags & CONTROLS_INPUT_FLAG_DOWN) &&
              (!(G_last_input_flags & CONTROLS_INPUT_FLAG_DOWN)))
    {
      if ((G_cursor_position >= 0) && (G_cursor_position < 2))
      {
        G_cursor_position += 1;
        doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
      }
    }

    /* change settings */
    if ((G_current_input_flags & CONTROLS_INPUT_FLAG_LEFT) &&
        (!(G_last_input_flags & CONTROLS_INPUT_FLAG_LEFT)))
    {
      /* music volume down */
      if ((G_cursor_position == 0) && (G_music_volume > 0))
      {
        G_music_volume -= 16;
        doremi_set_music_volume();
        doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
      }
      /* sfx volume down */
      else if ((G_cursor_position == 1) && (G_sfx_volume > 0))
      {
        G_sfx_volume -= 16;
        doremi_set_sfx_volume();
        doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
      }
      /* window size down */
      else if ( (G_cursor_position == 2)    && 
                (G_fullscreen_flag == 0x00) && 
                (G_window_h > GRAFX_WINDOW_HEIGHT_OPTION_1))
      {
        grafx_decrease_window_size();
        doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
      }
    }
    else if ( (G_current_input_flags & CONTROLS_INPUT_FLAG_RIGHT) &&
              (!(G_last_input_flags & CONTROLS_INPUT_FLAG_RIGHT)))
    {
      /* music volume up */
      if ((G_cursor_position == 0) && (G_music_volume < 128))
      {
        G_music_volume += 16;
        doremi_set_music_volume();
        doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
      }
      /* sfx volume up */
      else if ((G_cursor_position == 1) && (G_sfx_volume < 128))
      {
        G_sfx_volume += 16;
        doremi_set_sfx_volume();
        doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
      }
      /* window size up */
      else if ( (G_cursor_position == 2)    && 
                (G_fullscreen_flag == 0x00) && 
                (G_window_h < GRAFX_WINDOW_HEIGHT_OPTION_4))
      {
        if ((G_window_h == GRAFX_WINDOW_HEIGHT_OPTION_1)  &&
            (G_desktop_w > GRAFX_WINDOW_WIDTH_OPTION_2)   &&
            (G_desktop_h > GRAFX_WINDOW_HEIGHT_OPTION_2))
        {
          grafx_increase_window_size();
          doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
        }
        else if ( (G_window_h == GRAFX_WINDOW_HEIGHT_OPTION_2)  &&
                  (G_desktop_w > GRAFX_WINDOW_WIDTH_OPTION_3)   &&
                  (G_desktop_h > GRAFX_WINDOW_HEIGHT_OPTION_3))
        {
          grafx_increase_window_size();
          doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
        }
        else if ( (G_window_h == GRAFX_WINDOW_HEIGHT_OPTION_3)  &&
                  (G_desktop_w > GRAFX_WINDOW_WIDTH_OPTION_4)   &&
                  (G_desktop_h > GRAFX_WINDOW_HEIGHT_OPTION_4))
        {
          grafx_increase_window_size();
          doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
        }
      }
    }

    return 0;
  }
  /* help screen */
  else if (G_game_mode == GAME_MODE_HELP_SCREEN)
  {
    /* change page */
    if ((G_current_input_flags & CONTROLS_INPUT_FLAG_LEFT) &&
        (!(G_last_input_flags & CONTROLS_INPUT_FLAG_LEFT)))
    {
      if ((G_cursor_position > 0) && (G_cursor_position <= 28))
      {
        G_cursor_position -= 1;
        doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
      }
    }
    else if ( (G_current_input_flags & CONTROLS_INPUT_FLAG_RIGHT) &&
              (!(G_last_input_flags & CONTROLS_INPUT_FLAG_RIGHT)))
    {
      if ((G_cursor_position >= 0) && (G_cursor_position < 28))
      {
        G_cursor_position += 1;
        doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
      }
    }
  }
  /* try again panel */
  else if (G_game_mode == GAME_MODE_TRY_AGAIN_PANEL)
  {
    /* move cursor */
    if ((G_current_input_flags & CONTROLS_INPUT_FLAG_UP) &&
        (!(G_last_input_flags & CONTROLS_INPUT_FLAG_UP)))
    {
      if ((G_cursor_position > 0) && (G_cursor_position <= 1))
      {
        G_cursor_position -= 1;
        doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
      }
    }
    else if ( (G_current_input_flags & CONTROLS_INPUT_FLAG_DOWN) &&
              (!(G_last_input_flags & CONTROLS_INPUT_FLAG_DOWN)))
    {
      if ((G_cursor_position >= 0) && (G_cursor_position < 1))
      {
        G_cursor_position += 1;
        doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
      }
    }
  }
  /* menu panel */
  else if (G_game_mode == GAME_MODE_MENU_PANEL)
  {
    /* move cursor */
    if ((G_current_input_flags & CONTROLS_INPUT_FLAG_UP) &&
        (!(G_last_input_flags & CONTROLS_INPUT_FLAG_UP)))
    {
      if ((G_cursor_position > 0) && (G_cursor_position <= 5))
      {
        G_cursor_position -= 1;
        doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
      }
    }
    else if ( (G_current_input_flags & CONTROLS_INPUT_FLAG_DOWN) &&
              (!(G_last_input_flags & CONTROLS_INPUT_FLAG_DOWN)))
    {
      if ((G_cursor_position >= 0) && (G_cursor_position < 5))
      {
        G_cursor_position += 1;
        doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
      }
    }
  }
  /* playing */
  else if (G_game_mode == GAME_MODE_PLAYING)
  {
    /* if player has pressed a key, start the level */
    if (G_current_input_flags)
    {
      G_game_state_flags |= GLOBAL_GAME_STATE_FLAG_STARTED;
    }

    /* if evil eye is cast, the game is paused as the */
    /* evil eye spell approaches the player.          */
    if (G_game_state_flags & GLOBAL_GAME_STATE_FLAG_EVIL_EYE_CAST)
    {
      logic_evil_eye_update();
    }
    /* if a blood vial was lost, pause */
    else if (G_game_state_flags & GLOBAL_GAME_STATE_FLAG_BLOOD_LOST)
    {
      /* update world */
      world_update_particles();
    }
    /* if player has not pressed a key, wait */
    else if (!(G_game_state_flags & GLOBAL_GAME_STATE_FLAG_STARTED))
    {
      /* update world */
      world_update_animations();

      /* light pumpkins, etc */
      logic_set_enemy_animations_based_on_player_position();
    }
    else
    {
      /* process controller input */
      controls_process_player_input();

      /* enemy movements */
      logic_enemy_movements();

      /* convey entities */
      logic_convey_entities();

      /* update world */
      world_update_particles();
      world_update_positions();
      world_update_cooldowns();
      world_update_spins();
      world_update_animations();

      /* update spatial partitioning grid */
      collide_grid_update();

      /* check entities that stopped this frame */
      logic_movement_conclusions();

      /* check active switches */
      logic_check_active_switches();

      /* process levers */
      logic_process_lever_and_switch_flags();

      /* activate floor triggers */
      logic_activate_floor_triggers();

      /* light pumpkins, etc */
      logic_set_enemy_animations_based_on_player_position();

      /* activate venusian roots */
      logic_activate_venusian_roots();

      /* check frogs */
      logic_check_frogs();

      /* process reflections */
      logic_process_reflections();

      /* check spell casters */
      logic_check_spell_casters();

      /* check evil eye casters */
      logic_check_evil_eye_casters();

      /* cast spells */
      logic_process_spell_casting();

      /* if evil eye was cast, skip remaining steps */
      if (!(G_game_state_flags & GLOBAL_GAME_STATE_FLAG_EVIL_EYE_CAST))
      {
        /* process collisions */
        pair_trees_and_lists_process_collisions();

        /* handle warps */
        pair_trees_and_lists_consolidate_warps();
        logic_process_warps();

        /* process awaiting destructions and transformations */
        logic_process_awaiting();

        /* process solomons seals */
        logic_process_solomons_seals();

        /* process damage and transformations this frame */
        logic_process_damage_and_transformations();
      }
    }

    /* if player died this frame, or blood vial was lost, force restart */
    if ((G_game_state_flags & GLOBAL_GAME_STATE_FLAG_DEAD) ||
        (G_game_state_flags & GLOBAL_GAME_STATE_FLAG_BLOOD_LOST))
    {
      G_game_mode = GAME_MODE_TRY_AGAIN_PANEL;
      G_cursor_position = 0;
    }
  }

  return 0;
}

