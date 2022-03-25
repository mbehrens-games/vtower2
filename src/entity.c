/*******************************************************************************
** entity.c (entity)
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "entity.h"
#include "global.h"

#define ENTITY_SET_GRASS_BORDER_TILE_OFFSET(e)                                 \
  if (G_theme == THEME_FOYER)                                                  \
    e->tile += 0;                                                              \
  else if (G_theme == THEME_CRYPT)                                             \
    e->tile += 8;                                                              \
  else if (G_theme == THEME_WATERS)                                            \
    e->tile += 0;                                                              \
  else if (G_theme == THEME_PERISTYLE)                                         \
    e->tile += 0;                                                              \
  else if (G_theme == THEME_LIBRARY)                                           \
    e->tile += 8;                                                              \
  else if (G_theme == THEME_GARDENS)                                           \
    e->tile += 0;                                                              \
  else if (G_theme == THEME_DUNGEON)                                           \
    e->tile += 16;                                                             \
  else if (G_theme == THEME_SHRINE)                                            \
    e->tile += 24;                                                             \
  else if (G_theme == THEME_LABYRINTH)                                         \
    e->tile += 8;                                                              \
  else if (G_theme == THEME_BALLROOM)                                          \
    e->tile += 16;                                                             \
  else if (G_theme == THEME_PENTOMINO)                                         \
    e->tile += 0;                                                              \
  else if (G_theme == THEME_ARMORY)                                            \
    e->tile += 8;                                                              \
  else if (G_theme == THEME_YGGDRASIL)                                         \
    e->tile += 0;                                                              \
  else if (G_theme == THEME_HEAVEN)                                            \
    e->tile += 0;                                                              \
  else if (G_theme == THEME_FUTURE)                                            \
    e->tile += 8;                                                              \
  else if (G_theme == THEME_ALCHEMY)                                           \
    e->tile += 0;                                                              \
  else if (G_theme == THEME_ARENA)                                             \
    e->tile += 8;                                                              \
  else if (G_theme == THEME_APOGEE)                                            \
    e->tile += 0;                                                              \
  else if (G_theme == THEME_PAGAN)                                             \
    e->tile += 8;                                                              \
  else if (G_theme == THEME_TIBET)                                             \
    e->tile += 24;                                                             \
  else if (G_theme == THEME_GOLDEN)                                            \
    e->tile += 8;                                                              \
  else if (G_theme == THEME_DESSERTS)                                          \
    e->tile += 24;                                                             \
  else                                                                         \
    e->tile += 0;

/*******************************************************************************
** entity_init()
*******************************************************************************/
short int entity_init(entity* e)
{
  if (e == NULL)
    return 1;

  e->next   = NULL;
  e->prev   = NULL;
  e->id     = 0;

  e->type               = ENTITY_TYPE_NONE;
  e->update_flags       = ENTITY_UPDATE_FLAGS_CLEAR;
  e->action_flags       = ENTITY_ACTION_FLAGS_CLEAR;
  e->special_flags      = ENTITY_SPECIAL_FLAGS_CLEAR;
  e->animation_flags    = ENTITY_ANIMATION_FLAGS_CLEAR;
  e->move_attribute     = ENTITY_MOVE_FLAGS_CLEAR;
  e->move_affect        = ENTITY_MOVE_FLAGS_CLEAR;
  e->trigger_attribute  = ENTITY_TRIGGER_FLAGS_CLEAR;
  e->trigger_affect     = ENTITY_TRIGGER_FLAGS_CLEAR;
  e->damage_attribute   = ENTITY_DAMAGE_FLAGS_CLEAR;
  e->damage_affect      = ENTITY_DAMAGE_FLAGS_CLEAR;
  e->collision_flags    = ENTITY_COLLISION_FLAGS_CLEAR;
  e->orientation        = 0x00;

  e->pos_x  = 0;
  e->pos_y  = 0;
  e->vel_x  = 0;
  e->vel_y  = 0;

  e->hp     = 1;

  e->move_count       = 0;
  e->cooldown_count   = 0;
  e->spin_count       = 0;
  e->frame_count      = 0;

  e->rx     = 0;
  e->ry     = 0;

  e->tile   = 0;

  e->animation_array  = NULL;
  e->frame_length     = 0;
  e->animation_length = 0;

  return 0;
}

/*******************************************************************************
** entity_create()
*******************************************************************************/
entity* entity_create()
{
  entity* e;

  e = malloc(sizeof(entity));
  entity_init(e);

  return e;
}

/*******************************************************************************
** entity_deinit()
*******************************************************************************/
short int entity_deinit(entity* e)
{
  if (e == NULL)
    return 1;

  return 0;
}

/*******************************************************************************
** entity_destroy()
*******************************************************************************/
short int entity_destroy(entity* e)
{
  if (e == NULL)
    return 1;

  entity_deinit(e);
  free(e);

  return 0;
}

/*******************************************************************************
** entity_reset()
*******************************************************************************/
short int entity_reset(entity* e)
{
  if (e == NULL)
    return 1;

  e->type               = ENTITY_TYPE_NONE;
  e->update_flags       = ENTITY_UPDATE_FLAGS_CLEAR;
  e->action_flags       = ENTITY_ACTION_FLAGS_CLEAR;
  e->special_flags      = ENTITY_SPECIAL_FLAGS_CLEAR;
  e->animation_flags    = ENTITY_ANIMATION_FLAGS_CLEAR;
  e->move_attribute     = ENTITY_MOVE_FLAGS_CLEAR;
  e->move_affect        = ENTITY_MOVE_FLAGS_CLEAR;
  e->trigger_attribute  = ENTITY_TRIGGER_FLAGS_CLEAR;
  e->trigger_affect     = ENTITY_TRIGGER_FLAGS_CLEAR;
  e->damage_attribute   = ENTITY_DAMAGE_FLAGS_CLEAR;
  e->damage_affect      = ENTITY_DAMAGE_FLAGS_CLEAR;
  e->collision_flags    = ENTITY_COLLISION_FLAGS_CLEAR;
  e->orientation        = 0x00;

  e->pos_x  = 0;
  e->pos_y  = 0;
  e->vel_x  = 0;
  e->vel_y  = 0;

  e->hp     = 1;

  e->move_count       = 0;
  e->cooldown_count   = 0;
  e->spin_count       = 0;
  e->frame_count      = 0;

  e->rx     = 0;
  e->ry     = 0;

  e->tile   = 0;

  e->animation_array  = NULL;
  e->frame_length     = 0;
  e->animation_length = 0;

  return 0;
}

