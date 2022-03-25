/*******************************************************************************
** level.c (level)
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "animate.h"
#include "collide.h"
#include "entity.h"
#include "global.h"
#include "level.h"
#include "world.h"

#define LEVEL_LOAD_TILE(type, m, n)                                            \
  world_spawn_entity(type, 32 * m + 16, 32 * n + 16);                          \

#define LEVEL_LOAD_PLAYER(m, n)                                                \
  G_player =                                                                   \
    world_spawn_entity(ENTITY_TYPE_PLAYER_VAMPIRE, 32 * m + 16, 32 * n + 16);  \
  entity_set_facing(G_player, ENTITY_FACING_DOWN);                             \
  animation_setup(G_player);

#define LEVEL_LOAD_TILE_FACING_RIGHT(type, m, n)                               \
  e = world_spawn_entity(type, 32 * m + 16, 32 * n + 16);                      \
  entity_set_facing(e, ENTITY_FACING_RIGHT);                                   \
  animation_setup(e);

#define LEVEL_LOAD_TILE_FACING_UP_RIGHT(type, m, n)                            \
  e = world_spawn_entity(type, 32 * m + 16, 32 * n + 16);                      \
  entity_set_facing(e, ENTITY_FACING_UP_RIGHT);                                \
  animation_setup(e);

#define LEVEL_LOAD_TILE_FACING_UP(type, m, n)                                  \
  e = world_spawn_entity(type, 32 * m + 16, 32 * n + 16);                      \
  entity_set_facing(e, ENTITY_FACING_UP);                                      \
  animation_setup(e);

#define LEVEL_LOAD_TILE_FACING_UP_LEFT(type, m, n)                             \
  e = world_spawn_entity(type, 32 * m + 16, 32 * n + 16);                      \
  entity_set_facing(e, ENTITY_FACING_UP_LEFT);                                 \
  animation_setup(e);

#define LEVEL_LOAD_TILE_FACING_LEFT(type, m, n)                                \
  e = world_spawn_entity(type, 32 * m + 16, 32 * n + 16);                      \
  entity_set_facing(e, ENTITY_FACING_LEFT);                                    \
  animation_setup(e);

#define LEVEL_LOAD_TILE_FACING_DOWN_LEFT(type, m, n)                           \
  e = world_spawn_entity(type, 32 * m + 16, 32 * n + 16);                      \
  entity_set_facing(e, ENTITY_FACING_DOWN_LEFT);                               \
  animation_setup(e);

#define LEVEL_LOAD_TILE_FACING_DOWN(type, m, n)                                \
  e = world_spawn_entity(type, 32 * m + 16, 32 * n + 16);                      \
  entity_set_facing(e, ENTITY_FACING_DOWN);                                    \
  animation_setup(e);

#define LEVEL_LOAD_TILE_FACING_DOWN_RIGHT(type, m, n)                          \
  e = world_spawn_entity(type, 32 * m + 16, 32 * n + 16);                      \
  entity_set_facing(e, ENTITY_FACING_DOWN_RIGHT);                              \
  animation_setup(e);

#define LEVEL_LOAD_TILE_MOVING_RIGHT(type, m, n)                               \
  e = world_spawn_entity(type, 32 * m + 16, 32 * n + 16);                      \
  entity_set_facing(e, ENTITY_FACING_RIGHT);                                   \
  animation_setup(e);                                                          \
  e->orientation &= ~ENTITY_DIRECTION_MASK;                                    \
  e->orientation |= ENTITY_DIRECTION_RIGHT;

#define LEVEL_LOAD_TILE_MOVING_UP(type, m, n)                                  \
  e = world_spawn_entity(type, 32 * m + 16, 32 * n + 16);                      \
  entity_set_facing(e, ENTITY_FACING_UP);                                      \
  animation_setup(e);                                                          \
  e->orientation &= ~ENTITY_DIRECTION_MASK;                                    \
  e->orientation |= ENTITY_DIRECTION_UP;

#define LEVEL_LOAD_TILE_MOVING_LEFT(type, m, n)                                \
  e = world_spawn_entity(type, 32 * m + 16, 32 * n + 16);                      \
  entity_set_facing(e, ENTITY_FACING_LEFT);                                    \
  animation_setup(e);                                                          \
  e->orientation &= ~ENTITY_DIRECTION_MASK;                                    \
  e->orientation |= ENTITY_DIRECTION_LEFT;

#define LEVEL_LOAD_TILE_MOVING_DOWN(type, m, n)                                \
  e = world_spawn_entity(type, 32 * m + 16, 32 * n + 16);                      \
  entity_set_facing(e, ENTITY_FACING_DOWN);                                    \
  animation_setup(e);                                                          \
  e->orientation &= ~ENTITY_DIRECTION_MASK;                                    \
  e->orientation |= ENTITY_DIRECTION_DOWN;

#define LEVEL_LOAD_ACTIVE_CONVEYER_FACING_RIGHT(type, m, n)                    \
  e = world_spawn_entity(type, 32 * m + 16, 32 * n + 16);                      \
  e->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;                                \
  entity_set_facing(e, ENTITY_FACING_RIGHT);                                   \
  animation_setup(e);

#define LEVEL_LOAD_ACTIVE_CONVEYER_FACING_UP(type, m, n)                       \
  e = world_spawn_entity(type, 32 * m + 16, 32 * n + 16);                      \
  e->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;                                \
  entity_set_facing(e, ENTITY_FACING_UP);                                      \
  animation_setup(e);

#define LEVEL_LOAD_ACTIVE_CONVEYER_FACING_LEFT(type, m, n)                     \
  e = world_spawn_entity(type, 32 * m + 16, 32 * n + 16);                      \
  e->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;                                \
  entity_set_facing(e, ENTITY_FACING_LEFT);                                    \
  animation_setup(e);

#define LEVEL_LOAD_ACTIVE_CONVEYER_FACING_DOWN(type, m, n)                     \
  e = world_spawn_entity(type, 32 * m + 16, 32 * n + 16);                      \
  e->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;                                \
  entity_set_facing(e, ENTITY_FACING_DOWN);                                    \
  animation_setup(e);

#define LEVEL_LOAD_BALLISTA_FACING_RIGHT(type, m, n)                           \
  e = world_spawn_entity(type, 32 * m + 16, 32 * n + 16);                      \
  entity_set_facing(e, ENTITY_FACING_RIGHT);                                   \
  animation_setup(e);                                                          \
  e->frame_count = 0;

#define LEVEL_LOAD_BALLISTA_FACING_UP(type, m, n)                              \
  e = world_spawn_entity(type, 32 * m + 16, 32 * n + 16);                      \
  entity_set_facing(e, ENTITY_FACING_UP);                                      \
  animation_setup(e);                                                          \
  e->frame_count = 0;

#define LEVEL_LOAD_BALLISTA_FACING_LEFT(type, m, n)                            \
  e = world_spawn_entity(type, 32 * m + 16, 32 * n + 16);                      \
  entity_set_facing(e, ENTITY_FACING_LEFT);                                    \
  animation_setup(e);                                                          \
  e->frame_count = 0;

#define LEVEL_LOAD_BALLISTA_FACING_DOWN(type, m, n)                            \
  e = world_spawn_entity(type, 32 * m + 16, 32 * n + 16);                      \
  entity_set_facing(e, ENTITY_FACING_DOWN);                                    \
  animation_setup(e);                                                          \
  e->frame_count = 0;

#define LEVEL_LOAD_LASER_GUN(m, n)                                             \
  e = world_spawn_entity(ENTITY_TYPE_LASER_GUN, 32 * m + 16, 32 * n + 16);     \
  entity_set_facing(e, ENTITY_FACING_RIGHT);                                   \
  animation_setup(e);                                                          \
  e->frame_count = 0;

#define LEVEL_LOAD_YIN_YANG(m, n)                                              \
  e = world_spawn_entity(ENTITY_TYPE_YIN_YANG, 32 * m + 16, 32 * n + 16);      \
  e->frame_count = 0;

#define LEVEL_LOAD_FLOOR_SPIKES(type, m, n)                                    \
  e = world_spawn_entity(type, 32 * m + 8, 32 * n + 8);                        \
  e->frame_count = 0;                                                          \
  e = world_spawn_entity(type, 32 * m + 24, 32 * n + 8);                       \
  e->frame_count = 0;                                                          \
  e = world_spawn_entity(type, 32 * m + 8, 32 * n + 24);                       \
  e->frame_count = 0;                                                          \
  e = world_spawn_entity(type, 32 * m + 24, 32 * n + 24);                      \
  e->frame_count = 0;

#define LEVEL_LOAD_LEVER_OFF(type, m, n)                                       \
  e = world_spawn_entity(type, 32 * m + 16, 32 * n + 16);                      \
  e->frame_count = 0;

#define LEVEL_LOAD_LEVER_ON(type, m, n)                                        \
  e = world_spawn_entity(type, 32 * m + 16, 32 * n + 16);                      \
  e->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;                                \
  animation_setup(e);                                                          \
  e->frame_count = 0;

#define LEVEL_LOAD_WATER(m, n)                                                 \
  world_spawn_entity(ENTITY_TYPE_WATER, 32 * m + 8, 32 * n + 8);               \
  world_spawn_entity(ENTITY_TYPE_WATER, 32 * m + 24, 32 * n + 8);              \
  world_spawn_entity(ENTITY_TYPE_WATER, 32 * m + 8, 32 * n + 24);              \
  world_spawn_entity(ENTITY_TYPE_WATER, 32 * m + 24, 32 * n + 24);

#define LEVEL_DETERMINE_ENVIRONMENT(var, index)                                \
  if ((l->tiles[index] == LEVEL_TILE_GRASS)     ||                             \
      (l->tiles[index] == LEVEL_TILE_TREE)      ||                             \
      (l->tiles[index] == LEVEL_TILE_VENUSIAN))                                \
  {                                                                            \
    var = LEVEL_ENVIRONMENT_GRASS;                                             \
  }                                                                            \
  else if ( (l->tiles[index] == LEVEL_TILE_WATER)                     ||       \
            (l->tiles[index] == LEVEL_TILE_BRIDGE_STONE_VERTICAL)     ||       \
            (l->tiles[index] == LEVEL_TILE_BRIDGE_WOOD_VERTICAL)      ||       \
            (l->tiles[index] == LEVEL_TILE_BRIDGE_CRACKED_VERTICAL)   ||       \
            (l->tiles[index] == LEVEL_TILE_BRIDGE_STONE_HORIZONTAL)   ||       \
            (l->tiles[index] == LEVEL_TILE_BRIDGE_WOOD_HORIZONTAL)    ||       \
            (l->tiles[index] == LEVEL_TILE_BRIDGE_CRACKED_HORIZONTAL))         \
  {                                                                            \
    var = LEVEL_ENVIRONMENT_WATER;                                             \
  }                                                                            \
  else if (l->tiles[index] == LEVEL_TILE_ICE)                                  \
  {                                                                            \
    var = LEVEL_ENVIRONMENT_ICE;                                               \
  }                                                                            \
  else if ( (l->tiles[index] == LEVEL_TILE_CONVEYER_OFF_RIGHT_WHITE)      ||   \
            (l->tiles[index] == LEVEL_TILE_CONVEYER_OFF_UP_WHITE)         ||   \
            (l->tiles[index] == LEVEL_TILE_CONVEYER_OFF_LEFT_WHITE)       ||   \
            (l->tiles[index] == LEVEL_TILE_CONVEYER_OFF_DOWN_WHITE)       ||   \
            (l->tiles[index] == LEVEL_TILE_CONVEYER_ON_RIGHT_WHITE)       ||   \
            (l->tiles[index] == LEVEL_TILE_CONVEYER_ON_UP_WHITE)          ||   \
            (l->tiles[index] == LEVEL_TILE_CONVEYER_ON_LEFT_WHITE)        ||   \
            (l->tiles[index] == LEVEL_TILE_CONVEYER_ON_DOWN_WHITE)        ||   \
            (l->tiles[index] == LEVEL_TILE_CONVEYER_OFF_RIGHT_CYAN)       ||   \
            (l->tiles[index] == LEVEL_TILE_CONVEYER_OFF_UP_CYAN)          ||   \
            (l->tiles[index] == LEVEL_TILE_CONVEYER_OFF_LEFT_CYAN)        ||   \
            (l->tiles[index] == LEVEL_TILE_CONVEYER_OFF_DOWN_CYAN)        ||   \
            (l->tiles[index] == LEVEL_TILE_CONVEYER_ON_RIGHT_CYAN)        ||   \
            (l->tiles[index] == LEVEL_TILE_CONVEYER_ON_UP_CYAN)           ||   \
            (l->tiles[index] == LEVEL_TILE_CONVEYER_ON_LEFT_CYAN)         ||   \
            (l->tiles[index] == LEVEL_TILE_CONVEYER_ON_DOWN_CYAN)         ||   \
            (l->tiles[index] == LEVEL_TILE_CONVEYER_OFF_RIGHT_MAGENTA)    ||   \
            (l->tiles[index] == LEVEL_TILE_CONVEYER_OFF_UP_MAGENTA)       ||   \
            (l->tiles[index] == LEVEL_TILE_CONVEYER_OFF_LEFT_MAGENTA)     ||   \
            (l->tiles[index] == LEVEL_TILE_CONVEYER_OFF_DOWN_MAGENTA)     ||   \
            (l->tiles[index] == LEVEL_TILE_CONVEYER_ON_RIGHT_MAGENTA)     ||   \
            (l->tiles[index] == LEVEL_TILE_CONVEYER_ON_UP_MAGENTA)        ||   \
            (l->tiles[index] == LEVEL_TILE_CONVEYER_ON_LEFT_MAGENTA)      ||   \
            (l->tiles[index] == LEVEL_TILE_CONVEYER_ON_DOWN_MAGENTA))          \
  {                                                                            \
    var = LEVEL_ENVIRONMENT_CONVEYER;                                          \
  }                                                                            \
  else                                                                         \
  {                                                                            \
    var = LEVEL_ENVIRONMENT_FLOOR;                                             \
  }

enum
{
  LEVEL_ENVIRONMENT_NONE,
  LEVEL_ENVIRONMENT_FLOOR,
  LEVEL_ENVIRONMENT_GRASS,
  LEVEL_ENVIRONMENT_WATER,
  LEVEL_ENVIRONMENT_ICE,
  LEVEL_ENVIRONMENT_CONVEYER
};

level G_levels_all[330];

/*******************************************************************************
** level_init()
*******************************************************************************/
short int level_init(level* l)
{
  int i;

  if (l == NULL)
    return 1;

  for (i = 0; i < LEVEL_MAX_TILES; i++)
  {
    l->tiles[i] = LEVEL_TILE_FLOOR;
    l->border[i] = 0x00;
  }

  l->portcullis_position = 0;
  l->par_time = 0;
  l->theme = THEME_FOYER;

  return 0;
}

