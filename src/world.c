/*******************************************************************************
** world.c (entity and particle lists)
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "animate.h"
#include "entity.h"
#include "global.h"
#include "list.h"
#include "particle.h"
#include "world.h"

#define WORLD_UPDATE_PARTICLE_ARRAY_INDICES(num, max)                          \
  if ((G_particle_start_i > G_particle_end_i) &&                               \
      (G_particle_start_i < (G_particle_end_i + num)))                         \
  {                                                                            \
    G_particle_end_i = (G_particle_end_i + num) % max;                         \
    G_particle_start_i = (G_particle_end_i + 1) % max;                         \
  }                                                                            \
  else if ( (G_particle_end_i > ((G_particle_end_i + num) % max)) &&           \
            (G_particle_start_i < ((G_particle_end_i + num) % max)))           \
  {                                                                            \
    G_particle_end_i = (G_particle_end_i + num) % max;                         \
    G_particle_start_i = (G_particle_end_i + 1) % max;                         \
  }                                                                            \
  else if (G_particle_start_i == ((G_particle_end_i + num) % max))             \
  {                                                                            \
    G_particle_end_i = (G_particle_end_i + num) % max;                         \
    G_particle_start_i = (G_particle_end_i + 1) % max;                         \
  }                                                                            \
  else                                                                         \
  {                                                                            \
    G_particle_end_i = (G_particle_end_i + num) % max;                         \
  }

entity*     G_entity_active_list_head[CATEGORY_NUM_INDICES];
entity*     G_entity_active_list_tail[CATEGORY_NUM_INDICES];
entity*     G_entity_inactive_list_head;
entity*     G_entity_inactive_list_tail;

static int  S_world_num_entities;

particle    G_particle_array[WORLD_PARTICLES_MAX];
int         G_particle_start_i;
int         G_particle_end_i;

static int  S_world_firework_outer_vel_x[12] = 
              { (48 << PARTICLE_MANTISSA) / 60,
                (41 << PARTICLE_MANTISSA) / 60,
                (24 << PARTICLE_MANTISSA) / 60,
                (0 << PARTICLE_MANTISSA) / 60,
                -((24 << PARTICLE_MANTISSA) / 60),
                -((41 << PARTICLE_MANTISSA) / 60),
                -((48 << PARTICLE_MANTISSA) / 60),
                -((41 << PARTICLE_MANTISSA) / 60),
                -((24 << PARTICLE_MANTISSA) / 60),
                (0 << PARTICLE_MANTISSA) / 60,
                (24 << PARTICLE_MANTISSA) / 60,
                (41 << PARTICLE_MANTISSA) / 60};

static int  S_world_firework_outer_vel_y[12] = 
              { (0 << PARTICLE_MANTISSA) / 60,
                -((24 << PARTICLE_MANTISSA) / 60),
                -((41 << PARTICLE_MANTISSA) / 60),
                -((48 << PARTICLE_MANTISSA) / 60),
                -((41 << PARTICLE_MANTISSA) / 60),
                -((24 << PARTICLE_MANTISSA) / 60),
                (0 << PARTICLE_MANTISSA) / 60,
                (24 << PARTICLE_MANTISSA) / 60,
                (41 << PARTICLE_MANTISSA) / 60,
                (48 << PARTICLE_MANTISSA) / 60,
                (41 << PARTICLE_MANTISSA) / 60,
                (24 << PARTICLE_MANTISSA) / 60};

static int  S_world_firework_outer_acc_x[12] = 
              { -((48 << PARTICLE_MANTISSA) / 3600),
                -((41 << PARTICLE_MANTISSA) / 3600),
                -((24 << PARTICLE_MANTISSA) / 3600),
                (0 << PARTICLE_MANTISSA) / 3600,
                (24 << PARTICLE_MANTISSA) / 3600,
                (41 << PARTICLE_MANTISSA) / 3600,
                (48 << PARTICLE_MANTISSA) / 3600,
                (41 << PARTICLE_MANTISSA) / 3600,
                (24 << PARTICLE_MANTISSA) / 3600,
                (0 << PARTICLE_MANTISSA) / 3600,
                -((24 << PARTICLE_MANTISSA) / 3600),
                -((41 << PARTICLE_MANTISSA) / 3600)};

static int  S_world_firework_outer_acc_y[12] = 
              { (0 << PARTICLE_MANTISSA) / 3600,
                (24 << PARTICLE_MANTISSA) / 3600,
                (41 << PARTICLE_MANTISSA) / 3600,
                (48 << PARTICLE_MANTISSA) / 3600,
                (41 << PARTICLE_MANTISSA) / 3600,
                (24 << PARTICLE_MANTISSA) / 3600,
                (0 << PARTICLE_MANTISSA) / 3600,
                -((24 << PARTICLE_MANTISSA) / 3600),
                -((41 << PARTICLE_MANTISSA) / 3600),
                -((48 << PARTICLE_MANTISSA) / 3600),
                -((41 << PARTICLE_MANTISSA) / 3600),
                -((24 << PARTICLE_MANTISSA) / 3600)};

static int  S_world_firework_inner_vel_x[12] = 
              { (31 << PARTICLE_MANTISSA) / 60,
                (22 << PARTICLE_MANTISSA) / 60,
                (8 << PARTICLE_MANTISSA) / 60,
                -((8 << PARTICLE_MANTISSA) / 60),
                -((22 << PARTICLE_MANTISSA) / 60),
                -((31 << PARTICLE_MANTISSA) / 60),
                -((31 << PARTICLE_MANTISSA) / 60),
                -((22 << PARTICLE_MANTISSA) / 60),
                -((8 << PARTICLE_MANTISSA) / 60),
                (8 << PARTICLE_MANTISSA) / 60,
                (22 << PARTICLE_MANTISSA) / 60,
                (31 << PARTICLE_MANTISSA) / 60};

static int  S_world_firework_inner_vel_y[12] = 
              { -((8 << PARTICLE_MANTISSA) / 60),
                -((22 << PARTICLE_MANTISSA) / 60),
                -((31 << PARTICLE_MANTISSA) / 60),
                -((31 << PARTICLE_MANTISSA) / 60),
                -((22 << PARTICLE_MANTISSA) / 60),
                -((8 << PARTICLE_MANTISSA) / 60),
                (8 << PARTICLE_MANTISSA) / 60,
                (22 << PARTICLE_MANTISSA) / 60,
                (31 << PARTICLE_MANTISSA) / 60,
                (31 << PARTICLE_MANTISSA) / 60,
                (22 << PARTICLE_MANTISSA) / 60,
                (8 << PARTICLE_MANTISSA) / 60};

static int  S_world_firework_inner_acc_x[12] = 
              { -((31 << PARTICLE_MANTISSA) / 3600),
                -((22 << PARTICLE_MANTISSA) / 3600),
                -((8 << PARTICLE_MANTISSA) / 3600),
                (8 << PARTICLE_MANTISSA) / 3600,
                (22 << PARTICLE_MANTISSA) / 3600,
                (31 << PARTICLE_MANTISSA) / 3600,
                (31 << PARTICLE_MANTISSA) / 3600,
                (22 << PARTICLE_MANTISSA) / 3600,
                (8 << PARTICLE_MANTISSA) / 3600,
                -((8 << PARTICLE_MANTISSA) / 3600),
                -((22 << PARTICLE_MANTISSA) / 3600),
                -((31 << PARTICLE_MANTISSA) / 3600)};

static int  S_world_firework_inner_acc_y[12] = 
              { (8 << PARTICLE_MANTISSA) / 3600,
                (22 << PARTICLE_MANTISSA) / 3600,
                (31 << PARTICLE_MANTISSA) / 3600,
                (31 << PARTICLE_MANTISSA) / 3600,
                (22 << PARTICLE_MANTISSA) / 3600,
                (8 << PARTICLE_MANTISSA) / 3600,
                -((8 << PARTICLE_MANTISSA) / 3600),
                -((22 << PARTICLE_MANTISSA) / 3600),
                -((31 << PARTICLE_MANTISSA) / 3600),
                -((31 << PARTICLE_MANTISSA) / 3600),
                -((22 << PARTICLE_MANTISSA) / 3600),
                -((8 << PARTICLE_MANTISSA) / 3600)};

/*******************************************************************************
** world_init()
*******************************************************************************/
short int world_init()
{
  int     i;
  entity* new_e;

  /* initialize list pointers */
  for (i = 0; i < CATEGORY_NUM_INDICES; i++)
  {
    G_entity_active_list_head[i] = NULL;
    G_entity_active_list_tail[i] = NULL;
  }

  G_entity_inactive_list_head = NULL;
  G_entity_inactive_list_tail = NULL;

  /* create entities in inactive list */
  S_world_num_entities = 0;

  for (i = 0; i < WORLD_ENTITIES_INITIAL_NUM; i++)
  {
    new_e = entity_create();
    DLIST_ADD_TO_FRONT( G_entity_inactive_list_head, 
                        G_entity_inactive_list_tail, new_e)
    new_e->id = S_world_num_entities;
    S_world_num_entities += 1;
  }

  /* initialize particle array */
  for (i = 0; i < WORLD_PARTICLES_MAX; i++)
  {
    particle_init(&G_particle_array[i]);
  }

  G_particle_start_i = 0;
  G_particle_end_i = 0;

  /* initialize global variables */
  G_player = NULL;
  G_vials_remaining = 0;
  G_bat_transforms = 0;
  G_blue_mana = 0;
  G_green_mana = 0;
  G_theme = THEME_FOYER;

  return 0;
}