/*******************************************************************************
** entity_set_type()
*******************************************************************************/
short int entity_set_type(entity* e, int type)
{
  if (e == NULL)
    return 1;

  /* clear flags */
  e->update_flags       = ENTITY_UPDATE_FLAGS_CLEAR;
  e->action_flags       = ENTITY_ACTION_FLAGS_CLEAR;
  e->special_flags      = ENTITY_SPECIAL_FLAGS_CLEAR;
  e->animation_flags    = ENTITY_ANIMATION_FLAGS_CLEAR;
  e->move_attribute     = ENTITY_MOVE_FLAGS_CLEAR;
  e->move_affect        = ENTITY_MOVE_FLAGS_CLEAR;
  e->trigger_attribute  = ENTITY_TRIGGER_FLAGS_CLEAR;
  e->trigger_affect     = ENTITY_TRIGGER_FLAGS_CLEAR;
  e->damage_attribute   = ENTITY_DAMAGE_FLAGS_CLEAR;
  e->damage_affect      = ENTITY_DAMAGE_FLAGS_CLEAR;
  e->collision_flags    = ENTITY_COLLISION_FLAGS_CLEAR;

  /* clear speed flag */
  e->orientation &= ~ENTITY_SPEED_FLAG;

  /* walls */
  if (type == ENTITY_TYPE_OUTER_WALL_TOP_LEFT)
  {
    e->type = type;
    e->tile = 0;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_OUTER_WALL_TOP)
  {
    e->type = type;
    e->tile = 1;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_OUTER_WALL_TOP_RIGHT)
  {
    e->type = type;
    e->tile = 2;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_OUTER_WALL_RIGHT)
  {
    e->type = type;
    e->tile = 3;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_OUTER_WALL_LEFT)
  {
    e->type = type;
    e->tile = 4;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_OUTER_WALL_BOTTOM_LEFT)
  {
    e->type = type;
    e->tile = 5;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_OUTER_WALL_BOTTOM)
  {
    e->type = type;
    e->tile = 6;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_OUTER_WALL_BOTTOM_RIGHT)
  {
    e->type = type;
    e->tile = 7;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_INNER_WALL_TOP)
  {
    e->type = type;
    e->tile = 8;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_INNER_WALL_BOTTOM)
  {
    e->type = type;
    e->tile = 9;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  /* portcullis */
  else if (type == ENTITY_TYPE_PORTCULLIS_CLOSED)
  {
    e->type = type;
    e->tile = 12;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_PORTCULLIS_OPEN)
  {
    e->type = type;
    e->tile = 13;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_VAMPIRE;
    e->move_affect &= ~ENTITY_MOVE_FLAG_PLAYER_BAT;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  /* floor, floor borders */
  else if (type == ENTITY_TYPE_FLOOR)
  {
    e->type = type;
    e->tile = 10;
    e->rx = 16;
    e->ry = 16;
  }
  else if (type == ENTITY_TYPE_FLOOR_BORDER_TOP_LEFT)
  {
    e->type = type;
    e->tile = 0;
    e->rx = 4;
    e->ry = 4;
  }
  else if (type == ENTITY_TYPE_FLOOR_BORDER_TOP)
  {
    e->type = type;
    e->tile = 1;
    e->rx = 8;
    e->ry = 4;
  }
  else if (type == ENTITY_TYPE_FLOOR_BORDER_TOP_RIGHT)
  {
    e->type = type;
    e->tile = 2;
    e->rx = 4;
    e->ry = 4;
  }
  else if (type == ENTITY_TYPE_FLOOR_BORDER_LEFT)
  {
    e->type = type;
    e->tile = 3;
    e->rx = 4;
    e->ry = 8;
  }
  else if (type == ENTITY_TYPE_FLOOR_BORDER_RIGHT)
  {
    e->type = type;
    e->tile = 4;
    e->rx = 4;
    e->ry = 8;
  }
  else if (type == ENTITY_TYPE_FLOOR_BORDER_BOTTOM_LEFT)
  {
    e->type = type;
    e->tile = 5;
    e->rx = 4;
    e->ry = 4;
  }
  else if (type == ENTITY_TYPE_FLOOR_BORDER_BOTTOM)
  {
    e->type = type;
    e->tile = 6;
    e->rx = 8;
    e->ry = 4;
  }
  else if (type == ENTITY_TYPE_FLOOR_BORDER_BOTTOM_RIGHT)
  {
    e->type = type;
    e->tile = 7;
    e->rx = 4;
    e->ry = 4;
  }
  /* environment, environment borders */
  else if (type == ENTITY_TYPE_GRASS)
  {
    e->type = type;

    if (G_theme == THEME_FOYER)
      e->tile = 16;
    else if (G_theme == THEME_CRYPT)
      e->tile = 18;
    else if (G_theme == THEME_WATERS)
      e->tile = 16;
    else if (G_theme == THEME_PERISTYLE)
      e->tile = 16;
    else if (G_theme == THEME_LIBRARY)
      e->tile = 18;
    else if (G_theme == THEME_GARDENS)
      e->tile = 16;
    else if (G_theme == THEME_DUNGEON)
      e->tile = 20;
    else if (G_theme == THEME_SHRINE)
      e->tile = 22;
    else if (G_theme == THEME_LABYRINTH)
      e->tile = 18;
    else if (G_theme == THEME_BALLROOM)
      e->tile = 20;
    else if (G_theme == THEME_PENTOMINO)
      e->tile = 16;
    else if (G_theme == THEME_ARMORY)
      e->tile = 18;
    else if (G_theme == THEME_YGGDRASIL)
      e->tile = 16;
    else if (G_theme == THEME_HEAVEN)
      e->tile = 16;
    else if (G_theme == THEME_FUTURE)
      e->tile = 18;
    else if (G_theme == THEME_ALCHEMY)
      e->tile = 16;
    else if (G_theme == THEME_ARENA)
      e->tile = 18;
    else if (G_theme == THEME_APOGEE)
      e->tile = 16;
    else if (G_theme == THEME_PAGAN)
      e->tile = 18;
    else if (G_theme == THEME_TIBET)
      e->tile = 22;
    else if (G_theme == THEME_GOLDEN)
      e->tile = 18;
    else if (G_theme == THEME_DESSERTS)
      e->tile = 22;
    else
      e->tile = 16;

    e->rx = 16;
    e->ry = 16;
    e->move_affect |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect |= ENTITY_MOVE_FLAG_ENEMY_BAT;
  }
  else if (type == ENTITY_TYPE_WATER)
  {
    e->type = type;
    e->tile = 0;
    e->rx = 8;
    e->ry = 8;
    e->move_affect |= ENTITY_MOVE_FLAG_VAMPIRE;
    e->move_affect |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect |= ENTITY_MOVE_FLAG_PUSHABLE_LOW;
  }
  else if (type == ENTITY_TYPE_ICE)
  {
    e->type = type;
    e->tile = 2;
    e->rx = 16;
    e->ry = 16;
  }
  else if (type == ENTITY_TYPE_GRASS_BORDER_TOP_LEFT)
  {
    e->type = type;
    e->tile = 0;

    ENTITY_SET_GRASS_BORDER_TILE_OFFSET(e)

    e->rx = 2;
    e->ry = 2;
  }
  else if (type == ENTITY_TYPE_GRASS_BORDER_TOP)
  {
    e->type = type;
    e->tile = 1;

    ENTITY_SET_GRASS_BORDER_TILE_OFFSET(e)

    e->rx = 12;
    e->ry = 2;
  }
  else if (type == ENTITY_TYPE_GRASS_BORDER_TOP_RIGHT)
  {
    e->type = type;
    e->tile = 2;

    ENTITY_SET_GRASS_BORDER_TILE_OFFSET(e)

    e->rx = 2;
    e->ry = 2;
  }
  else if (type == ENTITY_TYPE_GRASS_BORDER_LEFT)
  {
    e->type = type;
    e->tile = 3;

    ENTITY_SET_GRASS_BORDER_TILE_OFFSET(e)

    e->rx = 2;
    e->ry = 12;
  }
  else if (type == ENTITY_TYPE_GRASS_BORDER_RIGHT)
  {
    e->type = type;
    e->tile = 4;

    ENTITY_SET_GRASS_BORDER_TILE_OFFSET(e)

    e->rx = 2;
    e->ry = 12;
  }
  else if (type == ENTITY_TYPE_GRASS_BORDER_BOTTOM_LEFT)
  {
    e->type = type;
    e->tile = 5;

    ENTITY_SET_GRASS_BORDER_TILE_OFFSET(e)

    e->rx = 2;
    e->ry = 2;
  }
  else if (type == ENTITY_TYPE_GRASS_BORDER_BOTTOM)
  {
    e->type = type;
    e->tile = 6;

    ENTITY_SET_GRASS_BORDER_TILE_OFFSET(e)

    e->rx = 12;
    e->ry = 2;
  }
  else if (type == ENTITY_TYPE_GRASS_BORDER_BOTTOM_RIGHT)
  {
    e->type = type;
    e->tile = 7;

    ENTITY_SET_GRASS_BORDER_TILE_OFFSET(e)

    e->rx = 2;
    e->ry = 2;
  }
  else if (type == ENTITY_TYPE_ICE_BORDER_TOP_LEFT)
  {
    e->type = type;
    e->tile = 0;
    e->rx = 2;
    e->ry = 2;
  }
  else if (type == ENTITY_TYPE_ICE_BORDER_TOP)
  {
    e->type = type;
    e->tile = 1;
    e->rx = 12;
    e->ry = 2;
  }
  else if (type == ENTITY_TYPE_ICE_BORDER_TOP_RIGHT)
  {
    e->type = type;
    e->tile = 2;
    e->rx = 2;
    e->ry = 2;
  }
  else if (type == ENTITY_TYPE_ICE_BORDER_LEFT)
  {
    e->type = type;
    e->tile = 3;
    e->rx = 2;
    e->ry = 12;
  }
  else if (type == ENTITY_TYPE_ICE_BORDER_RIGHT)
  {
    e->type = type;
    e->tile = 4;
    e->rx = 2;
    e->ry = 12;
  }
  else if (type == ENTITY_TYPE_ICE_BORDER_BOTTOM_LEFT)
  {
    e->type = type;
    e->tile = 5;
    e->rx = 2;
    e->ry = 2;
  }
  else if (type == ENTITY_TYPE_ICE_BORDER_BOTTOM)
  {
    e->type = type;
    e->tile = 6;
    e->rx = 12;
    e->ry = 2;
  }
  else if (type == ENTITY_TYPE_ICE_BORDER_BOTTOM_RIGHT)
  {
    e->type = type;
    e->tile = 7;
    e->rx = 2;
    e->ry = 2;
  }
  /* obstacles */
  else if (type == ENTITY_TYPE_BLOCK)
  {
    e->type = type;
    e->hp = 1;

    if (G_theme == THEME_FOYER)
      e->tile = 4;
    else if (G_theme == THEME_CRYPT)
      e->tile = 8;
    else if (G_theme == THEME_WATERS)
      e->tile = 1;
    else if (G_theme == THEME_PERISTYLE)
      e->tile = 4;
    else if (G_theme == THEME_LIBRARY)
      e->tile = 9;
    else if (G_theme == THEME_GARDENS)
      e->tile = 4;
    else if (G_theme == THEME_DUNGEON)
      e->tile = 6;
    else if (G_theme == THEME_SHRINE)
      e->tile = 5;
    else if (G_theme == THEME_LABYRINTH)
      e->tile = 2;
    else if (G_theme == THEME_BALLROOM)
      e->tile = 8;
    else if (G_theme == THEME_PENTOMINO)
      e->tile = 4;
    else if (G_theme == THEME_ARMORY)
      e->tile = 2;
    else if (G_theme == THEME_YGGDRASIL)
      e->tile = 9;
    else if (G_theme == THEME_HEAVEN)
      e->tile = 5;
    else if (G_theme == THEME_FUTURE)
      e->tile = 1;
    else if (G_theme == THEME_ALCHEMY)
      e->tile = 3;
    else if (G_theme == THEME_ARENA)
      e->tile = 8;
    else if (G_theme == THEME_APOGEE)
      e->tile = 4;
    else if (G_theme == THEME_PAGAN)
      e->tile = 7;
    else if (G_theme == THEME_TIBET)
      e->tile = 0;
    else if (G_theme == THEME_GOLDEN)
      e->tile = 3;
    else if (G_theme == THEME_DESSERTS)
      e->tile = 5;
    else
      e->tile = 4;

    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_PILLAR)
  {
    e->type = type;
    e->hp = 1;

    if (G_theme == THEME_FOYER)
      e->tile = 20;
    else if (G_theme == THEME_CRYPT)
      e->tile = 24;
    else if (G_theme == THEME_WATERS)
      e->tile = 17;
    else if (G_theme == THEME_PERISTYLE)
      e->tile = 20;
    else if (G_theme == THEME_LIBRARY)
      e->tile = 25;
    else if (G_theme == THEME_GARDENS)
      e->tile = 20;
    else if (G_theme == THEME_DUNGEON)
      e->tile = 22;
    else if (G_theme == THEME_SHRINE)
      e->tile = 21;
    else if (G_theme == THEME_LABYRINTH)
      e->tile = 18;
    else if (G_theme == THEME_BALLROOM)
      e->tile = 24;
    else if (G_theme == THEME_PENTOMINO)
      e->tile = 20;
    else if (G_theme == THEME_ARMORY)
      e->tile = 18;
    else if (G_theme == THEME_YGGDRASIL)
      e->tile = 25;
    else if (G_theme == THEME_HEAVEN)
      e->tile = 21;
    else if (G_theme == THEME_FUTURE)
      e->tile = 17;
    else if (G_theme == THEME_ALCHEMY)
      e->tile = 19;
    else if (G_theme == THEME_ARENA)
      e->tile = 24;
    else if (G_theme == THEME_APOGEE)
      e->tile = 20;
    else if (G_theme == THEME_PAGAN)
      e->tile = 23;
    else if (G_theme == THEME_TIBET)
      e->tile = 16;
    else if (G_theme == THEME_GOLDEN)
      e->tile = 19;
    else if (G_theme == THEME_DESSERTS)
      e->tile = 21;
    else
      e->tile = 20;

    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_EVIL_EYE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_TREE)
  {
    e->type = type;
    e->hp = 1;

    if (G_theme == THEME_FOYER)
      e->tile = 13;
    else if (G_theme == THEME_CRYPT)
      e->tile = 11;
    else if (G_theme == THEME_WATERS)
      e->tile = 13;
    else if (G_theme == THEME_PERISTYLE)
      e->tile = 13;
    else if (G_theme == THEME_LIBRARY)
      e->tile = 15;
    else if (G_theme == THEME_GARDENS)
      e->tile = 13;
    else if (G_theme == THEME_DUNGEON)
      e->tile = 12;
    else if (G_theme == THEME_SHRINE)
      e->tile = 14;
    else if (G_theme == THEME_LABYRINTH)
      e->tile = 15;
    else if (G_theme == THEME_BALLROOM)
      e->tile = 13;
    else if (G_theme == THEME_PENTOMINO)
      e->tile = 15;
    else if (G_theme == THEME_ARMORY)
      e->tile = 11;
    else if (G_theme == THEME_YGGDRASIL)
      e->tile = 13;
    else if (G_theme == THEME_HEAVEN)
      e->tile = 13;
    else if (G_theme == THEME_FUTURE)
      e->tile = 12;
    else if (G_theme == THEME_ALCHEMY)
      e->tile = 13;
    else if (G_theme == THEME_ARENA)
      e->tile = 11;
    else if (G_theme == THEME_APOGEE)
      e->tile = 13;
    else if (G_theme == THEME_PAGAN)
      e->tile = 11;
    else if (G_theme == THEME_TIBET)
      e->tile = 10;
    else if (G_theme == THEME_GOLDEN)
      e->tile = 11;
    else if (G_theme == THEME_DESSERTS)
      e->tile = 14;
    else
      e->tile = 13;

    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_EVIL_EYE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  /* symbols */
  else if (type == ENTITY_TYPE_COBWEB)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 4;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_VAMPIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_JOKER_CARD)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 5;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_SEAL_OF_SOLOMON)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 6;
    e->rx = 16;
    e->ry = 16;
  }
  else if (type == ENTITY_TYPE_YIN_YANG)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 8;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  /* bridges */
  else if (type == ENTITY_TYPE_BRIDGE_STONE_VERTICAL)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 27;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_BRIDGE_WOOD_VERTICAL)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 28;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_BRIDGE_CRACKED_VERTICAL)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 29;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_BRIDGE_STONE_HORIZONTAL)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 24;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_BRIDGE_WOOD_HORIZONTAL)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 25;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_BRIDGE_CRACKED_HORIZONTAL)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 26;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  /* submerged */
  else if (type == ENTITY_TYPE_BOX_WOOD_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 38;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_BOX_METAL_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 39;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_BOX_TNT_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 46;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_BOX_STONE_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 47;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_PRISM_BLOCK_0_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 55;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_PRISM_BLOCK_45_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 62;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_PRISM_BLOCK_90_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 54;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_PRISM_BLOCK_135_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 63;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_DIE_SOLID_1_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 48;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_DIE_SOLID_2_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 49;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_DIE_SOLID_3_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 50;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_DIE_SOLID_4_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 51;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_DIE_SOLID_5_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 52;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_DIE_SOLID_6_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 53;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_MAHJONG_TILE_EAST_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 32;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_MAHJONG_TILE_NORTH_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 34;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_MAHJONG_TILE_WEST_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 40;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_MAHJONG_TILE_SOUTH_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 42;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_SPELLBINDER_EMPTY_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 36;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_SPELLBINDER_FIRE_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 37;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_SPELLBINDER_ICE_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 44;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_SPELLBINDER_NEUTRAL_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 45;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_ICE_CUBE_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 30;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  /* pushable objects */
  else if (type == ENTITY_TYPE_BOX_WOOD)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 0;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_BOX_METAL)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 1;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_FLOOR_SPIKE;
  }
  else if (type == ENTITY_TYPE_BOX_TNT)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 2;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_BOX_STONE)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 3;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_POT_CLAY)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 8;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_LOW;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_PLAYER_BAT;
    e->move_affect &= ~ENTITY_MOVE_FLAG_ENEMY_BAT;
    e->move_affect &= ~ENTITY_MOVE_FLAG_EVIL_EYE;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_POT_METAL)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 9;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_LOW;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_PLAYER_BAT;
    e->move_affect &= ~ENTITY_MOVE_FLAG_ENEMY_BAT;
    e->move_affect &= ~ENTITY_MOVE_FLAG_EVIL_EYE;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_FLOOR_SPIKE;
  }
  else if (type == ENTITY_TYPE_POT_TNT)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 10;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_LOW;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_PLAYER_BAT;
    e->move_affect &= ~ENTITY_MOVE_FLAG_ENEMY_BAT;
    e->move_affect &= ~ENTITY_MOVE_FLAG_EVIL_EYE;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_POT_STONE)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 11;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_LOW;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_PLAYER_BAT;
    e->move_affect &= ~ENTITY_MOVE_FLAG_ENEMY_BAT;
    e->move_affect &= ~ENTITY_MOVE_FLAG_EVIL_EYE;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_AQUA_FORTIS)
  {
    e->type = type;
    e->hp = 4;
    e->tile = 6;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_LOW;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_PLAYER_BAT;
    e->move_affect &= ~ENTITY_MOVE_FLAG_ENEMY_BAT;
    e->move_affect &= ~ENTITY_MOVE_FLAG_EVIL_EYE;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_FLASK;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_FLOOR_SPIKE;
  }
  else if (type == ENTITY_TYPE_AQUA_EXPLODIS)
  {
    e->type = type;
    e->hp = 4;
    e->tile = 38;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_LOW;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_PLAYER_BAT;
    e->move_affect &= ~ENTITY_MOVE_FLAG_ENEMY_BAT;
    e->move_affect &= ~ENTITY_MOVE_FLAG_EVIL_EYE;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_FLASK;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_FLOOR_SPIKE;
  }
  else if (type == ENTITY_TYPE_CANDLE_UNLIT)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 16;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_LOW;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_PLAYER_BAT;
    e->move_affect &= ~ENTITY_MOVE_FLAG_ENEMY_BAT;
    e->move_affect &= ~ENTITY_MOVE_FLAG_EVIL_EYE;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_CANDLE_LIT)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 17;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_LOW;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_PLAYER_BAT;
    e->move_affect &= ~ENTITY_MOVE_FLAG_ENEMY_BAT;
    e->move_affect &= ~ENTITY_MOVE_FLAG_EVIL_EYE;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_PRISM_BLOCK_0)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 5;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_REFLECTER;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_PRISM_BLOCK_45)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 12;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_REFLECTER;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_PRISM_BLOCK_90)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 4;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_REFLECTER;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_PRISM_BLOCK_135)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 13;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_REFLECTER;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_EIGHT_BALL)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 40;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_EIGHT_BALLS;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_EIGHT_BALLS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_DIE_SOLID_1)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 48;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_DIE_SOLID_2)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 49;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_DIE_SOLID_3)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 50;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_DIE_SOLID_4)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 51;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_DIE_SOLID_5)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 52;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_DIE_SOLID_6)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 53;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_MAHJONG_TILE_EAST)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 24;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_MAHJONG_TILE_NORTH)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 26;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_MAHJONG_TILE_WEST)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 32;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_MAHJONG_TILE_SOUTH)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 34;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_SPELLBINDER_EMPTY)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 28;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_SPELLBINDER_FIRE)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 29;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_SPELLBINDER_ICE)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 36;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_SPELLBINDER_NEUTRAL)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 37;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  /* vanished dice */
  else if (type == ENTITY_TYPE_DIE_VANISHED_1)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 56;
    e->rx = 16;
    e->ry = 16;
  }
  else if (type == ENTITY_TYPE_DIE_VANISHED_2)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 57;
    e->rx = 16;
    e->ry = 16;
  }
  else if (type == ENTITY_TYPE_DIE_VANISHED_3)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 58;
    e->rx = 16;
    e->ry = 16;
  }
  else if (type == ENTITY_TYPE_DIE_VANISHED_4)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 59;
    e->rx = 16;
    e->ry = 16;
  }
  else if (type == ENTITY_TYPE_DIE_VANISHED_5)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 60;
    e->rx = 16;
    e->ry = 16;
  }
  else if (type == ENTITY_TYPE_DIE_VANISHED_6)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 61;
    e->rx = 16;
    e->ry = 16;
  }
  else if (type == ENTITY_TYPE_DIE_VANISHED_1_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 56;
    e->rx = 16;
    e->ry = 16;
  }
  else if (type == ENTITY_TYPE_DIE_VANISHED_2_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 57;
    e->rx = 16;
    e->ry = 16;
  }
  else if (type == ENTITY_TYPE_DIE_VANISHED_3_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 58;
    e->rx = 16;
    e->ry = 16;
  }
  else if (type == ENTITY_TYPE_DIE_VANISHED_4_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 59;
    e->rx = 16;
    e->ry = 16;
  }
  else if (type == ENTITY_TYPE_DIE_VANISHED_5_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 60;
    e->rx = 16;
    e->ry = 16;
  }
  else if (type == ENTITY_TYPE_DIE_VANISHED_6_SUBMERGED)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 61;
    e->rx = 16;
    e->ry = 16;
  }
  /* ice cubes */
  else if (ENTITY_TYPE_IS_ICE_CUBE(type))
  {
    e->type = type;
    e->hp = 1;
    e->tile = 20;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  /* arrows */
  else if (type == ENTITY_TYPE_ARROWS_RED)
  {
    e->type = type;
    e->tile = 5;
    e->rx = 16;
    e->ry = 16;
    e->move_affect |= ENTITY_MOVE_FLAG_VAMPIRE;
    e->move_affect |= ENTITY_MOVE_FLAG_PLAYER_BAT;
    e->move_affect |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect |= ENTITY_MOVE_FLAG_ENEMY_BAT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_ARROWS_GREEN)
  {
    e->type = type;
    e->tile = 6;
    e->rx = 16;
    e->ry = 16;
    e->move_affect |= ENTITY_MOVE_FLAG_VAMPIRE;
    e->move_affect |= ENTITY_MOVE_FLAG_PLAYER_BAT;
    e->move_affect |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect |= ENTITY_MOVE_FLAG_ENEMY_BAT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_ARROWS_BROWN)
  {
    e->type = type;
    e->tile = 7;
    e->rx = 16;
    e->ry = 16;
    e->move_affect |= ENTITY_MOVE_FLAG_VAMPIRE;
    e->move_affect |= ENTITY_MOVE_FLAG_PLAYER_BAT;
    e->move_affect |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect |= ENTITY_MOVE_FLAG_ENEMY_BAT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  /* ballistas */
  else if (type == ENTITY_TYPE_BALLISTA_RED)
  {
    e->type = type;
    e->tile = 0;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_EVIL_EYE;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_BALLISTAS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_BALLISTA_GREEN)
  {
    e->type = type;
    e->tile = 16;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_EVIL_EYE;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_BALLISTAS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_BALLISTA_BROWN)
  {
    e->type = type;
    e->tile = 32;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_EVIL_EYE;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_BALLISTAS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  /* pinball kickers */
  else if (type == ENTITY_TYPE_BAR_KICKER_RED)
  {
    e->type = type;
    e->tile = 21;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_REFLECTER;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_BAR_KICKER_GREEN)
  {
    e->type = type;
    e->tile = 22;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_REFLECTER;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_BAR_KICKER_BROWN)
  {
    e->type = type;
    e->tile = 23;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_REFLECTER;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_TRIANGLE_KICKER_RED)
  {
    e->type = type;
    e->tile = 45;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_REFLECTER;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_TRIANGLE_KICKER_GREEN)
  {
    e->type = type;
    e->tile = 46;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_REFLECTER;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_TRIANGLE_KICKER_BROWN)
  {
    e->type = type;
    e->tile = 47;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_REFLECTER;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  /* conveyers */
  else if (type == ENTITY_TYPE_CONVEYER_WHITE)
  {
    e->type = type;
    e->tile = 60;
    e->rx = 16;
    e->ry = 16;
  }
  else if (type == ENTITY_TYPE_CONVEYER_CYAN)
  {
    e->type = type;
    e->tile = 52;
    e->rx = 16;
    e->ry = 16;
  }
  else if (type == ENTITY_TYPE_CONVEYER_MAGENTA)
  {
    e->type = type;
    e->tile = 56;
    e->rx = 16;
    e->ry = 16;
  }
  /* floor spikes */
  else if (type == ENTITY_TYPE_FLOOR_SPIKE_DOWN_WHITE)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 212;
    e->rx = 8;
    e->ry = 8;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_FLOOR_SPIKE_DOWN_CYAN)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 208;
    e->rx = 8;
    e->ry = 8;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_FLOOR_SPIKE_DOWN_MAGENTA)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 210;
    e->rx = 8;
    e->ry = 8;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_FLOOR_SPIKE_UP_WHITE)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 197;
    e->rx = 8;
    e->ry = 8;
    e->move_affect |= ENTITY_MOVE_FLAG_VAMPIRE;
    e->move_affect |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect |= ENTITY_MOVE_FLAG_PUSHABLE_LOW;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_FLOOR_SPIKE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_FLASK;
  }
  else if (type == ENTITY_TYPE_FLOOR_SPIKE_UP_CYAN)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 193;
    e->rx = 8;
    e->ry = 8;
    e->move_affect |= ENTITY_MOVE_FLAG_VAMPIRE;
    e->move_affect |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect |= ENTITY_MOVE_FLAG_PUSHABLE_LOW;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_FLOOR_SPIKE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_FLASK;
  }
  else if (type == ENTITY_TYPE_FLOOR_SPIKE_UP_MAGENTA)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 195;
    e->rx = 8;
    e->ry = 8;
    e->move_affect |= ENTITY_MOVE_FLAG_VAMPIRE;
    e->move_affect |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect |= ENTITY_MOVE_FLAG_PUSHABLE_HIGH;
    e->move_affect |= ENTITY_MOVE_FLAG_PUSHABLE_LOW;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_FLOOR_SPIKE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_FLASK;
  }
  /* levers */
  else if (type == ENTITY_TYPE_LEVER_WHITE)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 16;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_PLAYER_BAT;
    e->move_affect &= ~ENTITY_MOVE_FLAG_ENEMY_BAT;
    e->move_affect &= ~ENTITY_MOVE_FLAG_EVIL_EYE;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_LEVERS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_LEVER_CYAN)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 0;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_PLAYER_BAT;
    e->move_affect &= ~ENTITY_MOVE_FLAG_ENEMY_BAT;
    e->move_affect &= ~ENTITY_MOVE_FLAG_EVIL_EYE;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_LEVERS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_LEVER_MAGENTA)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 8;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_PLAYER_BAT;
    e->move_affect &= ~ENTITY_MOVE_FLAG_ENEMY_BAT;
    e->move_affect &= ~ENTITY_MOVE_FLAG_EVIL_EYE;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_LEVERS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  /* switches */
  else if (type == ENTITY_TYPE_SPIN_SWITCH_RED_CCW)
  {
    e->type = type;
    e->tile = 24;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_SPIN_SWITCH_RED_CW)
  {
    e->type = type;
    e->tile = 3;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_SPIN_SWITCH_GREEN_CCW)
  {
    e->type = type;
    e->tile = 25;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_SPIN_SWITCH_GREEN_CW)
  {
    e->type = type;
    e->tile = 11;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_SPIN_SWITCH_BROWN_CCW)
  {
    e->type = type;
    e->tile = 26;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_SPIN_SWITCH_BROWN_CW)
  {
    e->type = type;
    e->tile = 19;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_NUMBER_SWITCH_EVEN)
  {
    e->type = type;
    e->tile = 27;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_NUMBER_SWITCH_ODD)
  {
    e->type = type;
    e->tile = 35;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_NUMBER_SWITCH_PRIME)
  {
    e->type = type;
    e->tile = 43;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_NUMBER_SWITCH_COMPOSITE)
  {
    e->type = type;
    e->tile = 51;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_NUMBER_SWITCH_SQUARE)
  {
    e->type = type;
    e->tile = 59;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_NUMBER_SWITCH_TRIANGULAR)
  {
    e->type = type;
    e->tile = 31;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  /* enemies */
  else if (type == ENTITY_TYPE_PUMPKIN)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 32;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_GHOST)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 60;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_MASK_HORIZONTAL)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 34;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_MASK_VERTICAL)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 42;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_SNAKE)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 44;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_DOUBLE_VAMPIRE)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 8;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_LEVERS;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_BALLISTAS;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_DOUBLE_BAT)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 13;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY_BAT;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_PUSHABLE_LOW;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_REVERSE_DOUBLE_VAMPIRE)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 8;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_LEVERS;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_BALLISTAS;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_REVERSE_DOUBLE_BAT)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 13;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY_BAT;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_PUSHABLE_LOW;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_FAERIE_HORIZONTAL)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 54;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_FAERIE_VERTICAL)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 48;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_VENUSIAN)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 56;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_VENUSIAN_ROOT)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 60;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_WITCH)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 36;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_UNDINE)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 0;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_SORCERESS)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 4;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_FROG)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 35;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_IMP_LT)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 3;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_PLAYER;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_IMP_RT)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 7;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_PLAYER;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_LIL_BOT)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 32;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_POLTERGEIST)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 32;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_WISP_LEFT_WALL)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 37;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_WISPS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_WISP_RIGHT_WALL)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 38;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_WISPS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_JIANGSHI_LT)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 56;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_JIANGSHIS;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_PLAYER;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_JIANGSHI_RT)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 60;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_JIANGSHIS;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_PLAYER;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_MUMMY_LT)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 0;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_MUMMY_RT)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 4;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_GUARDIAN_LT)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 44;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_REFLECTER;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_GUARDIAN_RT)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 40;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_ENEMY;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_REFLECTER;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_LASER_GUN)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 48;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  /* pickups */
  else if (type == ENTITY_TYPE_BLOOD_VIAL)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 25;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_VAMPIRE;
    e->move_affect &= ~ENTITY_MOVE_FLAG_EVIL_EYE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_BAT_VIAL)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 26;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_VAMPIRE;
    e->move_affect &= ~ENTITY_MOVE_FLAG_EVIL_EYE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_BLUE_MANA)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 27;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_VAMPIRE;
    e->move_affect &= ~ENTITY_MOVE_FLAG_EVIL_EYE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_GREEN_MANA)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 28;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_VAMPIRE;
    e->move_affect &= ~ENTITY_MOVE_FLAG_EVIL_EYE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_FLOPPY_DISK_3_AND_1_2)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 29;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_VAMPIRE;
    e->move_affect &= ~ENTITY_MOVE_FLAG_EVIL_EYE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_FLOPPY_DISK_5_AND_1_4)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 30;
    e->rx = 16;
    e->ry = 16;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_VAMPIRE;
    e->move_affect &= ~ENTITY_MOVE_FLAG_EVIL_EYE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  /* player */
  else if (type == ENTITY_TYPE_PLAYER_VAMPIRE)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 8;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_VAMPIRE;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PLAYER;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_PUSHABLE;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_LEVERS;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_BALLISTAS;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_JIANGSHIS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_PLAYER_BAT)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 13;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_PLAYER_BAT;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->move_affect &= ~ENTITY_MOVE_FLAG_PUSHABLE_LOW;
    e->trigger_attribute |= ENTITY_TRIGGER_FLAG_PLAYER;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_WISPS;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_JIANGSHIS;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  /* spells */
  else if (type == ENTITY_TYPE_FIRE_SPELL)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 26;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_SPELL;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_REFLECTER;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_SPELL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE;
    e->orientation |= ENTITY_SPEED_FLAG;
  }
  else if (type == ENTITY_TYPE_ICE_SPELL)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 32;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_SPELL;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_REFLECTER;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_SPELL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_WEAK_TO_ICE;
    e->orientation |= ENTITY_SPEED_FLAG;
  }
  else if (type == ENTITY_TYPE_NEUTRAL_SPELL)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 48;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_SPELL;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_REFLECTER;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_SPELL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
  }
  else if (type == ENTITY_TYPE_WARP_SPELL)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 40;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_SPELL;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_REFLECTER;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_SPELL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else if (type == ENTITY_TYPE_BALLISTA_BOLT)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 52;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_SPELL;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_REFLECTER;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_SPELL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
    e->orientation |= ENTITY_SPEED_FLAG;
  }
  else if (type == ENTITY_TYPE_LASER_SHOT)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 54;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_SPELL;
    e->move_affect = ENTITY_MOVE_FLAGS_ALL;
    e->trigger_affect |= ENTITY_TRIGGER_FLAG_REFLECTER;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_SPELL;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_SPELL;
    e->orientation |= ENTITY_SPEED_FLAG;
  }
  else if (type == ENTITY_TYPE_EVIL_EYE)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 44;
    e->rx = 16;
    e->ry = 16;
    e->move_attribute |= ENTITY_MOVE_FLAG_EVIL_EYE;
    e->orientation |= ENTITY_SPEED_FLAG;
  }
  else if (type == ENTITY_TYPE_EXPLOSION)
  {
    e->type = type;
    e->hp = 1;
    e->tile = 58;
    e->rx = 16;
    e->ry = 16;
    e->damage_attribute |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
    e->damage_affect |= ENTITY_DAMAGE_FLAG_EXPLODABLE;
  }
  else
  {
    e->type = ENTITY_TYPE_NONE;
  }

  return 0;
}