/*******************************************************************************
** level_create()
*******************************************************************************/
level* level_create()
{
  level* l;

  l = malloc(sizeof(level));
  level_init(l);

  return l;
}

/*******************************************************************************
** level_deinit()
*******************************************************************************/
short int level_deinit(level* l)
{
  int i;

  if (l == NULL)
    return 1;

  for (i = 0; i < LEVEL_MAX_TILES; i++)
  {
    l->tiles[i] = LEVEL_TILE_FLOOR;
    l->border[i] = 0x00;
  }

  l->portcullis_position = 0;
  l->par_time = 0;
  l->theme = THEME_FOYER;

  return 0;
}

/*******************************************************************************
** level_destroy()
*******************************************************************************/
short int level_destroy(level* l)
{
  if (l == NULL)
    return 1;

  level_deinit(l);
  free(l);

  return 0;
}

/*******************************************************************************
** level_generate_border()
*******************************************************************************/
short int level_generate_border(level* l)
{
  int i;
  int m;
  int n;
  int index;
  int env;
  int surround[8];
  int surround_env[8];

  if (l == NULL)
    return 1;

  /* clear existing border information */
  for (i = 0; i < LEVEL_MAX_TILES; i++)
    l->border[i] = LEVEL_BORDER_FLAGS_CLEAR;

  /* generate border */
  for (m = 0; m < LEVEL_WIDTH; m++)
  {
    for (n = 0; n < LEVEL_HEIGHT; n++)
    {
      index = m * LEVEL_HEIGHT + n;

      /* determine environment of this tile */
      LEVEL_DETERMINE_ENVIRONMENT(env, index)

      /* if this is a normal floor tile, skip it */
      if (env == LEVEL_ENVIRONMENT_FLOOR)
        continue;

      /* find indices of surrounding tiles */
      if ((m > 0) && (n > 0))
        surround[0] = (m - 1) * LEVEL_HEIGHT + (n - 1);
      else
        surround[0] = -1;

      if (n > 0)
        surround[1] = m * LEVEL_HEIGHT + (n - 1);
      else
        surround[1] = -1;

      if ((m < LEVEL_WIDTH - 1) && (n > 0))
        surround[2] = (m + 1) * LEVEL_HEIGHT + (n - 1);
      else
        surround[2] = -1;

      if (m > 0)
        surround[3] = (m - 1) * LEVEL_HEIGHT + n;
      else
        surround[3] = -1;

      if (m < LEVEL_WIDTH - 1)
        surround[4] = (m + 1) * LEVEL_HEIGHT + n;
      else
        surround[4] = -1;

      if ((m > 0) && (n < LEVEL_HEIGHT - 1))
        surround[5] = (m - 1) * LEVEL_HEIGHT + (n + 1);
      else
        surround[5] = -1;

      if (n < LEVEL_HEIGHT - 1)
        surround[6] = m * LEVEL_HEIGHT + (n + 1);
      else
        surround[6] = -1;

      if ((m < LEVEL_WIDTH - 1) && (n < LEVEL_HEIGHT - 1))
        surround[7] = (m + 1) * LEVEL_HEIGHT + (n + 1);
      else
        surround[7] = -1;

      /* determine environments of surrounding tiles */
      for (i = 0; i < 8; i++)
      {
        if (surround[i] == -1)
        {
          surround_env[i] = LEVEL_ENVIRONMENT_NONE;
          continue;
        }

        LEVEL_DETERMINE_ENVIRONMENT(surround_env[i], surround[i])
      }

      /* generate border between different environment types */
      for (i = 0; i < 8; i++)
      {
        /* water and conveyers */
        if (( (env == LEVEL_ENVIRONMENT_WATER) && 
              (surround_env[i] != LEVEL_ENVIRONMENT_WATER)) ||
            ( (env == LEVEL_ENVIRONMENT_CONVEYER) && 
              (surround_env[i] != LEVEL_ENVIRONMENT_CONVEYER)))
        {
          if (surround[i] == -1)
            continue;

          if (i == 0)
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_BOTTOM_RIGHT;
          else if (i == 1)
          {
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_BOTTOM_LEFT;
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_BOTTOM;
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_BOTTOM_RIGHT;
          }
          else if (i == 2)
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_BOTTOM_LEFT;
          else if (i == 3)
          {
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_TOP_RIGHT;
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_RIGHT;
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_BOTTOM_RIGHT;
          }
          else if (i == 4)
          {
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_TOP_LEFT;
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_LEFT;
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_BOTTOM_LEFT;
          }
          else if (i == 5)
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_TOP_RIGHT;
          else if (i == 6)
          {
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_TOP_LEFT;
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_TOP;
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_TOP_RIGHT;
          }
          else if (i == 7)
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_TOP_LEFT;
        }
        /* grass and ice */
        else if ( ( (env == LEVEL_ENVIRONMENT_GRASS) && 
                    (surround_env[i] != LEVEL_ENVIRONMENT_GRASS)) ||
                  ( (env == LEVEL_ENVIRONMENT_ICE) && 
                    (surround_env[i] != LEVEL_ENVIRONMENT_ICE)))
        {
          /* border for this grass/ice tile */
          if (i == 0)
          {
            l->border[index] |= LEVEL_BORDER_FLAG_TOP_LEFT;
          }
          else if (i == 1)
          {
            l->border[index] |= LEVEL_BORDER_FLAG_TOP_LEFT;
            l->border[index] |= LEVEL_BORDER_FLAG_TOP;
            l->border[index] |= LEVEL_BORDER_FLAG_TOP_RIGHT;
          }
          else if (i == 2)
          {
            l->border[index] |= LEVEL_BORDER_FLAG_TOP_RIGHT;
          }
          else if (i == 3)
          {
            l->border[index] |= LEVEL_BORDER_FLAG_TOP_LEFT;
            l->border[index] |= LEVEL_BORDER_FLAG_LEFT;
            l->border[index] |= LEVEL_BORDER_FLAG_BOTTOM_LEFT;
          }
          else if (i == 4)
          {
            l->border[index] |= LEVEL_BORDER_FLAG_TOP_RIGHT;
            l->border[index] |= LEVEL_BORDER_FLAG_RIGHT;
            l->border[index] |= LEVEL_BORDER_FLAG_BOTTOM_RIGHT;
          }
          else if (i == 5)
          {
            l->border[index] |= LEVEL_BORDER_FLAG_BOTTOM_LEFT;
          }
          else if (i == 6)
          {
            l->border[index] |= LEVEL_BORDER_FLAG_BOTTOM_LEFT;
            l->border[index] |= LEVEL_BORDER_FLAG_BOTTOM;
            l->border[index] |= LEVEL_BORDER_FLAG_BOTTOM_RIGHT;
          }
          else if (i == 7)
          {
            l->border[index] |= LEVEL_BORDER_FLAG_BOTTOM_RIGHT;
          }

          /* border on surrounding tile, if applicable */
          if (surround[i] == -1)
            continue;

          if (i == 0)
          {
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_BOTTOM_RIGHT;
          }
          else if (i == 1)
          {
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_BOTTOM_LEFT;
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_BOTTOM;
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_BOTTOM_RIGHT;
          }
          else if (i == 2)
          {
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_BOTTOM_LEFT;
          }
          else if (i == 3)
          {
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_TOP_RIGHT;
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_RIGHT;
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_BOTTOM_RIGHT;
          }
          else if (i == 4)
          {
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_TOP_LEFT;
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_LEFT;
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_BOTTOM_LEFT;
          }
          else if (i == 5)
          {
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_TOP_RIGHT;
          }
          else if (i == 6)
          {
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_TOP_LEFT;
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_TOP;
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_TOP_RIGHT;
          }
          else if (i == 7)
          {
            l->border[surround[i]] |= LEVEL_BORDER_FLAG_TOP_LEFT;
          }
        }
      }
    }
  }

  return 0;
}