/*******************************************************************************
** world_deinit()
*******************************************************************************/
short int world_deinit()
{
  int     i;
  entity* current_e;

  /* destroy all lists */
  for (i = 0; i < CATEGORY_NUM_INDICES; i++)
  {
    SLIST_DESTROY(entity, G_entity_active_list_head[i], current_e)
  }

  SLIST_DESTROY(entity, G_entity_inactive_list_head, current_e)

  S_world_num_entities = 0;

  /* deinitialize particle array */
  for (i = 0; i < WORLD_PARTICLES_MAX; i++)
  {
    particle_deinit(&G_particle_array[i]);
  }

  G_particle_start_i = 0;
  G_particle_end_i = 0;

  /* reset global variables */
  G_player = NULL;
  G_vials_remaining = 0;
  G_bat_transforms = 0;
  G_blue_mana = 0;
  G_green_mana = 0;
  G_theme = THEME_FOYER;

  return 0;
}

/*******************************************************************************
** world_spawn_particles_trailing()
*******************************************************************************/
short int world_spawn_particles_trailing(entity* e)
{
  int           i;
  particle*     p;

  int           pos_x[2];
  int           pos_y[2];
  unsigned char r;
  unsigned char g;
  unsigned char b;
  int           trail_padding;

  if (e == NULL)
    return 0;

  /* set particle color and trail padding based on spell type */
  if (e->type == ENTITY_TYPE_FIRE_SPELL)
  {
    r = 3;
    g = 1;
    b = 1;
    trail_padding = 0;
  }
  else if (e->type == ENTITY_TYPE_ICE_SPELL)
  {
    r = 1;
    g = 3;
    b = 3;
    trail_padding = 4;
  }
  else if (e->type == ENTITY_TYPE_NEUTRAL_SPELL)
  {
    r = 3;
    g = 1;
    b = 3;
    trail_padding = 4;
  }
  else if (e->type == ENTITY_TYPE_WARP_SPELL)
  {
    r = 1;
    g = 3;
    b = 1;
    trail_padding = 0;
  }
  else if (e->type == ENTITY_TYPE_BALLISTA_BOLT)
  {
    r = 2;
    g = 2;
    b = 2;
    trail_padding = 4;
  }
  else if (e->type == ENTITY_TYPE_LASER_SHOT)
  {
    r = 3;
    g = 1;
    b = 3;
    trail_padding = 4;
  }
  else
    return 0;

  /* determine iniitial particle positions */
  if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
  {
    pos_x[0] = e->pos_x - 16 - trail_padding;
    pos_y[0] = e->pos_y - (3 * (((e->pos_x / 8) % 2) + 1));
    pos_x[1] = e->pos_x - 16 - trail_padding;
    pos_y[1] = e->pos_y + (3 * (((e->pos_x / 8) % 2) + 1));
  }
  else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
  {
    pos_x[0] = e->pos_x - (3 * (((e->pos_y / 8) % 2) + 1));
    pos_y[0] = e->pos_y + 16 + trail_padding;
    pos_x[1] = e->pos_x + (3 * (((e->pos_y / 8) % 2) + 1));
    pos_y[1] = e->pos_y + 16 + trail_padding;
  }
  else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
  {
    pos_x[0] = e->pos_x + 16 + trail_padding;
    pos_y[0] = e->pos_y - (3 * (((e->pos_x / 8) % 2) + 1));
    pos_x[1] = e->pos_x + 16 + trail_padding;
    pos_y[1] = e->pos_y + (3 * (((e->pos_x / 8) % 2) + 1));
  }
  else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
  {
    pos_x[0] = e->pos_x - (3 * (((e->pos_y / 8) % 2) + 1));
    pos_y[0] = e->pos_y - 16 - trail_padding;
    pos_x[1] = e->pos_x + (3 * (((e->pos_y / 8) % 2) + 1));
    pos_y[1] = e->pos_y - 16 - trail_padding;
  }
  else
    return 0;

  /* add particles to particle array */
  for (i = 0; i < 2; i++)
  {
    p = &G_particle_array[(G_particle_end_i + i) % WORLD_PARTICLES_MAX];

    p->pos_x = pos_x[i] << PARTICLE_MANTISSA;
    p->pos_y = pos_y[i] << PARTICLE_MANTISSA;

    p->vel_x = 0;
    p->vel_y = 0;

    p->acc_x = 0;
    p->acc_y = 0;

    if (e->orientation & ENTITY_SPEED_FLAG)
      p->life_count = 12;
    else
      p->life_count = 24;

    p->color_r = r;
    p->color_g = g;
    p->color_b = b;
  }

  /* update start and end indices */
  WORLD_UPDATE_PARTICLE_ARRAY_INDICES(2, WORLD_PARTICLES_MAX)

  return 0;
}