/*******************************************************************************
** entity_set_facing()
*******************************************************************************/
short int entity_set_facing(entity* e, unsigned char facing)
{
  if (e == NULL)
    return 1;

  /* clear facing and rotation bits */
  e->orientation &= ~ENTITY_FACING_MASK;
  e->orientation &= ~ENTITY_THETA_MASK;

  /* set facing */
  e->orientation |= facing;

  /* set tile and rotation based on type */
  /* arrows */
  if (e->type == ENTITY_TYPE_ARROWS_RED)
  {
    if (facing == ENTITY_FACING_RIGHT)
    {
      e->tile = 5;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP_RIGHT)
    {
      e->tile = 13;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP)
    {
      e->tile = 5;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_UP_LEFT)
    {
      e->tile = 13;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_LEFT)
    {
      e->tile = 5;
      e->orientation |= ENTITY_THETA_180;
    }
    else if (facing == ENTITY_FACING_DOWN_LEFT)
    {
      e->tile = 13;
      e->orientation |= ENTITY_THETA_180;
    }
    else if (facing == ENTITY_FACING_DOWN)
    {
      e->tile = 5;
      e->orientation |= ENTITY_THETA_270;
    }
    else if (facing == ENTITY_FACING_DOWN_RIGHT)
    {
      e->tile = 13;
      e->orientation |= ENTITY_THETA_270;
    }
  }
  else if (e->type == ENTITY_TYPE_ARROWS_GREEN)
  {
    if (facing == ENTITY_FACING_RIGHT)
    {
      e->tile = 6;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP_RIGHT)
    {
      e->tile = 14;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP)
    {
      e->tile = 6;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_UP_LEFT)
    {
      e->tile = 14;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_LEFT)
    {
      e->tile = 6;
      e->orientation |= ENTITY_THETA_180;
    }
    else if (facing == ENTITY_FACING_DOWN_LEFT)
    {
      e->tile = 14;
      e->orientation |= ENTITY_THETA_180;
    }
    else if (facing == ENTITY_FACING_DOWN)
    {
      e->tile = 6;
      e->orientation |= ENTITY_THETA_270;
    }
    else if (facing == ENTITY_FACING_DOWN_RIGHT)
    {
      e->tile = 14;
      e->orientation |= ENTITY_THETA_270;
    }
  }
  else if (e->type == ENTITY_TYPE_ARROWS_BROWN)
  {
    if (facing == ENTITY_FACING_RIGHT)
    {
      e->tile = 7;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP_RIGHT)
    {
      e->tile = 15;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP)
    {
      e->tile = 7;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_UP_LEFT)
    {
      e->tile = 15;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_LEFT)
    {
      e->tile = 7;
      e->orientation |= ENTITY_THETA_180;
    }
    else if (facing == ENTITY_FACING_DOWN_LEFT)
    {
      e->tile = 15;
      e->orientation |= ENTITY_THETA_180;
    }
    else if (facing == ENTITY_FACING_DOWN)
    {
      e->tile = 7;
      e->orientation |= ENTITY_THETA_270;
    }
    else if (facing == ENTITY_FACING_DOWN_RIGHT)
    {
      e->tile = 15;
      e->orientation |= ENTITY_THETA_270;
    }
  }
  /* ballistas */
  else if (e->type == ENTITY_TYPE_BALLISTA_RED)
  {
    if (facing == ENTITY_FACING_RIGHT)
    {
      e->tile = 0;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP_RIGHT)
    {
      e->tile = 8;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP)
    {
      e->tile = 0;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_UP_LEFT)
    {
      e->tile = 8;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_LEFT)
    {
      e->tile = 0;
      e->orientation |= ENTITY_THETA_180;
    }
    else if (facing == ENTITY_FACING_DOWN_LEFT)
    {
      e->tile = 8;
      e->orientation |= ENTITY_THETA_180;
    }
    else if (facing == ENTITY_FACING_DOWN)
    {
      e->tile = 0;
      e->orientation |= ENTITY_THETA_270;
    }
    else if (facing == ENTITY_FACING_DOWN_RIGHT)
    {
      e->tile = 8;
      e->orientation |= ENTITY_THETA_270;
    }
  }
  else if (e->type == ENTITY_TYPE_BALLISTA_GREEN)
  {
    if (facing == ENTITY_FACING_RIGHT)
    {
      e->tile = 16;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP_RIGHT)
    {
      e->tile = 24;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP)
    {
      e->tile = 16;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_UP_LEFT)
    {
      e->tile = 24;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_LEFT)
    {
      e->tile = 16;
      e->orientation |= ENTITY_THETA_180;
    }
    else if (facing == ENTITY_FACING_DOWN_LEFT)
    {
      e->tile = 24;
      e->orientation |= ENTITY_THETA_180;
    }
    else if (facing == ENTITY_FACING_DOWN)
    {
      e->tile = 16;
      e->orientation |= ENTITY_THETA_270;
    }
    else if (facing == ENTITY_FACING_DOWN_RIGHT)
    {
      e->tile = 24;
      e->orientation |= ENTITY_THETA_270;
    }
  }
  else if (e->type == ENTITY_TYPE_BALLISTA_BROWN)
  {
    if (facing == ENTITY_FACING_RIGHT)
    {
      e->tile = 32;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP_RIGHT)
    {
      e->tile = 40;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP)
    {
      e->tile = 32;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_UP_LEFT)
    {
      e->tile = 40;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_LEFT)
    {
      e->tile = 32;
      e->orientation |= ENTITY_THETA_180;
    }
    else if (facing == ENTITY_FACING_DOWN_LEFT)
    {
      e->tile = 40;
      e->orientation |= ENTITY_THETA_180;
    }
    else if (facing == ENTITY_FACING_DOWN)
    {
      e->tile = 32;
      e->orientation |= ENTITY_THETA_270;
    }
    else if (facing == ENTITY_FACING_DOWN_RIGHT)
    {
      e->tile = 40;
      e->orientation |= ENTITY_THETA_270;
    }
  }
  /* pinball kickers */
  else if (e->type == ENTITY_TYPE_BAR_KICKER_RED)
  {
    if (facing == ENTITY_FACING_RIGHT)
    {
      e->tile = 21;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP_RIGHT)
    {
      e->tile = 29;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP)
    {
      e->tile = 21;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_UP_LEFT)
    {
      e->tile = 29;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_LEFT)
    {
      e->tile = 21;
      e->orientation |= ENTITY_THETA_180;
    }
    else if (facing == ENTITY_FACING_DOWN_LEFT)
    {
      e->tile = 29;
      e->orientation |= ENTITY_THETA_180;
    }
    else if (facing == ENTITY_FACING_DOWN)
    {
      e->tile = 21;
      e->orientation |= ENTITY_THETA_270;
    }
    else if (facing == ENTITY_FACING_DOWN_RIGHT)
    {
      e->tile = 29;
      e->orientation |= ENTITY_THETA_270;
    }
  }
  else if (e->type == ENTITY_TYPE_BAR_KICKER_GREEN)
  {
    if (facing == ENTITY_FACING_RIGHT)
    {
      e->tile = 22;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP_RIGHT)
    {
      e->tile = 30;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP)
    {
      e->tile = 22;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_UP_LEFT)
    {
      e->tile = 30;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_LEFT)
    {
      e->tile = 22;
      e->orientation |= ENTITY_THETA_180;
    }
    else if (facing == ENTITY_FACING_DOWN_LEFT)
    {
      e->tile = 30;
      e->orientation |= ENTITY_THETA_180;
    }
    else if (facing == ENTITY_FACING_DOWN)
    {
      e->tile = 22;
      e->orientation |= ENTITY_THETA_270;
    }
    else if (facing == ENTITY_FACING_DOWN_RIGHT)
    {
      e->tile = 30;
      e->orientation |= ENTITY_THETA_270;
    }
  }
  else if (e->type == ENTITY_TYPE_BAR_KICKER_BROWN)
  {
    if (facing == ENTITY_FACING_RIGHT)
    {
      e->tile = 23;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP_RIGHT)
    {
      e->tile = 31;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP)
    {
      e->tile = 23;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_UP_LEFT)
    {
      e->tile = 31;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_LEFT)
    {
      e->tile = 23;
      e->orientation |= ENTITY_THETA_180;
    }
    else if (facing == ENTITY_FACING_DOWN_LEFT)
    {
      e->tile = 31;
      e->orientation |= ENTITY_THETA_180;
    }
    else if (facing == ENTITY_FACING_DOWN)
    {
      e->tile = 23;
      e->orientation |= ENTITY_THETA_270;
    }
    else if (facing == ENTITY_FACING_DOWN_RIGHT)
    {
      e->tile = 31;
      e->orientation |= ENTITY_THETA_270;
    }
  }
  else if (e->type == ENTITY_TYPE_TRIANGLE_KICKER_RED)
  {
    if (facing == ENTITY_FACING_RIGHT)
    {
      e->tile = 37;
      e->orientation |= ENTITY_THETA_270;
    }
    else if (facing == ENTITY_FACING_UP_RIGHT)
    {
      e->tile = 45;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP)
    {
      e->tile = 37;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP_LEFT)
    {
      e->tile = 45;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_LEFT)
    {
      e->tile = 37;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_DOWN_LEFT)
    {
      e->tile = 45;
      e->orientation |= ENTITY_THETA_180;
    }
    else if (facing == ENTITY_FACING_DOWN)
    {
      e->tile = 37;
      e->orientation |= ENTITY_THETA_180;
    }
    else if (facing == ENTITY_FACING_DOWN_RIGHT)
    {
      e->tile = 45;
      e->orientation |= ENTITY_THETA_270;
    }
  }
  else if (e->type == ENTITY_TYPE_TRIANGLE_KICKER_GREEN)
  {
    if (facing == ENTITY_FACING_RIGHT)
    {
      e->tile = 38;
      e->orientation |= ENTITY_THETA_270;
    }
    else if (facing == ENTITY_FACING_UP_RIGHT)
    {
      e->tile = 46;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP)
    {
      e->tile = 38;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP_LEFT)
    {
      e->tile = 46;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_LEFT)
    {
      e->tile = 38;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_DOWN_LEFT)
    {
      e->tile = 46;
      e->orientation |= ENTITY_THETA_180;
    }
    else if (facing == ENTITY_FACING_DOWN)
    {
      e->tile = 38;
      e->orientation |= ENTITY_THETA_180;
    }
    else if (facing == ENTITY_FACING_DOWN_RIGHT)
    {
      e->tile = 46;
      e->orientation |= ENTITY_THETA_270;
    }
  }
  else if (e->type == ENTITY_TYPE_TRIANGLE_KICKER_BROWN)
  {
    if (facing == ENTITY_FACING_RIGHT)
    {
      e->tile = 39;
      e->orientation |= ENTITY_THETA_270;
    }
    else if (facing == ENTITY_FACING_UP_RIGHT)
    {
      e->tile = 47;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP)
    {
      e->tile = 39;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP_LEFT)
    {
      e->tile = 47;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_LEFT)
    {
      e->tile = 39;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_DOWN_LEFT)
    {
      e->tile = 47;
      e->orientation |= ENTITY_THETA_180;
    }
    else if (facing == ENTITY_FACING_DOWN)
    {
      e->tile = 39;
      e->orientation |= ENTITY_THETA_180;
    }
    else if (facing == ENTITY_FACING_DOWN_RIGHT)
    {
      e->tile = 47;
      e->orientation |= ENTITY_THETA_270;
    }
  }
  /* conveyers */
  else if (ENTITY_TYPE_IS_CONVEYER(e->type))
  {
    if (facing == ENTITY_FACING_RIGHT)
      e->orientation |= ENTITY_THETA_0;
    else if (facing == ENTITY_FACING_UP)
      e->orientation |= ENTITY_THETA_90;
    else if (facing == ENTITY_FACING_LEFT)
      e->orientation |= ENTITY_THETA_180;
    else if (facing == ENTITY_FACING_DOWN)
      e->orientation |= ENTITY_THETA_270;
  }
  /* enemies */
  else if (e->type == ENTITY_TYPE_GHOST)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      if (facing == ENTITY_FACING_RIGHT)
        e->tile = 61;
      else if (facing == ENTITY_FACING_UP)
        e->tile = 53;
      else if (facing == ENTITY_FACING_LEFT)
        e->tile = 57;
      else if (facing == ENTITY_FACING_DOWN)
        e->tile = 49;
    }
    else
    {
      if (facing == ENTITY_FACING_RIGHT)
        e->tile = 60;
      else if (facing == ENTITY_FACING_UP)
        e->tile = 52;
      else if (facing == ENTITY_FACING_LEFT)
        e->tile = 56;
      else if (facing == ENTITY_FACING_DOWN)
        e->tile = 48;
    }
  }
  else if (e->type == ENTITY_TYPE_SNAKE)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      if (facing == ENTITY_FACING_RIGHT)
        e->tile = 45;
      else if (facing == ENTITY_FACING_UP)
        e->tile = 37;
      else if (facing == ENTITY_FACING_LEFT)
        e->tile = 41;
      else if (facing == ENTITY_FACING_DOWN)
        e->tile = 33;
    }
    else
    {
      if (facing == ENTITY_FACING_RIGHT)
        e->tile = 44;
      else if (facing == ENTITY_FACING_UP)
        e->tile = 36;
      else if (facing == ENTITY_FACING_LEFT)
        e->tile = 40;
      else if (facing == ENTITY_FACING_DOWN)
        e->tile = 32;
    }
  }
  else if (e->type == ENTITY_TYPE_DOUBLE_VAMPIRE)
  {
    if (facing == ENTITY_FACING_RIGHT)
      e->tile = 8;
    else if (facing == ENTITY_FACING_UP)
      e->tile = 16;
    else if (facing == ENTITY_FACING_LEFT)
      e->tile = 24;
    else if (facing == ENTITY_FACING_DOWN)
      e->tile = 0;
  }
  else if (e->type == ENTITY_TYPE_DOUBLE_BAT)
  {
    if (facing == ENTITY_FACING_RIGHT)
      e->tile = 13;
    else if (facing == ENTITY_FACING_UP)
      e->tile = 21;
    else if (facing == ENTITY_FACING_LEFT)
      e->tile = 29;
    else if (facing == ENTITY_FACING_DOWN)
      e->tile = 5;
  }
  else if (e->type == ENTITY_TYPE_REVERSE_DOUBLE_VAMPIRE)
  {
    if (facing == ENTITY_FACING_RIGHT)
      e->tile = 8;
    else if (facing == ENTITY_FACING_UP)
      e->tile = 16;
    else if (facing == ENTITY_FACING_LEFT)
      e->tile = 24;
    else if (facing == ENTITY_FACING_DOWN)
      e->tile = 0;
  }
  else if (e->type == ENTITY_TYPE_REVERSE_DOUBLE_BAT)
  {
    if (facing == ENTITY_FACING_RIGHT)
      e->tile = 13;
    else if (facing == ENTITY_FACING_UP)
      e->tile = 21;
    else if (facing == ENTITY_FACING_LEFT)
      e->tile = 29;
    else if (facing == ENTITY_FACING_DOWN)
      e->tile = 5;
  }
  else if (e->type == ENTITY_TYPE_FAERIE_HORIZONTAL)
  {
    if (facing == ENTITY_FACING_UP)
      e->tile = 50;
    else if (facing == ENTITY_FACING_DOWN)
      e->tile = 54;
  }
  else if (e->type == ENTITY_TYPE_FAERIE_VERTICAL)
  {
    if (facing == ENTITY_FACING_RIGHT)
      e->tile = 48;
    else if (facing == ENTITY_FACING_LEFT)
      e->tile = 52;
  }
  else if (e->type == ENTITY_TYPE_WITCH)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      if (facing == ENTITY_FACING_RIGHT)
        e->tile = 37;
      else if (facing == ENTITY_FACING_UP)
        e->tile = 29;
      else if (facing == ENTITY_FACING_LEFT)
        e->tile = 33;
      else if (facing == ENTITY_FACING_DOWN)
        e->tile = 25;
    }
    else
    {
      if (facing == ENTITY_FACING_RIGHT)
        e->tile = 36;
      else if (facing == ENTITY_FACING_UP)
        e->tile = 28;
      else if (facing == ENTITY_FACING_LEFT)
        e->tile = 32;
      else if (facing == ENTITY_FACING_DOWN)
        e->tile = 24;
    }
  }
  else if (e->type == ENTITY_TYPE_UNDINE)
  {
    if (facing == ENTITY_FACING_RIGHT)
      e->tile = 0;
    else if (facing == ENTITY_FACING_UP)
      e->tile = 1;
    else if (facing == ENTITY_FACING_LEFT)
      e->tile = 2;
    else if (facing == ENTITY_FACING_DOWN)
      e->tile = 3;
  }
  else if (e->type == ENTITY_TYPE_SORCERESS)
  {
    if (facing == ENTITY_FACING_RIGHT)
      e->tile = 4;
    else if (facing == ENTITY_FACING_UP)
      e->tile = 5;
    else if (facing == ENTITY_FACING_LEFT)
      e->tile = 6;
    else if (facing == ENTITY_FACING_DOWN)
      e->tile = 7;
  }
  else if (e->type == ENTITY_TYPE_FROG)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      if (facing == ENTITY_FACING_RIGHT)
        e->tile = 36;
      else if (facing == ENTITY_FACING_UP)
        e->tile = 44;
      else if (facing == ENTITY_FACING_LEFT)
        e->tile = 52;
      else if (facing == ENTITY_FACING_DOWN)
        e->tile = 60;
    }
    else
    {
      if (facing == ENTITY_FACING_RIGHT)
        e->tile = 35;
      else if (facing == ENTITY_FACING_UP)
        e->tile = 43;
      else if (facing == ENTITY_FACING_LEFT)
        e->tile = 51;
      else if (facing == ENTITY_FACING_DOWN)
        e->tile = 59;
    }
  }
  else if (e->type == ENTITY_TYPE_IMP_LT)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      if (facing == ENTITY_FACING_RIGHT)
        e->tile = 0;
      else if (facing == ENTITY_FACING_UP)
        e->tile = 8;
      else if (facing == ENTITY_FACING_LEFT)
        e->tile = 16;
      else if (facing == ENTITY_FACING_DOWN)
        e->tile = 24;
    }
    else
    {
      if (facing == ENTITY_FACING_RIGHT)
        e->tile = 3;
      else if (facing == ENTITY_FACING_UP)
        e->tile = 11;
      else if (facing == ENTITY_FACING_LEFT)
        e->tile = 19;
      else if (facing == ENTITY_FACING_DOWN)
        e->tile = 27;
    }
  }
  else if (e->type == ENTITY_TYPE_IMP_RT)
  {
    if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      if (facing == ENTITY_FACING_RIGHT)
        e->tile = 4;
      else if (facing == ENTITY_FACING_UP)
        e->tile = 12;
      else if (facing == ENTITY_FACING_LEFT)
        e->tile = 20;
      else if (facing == ENTITY_FACING_DOWN)
        e->tile = 28;
    }
    else
    {
      if (facing == ENTITY_FACING_RIGHT)
        e->tile = 7;
      else if (facing == ENTITY_FACING_UP)
        e->tile = 15;
      else if (facing == ENTITY_FACING_LEFT)
        e->tile = 23;
      else if (facing == ENTITY_FACING_DOWN)
        e->tile = 31;
    }
  }
  else if (e->type == ENTITY_TYPE_LIL_BOT)
  {
    if (facing == ENTITY_FACING_RIGHT)
      e->tile = 32;
    else if (facing == ENTITY_FACING_UP)
      e->tile = 40;
    else if (facing == ENTITY_FACING_LEFT)
      e->tile = 48;
    else if (facing == ENTITY_FACING_DOWN)
      e->tile = 56;
  }
  else if (e->type == ENTITY_TYPE_POLTERGEIST)
  {
    if (facing == ENTITY_FACING_RIGHT)
      e->tile = 44;
    else if (facing == ENTITY_FACING_UP)
      e->tile = 36;
    else if (facing == ENTITY_FACING_LEFT)
      e->tile = 40;
    else if (facing == ENTITY_FACING_DOWN)
      e->tile = 32;
  }
  else if (e->type == ENTITY_TYPE_JIANGSHI_LT)
  {
    if (facing == ENTITY_FACING_RIGHT)
      e->tile = 32;
    else if (facing == ENTITY_FACING_UP)
      e->tile = 40;
    else if (facing == ENTITY_FACING_LEFT)
      e->tile = 48;
    else if (facing == ENTITY_FACING_DOWN)
      e->tile = 56;
  }
  else if (e->type == ENTITY_TYPE_JIANGSHI_RT)
  {
    if (facing == ENTITY_FACING_RIGHT)
      e->tile = 36;
    else if (facing == ENTITY_FACING_UP)
      e->tile = 44;
    else if (facing == ENTITY_FACING_LEFT)
      e->tile = 52;
    else if (facing == ENTITY_FACING_DOWN)
      e->tile = 60;
  }
  else if (e->type == ENTITY_TYPE_MUMMY_LT)
  {
    if (facing == ENTITY_FACING_RIGHT)
      e->tile = 0;
    else if (facing == ENTITY_FACING_UP)
      e->tile = 8;
    else if (facing == ENTITY_FACING_LEFT)
      e->tile = 16;
    else if (facing == ENTITY_FACING_DOWN)
      e->tile = 24;
  }
  else if (e->type == ENTITY_TYPE_MUMMY_RT)
  {
    if (facing == ENTITY_FACING_RIGHT)
      e->tile = 4;
    else if (facing == ENTITY_FACING_UP)
      e->tile = 12;
    else if (facing == ENTITY_FACING_LEFT)
      e->tile = 20;
    else if (facing == ENTITY_FACING_DOWN)
      e->tile = 28;
  }
  else if (e->type == ENTITY_TYPE_GUARDIAN_LT)
  {
    if (facing == ENTITY_FACING_RIGHT)
      e->tile = 44;
    else if (facing == ENTITY_FACING_UP)
      e->tile = 45;
    else if (facing == ENTITY_FACING_LEFT)
      e->tile = 46;
    else if (facing == ENTITY_FACING_DOWN)
      e->tile = 47;
  }
  else if (e->type == ENTITY_TYPE_GUARDIAN_RT)
  {
    if (facing == ENTITY_FACING_RIGHT)
      e->tile = 40;
    else if (facing == ENTITY_FACING_UP)
      e->tile = 41;
    else if (facing == ENTITY_FACING_LEFT)
      e->tile = 42;
    else if (facing == ENTITY_FACING_DOWN)
      e->tile = 43;
  }
  else if (e->type == ENTITY_TYPE_LASER_GUN)
  {
    if (facing == ENTITY_FACING_RIGHT)
    {
      e->tile = 48;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP_RIGHT)
    {
      e->tile = 52;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP)
    {
      e->tile = 48;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_UP_LEFT)
    {
      e->tile = 52;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_LEFT)
    {
      e->tile = 56;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_DOWN_LEFT)
    {
      e->tile = 60;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_DOWN)
    {
      e->tile = 56;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_DOWN_RIGHT)
    {
      e->tile = 60;
      e->orientation |= ENTITY_THETA_90;
    }
  }
  /* player */
  else if (e->type == ENTITY_TYPE_PLAYER_VAMPIRE)
  {
    if (facing == ENTITY_FACING_RIGHT)
      e->tile = 8;
    else if (facing == ENTITY_FACING_UP)
      e->tile = 16;
    else if (facing == ENTITY_FACING_LEFT)
      e->tile = 24;
    else if (facing == ENTITY_FACING_DOWN)
      e->tile = 0;
  }
  else if (e->type == ENTITY_TYPE_PLAYER_BAT)
  {
    if (facing == ENTITY_FACING_RIGHT)
      e->tile = 13;
    else if (facing == ENTITY_FACING_UP)
      e->tile = 21;
    else if (facing == ENTITY_FACING_LEFT)
      e->tile = 29;
    else if (facing == ENTITY_FACING_DOWN)
      e->tile = 5;
  }
  /* spells */
  else if (e->type == ENTITY_TYPE_FIRE_SPELL)
  {
    e->tile = 26;

    if (facing == ENTITY_FACING_RIGHT)
      e->orientation |= ENTITY_THETA_0;
    else if (facing == ENTITY_FACING_UP)
      e->orientation |= ENTITY_THETA_90;
    else if (facing == ENTITY_FACING_LEFT)
      e->orientation |= ENTITY_THETA_180;
    else if (facing == ENTITY_FACING_DOWN)
      e->orientation |= ENTITY_THETA_270;
  }
  else if (e->type == ENTITY_TYPE_ICE_SPELL)
  {
    if (facing == ENTITY_FACING_RIGHT)
    {
      e->tile = 32;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_UP)
    {
      e->tile = 32;
      e->orientation |= ENTITY_THETA_90;
    }
    else if (facing == ENTITY_FACING_LEFT)
    {
      e->tile = 36;
      e->orientation |= ENTITY_THETA_0;
    }
    else if (facing == ENTITY_FACING_DOWN)
    {
      e->tile = 36;
      e->orientation |= ENTITY_THETA_90;
    }
  }
  else if (e->type == ENTITY_TYPE_NEUTRAL_SPELL)
  {
    e->tile = 48;

    if (facing == ENTITY_FACING_RIGHT)
      e->orientation |= ENTITY_THETA_0;
    else if (facing == ENTITY_FACING_UP)
      e->orientation |= ENTITY_THETA_90;
    else if (facing == ENTITY_FACING_LEFT)
      e->orientation |= ENTITY_THETA_180;
    else if (facing == ENTITY_FACING_DOWN)
      e->orientation |= ENTITY_THETA_270;
  }
  else if (e->type == ENTITY_TYPE_BALLISTA_BOLT)
  {
    e->tile = 52;

    if (facing == ENTITY_FACING_RIGHT)
      e->orientation |= ENTITY_THETA_0;
    else if (facing == ENTITY_FACING_UP)
      e->orientation |= ENTITY_THETA_90;
    else if (facing == ENTITY_FACING_LEFT)
      e->orientation |= ENTITY_THETA_180;
    else if (facing == ENTITY_FACING_DOWN)
      e->orientation |= ENTITY_THETA_270;
  }
  else if (e->type == ENTITY_TYPE_LASER_SHOT)
  {
    e->tile = 54;

    if (facing == ENTITY_FACING_RIGHT)
      e->orientation |= ENTITY_THETA_0;
    else if (facing == ENTITY_FACING_UP)
      e->orientation |= ENTITY_THETA_90;
    else if (facing == ENTITY_FACING_LEFT)
      e->orientation |= ENTITY_THETA_0;
    else if (facing == ENTITY_FACING_DOWN)
      e->orientation |= ENTITY_THETA_90;
  }
  else if (e->type == ENTITY_TYPE_EVIL_EYE)
  {
    if (facing == ENTITY_FACING_RIGHT)
      e->tile = 44;
    else if (facing == ENTITY_FACING_UP)
      e->tile = 45;
    else if (facing == ENTITY_FACING_LEFT)
      e->tile = 46;
    else if (facing == ENTITY_FACING_DOWN)
      e->tile = 47;
  }

  return 0;
}
