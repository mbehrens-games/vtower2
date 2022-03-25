/*******************************************************************************
** collide.c (spatial partitioning grid and collision checking)
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "animate.h"
#include "collide.h"
#include "entity.h"
#include "world.h"

collide_grid_space G_collide_grid[COLLIDE_GRID_SIZE];

/*******************************************************************************
** collide_grid_init()
*******************************************************************************/
short int collide_grid_init()
{
  int i;
  int j;

  for (i = 0; i < COLLIDE_GRID_SIZE; i++)
  {
    /* allocate array */
    G_collide_grid[i].entities = 
      malloc(COLLIDE_GRID_SPACE_INITIAL_NUM * sizeof(entity*));

    /* make sure array was allocated */
    if (G_collide_grid[i].entities == NULL)
    {
      G_collide_grid[i].num_entities = 0;
      G_collide_grid[i].max_entities = 0;
      return 1;
    }
    else
    {
      G_collide_grid[i].num_entities = 0;
      G_collide_grid[i].max_entities = COLLIDE_GRID_SPACE_INITIAL_NUM;
    }

    /* initialize entity pointers to null */
    for (j = 0; j < G_collide_grid[i].max_entities; j++)
    {
      G_collide_grid[i].entities[j] = NULL;
    }
  }

  return 0;
}

/*******************************************************************************
** collide_grid_deinit()
*******************************************************************************/
short int collide_grid_deinit()
{
  int i;

  for (i = 0; i < COLLIDE_GRID_SIZE; i++)
  {
    /* deallocate array */
    if (G_collide_grid[i].entities)
    {
      free(G_collide_grid[i].entities);
      G_collide_grid[i].entities = NULL;
    }
  }

  return 0;
}

/*******************************************************************************
** collide_grid_reset()
*******************************************************************************/
short int collide_grid_reset()
{
  int i;

  for (i = 0; i < COLLIDE_GRID_SIZE; i++)
  {
    G_collide_grid[i].num_entities = 0;
  }

  return 0;
}

/*******************************************************************************
** collide_grid_update()
*******************************************************************************/
short int collide_grid_update()
{
  int                 i;
  int                 m;
  int                 n;
  entity*             current_e;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp;

  /* reset grid */
  collide_grid_reset();

  /* add entities to spaces they overlap in the grid */
  for (i = 0; i < CATEGORY_NUM_INDICES; i++)
  {
    if ((i == CATEGORY_INDEX_BACKGROUND)    ||
        (i == CATEGORY_INDEX_FLOOR_BORDERS) ||
        (i == CATEGORY_INDEX_GRASS_BORDERS) ||
        (i == CATEGORY_INDEX_ICE_BORDERS))
    {
      continue;
    }

    for ( current_e = G_entity_active_list_head[i]; 
          current_e != NULL; 
          current_e = current_e->next)
    {
      low_x = ((current_e->pos_x - current_e->rx) / 16) - 1;
      high_x = ((current_e->pos_x + current_e->rx - 1) / 16) - 1;

      low_y = ((current_e->pos_y - current_e->ry) / 16) - 3;
      high_y = ((current_e->pos_y + current_e->ry - 1) / 16) - 3;

      if (low_x < 0)
        low_x = 0;
      else if (low_x > COLLIDE_GRID_WIDTH - 1)
        continue;

      if (high_x < 0)
        continue;
      else if (high_x > COLLIDE_GRID_WIDTH - 1)
        high_x = COLLIDE_GRID_WIDTH - 1;

      if (low_y < 0)
        low_y = 0;
      else if (low_y > COLLIDE_GRID_HEIGHT - 1)
        continue;

      if (high_y < 0)
        continue;
      else if (high_y > COLLIDE_GRID_HEIGHT - 1)
        high_y = COLLIDE_GRID_HEIGHT - 1;

      for (m = low_x; m <= high_x; m++)
      {
        for (n = low_y; n <= high_y; n++)
        {
          sp = &(G_collide_grid[m * COLLIDE_GRID_HEIGHT + n]);

          if (sp->num_entities >= sp->max_entities)
          {
            sp->max_entities += COLLIDE_GRID_SPACE_RESIZE_NUM;
            sp->entities = realloc( sp->entities, 
                                    sp->max_entities * sizeof(entity*));

            if (sp->entities == NULL)
            {
              sp->num_entities = 0;
              sp->max_entities = 0;
              return 1;
            }
          }

          sp->entities[sp->num_entities] = current_e;
          sp->num_entities += 1;
        }
      }
    }
  }

  return 0;
}