/*******************************************************************************
** world_spawn_particles_warp_effect()
*******************************************************************************/
short int world_spawn_particles_warp_effect(entity* e1, entity* e2)
{
  int           i;
  particle*     p;

  int           vel_x[12];
  int           vel_y[12];
  unsigned char r[2];
  unsigned char g[2];
  unsigned char b[2];

  if ((e1 == NULL) || (e2 == NULL))
    return 0;

  /* set colors for each stream */
  r[0] = 3;
  g[0] = 3;
  b[0] = 3;

  r[1] = 1;
  g[1] = 3;
  b[1] = 1;

  /* compute velocities for each particle */
  if (e1->pos_x > e2->pos_x)
  {
    vel_x[0] = ((e1->pos_x - e2->pos_x) << PARTICLE_MANTISSA) / 48;
    vel_x[6] = -vel_x[0];
  }
  else
  {
    vel_x[6] = ((e2->pos_x - e1->pos_x) << PARTICLE_MANTISSA) / 48;
    vel_x[0] = -vel_x[6];
  }

  if (e1->pos_y > e2->pos_y)
  {
    vel_y[0] = ((e1->pos_y - e2->pos_y) << PARTICLE_MANTISSA) / 48;
    vel_y[6] = -vel_y[0];
  }
  else
  {
    vel_y[6] = ((e2->pos_y - e1->pos_y) << PARTICLE_MANTISSA) / 48;
    vel_y[0] = -vel_y[6];
  }

  vel_x[1] = vel_x[0] / 2;
  vel_y[1] = vel_y[0] / 2;

  vel_x[2] = vel_x[0] / 3;
  vel_y[2] = vel_y[0] / 3;

  vel_x[3] = vel_x[0] / 4;
  vel_y[3] = vel_y[0] / 4;

  vel_x[4] = vel_x[0] / 5;
  vel_y[4] = vel_y[0] / 5;

  vel_x[5] = vel_x[0] / 6;
  vel_y[5] = vel_y[0] / 6;

  vel_x[7] = vel_x[6] / 2;
  vel_y[7] = vel_y[6] / 2;

  vel_x[8] = vel_x[6] / 3;
  vel_y[8] = vel_y[6] / 3;

  vel_x[9] = vel_x[6] / 4;
  vel_y[9] = vel_y[6] / 4;

  vel_x[10] = vel_x[6] / 5;
  vel_y[10] = vel_y[6] / 5;

  vel_x[11] = vel_x[6] / 6;
  vel_y[11] = vel_y[6] / 6;

  /* add particles to particle array */
  for (i = 0; i < 12; i++)
  {
    p = &G_particle_array[(G_particle_end_i + i) % WORLD_PARTICLES_MAX];

    if (i < 6)
    {
      p->pos_x = e2->pos_x << PARTICLE_MANTISSA;
      p->pos_y = e2->pos_y << PARTICLE_MANTISSA;

      p->color_r = r[0];
      p->color_g = g[0];
      p->color_b = b[0];
    }
    else
    {
      p->pos_x = e1->pos_x << PARTICLE_MANTISSA;
      p->pos_y = e1->pos_y << PARTICLE_MANTISSA;

      p->color_r = r[1];
      p->color_g = g[1];
      p->color_b = b[1];
    }

    p->vel_x = vel_x[i];
    p->vel_y = vel_y[i];

    p->acc_x = 0;
    p->acc_y = 0;

    p->life_count = 48;
  }

  /* update start and end indices */
  WORLD_UPDATE_PARTICLE_ARRAY_INDICES(12, WORLD_PARTICLES_MAX)

  return 0;
}

/*******************************************************************************
** world_spawn_particles_firework()
*******************************************************************************/
short int world_spawn_particles_firework(entity* e)
{
  int           i;
  particle*     p;

  unsigned char r[3];
  unsigned char g[3];
  unsigned char b[3];

  if (e == NULL)
    return 0;

  /* determine particle colors */
  if (ENTITY_TYPE_HAS_RED_FIREWORK(e->type))
  {
    r[0] = 3;
    g[0] = 3;
    b[0] = 3;

    r[1] = 3;
    g[1] = 1;
    b[1] = 1;

    r[2] = 2;
    g[2] = 0;
    b[2] = 0;
  }
  else if (ENTITY_TYPE_HAS_CYAN_FIREWORK(e->type))
  {
    r[0] = 3;
    g[0] = 3;
    b[0] = 3;

    r[1] = 1;
    g[1] = 3;
    b[1] = 3;

    r[2] = 0;
    g[2] = 2;
    b[2] = 2;
  }
  else if (ENTITY_TYPE_HAS_GREEN_FIREWORK(e->type))
  {
    r[0] = 3;
    g[0] = 3;
    b[0] = 3;

    r[1] = 1;
    g[1] = 3;
    b[1] = 1;

    r[2] = 0;
    g[2] = 2;
    b[2] = 0;
  }
  else if (ENTITY_TYPE_HAS_MAGENTA_FIREWORK(e->type))
  {
    r[0] = 3;
    g[0] = 3;
    b[0] = 3;

    r[1] = 3;
    g[1] = 1;
    b[1] = 3;

    r[2] = 2;
    g[2] = 0;
    b[2] = 2;
  }
  else if (ENTITY_TYPE_HAS_BROWN_FIREWORK(e->type))
  {
    r[0] = 3;
    g[0] = 3;
    b[0] = 3;

    r[1] = 3;
    g[1] = 2;
    b[1] = 1;

    r[2] = 2;
    g[2] = 1;
    b[2] = 0;
  }
  else if (ENTITY_TYPE_HAS_GRAY_FIREWORK(e->type))
  {
    r[0] = 3;
    g[0] = 3;
    b[0] = 3;

    r[1] = 2;
    g[1] = 2;
    b[1] = 2;

    r[2] = 1;
    g[2] = 1;
    b[2] = 1;
  }
  else if (ENTITY_TYPE_HAS_BLACK_FIREWORK(e->type))
  {
    r[0] = 2;
    g[0] = 2;
    b[0] = 2;

    r[1] = 1;
    g[1] = 1;
    b[1] = 1;

    r[2] = 0;
    g[2] = 0;
    b[2] = 0;
  }
  else if (ENTITY_TYPE_HAS_YELLOW_FIREWORK(e->type))
  {
    r[0] = 3;
    g[0] = 3;
    b[0] = 3;

    r[1] = 3;
    g[1] = 3;
    b[1] = 1;

    r[2] = 3;
    g[2] = 2;
    b[2] = 0;
  }
  else if (ENTITY_TYPE_HAS_ORANGE_FIREWORK(e->type))
  {
    r[0] = 3;
    g[0] = 3;
    b[0] = 3;

    r[1] = 3;
    g[1] = 1;
    b[1] = 0;

    r[2] = 2;
    g[2] = 1;
    b[2] = 0;
  }
  else if (ENTITY_TYPE_HAS_PLAYER_FIREWORK(e->type))
  {
    r[0] = 3;
    g[0] = 3;
    b[0] = 3;

    r[1] = 2;
    g[1] = 2;
    b[1] = 2;

    r[2] = 3;
    g[2] = 1;
    b[2] = 3;
  }
  else if (ENTITY_TYPE_HAS_DOUBLE_FIREWORK(e->type))
  {
    r[0] = 2;
    g[0] = 2;
    b[0] = 2;

    r[1] = 1;
    g[1] = 1;
    b[1] = 1;

    r[2] = 3;
    g[2] = 2;
    b[2] = 3;
  }
  else if (ENTITY_TYPE_HAS_REVERSE_DOUBLE_FIREWORK(e->type))
  {
    r[0] = 3;
    g[0] = 2;
    b[0] = 3;

    r[1] = 3;
    g[1] = 0;
    b[1] = 2;

    r[2] = 1;
    g[2] = 1;
    b[2] = 1;
  }
  else
    return 0;

  /* add particles to particle array */
  for (i = 0; i < 24; i++)
  {
    p = &G_particle_array[(G_particle_end_i + i) % WORLD_PARTICLES_MAX];

    if (i < 12)
    {
      if ((i % 2) == 0)
      {
        p->color_r = r[0];
        p->color_g = g[0];
        p->color_b = b[0];
      }
      else
      {
        p->color_r = r[1];
        p->color_g = g[1];
        p->color_b = b[1];
      }

      p->vel_x = S_world_firework_outer_vel_x[i];
      p->vel_y = S_world_firework_outer_vel_y[i];

      p->acc_x = S_world_firework_outer_acc_x[i];
      p->acc_y = S_world_firework_outer_acc_y[i];
    }
    else
    {
      if ((i % 2) == 0)
      {
        p->color_r = r[1];
        p->color_g = g[1];
        p->color_b = b[1];
      }
      else
      {
        p->color_r = r[2];
        p->color_g = g[2];
        p->color_b = b[2];
      }

      p->vel_x = S_world_firework_inner_vel_x[i % 12];
      p->vel_y = S_world_firework_inner_vel_y[i % 12];

      p->acc_x = S_world_firework_inner_acc_x[i % 12];
      p->acc_y = S_world_firework_inner_acc_y[i % 12];
    }

    p->pos_x = e->pos_x << PARTICLE_MANTISSA;
    p->pos_y = e->pos_y << PARTICLE_MANTISSA;

    p->life_count = 48;
  }

  /* update start and end indices */
  WORLD_UPDATE_PARTICLE_ARRAY_INDICES(24, WORLD_PARTICLES_MAX)

  return 0;
}

