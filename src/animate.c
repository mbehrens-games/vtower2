/*******************************************************************************
** animate.c (animation handling)
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "animate.h"
#include "entity.h"

unsigned char G_animation_portcullis_open[3] = {15, 14, 13};
unsigned char G_animation_water[8] = {1, 16, 17, 2, 17, 16, 1, 0};
unsigned char G_animation_yin_yang[8] = {8, 15, 14, 13, 12, 11, 10, 9};
unsigned char G_animation_ice_cube_submerged[3] = {31, 30, 30};
unsigned char G_animation_aqua_fortis[4] = {30, 22, 14, 6};
unsigned char G_animation_aqua_fortis_cracked[4] = {31, 23, 15, 7};
unsigned char G_animation_aqua_explodis[4] = {62, 54, 46, 38};
unsigned char G_animation_aqua_explodis_cracked[4] = {63, 55, 47, 39};
unsigned char G_animation_candle_lit[3] = {19, 18, 17};
unsigned char G_animation_ice_cube[3] = {21, 20, 20};
unsigned char G_animation_eight_ball_right[4] = {44, 41, 45, 40};
unsigned char G_animation_eight_ball_up[4] = {43, 41, 42, 40};
unsigned char G_animation_eight_ball_left[4] = {45, 41, 44, 40};
unsigned char G_animation_eight_ball_down[4] = {42, 41, 43, 40};
unsigned char G_animation_mahjong_tile_east[2] = {24, 25};
unsigned char G_animation_mahjong_tile_north[2] = {26, 27};
unsigned char G_animation_mahjong_tile_west[2] = {32, 33};
unsigned char G_animation_mahjong_tile_south[2] = {34, 35};
unsigned char G_animation_mahjong_tile_east_submerged[2] = {32, 33};
unsigned char G_animation_mahjong_tile_north_submerged[2] = {34, 35};
unsigned char G_animation_mahjong_tile_west_submerged[2] = {40, 41};
unsigned char G_animation_mahjong_tile_south_submerged[2] = {42, 43};
unsigned char G_animation_ballista_red[7] = {0, 4, 3, 2, 1, 2, 1};
unsigned char G_animation_ballista_red_angled[7] = {8, 12, 11, 10, 9, 10, 9};
unsigned char G_animation_ballista_green[7] = {16, 20, 19, 18, 17, 18, 17};
unsigned char G_animation_ballista_green_angled[7] = {24, 28, 27, 26, 25, 26, 25};
unsigned char G_animation_ballista_brown[7] = {32, 36, 35, 34, 33, 34, 33};
unsigned char G_animation_ballista_brown_angled[7] = {40, 44, 43, 42, 41, 42, 41};
unsigned char G_animation_conveyer_white[3] = {63, 62, 61};
unsigned char G_animation_conveyer_cyan[3] = {55, 54, 53};
unsigned char G_animation_conveyer_magenta[3] = {59, 58, 57};
unsigned char G_animation_floor_spike_down_white[3] = {196, 197, 212};
unsigned char G_animation_floor_spike_down_cyan[3] = {192, 193, 208};
unsigned char G_animation_floor_spike_down_magenta[3] = {194, 195, 210};
unsigned char G_animation_floor_spike_up_white[3] = {213, 212, 197};
unsigned char G_animation_floor_spike_up_cyan[3] = {209, 208, 193};
unsigned char G_animation_floor_spike_up_magenta[3] = {211, 210, 195};
unsigned char G_animation_lever_white_off[2] = {16, 17};
unsigned char G_animation_lever_cyan_off[2] = {0, 1};
unsigned char G_animation_lever_magenta_off[2] = {8, 9};
unsigned char G_animation_lever_white_on[2] = {18, 17};
unsigned char G_animation_lever_cyan_on[2] = {2, 1};
unsigned char G_animation_lever_magenta_on[2] = {10, 9};
unsigned char G_animation_spin_switch_red_ccw[4] = {32, 56, 48, 40};
unsigned char G_animation_spin_switch_red_cw[4] = {4, 7, 6, 5};
unsigned char G_animation_spin_switch_green_ccw[4] = {33, 57, 49, 41};
unsigned char G_animation_spin_switch_green_cw[4] = {12, 15, 14, 13};
unsigned char G_animation_spin_switch_brown_ccw[4] = {34, 58, 50, 42};
unsigned char G_animation_spin_switch_brown_cw[4] = {20, 23, 22, 21};
unsigned char G_animation_number_switch_even[4] = {28, 29, 30, 29};
unsigned char G_animation_number_switch_odd[4] = {36, 37, 38, 37};
unsigned char G_animation_number_switch_prime[4] = {44, 45, 46, 45};
unsigned char G_animation_number_switch_composite[4] = {52, 53, 54, 53};
unsigned char G_animation_number_switch_square[4] = {60, 61, 62, 61};
unsigned char G_animation_number_switch_triangular[4] = {39, 47, 55, 47};
unsigned char G_animation_pumpkin_lit[4] = {41, 33, 40, 33};
unsigned char G_animation_ghost_awake_right[4] = {63, 61, 62, 61};
unsigned char G_animation_ghost_awake_up[4] = {55, 53, 54, 53};
unsigned char G_animation_ghost_awake_left[4] = {59, 57, 58, 57};
unsigned char G_animation_ghost_awake_down[4] = {51, 49, 50, 49};
unsigned char G_animation_mask_horizontal_smile[4] = {36, 34, 35, 34};
unsigned char G_animation_mask_horizontal_frown[4] = {39, 37, 38, 37};
unsigned char G_animation_mask_vertical_smile[4] = {44, 42, 43, 42};
unsigned char G_animation_mask_vertical_frown[4] = {47, 45, 46, 45};
unsigned char G_animation_snake_awake_right[2] = {46, 45};
unsigned char G_animation_snake_awake_up[2] = {38, 37};
unsigned char G_animation_snake_awake_left[2] = {42, 41};
unsigned char G_animation_snake_awake_down[2] = {34, 33};
unsigned char G_animation_faerie_right[2] = {49, 48};
unsigned char G_animation_faerie_up[2] = {51, 50};
unsigned char G_animation_faerie_left[2] = {53, 52};
unsigned char G_animation_faerie_down[2] = {55, 54};
unsigned char G_animation_venusian[6] = {57, 58, 59, 58, 57, 56};
unsigned char G_animation_venusian_root[4] = {61, 62, 61, 60};
unsigned char G_animation_witch_awake_right[2] = {38, 37};
unsigned char G_animation_witch_awake_up[2] = {30, 29};
unsigned char G_animation_witch_awake_left[2] = {34, 33};
unsigned char G_animation_witch_awake_down[2] = {26, 25};
unsigned char G_animation_undine_right[2] = {8, 0};
unsigned char G_animation_undine_up[2] = {9, 1};
unsigned char G_animation_undine_left[2] = {10, 2};
unsigned char G_animation_undine_down[2] = {11, 3};
unsigned char G_animation_sorceress_right[2] = {12, 4};
unsigned char G_animation_sorceress_up[2] = {13, 5};
unsigned char G_animation_sorceress_left[2] = {14, 6};
unsigned char G_animation_sorceress_down[2] = {15, 7};
unsigned char G_animation_imp_lt_right[4] = {2, 0, 1, 0};
unsigned char G_animation_imp_lt_up[4] = {10, 8, 9, 8};
unsigned char G_animation_imp_lt_left[4] = {18, 16, 17, 16};
unsigned char G_animation_imp_lt_down[4] = {26, 24, 25, 24};
unsigned char G_animation_imp_rt_right[4] = {6, 4, 5, 4};
unsigned char G_animation_imp_rt_up[4] = {14, 12, 13, 12};
unsigned char G_animation_imp_rt_left[4] = {22, 20, 21, 20};
unsigned char G_animation_imp_rt_down[4] = {30, 28, 29, 28};
unsigned char G_animation_lil_bot_right[4] = {34, 32, 33, 32};
unsigned char G_animation_lil_bot_up[4] = {42, 40, 41, 40};
unsigned char G_animation_lil_bot_left[4] = {50, 48, 49, 48};
unsigned char G_animation_lil_bot_down[4] = {58, 56, 57, 56};
unsigned char G_animation_poltergeist_right[6] = {44, 45, 46, 47, 46, 45};
unsigned char G_animation_poltergeist_up[6] = {36, 37, 38, 39, 38, 37};
unsigned char G_animation_poltergeist_left[6] = {40, 41, 42, 43, 42, 41};
unsigned char G_animation_poltergeist_down[6] = {32, 33, 34, 35, 34, 33};
unsigned char G_animation_wisp_left_wall[4] = {61, 53, 45, 37};
unsigned char G_animation_wisp_right_wall[4] = {62, 54, 46, 38};
unsigned char G_animation_wisp_left_wall_angry[4] = {61, 47, 45, 39};
unsigned char G_animation_wisp_right_wall_angry[4] = {62, 63, 46, 55};
unsigned char G_animation_jiangshi_lt_right[4] = {34, 32, 33, 32};
unsigned char G_animation_jiangshi_lt_up[4] = {42, 40, 41, 40};
unsigned char G_animation_jiangshi_lt_left[4] = {50, 48, 49, 48};
unsigned char G_animation_jiangshi_lt_down[4] = {58, 56, 57, 56};
unsigned char G_animation_jiangshi_lt_stopped[4] = {35, 43, 35, 51};
unsigned char G_animation_jiangshi_rt_right[4] = {38, 36, 37, 36};
unsigned char G_animation_jiangshi_rt_up[4] = {46, 44, 45, 44};
unsigned char G_animation_jiangshi_rt_left[4] = {54, 52, 53, 52};
unsigned char G_animation_jiangshi_rt_down[4] = {62, 60, 61, 60};
unsigned char G_animation_jiangshi_rt_stopped[4] = {39, 47, 39, 55};
unsigned char G_animation_mummy_lt_right[4] = {2, 0, 1, 0};
unsigned char G_animation_mummy_lt_up[4] = {10, 8, 9, 8};
unsigned char G_animation_mummy_lt_left[4] = {18, 16, 17, 16};
unsigned char G_animation_mummy_lt_down[4] = {26, 24, 25, 24};
unsigned char G_animation_mummy_lt_disintegrating[4] = {27, 19, 11, 3};
unsigned char G_animation_mummy_rt_right[4] = {6, 4, 5, 4};
unsigned char G_animation_mummy_rt_up[4] = {14, 12, 13, 12};
unsigned char G_animation_mummy_rt_left[4] = {22, 20, 21, 20};
unsigned char G_animation_mummy_rt_down[4] = {30, 28, 29, 28};
unsigned char G_animation_mummy_rt_disintegrating[4] = {31, 23, 15, 7};
unsigned char G_animation_guardian_lt_right[4] = {60, 44, 52, 44};
unsigned char G_animation_guardian_lt_up[4] = {61, 45, 53, 45};
unsigned char G_animation_guardian_lt_left[4] = {62, 46, 54, 46};
unsigned char G_animation_guardian_lt_down[4] = {63, 47, 55, 47};
unsigned char G_animation_guardian_rt_right[4] = {56, 40, 48, 40};
unsigned char G_animation_guardian_rt_up[4] = {57, 41, 49, 41};
unsigned char G_animation_guardian_rt_left[4] = {58, 42, 50, 42};
unsigned char G_animation_guardian_rt_down[4] = {59, 43, 51, 43};
unsigned char G_animation_laser_gun_right[4] = {48, 51, 50, 49};
unsigned char G_animation_laser_gun_up_right[4] = {52, 55, 54, 53};
unsigned char G_animation_laser_gun_left[4] = {56, 59, 58, 57};
unsigned char G_animation_laser_gun_down_left[4] = {60, 63, 62, 61};
unsigned char G_animation_blood_vial[8] = {49, 57, 49, 25, 33, 41, 33, 25};
unsigned char G_animation_bat_vial[8] = {50, 58, 50, 26, 34, 42, 34, 26};
unsigned char G_animation_blue_mana[8] = {51, 59, 51, 27, 35, 43, 35, 27};
unsigned char G_animation_green_mana[8] = {52, 60, 52, 28, 36, 44, 36, 28};
unsigned char G_animation_floppy_disk_3_and_1_2[8] = {53, 61, 53, 29, 37, 45, 37, 29};
unsigned char G_animation_floppy_disk_5_and_1_4[8] = {54, 62, 54, 30, 38, 46, 38, 30};
unsigned char G_animation_vampire_walking_right[4] = {10, 8, 9, 8};
unsigned char G_animation_vampire_walking_up[4] = {18, 16, 17, 16};
unsigned char G_animation_vampire_walking_left[4] = {26, 24, 25, 24};
unsigned char G_animation_vampire_walking_down[4] = {2, 0, 1, 0};
unsigned char G_animation_vampire_pushing_right[2] = {12, 11};
unsigned char G_animation_vampire_pushing_up[2] = {20, 19};
unsigned char G_animation_vampire_pushing_left[2] = {28, 27};
unsigned char G_animation_vampire_pushing_down[2] = {4, 3};
unsigned char G_animation_bat_right[4] = {15, 13, 14, 13};
unsigned char G_animation_bat_up[4] = {23, 21, 22, 21};
unsigned char G_animation_bat_left[4] = {31, 29, 30, 29};
unsigned char G_animation_bat_down[4] = {7, 5, 6, 5};
unsigned char G_animation_fire_spell[6] = {31, 30, 29, 28, 27, 26};
unsigned char G_animation_ice_spell_right[4] = {35, 34, 33, 32};
unsigned char G_animation_ice_spell_left[4] = {39, 38, 37, 36};
unsigned char G_animation_neutral_spell[6] = {49, 50, 51, 50, 49, 48};
unsigned char G_animation_warp_spell[4] = {43, 42, 41, 40};
unsigned char G_animation_laser_shot[4] = {55, 54, 53, 54};
unsigned char G_animation_explosion[6] = {63, 62, 61, 60, 59, 58};

/*******************************************************************************
** animation_setup()
*******************************************************************************/
short int animation_setup(entity* e)
{
  if (e == NULL)
    return 1;

  /* portcullis */
  if (e->type == ENTITY_TYPE_PORTCULLIS_OPEN)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_array = G_animation_portcullis_open;
    e->frame_length = 12;
    e->animation_length = 3;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  /* environment */
  else if (e->type == ENTITY_TYPE_WATER)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
    e->animation_array = G_animation_water;
    e->frame_length = 8;
    e->animation_length = 8;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  /* symbols */
  else if (e->type == ENTITY_TYPE_YIN_YANG)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_array = G_animation_yin_yang;
    e->frame_length = 8;
    e->animation_length = 8;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  /* pushable objects */
  else if (e->type == ENTITY_TYPE_AQUA_FORTIS)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
    e->animation_array = G_animation_aqua_fortis;
    e->frame_length = 12;
    e->animation_length = 4;
    e->frame_count = 11 - (((e->pos_x + e->pos_y) / 16) % 36);
  }
  else if (e->type == ENTITY_TYPE_AQUA_EXPLODIS)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
    e->animation_array = G_animation_aqua_explodis;
    e->frame_length = 12;
    e->animation_length = 4;
    e->frame_count = 11 - (((e->pos_x + e->pos_y) / 16) % 36);
  }
  else if (e->type == ENTITY_TYPE_CANDLE_LIT)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
    e->animation_array = G_animation_candle_lit;
    e->frame_length = 12;
    e->animation_length = 3;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  else if (e->type == ENTITY_TYPE_EIGHT_BALL)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ONLY_WHEN_MOVING;

    if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
      e->animation_array = G_animation_eight_ball_right;
    else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
      e->animation_array = G_animation_eight_ball_up;
    else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
      e->animation_array = G_animation_eight_ball_left;
    else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
      e->animation_array = G_animation_eight_ball_down;

    e->frame_length = 4;
    e->animation_length = 4;

    if (e->frame_count < 4)
      e->frame_count = 15;
    else if (e->frame_count < 12)
      e->frame_count = 7;
    else
      e->frame_count = 15;
  }
  else if (e->type == ENTITY_TYPE_MAHJONG_TILE_EAST)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_COOLDOWN)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_array = G_animation_mahjong_tile_east;
      e->frame_length = 12;
      e->animation_length = 2;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = NULL;
      e->tile = 24;
    }
  }
  else if (e->type == ENTITY_TYPE_MAHJONG_TILE_NORTH)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_COOLDOWN)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_array = G_animation_mahjong_tile_north;
      e->frame_length = 12;
      e->animation_length = 2;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = NULL;
      e->tile = 26;
    }
  }
  else if (e->type == ENTITY_TYPE_MAHJONG_TILE_WEST)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_COOLDOWN)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_array = G_animation_mahjong_tile_west;
      e->frame_length = 12;
      e->animation_length = 2;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = NULL;
      e->tile = 32;
    }
  }
  else if (e->type == ENTITY_TYPE_MAHJONG_TILE_SOUTH)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_COOLDOWN)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_array = G_animation_mahjong_tile_south;
      e->frame_length = 12;
      e->animation_length = 2;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = NULL;
      e->tile = 34;
    }
  }
  else if (ENTITY_TYPE_IS_ICE_CUBE(e->type))
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_array = G_animation_ice_cube;
    e->frame_length = 120;
    e->animation_length = 3;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  /* submerged */
  else if (e->type == ENTITY_TYPE_MAHJONG_TILE_EAST_SUBMERGED)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_COOLDOWN)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_array = G_animation_mahjong_tile_east_submerged;
      e->frame_length = 12;
      e->animation_length = 2;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = NULL;
      e->tile = 32;
    }
  }
  else if (e->type == ENTITY_TYPE_MAHJONG_TILE_NORTH_SUBMERGED)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_COOLDOWN)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_array = G_animation_mahjong_tile_north_submerged;
      e->frame_length = 12;
      e->animation_length = 2;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = NULL;
      e->tile = 34;
    }
  }
  else if (e->type == ENTITY_TYPE_MAHJONG_TILE_WEST_SUBMERGED)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_COOLDOWN)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_array = G_animation_mahjong_tile_west_submerged;
      e->frame_length = 12;
      e->animation_length = 2;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = NULL;
      e->tile = 40;
    }
  }
  else if (e->type == ENTITY_TYPE_MAHJONG_TILE_SOUTH_SUBMERGED)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_COOLDOWN)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_array = G_animation_mahjong_tile_south_submerged;
      e->frame_length = 12;
      e->animation_length = 2;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = NULL;
      e->tile = 42;
    }
  }
  else if (e->type == ENTITY_TYPE_ICE_CUBE_SUBMERGED)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_array = G_animation_ice_cube_submerged;
    e->frame_length = 120;
    e->animation_length = 3;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  /* ballistas */
  else if (e->type == ENTITY_TYPE_BALLISTA_RED)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;

    if ((ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT)) ||
        (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))    ||
        (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))  ||
        (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN)))
    {
      e->animation_array = G_animation_ballista_red;
    }
    else
    {
      e->animation_array = G_animation_ballista_red_angled;
    }

    e->frame_length = 8;
    e->animation_length = 7;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  else if (e->type == ENTITY_TYPE_BALLISTA_GREEN)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;

    if ((ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT)) ||
        (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))    ||
        (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))  ||
        (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN)))
    {
      e->animation_array = G_animation_ballista_green;
    }
    else
    {
      e->animation_array = G_animation_ballista_green_angled;
    }

    e->frame_length = 8;
    e->animation_length = 7;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  else if (e->type == ENTITY_TYPE_BALLISTA_BROWN)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;

    if ((ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT)) ||
        (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))    ||
        (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))  ||
        (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN)))
    {
      e->animation_array = G_animation_ballista_brown;
    }
    else
    {
      e->animation_array = G_animation_ballista_brown_angled;
    }

    e->frame_length = 8;
    e->animation_length = 7;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  /* conveyers */
  else if (e->type == ENTITY_TYPE_CONVEYER_WHITE)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_array = G_animation_conveyer_white;
      e->frame_length = 12;
      e->animation_length = 3;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = NULL;
      e->tile = 60;
    }
  }
  else if (e->type == ENTITY_TYPE_CONVEYER_CYAN)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_array = G_animation_conveyer_cyan;
      e->frame_length = 12;
      e->animation_length = 3;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = NULL;
      e->tile = 52;
    }
  }
  else if (e->type == ENTITY_TYPE_CONVEYER_MAGENTA)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_array = G_animation_conveyer_magenta;
      e->frame_length = 12;
      e->animation_length = 3;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = NULL;
      e->tile = 56;
    }
  }
  /* floor spikes */
  else if (e->type == ENTITY_TYPE_FLOOR_SPIKE_DOWN_WHITE)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_array = G_animation_floor_spike_down_white;
    e->frame_length = 8;
    e->animation_length = 3;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  else if (e->type == ENTITY_TYPE_FLOOR_SPIKE_DOWN_CYAN)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_array = G_animation_floor_spike_down_cyan;
    e->frame_length = 8;
    e->animation_length = 3;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  else if (e->type == ENTITY_TYPE_FLOOR_SPIKE_DOWN_MAGENTA)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_array = G_animation_floor_spike_down_magenta;
    e->frame_length = 8;
    e->animation_length = 3;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  else if (e->type == ENTITY_TYPE_FLOOR_SPIKE_UP_WHITE)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_array = G_animation_floor_spike_up_white;
    e->frame_length = 8;
    e->animation_length = 3;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  else if (e->type == ENTITY_TYPE_FLOOR_SPIKE_UP_CYAN)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_array = G_animation_floor_spike_up_cyan;
    e->frame_length = 8;
    e->animation_length = 3;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  else if (e->type == ENTITY_TYPE_FLOOR_SPIKE_UP_MAGENTA)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_array = G_animation_floor_spike_up_magenta;
    e->frame_length = 8;
    e->animation_length = 3;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  /* levers */
  else if (e->type == ENTITY_TYPE_LEVER_WHITE)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;

    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
      e->animation_array = G_animation_lever_white_on;
    else
      e->animation_array = G_animation_lever_white_off;

    e->frame_length = 12;
    e->animation_length = 2;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  else if (e->type == ENTITY_TYPE_LEVER_CYAN)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;

    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
      e->animation_array = G_animation_lever_cyan_on;
    else
      e->animation_array = G_animation_lever_cyan_off;

    e->frame_length = 12;
    e->animation_length = 2;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  else if (e->type == ENTITY_TYPE_LEVER_MAGENTA)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;

    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
      e->animation_array = G_animation_lever_magenta_on;
    else
      e->animation_array = G_animation_lever_magenta_off;

    e->frame_length = 12;
    e->animation_length = 2;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  /* switches */
  else if (e->type == ENTITY_TYPE_SPIN_SWITCH_RED_CCW)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = G_animation_spin_switch_red_ccw;

      e->frame_length = 6;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = NULL;
      e->tile = 24;
    }
  }
  else if (e->type == ENTITY_TYPE_SPIN_SWITCH_RED_CW)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = G_animation_spin_switch_red_cw;

      e->frame_length = 6;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = NULL;
      e->tile = 3;
    }
  }
  else if (e->type == ENTITY_TYPE_SPIN_SWITCH_GREEN_CCW)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = G_animation_spin_switch_green_ccw;

      e->frame_length = 6;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = NULL;
      e->tile = 25;
    }
  }
  else if (e->type == ENTITY_TYPE_SPIN_SWITCH_GREEN_CW)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = G_animation_spin_switch_green_cw;

      e->frame_length = 6;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = NULL;
      e->tile = 11;
    }
  }
  else if (e->type == ENTITY_TYPE_SPIN_SWITCH_BROWN_CCW)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = G_animation_spin_switch_brown_ccw;

      e->frame_length = 6;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = NULL;
      e->tile = 26;
    }
  }
  else if (e->type == ENTITY_TYPE_SPIN_SWITCH_BROWN_CW)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = G_animation_spin_switch_brown_cw;

      e->frame_length = 6;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = NULL;
      e->tile = 19;
    }
  }
  else if (e->type == ENTITY_TYPE_NUMBER_SWITCH_EVEN)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_array = G_animation_number_switch_even;

      e->frame_length = 8;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = NULL;
      e->tile = 27;
    }
  }
  else if (e->type == ENTITY_TYPE_NUMBER_SWITCH_ODD)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_array = G_animation_number_switch_odd;

      e->frame_length = 8;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = NULL;
      e->tile = 35;
    }
  }
  else if (e->type == ENTITY_TYPE_NUMBER_SWITCH_PRIME)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_array = G_animation_number_switch_prime;

      e->frame_length = 8;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = NULL;
      e->tile = 43;
    }
  }
  else if (e->type == ENTITY_TYPE_NUMBER_SWITCH_COMPOSITE)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_array = G_animation_number_switch_composite;

      e->frame_length = 8;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = NULL;
      e->tile = 51;
    }
  }
  else if (e->type == ENTITY_TYPE_NUMBER_SWITCH_SQUARE)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_array = G_animation_number_switch_square;

      e->frame_length = 8;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = NULL;
      e->tile = 59;
    }
  }
  else if (e->type == ENTITY_TYPE_NUMBER_SWITCH_TRIANGULAR)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_array = G_animation_number_switch_triangular;

      e->frame_length = 8;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
      e->animation_array = NULL;
      e->tile = 31;
    }
  }
  /* enemies */
  else if (e->type == ENTITY_TYPE_PUMPKIN)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_array = G_animation_pumpkin_lit;
      e->frame_length = 12;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
      e->tile = 32;
    }
  }
  else if (e->type == ENTITY_TYPE_GHOST)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;

      if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
        e->animation_array = G_animation_ghost_awake_right;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
        e->animation_array = G_animation_ghost_awake_up;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
        e->animation_array = G_animation_ghost_awake_left;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
        e->animation_array = G_animation_ghost_awake_down;

      e->frame_length = 12;
      e->animation_length = 4;
      e->frame_count = 11 - (((e->pos_x + e->pos_y) / 16) % 36);
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;

      if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
        e->tile = 60;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
        e->tile = 52;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
        e->tile = 56;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
        e->tile = 48;
    }
  }
  else if (e->type == ENTITY_TYPE_MASK_HORIZONTAL)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_array = G_animation_mask_horizontal_frown;
      e->frame_length = 12;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_array = G_animation_mask_horizontal_smile;
      e->frame_length = 12;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
  }
  else if (e->type == ENTITY_TYPE_MASK_VERTICAL)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_array = G_animation_mask_vertical_frown;
      e->frame_length = 12;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_array = G_animation_mask_vertical_smile;
      e->frame_length = 12;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
  }
  else if (e->type == ENTITY_TYPE_SNAKE)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_COOLDOWN)
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;

      if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
        e->tile = 47;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
        e->tile = 39;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
        e->tile = 43;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
        e->tile = 35;
    }
    else if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;

      if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
        e->animation_array = G_animation_snake_awake_right;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
        e->animation_array = G_animation_snake_awake_up;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
        e->animation_array = G_animation_snake_awake_left;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
        e->animation_array = G_animation_snake_awake_down;

      e->frame_length = 16;
      e->animation_length = 2;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;

      if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
        e->tile = 44;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
        e->tile = 36;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
        e->tile = 40;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
        e->tile = 32;
    }
  }
  else if (e->type == ENTITY_TYPE_FAERIE_HORIZONTAL)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;

    if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
      e->animation_array = G_animation_faerie_up;
    else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
      e->animation_array = G_animation_faerie_down;

    e->frame_length = 16;
    e->animation_length = 2;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  else if (e->type == ENTITY_TYPE_FAERIE_VERTICAL)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;

    if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
      e->animation_array = G_animation_faerie_right;
    else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
      e->animation_array = G_animation_faerie_left;

    e->frame_length = 16;
    e->animation_length = 2;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  else if (e->type == ENTITY_TYPE_VENUSIAN)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
    e->animation_array = G_animation_venusian;
    e->frame_length = 16;
    e->animation_length = 6;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  else if (e->type == ENTITY_TYPE_VENUSIAN_ROOT)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
    e->animation_array = G_animation_venusian_root;
    e->frame_length = 16;
    e->animation_length = 4;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  else if (e->type == ENTITY_TYPE_WITCH)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_COOLDOWN)
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;

      if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
        e->tile = 39;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
        e->tile = 31;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
        e->tile = 35;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
        e->tile = 27;
    }
    else if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;

      if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
        e->animation_array = G_animation_witch_awake_right;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
        e->animation_array = G_animation_witch_awake_up;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
        e->animation_array = G_animation_witch_awake_left;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
        e->animation_array = G_animation_witch_awake_down;

      e->frame_length = 16;
      e->animation_length = 2;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;

      if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
        e->tile = 36;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
        e->tile = 28;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
        e->tile = 32;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
        e->tile = 24;
    }
  }
  else if (e->type == ENTITY_TYPE_UNDINE)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_COOLDOWN)
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;

      if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
        e->tile = 16;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
        e->tile = 17;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
        e->tile = 18;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
        e->tile = 19;
    }
    else
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;

      if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
        e->animation_array = G_animation_undine_right;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
        e->animation_array = G_animation_undine_up;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
        e->animation_array = G_animation_undine_left;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
        e->animation_array = G_animation_undine_down;

      e->frame_length = 16;
      e->animation_length = 2;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
  }
  else if (e->type == ENTITY_TYPE_SORCERESS)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_COOLDOWN)
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;

      if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
        e->tile = 20;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
        e->tile = 21;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
        e->tile = 22;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
        e->tile = 23;
    }
    else
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;

      if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
        e->animation_array = G_animation_sorceress_right;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
        e->animation_array = G_animation_sorceress_up;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
        e->animation_array = G_animation_sorceress_left;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
        e->animation_array = G_animation_sorceress_down;

      e->frame_length = 16;
      e->animation_length = 2;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
  }
  else if (e->type == ENTITY_TYPE_IMP_LT)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ONLY_WHEN_MOVING;

      if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
        e->animation_array = G_animation_imp_lt_right;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
        e->animation_array = G_animation_imp_lt_up;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
        e->animation_array = G_animation_imp_lt_left;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
        e->animation_array = G_animation_imp_lt_down;

      e->frame_length = 8;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
      e->tile = e->animation_array[e->animation_length - 1];
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;

      if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
        e->tile = 3;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
        e->tile = 11;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
        e->tile = 19;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
        e->tile = 27;
    }
  }
  else if (e->type == ENTITY_TYPE_IMP_RT)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ONLY_WHEN_MOVING;

      if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
        e->animation_array = G_animation_imp_rt_right;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
        e->animation_array = G_animation_imp_rt_up;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
        e->animation_array = G_animation_imp_rt_left;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
        e->animation_array = G_animation_imp_rt_down;

      e->frame_length = 8;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
      e->tile = e->animation_array[e->animation_length - 1];
    }
    else
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;

      if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
        e->tile = 7;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
        e->tile = 15;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
        e->tile = 23;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
        e->tile = 31;
    }
  }
  else if (e->type == ENTITY_TYPE_LIL_BOT)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ONLY_WHEN_MOVING;

    if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
      e->animation_array = G_animation_lil_bot_right;
    else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
      e->animation_array = G_animation_lil_bot_up;
    else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
      e->animation_array = G_animation_lil_bot_left;
    else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
      e->animation_array = G_animation_lil_bot_down;

    e->frame_length = 12;
    e->animation_length = 4;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  else if (e->type == ENTITY_TYPE_POLTERGEIST)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;

    if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
      e->animation_array = G_animation_poltergeist_right;
    else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
      e->animation_array = G_animation_poltergeist_up;
    else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
      e->animation_array = G_animation_poltergeist_left;
    else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
      e->animation_array = G_animation_poltergeist_down;

    e->frame_length = 12;
    e->animation_length = 6;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  else if (e->type == ENTITY_TYPE_WISP_LEFT_WALL)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;

    if (e->update_flags & ENTITY_UPDATE_FLAG_COOLDOWN)
      e->animation_array = G_animation_wisp_left_wall_angry;
    else
      e->animation_array = G_animation_wisp_left_wall;

    e->frame_length = 8;
    e->animation_length = 4;

    if (e->frame_count < 8)
      e->frame_count = 31;
    else if (e->frame_count < 16)
      e->frame_count = 7;
    else if (e->frame_count < 24)
      e->frame_count = 15;
    else if (e->frame_count < 32)
      e->frame_count = 23;
    else
      e->frame_count = 31;
  }
  else if (e->type == ENTITY_TYPE_WISP_RIGHT_WALL)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;

    if (e->update_flags & ENTITY_UPDATE_FLAG_COOLDOWN)
      e->animation_array = G_animation_wisp_right_wall_angry;
    else
      e->animation_array = G_animation_wisp_right_wall;

    e->frame_length = 8;
    e->animation_length = 4;

    if (e->frame_count < 8)
      e->frame_count = 31;
    else if (e->frame_count < 16)
      e->frame_count = 7;
    else if (e->frame_count < 24)
      e->frame_count = 15;
    else if (e->frame_count < 32)
      e->frame_count = 23;
    else
      e->frame_count = 31;
  }
  else if (e->type == ENTITY_TYPE_JIANGSHI_LT)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ONLY_WHEN_MOVING;
      e->animation_array = G_animation_jiangshi_lt_stopped;
      e->frame_length = 12;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ONLY_WHEN_MOVING;

      if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
        e->animation_array = G_animation_jiangshi_lt_right;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
        e->animation_array = G_animation_jiangshi_lt_up;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
        e->animation_array = G_animation_jiangshi_lt_left;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
        e->animation_array = G_animation_jiangshi_lt_down;

      e->frame_length = 8;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
  }
  else if (e->type == ENTITY_TYPE_JIANGSHI_RT)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ONLY_WHEN_MOVING;
      e->animation_array = G_animation_jiangshi_rt_stopped;
      e->frame_length = 12;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ONLY_WHEN_MOVING;

      if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
        e->animation_array = G_animation_jiangshi_rt_right;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
        e->animation_array = G_animation_jiangshi_rt_up;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
        e->animation_array = G_animation_jiangshi_rt_left;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
        e->animation_array = G_animation_jiangshi_rt_down;

      e->frame_length = 8;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
  }
  else if (e->type == ENTITY_TYPE_MUMMY_LT)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_COOLDOWN)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ONLY_WHEN_MOVING;
      e->animation_array = G_animation_mummy_lt_disintegrating;
      e->frame_length = 8;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ONLY_WHEN_MOVING;

      if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
        e->animation_array = G_animation_mummy_lt_right;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
        e->animation_array = G_animation_mummy_lt_up;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
        e->animation_array = G_animation_mummy_lt_left;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
        e->animation_array = G_animation_mummy_lt_down;

      e->frame_length = 8;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
  }
  else if (e->type == ENTITY_TYPE_MUMMY_RT)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_COOLDOWN)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ONLY_WHEN_MOVING;
      e->animation_array = G_animation_mummy_rt_disintegrating;
      e->frame_length = 8;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
    else
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ONLY_WHEN_MOVING;

      if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
        e->animation_array = G_animation_mummy_rt_right;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
        e->animation_array = G_animation_mummy_rt_up;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
        e->animation_array = G_animation_mummy_rt_left;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
        e->animation_array = G_animation_mummy_rt_down;

      e->frame_length = 8;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
    }
  }
  else if (e->type == ENTITY_TYPE_GUARDIAN_LT)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ONLY_WHEN_MOVING;

    if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
      e->animation_array = G_animation_guardian_lt_right;
    else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
      e->animation_array = G_animation_guardian_lt_up;
    else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
      e->animation_array = G_animation_guardian_lt_left;
    else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
      e->animation_array = G_animation_guardian_lt_down;

    e->frame_length = 12;
    e->animation_length = 4;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  else if (e->type == ENTITY_TYPE_GUARDIAN_RT)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ONLY_WHEN_MOVING;

    if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
      e->animation_array = G_animation_guardian_rt_right;
    else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
      e->animation_array = G_animation_guardian_rt_up;
    else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
      e->animation_array = G_animation_guardian_rt_left;
    else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
      e->animation_array = G_animation_guardian_rt_down;

    e->frame_length = 12;
    e->animation_length = 4;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  else if (e->type == ENTITY_TYPE_LASER_GUN)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;

    if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT) ||
        ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
    {
      e->animation_array = G_animation_laser_gun_right;
    }
    else if ( ENTITY_FACING_CHECK(e, ENTITY_FACING_UP_RIGHT)  ||
              ENTITY_FACING_CHECK(e, ENTITY_FACING_UP_LEFT))
    {
      e->animation_array = G_animation_laser_gun_up_right;
    }
    else if ( ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT)  ||
              ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
    {
      e->animation_array = G_animation_laser_gun_left;
    }
    else
    {
      e->animation_array = G_animation_laser_gun_down_left;
    }

    e->frame_length = 8;
    e->animation_length = 4;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  /* pickups */
  else if (e->type == ENTITY_TYPE_BLOOD_VIAL)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
    e->animation_array = G_animation_blood_vial;
    e->frame_length = 8;
    e->animation_length = 8;
    e->frame_count = 7 - (((e->pos_x + e->pos_y) / 16) % 24);
  }
  else if (e->type == ENTITY_TYPE_BAT_VIAL)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
    e->animation_array = G_animation_bat_vial;
    e->frame_length = 8;
    e->animation_length = 8;
    e->frame_count = 7 - (((e->pos_x + e->pos_y) / 16) % 24);
  }
  else if (e->type == ENTITY_TYPE_BLUE_MANA)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
    e->animation_array = G_animation_blue_mana;
    e->frame_length = 8;
    e->animation_length = 8;
    e->frame_count = 7 - (((e->pos_x + e->pos_y) / 16) % 24);
  }
  else if (e->type == ENTITY_TYPE_GREEN_MANA)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
    e->animation_array = G_animation_green_mana;
    e->frame_length = 8;
    e->animation_length = 8;
    e->frame_count = 7 - (((e->pos_x + e->pos_y) / 16) % 24);
  }
  else if (e->type == ENTITY_TYPE_FLOPPY_DISK_3_AND_1_2)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
    e->animation_array = G_animation_floppy_disk_3_and_1_2;
    e->frame_length = 8;
    e->animation_length = 8;
    e->frame_count = 7 - (((e->pos_x + e->pos_y) / 16) % 24);
  }
  else if (e->type == ENTITY_TYPE_FLOPPY_DISK_5_AND_1_4)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
    e->animation_array = G_animation_floppy_disk_5_and_1_4;
    e->frame_length = 8;
    e->animation_length = 8;
    e->frame_count = 7 - (((e->pos_x + e->pos_y) / 16) % 24);
  }
  /* player */
  else if ( (e->type == ENTITY_TYPE_PLAYER_VAMPIRE)         ||
            (e->type == ENTITY_TYPE_DOUBLE_VAMPIRE)         ||
            (e->type == ENTITY_TYPE_REVERSE_DOUBLE_VAMPIRE))
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_COOLDOWN)
    {
      e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;

      if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
        e->tile = 12;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
        e->tile = 20;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
        e->tile = 28;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
        e->tile = 4;
    }
    else if (e->action_flags & ENTITY_ACTION_FLAG_PUSHING)
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ONLY_WHEN_MOVING;

      if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
        e->animation_array = G_animation_vampire_pushing_right;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
        e->animation_array = G_animation_vampire_pushing_up;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
        e->animation_array = G_animation_vampire_pushing_left;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
        e->animation_array = G_animation_vampire_pushing_down;

      e->frame_length = 8;
      e->animation_length = 2;
      e->frame_count = e->frame_length * e->animation_length - 1;
      e->tile = e->animation_array[e->animation_length - 1];
    }
    else
    {
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
      e->animation_flags |= ENTITY_ANIMATION_FLAG_ONLY_WHEN_MOVING;

      if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
        e->animation_array = G_animation_vampire_walking_right;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
        e->animation_array = G_animation_vampire_walking_up;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
        e->animation_array = G_animation_vampire_walking_left;
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
        e->animation_array = G_animation_vampire_walking_down;

      e->frame_length = 8;
      e->animation_length = 4;
      e->frame_count = e->frame_length * e->animation_length - 1;
      e->tile = e->animation_array[e->animation_length - 1];
    }
  }
  else if ( (e->type == ENTITY_TYPE_PLAYER_BAT)         ||
            (e->type == ENTITY_TYPE_DOUBLE_BAT)         ||
            (e->type == ENTITY_TYPE_REVERSE_DOUBLE_BAT))
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;

    if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
      e->animation_array = G_animation_bat_right;
    else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
      e->animation_array = G_animation_bat_up;
    else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
      e->animation_array = G_animation_bat_left;
    else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
      e->animation_array = G_animation_bat_down;

    e->frame_length = 8;
    e->animation_length = 4;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  /* spells */
  else if (e->type == ENTITY_TYPE_FIRE_SPELL)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
    e->animation_array = G_animation_fire_spell;
    e->frame_length = 4;
    e->animation_length = 6;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  else if (e->type == ENTITY_TYPE_ICE_SPELL)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;

    if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
      e->animation_array = G_animation_ice_spell_right;
    else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
      e->animation_array = G_animation_ice_spell_right;
    else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
      e->animation_array = G_animation_ice_spell_left;
    else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
      e->animation_array = G_animation_ice_spell_left;

    e->frame_length = 4;
    e->animation_length = 4;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  else if (e->type == ENTITY_TYPE_NEUTRAL_SPELL)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
    e->animation_array = G_animation_neutral_spell;
    e->frame_length = 6;
    e->animation_length = 6;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  else if (e->type == ENTITY_TYPE_WARP_SPELL)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
    e->animation_array = G_animation_warp_spell;
    e->frame_length = 6;
    e->animation_length = 4;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  else if (e->type == ENTITY_TYPE_LASER_SHOT)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_flags |= ENTITY_ANIMATION_FLAG_LOOPING;
    e->animation_array = G_animation_laser_shot;
    e->frame_length = 6;
    e->animation_length = 4;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  else if (e->type == ENTITY_TYPE_EXPLOSION)
  {
    e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
    e->animation_array = G_animation_explosion;
    e->frame_length = 8;
    e->animation_length = 6;
    e->frame_count = e->frame_length * e->animation_length - 1;
  }
  else
  {
    e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
    e->animation_array = NULL;
  }

  return 0;
}