/*******************************************************************************
** collide_grid_add_entity()
*******************************************************************************/
short int collide_grid_add_entity(entity* e)
{
  int                 m;
  int                 n;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp;

  if (e == NULL)
    return 1;

  /* determine which grid spaces this entity overlaps */
  low_x = ((e->pos_x - e->rx) / 16) - 1;
  high_x = ((e->pos_x + e->rx - 1) / 16) - 1;

  low_y = ((e->pos_y - e->ry) / 16) - 3;
  high_y = ((e->pos_y + e->ry - 1) / 16) - 3;

  /* if started movement this frame and also moving into water,   */
  /* shift bounds by 2 in the direction of movement               */
  if ((e->update_flags & ENTITY_UPDATE_FLAG_STARTED_MOVEMENT) &&
      (e->update_flags & ENTITY_UPDATE_FLAG_MOVING_INTO_WATER))
  {
    if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_RIGHT))
      high_x += 2;
    else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_UP))
      low_y -= 2;
    else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_LEFT))
      low_x -= 2;
    else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_DOWN))
      high_y += 2;
  }
  /* if started movement this frame, or continuing move into water, */
  /* shift bounds by 1 in the direction of movement                 */
  else if ( (e->update_flags & ENTITY_UPDATE_FLAG_STARTED_MOVEMENT) ||
            (e->update_flags & ENTITY_UPDATE_FLAG_MOVING_INTO_WATER))
  {
    if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_RIGHT))
      high_x += 1;
    else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_UP))
      low_y -= 1;
    else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_LEFT))
      low_x -= 1;
    else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_DOWN))
      high_y += 1;
  }

  /* check bounds */
  if (low_x < 0)
    low_x = 0;
  else if (low_x > COLLIDE_GRID_WIDTH - 1)
    return 0;

  if (high_x < 0)
    return 0;
  else if (high_x > COLLIDE_GRID_WIDTH - 1)
    high_x = COLLIDE_GRID_WIDTH - 1;

  if (low_y < 0)
    low_y = 0;
  else if (low_y > COLLIDE_GRID_HEIGHT - 1)
    return 0;

  if (high_y < 0)
    return 0;
  else if (high_y > COLLIDE_GRID_HEIGHT - 1)
    high_y = COLLIDE_GRID_HEIGHT - 1;

  /* add entity to appropriate grid spaces */
  for (m = low_x; m <= high_x; m++)
  {
    for (n = low_y; n <= high_y; n++)
    {
      sp = &(G_collide_grid[m * COLLIDE_GRID_HEIGHT + n]);

      if (sp->num_entities >= sp->max_entities)
      {
        sp->max_entities += COLLIDE_GRID_SPACE_RESIZE_NUM;
        sp->entities = realloc( sp->entities, 
                                sp->max_entities * sizeof(entity*));

        if (sp->entities == NULL)
        {
          sp->num_entities = 0;
          sp->max_entities = 0;
          return 1;
        }
      }

      sp->entities[sp->num_entities] = e;
      sp->num_entities += 1;
    }
  }

  return 0;
}

/*******************************************************************************
** collide_grid_remove_entity()
*******************************************************************************/
short int collide_grid_remove_entity(entity* e)
{
  int                 i;
  int                 index;
  int                 m;
  int                 n;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp;

  if (e == NULL)
    return 1;

  /* determine which grid spaces this entity overlaps */
  low_x = ((e->pos_x - e->rx) / 16) - 1;
  high_x = ((e->pos_x + e->rx - 1) / 16) - 1;

  low_y = ((e->pos_y - e->ry) / 16) - 3;
  high_y = ((e->pos_y + e->ry - 1) / 16) - 3;

  /* if started movement this frame and also moving into water,   */
  /* shift bounds by 2 in the direction of movement               */
  if ((e->update_flags & ENTITY_UPDATE_FLAG_STARTED_MOVEMENT) &&
      (e->update_flags & ENTITY_UPDATE_FLAG_MOVING_INTO_WATER))
  {
    if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_RIGHT))
      high_x += 2;
    else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_UP))
      low_y -= 2;
    else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_LEFT))
      low_x -= 2;
    else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_DOWN))
      high_y += 2;
  }
  /* if started movement this frame, or continuing move into water, */
  /* shift bounds by 1 in the direction of movement                 */
  else if ( (e->update_flags & ENTITY_UPDATE_FLAG_STARTED_MOVEMENT) ||
            (e->update_flags & ENTITY_UPDATE_FLAG_MOVING_INTO_WATER))
  {
    if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_RIGHT))
      high_x += 1;
    else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_UP))
      low_y -= 1;
    else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_LEFT))
      low_x -= 1;
    else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_DOWN))
      high_y += 1;
  }

  /* check bounds */
  if (low_x < 0)
    low_x = 0;
  else if (low_x > COLLIDE_GRID_WIDTH - 1)
    return 0;

  if (high_x < 0)
    return 0;
  else if (high_x > COLLIDE_GRID_WIDTH - 1)
    high_x = COLLIDE_GRID_WIDTH - 1;

  if (low_y < 0)
    low_y = 0;
  else if (low_y > COLLIDE_GRID_HEIGHT - 1)
    return 0;

  if (high_y < 0)
    return 0;
  else if (high_y > COLLIDE_GRID_HEIGHT - 1)
    high_y = COLLIDE_GRID_HEIGHT - 1;

  /* remove entity to appropriate grid spaces */
  for (m = low_x; m <= high_x; m++)
  {
    for (n = low_y; n <= high_y; n++)
    {
      sp = &(G_collide_grid[m * COLLIDE_GRID_HEIGHT + n]);

      /* find index of entity in this grid space */
      index = -1;

      for (i = 0; i < sp->num_entities; i++)
      {
        if (sp->entities[i] == e)
        {
          index = i;
          break;
        }
      }

      /* if entity not found in this grid space, continue */
      if (index == -1)
        continue;

      /* remove the entity from this grid space */
      for (i = index; i < sp->num_entities - 1; i++)
      {
        sp->entities[i] = sp->entities[i + 1];
      }

      sp->num_entities -= 1;
    }
  }

  return 0;
}