/*******************************************************************************
** world_spawn_particles_water_splash()
*******************************************************************************/
short int world_spawn_particles_water_splash(entity* e)
{
  int           i;
  particle*     p;

  unsigned char r[2];
  unsigned char g[2];
  unsigned char b[2];

  if (e == NULL)
    return 0;

  /* set particle colors */
  r[0] = 1;
  g[0] = 3;
  b[0] = 3;

  r[1] = 0;
  g[1] = 2;
  b[1] = 2;

  /* add particles to particle array */
  for (i = 0; i < 11; i++)
  {
    p = &G_particle_array[(G_particle_end_i + i) % WORLD_PARTICLES_MAX];

    if (i < 5)
    {
      p->color_r = r[0];
      p->color_g = g[0];
      p->color_b = b[0];

      p->vel_x = S_world_firework_outer_vel_x[i + 1];
      p->vel_y = S_world_firework_outer_vel_y[i + 1];

      p->acc_x = S_world_firework_outer_acc_x[i + 1];
      p->acc_y = S_world_firework_outer_acc_y[i + 1];
      p->acc_y += (24 << PARTICLE_MANTISSA) / 3600;
    }
    else
    {
      p->color_r = r[1];
      p->color_g = g[1];
      p->color_b = b[1];

      p->vel_x = S_world_firework_inner_vel_x[i - 5];
      p->vel_y = S_world_firework_inner_vel_y[i - 5];

      p->acc_x = S_world_firework_inner_acc_x[i - 5];
      p->acc_y = S_world_firework_inner_acc_y[i - 5];
      p->acc_y += (16 << PARTICLE_MANTISSA) / 3600;
    }

    p->pos_x = e->pos_x << PARTICLE_MANTISSA;
    p->pos_y = e->pos_y << PARTICLE_MANTISSA;

    p->life_count = 48;
  }

  /* update start and end indices */
  WORLD_UPDATE_PARTICLE_ARRAY_INDICES(11, WORLD_PARTICLES_MAX)

  return 0;
}

/*******************************************************************************
** world_spawn_particles_transform()
*******************************************************************************/
short int world_spawn_particles_transform(entity* e)
{
  int           i;
  particle*     p;

  unsigned char r[2];
  unsigned char g[2];
  unsigned char b[2];

  if (e == NULL)
    return 0;

  /* set particle colors */
  if (ENTITY_TYPE_HAS_PLAYER_FIREWORK(e->type))
  {
    r[0] = 3;
    g[0] = 3;
    b[0] = 3;

    r[1] = 3;
    g[1] = 1;
    b[1] = 3;
  }
  else if (ENTITY_TYPE_HAS_DOUBLE_FIREWORK(e->type))
  {
    r[0] = 3;
    g[0] = 3;
    b[0] = 3;

    r[1] = 3;
    g[1] = 2;
    b[1] = 3;
  }
  else if (ENTITY_TYPE_HAS_REVERSE_DOUBLE_FIREWORK(e->type))
  {
    r[0] = 3;
    g[0] = 2;
    b[0] = 3;

    r[1] = 3;
    g[1] = 3;
    b[1] = 3;
  }
  else if (ENTITY_TYPE_HAS_GREEN_FIREWORK(e->type))
  {
    r[0] = 1;
    g[0] = 3;
    b[0] = 1;

    r[1] = 0;
    g[1] = 2;
    b[1] = 0;
  }
  else
    return 0;

  /* add particles to particle array */
  for (i = 0; i < 12; i++)
  {
    p = &G_particle_array[(G_particle_end_i + i) % WORLD_PARTICLES_MAX];

    if ((i % 2) == 0)
    {
      p->color_r = r[0];
      p->color_g = g[0];
      p->color_b = b[0];
    }
    else
    {
      p->color_r = r[1];
      p->color_g = g[1];
      p->color_b = b[1];
    }

    p->vel_x = S_world_firework_outer_vel_x[i];
    p->vel_y = S_world_firework_outer_vel_y[i];

    p->acc_x = S_world_firework_outer_acc_x[i];
    p->acc_y = S_world_firework_outer_acc_y[i];

    p->pos_x = e->pos_x << PARTICLE_MANTISSA;
    p->pos_y = e->pos_y << PARTICLE_MANTISSA;

    p->life_count = 48;
  }

  /* update start and end indices */
  WORLD_UPDATE_PARTICLE_ARRAY_INDICES(12, WORLD_PARTICLES_MAX)

  return 0;
}

/*******************************************************************************
** world_spawn_particles_floor_spike()
*******************************************************************************/
short int world_spawn_particles_floor_spike(entity* e)
{
  int           i;
  particle*     p;

  int           outer_indices[3] = {1, 3, 5};
  int           inner_indices[4] = {0, 2, 3, 5};

  unsigned char r[2];
  unsigned char g[2];
  unsigned char b[2];

  if (e == NULL)
    return 0;

  /* set particle colors */
  r[0] = 3;
  g[0] = 3;
  b[0] = 3;

  r[1] = 2;
  g[1] = 2;
  b[1] = 2;

  /* add particles to particle array */
  for (i = 0; i < 7; i++)
  {
    p = &G_particle_array[(G_particle_end_i + i) % WORLD_PARTICLES_MAX];

    if (i < 3)
    {
      p->color_r = r[0];
      p->color_g = g[0];
      p->color_b = b[0];

      p->vel_x = S_world_firework_outer_vel_x[outer_indices[i]];
      p->vel_y = S_world_firework_outer_vel_y[outer_indices[i]];

      p->acc_x = S_world_firework_outer_acc_x[outer_indices[i]];
      p->acc_y = S_world_firework_outer_acc_y[outer_indices[i]];
      p->acc_y += (24 << PARTICLE_MANTISSA) / 3600;
    }
    else
    {
      p->color_r = r[1];
      p->color_g = g[1];
      p->color_b = b[1];

      p->vel_x = S_world_firework_inner_vel_x[inner_indices[i - 3]];
      p->vel_y = S_world_firework_inner_vel_y[inner_indices[i - 3]];

      p->acc_x = S_world_firework_inner_acc_x[inner_indices[i - 3]];
      p->acc_y = S_world_firework_inner_acc_y[inner_indices[i - 3]];
      p->acc_y += (16 << PARTICLE_MANTISSA) / 3600;
    }

    p->pos_x = e->pos_x << PARTICLE_MANTISSA;
    p->pos_y = e->pos_y << PARTICLE_MANTISSA;

    p->life_count = 48;
  }

  /* update start and end indices */
  WORLD_UPDATE_PARTICLE_ARRAY_INDICES(7, WORLD_PARTICLES_MAX)

  return 0;
}