/*******************************************************************************
** level_load_to_world()
*******************************************************************************/
short int level_load_to_world(level* l)
{
  int     m;
  int     n;
  int     index;
  int     env;
  entity* e;

  if (l == NULL)
    return 1;

  /* reset the world */
  world_reset();

  /* set theme */
  G_theme = l->theme;

  /* load par time */
  G_par_time_ms = l->par_time * 1000;

  /* load walls */
  LEVEL_LOAD_TILE(ENTITY_TYPE_OUTER_WALL_TOP_LEFT, 0, 0)
  LEVEL_LOAD_TILE(ENTITY_TYPE_OUTER_WALL_TOP_RIGHT, 12, 0)

  LEVEL_LOAD_TILE(ENTITY_TYPE_OUTER_WALL_BOTTOM_LEFT, 0, 13)
  LEVEL_LOAD_TILE(ENTITY_TYPE_OUTER_WALL_BOTTOM_RIGHT, 12, 13)

  for (m = 1; m < 12; m++)
  {
    LEVEL_LOAD_TILE(ENTITY_TYPE_OUTER_WALL_TOP, m, 0)
    LEVEL_LOAD_TILE(ENTITY_TYPE_OUTER_WALL_BOTTOM, m, 13)
  }

  for (n = 1; n < 13; n++)
  {
    LEVEL_LOAD_TILE(ENTITY_TYPE_OUTER_WALL_LEFT, 0, n)
    LEVEL_LOAD_TILE(ENTITY_TYPE_OUTER_WALL_RIGHT, 12, n)
  }

  for (m = 0; m < 13; m++)
  {
    LEVEL_LOAD_TILE(ENTITY_TYPE_INNER_WALL_BOTTOM, m, 14)
  }

  /* load top inner wall and portcullis */
  if ((l->portcullis_position < 0) || (l->portcullis_position > 10))
    l->portcullis_position = 0;

  for (m = 1; m < 12; m++)
  {
    if (m == l->portcullis_position + 1)
    {
      LEVEL_LOAD_TILE(ENTITY_TYPE_PORTCULLIS_CLOSED, m, 1)
    }
    else
    {
      LEVEL_LOAD_TILE(ENTITY_TYPE_INNER_WALL_TOP, m, 1)
    }
  }

  /* load level tiles */
  for (m = 1; m < LEVEL_WIDTH + 1; m++)
  {
    for (n = 2; n < LEVEL_HEIGHT + 2; n++)
    {
      index = ((m - 1) * LEVEL_HEIGHT) + (n - 2);

      /* 0x0x - environment, symbols, obstacles, vertical bridge */
      if (l->tiles[index] == LEVEL_TILE_FLOOR)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_GRASS)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_GRASS, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_WATER)
      {
        LEVEL_LOAD_WATER(m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_ICE)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_ICE, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_COBWEB)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_COBWEB, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_JOKER_CARD)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_JOKER_CARD, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_SEAL_OF_SOLOMON)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_SEAL_OF_SOLOMON, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_YIN_YANG)
      {
        LEVEL_LOAD_YIN_YANG(m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BLOCK)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_BLOCK, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_PILLAR)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_PILLAR, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_TREE)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_TREE, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_GRASS, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BRIDGE_STONE_VERTICAL)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_BRIDGE_STONE_VERTICAL, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BRIDGE_WOOD_VERTICAL)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_BRIDGE_WOOD_VERTICAL, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BRIDGE_CRACKED_VERTICAL)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_BRIDGE_CRACKED_VERTICAL, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      /* 0x1x - boxes, pots, flasks, candles, prism blocks */
      else if (l->tiles[index] == LEVEL_TILE_BOX_WOOD)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_BOX_WOOD, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BOX_METAL)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_BOX_METAL, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BOX_TNT)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_BOX_TNT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BOX_STONE)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_BOX_STONE, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_POT_CLAY)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_POT_CLAY, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_POT_METAL)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_POT_METAL, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_POT_TNT)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_POT_TNT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_POT_STONE)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_POT_STONE, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_AQUA_FORTIS)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_AQUA_FORTIS, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_AQUA_EXPLODIS)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_AQUA_EXPLODIS, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_CANDLE_UNLIT)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_CANDLE_UNLIT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_CANDLE_LIT)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_CANDLE_LIT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_PRISM_BLOCK_0)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_PRISM_BLOCK_0, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_PRISM_BLOCK_45)
      {
        LEVEL_LOAD_TILE_FACING_UP_RIGHT(ENTITY_TYPE_PRISM_BLOCK_45, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_PRISM_BLOCK_90)
      {
        LEVEL_LOAD_TILE_FACING_UP(ENTITY_TYPE_PRISM_BLOCK_90, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_PRISM_BLOCK_135)
      {
        LEVEL_LOAD_TILE_FACING_UP_LEFT(ENTITY_TYPE_PRISM_BLOCK_135, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      /* 0x2x - eight balls, dice, mahjong tiles, horizontal bridges */
      else if (l->tiles[index] == LEVEL_TILE_EIGHT_BALL)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_EIGHT_BALL, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_VANISHING_DIE_1)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_DIE_VANISHED_1, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_VANISHING_DIE_2)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_DIE_VANISHED_2, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_VANISHING_DIE_3)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_DIE_VANISHED_3, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_VANISHING_DIE_4)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_DIE_VANISHED_4, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_VANISHING_DIE_5)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_DIE_VANISHED_5, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_VANISHING_DIE_6)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_DIE_VANISHED_6, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_MAHJONG_EAST)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_MAHJONG_TILE_EAST, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_MAHJONG_NORTH)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_MAHJONG_TILE_NORTH, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_MAHJONG_WEST)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_MAHJONG_TILE_WEST, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_MAHJONG_SOUTH)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_MAHJONG_TILE_SOUTH, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_SPELLBINDER)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_SPELLBINDER_EMPTY, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BRIDGE_STONE_HORIZONTAL)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_BRIDGE_STONE_HORIZONTAL, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BRIDGE_WOOD_HORIZONTAL)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_BRIDGE_WOOD_HORIZONTAL, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BRIDGE_CRACKED_HORIZONTAL)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_BRIDGE_CRACKED_HORIZONTAL, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      /* 0x3x - arrows, red bar kickers */
      else if (l->tiles[index] == LEVEL_TILE_ARROWS_RED_RIGHT)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_ARROWS_RED, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_ARROWS_RED_UP)
      {
        LEVEL_LOAD_TILE_FACING_UP(ENTITY_TYPE_ARROWS_RED, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_ARROWS_RED_LEFT)
      {
        LEVEL_LOAD_TILE_FACING_LEFT(ENTITY_TYPE_ARROWS_RED, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_ARROWS_RED_DOWN)
      {
        LEVEL_LOAD_TILE_FACING_DOWN(ENTITY_TYPE_ARROWS_RED, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_ARROWS_GREEN_RIGHT)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_ARROWS_GREEN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_ARROWS_GREEN_UP)
      {
        LEVEL_LOAD_TILE_FACING_UP(ENTITY_TYPE_ARROWS_GREEN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_ARROWS_GREEN_LEFT)
      {
        LEVEL_LOAD_TILE_FACING_LEFT(ENTITY_TYPE_ARROWS_GREEN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_ARROWS_GREEN_DOWN)
      {
        LEVEL_LOAD_TILE_FACING_DOWN(ENTITY_TYPE_ARROWS_GREEN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_ARROWS_BROWN_RIGHT)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_ARROWS_BROWN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_ARROWS_BROWN_UP)
      {
        LEVEL_LOAD_TILE_FACING_UP(ENTITY_TYPE_ARROWS_BROWN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_ARROWS_BROWN_LEFT)
      {
        LEVEL_LOAD_TILE_FACING_LEFT(ENTITY_TYPE_ARROWS_BROWN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_ARROWS_BROWN_DOWN)
      {
        LEVEL_LOAD_TILE_FACING_DOWN(ENTITY_TYPE_ARROWS_BROWN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BAR_KICKER_RED_0)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_BAR_KICKER_RED, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BAR_KICKER_RED_45)
      {
        LEVEL_LOAD_TILE_FACING_UP_RIGHT(ENTITY_TYPE_BAR_KICKER_RED, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BAR_KICKER_RED_90)
      {
        LEVEL_LOAD_TILE_FACING_UP(ENTITY_TYPE_BAR_KICKER_RED, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BAR_KICKER_RED_135)
      {
        LEVEL_LOAD_TILE_FACING_UP_LEFT(ENTITY_TYPE_BAR_KICKER_RED, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      /* 0x4x - rest of bar kickers, red & green triangle kickers */
      else if (l->tiles[index] == LEVEL_TILE_BAR_KICKER_GREEN_0)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_BAR_KICKER_GREEN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BAR_KICKER_GREEN_45)
      {
        LEVEL_LOAD_TILE_FACING_UP_RIGHT(ENTITY_TYPE_BAR_KICKER_GREEN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BAR_KICKER_GREEN_90)
      {
        LEVEL_LOAD_TILE_FACING_UP(ENTITY_TYPE_BAR_KICKER_GREEN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BAR_KICKER_GREEN_135)
      {
        LEVEL_LOAD_TILE_FACING_UP_LEFT(ENTITY_TYPE_BAR_KICKER_GREEN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BAR_KICKER_BROWN_0)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_BAR_KICKER_BROWN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BAR_KICKER_BROWN_45)
      {
        LEVEL_LOAD_TILE_FACING_UP_RIGHT(ENTITY_TYPE_BAR_KICKER_BROWN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BAR_KICKER_BROWN_90)
      {
        LEVEL_LOAD_TILE_FACING_UP(ENTITY_TYPE_BAR_KICKER_BROWN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BAR_KICKER_BROWN_135)
      {
        LEVEL_LOAD_TILE_FACING_UP_LEFT(ENTITY_TYPE_BAR_KICKER_BROWN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_TRIANGLE_KICKER_RED_45)
      {
        LEVEL_LOAD_TILE_FACING_UP_RIGHT(ENTITY_TYPE_TRIANGLE_KICKER_RED, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_TRIANGLE_KICKER_RED_135)
      {
        LEVEL_LOAD_TILE_FACING_UP_LEFT(ENTITY_TYPE_TRIANGLE_KICKER_RED, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_TRIANGLE_KICKER_RED_225)
      {
        LEVEL_LOAD_TILE_FACING_DOWN_LEFT(ENTITY_TYPE_TRIANGLE_KICKER_RED, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_TRIANGLE_KICKER_RED_315)
      {
        LEVEL_LOAD_TILE_FACING_DOWN_RIGHT(ENTITY_TYPE_TRIANGLE_KICKER_RED, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_TRIANGLE_KICKER_GREEN_45)
      {
        LEVEL_LOAD_TILE_FACING_UP_RIGHT(ENTITY_TYPE_TRIANGLE_KICKER_GREEN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_TRIANGLE_KICKER_GREEN_135)
      {
        LEVEL_LOAD_TILE_FACING_UP_LEFT(ENTITY_TYPE_TRIANGLE_KICKER_GREEN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_TRIANGLE_KICKER_GREEN_225)
      {
        LEVEL_LOAD_TILE_FACING_DOWN_LEFT(ENTITY_TYPE_TRIANGLE_KICKER_GREEN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_TRIANGLE_KICKER_GREEN_315)
      {
        LEVEL_LOAD_TILE_FACING_DOWN_RIGHT(ENTITY_TYPE_TRIANGLE_KICKER_GREEN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      /* 0x5x - ballistas, first of conveyers */
      else if (l->tiles[index] == LEVEL_TILE_BALLISTA_RED_RIGHT)
      {
        LEVEL_LOAD_BALLISTA_FACING_RIGHT(ENTITY_TYPE_BALLISTA_RED, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BALLISTA_RED_UP)
      {
        LEVEL_LOAD_BALLISTA_FACING_UP(ENTITY_TYPE_BALLISTA_RED, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BALLISTA_RED_LEFT)
      {
        LEVEL_LOAD_BALLISTA_FACING_LEFT(ENTITY_TYPE_BALLISTA_RED, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BALLISTA_RED_DOWN)
      {
        LEVEL_LOAD_BALLISTA_FACING_DOWN(ENTITY_TYPE_BALLISTA_RED, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BALLISTA_GREEN_RIGHT)
      {
        LEVEL_LOAD_BALLISTA_FACING_RIGHT(ENTITY_TYPE_BALLISTA_GREEN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BALLISTA_GREEN_UP)
      {
        LEVEL_LOAD_BALLISTA_FACING_UP(ENTITY_TYPE_BALLISTA_GREEN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BALLISTA_GREEN_LEFT)
      {
        LEVEL_LOAD_BALLISTA_FACING_LEFT(ENTITY_TYPE_BALLISTA_GREEN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BALLISTA_GREEN_DOWN)
      {
        LEVEL_LOAD_BALLISTA_FACING_DOWN(ENTITY_TYPE_BALLISTA_GREEN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BALLISTA_BROWN_RIGHT)
      {
        LEVEL_LOAD_BALLISTA_FACING_RIGHT(ENTITY_TYPE_BALLISTA_BROWN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BALLISTA_BROWN_UP)
      {
        LEVEL_LOAD_BALLISTA_FACING_UP(ENTITY_TYPE_BALLISTA_BROWN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BALLISTA_BROWN_LEFT)
      {
        LEVEL_LOAD_BALLISTA_FACING_LEFT(ENTITY_TYPE_BALLISTA_BROWN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BALLISTA_BROWN_DOWN)
      {
        LEVEL_LOAD_BALLISTA_FACING_DOWN(ENTITY_TYPE_BALLISTA_BROWN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_CONVEYER_OFF_RIGHT_WHITE)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_CONVEYER_WHITE, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_CONVEYER_OFF_UP_WHITE)
      {
        LEVEL_LOAD_TILE_FACING_UP(ENTITY_TYPE_CONVEYER_WHITE, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_CONVEYER_OFF_LEFT_WHITE)
      {
        LEVEL_LOAD_TILE_FACING_LEFT(ENTITY_TYPE_CONVEYER_WHITE, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_CONVEYER_OFF_DOWN_WHITE)
      {
        LEVEL_LOAD_TILE_FACING_DOWN(ENTITY_TYPE_CONVEYER_WHITE, m, n)
      }
      /* 0x6x - conveyers */
      else if (l->tiles[index] == LEVEL_TILE_CONVEYER_ON_RIGHT_WHITE)
      {
        LEVEL_LOAD_ACTIVE_CONVEYER_FACING_RIGHT(ENTITY_TYPE_CONVEYER_WHITE, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_CONVEYER_ON_UP_WHITE)
      {
        LEVEL_LOAD_ACTIVE_CONVEYER_FACING_UP(ENTITY_TYPE_CONVEYER_WHITE, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_CONVEYER_ON_LEFT_WHITE)
      {
        LEVEL_LOAD_ACTIVE_CONVEYER_FACING_LEFT(ENTITY_TYPE_CONVEYER_WHITE, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_CONVEYER_ON_DOWN_WHITE)
      {
        LEVEL_LOAD_ACTIVE_CONVEYER_FACING_DOWN(ENTITY_TYPE_CONVEYER_WHITE, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_CONVEYER_OFF_RIGHT_CYAN)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_CONVEYER_CYAN, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_CONVEYER_OFF_UP_CYAN)
      {
        LEVEL_LOAD_TILE_FACING_UP(ENTITY_TYPE_CONVEYER_CYAN, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_CONVEYER_OFF_LEFT_CYAN)
      {
        LEVEL_LOAD_TILE_FACING_LEFT(ENTITY_TYPE_CONVEYER_CYAN, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_CONVEYER_OFF_DOWN_CYAN)
      {
        LEVEL_LOAD_TILE_FACING_DOWN(ENTITY_TYPE_CONVEYER_CYAN, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_CONVEYER_ON_RIGHT_CYAN)
      {
        LEVEL_LOAD_ACTIVE_CONVEYER_FACING_RIGHT(ENTITY_TYPE_CONVEYER_CYAN, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_CONVEYER_ON_UP_CYAN)
      {
        LEVEL_LOAD_ACTIVE_CONVEYER_FACING_UP(ENTITY_TYPE_CONVEYER_CYAN, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_CONVEYER_ON_LEFT_CYAN)
      {
        LEVEL_LOAD_ACTIVE_CONVEYER_FACING_LEFT(ENTITY_TYPE_CONVEYER_CYAN, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_CONVEYER_ON_DOWN_CYAN)
      {
        LEVEL_LOAD_ACTIVE_CONVEYER_FACING_DOWN(ENTITY_TYPE_CONVEYER_CYAN, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_CONVEYER_OFF_RIGHT_MAGENTA)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_CONVEYER_MAGENTA, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_CONVEYER_OFF_UP_MAGENTA)
      {
        LEVEL_LOAD_TILE_FACING_UP(ENTITY_TYPE_CONVEYER_MAGENTA, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_CONVEYER_OFF_LEFT_MAGENTA)
      {
        LEVEL_LOAD_TILE_FACING_LEFT(ENTITY_TYPE_CONVEYER_MAGENTA, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_CONVEYER_OFF_DOWN_MAGENTA)
      {
        LEVEL_LOAD_TILE_FACING_DOWN(ENTITY_TYPE_CONVEYER_MAGENTA, m, n)
      }
      /* 0x7x - last of conveyers, floor spikes, levers */
      else if (l->tiles[index] == LEVEL_TILE_CONVEYER_ON_RIGHT_MAGENTA)
      {
        LEVEL_LOAD_ACTIVE_CONVEYER_FACING_RIGHT(ENTITY_TYPE_CONVEYER_MAGENTA, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_CONVEYER_ON_UP_MAGENTA)
      {
        LEVEL_LOAD_ACTIVE_CONVEYER_FACING_UP(ENTITY_TYPE_CONVEYER_MAGENTA, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_CONVEYER_ON_LEFT_MAGENTA)
      {
        LEVEL_LOAD_ACTIVE_CONVEYER_FACING_LEFT(ENTITY_TYPE_CONVEYER_MAGENTA, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_CONVEYER_ON_DOWN_MAGENTA)
      {
        LEVEL_LOAD_ACTIVE_CONVEYER_FACING_DOWN(ENTITY_TYPE_CONVEYER_MAGENTA, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_FLOOR_SPIKES_DOWN_WHITE)
      {
        LEVEL_LOAD_FLOOR_SPIKES(ENTITY_TYPE_FLOOR_SPIKE_DOWN_WHITE, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_FLOOR_SPIKES_DOWN_CYAN)
      {
        LEVEL_LOAD_FLOOR_SPIKES(ENTITY_TYPE_FLOOR_SPIKE_DOWN_CYAN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_FLOOR_SPIKES_DOWN_MAGENTA)
      {
        LEVEL_LOAD_FLOOR_SPIKES(ENTITY_TYPE_FLOOR_SPIKE_DOWN_MAGENTA, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_FLOOR_SPIKES_UP_WHITE)
      {
        LEVEL_LOAD_FLOOR_SPIKES(ENTITY_TYPE_FLOOR_SPIKE_UP_WHITE, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_FLOOR_SPIKES_UP_CYAN)
      {
        LEVEL_LOAD_FLOOR_SPIKES(ENTITY_TYPE_FLOOR_SPIKE_UP_CYAN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_FLOOR_SPIKES_UP_MAGENTA)
      {
        LEVEL_LOAD_FLOOR_SPIKES(ENTITY_TYPE_FLOOR_SPIKE_UP_MAGENTA, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_LEVER_LEFT_WHITE)
      {
        LEVEL_LOAD_LEVER_OFF(ENTITY_TYPE_LEVER_WHITE, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_LEVER_LEFT_CYAN)
      {
        LEVEL_LOAD_LEVER_OFF(ENTITY_TYPE_LEVER_CYAN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_LEVER_LEFT_MAGENTA)
      {
        LEVEL_LOAD_LEVER_OFF(ENTITY_TYPE_LEVER_MAGENTA, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_LEVER_RIGHT_WHITE)
      {
        LEVEL_LOAD_LEVER_ON(ENTITY_TYPE_LEVER_WHITE, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_LEVER_RIGHT_CYAN)
      {
        LEVEL_LOAD_LEVER_ON(ENTITY_TYPE_LEVER_CYAN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_LEVER_RIGHT_MAGENTA)
      {
        LEVEL_LOAD_LEVER_ON(ENTITY_TYPE_LEVER_MAGENTA, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      /* 0x8x - spin switches, number switches, brown triangle kickers */
      else if (l->tiles[index] == LEVEL_TILE_SPIN_SWITCH_RED_CCW)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_SPIN_SWITCH_RED_CCW, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_SPIN_SWITCH_RED_CW)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_SPIN_SWITCH_RED_CW, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_SPIN_SWITCH_GREEN_CCW)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_SPIN_SWITCH_GREEN_CCW, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_SPIN_SWITCH_GREEN_CW)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_SPIN_SWITCH_GREEN_CW, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_SPIN_SWITCH_BROWN_CCW)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_SPIN_SWITCH_BROWN_CCW, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_SPIN_SWITCH_BROWN_CW)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_SPIN_SWITCH_BROWN_CW, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_NUMBER_SWITCH_EVEN)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_NUMBER_SWITCH_EVEN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_NUMBER_SWITCH_ODD)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_NUMBER_SWITCH_ODD, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_NUMBER_SWITCH_PRIME)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_NUMBER_SWITCH_PRIME, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_NUMBER_SWITCH_COMPOSITE)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_NUMBER_SWITCH_COMPOSITE, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_NUMBER_SWITCH_SQUARE)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_NUMBER_SWITCH_SQUARE, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_NUMBER_SWITCH_TRIANGULAR)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_NUMBER_SWITCH_TRIANGULAR, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_TRIANGLE_KICKER_BROWN_45)
      {
        LEVEL_LOAD_TILE_FACING_UP_RIGHT(ENTITY_TYPE_TRIANGLE_KICKER_BROWN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_TRIANGLE_KICKER_BROWN_135)
      {
        LEVEL_LOAD_TILE_FACING_UP_LEFT(ENTITY_TYPE_TRIANGLE_KICKER_BROWN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_TRIANGLE_KICKER_BROWN_225)
      {
        LEVEL_LOAD_TILE_FACING_DOWN_LEFT(ENTITY_TYPE_TRIANGLE_KICKER_BROWN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_TRIANGLE_KICKER_BROWN_315)
      {
        LEVEL_LOAD_TILE_FACING_DOWN_RIGHT(ENTITY_TYPE_TRIANGLE_KICKER_BROWN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      /* 0x9x - enemies */
      else if (l->tiles[index] == LEVEL_TILE_PUMPKIN)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_PUMPKIN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_GHOST_RIGHT)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_GHOST, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_GHOST_UP)
      {
        LEVEL_LOAD_TILE_FACING_UP(ENTITY_TYPE_GHOST, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_GHOST_LEFT)
      {
        LEVEL_LOAD_TILE_FACING_LEFT(ENTITY_TYPE_GHOST, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_GHOST_DOWN)
      {
        LEVEL_LOAD_TILE_FACING_DOWN(ENTITY_TYPE_GHOST, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_MASK_HORIZONTAL)
      {
        LEVEL_LOAD_TILE_MOVING_RIGHT(ENTITY_TYPE_MASK_HORIZONTAL, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_MASK_VERTICAL)
      {
        LEVEL_LOAD_TILE_MOVING_DOWN(ENTITY_TYPE_MASK_VERTICAL, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_SNAKE_RIGHT)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_SNAKE, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_SNAKE_UP)
      {
        LEVEL_LOAD_TILE_FACING_UP(ENTITY_TYPE_SNAKE, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_SNAKE_LEFT)
      {
        LEVEL_LOAD_TILE_FACING_LEFT(ENTITY_TYPE_SNAKE, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_SNAKE_DOWN)
      {
        LEVEL_LOAD_TILE_FACING_DOWN(ENTITY_TYPE_SNAKE, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_DOUBLE)
      {
        LEVEL_LOAD_TILE_FACING_DOWN(ENTITY_TYPE_DOUBLE_VAMPIRE, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_REVERSE_DOUBLE)
      {
        LEVEL_LOAD_TILE_FACING_UP(ENTITY_TYPE_REVERSE_DOUBLE_VAMPIRE, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_FAERIE_HORIZONTAL)
      {
        LEVEL_LOAD_TILE_FACING_DOWN(ENTITY_TYPE_FAERIE_HORIZONTAL, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_FAERIE_VERTICAL)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_FAERIE_VERTICAL, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_VENUSIAN)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_VENUSIAN, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_VENUSIAN_ROOT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_GRASS, m, n)
      }
      /* 0xAx - more enemies */
      else if (l->tiles[index] == LEVEL_TILE_WITCH_RIGHT)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_WITCH, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_WITCH_UP)
      {
        LEVEL_LOAD_TILE_FACING_UP(ENTITY_TYPE_WITCH, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_WITCH_LEFT)
      {
        LEVEL_LOAD_TILE_FACING_LEFT(ENTITY_TYPE_WITCH, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_WITCH_DOWN)
      {
        LEVEL_LOAD_TILE_FACING_DOWN(ENTITY_TYPE_WITCH, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_UNDINE_RIGHT)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_UNDINE, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_UNDINE_UP)
      {
        LEVEL_LOAD_TILE_FACING_UP(ENTITY_TYPE_UNDINE, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_UNDINE_LEFT)
      {
        LEVEL_LOAD_TILE_FACING_LEFT(ENTITY_TYPE_UNDINE, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_UNDINE_DOWN)
      {
        LEVEL_LOAD_TILE_FACING_DOWN(ENTITY_TYPE_UNDINE, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_SORCERESS_RIGHT)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_SORCERESS, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_SORCERESS_UP)
      {
        LEVEL_LOAD_TILE_FACING_UP(ENTITY_TYPE_SORCERESS, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_SORCERESS_LEFT)
      {
        LEVEL_LOAD_TILE_FACING_LEFT(ENTITY_TYPE_SORCERESS, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_SORCERESS_DOWN)
      {
        LEVEL_LOAD_TILE_FACING_DOWN(ENTITY_TYPE_SORCERESS, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_FROG_RIGHT)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_FROG, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_FROG_UP)
      {
        LEVEL_LOAD_TILE_FACING_UP(ENTITY_TYPE_FROG, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_FROG_LEFT)
      {
        LEVEL_LOAD_TILE_FACING_LEFT(ENTITY_TYPE_FROG, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_FROG_DOWN)
      {
        LEVEL_LOAD_TILE_FACING_DOWN(ENTITY_TYPE_FROG, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      /* 0xBx - mas enemies */
      else if (l->tiles[index] == LEVEL_TILE_IMP_LEFT_TURN_0)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_IMP_LT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_IMP_LEFT_TURN_90)
      {
        LEVEL_LOAD_TILE_FACING_UP(ENTITY_TYPE_IMP_LT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_IMP_LEFT_TURN_180)
      {
        LEVEL_LOAD_TILE_FACING_LEFT(ENTITY_TYPE_IMP_LT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_IMP_LEFT_TURN_270)
      {
        LEVEL_LOAD_TILE_FACING_DOWN(ENTITY_TYPE_IMP_LT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_IMP_RIGHT_TURN_0)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_IMP_RT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_IMP_RIGHT_TURN_90)
      {
        LEVEL_LOAD_TILE_FACING_UP(ENTITY_TYPE_IMP_RT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_IMP_RIGHT_TURN_180)
      {
        LEVEL_LOAD_TILE_FACING_LEFT(ENTITY_TYPE_IMP_RT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_IMP_RIGHT_TURN_270)
      {
        LEVEL_LOAD_TILE_FACING_DOWN(ENTITY_TYPE_IMP_RT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_LIL_BOT_HORIZONTAL)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_LIL_BOT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_LIL_BOT_VERTICAL)
      {
        LEVEL_LOAD_TILE_FACING_DOWN(ENTITY_TYPE_LIL_BOT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_POLTERGEIST_HORIZONTAL)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_POLTERGEIST, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_POLTERGEIST_VERTICAL)
      {
        LEVEL_LOAD_TILE_FACING_DOWN(ENTITY_TYPE_POLTERGEIST, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_WISP_LEFT_WALL_0)
      {
        LEVEL_LOAD_TILE_MOVING_RIGHT(ENTITY_TYPE_WISP_LEFT_WALL, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_WISP_LEFT_WALL_90)
      {
        LEVEL_LOAD_TILE_MOVING_UP(ENTITY_TYPE_WISP_LEFT_WALL, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_WISP_LEFT_WALL_180)
      {
        LEVEL_LOAD_TILE_MOVING_LEFT(ENTITY_TYPE_WISP_LEFT_WALL, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_WISP_LEFT_WALL_270)
      {
        LEVEL_LOAD_TILE_MOVING_DOWN(ENTITY_TYPE_WISP_LEFT_WALL, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      /* 0xCx - even mas enemies */
      else if (l->tiles[index] == LEVEL_TILE_WISP_RIGHT_WALL_0)
      {
        LEVEL_LOAD_TILE_MOVING_RIGHT(ENTITY_TYPE_WISP_RIGHT_WALL, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_WISP_RIGHT_WALL_90)
      {
        LEVEL_LOAD_TILE_MOVING_UP(ENTITY_TYPE_WISP_RIGHT_WALL, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_WISP_RIGHT_WALL_180)
      {
        LEVEL_LOAD_TILE_MOVING_LEFT(ENTITY_TYPE_WISP_RIGHT_WALL, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_WISP_RIGHT_WALL_270)
      {
        LEVEL_LOAD_TILE_MOVING_DOWN(ENTITY_TYPE_WISP_RIGHT_WALL, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_JIANGSHI_LEFT_TURN_0)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_JIANGSHI_LT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_JIANGSHI_LEFT_TURN_90)
      {
        LEVEL_LOAD_TILE_FACING_UP(ENTITY_TYPE_JIANGSHI_LT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_JIANGSHI_LEFT_TURN_180)
      {
        LEVEL_LOAD_TILE_FACING_LEFT(ENTITY_TYPE_JIANGSHI_LT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_JIANGSHI_LEFT_TURN_270)
      {
        LEVEL_LOAD_TILE_FACING_DOWN(ENTITY_TYPE_JIANGSHI_LT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_JIANGSHI_RIGHT_TURN_0)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_JIANGSHI_RT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_JIANGSHI_RIGHT_TURN_90)
      {
        LEVEL_LOAD_TILE_FACING_UP(ENTITY_TYPE_JIANGSHI_RT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_JIANGSHI_RIGHT_TURN_180)
      {
        LEVEL_LOAD_TILE_FACING_LEFT(ENTITY_TYPE_JIANGSHI_RT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_JIANGSHI_RIGHT_TURN_270)
      {
        LEVEL_LOAD_TILE_FACING_DOWN(ENTITY_TYPE_JIANGSHI_RT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_MUMMY_LEFT_TURN_0)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_MUMMY_LT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_MUMMY_LEFT_TURN_90)
      {
        LEVEL_LOAD_TILE_FACING_UP(ENTITY_TYPE_MUMMY_LT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_MUMMY_LEFT_TURN_180)
      {
        LEVEL_LOAD_TILE_FACING_LEFT(ENTITY_TYPE_MUMMY_LT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_MUMMY_LEFT_TURN_270)
      {
        LEVEL_LOAD_TILE_FACING_DOWN(ENTITY_TYPE_MUMMY_LT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      /* 0xDx - enemies fin */
      else if (l->tiles[index] == LEVEL_TILE_MUMMY_RIGHT_TURN_0)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_MUMMY_RT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_MUMMY_RIGHT_TURN_90)
      {
        LEVEL_LOAD_TILE_FACING_UP(ENTITY_TYPE_MUMMY_RT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_MUMMY_RIGHT_TURN_180)
      {
        LEVEL_LOAD_TILE_FACING_LEFT(ENTITY_TYPE_MUMMY_RT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_MUMMY_RIGHT_TURN_270)
      {
        LEVEL_LOAD_TILE_FACING_DOWN(ENTITY_TYPE_MUMMY_RT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_GUARDIAN_LEFT_TURN_0)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_GUARDIAN_LT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_GUARDIAN_LEFT_TURN_90)
      {
        LEVEL_LOAD_TILE_FACING_UP(ENTITY_TYPE_GUARDIAN_LT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_GUARDIAN_LEFT_TURN_180)
      {
        LEVEL_LOAD_TILE_FACING_LEFT(ENTITY_TYPE_GUARDIAN_LT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_GUARDIAN_LEFT_TURN_270)
      {
        LEVEL_LOAD_TILE_FACING_DOWN(ENTITY_TYPE_GUARDIAN_LT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_GUARDIAN_RIGHT_TURN_0)
      {
        LEVEL_LOAD_TILE_FACING_RIGHT(ENTITY_TYPE_GUARDIAN_RT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_GUARDIAN_RIGHT_TURN_90)
      {
        LEVEL_LOAD_TILE_FACING_UP(ENTITY_TYPE_GUARDIAN_RT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_GUARDIAN_RIGHT_TURN_180)
      {
        LEVEL_LOAD_TILE_FACING_LEFT(ENTITY_TYPE_GUARDIAN_RT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_GUARDIAN_RIGHT_TURN_270)
      {
        LEVEL_LOAD_TILE_FACING_DOWN(ENTITY_TYPE_GUARDIAN_RT, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_LASER_GUN)
      {
        LEVEL_LOAD_LASER_GUN(m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      /* 0xFx - pickups and player start */
      else if (l->tiles[index] == LEVEL_TILE_BLOOD_VIAL)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_BLOOD_VIAL, m, n)
        G_vials_remaining += 1;
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BAT_VIAL)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_BAT_VIAL, m, n)
        G_vials_remaining += 1;
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_BLUE_MANA)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_BLUE_MANA, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_GREEN_MANA)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_GREEN_MANA, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_FLOPPY_DISK_3_AND_1_2)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOPPY_DISK_3_AND_1_2, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_FLOPPY_DISK_5_AND_1_4)
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOPPY_DISK_5_AND_1_4, m, n)
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
      else if (l->tiles[index] == LEVEL_TILE_PLAYER_START)
      {
        if (G_player == NULL)
        {
          LEVEL_LOAD_PLAYER(m, n)
          LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
        }
        else
        {
          LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
        }
      }
      else
      {
        LEVEL_LOAD_TILE(ENTITY_TYPE_FLOOR, m, n)
      }
    }
  }

  /* load border tiles */
  for (m = 1; m < LEVEL_WIDTH + 1; m++)
  {
    for (n = 2; n < LEVEL_HEIGHT + 2; n++)
    {
      index = ((m - 1) * LEVEL_HEIGHT) + (n - 2);

      /* determine environment of this tile */
      LEVEL_DETERMINE_ENVIRONMENT(env, index)

      /* top left */
      if (l->border[index] & LEVEL_BORDER_FLAG_TOP_LEFT)
      {
        if (env == LEVEL_ENVIRONMENT_FLOOR)
        {
          world_spawn_entity( ENTITY_TYPE_FLOOR_BORDER_TOP_LEFT, 
                              32 * m + 4, 32 * n + 4);
        }
        else if (env == LEVEL_ENVIRONMENT_GRASS)
        {
          world_spawn_entity( ENTITY_TYPE_GRASS_BORDER_TOP_LEFT, 
                              32 * m + 2, 32 * n + 2);
        }
        else if (env == LEVEL_ENVIRONMENT_ICE)
        {
          world_spawn_entity( ENTITY_TYPE_ICE_BORDER_TOP_LEFT, 
                              32 * m + 2, 32 * n + 2);
        }
      }

      /* top */
      if (l->border[index] & LEVEL_BORDER_FLAG_TOP)
      {
        if (env == LEVEL_ENVIRONMENT_FLOOR)
        {
          world_spawn_entity( ENTITY_TYPE_FLOOR_BORDER_TOP, 
                              32 * m + 16, 32 * n + 4);
        }
        else if (env == LEVEL_ENVIRONMENT_GRASS)
        {
          world_spawn_entity( ENTITY_TYPE_GRASS_BORDER_TOP, 
                              32 * m + 16, 32 * n + 2);
        }
        else if (env == LEVEL_ENVIRONMENT_ICE)
        {
          world_spawn_entity( ENTITY_TYPE_ICE_BORDER_TOP, 
                              32 * m + 16, 32 * n + 2);
        }
      }

      /* top right */
      if (l->border[index] & LEVEL_BORDER_FLAG_TOP_RIGHT)
      {
        if (env == LEVEL_ENVIRONMENT_FLOOR)
        {
          world_spawn_entity( ENTITY_TYPE_FLOOR_BORDER_TOP_RIGHT, 
                              32 * m + 28, 32 * n + 4);
        }
        else if (env == LEVEL_ENVIRONMENT_GRASS)
        {
          world_spawn_entity( ENTITY_TYPE_GRASS_BORDER_TOP_RIGHT, 
                              32 * m + 30, 32 * n + 2);
        }
        else if (env == LEVEL_ENVIRONMENT_ICE)
        {
          world_spawn_entity( ENTITY_TYPE_ICE_BORDER_TOP_RIGHT, 
                              32 * m + 30, 32 * n + 2);
        }
      }

      /* left */
      if (l->border[index] & LEVEL_BORDER_FLAG_LEFT)
      {
        if (env == LEVEL_ENVIRONMENT_FLOOR)
        {
          world_spawn_entity( ENTITY_TYPE_FLOOR_BORDER_LEFT, 
                              32 * m + 4, 32 * n + 16);
        }
        else if (env == LEVEL_ENVIRONMENT_GRASS)
        {
          world_spawn_entity( ENTITY_TYPE_GRASS_BORDER_LEFT, 
                              32 * m + 2, 32 * n + 16);
        }
        else if (env == LEVEL_ENVIRONMENT_ICE)
        {
          world_spawn_entity( ENTITY_TYPE_ICE_BORDER_LEFT, 
                              32 * m + 2, 32 * n + 16);
        }
      }

      /* right */
      if (l->border[index] & LEVEL_BORDER_FLAG_RIGHT)
      {
        if (env == LEVEL_ENVIRONMENT_FLOOR)
        {
          world_spawn_entity( ENTITY_TYPE_FLOOR_BORDER_RIGHT, 
                              32 * m + 28, 32 * n + 16);
        }
        else if (env == LEVEL_ENVIRONMENT_GRASS)
        {
          world_spawn_entity( ENTITY_TYPE_GRASS_BORDER_RIGHT, 
                              32 * m + 30, 32 * n + 16);
        }
        else if (env == LEVEL_ENVIRONMENT_ICE)
        {
          world_spawn_entity( ENTITY_TYPE_ICE_BORDER_RIGHT, 
                              32 * m + 30, 32 * n + 16);
        }
      }

      /* bottom left */
      if (l->border[index] & LEVEL_BORDER_FLAG_BOTTOM_LEFT)
      {
        if (env == LEVEL_ENVIRONMENT_FLOOR)
        {
          world_spawn_entity( ENTITY_TYPE_FLOOR_BORDER_BOTTOM_LEFT, 
                              32 * m + 4, 32 * n + 28);
        }
        else if (env == LEVEL_ENVIRONMENT_GRASS)
        {
          world_spawn_entity( ENTITY_TYPE_GRASS_BORDER_BOTTOM_LEFT, 
                              32 * m + 2, 32 * n + 30);
        }
        else if (env == LEVEL_ENVIRONMENT_ICE)
        {
          world_spawn_entity( ENTITY_TYPE_ICE_BORDER_BOTTOM_LEFT, 
                              32 * m + 2, 32 * n + 30);
        }
      }

      /* bottom */
      if (l->border[index] & LEVEL_BORDER_FLAG_BOTTOM)
      {
        if (env == LEVEL_ENVIRONMENT_FLOOR)
        {
          world_spawn_entity( ENTITY_TYPE_FLOOR_BORDER_BOTTOM, 
                              32 * m + 16, 32 * n + 28);
        }
        else if (env == LEVEL_ENVIRONMENT_GRASS)
        {
          world_spawn_entity( ENTITY_TYPE_GRASS_BORDER_BOTTOM, 
                              32 * m + 16, 32 * n + 30);
        }
        else if (env == LEVEL_ENVIRONMENT_ICE)
        {
          world_spawn_entity( ENTITY_TYPE_ICE_BORDER_BOTTOM, 
                              32 * m + 16, 32 * n + 30);
        }
      }

      /* bottom right */
      if (l->border[index] & LEVEL_BORDER_FLAG_BOTTOM_RIGHT)
      {
        if (env == LEVEL_ENVIRONMENT_FLOOR)
        {
          world_spawn_entity( ENTITY_TYPE_FLOOR_BORDER_BOTTOM_RIGHT, 
                              32 * m + 28, 32 * n + 28);
        }
        else if (env == LEVEL_ENVIRONMENT_GRASS)
        {
          world_spawn_entity( ENTITY_TYPE_GRASS_BORDER_BOTTOM_RIGHT, 
                              32 * m + 30, 32 * n + 30);
        }
        else if (env == LEVEL_ENVIRONMENT_ICE)
        {
          world_spawn_entity( ENTITY_TYPE_ICE_BORDER_BOTTOM_RIGHT, 
                              32 * m + 30, 32 * n + 30);
        }
      }
    }
  }

  /* initialize spatial partitioning grid */
  collide_grid_update();

  return 0;
}

/*******************************************************************************
** level_load_all_from_file()
*******************************************************************************/
short int level_load_all_from_file(char* filename)
{
  FILE*         fp;
  int           i;
  int           j;
  int           m;
  int           n;
  unsigned char nc;
  char          signature[4];
  char          type[6];
  unsigned char num_worlds;
  unsigned char theme;
  level*        l;

  if (filename == NULL)
    return 1;

  /* open file */
  fp = fopen(filename, "rb");

  /* if file did not open, return error */
  if (fp == NULL)
    return 1;

  /* read signature */
  if (fread(signature, 1, 4, fp) < 4)
  {
    fclose(fp);
    return 1;
  }

  if ((signature[0] != 'V') || (signature[1] != 'T') ||
      (signature[2] != '2') || (signature[3] != '!'))
  {
    fclose(fp);
    return 1;
  }

  /* read type */
  if (fread(type, 1, 6, fp) < 6)
  {
    fclose(fp);
    return 1;
  }

  if ((type[0] != 'W') || (type[1] != 'O') || (type[2] != 'R') ||
      (type[3] != 'L') || (type[4] != 'D') || (type[5] != 'S'))
  {
    fclose(fp);
    return 1;
  }

  /* read number of worlds */
  if (fread(&num_worlds, 1, 1, fp) == 0)
  {
    fclose(fp);
    return 1;
  }

  if (num_worlds != 22)
  {
    fclose(fp);
    return 1;
  }

  /* cycle through worlds */
  for (i = 0; i < num_worlds; i++)
  {
    /* read theme for world */
    if (fread(&theme, 1, 1, fp) == 0)
    {
      fclose(fp);
      return 1;
    }

    /* cycle through rooms */
    for (j = 0; j < 15; j++)
    {
      l = &G_levels_all[(15 * i) + j];

      level_init(l);

      /* read tiles */
      for (n = 0; n < LEVEL_HEIGHT; n++)
      {
        for (m = 0; m < LEVEL_WIDTH; m++)
        {
          if (fread(&nc, 1, 1, fp) == 0)
          {
            fclose(fp);
            return 1;
          }

          l->tiles[m * LEVEL_HEIGHT + n] = nc;
        }
      }

      /* read portcullis position */
      if (fread(&nc, 1, 1, fp) == 0)
      {
        fclose(fp);
        return 1;
      }

      l->portcullis_position = nc;

      /* read par time */
      if (fread(&nc, 1, 1, fp) == 0)
      {
        fclose(fp);
        return 1;
      }

      l->par_time = nc;

      /* set level theme */
      if (theme == 0x01)
        l->theme = THEME_FOYER;
      else if (theme == 0x02)
        l->theme = THEME_CRYPT;
      else if (theme == 0x03)
        l->theme = THEME_WATERS;
      else if (theme == 0x04)
        l->theme = THEME_PERISTYLE;
      else if (theme == 0x05)
        l->theme = THEME_LIBRARY;
      else if (theme == 0x06)
        l->theme = THEME_GARDENS;
      else if (theme == 0x07)
        l->theme = THEME_DUNGEON;
      else if (theme == 0x08)
        l->theme = THEME_SHRINE;
      else if (theme == 0x09)
        l->theme = THEME_LABYRINTH;
      else if (theme == 0x0A)
        l->theme = THEME_BALLROOM;
      else if (theme == 0x0B)
        l->theme = THEME_PENTOMINO;
      else if (theme == 0x0C)
        l->theme = THEME_ARMORY;
      else if (theme == 0x0D)
        l->theme = THEME_YGGDRASIL;
      else if (theme == 0x0E)
        l->theme = THEME_HEAVEN;
      else if (theme == 0x0F)
        l->theme = THEME_FUTURE;
      else if (theme == 0x10)
        l->theme = THEME_ALCHEMY;
      else if (theme == 0x11)
        l->theme = THEME_ARENA;
      else if (theme == 0x12)
        l->theme = THEME_APOGEE;
      else if (theme == 0x13)
        l->theme = THEME_PAGAN;
      else if (theme == 0x14)
        l->theme = THEME_TIBET;
      else if (theme == 0x15)
        l->theme = THEME_GOLDEN;
      else if (theme == 0x16)
        l->theme = THEME_DESSERTS;
      else
        l->theme = THEME_FOYER;

      /* generate border */
      level_generate_border(l);
    }
  }

  /* close file */
  fclose(fp);

  return 0;
}