/*******************************************************************************
** world_spawn_entity()
*******************************************************************************/
entity* world_spawn_entity(int type, int pos_x, int pos_y)
{
  int     i;
  int     category;
  entity* new_e;

  /* determine category based on type */
  if ((type == ENTITY_TYPE_OUTER_WALL_RIGHT)        ||
      (type == ENTITY_TYPE_OUTER_WALL_LEFT)         ||
      (type == ENTITY_TYPE_OUTER_WALL_BOTTOM_LEFT)  ||
      (type == ENTITY_TYPE_OUTER_WALL_BOTTOM)       ||
      (type == ENTITY_TYPE_OUTER_WALL_BOTTOM_RIGHT) ||
      (type == ENTITY_TYPE_INNER_WALL_TOP))
  {
    category = CATEGORY_INDEX_WALLS;
  }
  else if ( (type == ENTITY_TYPE_PORTCULLIS_CLOSED) ||
            (type == ENTITY_TYPE_PORTCULLIS_OPEN))
  {
    category = CATEGORY_INDEX_PORTCULLIS;
  }
  else if ( (type == ENTITY_TYPE_OUTER_WALL_TOP_LEFT)     ||
            (type == ENTITY_TYPE_OUTER_WALL_TOP)          ||
            (type == ENTITY_TYPE_OUTER_WALL_TOP_RIGHT)    ||
            (type == ENTITY_TYPE_INNER_WALL_BOTTOM)       ||
            (type == ENTITY_TYPE_FLOOR))
  {
    category = CATEGORY_INDEX_BACKGROUND;
  }
  else if ( (type == ENTITY_TYPE_FLOOR_BORDER_TOP_LEFT)       ||
            (type == ENTITY_TYPE_FLOOR_BORDER_TOP)            ||
            (type == ENTITY_TYPE_FLOOR_BORDER_TOP_RIGHT)      ||
            (type == ENTITY_TYPE_FLOOR_BORDER_LEFT)           ||
            (type == ENTITY_TYPE_FLOOR_BORDER_RIGHT)          ||
            (type == ENTITY_TYPE_FLOOR_BORDER_BOTTOM_LEFT)    ||
            (type == ENTITY_TYPE_FLOOR_BORDER_BOTTOM)         ||
            (type == ENTITY_TYPE_FLOOR_BORDER_BOTTOM_RIGHT))
  {
    category = CATEGORY_INDEX_FLOOR_BORDERS;
  }
  else if (type == ENTITY_TYPE_WATER)
  {
    category = CATEGORY_INDEX_WATER;
  }
  else if ( (type == ENTITY_TYPE_GRASS)     ||
            (type == ENTITY_TYPE_ICE))
  {
    category = CATEGORY_INDEX_GRASS_ICE;
  }
  else if ( (type == ENTITY_TYPE_GRASS_BORDER_TOP_LEFT)     ||
            (type == ENTITY_TYPE_GRASS_BORDER_TOP)          ||
            (type == ENTITY_TYPE_GRASS_BORDER_TOP_RIGHT)    ||
            (type == ENTITY_TYPE_GRASS_BORDER_LEFT)         ||
            (type == ENTITY_TYPE_GRASS_BORDER_RIGHT)        ||
            (type == ENTITY_TYPE_GRASS_BORDER_BOTTOM_LEFT)  ||
            (type == ENTITY_TYPE_GRASS_BORDER_BOTTOM)       ||
            (type == ENTITY_TYPE_GRASS_BORDER_BOTTOM_RIGHT))
  {
    category = CATEGORY_INDEX_GRASS_BORDERS;
  }
  else if ( (type == ENTITY_TYPE_ICE_BORDER_TOP_LEFT)       ||
            (type == ENTITY_TYPE_ICE_BORDER_TOP)            ||
            (type == ENTITY_TYPE_ICE_BORDER_TOP_RIGHT)      ||
            (type == ENTITY_TYPE_ICE_BORDER_LEFT)           ||
            (type == ENTITY_TYPE_ICE_BORDER_RIGHT)          ||
            (type == ENTITY_TYPE_ICE_BORDER_BOTTOM_LEFT)    ||
            (type == ENTITY_TYPE_ICE_BORDER_BOTTOM)         ||
            (type == ENTITY_TYPE_ICE_BORDER_BOTTOM_RIGHT))
  {
    category = CATEGORY_INDEX_ICE_BORDERS;
  }
  else if ( (type == ENTITY_TYPE_BLOCK)   ||
            (type == ENTITY_TYPE_PILLAR)  ||
            (type == ENTITY_TYPE_TREE))
  {
    category = CATEGORY_INDEX_OBSTACLES;
  }
  else if ( (type == ENTITY_TYPE_COBWEB)          ||
            (type == ENTITY_TYPE_JOKER_CARD)      ||
            (type == ENTITY_TYPE_SEAL_OF_SOLOMON) ||
            (type == ENTITY_TYPE_YIN_YANG))
  {
    category = CATEGORY_INDEX_SYMBOLS;
  }
  else if ( ENTITY_TYPE_IS_BRIDGE(type)                   ||
            ENTITY_TYPE_IS_SUBMERGED(type)                ||
            ENTITY_TYPE_IS_VANISHED_DIE_SUBMERGED(type))
  {
    category = CATEGORY_INDEX_BRIDGES_SUBMERGED;
  }
  else if ( ENTITY_TYPE_IS_PUSHABLE_OBJECT(type)  ||
            ENTITY_TYPE_IS_ICE_CUBE(type))
  {
    category = CATEGORY_INDEX_PUSHABLE_OBJECTS;
  }
  else if (ENTITY_TYPE_IS_VANISHED_DIE(type))
  {
    category = CATEGORY_INDEX_VANISHED_DICE;
  }
  else if (ENTITY_TYPE_IS_ARROWS(type))
  {
    category = CATEGORY_INDEX_ARROWS;
  }
  else if (ENTITY_TYPE_IS_BALLISTA(type))
  {
    category = CATEGORY_INDEX_BALLISTAS;
  }
  else if (ENTITY_TYPE_IS_PINBALL_KICKER(type))
  {
    category = CATEGORY_INDEX_PINBALL_KICKERS;
  }
  else if ( ENTITY_TYPE_IS_FLOOR_SPIKE_DOWN(type) ||
            ENTITY_TYPE_IS_FLOOR_SPIKE_UP(type))
  {
    category = CATEGORY_INDEX_FLOOR_SPIKES;
  }
  else if (ENTITY_TYPE_IS_CONVEYER(type))
  {
    category = CATEGORY_INDEX_CONVEYERS;
  }
  else if (ENTITY_TYPE_IS_LEVER(type))
  {
    category = CATEGORY_INDEX_LEVERS;
  }
  else if ( ENTITY_TYPE_IS_SPIN_SWITCH(type)    ||
            ENTITY_TYPE_IS_NUMBER_SWITCH(type))
  {
    category = CATEGORY_INDEX_SWITCHES;
  }
  else if ( (type == ENTITY_TYPE_PUMPKIN)         ||
            (type == ENTITY_TYPE_GHOST)           ||
            (type == ENTITY_TYPE_MASK_HORIZONTAL) ||
            (type == ENTITY_TYPE_MASK_VERTICAL))
  {
    category = CATEGORY_INDEX_PUMPKINS_GHOSTS_MASKS;
  }
  else if ( (type == ENTITY_TYPE_DOUBLE_VAMPIRE)  ||
            (type == ENTITY_TYPE_DOUBLE_BAT))
  {
    category = CATEGORY_INDEX_DOUBLES;
  }
  else if ( (type == ENTITY_TYPE_SNAKE)               ||
            (type == ENTITY_TYPE_FAERIE_HORIZONTAL)   ||
            (type == ENTITY_TYPE_FAERIE_VERTICAL)     ||
            (type == ENTITY_TYPE_VENUSIAN))
  {
    category = CATEGORY_INDEX_SNAKES_FAERIES_VENUSIANS;
  }
  else if (type == ENTITY_TYPE_VENUSIAN_ROOT)
  {
    category = CATEGORY_INDEX_VENUSIAN_ROOTS;
  }
  else if ( (type == ENTITY_TYPE_REVERSE_DOUBLE_VAMPIRE)  ||
            (type == ENTITY_TYPE_REVERSE_DOUBLE_BAT))
  {
    category = CATEGORY_INDEX_REVERSE_DOUBLES;
  }
  else if ( (type == ENTITY_TYPE_FROG)            ||
            (type == ENTITY_TYPE_LIL_BOT)         ||
            (type == ENTITY_TYPE_WISP_LEFT_WALL)  ||
            (type == ENTITY_TYPE_WISP_RIGHT_WALL))
  {
    category = CATEGORY_INDEX_LIL_BOTS_WISPS_FROGS;
  }
  else if ( (type == ENTITY_TYPE_IMP_LT)        ||
            (type == ENTITY_TYPE_IMP_RT)        ||
            (type == ENTITY_TYPE_JIANGSHI_LT)   ||
            (type == ENTITY_TYPE_JIANGSHI_RT))
  {
    category = CATEGORY_INDEX_IMPS_JIANGSHIS;
  }
  else if ( (type == ENTITY_TYPE_WITCH)         ||
            (type == ENTITY_TYPE_UNDINE)        ||
            (type == ENTITY_TYPE_SORCERESS))
  {
    category = CATEGORY_INDEX_UNDINES_SORCERESSES_WITCHES;
  }
  else if ( (type == ENTITY_TYPE_GUARDIAN_LT)   ||
            (type == ENTITY_TYPE_GUARDIAN_RT))
  {
    category = CATEGORY_INDEX_GUARDIANS;
  }
  else if ( (type == ENTITY_TYPE_MUMMY_LT)  ||
            (type == ENTITY_TYPE_MUMMY_RT)  ||
            (type == ENTITY_TYPE_POLTERGEIST))
  {
    category = CATEGORY_INDEX_MUMMIES_POLTERGEISTS;
  }
  else if (type == ENTITY_TYPE_LASER_GUN)
  {
    category = CATEGORY_INDEX_LASER_GUNS;
  }
  else if (ENTITY_TYPE_IS_PICKUP(type))
  {
    category = CATEGORY_INDEX_PICKUPS;
  }
  else if ( (type == ENTITY_TYPE_PLAYER_VAMPIRE)    ||
            (type == ENTITY_TYPE_PLAYER_BAT))
  {
    category = CATEGORY_INDEX_PLAYER;
  }
  else if ( (type == ENTITY_TYPE_FIRE_SPELL)    ||
            (type == ENTITY_TYPE_ICE_SPELL)     ||
            (type == ENTITY_TYPE_NEUTRAL_SPELL) ||
            (type == ENTITY_TYPE_WARP_SPELL)    ||
            (type == ENTITY_TYPE_BALLISTA_BOLT) ||
            (type == ENTITY_TYPE_LASER_SHOT))
  {
    category = CATEGORY_INDEX_SPELLS;
  }
  else if (type == ENTITY_TYPE_EVIL_EYE)
  {
    category = CATEGORY_INDEX_EVIL_EYES;
  }
  else if (type == ENTITY_TYPE_EXPLOSION)
  {
    category = CATEGORY_INDEX_EXPLOSIONS;
  }
  else
  {
    return NULL;
  }

  /* create more entities if necessary */
  if (G_entity_inactive_list_head == NULL)
  {
    for (i = 0; i < WORLD_ENTITIES_RESIZE_NUM; i++)
    {
      new_e = entity_create();
      DLIST_ADD_TO_FRONT( G_entity_inactive_list_head,
                          G_entity_inactive_list_tail, new_e)
      new_e->id = S_world_num_entities;
      S_world_num_entities += 1;
    }
  }

  /* take first element off of inactive list as new element */
  if (G_entity_inactive_list_head == G_entity_inactive_list_tail)
  {
    new_e = G_entity_inactive_list_head;
    G_entity_inactive_list_head = NULL;
    G_entity_inactive_list_tail = NULL;
  }
  else
  {
    new_e = G_entity_inactive_list_head;
    G_entity_inactive_list_head = new_e->next;
  }

  /* add new element to the active list */
  if (G_entity_active_list_head[category] == NULL)
  {
    G_entity_active_list_head[category] = new_e;
    G_entity_active_list_tail[category] = new_e;
    new_e->next = NULL;
    new_e->prev = NULL;
  }
  else
  {
    new_e->next = G_entity_active_list_head[category];
    new_e->prev = NULL;
    G_entity_active_list_head[category]->prev = new_e;
    G_entity_active_list_head[category] = new_e;
  }

  /* initialize new entity */
  entity_reset(new_e);
  entity_set_type(new_e, type);
  new_e->pos_x = pos_x;
  new_e->pos_y = pos_y;
  animation_setup(new_e);

  return new_e;
}

/*******************************************************************************
** world_despawn_entity()
*******************************************************************************/
short int world_despawn_entity(entity* e)
{
  int index;

  if (e == NULL)
    return 1;

  /* if this entity is the head of a list, we need to update the head pointer */
  if (e->prev == NULL)
  {
    /* find category index */
    index = 0;

    while ( (G_entity_active_list_head[index] != e) && 
            (index < CATEGORY_NUM_INDICES))
    {
      index++;
    }

    if (index == CATEGORY_NUM_INDICES)
      return 1;

    /* update head pointer */
    G_entity_active_list_head[index] = e->next;
  }
  else
    e->prev->next = e->next;

  /* if this entity is the tail of a list, we need to update the tail pointer */
  if (e->next == NULL)
  {
    /* find category index */
    index = 0;

    while ( (G_entity_active_list_tail[index] != e) && 
            (index < CATEGORY_NUM_INDICES))
    {
      index++;
    }

    if (index == CATEGORY_NUM_INDICES)
      return 1;

    /* update tail pointer */
    G_entity_active_list_tail[index] = e->prev;
  }
  else
    e->next->prev = e->prev;

  /* add entity to the inactive list */
  if (G_entity_inactive_list_head == NULL)
  {
    G_entity_inactive_list_head = e;
    G_entity_inactive_list_tail = e;
    e->next = NULL;
    e->prev = NULL;
  }
  else
  {
    e->next = G_entity_inactive_list_head;
    G_entity_inactive_list_head->prev = e;
    e->prev = NULL;
    G_entity_inactive_list_head = e;
  }

  e->type = ENTITY_TYPE_NONE;

  return 0;
}

/*******************************************************************************
** world_reset()
*******************************************************************************/
short int world_reset()
{
  int i;

  /* clear all active lists */
  for (i = 0; i < CATEGORY_NUM_INDICES; i++)
  {
    /* if this list is empty, advance to next category */
    if (G_entity_active_list_head[i] == NULL)
      continue;

    /* if the inactive list is empty, simply set it to this list */
    if (G_entity_inactive_list_head == NULL)
    {
      G_entity_inactive_list_head = G_entity_active_list_head[i];
      G_entity_inactive_list_tail = G_entity_active_list_tail[i];
    }
    /* otherwise, add this active list onto the front of the inactive list */
    else
    {
      G_entity_active_list_tail[i]->next = G_entity_inactive_list_head;
      G_entity_inactive_list_head->prev = G_entity_active_list_tail[i];
      G_entity_inactive_list_head = G_entity_active_list_head[i];
    }

    G_entity_active_list_head[i] = NULL;
    G_entity_active_list_tail[i] = NULL;
  }

  /* reset particle array */
  for (i = 0; i < WORLD_PARTICLES_MAX; i++)
  {
    particle_reset(&G_particle_array[i]);
  }

  G_particle_start_i = 0;
  G_particle_end_i = 0;

  /* reset global variables */
  G_player = NULL;
  G_vials_remaining = 0;
  G_bat_transforms = 0;
  G_blue_mana = 0;
  G_green_mana = 0;
  G_theme = THEME_FOYER;

  return 0;
}

/*******************************************************************************
** world_update_particles()
*******************************************************************************/
short int world_update_particles()
{
  int       i;
  particle* p;

  /* update particle positions and lifetimes */
  for ( i = G_particle_start_i; 
        i != G_particle_end_i; 
        i = (i + 1) % WORLD_PARTICLES_MAX)
  {
    p = &G_particle_array[i];

    p->vel_x += p->acc_x;
    p->vel_y += p->acc_y;

    p->pos_x += p->vel_x;
    p->pos_y += p->vel_y;

    p->life_count -= 1;

    /* if particle is offscreen, set it to despawn */
    if (((p->pos_x >> PARTICLE_MANTISSA) < 0)     ||
        ((p->pos_x >> PARTICLE_MANTISSA) >= 640)  ||
        ((p->pos_y >> PARTICLE_MANTISSA) < 0)     ||
        ((p->pos_y >> PARTICLE_MANTISSA) >= 480))
    {
      p->life_count = 0;
    }
  }

  /* update start index by passing over despawned particles */
  /* at the start of the ring buffer                        */
  for ( i = G_particle_start_i; 
        i != G_particle_end_i; 
        i = (i + 1) % WORLD_PARTICLES_MAX)
  {
    p = &G_particle_array[i];

    if (p->life_count > 0)
      break;
    else
      G_particle_start_i = (G_particle_start_i + 1) % WORLD_PARTICLES_MAX;
  }

  return 0;
}

/*******************************************************************************
** world_update_positions()
*******************************************************************************/
short int world_update_positions()
{
  int     i;
  entity* e;

  for (i = 0; i < CATEGORY_NUM_INDICES; i++)
  {
    if (!(CATEGORY_INDEX_CAN_MOVE(i)))
      continue;

    e = G_entity_active_list_head[i];

    while (e != NULL)
    {
      /* clear carry over flag, if necessary */
      if (e->animation_flags & ENTITY_ANIMATION_FLAG_CARRY_OVER)
      {
        if ((e->type == ENTITY_TYPE_PLAYER_VAMPIRE)         ||
            (e->type == ENTITY_TYPE_DOUBLE_VAMPIRE)         ||
            (e->type == ENTITY_TYPE_REVERSE_DOUBLE_VAMPIRE))
        {
          /* if push was not continued, setup walking animation */
          if (!(e->action_flags & ENTITY_ACTION_FLAG_PUSHING))
          {
            animation_setup(e);

            if (!(e->action_flags & ENTITY_ACTION_FLAG_MOVING))
              e->tile = e->animation_array[e->animation_length - 1];
          }
        }

        e->animation_flags &= ~ENTITY_ANIMATION_FLAG_CARRY_OVER;
      }

      /* update position of moving entities */
      if ((e->action_flags & ENTITY_ACTION_FLAG_MOVING) ||
          (e->update_flags & ENTITY_UPDATE_FLAG_WALKING_IN_PLACE))
      {
        e->pos_x += e->vel_x;
        e->pos_y += e->vel_y;

        if (e->move_count > 0)
          e->move_count -= 1;

        /* spawn trailing particles, if necessary */
        if ((ENTITY_TYPE_IS_SPELL(e->type)) &&
            (e->type != ENTITY_TYPE_EVIL_EYE))
        {
          if (((e->pos_x % 8) == 0) && ((e->pos_y % 8) == 0))
            world_spawn_particles_trailing(e);
        }

        /* clear started this frame flag, if necessary */
        if (e->update_flags & ENTITY_UPDATE_FLAG_STARTED_MOVEMENT)
          e->update_flags &= ~ENTITY_UPDATE_FLAG_STARTED_MOVEMENT;

        /* check if movement is completed */
        if (e->move_count == 0)
        {
          e->vel_x = 0;
          e->vel_y = 0;
          e->action_flags &= ~ENTITY_ACTION_FLAG_MOVING;
          e->update_flags &= ~ENTITY_UPDATE_FLAG_WALKING_IN_PLACE;
          e->update_flags |= ENTITY_UPDATE_FLAG_STOPPED_MOVEMENT;

          if (e->action_flags & ENTITY_ACTION_FLAG_PUSHING)
            e->animation_flags |= ENTITY_ANIMATION_FLAG_CARRY_OVER;

          /* if ice cube has completed cooldown, set transformation flag */
          if (ENTITY_TYPE_IS_ICE_CUBE(e->type))
          {
            if ((e->cooldown_count == 0) &&
                (!(e->update_flags & ENTITY_UPDATE_FLAG_MOVING_INTO_WATER)))
            {
              e->update_flags |= ENTITY_UPDATE_FLAG_TRANSFORMING;
            }
          }
        }
      }

      e = e->next;
    }
  }

  return 0;
}

/*******************************************************************************
** world_update_cooldowns()
*******************************************************************************/
short int world_update_cooldowns()
{
  int     i;
  entity* e;

  for (i = 0; i < CATEGORY_NUM_INDICES; i++)
  {
    if (!(CATEGORY_INDEX_CAN_HAVE_COOLDOWN(i)))
      continue;

    e = G_entity_active_list_head[i];

    while (e != NULL)
    {
      if (e->update_flags & ENTITY_UPDATE_FLAG_COOLDOWN)
      {
        if (e->cooldown_count > 0)
          e->cooldown_count -= 1;

        if (e->cooldown_count == 0)
        {
          e->update_flags &= ~ENTITY_UPDATE_FLAG_COOLDOWN;

          /* if this is a stopped ice cube, set transformation flag */
          if (ENTITY_TYPE_IS_ICE_CUBE(e->type))
          {
            if ((!(e->action_flags & ENTITY_ACTION_FLAG_MOVING))  &&
                (!(e->update_flags & ENTITY_UPDATE_FLAG_MOVING_INTO_WATER)))
            {
              e->update_flags |= ENTITY_UPDATE_FLAG_TRANSFORMING;
            }
          }
          /* if this is a submerged mahjong tile or ice cube, */
          /* set awaiting destroyed flag                      */
          else if ( ENTITY_TYPE_IS_MAHJONG_TILE_SUBMERGED(e->type) ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_SUBMERGED))
          {
            e->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_DESTROY;
          }
          /* if this is a mahjong tile, wisp, mummy,  */
          /* or explosion, set destroyed flag         */
          else if ( ENTITY_TYPE_IS_MAHJONG_TILE(e->type)      ||
                    (e->type == ENTITY_TYPE_WISP_LEFT_WALL)   ||
                    (e->type == ENTITY_TYPE_WISP_RIGHT_WALL)  ||
                    (e->type == ENTITY_TYPE_MUMMY_LT)         ||
                    (e->type == ENTITY_TYPE_MUMMY_RT)         ||
                    (e->type == ENTITY_TYPE_EXPLOSION))
          {
            e->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
          }
          /* if this is a venusian root, set to active */
          else if (e->type == ENTITY_TYPE_VENUSIAN_ROOT)
          {
            e->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
          }
          /* reset animation after spell cast */
          else if ( (e->type == ENTITY_TYPE_SNAKE)                  ||
                    (e->type == ENTITY_TYPE_DOUBLE_VAMPIRE)         ||
                    (e->type == ENTITY_TYPE_REVERSE_DOUBLE_VAMPIRE) ||
                    (e->type == ENTITY_TYPE_WITCH)                  ||
                    (e->type == ENTITY_TYPE_UNDINE)                 ||
                    (e->type == ENTITY_TYPE_SORCERESS)              ||
                    (e->type == ENTITY_TYPE_PLAYER_VAMPIRE))
          {
            animation_setup(e);
          }
        }
      }

      e = e->next;
    }
  }

  return 0;
}

/*******************************************************************************
** world_update_spins()
*******************************************************************************/
short int world_update_spins()
{
  int     i;
  entity* e;
  int     original_frame_count;

  for (i = 0; i < CATEGORY_NUM_INDICES; i++)
  {
    if (!(CATEGORY_INDEX_CAN_SPIN(i)))
      continue;

    e = G_entity_active_list_head[i];

    while (e != NULL)
    {
      if (e->action_flags & ENTITY_ACTION_FLAG_ROTATING)
      {
        if (e->spin_count > 0)
          e->spin_count -= 1;

        if (e->spin_count == 0)
        {
          /* store animation frame for ballistas and laser guns */
          if (ENTITY_TYPE_IS_BALLISTA(e->type) ||
              (e->type == ENTITY_TYPE_LASER_GUN))
            original_frame_count = e->frame_count;

          /* counterclockwise spin */
          if (!(e->action_flags & ENTITY_ACTION_FLAG_MODE))
          {
            if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
              entity_set_facing(e, ENTITY_FACING_UP_RIGHT);
            else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP_RIGHT))
              entity_set_facing(e, ENTITY_FACING_UP);
            else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
              entity_set_facing(e, ENTITY_FACING_UP_LEFT);
            else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP_LEFT))
              entity_set_facing(e, ENTITY_FACING_LEFT);
            else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
              entity_set_facing(e, ENTITY_FACING_DOWN_LEFT);
            else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN_LEFT))
              entity_set_facing(e, ENTITY_FACING_DOWN);
            else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
              entity_set_facing(e, ENTITY_FACING_DOWN_RIGHT);
            else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN_RIGHT))
              entity_set_facing(e, ENTITY_FACING_RIGHT);
          }
          /* clockwise spin */
          else
          {
            if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
              entity_set_facing(e, ENTITY_FACING_DOWN_RIGHT);
            else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP_RIGHT))
              entity_set_facing(e, ENTITY_FACING_RIGHT);
            else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
              entity_set_facing(e, ENTITY_FACING_UP_RIGHT);
            else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP_LEFT))
              entity_set_facing(e, ENTITY_FACING_UP);
            else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
              entity_set_facing(e, ENTITY_FACING_UP_LEFT);
            else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN_LEFT))
              entity_set_facing(e, ENTITY_FACING_LEFT);
            else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
              entity_set_facing(e, ENTITY_FACING_DOWN_LEFT);
            else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN_RIGHT))
              entity_set_facing(e, ENTITY_FACING_DOWN);
          }

          /* set ballista or laser gun to proper animation frame */
          if (ENTITY_TYPE_IS_BALLISTA(e->type) || 
              (e->type == ENTITY_TYPE_LASER_GUN))
          {
            animation_setup(e);
            e->frame_count = original_frame_count;
          }

          e->action_flags &= ~ENTITY_ACTION_FLAG_ROTATING;
          e->action_flags &= ~ENTITY_ACTION_FLAG_MODE;
        }
      }

      e = e->next;
    }
  }

  return 0;
}

/*******************************************************************************
** world_update_animations()
*******************************************************************************/
short int world_update_animations()
{
  int     i;
  entity* e;

  for (i = 0; i < CATEGORY_NUM_INDICES; i++)
  {
    if (!(CATEGORY_INDEX_CAN_ANIMATE(i)))
      continue;

    for ( e = G_entity_active_list_head[i];
          e != NULL;
          e = e->next)
    {
      /* restart animation, if necessary */
      if (e->animation_flags & ENTITY_ANIMATION_FLAG_RESTART)
      {
        e->animation_flags |= ENTITY_ANIMATION_FLAG_ON;
        e->frame_count = e->frame_length * e->animation_length - 1;
        e->animation_flags &= ~ENTITY_ANIMATION_FLAG_RESTART;
      }

      /* update animation frames */
      if (e->animation_flags & ENTITY_ANIMATION_FLAG_ON)
      {
        if (e->animation_flags & ENTITY_ANIMATION_FLAG_ONLY_WHEN_MOVING)
        {
          if ((!(e->action_flags & ENTITY_ACTION_FLAG_MOVING))            &&
              (!(e->update_flags & ENTITY_UPDATE_FLAG_STOPPED_MOVEMENT))  &&
              (!(e->update_flags & ENTITY_UPDATE_FLAG_WALKING_IN_PLACE)))
          {
            continue;
          }

          if (e->action_flags & ENTITY_ACTION_FLAG_BEING_CONVEYED)
            continue;
        }

        if (e->animation_flags & ENTITY_ANIMATION_FLAG_PAUSED)
          continue;

        e->frame_count -= 1;

        if (e->frame_count < 0)
        {
          if (e->animation_flags & ENTITY_ANIMATION_FLAG_LOOPING)
            e->frame_count += e->frame_length * e->animation_length;
          else
          {
            e->animation_flags &= ~ENTITY_ANIMATION_FLAG_ON;
            e->tile = e->animation_array[0];
            continue;
          }
        }

        e->tile = e->animation_array[e->frame_count / e->frame_length];
      }
    }
  }

  return 0;
}

