/*******************************************************************************
** logic.c (game logic)
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "animate.h"
#include "collide.h"
#include "doremi.h"
#include "entity.h"
#include "global.h"
#include "logic.h"
#include "pairtree.h"
#include "world.h"

/*******************************************************************************
** logic_set_reflection_flags()
*******************************************************************************/
short int logic_set_reflection_flags(entity* e1, entity* e2)
{
  if ((e1 == NULL) || (e2 == NULL))
    return 0;

  /* make sure first entity is a spell */
  if (!(ENTITY_TYPE_IS_SPELL(e1->type)))
    return 0;

  /* make sure second entity is a reflecter */
  if (!(ENTITY_TYPE_IS_ONE_SIDED_REFLECTER(e2->type) ||
        ENTITY_TYPE_IS_DOUBLE_SIDED_REFLECTER(e2->type)))
    return 0;

  /* spell moving right */
  if ((ENTITY_DIRECTION_CHECK(e1, ENTITY_DIRECTION_RIGHT)) &&
      (e1->pos_y == e2->pos_y))
  {
    if (ENTITY_FACING_CHECK(e2, ENTITY_FACING_UP_LEFT))
    {
      e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_REVERSE;
      e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_BANK;
    }
    else if (ENTITY_FACING_CHECK(e2, ENTITY_FACING_LEFT))
      e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_REVERSE;
    else if (ENTITY_FACING_CHECK(e2, ENTITY_FACING_DOWN_LEFT))
      e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_BANK;

    if (ENTITY_TYPE_IS_DOUBLE_SIDED_REFLECTER(e2->type))
    {
      if (ENTITY_FACING_CHECK(e2, ENTITY_FACING_UP_RIGHT))
        e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_BANK;
      else if (ENTITY_FACING_CHECK(e2, ENTITY_FACING_RIGHT))
        e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_REVERSE;
      else if (ENTITY_FACING_CHECK(e2, ENTITY_FACING_DOWN_RIGHT))
      {
        e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_REVERSE;
        e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_BANK;
      }
    }
  }
  /* spell moving up */
  else if ( (ENTITY_DIRECTION_CHECK(e1, ENTITY_DIRECTION_UP)) &&
            (e1->pos_x == e2->pos_x))
  {
    if (ENTITY_FACING_CHECK(e2, ENTITY_FACING_DOWN_LEFT))
    {
      e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_REVERSE;
      e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_BANK;
    }
    else if (ENTITY_FACING_CHECK(e2, ENTITY_FACING_DOWN))
      e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_REVERSE;
    else if (ENTITY_FACING_CHECK(e2, ENTITY_FACING_DOWN_RIGHT))
      e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_BANK;

    if (ENTITY_TYPE_IS_DOUBLE_SIDED_REFLECTER(e2->type))
    {
      if (ENTITY_FACING_CHECK(e2, ENTITY_FACING_UP_LEFT))
        e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_BANK;
      else if (ENTITY_FACING_CHECK(e2, ENTITY_FACING_UP))
        e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_REVERSE;
      else if (ENTITY_FACING_CHECK(e2, ENTITY_FACING_UP_RIGHT))
      {
        e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_REVERSE;
        e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_BANK;
      }
    }
  }
  /* spell moving left */
  else if ( (ENTITY_DIRECTION_CHECK(e1, ENTITY_DIRECTION_LEFT)) &&
            (e1->pos_y == e2->pos_y))
  {
    if (ENTITY_FACING_CHECK(e2, ENTITY_FACING_DOWN_RIGHT))
    {
      e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_REVERSE;
      e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_BANK;
    }
    else if (ENTITY_FACING_CHECK(e2, ENTITY_FACING_RIGHT))
      e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_REVERSE;
    else if (ENTITY_FACING_CHECK(e2, ENTITY_FACING_UP_RIGHT))
      e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_BANK;

    if (ENTITY_TYPE_IS_DOUBLE_SIDED_REFLECTER(e2->type))
    {
      if (ENTITY_FACING_CHECK(e2, ENTITY_FACING_DOWN_LEFT))
        e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_BANK;
      else if (ENTITY_FACING_CHECK(e2, ENTITY_FACING_LEFT))
        e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_REVERSE;
      else if (ENTITY_FACING_CHECK(e2, ENTITY_FACING_UP_LEFT))
      {
        e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_REVERSE;
        e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_BANK;
      }
    }
  }
  /* spell moving down */
  else if ( (ENTITY_DIRECTION_CHECK(e1, ENTITY_DIRECTION_DOWN)) &&
            (e1->pos_x == e2->pos_x))
  {
    if (ENTITY_FACING_CHECK(e2, ENTITY_FACING_UP_RIGHT))
    {
      e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_REVERSE;
      e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_BANK;
    }
    else if (ENTITY_FACING_CHECK(e2, ENTITY_FACING_UP))
      e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_REVERSE;
    else if (ENTITY_FACING_CHECK(e2, ENTITY_FACING_UP_LEFT))
      e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_BANK;

    if (ENTITY_TYPE_IS_DOUBLE_SIDED_REFLECTER(e2->type))
    {
      if (ENTITY_FACING_CHECK(e2, ENTITY_FACING_DOWN_RIGHT))
        e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_BANK;
      else if (ENTITY_FACING_CHECK(e2, ENTITY_FACING_DOWN))
        e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_REVERSE;
      else if (ENTITY_FACING_CHECK(e2, ENTITY_FACING_DOWN_LEFT))
      {
        e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_REVERSE;
        e1->special_flags |= ENTITY_SPECIAL_FLAG_REFLECT_BANK;
      }
    }
  }

  return 0;
}

/*******************************************************************************
** logic_attempt_move()
*******************************************************************************/
short int logic_attempt_move(entity* e1, unsigned char direction)
{
  int                 i;
  int                 j;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp[2];
  int                 indices[2];
  collide_grid_space* extra_sp[2];
  int                 extra_indices[2];
  entity*             water[2];
  entity*             extra_water[2];
  entity*             e2;

  if (e1 == NULL)
    return 1;

  /* make sure entity is not already in motion, casting a spell, etc */
  if (ENTITY_IS_PERFORMING_ACTION(e1))
    return 0;

  /* make sure entity is not a matched mahjong tile */
  if ((ENTITY_TYPE_IS_MAHJONG_TILE(e1->type)) &&
      ENTITY_IS_IN_COOLDOWN(e1))
  {
    return 0;
  }

  /* make sure entity is not a stopped jiangshi */
  if ((e1->type == ENTITY_TYPE_JIANGSHI_LT) ||
      (e1->type == ENTITY_TYPE_JIANGSHI_RT))
  {
    if (e1->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      /* if jiangshi is being conveyed in this  */
      /* direction, this move is still allowed  */
      if (!((e1->action_flags & ENTITY_ACTION_FLAG_BEING_CONVEYED) &&
            ENTITY_DIRECTION_CHECK(e1, direction)))
      {
        return 0;
      }
    }
  }

  /* make sure entity has not fallen into water */
  if (e1->update_flags & ENTITY_UPDATE_FLAG_FELL_INTO_WATER)
    return 0;

  /* make sure direction is valid */
  if ((direction != ENTITY_DIRECTION_RIGHT) &&
      (direction != ENTITY_DIRECTION_UP)    &&
      (direction != ENTITY_DIRECTION_LEFT)  &&
      (direction != ENTITY_DIRECTION_DOWN))
  {
    return 1;
  }

  /* make sure entity is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
    return 0;

  /* check if entity is moving against conveyer belt */
  if (e1->action_flags & ENTITY_ACTION_FLAG_BEING_CONVEYED)
  {
    if (((direction == ENTITY_DIRECTION_RIGHT) &&
        (ENTITY_DIRECTION_CHECK(e1, ENTITY_DIRECTION_LEFT)))  ||
        ((direction == ENTITY_DIRECTION_UP) &&
        (ENTITY_DIRECTION_CHECK(e1, ENTITY_DIRECTION_DOWN)))  ||
        ((direction == ENTITY_DIRECTION_LEFT) &&
        (ENTITY_DIRECTION_CHECK(e1, ENTITY_DIRECTION_RIGHT))) ||
        ((direction == ENTITY_DIRECTION_DOWN) &&
        (ENTITY_DIRECTION_CHECK(e1, ENTITY_DIRECTION_UP))))
    {
      e1->orientation &= ~ENTITY_DIRECTION_MASK;
      e1->orientation |= direction;
      e1->update_flags |= ENTITY_UPDATE_FLAG_WALKING_IN_PLACE;
      e1->vel_x = 0;
      e1->vel_y = 0;
      e1->move_count = 8;
      e1->action_flags &= ~ENTITY_ACTION_FLAG_BEING_CONVEYED;

      return 0;
    }
  }

  /* determine location of entity in grid */
  low_x = (e1->pos_x / 16) - 2;
  high_x = low_x + 1;

  low_y = (e1->pos_y / 16) - 4;
  high_y = low_y + 1;

  /* make sure entity is within the grid */
  if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((high_x < 0) || (high_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  if ((high_y < 0) || (high_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  /* set indices to check based on movement direction */
  if (direction == ENTITY_DIRECTION_RIGHT)
  {
    if (high_x == COLLIDE_GRID_WIDTH - 1)
      return 0;

    indices[0] = (high_x + 1) * COLLIDE_GRID_HEIGHT + low_y;
    indices[1] = (high_x + 1) * COLLIDE_GRID_HEIGHT + high_y;
  }
  else if (direction == ENTITY_DIRECTION_UP)
  {
    if (low_y == 0)
      return 0;

    indices[0] = low_x * COLLIDE_GRID_HEIGHT + (low_y - 1);
    indices[1] = high_x * COLLIDE_GRID_HEIGHT + (low_y - 1);
  }
  else if (direction == ENTITY_DIRECTION_LEFT)
  {
    if (low_x == 0)
      return 0;

    indices[0] = (low_x - 1) * COLLIDE_GRID_HEIGHT + low_y;
    indices[1] = (low_x - 1) * COLLIDE_GRID_HEIGHT + high_y;
  }
  else if (direction == ENTITY_DIRECTION_DOWN)
  {
    if (high_y == COLLIDE_GRID_HEIGHT - 1)
      return 0;

    indices[0] = low_x * COLLIDE_GRID_HEIGHT + (high_y + 1);
    indices[1] = high_x * COLLIDE_GRID_HEIGHT + (high_y + 1);
  }
  else
  {
    return 0;
  }

  /* set first two grid space pointers */
  sp[0] = &(G_collide_grid[indices[0]]);
  sp[1] = &(G_collide_grid[indices[1]]);

  /* check for movement blocking entities */
  for (i = 0; i < 2; i++)
  {
    water[i] = NULL;

    for (j = 0; j < sp[i]->num_entities; j++)
    {
      e2 = sp[i]->entities[j];

      /* check triggers (pushable objects, eight balls, levers,       */
      /* ballistas, wisps, jiangshis, player, reflecters) separately  */
      if (e1->trigger_affect & e2->trigger_attribute)
        continue;

      /* check if this entity is a reflecter moving into a spell */
      if ((e1->trigger_attribute & ENTITY_TRIGGER_FLAG_REFLECTER) &&
          (e2->trigger_affect & ENTITY_TRIGGER_FLAG_REFLECTER))
      {
        if (((direction == ENTITY_DIRECTION_RIGHT) &&
            (ENTITY_DIRECTION_CHECK(e2, ENTITY_DIRECTION_LEFT)))  ||
            ((direction == ENTITY_DIRECTION_UP) &&
            (ENTITY_DIRECTION_CHECK(e2, ENTITY_DIRECTION_DOWN)))  ||
            ((direction == ENTITY_DIRECTION_LEFT) &&
            (ENTITY_DIRECTION_CHECK(e2, ENTITY_DIRECTION_RIGHT))) ||
            ((direction == ENTITY_DIRECTION_DOWN) &&
            (ENTITY_DIRECTION_CHECK(e2, ENTITY_DIRECTION_UP))))
        {
          continue;
        }
      }

      /* check damaging objects (spells, etc) separately */
      if ((e1->damage_affect & e2->damage_attribute)  ||
          (e2->damage_affect & e1->damage_attribute))
      {
        continue;
      }

      /* check if this entity blocks our movement */
      if (e1->move_attribute & e2->move_affect)
      {
        /* water */
        if ((e2->type == ENTITY_TYPE_WATER) && (water[i] == NULL))
        {
          water[i] = e2;
          continue;
        }

        /* special case - enemy conveyed onto grass */
        if (e2->type == ENTITY_TYPE_GRASS)
        {
          if ((e1->action_flags & ENTITY_ACTION_FLAG_BEING_CONVEYED) &&
              ENTITY_DIRECTION_CHECK(e1, direction))
          {
            continue;
          }
        }

        /* special case - two warp spells hitting each other */
        if ((e1->type == ENTITY_TYPE_WARP_SPELL) && 
            (e2->type == ENTITY_TYPE_WARP_SPELL))
        {
          e1->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
          e2->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
          return 0;
        }

        /* special case - arrows */
        if (ENTITY_TYPE_IS_ARROWS(e2->type))
        {
          if ((direction == ENTITY_DIRECTION_LEFT)  &&
              (e1->pos_x - e1->rx == e2->pos_x + e2->rx))
          {
            if ((ENTITY_FACING_CHECK(e2, ENTITY_FACING_RIGHT))      ||
                (ENTITY_FACING_CHECK(e2, ENTITY_FACING_UP_RIGHT))   ||
                (ENTITY_FACING_CHECK(e2, ENTITY_FACING_DOWN_RIGHT)))
              return 0;
          }
          else if ( (direction == ENTITY_DIRECTION_DOWN)  &&
                    (e1->pos_y + e1->ry == e2->pos_y - e2->ry))
          {
            if ((ENTITY_FACING_CHECK(e2, ENTITY_FACING_UP))         ||
                (ENTITY_FACING_CHECK(e2, ENTITY_FACING_UP_LEFT))    ||
                (ENTITY_FACING_CHECK(e2, ENTITY_FACING_UP_RIGHT)))
              return 0;
          }
          else if ( (direction == ENTITY_DIRECTION_RIGHT) &&
                    (e1->pos_x + e1->rx == e2->pos_x - e2->rx))
          {
            if ((ENTITY_FACING_CHECK(e2, ENTITY_FACING_LEFT))       ||
                (ENTITY_FACING_CHECK(e2, ENTITY_FACING_UP_LEFT))    ||
                (ENTITY_FACING_CHECK(e2, ENTITY_FACING_DOWN_LEFT)))
              return 0;
          }
          else if ( (direction == ENTITY_DIRECTION_UP)  &&
                    (e1->pos_y - e1->ry == e2->pos_y + e2->ry))
          {
            if ((ENTITY_FACING_CHECK(e2, ENTITY_FACING_DOWN))       ||
                (ENTITY_FACING_CHECK(e2, ENTITY_FACING_DOWN_LEFT))  ||
                (ENTITY_FACING_CHECK(e2, ENTITY_FACING_DOWN_RIGHT)))
              return 0;
          }

          continue;
        }

        /* special case - two entities are moving in same direction,  */
        /*                and 1st will not overtake the 2nd           */
        if (e2->action_flags & ENTITY_ACTION_FLAG_MOVING)
        {
          if (ENTITY_DIRECTION_CHECK(e2, direction))
          {
            if (!(e1->orientation & ENTITY_SPEED_FLAG))
              continue;
            else if ( (e1->orientation & ENTITY_SPEED_FLAG) &&
                      (e2->orientation & ENTITY_SPEED_FLAG))
              continue;
          }
        }

        /* special case - 1st entity is player or double,   */
        /*                2nd entity is double              */
        if ((e1->type == ENTITY_TYPE_PLAYER_VAMPIRE)  ||
            (e1->type == ENTITY_TYPE_PLAYER_BAT)      ||
            (e1->type == ENTITY_TYPE_DOUBLE_VAMPIRE)  ||
            (e1->type == ENTITY_TYPE_DOUBLE_BAT))
        {
          if ((e2->type == ENTITY_TYPE_DOUBLE_VAMPIRE)  ||
              (e2->type == ENTITY_TYPE_DOUBLE_BAT))
          {
            /* make sure double is not already moving, or in cooldown */
            if (ENTITY_IS_PERFORMING_ACTION(e2) ||
                ENTITY_IS_IN_COOLDOWN(e2))
            {
              return 0;
            }

            /* double is moving in a new direction */
            if ((direction == ENTITY_DIRECTION_RIGHT) &&
                (!(ENTITY_FACING_CHECK(e2, ENTITY_FACING_RIGHT))))
            {
              entity_set_facing(e2, ENTITY_FACING_RIGHT);
              logic_attempt_move(e2, direction);
              animation_setup(e2);
            }
            else if ( (direction == ENTITY_DIRECTION_UP) &&
                      (!(ENTITY_FACING_CHECK(e2, ENTITY_FACING_UP))))
            {
              entity_set_facing(e2, ENTITY_FACING_UP);
              logic_attempt_move(e2, direction);
              animation_setup(e2);
            }
            else if ( (direction == ENTITY_DIRECTION_LEFT) &&
                      (!(ENTITY_FACING_CHECK(e2, ENTITY_FACING_LEFT))))
            {
              entity_set_facing(e2, ENTITY_FACING_LEFT);
              logic_attempt_move(e2, direction);
              animation_setup(e2);
            }
            else if ( (direction == ENTITY_DIRECTION_DOWN) &&
                      (!(ENTITY_FACING_CHECK(e2, ENTITY_FACING_DOWN))))
            {
              entity_set_facing(e2, ENTITY_FACING_DOWN);
              logic_attempt_move(e2, direction);
              animation_setup(e2);
            }
            /* double is moving in the same direction */
            else
            {
              logic_attempt_move(e2, direction);

              /* if double started pushing this frame, setup animation */
              if ((e2->action_flags & ENTITY_ACTION_FLAG_PUSHING)    && 
                  (!(e2->animation_flags & ENTITY_ANIMATION_FLAG_CARRY_OVER)))
              {
                animation_setup(e2);
              }
            }

            if (e2->action_flags & ENTITY_ACTION_FLAG_MOVING)
              continue;
          }
        }

        /* otherwise, movement is blocked */
        return 0;
      }
    }
  }

  /* check if moving into water */
  if ((water[0] == NULL) && (water[1] == NULL))
  {
    extra_sp[0] = NULL;
    extra_sp[1] = NULL;
  }
  else if ( ((water[0] != NULL) && (water[1] == NULL))  ||
            ((water[0] == NULL) && (water[1] != NULL)))
  {
    return 0;
  }
  /* if halfway into the water, no need to check all four spaces */
  else if (e1->update_flags & ENTITY_UPDATE_FLAG_MOVING_INTO_WATER)
  {
    extra_sp[0] = NULL;
    extra_sp[1] = NULL;
    e1->update_flags &= ~ENTITY_UPDATE_FLAG_MOVING_INTO_WATER;
  }
  /* moving into water is possible for pushable objects,  */
  /* as well as slipping player and enemies               */
  else
  {
    /* determine extra indices */
    if (direction == ENTITY_DIRECTION_RIGHT)
    {
      if (high_x == COLLIDE_GRID_WIDTH - 2)
      {
        extra_indices[0] = indices[0];
        extra_indices[1] = indices[1];
      }
      else
      {
        extra_indices[0] = (high_x + 2) * COLLIDE_GRID_HEIGHT + low_y;
        extra_indices[1] = (high_x + 2) * COLLIDE_GRID_HEIGHT + high_y;
      }
    }
    else if (direction == ENTITY_DIRECTION_UP)
    {
      if (low_y == 1)
      {
        extra_indices[0] = indices[0];
        extra_indices[1] = indices[1];
      }
      else
      {
        extra_indices[0] = low_x * COLLIDE_GRID_HEIGHT + (low_y - 2);
        extra_indices[1] = high_x * COLLIDE_GRID_HEIGHT + (low_y - 2);
      }
    }
    else if (direction == ENTITY_DIRECTION_LEFT)
    {
      if (low_x == 1)
      {
        extra_indices[0] = indices[0];
        extra_indices[1] = indices[1];
      }
      else
      {
        extra_indices[0] = (low_x - 2) * COLLIDE_GRID_HEIGHT + low_y;
        extra_indices[1] = (low_x - 2) * COLLIDE_GRID_HEIGHT + high_y;
      }
    }
    else if (direction == ENTITY_DIRECTION_DOWN)
    {
      if (high_y == COLLIDE_GRID_HEIGHT - 2)
      {
        extra_indices[0] = indices[0];
        extra_indices[1] = indices[1];
      }
      else
      {
        extra_indices[0] = low_x * COLLIDE_GRID_HEIGHT + (high_y + 2);
        extra_indices[1] = high_x * COLLIDE_GRID_HEIGHT + (high_y + 2);
      }
    }

    /* set extra two grid space pointers */
    extra_sp[0] = &(G_collide_grid[extra_indices[0]]);
    extra_sp[1] = &(G_collide_grid[extra_indices[1]]);

    /* check extra spaces for movement blocking entities */
    for (i = 0; i < 2; i++)
    {
      extra_water[i] = NULL;

      for (j = 0; j < extra_sp[i]->num_entities; j++)
      {
        e2 = extra_sp[i]->entities[j];

        if (e1->move_attribute & e2->move_affect)
        {
          /* water */
          if ((e2->type == ENTITY_TYPE_WATER) && (extra_water[i] == NULL))
          {
            extra_water[i] = e2;
            continue;
          }

          /* otherwise, movement is blocked */
          return 0;
        }
      }
    }

    /* if water is found in all 4 spaces, */
    /* commence move if possible          */
    if ((extra_water[0] == NULL) || (extra_water[1] == NULL))
    {
      return 0;
    }
    else if ((extra_water[0] != NULL) && (extra_water[1] != NULL))
    {
      /* player or enemy can slip or be conveyed into water */
      if ((e1->move_attribute & ENTITY_MOVE_FLAG_VAMPIRE)   ||
          (e1->move_attribute & ENTITY_MOVE_FLAG_ENEMY))
      {
        if (!((e1->action_flags & ENTITY_ACTION_FLAG_SLIPPING) ||
              ((e1->action_flags & ENTITY_ACTION_FLAG_BEING_CONVEYED) &&
                ENTITY_DIRECTION_CHECK(e1, direction))))
        {
          return 0;
        }
      }
      /* otherwise, only pushable objects (and venusians) can enter */
      else if ( (!(e1->move_attribute & ENTITY_MOVE_FLAG_PUSHABLE_HIGH))  &&
                (!(e1->move_attribute & ENTITY_MOVE_FLAG_PUSHABLE_LOW)))
      {
        return 0;
      }

      e1->update_flags |= ENTITY_UPDATE_FLAG_MOVING_INTO_WATER;
    }
  }

  /* check pushable objects, if necessary */
  if (e1->trigger_affect & ENTITY_TRIGGER_FLAG_PUSHABLE)
  {
    for (i = 0; i < 2; i++)
    {
      for (j = 0; j < sp[i]->num_entities; j++)
      {
        e2 = sp[i]->entities[j];

        if (!(e2->trigger_attribute & ENTITY_TRIGGER_FLAG_PUSHABLE))
          continue;

        /* if pushable object is being conveyed,  */
        /* check its current movement direction   */
        if (e2->action_flags & ENTITY_ACTION_FLAG_BEING_CONVEYED)
        {
          /* if moving in opposing directions, return */
          if (((direction == ENTITY_DIRECTION_RIGHT) &&
              (ENTITY_DIRECTION_CHECK(e2, ENTITY_DIRECTION_LEFT)))  ||
              ((direction == ENTITY_DIRECTION_UP) &&
              (ENTITY_DIRECTION_CHECK(e2, ENTITY_DIRECTION_DOWN)))  ||
              ((direction == ENTITY_DIRECTION_LEFT) &&
              (ENTITY_DIRECTION_CHECK(e2, ENTITY_DIRECTION_RIGHT))) ||
              ((direction == ENTITY_DIRECTION_DOWN) &&
              (ENTITY_DIRECTION_CHECK(e2, ENTITY_DIRECTION_UP))))
          {
            return 0;
          }
        }

        /* make sure pushable object is lined up with entity */
        if (direction == ENTITY_DIRECTION_RIGHT)
        {
          if (e1->pos_y != e2->pos_y)
            return 0;
        }
        else if (direction == ENTITY_DIRECTION_UP)
        {
          if (e1->pos_x != e2->pos_x)
            return 0;
        }
        else if (direction == ENTITY_DIRECTION_LEFT)
        {
          if (e1->pos_y != e2->pos_y)
            return 0;
        }
        else if (direction == ENTITY_DIRECTION_DOWN)
        {
          if (e1->pos_x != e2->pos_x)
            return 0;
        }

        /* if we are on the second grid space, assume that we already */
        /* handled this object on the first grid space                */
        if (i == 1)
          continue;

        /* make sure pushable object is not already in motion */
        if (e2->action_flags & ENTITY_ACTION_FLAG_MOVING)
        {
          if (!(ENTITY_DIRECTION_CHECK(e2, direction)))
            return 0;
          else
            continue;
        }

        /* if this entity is slipping into a stone box or stone pot,  */
        /* the push is cancelled                                      */
        if (e1->action_flags & ENTITY_ACTION_FLAG_SLIPPING)
        {
          if (ENTITY_TYPE_IS_STONE(e2->type))
            return 0;
        }

        /* setup facing and animation for eight ball */
        if (e2->type == ENTITY_TYPE_EIGHT_BALL)
        {
          if (direction == ENTITY_DIRECTION_RIGHT)
            entity_set_facing(e2, ENTITY_FACING_RIGHT);
          else if (direction == ENTITY_DIRECTION_UP)
            entity_set_facing(e2, ENTITY_FACING_UP);
          else if (direction == ENTITY_DIRECTION_LEFT)
            entity_set_facing(e2, ENTITY_FACING_LEFT);
          else if (direction == ENTITY_DIRECTION_DOWN)
            entity_set_facing(e2, ENTITY_FACING_DOWN);

          animation_setup(e2);
        }

        /* try to move pushable object */
        e2->action_flags |= ENTITY_ACTION_FLAG_BEING_PUSHED;
        logic_attempt_move(e2, direction);

        /* if pushable object did not move, return */
        if (!(e2->action_flags & ENTITY_ACTION_FLAG_MOVING))
        {
          e2->action_flags &= ~ENTITY_ACTION_FLAG_BEING_PUSHED;
          return 0;
        }

        /* set flags */
        e1->action_flags |= ENTITY_ACTION_FLAG_PUSHING;

        if (e2->type == ENTITY_TYPE_EIGHT_BALL)
          e2->special_flags |= ENTITY_SPECIAL_FLAG_ROLLING;
      }
    }
  }

  /* check eight balls, if necessary */
  if (e1->trigger_affect & ENTITY_TRIGGER_FLAG_EIGHT_BALLS)
  {
    for (i = 0; i < 2; i++)
    {
      for (j = 0; j < sp[i]->num_entities; j++)
      {
        e2 = sp[i]->entities[j];

        if (!(e2->trigger_attribute & ENTITY_TRIGGER_FLAG_EIGHT_BALLS))
          continue;

        /* make sure 1st eight ball is lined up with 2nd eight ball */
        if ((direction == ENTITY_DIRECTION_RIGHT) ||
            (direction == ENTITY_DIRECTION_LEFT))
        {
          if (e1->pos_y != e2->pos_y)
          {
            if (e1->special_flags & ENTITY_SPECIAL_FLAG_ROLLING)
              e1->special_flags &= ~ENTITY_SPECIAL_FLAG_ROLLING;

            return 0;
          }
        }
        else if ( (direction == ENTITY_DIRECTION_UP) ||
                  (direction == ENTITY_DIRECTION_DOWN))
        {
          if (e1->pos_x != e2->pos_x)
          {
            if (e1->special_flags & ENTITY_SPECIAL_FLAG_ROLLING)
              e1->special_flags &= ~ENTITY_SPECIAL_FLAG_ROLLING;

            return 0;
          }
        }
        else
          return 0;

        /* if we are on the second grid space, assume that we already */
        /* handled this eight ball on the first grid space            */
        if (i == 1)
          continue;

        /* if 2nd eight ball is already moving, make sure */
        /* it is moving in the same direction as the 1st  */
        if (e2->action_flags & ENTITY_ACTION_FLAG_MOVING)
        {
          if (!(ENTITY_DIRECTION_CHECK(e2, direction)))
          {
            if (e1->special_flags & ENTITY_SPECIAL_FLAG_ROLLING)
              e1->special_flags &= ~ENTITY_SPECIAL_FLAG_ROLLING;

            return 0;
          }
          else
            continue;
        }
        /* if 2nd eight ball is potentially starting  */
        /* to move, setup animation                   */
        else
        {
          if (direction == ENTITY_DIRECTION_RIGHT)
            entity_set_facing(e2, ENTITY_FACING_RIGHT);
          else if (direction == ENTITY_DIRECTION_UP)
            entity_set_facing(e2, ENTITY_FACING_UP);
          else if (direction == ENTITY_DIRECTION_LEFT)
            entity_set_facing(e2, ENTITY_FACING_LEFT);
          else if (direction == ENTITY_DIRECTION_DOWN)
            entity_set_facing(e2, ENTITY_FACING_DOWN);

          animation_setup(e2);
        }

        /* 1st eight ball being pushed into 2nd eight ball */
        if (e1->action_flags & ENTITY_ACTION_FLAG_BEING_PUSHED)
        {
          e2->action_flags |= ENTITY_ACTION_FLAG_BEING_PUSHED;
          logic_attempt_move(e2, direction);

          if (e2->action_flags & ENTITY_ACTION_FLAG_MOVING)
          {
            e1->special_flags |= ENTITY_SPECIAL_FLAG_ROLLING;
            e2->special_flags |= ENTITY_SPECIAL_FLAG_ROLLING;
            doremi_play_sfx(SFX_INDEX_EIGHT_BALL_HIT);
          }
          else
          {
            e1->action_flags &= ~ENTITY_ACTION_FLAG_BEING_PUSHED;

            if (e1->special_flags & ENTITY_SPECIAL_FLAG_ROLLING)
              e1->special_flags &= ~ENTITY_SPECIAL_FLAG_ROLLING;

            e2->action_flags &= ~ENTITY_ACTION_FLAG_BEING_PUSHED;

            if (e2->special_flags & ENTITY_SPECIAL_FLAG_ROLLING)
              e2->special_flags &= ~ENTITY_SPECIAL_FLAG_ROLLING;

            return 0;
          }
        }
        /* 2nd eight ball is rolling in front of 1st eight ball */
        else if (e2->special_flags & ENTITY_SPECIAL_FLAG_ROLLING)
        {
          logic_attempt_move(e2, direction);

          /* if 2nd eight ball stopped, impart momentum from  */
          /* 1st eight ball and try to move another time      */
          if (!(e2->action_flags & ENTITY_ACTION_FLAG_MOVING))
          {
            if (e1->special_flags & ENTITY_SPECIAL_FLAG_ROLLING)
              e1->special_flags &= ~ENTITY_SPECIAL_FLAG_ROLLING;

            logic_attempt_move(e2, direction);

            if (!(e2->action_flags & ENTITY_ACTION_FLAG_MOVING))
            {
              e2->special_flags &= ~ENTITY_SPECIAL_FLAG_ROLLING;
            }
            else
            {
              doremi_play_sfx(SFX_INDEX_EIGHT_BALL_HIT);
            }

            return 0;
          }
        }
        /* 1st eight ball hits 2nd eight ball */
        else
        {
          if (e1->special_flags & ENTITY_SPECIAL_FLAG_ROLLING)
            e1->special_flags &= ~ENTITY_SPECIAL_FLAG_ROLLING;

          logic_attempt_move(e2, direction);

          if (e2->action_flags & ENTITY_ACTION_FLAG_MOVING)
          {
            e2->special_flags |= ENTITY_SPECIAL_FLAG_ROLLING;
            doremi_play_sfx(SFX_INDEX_EIGHT_BALL_HIT);
          }

          return 0;
        }
      }
    }
  }

  /* check for lever toggling */
  if (e1->trigger_affect & ENTITY_TRIGGER_FLAG_LEVERS)
  {
    for (i = 0; i < 2; i++)
    {
      for (j = 0; j < sp[i]->num_entities; j++)
      {
        e2 = sp[i]->entities[j];

        if ((e2->trigger_attribute & ENTITY_TRIGGER_FLAG_LEVERS)  &&
            (!(e2->update_flags & ENTITY_UPDATE_FLAG_COOLDOWN))   &&
            ((e1->pos_x == e2->pos_x) || (e1->pos_y == e2->pos_y)))
        {
          e2->update_flags |= ENTITY_UPDATE_FLAG_COOLDOWN;
          e2->cooldown_count = ENTITY_COOLDOWN_TIME_LEVER;

          /* play sfx */
          if (e2->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
            doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
          else
            doremi_play_sfx(SFX_INDEX_TOGGLE_UP);

          /* set flags */
          if (e2->type == ENTITY_TYPE_LEVER_WHITE)
          {
            if (e2->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
            {
              G_lever_flags |= GLOBAL_LEVER_FLAG_WHITE_OFF;
              e2->update_flags &= ~ENTITY_UPDATE_FLAG_ACTIVE;
            }
            else
            {
              G_lever_flags |= GLOBAL_LEVER_FLAG_WHITE_ON;
              e2->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
            }
          }
          else if (e2->type == ENTITY_TYPE_LEVER_CYAN)
          {
            if (e2->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
            {
              G_lever_flags |= GLOBAL_LEVER_FLAG_CYAN_OFF;
              e2->update_flags &= ~ENTITY_UPDATE_FLAG_ACTIVE;
            }
            else
            {
              G_lever_flags |= GLOBAL_LEVER_FLAG_CYAN_ON;
              e2->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
            }
          }
          else if (e2->type == ENTITY_TYPE_LEVER_MAGENTA)
          {
            if (e2->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
            {
              G_lever_flags |= GLOBAL_LEVER_FLAG_MAGENTA_OFF;
              e2->update_flags &= ~ENTITY_UPDATE_FLAG_ACTIVE;
            }
            else
            {
              G_lever_flags |= GLOBAL_LEVER_FLAG_MAGENTA_ON;
              e2->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
            }
          }

          animation_setup(e2);
        }
      }
    }
  }

  /* check for ballista firing */
  if (e1->trigger_affect & ENTITY_TRIGGER_FLAG_BALLISTAS)
  {
    for (i = 0; i < 2; i++)
    {
      for (j = 0; j < sp[i]->num_entities; j++)
      {
        e2 = sp[i]->entities[j];

        if ((e2->trigger_attribute & ENTITY_TRIGGER_FLAG_BALLISTAS) &&
            (!(e2->update_flags & ENTITY_UPDATE_FLAG_COOLDOWN)))
        {
          /* firing right */
          if ((ENTITY_FACING_CHECK(e1, ENTITY_FACING_RIGHT))  &&
              (ENTITY_FACING_CHECK(e2, ENTITY_FACING_RIGHT))  &&
              (e1->pos_y == e2->pos_y))
          {
            e2->action_flags |= ENTITY_ACTION_FLAG_CASTING;
          }
          /* firing up */
          else if ( (ENTITY_FACING_CHECK(e1, ENTITY_FACING_UP)) &&
                    (ENTITY_FACING_CHECK(e2, ENTITY_FACING_UP)) &&
                    (e1->pos_x == e2->pos_x))
          {
            e2->action_flags |= ENTITY_ACTION_FLAG_CASTING;
          }
          /* firing left */
          else if ( (ENTITY_FACING_CHECK(e1, ENTITY_FACING_LEFT)) &&
                    (ENTITY_FACING_CHECK(e2, ENTITY_FACING_LEFT)) &&
                    (e1->pos_y == e2->pos_y))
          {
            e2->action_flags |= ENTITY_ACTION_FLAG_CASTING;
          }
          /* firing down */
          else if ( (ENTITY_FACING_CHECK(e1, ENTITY_FACING_DOWN)) &&
                    (ENTITY_FACING_CHECK(e2, ENTITY_FACING_DOWN)) &&
                    (e1->pos_x == e2->pos_x))
          {
            e2->action_flags |= ENTITY_ACTION_FLAG_CASTING;
          }
        }
      }
    }
  }

  /* check for contact with wisp */
  if (e1->trigger_affect & ENTITY_TRIGGER_FLAG_WISPS)
  {
    for (i = 0; i < 2; i++)
    {
      for (j = 0; j < sp[i]->num_entities; j++)
      {
        e2 = sp[i]->entities[j];

        if (e2->trigger_attribute & ENTITY_TRIGGER_FLAG_WISPS)
        {
          if (!(e2->update_flags & ENTITY_UPDATE_FLAG_COOLDOWN))
          {
            e2->update_flags |= ENTITY_UPDATE_FLAG_COOLDOWN;
            e2->cooldown_count = ENTITY_COOLDOWN_TIME_WISP;
            animation_setup(e2);
            doremi_play_sfx(SFX_INDEX_WISP_ANGERED);
          }
        }
      }
    }
  }

  /* check for contact with jiangshi */
  if (e1->trigger_affect & ENTITY_TRIGGER_FLAG_JIANGSHIS)
  {
    for (i = 0; i < 2; i++)
    {
      for (j = 0; j < sp[i]->num_entities; j++)
      {
        e2 = sp[i]->entities[j];

        if (e2->trigger_attribute & ENTITY_TRIGGER_FLAG_JIANGSHIS)
        {
          if (!(e2->update_flags & ENTITY_UPDATE_FLAG_ACTIVE))
          {
            e2->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
            animation_setup(e2);
            doremi_play_sfx(SFX_INDEX_JIANGSHI_STOP);
          }
        }
      }
    }
  }

  /* check for contact with player */
  if (e1->trigger_affect & ENTITY_TRIGGER_FLAG_PLAYER)
  {
    for (i = 0; i < 2; i++)
    {
      for (j = 0; j < sp[i]->num_entities; j++)
      {
        e2 = sp[i]->entities[j];

        if (e2->trigger_attribute & ENTITY_TRIGGER_FLAG_PLAYER)
        {
          /* imps destroy player on contact */
          if ((e1->type == ENTITY_TYPE_IMP_LT) ||
              (e1->type == ENTITY_TYPE_IMP_RT))
          {
            if (e1->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
            {
              e2->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
            }
          }
          /* jiangshis activate (stop) when player is touched */
          else if ( (e1->type == ENTITY_TYPE_JIANGSHI_LT) ||
                    (e1->type == ENTITY_TYPE_JIANGSHI_RT))
          {
            if (!(e1->update_flags & ENTITY_UPDATE_FLAG_ACTIVE))
            {
              e1->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
              animation_setup(e1);
              doremi_play_sfx(SFX_INDEX_JIANGSHI_STOP);
            }
          }
        }
      }
    }
  }

  /* check for spell moving into reflecter */
  if (e1->trigger_affect & ENTITY_TRIGGER_FLAG_REFLECTER)
  {
    for (i = 0; i < 2; i++)
    {
      for (j = 0; j < sp[i]->num_entities; j++)
      {
        e2 = sp[i]->entities[j];

        if (e2->trigger_attribute & ENTITY_TRIGGER_FLAG_REFLECTER)
          logic_set_reflection_flags(e1, e2);
      }
    }
  }

  /* check for reflecter moving into spell */
  if (e1->trigger_attribute & ENTITY_TRIGGER_FLAG_REFLECTER)
  {
    for (i = 0; i < 2; i++)
    {
      for (j = 0; j < sp[i]->num_entities; j++)
      {
        e2 = sp[i]->entities[j];

        if (e2->trigger_affect & ENTITY_TRIGGER_FLAG_REFLECTER)
        {
          if (((direction == ENTITY_DIRECTION_RIGHT) &&
              (ENTITY_DIRECTION_CHECK(e2, ENTITY_DIRECTION_LEFT)))  ||
              ((direction == ENTITY_DIRECTION_UP) &&
              (ENTITY_DIRECTION_CHECK(e2, ENTITY_DIRECTION_DOWN)))  ||
              ((direction == ENTITY_DIRECTION_LEFT) &&
              (ENTITY_DIRECTION_CHECK(e2, ENTITY_DIRECTION_RIGHT))) ||
              ((direction == ENTITY_DIRECTION_DOWN) &&
              (ENTITY_DIRECTION_CHECK(e2, ENTITY_DIRECTION_UP))))
          {
            logic_set_reflection_flags(e2, e1);
            e2->special_flags |= ENTITY_SPECIAL_FLAG_OVERLAP;
          }
        }
      }
    }
  }

  /* if entity was reflected, cancel move this frame */
  if ((e1->special_flags & ENTITY_SPECIAL_FLAG_REFLECT_REVERSE) ||
      (e1->special_flags & ENTITY_SPECIAL_FLAG_REFLECT_BANK))
  {
    return 0;
  }

  /* check for damage due to collision */
  for (i = 0; i < 2; i++)
  {
    for (j = 0; j < sp[i]->num_entities; j++)
    {
      e2 = sp[i]->entities[j];

      /* check for damage done by this entity to another entity */
      /* also check for reciprocal damage                       */
      if ((e1->damage_affect & e2->damage_attribute)  ||
          (e2->damage_affect & e1->damage_attribute))
      {
        /* if entities are moving in same direction,  */
        /* and the 1st will not overtake the 2nd,     */
        /* this does not count as a collision         */
        if ((e2->action_flags & ENTITY_ACTION_FLAG_MOVING) && 
            (ENTITY_DIRECTION_CHECK(e2, direction)))
        {
          if (e2->orientation & ENTITY_SPEED_FLAG)
            continue;

          if ((!(e1->orientation & ENTITY_SPEED_FLAG))  &&
              (!(e2->orientation & ENTITY_SPEED_FLAG)))
            continue;
        }

        /* if these entities were involved in a successful  */
        /* reflection, this does not count as a collision   */
        if ((e1->trigger_attribute & ENTITY_TRIGGER_FLAG_REFLECTER) &&
            (e2->trigger_affect & ENTITY_TRIGGER_FLAG_REFLECTER))
        {
          if ((e2->special_flags & ENTITY_SPECIAL_FLAG_REFLECT_REVERSE) ||
              (e2->special_flags & ENTITY_SPECIAL_FLAG_REFLECT_BANK))
            continue;
        }

        /* if the 2nd entity is a spell that is not currently   */
        /* moving, but is set to move away from the 1st entity, */
        /* this does not count as a collision                   */
        if ((ENTITY_TYPE_IS_SPELL(e2->type)) && 
            (!(e2->action_flags & ENTITY_ACTION_FLAG_MOVING)))
        {
          if (ENTITY_DIRECTION_CHECK(e2, direction))
            continue;
        }

        pair_trees_and_lists_add_collision(e1, e2);
      }
    }
  }

  /* double check if movement was blocked by a lever, */
  /* a ballista, a wisp, a jiangshi, the player, a    */
  /* reflecter/spell, or by a damaging collision      */
  for (i = 0; i < 2; i++)
  {
    for (j = 0; j < sp[i]->num_entities; j++)
    {
      e2 = sp[i]->entities[j];

      /* lever */
      if ((e1->trigger_affect & ENTITY_TRIGGER_FLAG_LEVERS) && 
          (e2->trigger_attribute & ENTITY_TRIGGER_FLAG_LEVERS))
      {
        if (e1->move_attribute & e2->move_affect)
          return 0;
      }

      /* ballista */
      if ((e1->trigger_affect & ENTITY_TRIGGER_FLAG_BALLISTAS) && 
          (e2->trigger_attribute & ENTITY_TRIGGER_FLAG_BALLISTAS))
      {
        if (e1->move_attribute & e2->move_affect)
          return 0;
      }

      /* wisp */
      if ((e1->trigger_affect & ENTITY_TRIGGER_FLAG_WISPS) && 
          (e2->trigger_attribute & ENTITY_TRIGGER_FLAG_WISPS))
      {
        if (e1->move_attribute & e2->move_affect)
          return 0;
      }

      /* jiangshi */
      if ((e1->trigger_affect & ENTITY_TRIGGER_FLAG_JIANGSHIS) && 
          (e2->trigger_attribute & ENTITY_TRIGGER_FLAG_JIANGSHIS))
      {
        if (e1->move_attribute & e2->move_affect)
          return 0;
      }

      /* player */
      if ((e1->trigger_affect & ENTITY_TRIGGER_FLAG_PLAYER) && 
          (e2->trigger_attribute & ENTITY_TRIGGER_FLAG_PLAYER))
      {
        if (e1->move_attribute & e2->move_affect)
          return 0;
      }

      /* spell moving into reflecter */
      if ((e1->trigger_affect & ENTITY_TRIGGER_FLAG_REFLECTER) && 
          (e2->trigger_attribute & ENTITY_TRIGGER_FLAG_REFLECTER))
      {
        if (e1->move_attribute & e2->move_affect)
          return 0;
      }

      /* reflecter moving into spell */
      if ((e1->trigger_attribute & ENTITY_TRIGGER_FLAG_REFLECTER) && 
          (e2->trigger_affect & ENTITY_TRIGGER_FLAG_REFLECTER))
      {
        if ((e1->move_attribute & e2->move_affect) &&
            (!(e2->special_flags & ENTITY_SPECIAL_FLAG_REFLECT_REVERSE)) &&
            (!(e2->special_flags & ENTITY_SPECIAL_FLAG_REFLECT_BANK)))
          return 0;
      }

      /* damaging collision */
      if ((e1->damage_affect & e2->damage_attribute)  ||
          (e2->damage_affect & e1->damage_attribute))
      {
        /* special case - pushable object breaking floor spikes */
        if (ENTITY_TYPE_IS_SPIKE_DESTROYING(e1->type))
        {
          if (ENTITY_TYPE_IS_FLOOR_SPIKE_UP(e2->type))
          {
            continue;
          }
        }

        if (e1->move_attribute & e2->move_affect)
          return 0;
      }
    }
  }

  /* otherwise, move should be successful */
  e1->action_flags |= ENTITY_ACTION_FLAG_MOVING;
  e1->vel_x = 0;
  e1->vel_y = 0;

  /* set rolling flag for eight ball */
  if ((e1->type == ENTITY_TYPE_EIGHT_BALL) &&
      (!(e1->action_flags & ENTITY_ACTION_FLAG_BEING_CONVEYED)))
  {
    e1->special_flags |= ENTITY_SPECIAL_FLAG_ROLLING;
  }

  /* clear conveyance flag (will be re-set after this         */
  /* function call if the entity is actually being conveyed)  */
  if (e1->action_flags & ENTITY_ACTION_FLAG_BEING_CONVEYED)
    e1->action_flags &= ~ENTITY_ACTION_FLAG_BEING_CONVEYED;

  /* set movement speed based on speed flag */
  if (e1->orientation & ENTITY_SPEED_FLAG)
  {
    if (direction == ENTITY_DIRECTION_RIGHT)
      e1->vel_x = 4;
    else if (direction == ENTITY_DIRECTION_UP)
      e1->vel_y = -4;
    else if (direction == ENTITY_DIRECTION_LEFT)
      e1->vel_x = -4;
    else if (direction == ENTITY_DIRECTION_DOWN)
      e1->vel_y = 4;

    e1->move_count = 4;
  }
  else
  {
    if (direction == ENTITY_DIRECTION_RIGHT)
      e1->vel_x = 2;
    else if (direction == ENTITY_DIRECTION_UP)
      e1->vel_y = -2;
    else if (direction == ENTITY_DIRECTION_LEFT)
      e1->vel_x = -2;
    else if (direction == ENTITY_DIRECTION_DOWN)
      e1->vel_y = 2;

    e1->move_count = 8;
  }

  /* set entity direction */
  e1->orientation &= ~ENTITY_DIRECTION_MASK;
  e1->orientation |= direction;

  /* reserve this entity's position in adjacent grid spaces */
  e1->update_flags |= ENTITY_UPDATE_FLAG_STARTED_MOVEMENT;

  for (i = 0; i < 2; i++)
  {
    if (sp[i]->num_entities >= sp[i]->max_entities)
    {
      sp[i]->max_entities += COLLIDE_GRID_SPACE_RESIZE_NUM;
      sp[i]->entities = realloc(sp[i]->entities, 
                                sp[i]->max_entities * sizeof(entity*));

      if (sp[i]->entities == NULL)
      {
        sp[i]->num_entities = 0;
        sp[i]->max_entities = 0;
        return 1;
      }
    }

    sp[i]->entities[sp[i]->num_entities] = e1;
    sp[i]->num_entities += 1;
  }

  /* reserve extra spaces, if necessary */
  if (e1->update_flags & ENTITY_UPDATE_FLAG_MOVING_INTO_WATER)
  {
    for (i = 0; i < 2; i++)
    {
      if (extra_sp[i] == NULL)
        continue;

      if (extra_sp[i]->num_entities >= extra_sp[i]->max_entities)
      {
        extra_sp[i]->max_entities += COLLIDE_GRID_SPACE_RESIZE_NUM;
        extra_sp[i]->entities = 
          realloc(extra_sp[i]->entities, 
                  extra_sp[i]->max_entities * sizeof(entity*));

        if (extra_sp[i]->entities == NULL)
        {
          extra_sp[i]->num_entities = 0;
          extra_sp[i]->max_entities = 0;
          return 1;
        }
      }

      extra_sp[i]->entities[extra_sp[i]->num_entities] = e1;
      extra_sp[i]->num_entities += 1;
    }
  }

  return 0;
}

/*******************************************************************************
** logic_player_key_move()
*******************************************************************************/
short int logic_player_key_move(unsigned char direction)
{
  entity*       e;
  unsigned char facing;
  unsigned char reverse_direction;
  unsigned char reverse_facing;

  /* set facing, reverse direction, reverse facing based on direction */
  if (direction == ENTITY_DIRECTION_RIGHT)
  {
    facing = ENTITY_FACING_RIGHT;
    reverse_direction = ENTITY_DIRECTION_LEFT;
    reverse_facing = ENTITY_FACING_LEFT;
  }
  else if (direction == ENTITY_DIRECTION_UP)
  {
    facing = ENTITY_FACING_UP;
    reverse_direction = ENTITY_DIRECTION_DOWN;
    reverse_facing = ENTITY_FACING_DOWN;
  }
  else if (direction == ENTITY_DIRECTION_LEFT)
  {
    facing = ENTITY_FACING_LEFT;
    reverse_direction = ENTITY_DIRECTION_RIGHT;
    reverse_facing = ENTITY_FACING_RIGHT;
  }
  else if (direction == ENTITY_DIRECTION_DOWN)
  {
    facing = ENTITY_FACING_DOWN;
    reverse_direction = ENTITY_DIRECTION_UP;
    reverse_facing = ENTITY_FACING_UP;
  }
  else
    return 0;

  /* player movement */
  if (G_player == NULL)
    return 0;

  /* make sure player is not already moving, or in cooldown */
  if (ENTITY_IS_PERFORMING_ACTION(G_player) ||
      ENTITY_IS_IN_COOLDOWN(G_player))
  {
    return 0;
  }

  /* moving in a new direction */
  if (!(ENTITY_FACING_CHECK(G_player, facing)))
  {
    entity_set_facing(G_player, facing);
    logic_attempt_move(G_player, direction);
    animation_setup(G_player);
  }
  /* moving in the same direction */
  else
  {
    logic_attempt_move(G_player, direction);

    /* if player started pushing this frame, setup animation */
    if ((G_player->action_flags & ENTITY_ACTION_FLAG_PUSHING)    && 
        (!(G_player->animation_flags & ENTITY_ANIMATION_FLAG_CARRY_OVER)))
    {
      animation_setup(G_player);
    }
  }

  /* cycle through doubles */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_DOUBLES];
        e != NULL;
        e = e->next)
  {
    /* make sure double is not already moving, or in cooldown */
    if (ENTITY_IS_PERFORMING_ACTION(e) ||
        ENTITY_IS_IN_COOLDOWN(e))
    {
      continue;
    }

    /* if player did not successfully move, only set facing */
    if (!(G_player->action_flags & ENTITY_ACTION_FLAG_MOVING))
    {
      if (!(ENTITY_FACING_CHECK(e, facing)))
      {
        entity_set_facing(e, facing);
        animation_setup(e);
      }

      continue;
    }

    /* moving in a new direction */
    if (!(ENTITY_FACING_CHECK(e, facing)))
    {
      entity_set_facing(e, facing);
      logic_attempt_move(e, direction);
      animation_setup(e);
    }
    /* moving in the same direction */
    else
    {
      logic_attempt_move(e, direction);

      /* if double started pushing this frame, setup animation */
      if ((e->action_flags & ENTITY_ACTION_FLAG_PUSHING)    && 
          (!(e->animation_flags & ENTITY_ANIMATION_FLAG_CARRY_OVER)))
      {
        animation_setup(e);
      }
    }
  }

  /* cycle through reverse doubles */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_REVERSE_DOUBLES];
        e != NULL;
        e = e->next)
  {
    /* make sure reverse double is not already moving, or in cooldown */
    if (ENTITY_IS_PERFORMING_ACTION(e) ||
        ENTITY_IS_IN_COOLDOWN(e))
    {
      continue;
    }

    /* if player did not successfully move, only set facing */
    if (!(G_player->action_flags & ENTITY_ACTION_FLAG_MOVING))
    {
      if (!(ENTITY_FACING_CHECK(e, reverse_facing)))
      {
        entity_set_facing(e, reverse_facing);
        animation_setup(e);
      }

      continue;
    }

    /* moving in a new direction */
    if (!(ENTITY_FACING_CHECK(e, reverse_facing)))
    {
      entity_set_facing(e, reverse_facing);
      logic_attempt_move(e, reverse_direction);
      animation_setup(e);
    }
    /* moving in the same direction */
    else
    {
      logic_attempt_move(e, reverse_direction);

      /* if double started pushing this frame, setup animation */
      if ((e->action_flags & ENTITY_ACTION_FLAG_PUSHING)    && 
          (!(e->animation_flags & ENTITY_ANIMATION_FLAG_CARRY_OVER)))
      {
        animation_setup(e);
      }
    }
  }

  return 0;
}

/*******************************************************************************
** logic_player_key_turn()
*******************************************************************************/
short int logic_player_key_turn(unsigned char facing)
{
  entity*       e;
  unsigned char reverse_facing;

  /* set reverse facing based on facing */
  if (facing == ENTITY_FACING_RIGHT)
    reverse_facing = ENTITY_FACING_LEFT;
  else if (facing == ENTITY_FACING_UP)
    reverse_facing = ENTITY_FACING_DOWN;
  else if (facing == ENTITY_FACING_LEFT)
    reverse_facing = ENTITY_FACING_RIGHT;
  else if (facing == ENTITY_FACING_DOWN)
    reverse_facing = ENTITY_FACING_UP;
  else
    return 0;

  /* player turning */
  if (G_player == NULL)
    return 0;

  /* make sure player is not already moving, or in cooldown */
  if (ENTITY_IS_PERFORMING_ACTION(G_player) ||
      ENTITY_IS_IN_COOLDOWN(G_player))
  {
    return 0;
  }

  /* if not turning to a new direction, return */
  if (ENTITY_FACING_CHECK(G_player, facing))
    return 0;

  /* set new facing */
  entity_set_facing(G_player, facing);
  animation_setup(G_player);

  /* cycle through doubles */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_DOUBLES];
        e != NULL;
        e = e->next)
  {
    /* make sure double is not already moving, or in cooldown */
    if (ENTITY_IS_PERFORMING_ACTION(e) ||
        ENTITY_IS_IN_COOLDOWN(e))
    {
      continue;
    }

    /* set new facing */
    entity_set_facing(e, facing);
    animation_setup(e);
  }

  /* cycle through reverse doubles */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_REVERSE_DOUBLES];
        e != NULL;
        e = e->next)
  {
    /* make sure reverse double is not already moving, or in cooldown */
    if (ENTITY_IS_PERFORMING_ACTION(e) ||
        ENTITY_IS_IN_COOLDOWN(e))
    {
      continue;
    }

    /* set new facing */
    entity_set_facing(e, reverse_facing);
    animation_setup(e);
  }

  return 0;
}

/*******************************************************************************
** logic_check_if_over_joker_card()
*******************************************************************************/
short int logic_check_if_over_joker_card(entity* e1)
{
  int                 i;
  int                 low_x;
  int                 low_y;
  collide_grid_space* sp;
  entity*             e2;

  if (e1 == NULL)
    return 1;

  /* make sure entity is a player or enemy vampire or bat */
  if (!(ENTITY_TYPE_IS_PLAYER_OR_DOUBLE(e1->type)))
    return 0;

  /* make sure entity is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
    return 0;

  /* determine location of entity in grid */
  low_x = (e1->pos_x / 16) - 2;
  low_y = (e1->pos_y / 16) - 4;

  /* make sure entity is within the grid */
  if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  /* set space to check */
  sp = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);

  /* check space */
  for (i = 0; i < sp->num_entities; i++)
  {
    e2 = sp->entities[i];

    if (e1 == e2)
      continue;

    if ((e1->pos_x != e2->pos_x) || (e1->pos_y != e2->pos_y))
      continue;

    /* if a vampire is over a joker card, prevent bat transformation  */
    /* if a bat is over a joker card, transform back to vampire       */
    if (e2->type == ENTITY_TYPE_JOKER_CARD)
    {
      if (ENTITY_TYPE_IS_VAMPIRE(e1->type))
        e1->update_flags &= ~ENTITY_UPDATE_FLAG_TRANSFORMING;
      else if (ENTITY_TYPE_IS_BAT(e1->type))
        e1->update_flags |= ENTITY_UPDATE_FLAG_TRANSFORMING;

      return 0;
    }
  }

  return 0;
}

/*******************************************************************************
** logic_attempt_transform()
*******************************************************************************/
short int logic_attempt_transform(entity* e)
{
  int                 i;
  int                 m;
  int                 n;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp;

  /* if entity does not exist, return */
  if (e == NULL)
    return 0;

  /* make sure this entity can transform */
  if (!(ENTITY_TYPE_IS_PLAYER_OR_DOUBLE(e->type)))
    return 0;

  /* determine location of entity in grid */
  low_x = ((e->pos_x - e->rx) / 16) - 1;
  high_x = ((e->pos_x + e->rx - 1) / 16) - 1;

  low_y = ((e->pos_y - e->ry) / 16) - 3;
  high_y = ((e->pos_y + e->ry - 1) / 16) - 3;

  /* make sure entity is within the grid */
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

  /* check for entities that would block the new entity */
  for (m = low_x; m <= high_x; m++)
  {
    for (n = low_y; n <= high_y; n++)
    {
      sp = &(G_collide_grid[m * COLLIDE_GRID_HEIGHT + n]);

      for (i = 0; i < sp->num_entities; i++)
      {
        if (sp->entities[i] == e)
          continue;

        if ((e->type == ENTITY_TYPE_PLAYER_BAT)                       &&
            (sp->entities[i]->move_affect & ENTITY_MOVE_FLAG_VAMPIRE) &&
            (!(ENTITY_TYPE_IS_ARROWS(sp->entities[i]->type))))
          return 0;

        if ((e->type == ENTITY_TYPE_PLAYER_VAMPIRE)                       &&
            (sp->entities[i]->move_affect & ENTITY_MOVE_FLAG_PLAYER_BAT)  &&
            (!(ENTITY_TYPE_IS_ARROWS(sp->entities[i]->type))))
          return 0;

        if ((e->type == ENTITY_TYPE_DOUBLE_BAT)                     &&
            (sp->entities[i]->move_affect & ENTITY_MOVE_FLAG_ENEMY) &&
            (!(ENTITY_TYPE_IS_ARROWS(sp->entities[i]->type))))
          return 0;

        if ((e->type == ENTITY_TYPE_DOUBLE_VAMPIRE)                     &&
            (sp->entities[i]->move_affect & ENTITY_MOVE_FLAG_ENEMY_BAT) &&
            (!(ENTITY_TYPE_IS_ARROWS(sp->entities[i]->type))))
          return 0;

        if ((e->type == ENTITY_TYPE_REVERSE_DOUBLE_BAT)             &&
            (sp->entities[i]->move_affect & ENTITY_MOVE_FLAG_ENEMY) &&
            (!(ENTITY_TYPE_IS_ARROWS(sp->entities[i]->type))))
          return 0;

        if ((e->type == ENTITY_TYPE_REVERSE_DOUBLE_VAMPIRE)             &&
            (sp->entities[i]->move_affect & ENTITY_MOVE_FLAG_ENEMY_BAT) &&
            (!(ENTITY_TYPE_IS_ARROWS(sp->entities[i]->type))))
          return 0;
      }
    }
  }

  /* set transforming flag */
  e->update_flags |= ENTITY_UPDATE_FLAG_TRANSFORMING;

  /* prevent bat transformation if vampire is over joker card */
  if (ENTITY_TYPE_IS_VAMPIRE(e->type))
  {
    logic_check_if_over_joker_card(e);
  }

  return 0;
}

/*******************************************************************************
** logic_player_key_bat_transform()
*******************************************************************************/
short int logic_player_key_bat_transform()
{
  entity* e;

  if (G_player == NULL)
    return 0;

  /* make sure player is not already moving, or in cooldown */
  if (ENTITY_IS_PERFORMING_ACTION(G_player) ||
      ENTITY_IS_IN_COOLDOWN(G_player))
  {
    return 0;
  }

  /* vampire to bat */
  if ((G_player->type == ENTITY_TYPE_PLAYER_VAMPIRE) &&
      (G_bat_transforms > 0))
  {
    logic_attempt_transform(G_player);

    /* if transform was successful, use a bat vial and transform doubles */
    if (G_player->update_flags & ENTITY_UPDATE_FLAG_TRANSFORMING)
    {
      for ( e = G_entity_active_list_head[CATEGORY_INDEX_DOUBLES];
            e != NULL;
            e = e->next)
      {
        /* make sure double is not already moving, or in cooldown */
        if (ENTITY_IS_PERFORMING_ACTION(e) ||
            ENTITY_IS_IN_COOLDOWN(e))
        {
          continue;
        }

        if (e->type == ENTITY_TYPE_DOUBLE_VAMPIRE)
          logic_attempt_transform(e);
      }

      for ( e = G_entity_active_list_head[CATEGORY_INDEX_REVERSE_DOUBLES];
            e != NULL;
            e = e->next)
      {
        /* make sure reverse double is not already moving, or in cooldown */
        if (ENTITY_IS_PERFORMING_ACTION(e) ||
            ENTITY_IS_IN_COOLDOWN(e))
        {
          continue;
        }

        if (e->type == ENTITY_TYPE_REVERSE_DOUBLE_VAMPIRE)
          logic_attempt_transform(e);
      }

      G_bat_transforms -= 1;
    }
    else
      return 0;
  }
  /* bat to vampire */
  else if (G_player->type == ENTITY_TYPE_PLAYER_BAT)
  {
    logic_attempt_transform(G_player);

    /* if transform was successful, transform doubles */
    if (G_player->update_flags & ENTITY_UPDATE_FLAG_TRANSFORMING)
    {
      for ( e = G_entity_active_list_head[CATEGORY_INDEX_DOUBLES];
            e != NULL;
            e = e->next)
      {
        /* make sure double is not already moving, or in cooldown */
        if (ENTITY_IS_PERFORMING_ACTION(e) ||
            ENTITY_IS_IN_COOLDOWN(e))
        {
          continue;
        }

        if (e->type == ENTITY_TYPE_DOUBLE_BAT)
          logic_attempt_transform(e);
      }

      for ( e = G_entity_active_list_head[CATEGORY_INDEX_REVERSE_DOUBLES];
            e != NULL;
            e = e->next)
      {
        /* make sure reverse double is not already moving, or in cooldown */
        if (ENTITY_IS_PERFORMING_ACTION(e) ||
            ENTITY_IS_IN_COOLDOWN(e))
        {
          continue;
        }

        if (e->type == ENTITY_TYPE_REVERSE_DOUBLE_BAT)
          logic_attempt_transform(e);
      }
    }
    else
      return 0;
  }
  else
    return 0;

  return 0;
}

/*******************************************************************************
** logic_player_key_ice_spell()
*******************************************************************************/
short int logic_player_key_ice_spell()
{
  entity* e;

  if (G_player == NULL)
    return 0;

  /* cast ice spell */
  if ((G_player->type == ENTITY_TYPE_PLAYER_VAMPIRE) &&
      (G_blue_mana > 0))
  {
    /* see if the player can cast an ice spell */
    if (!(ENTITY_IS_PERFORMING_ACTION(G_player) ||
          ENTITY_IS_IN_COOLDOWN(G_player)))
    {
      G_player->action_flags |= ENTITY_ACTION_FLAG_CASTING;
      G_blue_mana -= 1;
    }

    /* if cast was successful, use a blue mana and set doubles to cast */
    if (G_player->action_flags & ENTITY_ACTION_FLAG_CASTING)
    {
      for ( e = G_entity_active_list_head[CATEGORY_INDEX_DOUBLES];
            e != NULL;
            e = e->next)
      {
        /* make sure double is not already moving, or in cooldown */
        if (ENTITY_IS_PERFORMING_ACTION(e) ||
            ENTITY_IS_IN_COOLDOWN(e))
        {
          continue;
        }

        if (e->type == ENTITY_TYPE_DOUBLE_VAMPIRE)
          e->action_flags |= ENTITY_ACTION_FLAG_CASTING;
      }

      for ( e = G_entity_active_list_head[CATEGORY_INDEX_REVERSE_DOUBLES];
            e != NULL;
            e = e->next)
      {
        /* make sure reverse double is not already moving, or in cooldown */
        if (ENTITY_IS_PERFORMING_ACTION(e) ||
            ENTITY_IS_IN_COOLDOWN(e))
        {
          continue;
        }

        if (e->type == ENTITY_TYPE_REVERSE_DOUBLE_VAMPIRE)
          e->action_flags |= ENTITY_ACTION_FLAG_CASTING;
      }
    }
    else
      return 0;
  }

  return 0;
}

/*******************************************************************************
** logic_player_key_warp_spell()
*******************************************************************************/
short int logic_player_key_warp_spell()
{
  entity* e;

  if (G_player == NULL)
    return 0;

  /* cast warp spell */
  if ((G_player->type == ENTITY_TYPE_PLAYER_VAMPIRE) &&
      (G_green_mana > 0))
  {
    /* see if the player can cast a warp spell */
    if (!(ENTITY_IS_PERFORMING_ACTION(G_player) ||
          ENTITY_IS_IN_COOLDOWN(G_player)))
    {
      G_player->action_flags |= ENTITY_ACTION_FLAG_CASTING;
      G_player->action_flags |= ENTITY_ACTION_FLAG_MODE;
      G_green_mana -= 1;
    }

    /* if cast was successful, use a green mana and set doubles to cast */
    if (G_player->action_flags & ENTITY_ACTION_FLAG_CASTING)
    {
      for ( e = G_entity_active_list_head[CATEGORY_INDEX_DOUBLES];
            e != NULL;
            e = e->next)
      {
        /* make sure double is not already moving, or in cooldown */
        if (ENTITY_IS_PERFORMING_ACTION(e) ||
            ENTITY_IS_IN_COOLDOWN(e))
        {
          continue;
        }

        if (e->type == ENTITY_TYPE_DOUBLE_VAMPIRE)
        {
          e->action_flags |= ENTITY_ACTION_FLAG_CASTING;
          e->action_flags |= ENTITY_ACTION_FLAG_MODE;
        }
      }

      for ( e = G_entity_active_list_head[CATEGORY_INDEX_REVERSE_DOUBLES];
            e != NULL;
            e = e->next)
      {
        /* make sure reverse double is not already moving, or in cooldown */
        if (ENTITY_IS_PERFORMING_ACTION(e) ||
            ENTITY_IS_IN_COOLDOWN(e))
        {
          continue;
        }

        if (e->type == ENTITY_TYPE_REVERSE_DOUBLE_VAMPIRE)
        {
          e->action_flags |= ENTITY_ACTION_FLAG_CASTING;
          e->action_flags |= ENTITY_ACTION_FLAG_MODE;
        }
      }
    }
    else
      return 0;
  }

  return 0;
}

/*******************************************************************************
** logic_set_enemy_animations_based_on_player_position()
*******************************************************************************/
short int logic_set_enemy_animations_based_on_player_position()
{
  entity*       e;
  int           original_frame_count;
  unsigned char desired_facing;

  /* if player does not exist, return */
  if (G_player == NULL)
    return 0;

  /* make sure faeries are facing the player */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_SNAKES_FAERIES_VENUSIANS];
        e != NULL;
        e = e->next)
  {
    if (e->type == ENTITY_TYPE_FAERIE_HORIZONTAL)
    {
      if ((e->pos_y < G_player->pos_y) && 
          (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP)))
      {
        entity_set_facing(e, ENTITY_FACING_DOWN);
        animation_setup(e);
      }
      else if ( (e->pos_y > G_player->pos_y) && 
                (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN)))
      {
        entity_set_facing(e, ENTITY_FACING_UP);
        animation_setup(e);
      }
    }
    else if (e->type == ENTITY_TYPE_FAERIE_VERTICAL)
    {
      if ((e->pos_x < G_player->pos_x) && 
          (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT)))
      {
        entity_set_facing(e, ENTITY_FACING_RIGHT);
        animation_setup(e);
      }
      else if ( (e->pos_x > G_player->pos_x) && 
                (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT)))
      {
        entity_set_facing(e, ENTITY_FACING_LEFT);
        animation_setup(e);
      }
    }
  }

  /* pumpkins, masks active/inactive based on player position */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_PUMPKINS_GHOSTS_MASKS];
        e != NULL;
        e = e->next)
  {
    if (e->type == ENTITY_TYPE_PUMPKIN)
    {
      /* if player is frozen, pumpkins should remain inactive */
      if ((G_player->type == ENTITY_TYPE_PLAYER_VAMPIRE) ||
          (G_player->type == ENTITY_TYPE_PLAYER_BAT))
      {
        /* check if pumpkin and player are lined up vertically or horizontally */
        if (((e->pos_x - G_player->pos_x < 32)    &&
            (e->pos_x - G_player->pos_x > -32))   ||
            ((e->pos_y - G_player->pos_y < 32)    &&
            (e->pos_y - G_player->pos_y > -32)))
        {
          if (!(e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE))
          {
            e->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
            animation_setup(e);
          }
        }
        else if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
        {
          e->update_flags &= ~ENTITY_UPDATE_FLAG_ACTIVE;
          animation_setup(e);
        }
      }
      else if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
      {
        e->update_flags &= ~ENTITY_UPDATE_FLAG_ACTIVE;
        animation_setup(e);
      }
    }
    else if ( (e->type == ENTITY_TYPE_MASK_HORIZONTAL)  ||
              (e->type == ENTITY_TYPE_MASK_VERTICAL))
    {
      /* if player is frozen, masks should remain inactive */
      if ((G_player->type == ENTITY_TYPE_PLAYER_VAMPIRE) ||
          (G_player->type == ENTITY_TYPE_PLAYER_BAT))
      {
        /* check if mask and player are lined up vertically or horizontally */
        if (((e->pos_x - G_player->pos_x < 32)    &&
            (e->pos_x - G_player->pos_x > -32))   ||
            ((e->pos_y - G_player->pos_y < 32)    &&
            (e->pos_y - G_player->pos_y > -32)))
        {
          if (!(e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE))
          {
            original_frame_count = e->frame_count;
            e->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
            animation_setup(e);
            e->frame_count = original_frame_count;
          }
        }
        else if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
        {
          original_frame_count = e->frame_count;
          e->update_flags &= ~ENTITY_UPDATE_FLAG_ACTIVE;
          animation_setup(e);
          e->frame_count = original_frame_count;
        }
      }
      else if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
      {
        original_frame_count = e->frame_count;
        e->update_flags &= ~ENTITY_UPDATE_FLAG_ACTIVE;
        animation_setup(e);
        e->frame_count = original_frame_count;
      }
    }
  }

  /* frogs active/inactive based on player position */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_LIL_BOTS_WISPS_FROGS];
        e != NULL;
        e = e->next)
  {
    if (e->type == ENTITY_TYPE_FROG)
    {
      /* if player is frozen, frogs should remain inactive */
      if ((G_player->type == ENTITY_TYPE_PLAYER_VAMPIRE) ||
          (G_player->type == ENTITY_TYPE_PLAYER_BAT))
      {
        /* check if frog and player are lined up */
        if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT)       &&
            (e->pos_y - G_player->pos_y < 16)                 &&
            (e->pos_y - G_player->pos_y > -16)                &&
            (e->pos_x < G_player->pos_x))
        {
          if (!(e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE))
          {
            e->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
            entity_set_facing(e, ENTITY_FACING_RIGHT);
            doremi_play_sfx(SFX_INDEX_FROG_ACTIVATE);
          }
        }
        else if ( ENTITY_FACING_CHECK(e, ENTITY_FACING_UP)    &&
                  (e->pos_x - G_player->pos_x < 16)           &&
                  (e->pos_x - G_player->pos_x > -16)          &&
                  (e->pos_y > G_player->pos_y))
        {
          if (!(e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE))
          {
            e->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
            entity_set_facing(e, ENTITY_FACING_UP);
            doremi_play_sfx(SFX_INDEX_FROG_ACTIVATE);
          }
        }
        else if ( ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT)  &&
                  (e->pos_y - G_player->pos_y < 16)           &&
                  (e->pos_y - G_player->pos_y > -16)          &&
                  (e->pos_x > G_player->pos_x))
        {
          if (!(e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE))
          {
            e->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
            entity_set_facing(e, ENTITY_FACING_LEFT);
            doremi_play_sfx(SFX_INDEX_FROG_ACTIVATE);
          }
        }
        else if ( ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN)  &&
                  (e->pos_x - G_player->pos_x < 16)           &&
                  (e->pos_x - G_player->pos_x > -16)          &&
                  (e->pos_y < G_player->pos_y))
        {
          if (!(e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE))
          {
            e->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
            entity_set_facing(e, ENTITY_FACING_DOWN);
            doremi_play_sfx(SFX_INDEX_FROG_ACTIVATE);
          }
        }
        else if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
        {
          e->update_flags &= ~ENTITY_UPDATE_FLAG_ACTIVE;
          entity_set_facing(e, e->orientation & ENTITY_FACING_MASK);
        }
      }
      else if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
      {
        e->update_flags &= ~ENTITY_UPDATE_FLAG_ACTIVE;
        entity_set_facing(e, e->orientation & ENTITY_FACING_MASK);
      }
    }
  }

  /* laser guns rotate based on player position */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_LASER_GUNS];
        e != NULL;
        e = e->next)
  {
    if (e->type == ENTITY_TYPE_LASER_GUN)
    {
      if (ENTITY_IS_PERFORMING_ACTION(e))
        continue;

      desired_facing = ENTITY_FACING_RIGHT;

      /* determine desired laser gun facing */
      if ((G_player->pos_x > e->pos_x) && (G_player->pos_y == e->pos_y))
      {
        desired_facing = ENTITY_FACING_RIGHT;
      }
      else if ((G_player->pos_x > e->pos_x) && (G_player->pos_y < e->pos_y))
      {
        if (G_player->pos_x - e->pos_x <= e->pos_y - G_player->pos_y)
          desired_facing = ENTITY_FACING_UP;
        else
          desired_facing = ENTITY_FACING_RIGHT;
      }
      else if ((G_player->pos_x == e->pos_x) && (G_player->pos_y < e->pos_y))
      {
        desired_facing = ENTITY_FACING_UP;
      }
      else if ((G_player->pos_x < e->pos_x) && (G_player->pos_y < e->pos_y))
      {
        if (e->pos_x - G_player->pos_x <= e->pos_y - G_player->pos_y)
          desired_facing = ENTITY_FACING_UP;
        else
          desired_facing = ENTITY_FACING_LEFT;
      }
      else if ((G_player->pos_x < e->pos_x) && (G_player->pos_y == e->pos_y))
      {
        desired_facing = ENTITY_FACING_LEFT;
      }
      else if ((G_player->pos_x < e->pos_x) && (G_player->pos_y > e->pos_y))
      {
        if (e->pos_x - G_player->pos_x <= G_player->pos_y - e->pos_y)
          desired_facing = ENTITY_FACING_DOWN;
        else
          desired_facing = ENTITY_FACING_LEFT;
      }
      else if ((G_player->pos_x == e->pos_x) && (G_player->pos_y > e->pos_y))
      {
        desired_facing = ENTITY_FACING_DOWN;
      }
      else if ((G_player->pos_x > e->pos_x) && (G_player->pos_y > e->pos_y))
      {
        if (G_player->pos_x - e->pos_x <= G_player->pos_y - e->pos_y)
          desired_facing = ENTITY_FACING_DOWN;
        else
          desired_facing = ENTITY_FACING_RIGHT;
      }

      /* if laser gun is already facing the desired way, continue */
      if (ENTITY_FACING_CHECK(e, desired_facing))
        continue;

      /* begin rotation */
      original_frame_count = e->frame_count;

      if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
      {
        if (desired_facing == ENTITY_FACING_DOWN)
        {
          entity_set_facing(e, ENTITY_FACING_DOWN_RIGHT);
          e->action_flags |= ENTITY_ACTION_FLAG_MODE;
        }
        else
          entity_set_facing(e, ENTITY_FACING_UP_RIGHT);
      }
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
      {
        if (desired_facing == ENTITY_FACING_RIGHT)
        {
          entity_set_facing(e, ENTITY_FACING_UP_RIGHT);
          e->action_flags |= ENTITY_ACTION_FLAG_MODE;
        }
        else
          entity_set_facing(e, ENTITY_FACING_UP_LEFT);
      }
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
      {
        if (desired_facing == ENTITY_FACING_UP)
        {
          entity_set_facing(e, ENTITY_FACING_UP_LEFT);
          e->action_flags |= ENTITY_ACTION_FLAG_MODE;
        }
        else
          entity_set_facing(e, ENTITY_FACING_DOWN_LEFT);
      }
      else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
      {
        if (desired_facing == ENTITY_FACING_LEFT)
        {
          entity_set_facing(e, ENTITY_FACING_DOWN_LEFT);
          e->action_flags |= ENTITY_ACTION_FLAG_MODE;
        }
        else
          entity_set_facing(e, ENTITY_FACING_DOWN_RIGHT);
      }

      animation_setup(e);
      e->frame_count = original_frame_count;

      e->action_flags |= ENTITY_ACTION_FLAG_ROTATING;
      e->spin_count = ENTITY_SPIN_TIME_LASER_GUN;
    }
  }

  return 0;
}

/*******************************************************************************
** logic_attempt_spell_cast()
*******************************************************************************/
short int logic_attempt_spell_cast(entity* e1)
{
  int                 i;
  int                 m;
  int                 n;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp;
  entity*             e2;
  unsigned char       blocked_flag;

  /* if entity or player does not exist, return */
  if ((e1 == NULL) || (G_player == NULL))
    return 0;

  /* make sure entity is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
    return 0;

  /* determine spaces between entities */
  if (ENTITY_FACING_CHECK(e1, ENTITY_FACING_RIGHT))
  {
    low_x = ((e1->pos_x + e1->rx - 1) / 16) - 1 + 1;
    high_x = ((G_player->pos_x - G_player->rx) / 16) - 1 - 1;

    low_y = ((e1->pos_y - e1->ry) / 16) - 3;
    high_y = ((e1->pos_y + e1->ry - 1) / 16) - 3;
  }
  else if (ENTITY_FACING_CHECK(e1, ENTITY_FACING_UP))
  {
    low_x = ((e1->pos_x - e1->rx) / 16) - 1;
    high_x = ((e1->pos_x + e1->rx - 1) / 16) - 1;

    low_y = ((G_player->pos_y + G_player->ry - 1) / 16) - 3 + 1;
    high_y = ((e1->pos_y - e1->ry) / 16) - 3 - 1;
  }
  else if (ENTITY_FACING_CHECK(e1, ENTITY_FACING_LEFT))
  {
    low_x = ((G_player->pos_x + G_player->rx - 1) / 16) - 1 + 1;
    high_x = ((e1->pos_x - e1->rx) / 16) - 1 - 1;

    low_y = ((e1->pos_y - e1->ry) / 16) - 3;
    high_y = ((e1->pos_y + e1->ry - 1) / 16) - 3;
  }
  else if (ENTITY_FACING_CHECK(e1, ENTITY_FACING_DOWN))
  {
    low_x = ((e1->pos_x - e1->rx) / 16) - 1;
    high_x = ((e1->pos_x + e1->rx - 1) / 16) - 1;

    low_y = ((e1->pos_y + e1->ry - 1) / 16) - 3 + 1;
    high_y = ((G_player->pos_y - G_player->ry) / 16) - 3 - 1;
  }
  else
    return 0;

  /* make sure spaces are within the grid */
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

  /* clear blocked flag */
  blocked_flag = 0x00;

  /* check spaces for any obstructions, and   */
  /* cast spell if something can be hit  */
  if (ENTITY_FACING_CHECK(e1, ENTITY_FACING_RIGHT))
  {
    for (m = low_x; m <= high_x; m++)
    {
      for (n = low_y; n <= high_y; n++)
      {
        sp = &(G_collide_grid[m * COLLIDE_GRID_HEIGHT + n]);

        for (i = 0; i < sp->num_entities; i++)
        {
          e2 = sp->entities[i];

          if ((e1 == e2) || (G_player == e2))
            continue;

          if ((e2->damage_attribute & ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE)  &&
              (e1->type == ENTITY_TYPE_SNAKE))
          {
            e1->action_flags |= ENTITY_ACTION_FLAG_CASTING;
            return 0;
          }
          else if ( (e2->damage_attribute & ENTITY_DAMAGE_FLAG_WEAK_TO_ICE) &&
                    (e1->type == ENTITY_TYPE_UNDINE) &&
                    (!(ENTITY_TYPE_IS_ICE_CUBE(e2->type))))
          {
            e1->action_flags |= ENTITY_ACTION_FLAG_CASTING;
            return 0;
          }
          else if ( (e2->damage_attribute & ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL) &&
                    (e1->type == ENTITY_TYPE_WITCH))
          {
            e1->action_flags |= ENTITY_ACTION_FLAG_CASTING;
            return 0;
          }

          if (e1->type == ENTITY_TYPE_LASER_GUN)
          {
            if ((e2->type == ENTITY_TYPE_EXPLOSION) ||
                (e2->type == ENTITY_TYPE_LASER_SHOT))
              blocked_flag |= 0x01;
          }
          else if (e2->type != ENTITY_TYPE_WARP_SPELL)
          {
            if (e2->move_affect & ENTITY_MOVE_FLAG_SPELL)
              blocked_flag |= 0x01;

            if (e2->damage_affect & ENTITY_DAMAGE_FLAG_SPELL)
              blocked_flag |= 0x01;
          }

          if ((e1->type == ENTITY_TYPE_SORCERESS) && 
              (ENTITY_TYPE_IS_UNWARPABLE(e2->type)))
            blocked_flag |= 0x01;
        }
      }

      if (blocked_flag & 0x01)
        return 0;
    }
  }
  else if (ENTITY_FACING_CHECK(e1, ENTITY_FACING_UP))
  {
    for (n = high_y; n >= low_y; n--)
    {
      for (m = low_x; m <= high_x; m++)
      {
        sp = &(G_collide_grid[m * COLLIDE_GRID_HEIGHT + n]);

        for (i = 0; i < sp->num_entities; i++)
        {
          e2 = sp->entities[i];

          if ((e1 == e2) || (G_player == e2))
            continue;

          if ((e2->damage_attribute & ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE)  &&
              (e1->type == ENTITY_TYPE_SNAKE))
          {
            e1->action_flags |= ENTITY_ACTION_FLAG_CASTING;
            return 0;
          }
          else if ( (e2->damage_attribute & ENTITY_DAMAGE_FLAG_WEAK_TO_ICE) &&
                    (e1->type == ENTITY_TYPE_UNDINE) &&
                    (!(ENTITY_TYPE_IS_ICE_CUBE(e2->type))))
          {
            e1->action_flags |= ENTITY_ACTION_FLAG_CASTING;
            return 0;
          }
          else if ( (e2->damage_attribute & ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL) &&
                    (e1->type == ENTITY_TYPE_WITCH))
          {
            e1->action_flags |= ENTITY_ACTION_FLAG_CASTING;
            return 0;
          }

          if (e1->type == ENTITY_TYPE_LASER_GUN)
          {
            if ((e2->type == ENTITY_TYPE_EXPLOSION) ||
                (e2->type == ENTITY_TYPE_LASER_SHOT))
              blocked_flag |= 0x01;
          }
          else if (e2->type != ENTITY_TYPE_WARP_SPELL)
          {
            if (e2->move_affect & ENTITY_MOVE_FLAG_SPELL)
              blocked_flag |= 0x01;

            if (e2->damage_affect & ENTITY_DAMAGE_FLAG_SPELL)
              blocked_flag |= 0x01;
          }

          if ((e1->type == ENTITY_TYPE_SORCERESS) && 
              (ENTITY_TYPE_IS_UNWARPABLE(e2->type)))
            blocked_flag |= 0x01;
        }
      }

      if (blocked_flag & 0x01)
        return 0;
    }
  }
  else if (ENTITY_FACING_CHECK(e1, ENTITY_FACING_LEFT))
  {
    for (m = high_x; m >= low_x; m--)
    {
      for (n = low_y; n <= high_y; n++)
      {
        sp = &(G_collide_grid[m * COLLIDE_GRID_HEIGHT + n]);

        for (i = 0; i < sp->num_entities; i++)
        {
          e2 = sp->entities[i];

          if ((e1 == e2) || (G_player == e2))
            continue;

          if ((e2->damage_attribute & ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE)  &&
              (e1->type == ENTITY_TYPE_SNAKE))
          {
            e1->action_flags |= ENTITY_ACTION_FLAG_CASTING;
            return 0;
          }
          else if ( (e2->damage_attribute & ENTITY_DAMAGE_FLAG_WEAK_TO_ICE) &&
                    (e1->type == ENTITY_TYPE_UNDINE) &&
                    (!(ENTITY_TYPE_IS_ICE_CUBE(e2->type))))
          {
            e1->action_flags |= ENTITY_ACTION_FLAG_CASTING;
            return 0;
          }
          else if ( (e2->damage_attribute & ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL) &&
                    (e1->type == ENTITY_TYPE_WITCH))
          {
            e1->action_flags |= ENTITY_ACTION_FLAG_CASTING;
            return 0;
          }

          if (e1->type == ENTITY_TYPE_LASER_GUN)
          {
            if ((e2->type == ENTITY_TYPE_EXPLOSION) ||
                (e2->type == ENTITY_TYPE_LASER_SHOT))
              blocked_flag |= 0x01;
          }
          else if (e2->type != ENTITY_TYPE_WARP_SPELL)
          {
            if (e2->move_affect & ENTITY_MOVE_FLAG_SPELL)
              blocked_flag |= 0x01;

            if (e2->damage_affect & ENTITY_DAMAGE_FLAG_SPELL)
              blocked_flag |= 0x01;
          }

          if ((e1->type == ENTITY_TYPE_SORCERESS) && 
              (ENTITY_TYPE_IS_UNWARPABLE(e2->type)))
            blocked_flag |= 0x01;
        }
      }

      if (blocked_flag & 0x01)
        return 0;
    }
  }
  else if (ENTITY_FACING_CHECK(e1, ENTITY_FACING_DOWN))
  {
    for (n = low_y; n <= high_y; n++)
    {
      for (m = low_x; m <= high_x; m++)
      {
        sp = &(G_collide_grid[m * COLLIDE_GRID_HEIGHT + n]);

        for (i = 0; i < sp->num_entities; i++)
        {
          e2 = sp->entities[i];

          if ((e1 == e2) || (G_player == e2))
            continue;

          if ((e2->damage_attribute & ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE)  &&
              (e1->type == ENTITY_TYPE_SNAKE))
          {
            e1->action_flags |= ENTITY_ACTION_FLAG_CASTING;
            return 0;
          }
          else if ( (e2->damage_attribute & ENTITY_DAMAGE_FLAG_WEAK_TO_ICE) &&
                    (e1->type == ENTITY_TYPE_UNDINE) &&
                    (!(ENTITY_TYPE_IS_ICE_CUBE(e2->type))))
          {
            e1->action_flags |= ENTITY_ACTION_FLAG_CASTING;
            return 0;
          }
          else if ( (e2->damage_attribute & ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL) &&
                    (e1->type == ENTITY_TYPE_WITCH))
          {
            e1->action_flags |= ENTITY_ACTION_FLAG_CASTING;
            return 0;
          }

          if (e1->type == ENTITY_TYPE_LASER_GUN)
          {
            if ((e2->type == ENTITY_TYPE_EXPLOSION) ||
                (e2->type == ENTITY_TYPE_LASER_SHOT))
              blocked_flag |= 0x01;
          }
          else if (e2->type != ENTITY_TYPE_WARP_SPELL)
          {
            if (e2->move_affect & ENTITY_MOVE_FLAG_SPELL)
              blocked_flag |= 0x01;

            if (e2->damage_affect & ENTITY_DAMAGE_FLAG_SPELL)
              blocked_flag |= 0x01;
          }

          if ((e1->type == ENTITY_TYPE_SORCERESS) && 
              (ENTITY_TYPE_IS_UNWARPABLE(e2->type)))
            blocked_flag |= 0x01;
        }
      }

      if (blocked_flag & 0x01)
        return 0;
    }
  }

  /* set casting flag, if not blocked */
  e1->action_flags |= ENTITY_ACTION_FLAG_CASTING;

  return 0;
}

/*******************************************************************************
** logic_check_spell_casters()
*******************************************************************************/
short int logic_check_spell_casters()
{
  entity* e;

  /* if player does not exist, return */
  if (G_player == NULL)
    return 0;

  /* if player is not a vampire or bat, return */
  if ((G_player->type != ENTITY_TYPE_PLAYER_VAMPIRE)  &&
      (G_player->type != ENTITY_TYPE_PLAYER_BAT))
  {
    return 0;
  }

  /* cycle through snakes */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_SNAKES_FAERIES_VENUSIANS];
        e != NULL;
        e = e->next)
  {
    if (e->type == ENTITY_TYPE_SNAKE)
    {
      if ((e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE) &&
          (!(ENTITY_IS_PERFORMING_ACTION(e) || ENTITY_IS_IN_COOLDOWN(e))))
      {
        if ((e->pos_x < G_player->pos_x)        &&
            (e->pos_y - G_player->pos_y >= -16) &&
            (e->pos_y - G_player->pos_y <= 16)  &&
            (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT)))
        {
          logic_attempt_spell_cast(e);
        }
        else if ( (e->pos_x - G_player->pos_x >= -16) &&
                  (e->pos_x - G_player->pos_x <= 16)  &&
                  (e->pos_y > G_player->pos_y)        &&
                  (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP)))
        {
          logic_attempt_spell_cast(e);
        }
        else if ( (e->pos_x > G_player->pos_x)        &&
                  (e->pos_y - G_player->pos_y >= -16) &&
                  (e->pos_y - G_player->pos_y <= 16)  &&
                  (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT)))
        {
          logic_attempt_spell_cast(e);
        }
        else if ( (e->pos_x - G_player->pos_x >= -16) &&
                  (e->pos_x - G_player->pos_x <= 16)  &&
                  (e->pos_y < G_player->pos_y)        &&
                  (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN)))
        {
          logic_attempt_spell_cast(e);
        }
      }
    }
  }

  /* cycle through witches, undines, sorceresses */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_UNDINES_SORCERESSES_WITCHES];
        e != NULL;
        e = e->next)
  {
    if (e->type == ENTITY_TYPE_WITCH)
    {
      if ((e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE) &&
          (!(ENTITY_IS_PERFORMING_ACTION(e) || ENTITY_IS_IN_COOLDOWN(e))))
      {
        if ((e->pos_x < G_player->pos_x)        &&
            (e->pos_y - G_player->pos_y >= -16) &&
            (e->pos_y - G_player->pos_y <= 16)  &&
            (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT)))
        {
          logic_attempt_spell_cast(e);
        }
        else if ( (e->pos_x - G_player->pos_x >= -16) &&
                  (e->pos_x - G_player->pos_x <= 16)  &&
                  (e->pos_y > G_player->pos_y)        &&
                  (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP)))
        {
          logic_attempt_spell_cast(e);
        }
        else if ( (e->pos_x > G_player->pos_x)        &&
                  (e->pos_y - G_player->pos_y >= -16) &&
                  (e->pos_y - G_player->pos_y <= 16)  &&
                  (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT)))
        {
          logic_attempt_spell_cast(e);
        }
        else if ( (e->pos_x - G_player->pos_x >= -16) &&
                  (e->pos_x - G_player->pos_x <= 16)  &&
                  (e->pos_y < G_player->pos_y)        &&
                  (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN)))
        {
          logic_attempt_spell_cast(e);
        }
      }
    }
    else if ( (e->type == ENTITY_TYPE_UNDINE)     ||
              (e->type == ENTITY_TYPE_SORCERESS))
    {
      if (!(ENTITY_IS_PERFORMING_ACTION(e) || ENTITY_IS_IN_COOLDOWN(e)))
      {
        if ((e->pos_x < G_player->pos_x)        &&
            (e->pos_y - G_player->pos_y >= -16) &&
            (e->pos_y - G_player->pos_y <= 16)  &&
            (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT)))
        {
          logic_attempt_spell_cast(e);
        }
        else if ( (e->pos_x - G_player->pos_x >= -16) &&
                  (e->pos_x - G_player->pos_x <= 16)  &&
                  (e->pos_y > G_player->pos_y)        &&
                  (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP)))
        {
          logic_attempt_spell_cast(e);
        }
        else if ( (e->pos_x > G_player->pos_x)        &&
                  (e->pos_y - G_player->pos_y >= -16) &&
                  (e->pos_y - G_player->pos_y <= 16)  &&
                  (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT)))
        {
          logic_attempt_spell_cast(e);
        }
        else if ( (e->pos_x - G_player->pos_x >= -16) &&
                  (e->pos_x - G_player->pos_x <= 16)  &&
                  (e->pos_y < G_player->pos_y)        &&
                  (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN)))
        {
          logic_attempt_spell_cast(e);
        }
      }
    }
  }

  /* cycle through laser guns */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_LASER_GUNS];
        e != NULL;
        e = e->next)
  {
    if (e->type == ENTITY_TYPE_LASER_GUN)
    {
      if (!(ENTITY_IS_PERFORMING_ACTION(e) || ENTITY_IS_IN_COOLDOWN(e)))
      {
        if ((e->pos_x < G_player->pos_x)        &&
            (e->pos_y - G_player->pos_y >= -16) &&
            (e->pos_y - G_player->pos_y <= 16)  &&
            (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT)))
        {
          logic_attempt_spell_cast(e);
        }
        else if ( (e->pos_x - G_player->pos_x >= -16) &&
                  (e->pos_x - G_player->pos_x <= 16)  &&
                  (e->pos_y > G_player->pos_y)        &&
                  (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP)))
        {
          logic_attempt_spell_cast(e);
        }
        else if ( (e->pos_x > G_player->pos_x)        &&
                  (e->pos_y - G_player->pos_y >= -16) &&
                  (e->pos_y - G_player->pos_y <= 16)  &&
                  (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT)))
        {
          logic_attempt_spell_cast(e);
        }
        else if ( (e->pos_x - G_player->pos_x >= -16) &&
                  (e->pos_x - G_player->pos_x <= 16)  &&
                  (e->pos_y < G_player->pos_y)        &&
                  (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN)))
        {
          logic_attempt_spell_cast(e);
        }
      }
    }
  }

  return 0;
}

/*******************************************************************************
** logic_attempt_cast_evil_eye()
*******************************************************************************/
short int logic_attempt_cast_evil_eye(entity* e1)
{
  int                 i;
  int                 m;
  int                 n;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp;
  entity*             e2;

  /* if entity or player does not exist, return */
  if ((e1 == NULL) || (G_player == NULL))
    return 0;

  /* determine spaces between entities */
  if (ENTITY_FACING_CHECK(e1, ENTITY_FACING_RIGHT))
  {
    low_x = ((e1->pos_x + e1->rx - 1) / 16) - 1 + 1;
    high_x = ((G_player->pos_x - G_player->rx) / 16) - 1 - 1;

    low_y = ((e1->pos_y - e1->ry) / 16) - 3;
    high_y = ((e1->pos_y + e1->ry - 1) / 16) - 3;
  }
  else if (ENTITY_FACING_CHECK(e1, ENTITY_FACING_UP))
  {
    low_x = ((e1->pos_x - e1->rx) / 16) - 1;
    high_x = ((e1->pos_x + e1->rx - 1) / 16) - 1;

    low_y = ((G_player->pos_y + G_player->ry - 1) / 16) - 3 + 1;
    high_y = ((e1->pos_y - e1->ry) / 16) - 3 - 1;
  }
  else if (ENTITY_FACING_CHECK(e1, ENTITY_FACING_LEFT))
  {
    low_x = ((G_player->pos_x + G_player->rx - 1) / 16) - 1 + 1;
    high_x = ((e1->pos_x - e1->rx) / 16) - 1 - 1;

    low_y = ((e1->pos_y - e1->ry) / 16) - 3;
    high_y = ((e1->pos_y + e1->ry - 1) / 16) - 3;
  }
  else if (ENTITY_FACING_CHECK(e1, ENTITY_FACING_DOWN))
  {
    low_x = ((e1->pos_x - e1->rx) / 16) - 1;
    high_x = ((e1->pos_x + e1->rx - 1) / 16) - 1;

    low_y = ((e1->pos_y + e1->ry - 1) / 16) - 3 + 1;
    high_y = ((G_player->pos_y - G_player->ry) / 16) - 3 - 1;
  }
  else
    return 0;

  /* make sure spaces are within the grid */
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

  /* check spaces for any obstructions */
  for (m = low_x; m <= high_x; m++)
  {
    for (n = low_y; n <= high_y; n++)
    {
      sp = &(G_collide_grid[m * COLLIDE_GRID_HEIGHT + n]);

      for (i = 0; i < sp->num_entities; i++)
      {
        e2 = sp->entities[i];

        if ((e1 == e2) || (G_player == e2))
          continue;

        if (e2->move_affect & ENTITY_MOVE_FLAG_EVIL_EYE)
        {
          if ((ENTITY_FACING_CHECK(e1, ENTITY_FACING_RIGHT))  ||
              (ENTITY_FACING_CHECK(e1, ENTITY_FACING_LEFT)))
          {
            if ((e1->pos_y > e2->pos_y) &&
                (e1->pos_y - e1->ry < e2->pos_y + e2->ry - 1))
            {
              return 0;
            }
            else if ( (e1->pos_y < e2->pos_y) &&
                      (e1->pos_y + e1->ry - 1 > e2->pos_y - e2->ry))
            {
              return 0;
            }
            else if (e1->pos_y == e2->pos_y)
              return 0;
          }
          else if ( (ENTITY_FACING_CHECK(e1, ENTITY_FACING_UP))   ||
                    (ENTITY_FACING_CHECK(e1, ENTITY_FACING_DOWN)))
          {
            if ((e1->pos_x > e2->pos_x) &&
                (e1->pos_x - e1->rx < e2->pos_x + e2->rx - 1))
            {
              return 0;
            }
            else if ( (e1->pos_x < e2->pos_x) &&
                      (e1->pos_x + e1->rx - 1 > e2->pos_x - e2->rx))
            {
              return 0;
            }
            else if (e1->pos_x == e2->pos_x)
              return 0;
          }
        }
      }
    }
  }

  /* cast evil eye */
  e1->action_flags |= ENTITY_ACTION_FLAG_CASTING;

  return 0;
}

/*******************************************************************************
** logic_check_evil_eye_casters()
*******************************************************************************/
short int logic_check_evil_eye_casters()
{
  entity* e;

  /* if player does not exist, return */
  if (G_player == NULL)
    return 0;

  /* if player is not a vampire or bat, return */
  if ((G_player->type != ENTITY_TYPE_PLAYER_VAMPIRE)  &&
      (G_player->type != ENTITY_TYPE_PLAYER_BAT))
  {
    return 0;
  }

  /* if player is already colliding with another entity, return */
  if (G_player->collision_flags != ENTITY_COLLISION_FLAGS_CLEAR)
    return 0;

  /* if player is over a solomon's seal, return */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_SYMBOLS];
        e != NULL;
        e = e->next)
  {
    if (e->type == ENTITY_TYPE_SEAL_OF_SOLOMON)
    {
      if ((G_player->pos_x - e->pos_x < 16)   &&
          (G_player->pos_x - e->pos_x > -16)  &&
          (G_player->pos_y - e->pos_y < 16)   &&
          (G_player->pos_y - e->pos_y > -16))
      {
        return 0;
      }
    }
  }

  /* cycle through the evil eye casters */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_PUMPKINS_GHOSTS_MASKS];
        e != NULL;
        e = e->next)
  {
    if (!(e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE))
      continue;

    /* pumpkins and masks */
    if ((e->type == ENTITY_TYPE_PUMPKIN)          ||
        (e->type == ENTITY_TYPE_MASK_HORIZONTAL)  ||
        (e->type == ENTITY_TYPE_MASK_VERTICAL))
    {
      if ((e->pos_x < G_player->pos_x) && (e->pos_y == G_player->pos_y))
      {
        entity_set_facing(e, ENTITY_FACING_RIGHT);
        logic_attempt_cast_evil_eye(e);
      }
      else if ((e->pos_x == G_player->pos_x) && (e->pos_y > G_player->pos_y))
      {
        entity_set_facing(e, ENTITY_FACING_UP);
        logic_attempt_cast_evil_eye(e);
      }
      else if ((e->pos_x > G_player->pos_x) && (e->pos_y == G_player->pos_y))
      {
        entity_set_facing(e, ENTITY_FACING_LEFT);
        logic_attempt_cast_evil_eye(e);
      }
      else if ((e->pos_x == G_player->pos_x) && (e->pos_y < G_player->pos_y))
      {
        entity_set_facing(e, ENTITY_FACING_DOWN);
        logic_attempt_cast_evil_eye(e);
      }
      else if ( (e->action_flags & ENTITY_ACTION_FLAG_MOVING) ||
                (G_player->action_flags & ENTITY_ACTION_FLAG_MOVING))
      {
        if ((ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_RIGHT)) &&
            (e->pos_x - G_player->pos_x == 2))
        {
          if (e->pos_y > G_player->pos_y)
            entity_set_facing(e, ENTITY_FACING_UP);
          else if (e->pos_y < G_player->pos_y)
            entity_set_facing(e, ENTITY_FACING_DOWN);

          logic_attempt_cast_evil_eye(e);
        }
        else if ( (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_UP)) &&
                  (e->pos_y - G_player->pos_y == -2))
        {
          if (e->pos_x < G_player->pos_x)
            entity_set_facing(e, ENTITY_FACING_RIGHT);
          else if (e->pos_x > G_player->pos_x)
            entity_set_facing(e, ENTITY_FACING_LEFT);

          logic_attempt_cast_evil_eye(e);
        }
        else if ( (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_LEFT)) &&
                  (e->pos_x - G_player->pos_x == -2))
        {
          if (e->pos_y > G_player->pos_y)
            entity_set_facing(e, ENTITY_FACING_UP);
          else if (e->pos_y < G_player->pos_y)
            entity_set_facing(e, ENTITY_FACING_DOWN);

          logic_attempt_cast_evil_eye(e);
        }
        else if ( (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_DOWN)) &&
                  (e->pos_y - G_player->pos_y == 2))
        {
          if (e->pos_x < G_player->pos_x)
            entity_set_facing(e, ENTITY_FACING_RIGHT);
          else if (e->pos_x > G_player->pos_x)
            entity_set_facing(e, ENTITY_FACING_LEFT);

          logic_attempt_cast_evil_eye(e);
        }
      }
    }
    /* ghosts */
    else if (e->type == ENTITY_TYPE_GHOST)
    {
      if ((e->pos_x < G_player->pos_x)  &&
          (e->pos_y == G_player->pos_y) &&
          (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT)))
      {
        logic_attempt_cast_evil_eye(e);
      }
      else if ( (e->pos_x == G_player->pos_x) &&
                (e->pos_y > G_player->pos_y)  &&
                (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP)))
      {
        logic_attempt_cast_evil_eye(e);
      }
      else if ( (e->pos_x > G_player->pos_x)  &&
                (e->pos_y == G_player->pos_y) &&
                (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT)))
      {
        logic_attempt_cast_evil_eye(e);
      }
      else if ( (e->pos_x == G_player->pos_x) &&
                (e->pos_y < G_player->pos_y)  &&
                (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN)))
      {
        logic_attempt_cast_evil_eye(e);
      }
    }

    /* if evil eye was cast, return now */
    if (e->action_flags & ENTITY_ACTION_FLAG_CASTING)
      return 0;
  }

  return 0;
}

/*******************************************************************************
** logic_attempt_frog_action()
*******************************************************************************/
short int logic_attempt_frog_action(entity* e1)
{
  int                 i;
  int                 m;
  int                 n;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp;
  entity*             e2;

  /* if entity or player does not exist, return */
  if ((e1 == NULL) || (G_player == NULL))
    return 0;

  /* make sure entity is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
    return 0;

  /* determine spaces between entities */
  if (ENTITY_FACING_CHECK(e1, ENTITY_FACING_RIGHT))
  {
    low_x = ((e1->pos_x + e1->rx - 1) / 16) - 1 + 1;
    high_x = ((G_player->pos_x - G_player->rx) / 16) - 1 - 1;

    low_y = ((e1->pos_y - e1->ry) / 16) - 3;
    high_y = ((e1->pos_y + e1->ry - 1) / 16) - 3;
  }
  else if (ENTITY_FACING_CHECK(e1, ENTITY_FACING_UP))
  {
    low_x = ((e1->pos_x - e1->rx) / 16) - 1;
    high_x = ((e1->pos_x + e1->rx - 1) / 16) - 1;

    low_y = ((G_player->pos_y + G_player->ry - 1) / 16) - 3 + 1;
    high_y = ((e1->pos_y - e1->ry) / 16) - 3 - 1;
  }
  else if (ENTITY_FACING_CHECK(e1, ENTITY_FACING_LEFT))
  {
    low_x = ((G_player->pos_x + G_player->rx - 1) / 16) - 1 + 1;
    high_x = ((e1->pos_x - e1->rx) / 16) - 1 - 1;

    low_y = ((e1->pos_y - e1->ry) / 16) - 3;
    high_y = ((e1->pos_y + e1->ry - 1) / 16) - 3;
  }
  else if (ENTITY_FACING_CHECK(e1, ENTITY_FACING_DOWN))
  {
    low_x = ((e1->pos_x - e1->rx) / 16) - 1;
    high_x = ((e1->pos_x + e1->rx - 1) / 16) - 1;

    low_y = ((e1->pos_y + e1->ry - 1) / 16) - 3 + 1;
    high_y = ((G_player->pos_y - G_player->ry) / 16) - 3 - 1;
  }
  else
    return 0;

  /* make sure spaces are within the grid */
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

  /* check spaces for any obstructions */
  for (m = low_x; m <= high_x; m++)
  {
    for (n = low_y; n <= high_y; n++)
    {
      sp = &(G_collide_grid[m * COLLIDE_GRID_HEIGHT + n]);

      for (i = 0; i < sp->num_entities; i++)
      {
        e2 = sp->entities[i];

        if ((e1 == e2) || (G_player == e2))
          continue;

        if (e2->move_affect & ENTITY_MOVE_FLAG_SPELL)
          return 0;
      }
    }
  }

  /* perform frog action  */
  e1->action_flags |= ENTITY_ACTION_FLAG_CASTING;

  return 0;
}

/*******************************************************************************
** logic_check_frogs()
*******************************************************************************/
short int logic_check_frogs()
{
  entity* e;
  entity* acting_frog;

  /* if player does not exist, return */
  if (G_player == NULL)
    return 0;

  /* if player is not a vampire or bat, return */
  if ((G_player->type != ENTITY_TYPE_PLAYER_VAMPIRE)  &&
      (G_player->type != ENTITY_TYPE_PLAYER_BAT))
  {
    return 0;
  }

  /* if player is performing an action or moving into water, return */
  if (ENTITY_IS_PERFORMING_ACTION(G_player))
    return 0;

  if (G_player->update_flags & ENTITY_UPDATE_FLAG_MOVING_INTO_WATER)
    return 0;

  /* initialize frog pointer */
  acting_frog = NULL;

  /* cycle through frogs */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_LIL_BOTS_WISPS_FROGS];
        e != NULL;
        e = e->next)
  {
    if ((e->type == ENTITY_TYPE_FROG) &&
        (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE))
    {
      logic_attempt_frog_action(e);

      /* if frog action was successful, set frog pointer */
      if (e->action_flags & ENTITY_ACTION_FLAG_CASTING)
      {
        e->action_flags &= ~ENTITY_ACTION_FLAG_CASTING;

        /* if frog pointer is already set, return */
        /* (only 1 frog acts at a time)           */
        if (acting_frog == NULL)
          acting_frog = e;
        else
          return 0;
      }
    }
  }

  /* perform frog action, if necessary */
  if (acting_frog != NULL)
  {
    /* if player is already being conveyed, cancel conveyance */
    /* if frog action is in opposing direction                */
    if (G_player->action_flags & ENTITY_ACTION_FLAG_BEING_CONVEYED)
    {
      if (ENTITY_FACING_CHECK(acting_frog, ENTITY_FACING_RIGHT) &&
          ENTITY_DIRECTION_CHECK(G_player, ENTITY_DIRECTION_RIGHT))
      {
        G_player->action_flags &= ~ENTITY_ACTION_FLAG_BEING_CONVEYED;
        return 0;
      }
      else if ( ENTITY_FACING_CHECK(acting_frog, ENTITY_FACING_UP) &&
                ENTITY_DIRECTION_CHECK(G_player, ENTITY_DIRECTION_UP))
      {
        G_player->action_flags &= ~ENTITY_ACTION_FLAG_BEING_CONVEYED;
        return 0;
      }
      else if ( ENTITY_FACING_CHECK(acting_frog, ENTITY_FACING_LEFT) &&
                ENTITY_DIRECTION_CHECK(G_player, ENTITY_DIRECTION_LEFT))
      {
        G_player->action_flags &= ~ENTITY_ACTION_FLAG_BEING_CONVEYED;
        return 0;
      }
      else if ( ENTITY_FACING_CHECK(acting_frog, ENTITY_FACING_DOWN) &&
                ENTITY_DIRECTION_CHECK(G_player, ENTITY_DIRECTION_DOWN))
      {
        G_player->action_flags &= ~ENTITY_ACTION_FLAG_BEING_CONVEYED;
        return 0;
      }
    }

    /* otherwise, conveyance is overridden by frog action */
    G_player->action_flags |= ENTITY_ACTION_FLAG_BEING_CONVEYED;
    G_player->orientation &= ~ENTITY_DIRECTION_MASK;

    if (ENTITY_FACING_CHECK(acting_frog, ENTITY_FACING_RIGHT))
      G_player->orientation |= ENTITY_DIRECTION_LEFT;
    else if (ENTITY_FACING_CHECK(acting_frog, ENTITY_FACING_UP))
      G_player->orientation |= ENTITY_DIRECTION_DOWN;
    else if (ENTITY_FACING_CHECK(acting_frog, ENTITY_FACING_LEFT))
      G_player->orientation |= ENTITY_DIRECTION_RIGHT;
    else if (ENTITY_FACING_CHECK(acting_frog, ENTITY_FACING_DOWN))
      G_player->orientation |= ENTITY_DIRECTION_UP;
  }

  return 0;
}

/*******************************************************************************
** logic_enemy_movement_pattern_back_and_forth()
*******************************************************************************/
short int logic_enemy_movement_pattern_back_and_forth(entity* e)
{
  if (e == NULL)
    return 0;

  /* make sure entity is not already moving, casting a spell, etc */
  if (ENTITY_IS_PERFORMING_ACTION(e) || ENTITY_IS_IN_COOLDOWN(e))
    return 0;

  /* moving right */
  if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_RIGHT))
  {
    logic_attempt_move(e, ENTITY_DIRECTION_RIGHT);

    /* if move attempt failed, try other direction */
    if (!(e->action_flags & ENTITY_ACTION_FLAG_MOVING))
      logic_attempt_move(e, ENTITY_DIRECTION_LEFT);
  }
  /* moving up */
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_UP))
  {
    logic_attempt_move(e, ENTITY_DIRECTION_UP);

    /* if move attempt failed, try other direction */
    if (!(e->action_flags & ENTITY_ACTION_FLAG_MOVING))
      logic_attempt_move(e, ENTITY_DIRECTION_DOWN);
  }
  /* moving left */
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_LEFT))
  {
    logic_attempt_move(e, ENTITY_DIRECTION_LEFT);

    /* if move attempt failed, try other direction */
    if (!(e->action_flags & ENTITY_ACTION_FLAG_MOVING))
      logic_attempt_move(e, ENTITY_DIRECTION_RIGHT);
  }
  /* moving down */
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_DOWN))
  {
    logic_attempt_move(e, ENTITY_DIRECTION_DOWN);

    /* if move attempt failed, try other direction */
    if (!(e->action_flags & ENTITY_ACTION_FLAG_MOVING))
      logic_attempt_move(e, ENTITY_DIRECTION_UP);
  }

  return 0;
}

/*******************************************************************************
** logic_enemy_movement_pattern_back_and_forth_using_facing()
*******************************************************************************/
short int logic_enemy_movement_pattern_back_and_forth_using_facing(entity* e)
{
  if (e == NULL)
    return 0;

  /* make sure entity is not already moving, casting a spell, etc */
  if (ENTITY_IS_PERFORMING_ACTION(e) || ENTITY_IS_IN_COOLDOWN(e))
    return 0;

  /* facing right */
  if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
  {
    /* try moving right */
    logic_attempt_move(e, ENTITY_DIRECTION_RIGHT);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
      return 0;

    /* try moving left */
    logic_attempt_move(e, ENTITY_DIRECTION_LEFT);

    /* if 2nd move attempt was successful, setup animation */
    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_LEFT);
      animation_setup(e);
    }
  }
  /* facing up */
  else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
  {
    /* try moving up */
    logic_attempt_move(e, ENTITY_DIRECTION_UP);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
      return 0;

    /* try moving down */
    logic_attempt_move(e, ENTITY_DIRECTION_DOWN);

    /* if 2nd move attempt was successful, setup animation */
    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_DOWN);
      animation_setup(e);
    }
  }
  /* facing left */
  else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
  {
    /* try moving left */
    logic_attempt_move(e, ENTITY_DIRECTION_LEFT);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
      return 0;

    /* try moving right */
    logic_attempt_move(e, ENTITY_DIRECTION_RIGHT);

    /* if 2nd move attempt was successful, setup animation */
    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_RIGHT);
      animation_setup(e);
    }
  }
  /* facing down */
  else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
  {
    /* try moving down */
    logic_attempt_move(e, ENTITY_DIRECTION_DOWN);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
      return 0;

    /* try moving up */
    logic_attempt_move(e, ENTITY_DIRECTION_UP);

    /* if 2nd move attempt was successful, setup animation */
    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_UP);
      animation_setup(e);
    }
  }

  return 0;
}

/*******************************************************************************
** logic_enemy_movement_pattern_faerie_horizontal()
*******************************************************************************/
short int logic_enemy_movement_pattern_faerie_horizontal(entity* e)
{
  if (e == NULL)
    return 0;

  /* make sure entity is not already moving, casting a spell, etc */
  if (ENTITY_IS_PERFORMING_ACTION(e) || ENTITY_IS_IN_COOLDOWN(e))
    return 0;

  /* if player does not exist, return */
  if (G_player == NULL)
    return 0;

  /* try to move towards player */
  if (e->pos_x < G_player->pos_x)
    logic_attempt_move(e, ENTITY_DIRECTION_RIGHT);
  else if (e->pos_x > G_player->pos_x)
    logic_attempt_move(e, ENTITY_DIRECTION_LEFT);

  return 0;
}

/*******************************************************************************
** logic_enemy_movement_pattern_faerie_vertical()
*******************************************************************************/
short int logic_enemy_movement_pattern_faerie_vertical(entity* e)
{
  if (e == NULL)
    return 0;

  /* make sure entity is not already moving, casting a spell, etc */
  if (ENTITY_IS_PERFORMING_ACTION(e) || ENTITY_IS_IN_COOLDOWN(e))
    return 0;

  /* if player does not exist, return */
  if (G_player == NULL)
    return 0;

  /* try to move towards player */
  if (e->pos_y < G_player->pos_y)
    logic_attempt_move(e, ENTITY_DIRECTION_DOWN);
  else if (e->pos_y > G_player->pos_y)
    logic_attempt_move(e, ENTITY_DIRECTION_UP);

  return 0;
}

/*******************************************************************************
** logic_enemy_movement_pattern_left_turn_using_facing()
*******************************************************************************/
short int logic_enemy_movement_pattern_left_turn_using_facing(entity* e)
{
  if (e == NULL)
    return 0;

  /* make sure entity is not already moving, casting a spell, etc */
  if (ENTITY_IS_PERFORMING_ACTION(e) || ENTITY_IS_IN_COOLDOWN(e))
    return 0;

  /* facing right */
  if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
  {
    /* try moving right */
    logic_attempt_move(e, ENTITY_DIRECTION_RIGHT);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
      return 0;

    /* try moving up */
    logic_attempt_move(e, ENTITY_DIRECTION_UP);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_UP);
      animation_setup(e);
      return 0;
    }

    /* try moving left */
    logic_attempt_move(e, ENTITY_DIRECTION_LEFT);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_LEFT);
      animation_setup(e);
      return 0;
    }

    /* try moving down */
    logic_attempt_move(e, ENTITY_DIRECTION_DOWN);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_DOWN);
      animation_setup(e);
      return 0;
    }
  }
  /* facing up */
  else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
  {
    /* try moving up */
    logic_attempt_move(e, ENTITY_DIRECTION_UP);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
      return 0;

    /* try moving left */
    logic_attempt_move(e, ENTITY_DIRECTION_LEFT);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_LEFT);
      animation_setup(e);
      return 0;
    }

    /* try moving down */
    logic_attempt_move(e, ENTITY_DIRECTION_DOWN);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_DOWN);
      animation_setup(e);
      return 0;
    }

    /* try moving right */
    logic_attempt_move(e, ENTITY_DIRECTION_RIGHT);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_RIGHT);
      animation_setup(e);
      return 0;
    }
  }
  /* facing left */
  else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
  {
    /* try moving left */
    logic_attempt_move(e, ENTITY_DIRECTION_LEFT);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
      return 0;

    /* try moving down */
    logic_attempt_move(e, ENTITY_DIRECTION_DOWN);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_DOWN);
      animation_setup(e);
      return 0;
    }

    /* try moving right */
    logic_attempt_move(e, ENTITY_DIRECTION_RIGHT);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_RIGHT);
      animation_setup(e);
      return 0;
    }

    /* try moving up */
    logic_attempt_move(e, ENTITY_DIRECTION_UP);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_UP);
      animation_setup(e);
      return 0;
    }
  }
  /* facing down */
  else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
  {
    /* try moving down */
    logic_attempt_move(e, ENTITY_DIRECTION_DOWN);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
      return 0;

    /* try moving right */
    logic_attempt_move(e, ENTITY_DIRECTION_RIGHT);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_RIGHT);
      animation_setup(e);
      return 0;
    }

    /* try moving up */
    logic_attempt_move(e, ENTITY_DIRECTION_UP);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_UP);
      animation_setup(e);
      return 0;
    }

    /* try moving left */
    logic_attempt_move(e, ENTITY_DIRECTION_LEFT);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_LEFT);
      animation_setup(e);
      return 0;
    }
  }

  return 0;
}

/*******************************************************************************
** logic_enemy_movement_pattern_right_turn_using_facing()
*******************************************************************************/
short int logic_enemy_movement_pattern_right_turn_using_facing(entity* e)
{
  if (e == NULL)
    return 0;

  /* make sure entity is not already moving, casting a spell, etc */
  if (ENTITY_IS_PERFORMING_ACTION(e) || ENTITY_IS_IN_COOLDOWN(e))
    return 0;

  /* facing right */
  if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
  {
    /* try moving right */
    logic_attempt_move(e, ENTITY_DIRECTION_RIGHT);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
      return 0;

    /* try moving down */
    logic_attempt_move(e, ENTITY_DIRECTION_DOWN);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_DOWN);
      animation_setup(e);
      return 0;
    }

    /* try moving left */
    logic_attempt_move(e, ENTITY_DIRECTION_LEFT);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_LEFT);
      animation_setup(e);
      return 0;
    }

    /* try moving up */
    logic_attempt_move(e, ENTITY_DIRECTION_UP);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_UP);
      animation_setup(e);
      return 0;
    }
  }
  /* facing up */
  else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
  {
    /* try moving up */
    logic_attempt_move(e, ENTITY_DIRECTION_UP);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
      return 0;

    /* try moving right */
    logic_attempt_move(e, ENTITY_DIRECTION_RIGHT);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_RIGHT);
      animation_setup(e);
      return 0;
    }

    /* try moving down */
    logic_attempt_move(e, ENTITY_DIRECTION_DOWN);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_DOWN);
      animation_setup(e);
      return 0;
    }

    /* try moving left */
    logic_attempt_move(e, ENTITY_DIRECTION_LEFT);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_LEFT);
      animation_setup(e);
      return 0;
    }
  }
  /* facing left */
  else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
  {
    /* try moving left */
    logic_attempt_move(e, ENTITY_DIRECTION_LEFT);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
      return 0;

    /* try moving up */
    logic_attempt_move(e, ENTITY_DIRECTION_UP);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_UP);
      animation_setup(e);
      return 0;
    }

    /* try moving right */
    logic_attempt_move(e, ENTITY_DIRECTION_RIGHT);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_RIGHT);
      animation_setup(e);
      return 0;
    }

    /* try moving down */
    logic_attempt_move(e, ENTITY_DIRECTION_DOWN);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_DOWN);
      animation_setup(e);
      return 0;
    }
  }
  /* facing down */
  else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
  {
    /* try moving down */
    logic_attempt_move(e, ENTITY_DIRECTION_DOWN);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
      return 0;

    /* try moving left */
    logic_attempt_move(e, ENTITY_DIRECTION_LEFT);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_LEFT);
      animation_setup(e);
      return 0;
    }

    /* try moving up */
    logic_attempt_move(e, ENTITY_DIRECTION_UP);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_UP);
      animation_setup(e);
      return 0;
    }

    /* try moving right */
    logic_attempt_move(e, ENTITY_DIRECTION_RIGHT);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      entity_set_facing(e, ENTITY_FACING_RIGHT);
      animation_setup(e);
      return 0;
    }
  }

  return 0;
}

/*******************************************************************************
** logic_enemy_movement_pattern_follow_left_wall()
*******************************************************************************/
short int logic_enemy_movement_pattern_follow_left_wall(entity* e)
{
  if (e == NULL)
    return 0;

  /* make sure entity is not already moving, casting a spell, etc */
  if (ENTITY_IS_PERFORMING_ACTION(e) || ENTITY_IS_IN_COOLDOWN(e))
    return 0;

  /* try to move in direction of left wall */
  if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_RIGHT))
    logic_attempt_move(e, ENTITY_DIRECTION_UP);
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_UP))
    logic_attempt_move(e, ENTITY_DIRECTION_LEFT);
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_LEFT))
    logic_attempt_move(e, ENTITY_DIRECTION_DOWN);
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_DOWN))
    logic_attempt_move(e, ENTITY_DIRECTION_RIGHT);

  /* if move was successful, return */
  if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    return 0;

  /* try to move forward */
  if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_RIGHT))
    logic_attempt_move(e, ENTITY_DIRECTION_RIGHT);
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_UP))
    logic_attempt_move(e, ENTITY_DIRECTION_UP);
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_LEFT))
    logic_attempt_move(e, ENTITY_DIRECTION_LEFT);
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_DOWN))
    logic_attempt_move(e, ENTITY_DIRECTION_DOWN);

  /* if move was successful, return */
  if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    return 0;

  /* try to move in direction of right wall */
  if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_RIGHT))
    logic_attempt_move(e, ENTITY_DIRECTION_DOWN);
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_UP))
    logic_attempt_move(e, ENTITY_DIRECTION_RIGHT);
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_LEFT))
    logic_attempt_move(e, ENTITY_DIRECTION_UP);
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_DOWN))
    logic_attempt_move(e, ENTITY_DIRECTION_LEFT);

  /* if move was successful, return */
  if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    return 0;

  /* try to move backward */
  if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_RIGHT))
    logic_attempt_move(e, ENTITY_DIRECTION_LEFT);
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_UP))
    logic_attempt_move(e, ENTITY_DIRECTION_DOWN);
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_LEFT))
    logic_attempt_move(e, ENTITY_DIRECTION_RIGHT);
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_DOWN))
    logic_attempt_move(e, ENTITY_DIRECTION_UP);

  return 0;
}

/*******************************************************************************
** logic_enemy_movement_pattern_follow_right_wall()
*******************************************************************************/
short int logic_enemy_movement_pattern_follow_right_wall(entity* e)
{
  if (e == NULL)
    return 0;

  /* make sure entity is not already moving, casting a spell, etc */
  if (ENTITY_IS_PERFORMING_ACTION(e) || ENTITY_IS_IN_COOLDOWN(e))
    return 0;

  /* try to move in direction of right wall */
  if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_RIGHT))
    logic_attempt_move(e, ENTITY_DIRECTION_DOWN);
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_UP))
    logic_attempt_move(e, ENTITY_DIRECTION_RIGHT);
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_LEFT))
    logic_attempt_move(e, ENTITY_DIRECTION_UP);
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_DOWN))
    logic_attempt_move(e, ENTITY_DIRECTION_LEFT);

  /* if move was successful, return */
  if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    return 0;

  /* try to move forward */
  if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_RIGHT))
    logic_attempt_move(e, ENTITY_DIRECTION_RIGHT);
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_UP))
    logic_attempt_move(e, ENTITY_DIRECTION_UP);
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_LEFT))
    logic_attempt_move(e, ENTITY_DIRECTION_LEFT);
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_DOWN))
    logic_attempt_move(e, ENTITY_DIRECTION_DOWN);

  /* if move was successful, return */
  if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    return 0;

  /* try to move in direction of left wall */
  if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_RIGHT))
    logic_attempt_move(e, ENTITY_DIRECTION_UP);
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_UP))
    logic_attempt_move(e, ENTITY_DIRECTION_LEFT);
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_LEFT))
    logic_attempt_move(e, ENTITY_DIRECTION_DOWN);
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_DOWN))
    logic_attempt_move(e, ENTITY_DIRECTION_RIGHT);

  /* if move was successful, return */
  if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    return 0;

  /* try to move backward */
  if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_RIGHT))
    logic_attempt_move(e, ENTITY_DIRECTION_LEFT);
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_UP))
    logic_attempt_move(e, ENTITY_DIRECTION_DOWN);
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_LEFT))
    logic_attempt_move(e, ENTITY_DIRECTION_RIGHT);
  else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_DOWN))
    logic_attempt_move(e, ENTITY_DIRECTION_UP);

  return 0;
}

/*******************************************************************************
** logic_enemy_movement_pattern_poltergeist()
*******************************************************************************/
short int logic_enemy_movement_pattern_poltergeist(entity* e)
{
  int poltergeist_frame_count;

  if (e == NULL)
    return 0;

  /* make sure entity is not already moving, etc */
  if (ENTITY_IS_PERFORMING_ACTION(e))
    return 0;

  /* facing right */
  if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
  {
    /* if player is nearby, return */
    if ((G_player != NULL) && (ENTITY_TYPE_IS_PLAYER(G_player->type)))
    {
      if ((G_player->pos_x - e->pos_x >= 32)  &&
          (G_player->pos_x - e->pos_x < 48)   &&
          (G_player->pos_y - e->pos_y < 32)   &&
          (G_player->pos_y - e->pos_y > -32))
      {
        return 0;
      }

      if ((G_player->pos_x - e->pos_x < 32)     &&
          (G_player->pos_x - e->pos_x >= -16)   &&
          (G_player->pos_y - e->pos_y <= 32)    &&
          (G_player->pos_y - e->pos_y >= -32))
      {
        return 0;
      }

      if ((G_player->pos_x - e->pos_x == 48)  &&
          (G_player->pos_y - e->pos_y < 32)   &&
          (G_player->pos_y - e->pos_y > -32)  &&
          (G_player->action_flags & ENTITY_ACTION_FLAG_MOVING) &&
          ENTITY_DIRECTION_CHECK(G_player, ENTITY_DIRECTION_LEFT))
      {
        return 0;
      }
    }

    /* try moving right */
    logic_attempt_move(e, ENTITY_DIRECTION_RIGHT);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
      return 0;

    /* try moving left */
    logic_attempt_move(e, ENTITY_DIRECTION_LEFT);

    /* if 2nd move attempt was successful, setup animation */
    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      poltergeist_frame_count = e->frame_count;
      entity_set_facing(e, ENTITY_FACING_LEFT);
      animation_setup(e);
      e->frame_count = poltergeist_frame_count;
    }
  }
  /* facing up */
  else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
  {
    /* if player is nearby, return */
    if ((G_player != NULL) && (ENTITY_TYPE_IS_PLAYER(G_player->type)))
    {
      if ((G_player->pos_y - e->pos_y <= -32) &&
          (G_player->pos_y - e->pos_y > -48)  &&
          (G_player->pos_x - e->pos_x < 32)   &&
          (G_player->pos_x - e->pos_x > -32))
      {
        return 0;
      }

      if ((G_player->pos_x - e->pos_x >= -32)   &&
          (G_player->pos_x - e->pos_x <= 32)    &&
          (G_player->pos_y - e->pos_y > -32)    &&
          (G_player->pos_y - e->pos_y <= 16))
      {
        return 0;
      }

      if ((G_player->pos_y - e->pos_y == -48) &&
          (G_player->pos_x - e->pos_x < 32)   &&
          (G_player->pos_x - e->pos_x > -32)  &&
          (G_player->action_flags & ENTITY_ACTION_FLAG_MOVING) &&
          ENTITY_DIRECTION_CHECK(G_player, ENTITY_DIRECTION_DOWN))
      {
        return 0;
      }
    }

    /* try moving up */
    logic_attempt_move(e, ENTITY_DIRECTION_UP);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
      return 0;

    /* try moving down */
    logic_attempt_move(e, ENTITY_DIRECTION_DOWN);

    /* if 2nd move attempt was successful, setup animation */
    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      poltergeist_frame_count = e->frame_count;
      entity_set_facing(e, ENTITY_FACING_DOWN);
      animation_setup(e);
      e->frame_count = poltergeist_frame_count;
    }
  }
  /* facing left */
  else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
  {
    /* if player is nearby, return */
    if ((G_player != NULL) && (ENTITY_TYPE_IS_PLAYER(G_player->type)))
    {
      if ((G_player->pos_x - e->pos_x <= -32) &&
          (G_player->pos_x - e->pos_x > -48)  &&
          (G_player->pos_y - e->pos_y < 32)   &&
          (G_player->pos_y - e->pos_y > -32))
      {
        return 0;
      }

      if ((G_player->pos_x - e->pos_x > -32)    &&
          (G_player->pos_x - e->pos_x <= 16)    &&
          (G_player->pos_y - e->pos_y <= 32)    &&
          (G_player->pos_y - e->pos_y >= -32))
      {
        return 0;
      }

      if ((G_player->pos_x - e->pos_x == -48) &&
          (G_player->pos_y - e->pos_y < 32)   &&
          (G_player->pos_y - e->pos_y > -32)  &&
          (G_player->action_flags & ENTITY_ACTION_FLAG_MOVING) &&
          ENTITY_DIRECTION_CHECK(G_player, ENTITY_DIRECTION_RIGHT))
      {
        return 0;
      }
    }

    /* try moving left */
    logic_attempt_move(e, ENTITY_DIRECTION_LEFT);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
      return 0;

    /* try moving right */
    logic_attempt_move(e, ENTITY_DIRECTION_RIGHT);

    /* if 2nd move attempt was successful, setup animation */
    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      poltergeist_frame_count = e->frame_count;
      entity_set_facing(e, ENTITY_FACING_RIGHT);
      animation_setup(e);
      e->frame_count = poltergeist_frame_count;
    }
  }
  /* facing down */
  else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
  {
    /* if player is nearby, return */
    if ((G_player != NULL) && (ENTITY_TYPE_IS_PLAYER(G_player->type)))
    {
      if ((G_player->pos_y - e->pos_y >= 32)  &&
          (G_player->pos_y - e->pos_y < 48)   &&
          (G_player->pos_x - e->pos_x < 32)   &&
          (G_player->pos_x - e->pos_x > -32))
      {
        return 0;
      }

      if ((G_player->pos_x - e->pos_x >= -32)   &&
          (G_player->pos_x - e->pos_x <= 32)    &&
          (G_player->pos_y - e->pos_y >= -16)   &&
          (G_player->pos_y - e->pos_y < 32))
      {
        return 0;
      }

      if ((G_player->pos_y - e->pos_y == 48)  &&
          (G_player->pos_x - e->pos_x < 32)   &&
          (G_player->pos_x - e->pos_x > -32)  &&
          (G_player->action_flags & ENTITY_ACTION_FLAG_MOVING) &&
          ENTITY_DIRECTION_CHECK(G_player, ENTITY_DIRECTION_UP))
      {
        return 0;
      }
    }

    /* try moving down */
    logic_attempt_move(e, ENTITY_DIRECTION_DOWN);

    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
      return 0;

    /* try moving up */
    logic_attempt_move(e, ENTITY_DIRECTION_UP);

    /* if 2nd move attempt was successful, setup animation */
    if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      poltergeist_frame_count = e->frame_count;
      entity_set_facing(e, ENTITY_FACING_UP);
      animation_setup(e);
      e->frame_count = poltergeist_frame_count;
    }
  }

  return 0;
}

/*******************************************************************************
** logic_enemy_movements()
*******************************************************************************/
short int logic_enemy_movements()
{
  entity* e;

  /* cycle through masks */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_PUMPKINS_GHOSTS_MASKS];
        e != NULL;
        e = e->next)
  {
    /* if mask is already moving, continue */
    if (ENTITY_IS_PERFORMING_ACTION(e))
      continue;

    if ((e->type == ENTITY_TYPE_MASK_HORIZONTAL)  ||
        (e->type == ENTITY_TYPE_MASK_VERTICAL))
    {
      logic_enemy_movement_pattern_back_and_forth(e);
    }
  }

  /* cycle through faeries */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_SNAKES_FAERIES_VENUSIANS];
        e != NULL;
        e = e->next)
  {
    /* if faerie is already moving, continue */
    if (ENTITY_IS_PERFORMING_ACTION(e))
      continue;

    if (e->type == ENTITY_TYPE_FAERIE_HORIZONTAL)
      logic_enemy_movement_pattern_faerie_horizontal(e);
    else if (e->type == ENTITY_TYPE_FAERIE_VERTICAL)
      logic_enemy_movement_pattern_faerie_vertical(e);
  }

  /* cycle through lil bots, wisps */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_LIL_BOTS_WISPS_FROGS];
        e != NULL;
        e = e->next)
  {
    /* if lil bot or wisp is already moving,  */
    /* or if wisp is detonating, continue     */
    if (ENTITY_IS_PERFORMING_ACTION(e) || ENTITY_IS_IN_COOLDOWN(e))
      continue;

    if (e->type == ENTITY_TYPE_LIL_BOT)
      logic_enemy_movement_pattern_back_and_forth_using_facing(e);
    else if (e->type == ENTITY_TYPE_WISP_LEFT_WALL)
      logic_enemy_movement_pattern_follow_left_wall(e);
    else if (e->type == ENTITY_TYPE_WISP_RIGHT_WALL)
      logic_enemy_movement_pattern_follow_right_wall(e);
  }

  /* cycle through imps, jiangshis */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_IMPS_JIANGSHIS];
        e != NULL;
        e = e->next)
  {
    /* if imp or jiangshi is already moving, continue */
    if (ENTITY_IS_PERFORMING_ACTION(e))
      continue;

    if ((e->type == ENTITY_TYPE_IMP_LT) &&
        (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE))
    {
      logic_enemy_movement_pattern_left_turn_using_facing(e);
    }
    else if ( (e->type == ENTITY_TYPE_IMP_RT) &&
              (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE))
    {
      logic_enemy_movement_pattern_right_turn_using_facing(e);
    }
    else if ( (e->type == ENTITY_TYPE_JIANGSHI_LT) &&
              (!(e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)))
    {
      logic_enemy_movement_pattern_left_turn_using_facing(e);
    }
    else if ( (e->type == ENTITY_TYPE_JIANGSHI_RT) &&
              (!(e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)))
    {
      logic_enemy_movement_pattern_right_turn_using_facing(e);
    }
  }

  /* cycle through guardians */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_GUARDIANS];
        e != NULL;
        e = e->next)
  {
    /* if guardian is already moving, continue */
    if (ENTITY_IS_PERFORMING_ACTION(e))
      continue;

    if (e->type == ENTITY_TYPE_GUARDIAN_LT)
      logic_enemy_movement_pattern_left_turn_using_facing(e);
    else if (e->type == ENTITY_TYPE_GUARDIAN_RT)
      logic_enemy_movement_pattern_right_turn_using_facing(e);
  }

  /* cycle through mummies, poltergeists */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_MUMMIES_POLTERGEISTS];
        e != NULL;
        e = e->next)
  {
    /* if mummy or poltergeist is already moving, */
    /* or mummy is disintegrating, continue       */
    if (ENTITY_IS_PERFORMING_ACTION(e) || ENTITY_IS_IN_COOLDOWN(e))
      continue;

    if (e->type == ENTITY_TYPE_MUMMY_LT)
      logic_enemy_movement_pattern_left_turn_using_facing(e);
    else if (e->type == ENTITY_TYPE_MUMMY_RT)
      logic_enemy_movement_pattern_right_turn_using_facing(e);
    else if (e->type == ENTITY_TYPE_POLTERGEIST)
      logic_enemy_movement_pattern_poltergeist(e);
  }

  return 0;
}

/*******************************************************************************
** logic_convey_entities()
*******************************************************************************/
short int logic_convey_entities()
{
  int     i;
  entity* e;

  for (i = 0; i < CATEGORY_NUM_INDICES; i++)
  {
    if (!(CATEGORY_INDEX_CAN_BE_CONVEYED(i)))
      continue;

    e = G_entity_active_list_head[i];

    while (e != NULL)
    {
      /* trigger conveyance */
      if ((e->action_flags & ENTITY_ACTION_FLAG_BEING_CONVEYED) &&
          (!(ENTITY_IS_PERFORMING_ACTION(e))))
      {
        logic_attempt_move(e, e->orientation & ENTITY_DIRECTION_MASK);
        e->action_flags |= ENTITY_ACTION_FLAG_BEING_CONVEYED;

        if (e->type == ENTITY_TYPE_EIGHT_BALL)
        {
          if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_RIGHT))
            entity_set_facing(e, ENTITY_FACING_RIGHT);
          else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_UP))
            entity_set_facing(e, ENTITY_FACING_UP);
          else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_LEFT))
            entity_set_facing(e, ENTITY_FACING_LEFT);
          else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_DOWN))
            entity_set_facing(e, ENTITY_FACING_DOWN);

          animation_setup(e);
        }
      }

      e = e->next;
    }
  }

  return 0;
}

/*******************************************************************************
** logic_all_vials_collected()
*******************************************************************************/
short int logic_all_vials_collected()
{
  entity* e;

  /* open portcullis */
  e = G_entity_active_list_head[CATEGORY_INDEX_PORTCULLIS];

  while (e != NULL)
  {
    if (e->type == ENTITY_TYPE_PORTCULLIS_CLOSED)
    {
      e->update_flags |= ENTITY_UPDATE_FLAG_TRANSFORMING;
    }

    e = e->next;
  }

  /* awaken ghosts */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_PUMPKINS_GHOSTS_MASKS];
        e != NULL;
        e = e->next)
  {
    if ((e->type == ENTITY_TYPE_GHOST) &&
        (!(e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)))
    {
      e->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
      animation_setup(e);
    }
  }

  /* awaken snakes */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_SNAKES_FAERIES_VENUSIANS];
        e != NULL;
        e = e->next)
  {
    if ((e->type == ENTITY_TYPE_SNAKE) &&
        (!(e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)))
    {
      e->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
      animation_setup(e);
    }
  }

  /* awaken imps */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_IMPS_JIANGSHIS];
        e != NULL;
        e = e->next)
  {
    if ((e->type == ENTITY_TYPE_IMP_LT) &&
        (!(e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)))
    {
      e->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
      animation_setup(e);
    }
    else if ( (e->type == ENTITY_TYPE_IMP_RT) &&
              (!(e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)))
    {
      e->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
      animation_setup(e);
    }
  }

  /* awaken witches */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_UNDINES_SORCERESSES_WITCHES];
        e != NULL;
        e = e->next)
  {
    if ((e->type == ENTITY_TYPE_WITCH) &&
        (!(e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)))
    {
      e->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
      animation_setup(e);
    }
  }

  return 0;
}

/*******************************************************************************
** logic_collect_pickups()
*******************************************************************************/
short int logic_collect_pickups(entity* e1)
{
  int                 i;
  int                 low_x;
  int                 low_y;
  collide_grid_space* sp;
  entity*             e2;
  entity*             pickup;

  if (e1 == NULL)
    return 1;

  /* make sure entity is the player in vampire form */
  if (e1->type != ENTITY_TYPE_PLAYER_VAMPIRE)
    return 0;

  /* make sure player is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
    return 0;

  /* determine location of player in grid */
  low_x = (e1->pos_x / 16) - 2;
  low_y = (e1->pos_y / 16) - 4;

  /* make sure player is within the grid */
  if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  /* set space to check as upper left corner */
  sp = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);

  /* check for pickup in this space */
  pickup = NULL;

  for (i = 0; i < sp->num_entities; i++)
  {
    e2 = sp->entities[i];

    if (e1 == e2)
      continue;

    /* make sure entities are on top of each other */
    if ((e1->pos_x != e2->pos_x) || (e1->pos_y != e2->pos_y))
      continue;

    /* if the second entity is a pickup, collect it */
    if (ENTITY_TYPE_IS_PICKUP(e2->type))
    {
      pickup = e2;
      break;
    }
  }

  /* if no pickup found, return */
  if (pickup == NULL)
    return 0;

  /* update global variables as necessary */
  if (pickup->type == ENTITY_TYPE_BLOOD_VIAL)
  {
    G_vials_remaining -= 1;

    if (G_vials_remaining == 0)
    {
      logic_all_vials_collected();
      doremi_play_sfx(SFX_INDEX_PORTCULLIS_OPENING);
    }
    else
    {
      doremi_play_sfx(SFX_INDEX_PICKUP);
    }
  }
  else if (pickup->type == ENTITY_TYPE_BAT_VIAL)
  {
    G_vials_remaining -= 1;
    G_bat_transforms += 1;

    if (G_vials_remaining == 0)
    {
      logic_all_vials_collected();
      doremi_play_sfx(SFX_INDEX_PORTCULLIS_OPENING);
    }
    else
    {
      doremi_play_sfx(SFX_INDEX_PICKUP);
    }
  }
  else if (pickup->type == ENTITY_TYPE_BLUE_MANA)
  {
    G_blue_mana += 1;
    doremi_play_sfx(SFX_INDEX_PICKUP);
  }
  else if (pickup->type == ENTITY_TYPE_GREEN_MANA)
  {
    G_green_mana += 1;
    doremi_play_sfx(SFX_INDEX_PICKUP);
  }
  else if (pickup->type == ENTITY_TYPE_FLOPPY_DISK_3_AND_1_2)
  {
    G_game_state_flags |= GLOBAL_GAME_STATE_FLAG_FLOPPY_COLLECTED;
    doremi_play_sfx(SFX_INDEX_PICKUP);
  }
  else if (pickup->type == ENTITY_TYPE_FLOPPY_DISK_5_AND_1_4)
  {
    G_game_state_flags |= GLOBAL_GAME_STATE_FLAG_FLOPPY_COLLECTED;
    doremi_play_sfx(SFX_INDEX_PICKUP);
  }
  else if (pickup->type == ENTITY_TYPE_COBWEB)
  {
    doremi_play_sfx(SFX_INDEX_COBWEB_CLEAR);
  }

  /* set pickup to despawn */
  pickup->collision_flags |= ENTITY_COLLISION_FLAG_COLLECTED;

  return 0;
}

/*******************************************************************************
** logic_check_if_over_water()
*******************************************************************************/
short int logic_check_if_over_water(entity* e1)
{
  int                 i;
  int                 j;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp[4];
  entity*             e2;
  entity*             water[4];

  if (e1 == NULL)
    return 1;

  /* make sure entity can fall into water */
  if (ENTITY_TYPE_IS_FLYING(e1->type)  ||
      ENTITY_TYPE_IS_SPELL(e1->type))
  {
    return 0;
  }

  /* make sure entity is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
    return 0;

  /* determine location of entity in grid */
  low_x = (e1->pos_x / 16) - 2;
  high_x = low_x + 1;

  low_y = (e1->pos_y / 16) - 4;
  high_y = low_y + 1;

  /* make sure entity is within the grid */
  if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((high_x < 0) || (high_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  if ((high_y < 0) || (high_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  /* set spaces to check */
  sp[0] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[1] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[2] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + high_y]);
  sp[3] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + high_y]);

  /* check for water tile in each space */
  for (i = 0; i < 4; i++)
  {
    water[i] = NULL;

    for (j = 0; j < sp[i]->num_entities; j++)
    {
      e2 = sp[i]->entities[j];

      if (e1 == e2)
        continue;

      /* if the second entity is a water tile, store it */
      if (e2->type == ENTITY_TYPE_WATER)
      {
        water[i] = e2;
        break;
      }
    }
  }

  /* check if the entity is completely over water */
  if ((water[0] != NULL) && (water[1] != NULL) && 
      (water[2] != NULL) && (water[3] != NULL))
  {
    if ((ENTITY_TYPE_IS_SUBMERGABLE(e1->type))  &&
        (!(ENTITY_TYPE_IS_VANISHED_DIE(e1->type))))
    {
      for (i = 0; i < 4; i++)
      {
        water[i]->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
      }
    }

    e1->update_flags |= ENTITY_UPDATE_FLAG_FELL_INTO_WATER;
  }

  return 0;
}

/*******************************************************************************
** logic_check_if_over_ice()
*******************************************************************************/
short int logic_check_if_over_ice(entity* e1)
{
  int                 i;
  int                 j;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp[2];
  entity*             e2;
  entity*             ice[2];

  if (e1 == NULL)
    return 1;

  /* make sure entity can slip on ice */
  if (!(ENTITY_TYPE_IS_PLAYER(e1->type)           ||
        ENTITY_TYPE_IS_ENEMY(e1->type)            ||
        ENTITY_TYPE_IS_PUSHABLE_OBJECT(e1->type)  ||
        ENTITY_TYPE_IS_ICE_CUBE(e1->type)))
  {
    return 0;
  }

  if (ENTITY_TYPE_IS_STONE(e1->type)        ||
      ENTITY_TYPE_IS_FLOATING(e1->type)     ||
      ENTITY_TYPE_IS_FLYING(e1->type)       ||
      (e1->type == ENTITY_TYPE_EIGHT_BALL))
  {
    return 0;
  }

  /* clear slipping flag */
  e1->action_flags &= ~ENTITY_ACTION_FLAG_SLIPPING;

  /* make sure entity is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
    return 0;

  /* determine location of entity in grid */
  low_x = (e1->pos_x / 16) - 2;
  high_x = low_x + 1;

  low_y = (e1->pos_y / 16) - 4;
  high_y = low_y + 1;

  /* make sure entity is within the grid */
  if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((high_x < 0) || (high_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  if ((high_y < 0) || (high_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  /* set spaces to check */
  if (ENTITY_DIRECTION_CHECK(e1, ENTITY_DIRECTION_RIGHT))
  {
    sp[0] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);
    sp[1] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + high_y]);
  }
  else if (ENTITY_DIRECTION_CHECK(e1, ENTITY_DIRECTION_UP))
  {
    sp[0] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + high_y]);
    sp[1] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + high_y]);
  }
  else if (ENTITY_DIRECTION_CHECK(e1, ENTITY_DIRECTION_LEFT))
  {
    sp[0] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + low_y]);
    sp[1] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + high_y]);
  }
  else if (ENTITY_DIRECTION_CHECK(e1, ENTITY_DIRECTION_DOWN))
  {
    sp[0] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);
    sp[1] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + low_y]);
  }
  else
    return 0;

  /* check for ice tile in each space */
  for (i = 0; i < 2; i++)
  {
    ice[i] = NULL;

    for (j = 0; j < sp[i]->num_entities; j++)
    {
      e2 = sp[i]->entities[j];

      if (e1 == e2)
        continue;

      /* if the second entity is an ice tile, store it */
      if ((e2->type == ENTITY_TYPE_ICE) ||
          (e2->type == ENTITY_TYPE_ICE_CUBE_SUBMERGED))
      {
        ice[i] = e2;
        break;
      }
    }
  }

  /* check if the entity's back half is over ice */
  if ((ice[0] != NULL) && (ice[1] != NULL))
    e1->action_flags |= ENTITY_ACTION_FLAG_SLIPPING;

  return 0;
}

/*******************************************************************************
** logic_check_if_over_conveyer()
*******************************************************************************/
short int logic_check_if_over_conveyer(entity* e1)
{
  int                 i;
  int                 j;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp[4];
  entity*             e2;
  entity*             conveyer[4];
  unsigned char       facing[4];

  if (e1 == NULL)
    return 1;

  /* make sure entity is conveyable */
  if (!(ENTITY_TYPE_IS_CONVEYABLE(e1->type)))
    return 0;

  /* clear being conveyed flag */
  e1->action_flags &= ~ENTITY_ACTION_FLAG_BEING_CONVEYED;

  /* make sure entity is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
    return 0;

  /* determine location of entity in grid */
  low_x = (e1->pos_x / 16) - 2;
  high_x = low_x + 1;

  low_y = (e1->pos_y / 16) - 4;
  high_y = low_y + 1;

  /* make sure entity is within the grid */
  if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((high_x < 0) || (high_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  if ((high_y < 0) || (high_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  /* set spaces to check */
  sp[0] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[1] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[2] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + high_y]);
  sp[3] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + high_y]);

  /* check for conveyer in each space */
  for (i = 0; i < 4; i++)
  {
    conveyer[i] = NULL;

    for (j = 0; j < sp[i]->num_entities; j++)
    {
      e2 = sp[i]->entities[j];

      if (e1 == e2)
        continue;

      /* if the second entity is a conveyer, store it */
      if (ENTITY_TYPE_IS_CONVEYER(e2->type))
      {
        conveyer[i] = e2;
        facing[i] = e2->orientation & ENTITY_FACING_MASK;
        break;
      }
    }
  }

  /* check if conveyed right */
  if ((conveyer[0] != NULL) && (facing[0] == ENTITY_FACING_RIGHT) &&
      (conveyer[2] != NULL) && (facing[2] == ENTITY_FACING_RIGHT) &&
      (conveyer[0]->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)     &&
      (conveyer[2]->update_flags & ENTITY_UPDATE_FLAG_ACTIVE))
  {
    e1->action_flags |= ENTITY_ACTION_FLAG_BEING_CONVEYED;
    e1->orientation &= ~ENTITY_DIRECTION_MASK;
    e1->orientation |= ENTITY_DIRECTION_RIGHT;
  }
  /* check if conveyed up */
  else if ( (conveyer[2] != NULL) && (facing[2] == ENTITY_FACING_UP)  &&
            (conveyer[3] != NULL) && (facing[3] == ENTITY_FACING_UP)  &&
            (conveyer[2]->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)   &&
            (conveyer[3]->update_flags & ENTITY_UPDATE_FLAG_ACTIVE))
  {
    e1->action_flags |= ENTITY_ACTION_FLAG_BEING_CONVEYED;
    e1->orientation &= ~ENTITY_DIRECTION_MASK;
    e1->orientation |= ENTITY_DIRECTION_UP;
  }
  /* check if conveyed left */
  else if ( (conveyer[1] != NULL) && (facing[1] == ENTITY_FACING_LEFT)  &&
            (conveyer[3] != NULL) && (facing[3] == ENTITY_FACING_LEFT)  &&
            (conveyer[1]->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)     &&
            (conveyer[3]->update_flags & ENTITY_UPDATE_FLAG_ACTIVE))
  {
    e1->action_flags |= ENTITY_ACTION_FLAG_BEING_CONVEYED;
    e1->orientation &= ~ENTITY_DIRECTION_MASK;
    e1->orientation |= ENTITY_DIRECTION_LEFT;
  }
  /* check if conveyed down */
  else if ( (conveyer[0] != NULL) && (facing[0] == ENTITY_FACING_DOWN)  &&
            (conveyer[1] != NULL) && (facing[1] == ENTITY_FACING_DOWN)  &&
            (conveyer[0]->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)     &&
            (conveyer[1]->update_flags & ENTITY_UPDATE_FLAG_ACTIVE))
  {
    e1->action_flags |= ENTITY_ACTION_FLAG_BEING_CONVEYED;
    e1->orientation &= ~ENTITY_DIRECTION_MASK;
    e1->orientation |= ENTITY_DIRECTION_DOWN;
  }

  return 0;
}

/*******************************************************************************
** logic_check_if_over_candle()
*******************************************************************************/
short int logic_check_if_over_candle(entity* e1)
{
  int                 i;
  int                 j;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp[4];
  entity*             e2;

  if (e1 == NULL)
    return 1;

  /* make sure entity is a flying entity */
  if (!(ENTITY_TYPE_IS_FLYING(e1->type)))
    return 0;

  /* make sure entity is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
    return 0;

  /* determine location of entity in grid */
  low_x = (e1->pos_x / 16) - 2;
  high_x = low_x + 1;

  low_y = (e1->pos_y / 16) - 4;
  high_y = low_y + 1;

  /* make sure entity is within the grid */
  if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((high_x < 0) || (high_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  if ((high_y < 0) || (high_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  /* set spaces to check */
  sp[0] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[1] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[2] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + high_y]);
  sp[3] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + high_y]);

  /* check for lit candle in each space */
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < sp[i]->num_entities; j++)
    {
      e2 = sp[i]->entities[j];

      if (e1 == e2)
        continue;

      /* if the second entity is a lit candle, */
      /* destroy first entity and return */
      if (e2->type == ENTITY_TYPE_CANDLE_LIT)
      {
        e1->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
        return 0;
      }
    }
  }

  return 0;
}

/*******************************************************************************
** logic_check_if_touching_mahjong_tile()
*******************************************************************************/
short int logic_check_if_touching_mahjong_tile(entity* e1)
{
  int                 i;
  int                 j;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp[4];
  collide_grid_space* neighbor[8];
  entity*             e2;

  if (e1 == NULL)
    return 1;

  /* make sure entity is a mahjong tile */
  if (!(ENTITY_TYPE_IS_MAHJONG_TILE(e1->type)))
    return 0;

  /* make sure entity is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
    return 0;

  /* determine location of entity in grid */
  low_x = (e1->pos_x / 16) - 2;
  high_x = low_x + 1;

  low_y = (e1->pos_y / 16) - 4;
  high_y = low_y + 1;

  /* make sure entity is within the grid */
  if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((high_x < 0) || (high_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  if ((high_y < 0) || (high_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  /* set spaces to check */
  sp[0] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[1] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[2] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + high_y]);
  sp[3] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + high_y]);

  /* set neighboring spaces to check */
  if (low_x > 0)
  {
    neighbor[0] = &(G_collide_grid[(low_x - 1) * COLLIDE_GRID_HEIGHT + low_y]);
    neighbor[1] = &(G_collide_grid[(low_x - 1) * COLLIDE_GRID_HEIGHT + high_y]);
  }
  else
  {
    neighbor[0] = NULL;
    neighbor[1] = NULL;
  }

  if (high_x < COLLIDE_GRID_WIDTH - 1)
  {
    neighbor[2] = &(G_collide_grid[(high_x + 1) * COLLIDE_GRID_HEIGHT + low_y]);
    neighbor[3] = &(G_collide_grid[(high_x + 1) * COLLIDE_GRID_HEIGHT + high_y]);
  }
  else
  {
    neighbor[2] = NULL;
    neighbor[3] = NULL;
  }

  if (low_y > 0)
  {
    neighbor[4] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + (low_y - 1)]);
    neighbor[5] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + (low_y - 1)]);
  }
  else
  {
    neighbor[4] = NULL;
    neighbor[5] = NULL;
  }

  if (high_y < COLLIDE_GRID_HEIGHT - 1)
  {
    neighbor[6] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + (high_y + 1)]);
    neighbor[7] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + (high_y + 1)]);
  }
  else
  {
    neighbor[6] = NULL;
    neighbor[7] = NULL;
  }

  /* check for submerged mahjong tile under entity */
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < sp[i]->num_entities; j++)
    {
      e2 = sp[i]->entities[j];

      if (e1 == e2)
        continue;

      /* if a match is found, activate both tiles */
      if (( (e1->type == ENTITY_TYPE_MAHJONG_TILE_EAST) &&
            (e2->type == ENTITY_TYPE_MAHJONG_TILE_EAST_SUBMERGED))  ||
          ( (e1->type == ENTITY_TYPE_MAHJONG_TILE_NORTH) &&
            (e2->type == ENTITY_TYPE_MAHJONG_TILE_NORTH_SUBMERGED)) ||
          ( (e1->type == ENTITY_TYPE_MAHJONG_TILE_WEST) &&
            (e2->type == ENTITY_TYPE_MAHJONG_TILE_WEST_SUBMERGED))  ||
          ( (e1->type == ENTITY_TYPE_MAHJONG_TILE_SOUTH) &&
            (e2->type == ENTITY_TYPE_MAHJONG_TILE_SOUTH_SUBMERGED)))
      {
        e1->update_flags |= ENTITY_UPDATE_FLAG_COOLDOWN;
        e1->cooldown_count = ENTITY_COOLDOWN_TIME_MAHJONG_TILE;
        animation_setup(e1);

        e2->update_flags |= ENTITY_UPDATE_FLAG_COOLDOWN;
        e2->cooldown_count = ENTITY_COOLDOWN_TIME_MAHJONG_TILE;
        animation_setup(e2);

        doremi_play_sfx(SFX_INDEX_MAHJONG_MATCH);
      }
    }
  }

  /* check for mahjong tile in neighboring spaces */
  for (i = 0; i < 8; i++)
  {
    if (neighbor[i] == NULL)
      continue;

    for (j = 0; j < neighbor[i]->num_entities; j++)
    {
      e2 = neighbor[i]->entities[j];

      if (e1 == e2)
        continue;

      /* if a match is found, activate both tiles */
      if ((ENTITY_TYPE_IS_MAHJONG_TILE(e2->type)) &&
          (e1->type == e2->type))
      {
        e1->update_flags |= ENTITY_UPDATE_FLAG_COOLDOWN;
        e1->cooldown_count = ENTITY_COOLDOWN_TIME_MAHJONG_TILE;
        animation_setup(e1);

        e2->update_flags |= ENTITY_UPDATE_FLAG_COOLDOWN;
        e2->cooldown_count = ENTITY_COOLDOWN_TIME_MAHJONG_TILE;
        animation_setup(e2);

        doremi_play_sfx(SFX_INDEX_MAHJONG_MATCH);
      }
    }
  }

  return 0;
}

/*******************************************************************************
** logic_check_damage_on_spawn()
*******************************************************************************/
short int logic_check_damage_on_spawn(entity* e1)
{
  int                 i;
  int                 j;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp[4];
  entity*             e2;

  if (e1 == NULL)
    return 1;

  /* make sure entity is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
  {
    e1->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
    return 0;
  }

  /* determine location of entity in grid */
  low_x = (e1->pos_x / 16) - 2;
  high_x = low_x + 1;

  low_y = (e1->pos_y / 16) - 4;
  high_y = low_y + 1;

  /* make sure entity is within the grid */
  if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
  {
    e1->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
    return 0;
  }

  if ((high_x < 0) || (high_x > COLLIDE_GRID_WIDTH - 1))
  {
    e1->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
    return 0;
  }

  if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
  {
    e1->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
    return 0;
  }

  if ((high_y < 0) || (high_y > COLLIDE_GRID_HEIGHT - 1))
  {
    e1->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
    return 0;
  }

  /* set spaces to check */
  sp[0] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[1] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[2] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + high_y]);
  sp[3] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + high_y]);

  /* check for damage due to collision */
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < sp[i]->num_entities; j++)
    {
      e2 = sp[i]->entities[j];

      /* check if spell spawned on a reflecter */
      if ((e1->trigger_affect & ENTITY_TRIGGER_FLAG_REFLECTER) &&
          (e2->trigger_attribute & ENTITY_TRIGGER_FLAG_REFLECTER))
      {
        logic_set_reflection_flags(e1, e2);

        /* set overlap */
        if ((e1->special_flags & ENTITY_SPECIAL_FLAG_REFLECT_REVERSE) ||
            (e1->special_flags & ENTITY_SPECIAL_FLAG_REFLECT_BANK))
        {
          e1->special_flags |= ENTITY_SPECIAL_FLAG_OVERLAP;

          if ((ENTITY_DIRECTION_CHECK(e1, ENTITY_DIRECTION_RIGHT)) &&
              (e2->pos_x - e1->pos_x < 16))
          {
            e1->action_flags |= ENTITY_ACTION_FLAG_MODE;
          }
          else if ( (ENTITY_DIRECTION_CHECK(e1, ENTITY_DIRECTION_UP)) &&
                    (e1->pos_y - e2->pos_y < 16))
          {
            e1->action_flags |= ENTITY_ACTION_FLAG_MODE;
          }
          else if ( (ENTITY_DIRECTION_CHECK(e1, ENTITY_DIRECTION_LEFT)) &&
                    (e1->pos_x - e2->pos_x < 16))
          {
            e1->action_flags |= ENTITY_ACTION_FLAG_MODE;
          }
          else if ( (ENTITY_DIRECTION_CHECK(e1, ENTITY_DIRECTION_DOWN))  &&
                    (e2->pos_y - e1->pos_y < 16))
          {
            e1->action_flags |= ENTITY_ACTION_FLAG_MODE;
          }

          continue;
        }
      }

      /* check for damage done by this entity to another entity */
      if (e1->damage_affect & e2->damage_attribute)
      {
        pair_trees_and_lists_add_collision(e1, e2);
      }

      /* check for reciprocal damage */
      if (e2->damage_affect & e1->damage_attribute)
      {
        pair_trees_and_lists_add_collision(e1, e2);
      }
    }
  }

  return 0;
}

/*******************************************************************************
** logic_trigger_floor_spike()
*******************************************************************************/
short int logic_trigger_floor_spike(entity* e1)
{
  int                 i;
  int                 x;
  int                 y;
  collide_grid_space* sp;
  entity*             e2;

  if (e1 == NULL)
    return 1;

  /* make sure entity is a floor spike in down position */
  if (!(ENTITY_TYPE_IS_FLOOR_SPIKE_DOWN(e1->type)))
  {
    return 0;
  }

  /* make sure entity is inside a single grid space     */
  /* (i.e., its center is at a grid space center)       */
  if ((e1->pos_x % 16 != 8) || (e1->pos_y % 16 != 8))
    return 0;

  /* determine location of entity in grid */
  x = ((e1->pos_x - 8) / 16) - 1;
  y = ((e1->pos_y - 8) / 16) - 3;

  /* make sure entity is within the grid */
  if ((x < 0) || (x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((y < 0) || (y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  /* set grid space to check */
  sp = &(G_collide_grid[x * COLLIDE_GRID_HEIGHT + y]);

  /* check entities in grid space for any obstructions */
  for (i = 0; i < sp->num_entities; i++)
  {
    e2 = sp->entities[i];

    if (e1 == e2)
      continue;

    /* if an obstruction is found, cancel this trigger */
    if ((!(ENTITY_TYPE_IS_FLYING(e2->type)))  &&
        (!(ENTITY_TYPE_IS_SPELL(e2->type)))   &&
        (!(ENTITY_TYPE_IS_FLASK(e2->type))))
    {
      return 0;
    }

    /* if flask is above this floor spike, set collision flags */
    if (ENTITY_TYPE_IS_FLASK(e2->type))
    {
      e1->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;

      /* increment lost hp count */
      if ((!(e2->collision_flags & ENTITY_COLLISION_FLAG_LOST_1_HP))  &&
          (!(e2->collision_flags & ENTITY_COLLISION_FLAG_LOST_2_HP)))
      {
        e2->collision_flags |= ENTITY_COLLISION_FLAG_LOST_1_HP;
      }
      else if ( (e2->collision_flags & ENTITY_COLLISION_FLAG_LOST_1_HP)     &&
                (!(e2->collision_flags & ENTITY_COLLISION_FLAG_LOST_2_HP)))
      {
        e2->collision_flags &= ~ENTITY_COLLISION_FLAG_LOST_1_HP;
        e2->collision_flags |= ENTITY_COLLISION_FLAG_LOST_2_HP;
      }
      else if ( (!(e2->collision_flags & ENTITY_COLLISION_FLAG_LOST_1_HP))  &&
                (e2->collision_flags & ENTITY_COLLISION_FLAG_LOST_2_HP))
      {
        e2->collision_flags |= ENTITY_COLLISION_FLAG_LOST_1_HP;
      }
      else if ( (e2->collision_flags & ENTITY_COLLISION_FLAG_LOST_1_HP)     &&
                (e2->collision_flags & ENTITY_COLLISION_FLAG_LOST_2_HP))
      {
        e2->collision_flags &= ~ENTITY_COLLISION_FLAG_LOST_1_HP;
        e2->collision_flags &= ~ENTITY_COLLISION_FLAG_LOST_2_HP;
        e2->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
      }
    }
  }

  /* trigger floor spike if no obstruction was found, */
  /* and the spike was not destroyed by a flask       */
  if (!(e1->collision_flags & ENTITY_COLLISION_FLAG_DESTROYED))
    e1->update_flags |= ENTITY_UPDATE_FLAG_TRANSFORMING;

  return 0;
}

/*******************************************************************************
** logic_trigger_bridge()
*******************************************************************************/
short int logic_trigger_bridge(entity* e1)
{
  int                 i;
  int                 j;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp[4];
  entity*             e2;

  if (e1 == NULL)
    return 1;

  /* make sure entity is a bridge */
  if (!(ENTITY_TYPE_IS_WOOD_OR_CRACKED_BRIDGE(e1->type)))
    return 0;

  /* make sure this entity is not already awaiting destruction */
  if (e1->special_flags & ENTITY_SPECIAL_FLAG_AWAITING_DESTROY)
    return 0;

  /* make sure entity is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
    return 0;

  /* determine location of entity in grid */
  low_x = (e1->pos_x / 16) - 2;
  high_x = low_x + 1;

  low_y = (e1->pos_y / 16) - 4;
  high_y = low_y + 1;

  /* make sure entity is within the grid */
  if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((high_x < 0) || (high_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  if ((high_y < 0) || (high_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  /* set spaces to check */
  sp[0] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[1] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[2] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + high_y]);
  sp[3] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + high_y]);

  /* check spaces */
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < sp[i]->num_entities; j++)
    {
      e2 = sp[i]->entities[j];

      if (e1 == e2)
        continue;

      /* if an object is on the bridge, cancel this trigger */
      if ((!(ENTITY_TYPE_IS_FLYING(e2->type)))  &&
          (!(ENTITY_TYPE_IS_SPELL(e2->type))))
      {
        return 0;
      }
    }
  }

  /* collapse bridge if it is clear */
  if ((e1->type == ENTITY_TYPE_BRIDGE_WOOD_VERTICAL)  ||
      (e1->type == ENTITY_TYPE_BRIDGE_WOOD_HORIZONTAL))
  {
    e1->update_flags |= ENTITY_UPDATE_FLAG_TRANSFORMING;
  }
  else if ( (e1->type == ENTITY_TYPE_BRIDGE_CRACKED_VERTICAL)   ||
            (e1->type == ENTITY_TYPE_BRIDGE_CRACKED_HORIZONTAL))
  {
    e1->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
  }

  return 0;
}

/*******************************************************************************
** logic_activate_floor_triggers()
*******************************************************************************/
short int logic_activate_floor_triggers()
{
  entity* e;

  /* cycle through floor spikes */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_FLOOR_SPIKES];
        e != NULL;
        e = e->next)
  {
    if (ENTITY_TYPE_IS_FLOOR_SPIKE_DOWN(e->type))
    {
      if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
        logic_trigger_floor_spike(e);
    }
  }

  /* cycle through bridges */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_BRIDGES_SUBMERGED];
        e != NULL;
        e = e->next)
  {
    if (ENTITY_TYPE_IS_WOOD_OR_CRACKED_BRIDGE(e->type))
    {
      if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
        logic_trigger_bridge(e);
    }
  }

  return 0;
}

/*******************************************************************************
** logic_set_floor_triggers()
*******************************************************************************/
short int logic_set_floor_triggers(entity* e1)
{
  int                 i;
  int                 j;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp[4];
  entity*             e2;

  if (e1 == NULL)
    return 1;

  /* make sure entity can affect floor tiles by walking on them */
  if (!(ENTITY_TYPE_IS_PLAYER(e1->type) || 
        ENTITY_TYPE_IS_ENEMY(e1->type)))
  {
    return 0;
  }

  if (ENTITY_TYPE_IS_FLYING(e1->type)   || 
      ENTITY_TYPE_IS_FLOATING(e1->type))
  {
    return 0;
  }

  /* make sure entity is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
    return 0;

  /* determine location of entity in grid */
  low_x = (e1->pos_x / 16) - 2;
  high_x = low_x + 1;

  low_y = (e1->pos_y / 16) - 4;
  high_y = low_y + 1;

  /* make sure entity is within the grid */
  if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((high_x < 0) || (high_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  if ((high_y < 0) || (high_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  /* set spaces to check */
  sp[0] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[1] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[2] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + high_y]);
  sp[3] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + high_y]);

  /* check spaces */
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < sp[i]->num_entities; j++)
    {
      e2 = sp[i]->entities[j];

      /* floor spikes */
      if (ENTITY_TYPE_IS_FLOOR_SPIKE_DOWN(e2->type))
      {
        e2->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
      }
      /* wooden bridges */
      else if (ENTITY_TYPE_IS_WOOD_OR_CRACKED_BRIDGE(e2->type))
      {
        if ((e1->pos_x == e2->pos_x) && (e1->pos_y == e2->pos_y))
        {
          e2->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
        }
      }
    }
  }

  return 0;
}

/*******************************************************************************
** logic_trigger_venusian_root()
*******************************************************************************/
short int logic_trigger_venusian_root(entity* e1)
{
  int                 i;
  int                 j;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp[4];
  entity*             e2;
  entity*             new_e;
  int                 venusian_frame_count;

  if (e1 == NULL)
    return 1;

  /* make sure entity is a venusian root */
  if (e1->type != ENTITY_TYPE_VENUSIAN_ROOT)
    return 0;

  /* make sure entity is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
    return 0;

  /* determine venusian frame count */
  e2 = G_entity_active_list_head[CATEGORY_INDEX_SNAKES_FAERIES_VENUSIANS];

  if (e2 == NULL)
    venusian_frame_count = 0;
  else
    venusian_frame_count = e2->frame_count;

  /* determine location of entity in grid */
  low_x = (e1->pos_x / 16) - 2;
  high_x = low_x + 1;

  low_y = (e1->pos_y / 16) - 4;
  high_y = low_y + 1;

  /* make sure entity is within the grid */
  if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((high_x < 0) || (high_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  if ((high_y < 0) || (high_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  /* set spaces to check */
  sp[0] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[1] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[2] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + high_y]);
  sp[3] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + high_y]);

  /* check spaces */
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < sp[i]->num_entities; j++)
    {
      e2 = sp[i]->entities[j];

      if (e1 == e2)
        continue;

      /* if a venusian is found above the root, deactivate root */
      if (e2->type == ENTITY_TYPE_VENUSIAN)
      {
        e1->update_flags &= ~ENTITY_UPDATE_FLAG_ACTIVE;
        return 0;
      }
      /* otherwise, cancel this trigger if obstruction is found */
      else if (e2->type != ENTITY_TYPE_GRASS)
      {
        return 0;
      }
    }
  }

  /* spawn venusian if it is clear */
  new_e = world_spawn_entity(ENTITY_TYPE_VENUSIAN, e1->pos_x, e1->pos_y);
  collide_grid_add_entity(new_e);
  animation_setup(new_e);
  new_e->frame_count = venusian_frame_count;
  e1->update_flags &= ~ENTITY_UPDATE_FLAG_ACTIVE;

  world_spawn_particles_transform(new_e);
  doremi_play_sfx(SFX_INDEX_VENUSIAN_APPEAR);

  return 0;
}

/*******************************************************************************
** logic_activate_venusian_roots()
*******************************************************************************/
short int logic_activate_venusian_roots()
{
  entity* e;

  /* cycle through venusian roots */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_VENUSIAN_ROOTS];
        e != NULL;
        e = e->next)
  {
    if ((e->type == ENTITY_TYPE_VENUSIAN_ROOT) &&
        (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE))
    {
      logic_trigger_venusian_root(e);
    }
  }

  return 0;
}

/*******************************************************************************
** logic_set_venusian_roots()
*******************************************************************************/
short int logic_set_venusian_roots(entity* e1)
{
  int                 i;
  int                 j;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp[4];
  entity*             e2;

  if (e1 == NULL)
    return 1;

  /* make sure entity is a venusian */
  if (e1->type != ENTITY_TYPE_VENUSIAN)
  {
    return 0;
  }

  /* make sure entity is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
    return 0;

  /* determine location of entity in grid */
  low_x = (e1->pos_x / 16) - 2;
  high_x = low_x + 1;

  low_y = (e1->pos_y / 16) - 4;
  high_y = low_y + 1;

  /* make sure entity is within the grid */
  if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((high_x < 0) || (high_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  if ((high_y < 0) || (high_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  /* set spaces to check */
  sp[0] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[1] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[2] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + high_y]);
  sp[3] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + high_y]);

  /* check spaces */
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < sp[i]->num_entities; j++)
    {
      e2 = sp[i]->entities[j];

      if (e1 == e2)
        continue;

      /* venusian root */
      if ((e2->type == ENTITY_TYPE_VENUSIAN_ROOT) &&
          (!(e2->update_flags & ENTITY_UPDATE_FLAG_COOLDOWN)))
      {
        e2->update_flags |= ENTITY_UPDATE_FLAG_COOLDOWN;
        e2->cooldown_count = ENTITY_COOLDOWN_TIME_VENUSIAN;
      }
    }
  }

  return 0;
}

/*******************************************************************************
** logic_press_switches()
*******************************************************************************/
short int logic_press_switches(entity* e1)
{
  int                 i;
  int                 j;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp[4];
  entity*             e2;

  if (e1 == NULL)
    return 1;

  /* make sure entity can affect switches by walking on them */
  if (ENTITY_TYPE_IS_FLYING(e1->type)       ||
      ENTITY_TYPE_IS_FLOATING(e1->type)     ||
      ENTITY_TYPE_IS_SPELL(e1->type)        ||
      ENTITY_TYPE_IS_VANISHED_DIE(e1->type))
  {
    return 0;
  }

  /* make sure entity is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
    return 0;

  /* determine location of entity in grid */
  low_x = (e1->pos_x / 16) - 2;
  high_x = low_x + 1;

  low_y = (e1->pos_y / 16) - 4;
  high_y = low_y + 1;

  /* make sure entity is within the grid */
  if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((high_x < 0) || (high_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  if ((high_y < 0) || (high_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  /* set spaces to check */
  sp[0] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[1] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[2] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + high_y]);
  sp[3] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + high_y]);

  /* check spaces */
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < sp[i]->num_entities; j++)
    {
      e2 = sp[i]->entities[j];

      /* spin switches */
      if ((ENTITY_TYPE_IS_SPIN_SWITCH(e2->type))  &&
          (!(e2->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)))
      {
        if (e2->type == ENTITY_TYPE_SPIN_SWITCH_RED_CCW)
          G_spin_switch_flags |= GLOBAL_SPIN_SWITCH_FLAG_RED_CCW;
        else if (e2->type == ENTITY_TYPE_SPIN_SWITCH_RED_CW)
          G_spin_switch_flags |= GLOBAL_SPIN_SWITCH_FLAG_RED_CW;
        else if (e2->type == ENTITY_TYPE_SPIN_SWITCH_GREEN_CCW)
          G_spin_switch_flags |= GLOBAL_SPIN_SWITCH_FLAG_GREEN_CCW;
        else if (e2->type == ENTITY_TYPE_SPIN_SWITCH_GREEN_CW)
          G_spin_switch_flags |= GLOBAL_SPIN_SWITCH_FLAG_GREEN_CW;
        else if (e2->type == ENTITY_TYPE_SPIN_SWITCH_BROWN_CCW)
          G_spin_switch_flags |= GLOBAL_SPIN_SWITCH_FLAG_BROWN_CCW;
        else if (e2->type == ENTITY_TYPE_SPIN_SWITCH_BROWN_CW)
          G_spin_switch_flags |= GLOBAL_SPIN_SWITCH_FLAG_BROWN_CW;

        e2->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
        animation_setup(e2);

        /* play sfx */
        if ((e2->type == ENTITY_TYPE_SPIN_SWITCH_RED_CCW)   ||
            (e2->type == ENTITY_TYPE_SPIN_SWITCH_GREEN_CCW) ||
            (e2->type == ENTITY_TYPE_SPIN_SWITCH_BROWN_CCW))
        {
          doremi_play_sfx(SFX_INDEX_TOGGLE_UP);
        }
        else if ( (e2->type == ENTITY_TYPE_SPIN_SWITCH_RED_CW)    ||
                  (e2->type == ENTITY_TYPE_SPIN_SWITCH_GREEN_CW)  ||
                  (e2->type == ENTITY_TYPE_SPIN_SWITCH_BROWN_CW))
        {
          doremi_play_sfx(SFX_INDEX_TOGGLE_DOWN);
        }
      }
      /* number switches */
      else if ( (ENTITY_TYPE_IS_NUMBER_SWITCH(e2->type))  &&
                (!(e2->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)))
      {
        e2->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
        animation_setup(e2);
      }
    }
  }

  return 0;
}

/*******************************************************************************
** logic_check_active_switches()
*******************************************************************************/
short int logic_check_active_switches()
{
  int                 i;
  int                 j;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp[4];
  entity*             e1;
  entity*             e2;

  /* clear number switch flags */
  G_number_switch_flags = GLOBAL_NUMBER_SWITCH_FLAGS_CLEAR;

  /* cycle through switches */
  for ( e1 = G_entity_active_list_head[CATEGORY_INDEX_SWITCHES];
        e1 != NULL;
        e1 = e1->next)
  {
    if (e1->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    {
      /* make sure entity is "snapped onto the grid"        */
      /* (i.e., its center is at a grid space intersection) */
      if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
        continue;

      /* determine location of entity in grid */
      low_x = (e1->pos_x / 16) - 2;
      high_x = low_x + 1;

      low_y = (e1->pos_y / 16) - 4;
      high_y = low_y + 1;

      /* make sure entity is within the grid */
      if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
        continue;

      if ((high_x < 0) || (high_x > COLLIDE_GRID_WIDTH - 1))
        continue;

      if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
        continue;

      if ((high_y < 0) || (high_y > COLLIDE_GRID_HEIGHT - 1))
        continue;

      /* set spaces to check */
      sp[0] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);
      sp[1] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + low_y]);
      sp[2] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + high_y]);
      sp[3] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + high_y]);

      /* clear active flag */
      e1->update_flags &= ~ENTITY_UPDATE_FLAG_ACTIVE;

      /* check for entity in each space */
      for (i = 0; i < 4; i++)
      {
        for (j = 0; j < sp[i]->num_entities; j++)
        {
          e2 = sp[i]->entities[j];

          if (e1 == e2)
            continue;

          if (!(ENTITY_TYPE_IS_FLYING(e2->type)         ||
                ENTITY_TYPE_IS_FLOATING(e2->type)       ||
                ENTITY_TYPE_IS_SPELL(e2->type)          ||
                ENTITY_TYPE_IS_VANISHED_DIE(e2->type)))
          {
            e1->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
          }
        }
      }

      /* if active flag was not set, setup animation */
      if (!(e1->update_flags & ENTITY_UPDATE_FLAG_ACTIVE))
      {
        animation_setup(e1);
      }
      /* otherwise, set number switch flags for number switches */
      else if (e1->type == ENTITY_TYPE_NUMBER_SWITCH_EVEN)
      {
        G_number_switch_flags |= GLOBAL_NUMBER_SWITCH_FLAG_2;
        G_number_switch_flags |= GLOBAL_NUMBER_SWITCH_FLAG_4;
        G_number_switch_flags |= GLOBAL_NUMBER_SWITCH_FLAG_6;
      }
      else if (e1->type == ENTITY_TYPE_NUMBER_SWITCH_ODD)
      {
        G_number_switch_flags |= GLOBAL_NUMBER_SWITCH_FLAG_1;
        G_number_switch_flags |= GLOBAL_NUMBER_SWITCH_FLAG_3;
        G_number_switch_flags |= GLOBAL_NUMBER_SWITCH_FLAG_5;
      }
      else if (e1->type == ENTITY_TYPE_NUMBER_SWITCH_PRIME)
      {
        G_number_switch_flags |= GLOBAL_NUMBER_SWITCH_FLAG_2;
        G_number_switch_flags |= GLOBAL_NUMBER_SWITCH_FLAG_3;
        G_number_switch_flags |= GLOBAL_NUMBER_SWITCH_FLAG_5;
      }
      else if (e1->type == ENTITY_TYPE_NUMBER_SWITCH_COMPOSITE)
      {
        G_number_switch_flags |= GLOBAL_NUMBER_SWITCH_FLAG_4;
        G_number_switch_flags |= GLOBAL_NUMBER_SWITCH_FLAG_6;
      }
      else if (e1->type == ENTITY_TYPE_NUMBER_SWITCH_SQUARE)
      {
        G_number_switch_flags |= GLOBAL_NUMBER_SWITCH_FLAG_1;
        G_number_switch_flags |= GLOBAL_NUMBER_SWITCH_FLAG_4;
      }
      else if (e1->type == ENTITY_TYPE_NUMBER_SWITCH_TRIANGULAR)
      {
        G_number_switch_flags |= GLOBAL_NUMBER_SWITCH_FLAG_1;
        G_number_switch_flags |= GLOBAL_NUMBER_SWITCH_FLAG_3;
        G_number_switch_flags |= GLOBAL_NUMBER_SWITCH_FLAG_6;
      }
    }
  }

  return 0;
}

/*******************************************************************************
** logic_activate_conveyer()
*******************************************************************************/
short int logic_activate_conveyer(entity* e1)
{
  int                 i;
  int                 j;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp[4];
  entity*             e2;

  if (e1 == NULL)
    return 1;

  /* make sure entity is a conveyer */
  if (!(ENTITY_TYPE_IS_CONVEYER(e1->type)))
    return 0;

  /* make sure this entity is not already active */
  if (e1->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
    return 0;

  /* make sure entity is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
    return 0;

  /* determine location of entity in grid */
  low_x = (e1->pos_x / 16) - 2;
  high_x = low_x + 1;

  low_y = (e1->pos_y / 16) - 4;
  high_y = low_y + 1;

  /* make sure entity is within the grid */
  if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((high_x < 0) || (high_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  if ((high_y < 0) || (high_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  /* set spaces to check */
  sp[0] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[1] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[2] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + high_y]);
  sp[3] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + high_y]);

  /* check spaces */
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < sp[i]->num_entities; j++)
    {
      e2 = sp[i]->entities[j];

      if (e1 == e2)
        continue;

      /* if a nonconveyable object is on the conveyer, cancel this trigger */
      if ((!(ENTITY_TYPE_IS_CONVEYABLE(e2->type)))  &&
          (!(ENTITY_TYPE_IS_FLYING(e2->type)))      &&
          (!(ENTITY_TYPE_IS_FLOATING(e2->type)))    &&
          (!(ENTITY_TYPE_IS_SPELL(e2->type))))
      {
        return 0;
      }
    }
  }

  /* activate conveyer if it is clear */
  e1->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;

  /* attempt to convey objects above this conveyer */
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < sp[i]->num_entities; j++)
    {
      e2 = sp[i]->entities[j];

      if (e1 == e2)
        continue;

      /* if a conveyable object is on the conveyer, attempt to convey it */
      if (ENTITY_TYPE_IS_CONVEYABLE(e2->type))
        logic_check_if_over_conveyer(e2);
    }
  }

  return 0;
}

/*******************************************************************************
** logic_deactivate_conveyer()
*******************************************************************************/
short int logic_deactivate_conveyer(entity* e1)
{
  int                 i;
  int                 j;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp[4];
  entity*             e2;

  if (e1 == NULL)
    return 1;

  /* make sure entity is a conveyer */
  if (!(ENTITY_TYPE_IS_CONVEYER(e1->type)))
    return 0;

  /* make sure this entity is not already inactive */
  if (!(e1->update_flags & ENTITY_UPDATE_FLAG_ACTIVE))
    return 0;

  /* make sure entity is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
    return 0;

  /* determine location of entity in grid */
  low_x = (e1->pos_x / 16) - 2;
  high_x = low_x + 1;

  low_y = (e1->pos_y / 16) - 4;
  high_y = low_y + 1;

  /* make sure entity is within the grid */
  if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((high_x < 0) || (high_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  if ((high_y < 0) || (high_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  /* set spaces to check */
  sp[0] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[1] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[2] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + high_y]);
  sp[3] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + high_y]);

  /* deactivate conveyer */
  e1->update_flags &= ~ENTITY_UPDATE_FLAG_ACTIVE;

  /* check spaces */
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < sp[i]->num_entities; j++)
    {
      e2 = sp[i]->entities[j];

      if (e1 == e2)
        continue;

      /* double check if an object over conveyer is still being conveyed */
      if (ENTITY_TYPE_IS_CONVEYABLE(e2->type))
        logic_check_if_over_conveyer(e2);
    }
  }

  return 0;
}

/*******************************************************************************
** logic_check_lit_candle()
*******************************************************************************/
short int logic_check_lit_candle(entity* e1)
{
  int                 i;
  int                 j;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp[4];
  entity*             e2;

  if (e1 == NULL)
    return 1;

  /* make sure entity is a lit candle */
  if (e1->type != ENTITY_TYPE_CANDLE_LIT)
    return 0;

  /* make sure entity is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
    return 0;

  /* determine location of entity in grid */
  low_x = (e1->pos_x / 16) - 2;
  high_x = low_x + 1;

  low_y = (e1->pos_y / 16) - 4;
  high_y = low_y + 1;

  /* make sure entity is within the grid */
  if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((high_x < 0) || (high_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  if ((high_y < 0) || (high_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  /* set spaces to check */
  sp[0] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[1] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[2] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + high_y]);
  sp[3] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + high_y]);

  /* check spaces */
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < sp[i]->num_entities; j++)
    {
      e2 = sp[i]->entities[j];

      if (e1 == e2)
        continue;

      /* if a flying entity is above the candle, destroy it */
      if (ENTITY_TYPE_IS_FLYING(e2->type))
        e2->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
    }
  }

  return 0;
}

/*******************************************************************************
** logic_process_lever_and_switch_flags()
*******************************************************************************/
short int logic_process_lever_and_switch_flags()
{
  int     conveyer_frame_count;
  int     ballista_frame_count;
  entity* e;

  /* nullify conflicting flags */
  if ((G_lever_flags & GLOBAL_LEVER_FLAG_WHITE_OFF) &&
      (G_lever_flags & GLOBAL_LEVER_FLAG_WHITE_ON))
  {
    G_lever_flags &= ~GLOBAL_LEVER_FLAG_WHITE_OFF;
    G_lever_flags &= ~GLOBAL_LEVER_FLAG_WHITE_ON;
  }

  if ((G_lever_flags & GLOBAL_LEVER_FLAG_CYAN_OFF)  &&
      (G_lever_flags & GLOBAL_LEVER_FLAG_CYAN_ON))
  {
    G_lever_flags &= ~GLOBAL_LEVER_FLAG_CYAN_OFF;
    G_lever_flags &= ~GLOBAL_LEVER_FLAG_CYAN_ON;
  }

  if ((G_lever_flags & GLOBAL_LEVER_FLAG_MAGENTA_OFF) &&
      (G_lever_flags & GLOBAL_LEVER_FLAG_MAGENTA_ON))
  {
    G_lever_flags &= ~GLOBAL_LEVER_FLAG_MAGENTA_OFF;
    G_lever_flags &= ~GLOBAL_LEVER_FLAG_MAGENTA_ON;
  }

  if ((G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_RED_CCW) &&
      (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_RED_CW))
  {
    G_spin_switch_flags &= ~GLOBAL_SPIN_SWITCH_FLAG_RED_CCW;
    G_spin_switch_flags &= ~GLOBAL_SPIN_SWITCH_FLAG_RED_CW;
  }

  if ((G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_GREEN_CCW) &&
      (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_GREEN_CW))
  {
    G_spin_switch_flags &= ~GLOBAL_SPIN_SWITCH_FLAG_GREEN_CCW;
    G_spin_switch_flags &= ~GLOBAL_SPIN_SWITCH_FLAG_GREEN_CW;
  }

  if ((G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_BROWN_CCW) &&
      (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_BROWN_CW))
  {
    G_spin_switch_flags &= ~GLOBAL_SPIN_SWITCH_FLAG_BROWN_CCW;
    G_spin_switch_flags &= ~GLOBAL_SPIN_SWITCH_FLAG_BROWN_CW;
  }

  /* levers */
  if (G_lever_flags != GLOBAL_LEVER_FLAGS_CLEAR)
  {
    /* raise / lower floor spikes on lever toggle */
    e = G_entity_active_list_head[CATEGORY_INDEX_FLOOR_SPIKES];

    while (e != NULL)
    {
      if (e->type == ENTITY_TYPE_FLOOR_SPIKE_DOWN_WHITE)
      {
        if (G_lever_flags & GLOBAL_LEVER_FLAG_WHITE_ON)
          e->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
        else if (G_lever_flags & GLOBAL_LEVER_FLAG_WHITE_OFF)
          e->update_flags &= ~ENTITY_UPDATE_FLAG_ACTIVE;
      }
      else if ( (e->type == ENTITY_TYPE_FLOOR_SPIKE_UP_WHITE) &&
                (G_lever_flags & GLOBAL_LEVER_FLAG_WHITE_OFF))
      {
        e->update_flags |= ENTITY_UPDATE_FLAG_TRANSFORMING;
      }
      else if (e->type == ENTITY_TYPE_FLOOR_SPIKE_DOWN_CYAN)
      {
        if (G_lever_flags & GLOBAL_LEVER_FLAG_CYAN_ON)
          e->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
        else if (G_lever_flags & GLOBAL_LEVER_FLAG_CYAN_OFF)
          e->update_flags &= ~ENTITY_UPDATE_FLAG_ACTIVE;
      }
      else if ( (e->type == ENTITY_TYPE_FLOOR_SPIKE_UP_CYAN) &&
                (G_lever_flags & GLOBAL_LEVER_FLAG_CYAN_OFF))
      {
        e->update_flags |= ENTITY_UPDATE_FLAG_TRANSFORMING;
      }
      else if (e->type == ENTITY_TYPE_FLOOR_SPIKE_DOWN_MAGENTA)
      {
        if (G_lever_flags & GLOBAL_LEVER_FLAG_MAGENTA_ON)
          e->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
        else if (G_lever_flags & GLOBAL_LEVER_FLAG_MAGENTA_OFF)
          e->update_flags &= ~ENTITY_UPDATE_FLAG_ACTIVE;
      }
      else if ( (e->type == ENTITY_TYPE_FLOOR_SPIKE_UP_MAGENTA) &&
                (G_lever_flags & GLOBAL_LEVER_FLAG_MAGENTA_OFF))
      {
        e->update_flags |= ENTITY_UPDATE_FLAG_TRANSFORMING;
      }

      e = e->next;
    }

    /* get conveyer frame count */
    conveyer_frame_count = 0;

    e = G_entity_active_list_head[CATEGORY_INDEX_CONVEYERS];

    while (e != NULL)
    {
      if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
      {
        conveyer_frame_count = e->frame_count;
        break;
      }

      e = e->next;
    }

    /* start / stop conveyers on lever toggle */
    e = G_entity_active_list_head[CATEGORY_INDEX_CONVEYERS];

    while (e != NULL)
    {
      if (e->type == ENTITY_TYPE_CONVEYER_WHITE)
      {
        if (G_lever_flags & GLOBAL_LEVER_FLAG_WHITE_ON)
        {
          logic_activate_conveyer(e);
          animation_setup(e);
          e->frame_count = conveyer_frame_count;
        }
        else if (G_lever_flags & GLOBAL_LEVER_FLAG_WHITE_OFF)
        {
          logic_deactivate_conveyer(e);
          animation_setup(e);
        }
      }
      else if (e->type == ENTITY_TYPE_CONVEYER_CYAN)
      {
        if (G_lever_flags & GLOBAL_LEVER_FLAG_CYAN_ON)
        {
          logic_activate_conveyer(e);
          animation_setup(e);
          e->frame_count = conveyer_frame_count;
        }
        else if (G_lever_flags & GLOBAL_LEVER_FLAG_CYAN_OFF)
        {
          logic_deactivate_conveyer(e);
          animation_setup(e);
        }
      }
      else if (e->type == ENTITY_TYPE_CONVEYER_MAGENTA)
      {
        if (G_lever_flags & GLOBAL_LEVER_FLAG_MAGENTA_ON)
        {
          logic_activate_conveyer(e);
          animation_setup(e);
          e->frame_count = conveyer_frame_count;
        }
        else if (G_lever_flags & GLOBAL_LEVER_FLAG_MAGENTA_OFF)
        {
          logic_deactivate_conveyer(e);
          animation_setup(e);
        }
      }

      e = e->next;
    }
  }

  /* spin switches */
  if (G_spin_switch_flags != GLOBAL_SPIN_SWITCH_FLAGS_CLEAR)
  {
    /* rotate arrows */
    for ( e = G_entity_active_list_head[CATEGORY_INDEX_ARROWS];
          e != NULL;
          e = e->next)
    {
      /* if entity is already rotating, continue */
      if (e->action_flags & ENTITY_ACTION_FLAG_ROTATING)
        continue;

      /* counterclockwise spin */
      if (( (e->type == ENTITY_TYPE_ARROWS_RED) && 
            (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_RED_CCW))    ||
          ( (e->type == ENTITY_TYPE_ARROWS_GREEN) && 
            (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_GREEN_CCW))  ||
          ( (e->type == ENTITY_TYPE_ARROWS_BROWN) && 
            (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_BROWN_CCW)))
      {
        if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
          entity_set_facing(e, ENTITY_FACING_UP_RIGHT);
        else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
          entity_set_facing(e, ENTITY_FACING_UP_LEFT);
        else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
          entity_set_facing(e, ENTITY_FACING_DOWN_LEFT);
        else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
          entity_set_facing(e, ENTITY_FACING_DOWN_RIGHT);

        e->action_flags |= ENTITY_ACTION_FLAG_ROTATING;
        e->spin_count = ENTITY_SPIN_TIME_ARROWS;
      }
      /* clockwise spin */
      else if ( ( (e->type == ENTITY_TYPE_ARROWS_RED) && 
                  (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_RED_CW))   ||
                ( (e->type == ENTITY_TYPE_ARROWS_GREEN) && 
                  (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_GREEN_CW)) ||
                ( (e->type == ENTITY_TYPE_ARROWS_BROWN) && 
                  (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_BROWN_CW)))
      {
        if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
          entity_set_facing(e, ENTITY_FACING_DOWN_RIGHT);
        else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
          entity_set_facing(e, ENTITY_FACING_UP_RIGHT);
        else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
          entity_set_facing(e, ENTITY_FACING_UP_LEFT);
        else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
          entity_set_facing(e, ENTITY_FACING_DOWN_LEFT);

        e->action_flags |= ENTITY_ACTION_FLAG_ROTATING;
        e->action_flags |= ENTITY_ACTION_FLAG_MODE;
        e->spin_count = ENTITY_SPIN_TIME_ARROWS;
      }
    }

    /* rotate ballistas */
    for ( e = G_entity_active_list_head[CATEGORY_INDEX_BALLISTAS];
          e != NULL;
          e = e->next)
    {
      /* if entity is already rotating, continue */
      if (e->action_flags & ENTITY_ACTION_FLAG_ROTATING)
        continue;

      /* counterclockwise spin */
      if (( (e->type == ENTITY_TYPE_BALLISTA_RED) && 
            (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_RED_CCW))    ||
          ( (e->type == ENTITY_TYPE_BALLISTA_GREEN) && 
            (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_GREEN_CCW))  ||
          ( (e->type == ENTITY_TYPE_BALLISTA_BROWN) && 
            (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_BROWN_CCW)))
      {
        ballista_frame_count = e->frame_count;

        if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
          entity_set_facing(e, ENTITY_FACING_UP_RIGHT);
        else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
          entity_set_facing(e, ENTITY_FACING_UP_LEFT);
        else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
          entity_set_facing(e, ENTITY_FACING_DOWN_LEFT);
        else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
          entity_set_facing(e, ENTITY_FACING_DOWN_RIGHT);

        animation_setup(e);
        e->frame_count = ballista_frame_count;

        e->action_flags |= ENTITY_ACTION_FLAG_ROTATING;
        e->spin_count = ENTITY_SPIN_TIME_BALLISTA;
      }
      /* clockwise spin */
      else if ( ( (e->type == ENTITY_TYPE_BALLISTA_RED) && 
                  (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_RED_CW))   ||
                ( (e->type == ENTITY_TYPE_BALLISTA_GREEN) && 
                  (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_GREEN_CW)) ||
                ( (e->type == ENTITY_TYPE_BALLISTA_BROWN) && 
                  (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_BROWN_CW)))
      {
        ballista_frame_count = e->frame_count;

        if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
          entity_set_facing(e, ENTITY_FACING_DOWN_RIGHT);
        else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
          entity_set_facing(e, ENTITY_FACING_UP_RIGHT);
        else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
          entity_set_facing(e, ENTITY_FACING_UP_LEFT);
        else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
          entity_set_facing(e, ENTITY_FACING_DOWN_LEFT);

        animation_setup(e);
        e->frame_count = ballista_frame_count;

        e->action_flags |= ENTITY_ACTION_FLAG_ROTATING;
        e->action_flags |= ENTITY_ACTION_FLAG_MODE;
        e->spin_count = ENTITY_SPIN_TIME_BALLISTA;
      }
    }

    /* rotate pinball kickers */
    for ( e = G_entity_active_list_head[CATEGORY_INDEX_PINBALL_KICKERS];
          e != NULL;
          e = e->next)
    {
      /* if entity is already rotating, continue */
      if (e->action_flags & ENTITY_ACTION_FLAG_ROTATING)
        continue;

      /* counterclockwise spin */
      if (( (e->type == ENTITY_TYPE_BAR_KICKER_RED) && 
            (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_RED_CCW))    ||
          ( (e->type == ENTITY_TYPE_TRIANGLE_KICKER_RED) && 
            (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_RED_CCW))    ||
          ( (e->type == ENTITY_TYPE_BAR_KICKER_GREEN) && 
            (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_GREEN_CCW))  ||
          ( (e->type == ENTITY_TYPE_TRIANGLE_KICKER_GREEN) && 
            (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_GREEN_CCW))  ||
          ( (e->type == ENTITY_TYPE_BAR_KICKER_BROWN) && 
            (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_BROWN_CCW))  ||
          ( (e->type == ENTITY_TYPE_TRIANGLE_KICKER_BROWN) && 
            (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_BROWN_CCW)))
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

        e->action_flags |= ENTITY_ACTION_FLAG_ROTATING;
        e->spin_count = ENTITY_SPIN_TIME_PINBALL_KICKER;
      }
      /* clockwise spin */
      else if ( ( (e->type == ENTITY_TYPE_BAR_KICKER_RED) && 
                  (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_RED_CW))   ||
                ( (e->type == ENTITY_TYPE_TRIANGLE_KICKER_RED) && 
                  (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_RED_CW))   ||
                ( (e->type == ENTITY_TYPE_BAR_KICKER_GREEN) && 
                  (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_GREEN_CW)) ||
                ( (e->type == ENTITY_TYPE_TRIANGLE_KICKER_GREEN) && 
                  (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_GREEN_CW)) ||
                ( (e->type == ENTITY_TYPE_BAR_KICKER_BROWN) && 
                  (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_BROWN_CW)) ||
                ( (e->type == ENTITY_TYPE_TRIANGLE_KICKER_BROWN) && 
                  (G_spin_switch_flags & GLOBAL_SPIN_SWITCH_FLAG_BROWN_CW)))
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

        e->action_flags |= ENTITY_ACTION_FLAG_ROTATING;
        e->action_flags |= ENTITY_ACTION_FLAG_MODE;
        e->spin_count = ENTITY_SPIN_TIME_PINBALL_KICKER;
      }
    }
  }

  /* number switches */
  /* attempt transform of solid dice to vanished */
  e = G_entity_active_list_head[CATEGORY_INDEX_PUSHABLE_OBJECTS];

  while (e != NULL)
  {
    if (e->type == ENTITY_TYPE_DIE_SOLID_1)
    {
      if (!(G_number_switch_flags & GLOBAL_NUMBER_SWITCH_FLAG_1))
        e->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
      else
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
    }
    else if (e->type == ENTITY_TYPE_DIE_SOLID_2)
    {
      if (!(G_number_switch_flags & GLOBAL_NUMBER_SWITCH_FLAG_2))
        e->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
      else
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
    }
    else if (e->type == ENTITY_TYPE_DIE_SOLID_3)
    {
      if (!(G_number_switch_flags & GLOBAL_NUMBER_SWITCH_FLAG_3))
        e->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
      else
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
    }
    else if (e->type == ENTITY_TYPE_DIE_SOLID_4)
    {
      if (!(G_number_switch_flags & GLOBAL_NUMBER_SWITCH_FLAG_4))
        e->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
      else
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
    }
    else if (e->type == ENTITY_TYPE_DIE_SOLID_5)
    {
      if (!(G_number_switch_flags & GLOBAL_NUMBER_SWITCH_FLAG_5))
        e->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
      else
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
    }
    else if (e->type == ENTITY_TYPE_DIE_SOLID_6)
    {
      if (!(G_number_switch_flags & GLOBAL_NUMBER_SWITCH_FLAG_6))
        e->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
      else
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
    }

    e = e->next;
  }

  /* attempt transform of vanished dice to solid */
  e = G_entity_active_list_head[CATEGORY_INDEX_VANISHED_DICE];

  while (e != NULL)
  {
    if (e->type == ENTITY_TYPE_DIE_VANISHED_1)
    {
      if (G_number_switch_flags & GLOBAL_NUMBER_SWITCH_FLAG_1)
        e->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
      else
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
    }
    else if (e->type == ENTITY_TYPE_DIE_VANISHED_2)
    {
      if (G_number_switch_flags & GLOBAL_NUMBER_SWITCH_FLAG_2)
        e->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
      else
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
    }
    else if (e->type == ENTITY_TYPE_DIE_VANISHED_3)
    {
      if (G_number_switch_flags & GLOBAL_NUMBER_SWITCH_FLAG_3)
        e->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
      else
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
    }
    else if (e->type == ENTITY_TYPE_DIE_VANISHED_4)
    {
      if (G_number_switch_flags & GLOBAL_NUMBER_SWITCH_FLAG_4)
        e->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
      else
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
    }
    else if (e->type == ENTITY_TYPE_DIE_VANISHED_5)
    {
      if (G_number_switch_flags & GLOBAL_NUMBER_SWITCH_FLAG_5)
        e->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
      else
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
    }
    else if (e->type == ENTITY_TYPE_DIE_VANISHED_6)
    {
      if (G_number_switch_flags & GLOBAL_NUMBER_SWITCH_FLAG_6)
        e->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
      else
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
    }

    e = e->next;
  }

  /* toggle submerged dice */
  e = G_entity_active_list_head[CATEGORY_INDEX_BRIDGES_SUBMERGED];

  while (e != NULL)
  {
    if (e->type == ENTITY_TYPE_DIE_SOLID_1_SUBMERGED)
    {
      if (!(G_number_switch_flags & GLOBAL_NUMBER_SWITCH_FLAG_1))
        e->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
      else
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
    }
    else if (e->type == ENTITY_TYPE_DIE_SOLID_2_SUBMERGED)
    {
      if (!(G_number_switch_flags & GLOBAL_NUMBER_SWITCH_FLAG_2))
        e->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
      else
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
    }
    else if (e->type == ENTITY_TYPE_DIE_SOLID_3_SUBMERGED)
    {
      if (!(G_number_switch_flags & GLOBAL_NUMBER_SWITCH_FLAG_3))
        e->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
      else
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
    }
    else if (e->type == ENTITY_TYPE_DIE_SOLID_4_SUBMERGED)
    {
      if (!(G_number_switch_flags & GLOBAL_NUMBER_SWITCH_FLAG_4))
        e->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
      else
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
    }
    else if (e->type == ENTITY_TYPE_DIE_SOLID_5_SUBMERGED)
    {
      if (!(G_number_switch_flags & GLOBAL_NUMBER_SWITCH_FLAG_5))
        e->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
      else
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
    }
    else if (e->type == ENTITY_TYPE_DIE_SOLID_6_SUBMERGED)
    {
      if (!(G_number_switch_flags & GLOBAL_NUMBER_SWITCH_FLAG_6))
        e->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
      else
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
    }
    else if (e->type == ENTITY_TYPE_DIE_VANISHED_1_SUBMERGED)
    {
      if (G_number_switch_flags & GLOBAL_NUMBER_SWITCH_FLAG_1)
        e->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
      else
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
    }
    else if (e->type == ENTITY_TYPE_DIE_VANISHED_2_SUBMERGED)
    {
      if (G_number_switch_flags & GLOBAL_NUMBER_SWITCH_FLAG_2)
        e->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
      else
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
    }
    else if (e->type == ENTITY_TYPE_DIE_VANISHED_3_SUBMERGED)
    {
      if (G_number_switch_flags & GLOBAL_NUMBER_SWITCH_FLAG_3)
        e->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
      else
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
    }
    else if (e->type == ENTITY_TYPE_DIE_VANISHED_4_SUBMERGED)
    {
      if (G_number_switch_flags & GLOBAL_NUMBER_SWITCH_FLAG_4)
        e->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
      else
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
    }
    else if (e->type == ENTITY_TYPE_DIE_VANISHED_5_SUBMERGED)
    {
      if (G_number_switch_flags & GLOBAL_NUMBER_SWITCH_FLAG_5)
        e->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
      else
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
    }
    else if (e->type == ENTITY_TYPE_DIE_VANISHED_6_SUBMERGED)
    {
      if (G_number_switch_flags & GLOBAL_NUMBER_SWITCH_FLAG_6)
        e->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
      else
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
    }

    e = e->next;
  }

  /* clear flags, now that they have been processed */
  G_lever_flags = GLOBAL_LEVER_FLAGS_CLEAR;
  G_spin_switch_flags = GLOBAL_SPIN_SWITCH_FLAGS_CLEAR;
  G_number_switch_flags = GLOBAL_NUMBER_SWITCH_FLAGS_CLEAR;

  return 0;
}

/*******************************************************************************
** logic_check_if_stood_upon()
*******************************************************************************/
short int logic_check_if_stood_upon(entity* e1)
{
  int                 i;
  int                 j;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp[4];
  entity*             e2;

  if (e1 == NULL)
    return 1;

  /* make sure entity is a bridge or submerged pushable object */
  if ((!(ENTITY_TYPE_IS_BRIDGE(e1->type))) && 
      (!(ENTITY_TYPE_IS_SUBMERGED(e1->type))))
  {
    return 0;
  }

  /* make sure entity is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
    return 0;

  /* determine location of entity in grid */
  low_x = (e1->pos_x / 16) - 2;
  high_x = low_x + 1;

  low_y = (e1->pos_y / 16) - 4;
  high_y = low_y + 1;

  /* make sure entity is within the grid */
  if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((high_x < 0) || (high_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  if ((high_y < 0) || (high_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  /* set spaces to check */
  sp[0] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[1] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[2] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + high_y]);
  sp[3] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + high_y]);

  /* check spaces */
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < sp[i]->num_entities; j++)
    {
      e2 = sp[i]->entities[j];

      if (e1 == e2)
        continue;

      /* if an object is on the bridge, cancel this trigger */
      if (!(ENTITY_TYPE_IS_FLYING(e2->type)     ||
            ENTITY_TYPE_IS_SPELL(e2->type)      ||
            (e2->type == ENTITY_TYPE_EXPLOSION) ||
            ENTITY_TYPE_IS_VANISHED_DIE_SUBMERGED(e2->type)))
      {
        return 0;
      }
    }
  }

  /* destroy / vanish bridge or submerged object if it is clear */
  if (e1->special_flags & ENTITY_SPECIAL_FLAG_AWAITING_DESTROY)
  {
    e1->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_DESTROY;
    e1->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
  }
  else if (e1->special_flags & ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM)
  {
    e1->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
    e1->update_flags |= ENTITY_UPDATE_FLAG_TRANSFORMING;
  }

  return 0;
}

/*******************************************************************************
** logic_solidify_vanished_die()
*******************************************************************************/
short int logic_solidify_vanished_die(entity* e1)
{
  int                 i;
  int                 j;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp[4];
  entity*             e2;

  if (e1 == NULL)
    return 1;

  /* make sure entity is a vanished die */
  if (!(ENTITY_TYPE_IS_VANISHED_DIE(e1->type)))
  {
    return 0;
  }

  /* make sure entity is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
    return 0;

  /* determine location of entity in grid */
  low_x = (e1->pos_x / 16) - 2;
  high_x = low_x + 1;

  low_y = (e1->pos_y / 16) - 4;
  high_y = low_y + 1;

  /* make sure entity is within the grid */
  if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((high_x < 0) || (high_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  if ((high_y < 0) || (high_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  /* set spaces to check */
  sp[0] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[1] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[2] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + high_y]);
  sp[3] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + high_y]);

  /* check spaces */
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < sp[i]->num_entities; j++)
    {
      e2 = sp[i]->entities[j];

      if (e1 == e2)
        continue;

      /* if a movement blocking object is within the die, return */
      if ((e2->move_affect & ENTITY_MOVE_FLAG_PUSHABLE_HIGH) &&
          (!(ENTITY_TYPE_IS_ARROWS(e2->type))))
      {
        return 0;
      }
      /* if another die overlaps this one, and  */
      /* is also trying to solidify, return     */
      else if ( (ENTITY_TYPE_IS_VANISHED_DIE(e2->type)) &&
                (e2->special_flags & ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM))
      {
        return 0;
      }
    }
  }

  /* solidify die if it is clear */
  if (e1->special_flags & ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM)
  {
    e1->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;

    /* check if die is solidifying into an explosion */
    for (i = 0; i < 4; i++)
    {
      for (j = 0; j < sp[i]->num_entities; j++)
      {
        e2 = sp[i]->entities[j];

        if (e1 == e2)
          continue;

        if (e2->type == ENTITY_TYPE_EXPLOSION)
        {
          e1->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
          return 0;
        }
      }
    }

    e1->update_flags |= ENTITY_UPDATE_FLAG_TRANSFORMING;
  }

  return 0;
}

/*******************************************************************************
** logic_solidify_submerged_vanished_die()
*******************************************************************************/
short int logic_solidify_submerged_vanished_die(entity* e1)
{
  int                 i;
  int                 j;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp[4];
  entity*             e2;

  if (e1 == NULL)
    return 1;

  /* make sure entity is a submerged vanished die */
  if (!(ENTITY_TYPE_IS_VANISHED_DIE_SUBMERGED(e1->type)))
  {
    return 0;
  }

  /* make sure entity is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
    return 0;

  /* determine location of entity in grid */
  low_x = (e1->pos_x / 16) - 2;
  high_x = low_x + 1;

  low_y = (e1->pos_y / 16) - 4;
  high_y = low_y + 1;

  /* make sure entity is within the grid */
  if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((high_x < 0) || (high_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  if ((high_y < 0) || (high_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  /* set spaces to check */
  sp[0] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[1] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[2] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + high_y]);
  sp[3] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + high_y]);

  /* check spaces */
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < sp[i]->num_entities; j++)
    {
      e2 = sp[i]->entities[j];

      if (e1 == e2)
        continue;

      /* if this submerged die overlaps another submerged */
      /* die that is also trying to soldify, return       */
      if (ENTITY_TYPE_IS_VANISHED_DIE_SUBMERGED(e2->type))
      {
        if (e2->special_flags & ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM)
          return 0;
      }
      /* if this submerged die overlaps a solid object, return */
      else if (!( (e2->type == ENTITY_TYPE_WATER)     ||
                  (e2->type == ENTITY_TYPE_EXPLOSION) ||
                  ENTITY_TYPE_IS_FLYING(e2->type)     ||
                  ENTITY_TYPE_IS_SPELL(e2->type)))
        return 0;
    }
  }

  /* if path is clear, try to solidify */
  if (e1->special_flags & ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM)
  {
    e1->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;

    /* check if die is solidifying into an explosion */
    for (i = 0; i < 4; i++)
    {
      for (j = 0; j < sp[i]->num_entities; j++)
      {
        e2 = sp[i]->entities[j];

        if (e1 == e2)
          continue;

        if (e2->type == ENTITY_TYPE_EXPLOSION)
        {
          e1->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
          return 0;
        }
      }
    }

    /* if die was not destroyed, clear water tiles */
    for (i = 0; i < 4; i++)
    {
      for (j = 0; j < sp[i]->num_entities; j++)
      {
        e2 = sp[i]->entities[j];

        if (e1 == e2)
          continue;

        /* if a water tile is found, set it to destroyed */
        if (e2->type == ENTITY_TYPE_WATER)
          e2->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
      }
    }

    e1->update_flags |= ENTITY_UPDATE_FLAG_TRANSFORMING;
  }

  return 0;
}

/*******************************************************************************
** logic_process_awaiting()
*******************************************************************************/
short int logic_process_awaiting()
{
  entity* e;

  /* cycle through bridges and submerged pushable objects */
  e = G_entity_active_list_head[CATEGORY_INDEX_BRIDGES_SUBMERGED];

  while (e != NULL)
  {
    /* for a vanished submerged die, we need to */
    /* destroy the water tiles it covers        */
    if ((ENTITY_TYPE_IS_VANISHED_DIE_SUBMERGED(e->type))  &&
        (e->special_flags & ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM))
    {
      logic_solidify_submerged_vanished_die(e);
    }
    /* otherwise, make sure that nothing is standing on this object */
    else
    {
      if ((e->special_flags & ENTITY_SPECIAL_FLAG_AWAITING_DESTROY) ||
          (e->special_flags & ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM))
      {
        logic_check_if_stood_upon(e);
      }
    }

    e = e->next;
  }

  /* cycle through solid dice trying to vanish */
  e = G_entity_active_list_head[CATEGORY_INDEX_PUSHABLE_OBJECTS];

  while (e != NULL)
  {
    if ((ENTITY_TYPE_IS_SOLID_DIE(e->type)) &&
        (e->special_flags & ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM))
    {
      if (!((e->action_flags & ENTITY_ACTION_FLAG_MOVING) ||
            (e->update_flags & ENTITY_UPDATE_FLAG_MOVING_INTO_WATER)))
      {
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM;
        e->update_flags |= ENTITY_UPDATE_FLAG_TRANSFORMING;
      }
    }

    e = e->next;
  }

  /* cycle through vanished dice trying to solidify */
  e = G_entity_active_list_head[CATEGORY_INDEX_VANISHED_DICE];

  while (e != NULL)
  {
    if (e->special_flags & ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM)
    {
      logic_solidify_vanished_die(e);
    }

    e = e->next;
  }

  return 0;
}

/*******************************************************************************
** logic_check_if_over_yin_yang()
*******************************************************************************/
short int logic_check_if_over_yin_yang(entity* e1)
{
  int                 i;
  int                 low_x;
  int                 low_y;
  collide_grid_space* sp;
  entity*             e2;

  if (e1 == NULL)
    return 1;

  /* make sure entity is a fire spell or ice spell */
  if (!((e1->type != ENTITY_TYPE_FIRE_SPELL) ||
        (e1->type != ENTITY_TYPE_ICE_SPELL)))
    return 0;

  /* make sure entity is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
    return 0;

  /* determine location of entity in grid */
  low_x = (e1->pos_x / 16) - 2;
  low_y = (e1->pos_y / 16) - 4;

  /* make sure entity is within the grid */
  if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  /* set space to check */
  sp = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);

  /* check space */
  for (i = 0; i < sp->num_entities; i++)
  {
    e2 = sp->entities[i];

    if (e1 == e2)
      continue;

    if ((e1->pos_x != e2->pos_x) || (e1->pos_y != e2->pos_y))
      continue;

    if (e2->type == ENTITY_TYPE_YIN_YANG)
    {
      /* check if spell is already transforming (this can occur when      */
      /* there is a yin yang on two sides of a banked reflecter, and the  */
      /* reflecter triggered the reflection during the spell's movement)  */
      if (e1->update_flags & ENTITY_UPDATE_FLAG_TRANSFORMING)
      {
        e1->update_flags &= ~ENTITY_UPDATE_FLAG_TRANSFORMING;

        if (!(e2->animation_flags & ENTITY_ANIMATION_FLAG_ON))
          e2->animation_flags |= ENTITY_ANIMATION_FLAG_RESTART;
      }
      else
      {
        e1->update_flags |= ENTITY_UPDATE_FLAG_TRANSFORMING;

        if (!(e2->animation_flags & ENTITY_ANIMATION_FLAG_ON))
          e2->animation_flags |= ENTITY_ANIMATION_FLAG_RESTART;
      }

      return 0;
    }
  }

  return 0;
}

/*******************************************************************************
** logic_check_if_over_portcullis()
*******************************************************************************/
short int logic_check_if_over_portcullis(entity* e1)
{
  int                 i;
  int                 j;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp[4];
  entity*             e2;

  if (e1 == NULL)
    return 1;

  /* make sure entity is the player */
  if (!((e1->type != ENTITY_TYPE_PLAYER_VAMPIRE) ||
        (e1->type != ENTITY_TYPE_PLAYER_BAT)))
    return 0;

  /* make sure entity is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
    return 0;

  /* determine location of entity in grid */
  low_x = (e1->pos_x / 16) - 2;
  high_x = low_x + 1;

  low_y = (e1->pos_y / 16) - 4;
  high_y = low_y + 1;

  /* make sure entity is within the grid */
  if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((high_x < 0) || (high_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  if ((high_y < 0) || (high_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  /* set spaces to check */
  sp[0] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[1] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[2] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + high_y]);
  sp[3] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + high_y]);

  /* check spaces */
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < sp[i]->num_entities; j++)
    {
      e2 = sp[i]->entities[j];

      if (e1 == e2)
        continue;

      if (e2->type == ENTITY_TYPE_PORTCULLIS_OPEN)
      {
        G_game_state_flags |= GLOBAL_GAME_STATE_FLAG_LEVEL_COMPLETE;

        return 0;
      }
    }
  }

  return 0;
}

/*******************************************************************************
** logic_process_solomons_seals()
*******************************************************************************/
short int logic_process_solomons_seals()
{
  int                 i;
  int                 low_x;
  int                 low_y;
  collide_grid_space* sp;
  entity*             e1;
  entity*             e2;

  /* cycle through symbols */
  for ( e1 = G_entity_active_list_head[CATEGORY_INDEX_SYMBOLS];
        e1 != NULL;
        e1 = e1->next)
  {
    /* make sure symbol is "snapped onto the grid"        */
    /* (i.e., its center is at a grid space intersection) */
    if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
      continue;

    /* determine location of symbol in grid */
    low_x = (e1->pos_x / 16) - 2;
    low_y = (e1->pos_y / 16) - 4;

    /* make sure symbol is within the grid */
    if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
      return 0;

    if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
      return 0;

    /* set space to check as upper left corner */
    sp = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);

    /* solomon's seal */
    if (e1->type == ENTITY_TYPE_SEAL_OF_SOLOMON)
    {
      /* clear mode flag */
      e1->action_flags &= ~ENTITY_ACTION_FLAG_MODE;

      for (i = 0; i < sp->num_entities; i++)
      {
        e2 = sp->entities[i];

        if (e1 == e2)
          continue;

        if ((e1->pos_x - e2->pos_x >= 16) || (e1->pos_x - e2->pos_x <= -16) ||
            (e1->pos_y - e2->pos_y >= 16) || (e1->pos_y - e2->pos_y <= -16))
          continue;

        /* protect player and enemies from damage */
        if (ENTITY_TYPE_IS_PLAYER(e2->type)   ||
            ENTITY_TYPE_IS_ENEMY(e2->type))
        {
          e2->collision_flags &= ~ENTITY_COLLISION_FLAG_LOST_1_HP;
          e2->collision_flags &= ~ENTITY_COLLISION_FLAG_LOST_2_HP;
          e2->collision_flags &= ~ENTITY_COLLISION_FLAG_DESTROYED;
          e2->collision_flags &= ~ENTITY_COLLISION_FLAG_FIRE;
          e2->collision_flags &= ~ENTITY_COLLISION_FLAG_ICE;
          e2->collision_flags &= ~ENTITY_COLLISION_FLAG_NEUTRAL;
          e2->collision_flags &= ~ENTITY_COLLISION_FLAG_BOLT;

          e1->action_flags |= ENTITY_ACTION_FLAG_MODE;
        }
      }

      /* light / unlight seal based on mode and active flags */
      if ((e1->action_flags & ENTITY_ACTION_FLAG_MODE) &&
          (!(e1->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)))
      {
        e1->tile = 7;
        doremi_play_sfx(SFX_INDEX_SOLOMONS_SEAL_ACTIVATE);
        e1->action_flags &= ~ENTITY_ACTION_FLAG_MODE;
        e1->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
      }
      else if ( (!(e1->action_flags & ENTITY_ACTION_FLAG_MODE)) &&
                (e1->update_flags & ENTITY_UPDATE_FLAG_ACTIVE))
      {
        e1->tile = 6;
        e1->update_flags &= ~ENTITY_UPDATE_FLAG_ACTIVE;
      }
    }
  }

  return 0;
}

/*******************************************************************************
** logic_check_post_warp_location()
*******************************************************************************/
short int logic_check_post_warp_location(entity* e1)
{
  int                 i;
  int                 j;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp[4];
  entity*             e2;

  if (e1 == NULL)
    return 1;

  /* make sure entity is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
    return 0;

  /* determine location of entity in grid */
  low_x = (e1->pos_x / 16) - 2;
  high_x = low_x + 1;

  low_y = (e1->pos_y / 16) - 4;
  high_y = low_y + 1;

  /* make sure entity is within the grid */
  if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((high_x < 0) || (high_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  if ((high_y < 0) || (high_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  /* set spaces to check */
  sp[0] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[1] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[2] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + high_y]);
  sp[3] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + high_y]);

  /* check for problematic entities in each space */
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < sp[i]->num_entities; j++)
    {
      e2 = sp[i]->entities[j];

      if (e1 == e2)
        continue;

      /* warped onto blocking object */
      if (e1->move_attribute & e2->move_affect)
      {
        /* special case: spike destroying object warped */
        /*               onto floor spikes              */
        if ((ENTITY_TYPE_IS_SPIKE_DESTROYING(e1->type)) &&
            (ENTITY_TYPE_IS_FLOOR_SPIKE_UP(e2->type)))
        {
          if (ENTITY_TYPE_IS_FLASK(e1->type))
          {
            if ((!(e1->collision_flags & ENTITY_COLLISION_FLAG_LOST_1_HP))  &&
                (!(e1->collision_flags & ENTITY_COLLISION_FLAG_LOST_2_HP)))
            {
              e1->collision_flags |= ENTITY_COLLISION_FLAG_LOST_1_HP;
            }
            else if ( (e1->collision_flags & ENTITY_COLLISION_FLAG_LOST_1_HP) &&
                      (!(e1->collision_flags & ENTITY_COLLISION_FLAG_LOST_2_HP)))
            {
              e1->collision_flags &= ~ENTITY_COLLISION_FLAG_LOST_1_HP;
              e1->collision_flags |= ENTITY_COLLISION_FLAG_LOST_2_HP;
            }
            else if ( (!(e1->collision_flags & ENTITY_COLLISION_FLAG_LOST_1_HP)) &&
                      (e1->collision_flags & ENTITY_COLLISION_FLAG_LOST_2_HP))
            {
              e1->collision_flags |= ENTITY_COLLISION_FLAG_LOST_1_HP;
            }
            else if ( (e1->collision_flags & ENTITY_COLLISION_FLAG_LOST_1_HP) &&
                      (e1->collision_flags & ENTITY_COLLISION_FLAG_LOST_2_HP))
            {
              e1->collision_flags &= ~ENTITY_COLLISION_FLAG_LOST_1_HP;
              e1->collision_flags &= ~ENTITY_COLLISION_FLAG_LOST_2_HP;
              e1->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
            }
          }

          e2->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
          continue;
        }

        /* if warped onto arrow, continue */
        if (ENTITY_TYPE_IS_ARROWS(e2->type))
          continue;

        /* if warped onto grass, continue */
        if (e2->type == ENTITY_TYPE_GRASS)
          continue;

        /* if warped onto warp spell, continue */
        if (e2->type == ENTITY_TYPE_WARP_SPELL)
          continue;

        /* otherwise, entity is destroyed */
        e1->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
        return 0;
      }

      /* warped onto water or raised floor spikes */
      if (ENTITY_TYPE_IS_FLOOR_SPIKE_UP(e2->type) ||
          (e2->type == ENTITY_TYPE_WATER))
      {
        if (ENTITY_TYPE_IS_FLYING(e1->type) ||
            ENTITY_TYPE_IS_SPELL(e1->type))
        {
          continue;
        }
        else
        {
          e1->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
          return 0;
        }
      }

      /* warped over pot, flask, candle, lever */
      if ((e2->type == ENTITY_TYPE_POT_CLAY)      ||
          (e2->type == ENTITY_TYPE_POT_METAL)     ||
          (e2->type == ENTITY_TYPE_POT_TNT)       ||
          (e2->type == ENTITY_TYPE_POT_STONE)     ||
          (e2->type == ENTITY_TYPE_AQUA_FORTIS)   ||
          (e2->type == ENTITY_TYPE_AQUA_EXPLODIS) ||
          (e2->type == ENTITY_TYPE_CANDLE_UNLIT)  ||
          (e2->type == ENTITY_TYPE_CANDLE_LIT)    ||
          ENTITY_TYPE_IS_LEVER(e2->type))
      {
        if (ENTITY_TYPE_IS_FLYING(e1->type))
        {
          if (e2->type == ENTITY_TYPE_CANDLE_LIT)
          {
            e1->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
            return 0;
          }
          else
          {
            continue;
          }
        }
        else
        {
          e1->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
          return 0;
        }
      }

      /* warped onto cobweb or pickup */
      if (ENTITY_TYPE_IS_PICKUP(e2->type))
      {
        if (e1->type == ENTITY_TYPE_PLAYER_VAMPIRE)
        {
          continue;
        }
        else
        {
          e1->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
          return 0;
        }
      }
    }
  }

  /* if entity was destroyed, return */
  if (e1->collision_flags & ENTITY_COLLISION_FLAG_DESTROYED)
    return 0;

  /* check if immovable object warped onto active conveyer */
  if (!(ENTITY_TYPE_IS_CONVEYABLE(e1->type)   ||
        ENTITY_TYPE_IS_FLYING(e1->type))      ||
        ENTITY_TYPE_IS_FLOATING(e1->type)     ||
        ENTITY_TYPE_IS_SPELL(e1->type))
  {
    for (i = 0; i < 4; i++)
    {
      for (j = 0; j < sp[i]->num_entities; j++)
      {
        e2 = sp[i]->entities[j];

        if (e1 == e2)
          continue;

        if ((ENTITY_TYPE_IS_CONVEYER(e2->type)) &&
            (e2->update_flags & ENTITY_UPDATE_FLAG_ACTIVE))
        {
          logic_deactivate_conveyer(e2);
          animation_setup(e2);
        }
      }
    }
  }

  return 0;
}

/*******************************************************************************
** logic_check_post_freeze_location()
*******************************************************************************/
short int logic_check_post_freeze_location(entity* e1)
{
  int                 i;
  int                 j;
  int                 low_x;
  int                 high_x;
  int                 low_y;
  int                 high_y;
  collide_grid_space* sp[4];
  entity*             e2;

  if (e1 == NULL)
    return 1;

  /* make sure entity is an ice cube */
  if (!(ENTITY_TYPE_IS_ICE_CUBE(e1->type)))
    return 0;

  /* make sure entity is "snapped onto the grid"        */
  /* (i.e., its center is at a grid space intersection) */
  if ((e1->pos_x % 16 != 0) || (e1->pos_y % 16 != 0))
    return 0;

  /* determine location of entity in grid */
  low_x = (e1->pos_x / 16) - 2;
  high_x = low_x + 1;

  low_y = (e1->pos_y / 16) - 4;
  high_y = low_y + 1;

  /* make sure entity is within the grid */
  if ((low_x < 0) || (low_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((high_x < 0) || (high_x > COLLIDE_GRID_WIDTH - 1))
    return 0;

  if ((low_y < 0) || (low_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  if ((high_y < 0) || (high_y > COLLIDE_GRID_HEIGHT - 1))
    return 0;

  /* set spaces to check */
  sp[0] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[1] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + low_y]);
  sp[2] = &(G_collide_grid[low_x * COLLIDE_GRID_HEIGHT + high_y]);
  sp[3] = &(G_collide_grid[high_x * COLLIDE_GRID_HEIGHT + high_y]);

  /* check for stationary blocking objects in each space */
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < sp[i]->num_entities; j++)
    {
      e2 = sp[i]->entities[j];

      if (e1 == e2)
        continue;

      /* frozen over stationary blocking object */
      if ((e1->move_attribute & e2->move_affect) &&
          (!(e2->action_flags & ENTITY_ACTION_FLAG_MOVING)))
      {
        e1->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
        return 0;
      }
    }
  }

  /* check for moving blocking objects in each space */
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < sp[i]->num_entities; j++)
    {
      e2 = sp[i]->entities[j];

      if (e1 == e2)
        continue;

      /* frozen over moving blocking object */
      if ((e1->move_attribute & e2->move_affect) &&
          (e2->action_flags & ENTITY_ACTION_FLAG_MOVING))
      {
        /* check if object is moving out of the way */
        if (ENTITY_DIRECTION_CHECK(e2, ENTITY_DIRECTION_RIGHT) &&
            (e2->pos_x - e1->pos_x >= 16))
        {
          continue;
        }
        else if ( ENTITY_DIRECTION_CHECK(e2, ENTITY_DIRECTION_UP) &&
                  (e1->pos_y - e2->pos_y >= 16))
        {
          continue;
        }
        else if ( ENTITY_DIRECTION_CHECK(e2, ENTITY_DIRECTION_LEFT) &&
                  (e1->pos_x - e2->pos_x >= 16))
        {
          continue;
        }
        else if   (ENTITY_DIRECTION_CHECK(e2, ENTITY_DIRECTION_DOWN) &&
                  (e2->pos_y - e1->pos_y >= 16))
        {
          continue;
        }
        else
        {
          e1->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
          return 0;
        }
      }
    }
  }

  return 0;
}

/*******************************************************************************
** logic_player_death()
*******************************************************************************/
short int logic_player_death()
{
  entity* e;

  /* set game state flag */
  G_game_state_flags |= GLOBAL_GAME_STATE_FLAG_DEAD;

  /* play sfx */
  doremi_play_sfx(SFX_INDEX_PLAYER_DEATH);

  /* unlight pumpkins, make masks smile */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_PUMPKINS_GHOSTS_MASKS];
        e != NULL;
        e = e->next)
  {
    if ((e->type == ENTITY_TYPE_PUMPKIN) && 
        (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE))
    {
      e->update_flags &= ~ENTITY_UPDATE_FLAG_ACTIVE;
      animation_setup(e);
    }
    else if ( (e->type == ENTITY_TYPE_MASK_HORIZONTAL) && 
              (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE))
    {
      e->update_flags &= ~ENTITY_UPDATE_FLAG_ACTIVE;
      animation_setup(e);
    }
    else if ( (e->type == ENTITY_TYPE_MASK_VERTICAL) && 
              (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE))
    {
      e->update_flags &= ~ENTITY_UPDATE_FLAG_ACTIVE;
      animation_setup(e);
    }
  }

  /* deactivate frogs */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_LIL_BOTS_WISPS_FROGS];
        e != NULL;
        e = e->next)
  {
    if ((e->type == ENTITY_TYPE_FROG) && 
        (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE))
    {
      e->update_flags &= ~ENTITY_UPDATE_FLAG_ACTIVE;
      entity_set_facing(e, e->orientation & ENTITY_FACING_MASK);
    }
  }

  return 0;
}

/*******************************************************************************
** logic_process_spell_casting()
*******************************************************************************/
short int logic_process_spell_casting()
{
  int     i;
  entity* e;
  entity* new_e;
  int     new_entity_type;

  /* evil eye casting */
  e = G_entity_active_list_head[CATEGORY_INDEX_PUMPKINS_GHOSTS_MASKS];

  while (e != NULL)
  {
    if (e->action_flags & ENTITY_ACTION_FLAG_CASTING)
    {
      if (!(G_game_state_flags & GLOBAL_GAME_STATE_FLAG_EVIL_EYE_CAST))
      {
        new_entity_type = ENTITY_TYPE_EVIL_EYE;

        /* create evil eye spell */
        if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
        {
          new_e = world_spawn_entity( new_entity_type, 
                                      e->pos_x + 32, e->pos_y);
          entity_set_facing(new_e, ENTITY_FACING_RIGHT);
          new_e->vel_x = 4;
          new_e->vel_y = 0;
        }
        else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
        {
          new_e = world_spawn_entity( new_entity_type, 
                                      e->pos_x, e->pos_y - 32);
          entity_set_facing(new_e, ENTITY_FACING_UP);
          new_e->vel_x = 0;
          new_e->vel_y = -4;
        }
        else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
        {
          new_e = world_spawn_entity( new_entity_type, 
                                      e->pos_x - 32, e->pos_y);
          entity_set_facing(new_e, ENTITY_FACING_LEFT);
          new_e->vel_x = -4;
          new_e->vel_y = 0;
        }
        else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
        {
          new_e = world_spawn_entity( new_entity_type, 
                                      e->pos_x, e->pos_y + 32);
          entity_set_facing(new_e, ENTITY_FACING_DOWN);
          new_e->vel_x = 0;
          new_e->vel_y = 4;
        }

        doremi_play_sfx(SFX_INDEX_EVIL_EYE_CAST);

        G_game_state_flags |= GLOBAL_GAME_STATE_FLAG_EVIL_EYE_CAST;
      }

      /* clear casting flag */
      e->action_flags &= ~ENTITY_ACTION_FLAG_CASTING;
    }

    e = e->next;
  }

  /* if evil eye was cast, return */
  if (G_game_state_flags & GLOBAL_GAME_STATE_FLAG_EVIL_EYE_CAST)
    return 0;

  /* spell casting */
  for (i = 0; i < CATEGORY_NUM_INDICES; i++)
  {
    if (!(CATEGORY_INDEX_CAN_CAST_SPELLS(i)))
      continue;

    for ( e = G_entity_active_list_head[i];
          e != NULL;
          e = e->next)
    {
      if (e->action_flags & ENTITY_ACTION_FLAG_CASTING)
      {
        /* determine spell to cast */
        if (ENTITY_TYPE_IS_BALLISTA(e->type))
          new_entity_type = ENTITY_TYPE_BALLISTA_BOLT;
        else if (e->type == ENTITY_TYPE_SNAKE)
          new_entity_type = ENTITY_TYPE_FIRE_SPELL;
        else if (e->type == ENTITY_TYPE_WITCH)
          new_entity_type = ENTITY_TYPE_NEUTRAL_SPELL;
        else if (e->type == ENTITY_TYPE_UNDINE)
          new_entity_type = ENTITY_TYPE_ICE_SPELL;
        else if (e->type == ENTITY_TYPE_SORCERESS)
          new_entity_type = ENTITY_TYPE_WARP_SPELL;
        else if (e->type == ENTITY_TYPE_LASER_GUN)
          new_entity_type = ENTITY_TYPE_LASER_SHOT;
        else if ( (e->type == ENTITY_TYPE_PLAYER_VAMPIRE)         ||
                  (e->type == ENTITY_TYPE_DOUBLE_VAMPIRE)         ||
                  (e->type == ENTITY_TYPE_REVERSE_DOUBLE_VAMPIRE))
        {
          if (e->action_flags & ENTITY_ACTION_FLAG_MODE)
          {
            new_entity_type = ENTITY_TYPE_WARP_SPELL;
            e->action_flags &= ~ENTITY_ACTION_FLAG_MODE;
          }
          else
          {
            new_entity_type = ENTITY_TYPE_ICE_SPELL;
          }
        }
        else if (e->type == ENTITY_TYPE_SPELLBINDER_FIRE)
          new_entity_type = ENTITY_TYPE_FIRE_SPELL;
        else if (e->type == ENTITY_TYPE_SPELLBINDER_ICE)
          new_entity_type = ENTITY_TYPE_ICE_SPELL;
        else if (e->type == ENTITY_TYPE_SPELLBINDER_NEUTRAL)
          new_entity_type = ENTITY_TYPE_NEUTRAL_SPELL;
        else
          new_entity_type = ENTITY_TYPE_NONE;

        if (new_entity_type != ENTITY_TYPE_NONE)
        {
          /* play sfx */
          if (new_entity_type == ENTITY_TYPE_BALLISTA_BOLT)
            doremi_play_sfx(SFX_INDEX_BALLISTA_CAST);
          else if (new_entity_type == ENTITY_TYPE_FIRE_SPELL)
            doremi_play_sfx(SFX_INDEX_FIRE_SPELL_CAST);
          else if (new_entity_type == ENTITY_TYPE_ICE_SPELL)
            doremi_play_sfx(SFX_INDEX_ICE_SPELL_CAST);
          else if (new_entity_type == ENTITY_TYPE_NEUTRAL_SPELL)
            doremi_play_sfx(SFX_INDEX_NEUTRAL_SPELL_CAST);
          else if (new_entity_type == ENTITY_TYPE_WARP_SPELL)
            doremi_play_sfx(SFX_INDEX_WARP_SPELL_CAST);
          else if (new_entity_type == ENTITY_TYPE_LASER_SHOT)
            doremi_play_sfx(SFX_INDEX_LASER_SHOT_CAST);

          /* if caster is moving, complete move before spell cast */
          /* (should only be happening with spellbinders)         */
          if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
          {
            collide_grid_remove_entity(e);
            e->pos_x += e->vel_x * e->move_count;
            e->pos_y += e->vel_y * e->move_count;
            e->move_count = 0;
            e->vel_x = 0;
            e->vel_y = 0;
            collide_grid_add_entity(e);
          }

          /* create spell */
          if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
          {
            new_e = world_spawn_entity( new_entity_type, 
                                        e->pos_x + 32, e->pos_y);
            collide_grid_add_entity(new_e);
            entity_set_facing(new_e, ENTITY_FACING_RIGHT);
            animation_setup(new_e);
            new_e->orientation &= ~ENTITY_DIRECTION_MASK;
            new_e->orientation |= ENTITY_DIRECTION_RIGHT;
          }
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
          {
            new_e = world_spawn_entity( new_entity_type, 
                                        e->pos_x, e->pos_y - 32);
            collide_grid_add_entity(new_e);
            entity_set_facing(new_e, ENTITY_FACING_UP);
            animation_setup(new_e);
            new_e->orientation &= ~ENTITY_DIRECTION_MASK;
            new_e->orientation |= ENTITY_DIRECTION_UP;
          }
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
          {
            new_e = world_spawn_entity( new_entity_type, 
                                        e->pos_x - 32, e->pos_y);
            collide_grid_add_entity(new_e);
            entity_set_facing(new_e, ENTITY_FACING_LEFT);
            animation_setup(new_e);
            new_e->orientation &= ~ENTITY_DIRECTION_MASK;
            new_e->orientation |= ENTITY_DIRECTION_LEFT;
          }
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
          {
            new_e = world_spawn_entity( new_entity_type, 
                                        e->pos_x, e->pos_y + 32);
            collide_grid_add_entity(new_e);
            entity_set_facing(new_e, ENTITY_FACING_DOWN);
            animation_setup(new_e);
            new_e->orientation &= ~ENTITY_DIRECTION_MASK;
            new_e->orientation |= ENTITY_DIRECTION_DOWN;
          }
          else
          {
            e->action_flags &= ~ENTITY_ACTION_FLAG_CASTING;
            continue;
          }

          /* if warp spell was cast, add node to the cast warps list */
          if (new_entity_type == ENTITY_TYPE_WARP_SPELL)
            pair_trees_and_lists_add_cast_warp(new_e, e);

          /* check if spell spawned on a damaging tile */
          logic_check_damage_on_spawn(new_e);

          /* check if fire or ice spell spawned over a yin yang */
          if ((new_entity_type == ENTITY_TYPE_FIRE_SPELL) ||
              (new_entity_type == ENTITY_TYPE_ICE_SPELL))
          {
            logic_check_if_over_yin_yang(new_e);
          }

          /* set cooldown */
          if (ENTITY_TYPE_IS_BALLISTA(e->type))
          {
            e->update_flags |= ENTITY_UPDATE_FLAG_COOLDOWN;
            e->cooldown_count = ENTITY_COOLDOWN_TIME_BALLISTA;
            animation_setup(e);
          }
          else if (e->type == ENTITY_TYPE_SNAKE)
          {
            e->update_flags |= ENTITY_UPDATE_FLAG_COOLDOWN;
            e->cooldown_count = ENTITY_COOLDOWN_TIME_SNAKE;
            animation_setup(e);
          }
          else if (e->type == ENTITY_TYPE_WITCH)
          {
            e->update_flags |= ENTITY_UPDATE_FLAG_COOLDOWN;
            e->cooldown_count = ENTITY_COOLDOWN_TIME_WITCH;
            animation_setup(e);
          }
          else if (e->type == ENTITY_TYPE_UNDINE)
          {
            e->update_flags |= ENTITY_UPDATE_FLAG_COOLDOWN;
            e->cooldown_count = ENTITY_COOLDOWN_TIME_UNDINE;
            animation_setup(e);
          }
          else if (e->type == ENTITY_TYPE_SORCERESS)
          {
            e->update_flags |= ENTITY_UPDATE_FLAG_COOLDOWN;
            e->cooldown_count = ENTITY_COOLDOWN_TIME_SORCERESS;
            animation_setup(e);
          }
          else if (e->type == ENTITY_TYPE_LASER_GUN)
          {
            e->update_flags |= ENTITY_UPDATE_FLAG_COOLDOWN;
            e->cooldown_count = ENTITY_COOLDOWN_TIME_LASER_GUN;
            animation_setup(e);
          }
          else if ( (e->type == ENTITY_TYPE_PLAYER_VAMPIRE) ||
                    (e->type == ENTITY_TYPE_DOUBLE_VAMPIRE) ||
                    (e->type == ENTITY_TYPE_REVERSE_DOUBLE_VAMPIRE))
          {
            e->update_flags |= ENTITY_UPDATE_FLAG_COOLDOWN;
            e->cooldown_count = ENTITY_COOLDOWN_TIME_VAMPIRE;
            animation_setup(e);
          }

          /* if this is a spellbinder, set transformation flag            */
          /* mode flag prevents this transformation from being cancelled  */
          if (ENTITY_TYPE_IS_SPELLBINDER(e->type))
          {
            e->update_flags |= ENTITY_UPDATE_FLAG_TRANSFORMING;
            e->action_flags |= ENTITY_ACTION_FLAG_MODE;
          }
        }

        /* clear casting flag */
        e->action_flags &= ~ENTITY_ACTION_FLAG_CASTING;
      }
    }
  }

  return 0;
}

/*******************************************************************************
** logic_process_damage_and_transformations()
*******************************************************************************/
short int logic_process_damage_and_transformations()
{
  int     i;
  entity* e;
  entity* next_e;
  entity* new_e;
  int     new_entity_type;
  entity* sync_e;
  int     water_frame_count;
  int     venusian_frame_count;

  /* set up water frame count */
  sync_e = G_entity_active_list_head[CATEGORY_INDEX_WATER];

  if (sync_e == NULL)
    water_frame_count = 0;
  else
    water_frame_count = sync_e->frame_count;

  /* set up venusian frame count */
  venusian_frame_count = 0;

  for ( sync_e = G_entity_active_list_head[CATEGORY_INDEX_SNAKES_FAERIES_VENUSIANS];
        sync_e != NULL;
        sync_e = sync_e->next)
  {
    if (sync_e->type == ENTITY_TYPE_VENUSIAN)
    {
      venusian_frame_count = sync_e->frame_count;
      break;
    }
  }

  /* objects falling into water */
  for (i = 0; i < CATEGORY_NUM_INDICES; i++)
  {
    if (!(CATEGORY_INDEX_CAN_FALL_INTO_WATER(i)))
      continue;

    e = G_entity_active_list_head[i];

    while (e != NULL)
    {
      next_e = e->next;

      if (e->update_flags & ENTITY_UPDATE_FLAG_FELL_INTO_WATER)
      {
        world_spawn_particles_water_splash(e);
        doremi_play_sfx(SFX_INDEX_WATER_SPLASH);

        if (ENTITY_TYPE_IS_SUBMERGABLE(e->type))
        {
          if (e->type == ENTITY_TYPE_BOX_WOOD)
            new_entity_type = ENTITY_TYPE_BOX_WOOD_SUBMERGED;
          else if (e->type == ENTITY_TYPE_BOX_METAL)
            new_entity_type = ENTITY_TYPE_BOX_METAL_SUBMERGED;
          else if (e->type == ENTITY_TYPE_BOX_TNT)
            new_entity_type = ENTITY_TYPE_BOX_TNT_SUBMERGED;
          else if (e->type == ENTITY_TYPE_BOX_STONE)
            new_entity_type = ENTITY_TYPE_BOX_STONE_SUBMERGED;
          else if (e->type == ENTITY_TYPE_PRISM_BLOCK_0)
            new_entity_type = ENTITY_TYPE_PRISM_BLOCK_0_SUBMERGED;
          else if (e->type == ENTITY_TYPE_PRISM_BLOCK_45)
            new_entity_type = ENTITY_TYPE_PRISM_BLOCK_45_SUBMERGED;
          else if (e->type == ENTITY_TYPE_PRISM_BLOCK_90)
            new_entity_type = ENTITY_TYPE_PRISM_BLOCK_90_SUBMERGED;
          else if (e->type == ENTITY_TYPE_PRISM_BLOCK_135)
            new_entity_type = ENTITY_TYPE_PRISM_BLOCK_135_SUBMERGED;
          else if (e->type == ENTITY_TYPE_DIE_SOLID_1)
            new_entity_type = ENTITY_TYPE_DIE_SOLID_1_SUBMERGED;
          else if (e->type == ENTITY_TYPE_DIE_SOLID_2)
            new_entity_type = ENTITY_TYPE_DIE_SOLID_2_SUBMERGED;
          else if (e->type == ENTITY_TYPE_DIE_SOLID_3)
            new_entity_type = ENTITY_TYPE_DIE_SOLID_3_SUBMERGED;
          else if (e->type == ENTITY_TYPE_DIE_SOLID_4)
            new_entity_type = ENTITY_TYPE_DIE_SOLID_4_SUBMERGED;
          else if (e->type == ENTITY_TYPE_DIE_SOLID_5)
            new_entity_type = ENTITY_TYPE_DIE_SOLID_5_SUBMERGED;
          else if (e->type == ENTITY_TYPE_DIE_SOLID_6)
            new_entity_type = ENTITY_TYPE_DIE_SOLID_6_SUBMERGED;
          else if (e->type == ENTITY_TYPE_DIE_VANISHED_1)
            new_entity_type = ENTITY_TYPE_DIE_VANISHED_1_SUBMERGED;
          else if (e->type == ENTITY_TYPE_DIE_VANISHED_2)
            new_entity_type = ENTITY_TYPE_DIE_VANISHED_2_SUBMERGED;
          else if (e->type == ENTITY_TYPE_DIE_VANISHED_3)
            new_entity_type = ENTITY_TYPE_DIE_VANISHED_3_SUBMERGED;
          else if (e->type == ENTITY_TYPE_DIE_VANISHED_4)
            new_entity_type = ENTITY_TYPE_DIE_VANISHED_4_SUBMERGED;
          else if (e->type == ENTITY_TYPE_DIE_VANISHED_5)
            new_entity_type = ENTITY_TYPE_DIE_VANISHED_5_SUBMERGED;
          else if (e->type == ENTITY_TYPE_DIE_VANISHED_6)
            new_entity_type = ENTITY_TYPE_DIE_VANISHED_6_SUBMERGED;
          else if (e->type == ENTITY_TYPE_MAHJONG_TILE_EAST)
            new_entity_type = ENTITY_TYPE_MAHJONG_TILE_EAST_SUBMERGED;
          else if (e->type == ENTITY_TYPE_MAHJONG_TILE_NORTH)
            new_entity_type = ENTITY_TYPE_MAHJONG_TILE_NORTH_SUBMERGED;
          else if (e->type == ENTITY_TYPE_MAHJONG_TILE_WEST)
            new_entity_type = ENTITY_TYPE_MAHJONG_TILE_WEST_SUBMERGED;
          else if (e->type == ENTITY_TYPE_MAHJONG_TILE_SOUTH)
            new_entity_type = ENTITY_TYPE_MAHJONG_TILE_SOUTH_SUBMERGED;
          else if (e->type == ENTITY_TYPE_SPELLBINDER_EMPTY)
            new_entity_type = ENTITY_TYPE_SPELLBINDER_EMPTY_SUBMERGED;
          else if (e->type == ENTITY_TYPE_SPELLBINDER_FIRE)
            new_entity_type = ENTITY_TYPE_SPELLBINDER_FIRE_SUBMERGED;
          else if (e->type == ENTITY_TYPE_SPELLBINDER_ICE)
            new_entity_type = ENTITY_TYPE_SPELLBINDER_ICE_SUBMERGED;
          else if (e->type == ENTITY_TYPE_SPELLBINDER_NEUTRAL)
            new_entity_type = ENTITY_TYPE_SPELLBINDER_NEUTRAL_SUBMERGED;
          else if (ENTITY_TYPE_IS_ICE_CUBE(e->type))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_SUBMERGED;
          else
            new_entity_type = ENTITY_TYPE_NONE;

          if (new_entity_type != ENTITY_TYPE_NONE)
          {
            new_e = world_spawn_entity(new_entity_type, e->pos_x, e->pos_y);
            animation_setup(new_e);
            collide_grid_add_entity(new_e);

            /* copy collision flags, in case this entity was hit this frame */
            new_e->collision_flags = e->collision_flags;

            /* copy cooldown count and frame count for ice cube */
            if (new_entity_type == ENTITY_TYPE_ICE_CUBE_SUBMERGED)
            {
              new_e->update_flags |= ENTITY_UPDATE_FLAG_COOLDOWN;
              new_e->cooldown_count = e->cooldown_count;
              new_e->frame_count = e->frame_count;
            }

            /* if player fell into water (as an ice cube),  */
            /* update G_player accordinly                   */
            if (e == G_player)
            {
              G_player = new_e;
            }
          }
        }
        else if (ENTITY_TYPE_IS_WARP_CASTER(e->type))
        {
          pair_trees_and_lists_remove_all_cast_warps_by_caster(e);

          /* if player fell into water (as a vampire),  */
          /* count this as a player death               */
          if (e == G_player)
          {
            G_player = NULL;
            logic_player_death();
          }
        }

        collide_grid_remove_entity(e);
        world_despawn_entity(e);
      }

      e = next_e;
    }
  }

  /* damage calculation - cycle through all spawned entities */
  for (i = 0; i < CATEGORY_NUM_INDICES; i++)
  {
    if (!(CATEGORY_INDEX_CAN_BE_DAMAGED(i)))
      continue;

    e = G_entity_active_list_head[i];

    while (e != NULL)
    {
      next_e = e->next;

      /* compute damage done to this entity, if necessary */
      if (e->collision_flags != ENTITY_COLLISION_FLAGS_CLEAR)
      {
        /* fire and ice spells cancel each other */
        if ((e->collision_flags & ENTITY_COLLISION_FLAG_FIRE) &&
            (e->collision_flags & ENTITY_COLLISION_FLAG_ICE))
        {
          e->collision_flags &= ~ENTITY_COLLISION_FLAG_FIRE;
          e->collision_flags &= ~ENTITY_COLLISION_FLAG_ICE;
        }

        /* if a damaging type is set, subtract damage amount from hp */
        if (e->collision_flags & ENTITY_COLLISION_FLAG_LOST_1_HP)
          e->hp -= 1;

        if (e->collision_flags & ENTITY_COLLISION_FLAG_LOST_2_HP)
          e->hp -= 2;

        if (e->collision_flags & ENTITY_COLLISION_FLAG_DESTROYED)
          e->hp = 0;

        /* fire thaws ice cubes, lights candles,          */
        /* sets spellbinders, and destroys other entities */
        if (e->collision_flags & ENTITY_COLLISION_FLAG_FIRE)
        {
          if (ENTITY_TYPE_IS_ICE_CUBE(e->type))
          {
            e->cooldown_count = 0;
            e->update_flags &= ~ENTITY_UPDATE_FLAG_COOLDOWN;

            if (!(e->action_flags & ENTITY_ACTION_FLAG_MOVING))
              e->update_flags |= ENTITY_UPDATE_FLAG_TRANSFORMING;
          }
          else if (e->type == ENTITY_TYPE_CANDLE_UNLIT)
          {
            e->update_flags |= ENTITY_UPDATE_FLAG_TRANSFORMING;
          }
          else if (!(ENTITY_TYPE_IS_SPELLBINDER(e->type)))
            e->hp = 0;
        }

        /* neutral sets spellbinders, destroys other entities */
        if (e->collision_flags & ENTITY_COLLISION_FLAG_NEUTRAL)
        {
          if (!(ENTITY_TYPE_IS_SPELLBINDER(e->type)))
            e->hp = 0;
        }

        /* ballista bolt sets spellbinders, destroys other entities */
        if (e->collision_flags & ENTITY_COLLISION_FLAG_BOLT)
        {
          if (!(ENTITY_TYPE_IS_SPELLBINDER(e->type)))
            e->hp = 0;
        }

        /* update animation for flasks, if necessary */
        if ((e->type == ENTITY_TYPE_AQUA_FORTIS) && (e->hp <= 2))
          e->animation_array = G_animation_aqua_fortis_cracked;
        else if ((e->type == ENTITY_TYPE_AQUA_EXPLODIS) && (e->hp <= 2))
          e->animation_array = G_animation_aqua_explodis_cracked;

        /* pickup collected */
        if ((ENTITY_TYPE_IS_PICKUP(e->type)) && 
            (e->collision_flags & ENTITY_COLLISION_FLAG_COLLECTED))
        {
          collide_grid_remove_entity(e);
          world_despawn_entity(e);
        }
        /* entity is destroyed if hp is depleted */
        else if (e->hp <= 0)
        {
          if (ENTITY_TYPE_IS_FLOOR_SPIKE_UP(e->type)  ||
              ENTITY_TYPE_IS_FLOOR_SPIKE_DOWN(e->type))
          {
            world_spawn_particles_floor_spike(e);
          }
          else
          {
            world_spawn_particles_firework(e);
          }

          /* bridges and submerged objects spawn water tiles */
          if (ENTITY_TYPE_IS_BRIDGE(e->type)    ||
              ENTITY_TYPE_IS_SUBMERGED(e->type))
          {
            new_e = world_spawn_entity( ENTITY_TYPE_WATER, 
                                        e->pos_x - 8, e->pos_y - 8);
            collide_grid_add_entity(new_e);
            new_e->frame_count = water_frame_count;

            new_e = world_spawn_entity( ENTITY_TYPE_WATER, 
                                        e->pos_x + 8, e->pos_y - 8);
            collide_grid_add_entity(new_e);
            new_e->frame_count = water_frame_count;

            new_e = world_spawn_entity( ENTITY_TYPE_WATER, 
                                        e->pos_x - 8, e->pos_y + 8);
            collide_grid_add_entity(new_e);
            new_e->frame_count = water_frame_count;

            new_e = world_spawn_entity( ENTITY_TYPE_WATER, 
                                        e->pos_x + 8, e->pos_y + 8);
            collide_grid_add_entity(new_e);
            new_e->frame_count = water_frame_count;

            /* if submerged object was the player (as an ice cube), */
            /* count this as a player death                         */
            if (e == G_player)
            {
              G_player = NULL;
              logic_player_death();
            }

            collide_grid_remove_entity(e);
            world_despawn_entity(e);
            doremi_play_sfx(SFX_INDEX_ENTITY_DESTROYED);
          }
          /* explosive objects spawn explosions */
          else if (ENTITY_TYPE_IS_EXPLOSIVE(e->type))
          {
            doremi_play_sfx(SFX_INDEX_KABOOM);

            collide_grid_remove_entity(e);

            /* if object was moving, complete move */
            if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
            {
              e->pos_x += e->vel_x * e->move_count;
              e->pos_y += e->vel_y * e->move_count;
              e->move_count = 0;
              e->vel_x = 0;
              e->vel_y = 0;
            }

            /* explosion (center) */
            new_e = world_spawn_entity( ENTITY_TYPE_EXPLOSION, 
                                        e->pos_x, e->pos_y);
            collide_grid_add_entity(new_e);
            new_e->update_flags |= ENTITY_UPDATE_FLAG_COOLDOWN;
            new_e->cooldown_count = ENTITY_COOLDOWN_TIME_EXPLOSION;

            /* explosion (left) */
            if (e->pos_x >= 64)
            {
              new_e = world_spawn_entity( ENTITY_TYPE_EXPLOSION, 
                                          e->pos_x - 32, e->pos_y);
              collide_grid_add_entity(new_e);
              new_e->update_flags |= ENTITY_UPDATE_FLAG_COOLDOWN;
              new_e->cooldown_count = ENTITY_COOLDOWN_TIME_EXPLOSION;
            }

            /* explosion (right) */
            if (e->pos_x <= 352)
            {
              new_e = world_spawn_entity( ENTITY_TYPE_EXPLOSION, 
                                          e->pos_x + 32, e->pos_y);
              collide_grid_add_entity(new_e);
              new_e->update_flags |= ENTITY_UPDATE_FLAG_COOLDOWN;
              new_e->cooldown_count = ENTITY_COOLDOWN_TIME_EXPLOSION;
            }

            /* explosion (up) */
            if (e->pos_y >= 96)
            {
              new_e = world_spawn_entity( ENTITY_TYPE_EXPLOSION, 
                                          e->pos_x, e->pos_y - 32);
              collide_grid_add_entity(new_e);
              new_e->update_flags |= ENTITY_UPDATE_FLAG_COOLDOWN;
              new_e->cooldown_count = ENTITY_COOLDOWN_TIME_EXPLOSION;
            }

            /* explosion (down) */
            if (e->pos_y <= 384)
            {
              new_e = world_spawn_entity( ENTITY_TYPE_EXPLOSION, 
                                          e->pos_x, e->pos_y + 32);
              collide_grid_add_entity(new_e);
              new_e->update_flags |= ENTITY_UPDATE_FLAG_COOLDOWN;
              new_e->cooldown_count = ENTITY_COOLDOWN_TIME_EXPLOSION;
            }

            world_despawn_entity(e);
          }
          /* if warp caster is destroyed, nullify cast warps */
          else if (ENTITY_TYPE_IS_WARP_CASTER(e->type))
          {
            pair_trees_and_lists_remove_all_cast_warps_by_caster(e);

            /* if player is destroyed, set game state */
            if (e == G_player)
            {
              G_player = NULL;
              logic_player_death();
            }
            else
            {
              doremi_play_sfx(SFX_INDEX_ENEMY_DEATH);
            }

            collide_grid_remove_entity(e);
            world_despawn_entity(e);
          }
          /* if a venusian is destroyed, set roots */
          else if (e->type == ENTITY_TYPE_VENUSIAN)
          {
            logic_set_venusian_roots(e);

            collide_grid_remove_entity(e);
            world_despawn_entity(e);
            doremi_play_sfx(SFX_INDEX_ENEMY_DEATH);
          }
          /* if blood or bat vial was destroyed, set game state */
          else if ( (e->type == ENTITY_TYPE_BLOOD_VIAL) ||
                    (e->type == ENTITY_TYPE_BAT_VIAL))
          {
            G_game_state_flags |= GLOBAL_GAME_STATE_FLAG_BLOOD_LOST;

            collide_grid_remove_entity(e);
            world_despawn_entity(e);
            doremi_play_sfx(SFX_INDEX_GLASS_BREAK);
          }
          /* otherwise, despawn entity */
          else if ( (e->type == ENTITY_TYPE_BLUE_MANA)  ||
                    (e->type == ENTITY_TYPE_GREEN_MANA) ||
                    (e->type == ENTITY_TYPE_AQUA_FORTIS))
          {
            collide_grid_remove_entity(e);
            world_despawn_entity(e);
            doremi_play_sfx(SFX_INDEX_GLASS_BREAK);
          }
          else if (ENTITY_TYPE_IS_ENEMY(e->type))
          {
            collide_grid_remove_entity(e);
            world_despawn_entity(e);
            doremi_play_sfx(SFX_INDEX_ENEMY_DEATH);
          }
          else if (ENTITY_TYPE_IS_SPELL(e->type))
          {
            collide_grid_remove_entity(e);
            world_despawn_entity(e);
            doremi_play_sfx(SFX_INDEX_SPELL_HITTING_WALL);
          }
          else if ( ENTITY_TYPE_IS_FLOOR_SPIKE_UP(e->type)  ||
                    ENTITY_TYPE_IS_FLOOR_SPIKE_DOWN(e->type))
          {
            collide_grid_remove_entity(e);
            world_despawn_entity(e);
            doremi_play_sfx(SFX_INDEX_SPIKE_BREAK);
          }
          else if ( (e->type == ENTITY_TYPE_WATER)  ||
                    (e->type == ENTITY_TYPE_EXPLOSION))
          {
            collide_grid_remove_entity(e);
            world_despawn_entity(e);
          }
          else
          {
            collide_grid_remove_entity(e);
            world_despawn_entity(e);
            doremi_play_sfx(SFX_INDEX_ENTITY_DESTROYED);
          }
        }
        /* casting / transforming spellbinders retain flags */
        else if (ENTITY_TYPE_IS_SPELLBINDER(e->type))
        {
          if ((e->update_flags & ENTITY_UPDATE_FLAG_TRANSFORMING) ||
              (e->action_flags & ENTITY_ACTION_FLAG_CASTING))
          {
            e->collision_flags &= ENTITY_COLLISION_MASK_ELEMENTAL;

            /* if more than one elemental flag is set,  */
            /* cancel this cast or transform            */
            if (!((e->collision_flags == ENTITY_COLLISION_FLAG_FIRE)    ||
                  (e->collision_flags == ENTITY_COLLISION_FLAG_ICE)     ||
                  (e->collision_flags == ENTITY_COLLISION_FLAG_NEUTRAL) ||
                  (e->collision_flags == ENTITY_COLLISION_FLAG_BOLT)))
            {
              e->update_flags &= ~ENTITY_UPDATE_FLAG_TRANSFORMING;
              e->action_flags &= ~ENTITY_ACTION_FLAG_MODE;
              e->action_flags &= ~ENTITY_ACTION_FLAG_CASTING;
              e->collision_flags = ENTITY_COLLISION_FLAGS_CLEAR;
            }
          }
          else
          {
            e->collision_flags = ENTITY_COLLISION_FLAGS_CLEAR;
          }
        }
        /* freezing is handled during transformation stage */
        else if (e->collision_flags & ENTITY_COLLISION_FLAG_ICE)
        {
          if (ENTITY_TYPE_IS_ICE_CUBE(e->type))
          {
            e->update_flags |= ENTITY_UPDATE_FLAG_COOLDOWN;
            e->cooldown_count = ENTITY_COOLDOWN_TIME_ICE_CUBE;
            animation_setup(e);
            e->collision_flags = ENTITY_COLLISION_FLAGS_CLEAR;
          }
          else if (e->type == ENTITY_TYPE_CANDLE_LIT)
          {
            e->update_flags |= ENTITY_UPDATE_FLAG_TRANSFORMING;
            e->collision_flags = ENTITY_COLLISION_FLAGS_CLEAR;
          }
          else if ( (e->type == ENTITY_TYPE_MUMMY_LT) &&
                    (ENTITY_IS_IN_COOLDOWN(e)))
          {
            e->collision_flags = ENTITY_COLLISION_FLAGS_CLEAR;
          }
          else if ( (e->type == ENTITY_TYPE_MUMMY_RT) &&
                    (ENTITY_IS_IN_COOLDOWN(e)))
          {
            e->collision_flags = ENTITY_COLLISION_FLAGS_CLEAR;
          }
          else
          {
            e->collision_flags = ENTITY_COLLISION_FLAGS_CLEAR;
            e->collision_flags |= ENTITY_COLLISION_FLAG_ICE;
          }
        }
        /* otherwise, clear processed collision flags */
        else
        {
          e->collision_flags = ENTITY_COLLISION_FLAGS_CLEAR;
        }
      }

      e = next_e;
    }
  }

  /* transformations - cycle through all spawned entities */
  for (i = 0; i < CATEGORY_NUM_INDICES; i++)
  {
    if (!(CATEGORY_INDEX_CAN_TRANSFORM(i)))
      continue;

    e = G_entity_active_list_head[i];

    while (e != NULL)
    {
      next_e = e->next;

      /* spellbinders */
      if (ENTITY_TYPE_IS_SPELLBINDER(e->type))
      {
        if (e->update_flags & ENTITY_UPDATE_FLAG_TRANSFORMING)
        {
          if (e->collision_flags & ENTITY_COLLISION_FLAG_FIRE)
            new_entity_type = ENTITY_TYPE_SPELLBINDER_FIRE;
          else if (e->collision_flags & ENTITY_COLLISION_FLAG_ICE)
            new_entity_type = ENTITY_TYPE_SPELLBINDER_ICE;
          else if (e->collision_flags & ENTITY_COLLISION_FLAG_NEUTRAL)
            new_entity_type = ENTITY_TYPE_SPELLBINDER_NEUTRAL;
          else if (e->collision_flags & ENTITY_COLLISION_FLAG_BOLT)
            new_entity_type = ENTITY_TYPE_SPELLBINDER_EMPTY;
          else
            new_entity_type = ENTITY_TYPE_NONE;

          if (new_entity_type != ENTITY_TYPE_NONE)
          {
            new_e = world_spawn_entity( new_entity_type, 
                                        e->pos_x, e->pos_y);

            /* if spellbinder was moving, jump to end of that movement */
            if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
            {
              new_e->pos_x += e->vel_x * e->move_count;
              new_e->pos_y += e->vel_y * e->move_count;
            }

            /* if spellbinder was moving into water, jump additional amount */
            if (e->update_flags & ENTITY_UPDATE_FLAG_MOVING_INTO_WATER)
            {
              if (e->vel_x > 0)
                new_e->pos_x += 16;
              else if (e->vel_x < 0)
                new_e->pos_x -= 16;

              if (e->vel_y > 0)
                new_e->pos_y += 16;
              else if (e->vel_y < 0)
                new_e->pos_y -= 16;
            }

            animation_setup(new_e);
            collide_grid_add_entity(new_e);

            collide_grid_remove_entity(e);
            world_despawn_entity(e);

            /* check if spellbinder is over water */
            logic_check_if_over_water(new_e);

            if (!(new_e->update_flags & ENTITY_UPDATE_FLAG_FELL_INTO_WATER))
            {
              logic_press_switches(new_e);
              logic_check_if_over_conveyer(new_e);
            }
          }
        }
      }
      /* freezing */
      else if (e->collision_flags & ENTITY_COLLISION_FLAG_ICE)
      {
        /* determine ice cube type */
        if (e->type == ENTITY_TYPE_PUMPKIN)
        {
          new_entity_type = ENTITY_TYPE_ICE_CUBE_PUMPKIN;
        }
        else if (e->type == ENTITY_TYPE_GHOST)
        {
          if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_GHOST_RIGHT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_GHOST_UP;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_GHOST_LEFT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_GHOST_DOWN;
          else
            new_entity_type = ENTITY_TYPE_NONE;
        }
        else if (e->type == ENTITY_TYPE_MASK_HORIZONTAL)
        {
          if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_RIGHT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_MASK_HORIZONTAL_RIGHT;
          else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_LEFT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_MASK_HORIZONTAL_LEFT;
          else
            new_entity_type = ENTITY_TYPE_NONE;
        }
        else if (e->type == ENTITY_TYPE_MASK_VERTICAL)
        {
          if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_UP))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_MASK_VERTICAL_UP;
          else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_DOWN))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_MASK_VERTICAL_DOWN;
          else
            new_entity_type = ENTITY_TYPE_NONE;
        }
        else if (e->type == ENTITY_TYPE_SNAKE)
        {
          if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_SNAKE_RIGHT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_SNAKE_UP;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_SNAKE_LEFT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_SNAKE_DOWN;
          else
            new_entity_type = ENTITY_TYPE_NONE;
        }
        else if (e->type == ENTITY_TYPE_DOUBLE_VAMPIRE)
        {
          if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_DOUBLE_VAMPIRE_RIGHT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_DOUBLE_VAMPIRE_UP;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_DOUBLE_VAMPIRE_LEFT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_DOUBLE_VAMPIRE_DOWN;
          else
            new_entity_type = ENTITY_TYPE_NONE;
        }
        else if (e->type == ENTITY_TYPE_DOUBLE_BAT)
        {
          if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_DOUBLE_BAT_RIGHT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_DOUBLE_BAT_UP;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_DOUBLE_BAT_LEFT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_DOUBLE_BAT_DOWN;
          else
            new_entity_type = ENTITY_TYPE_NONE;
        }
        else if (e->type == ENTITY_TYPE_REVERSE_DOUBLE_VAMPIRE)
        {
          if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_VAMPIRE_RIGHT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_VAMPIRE_UP;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_VAMPIRE_LEFT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_VAMPIRE_DOWN;
          else
            new_entity_type = ENTITY_TYPE_NONE;
        }
        else if (e->type == ENTITY_TYPE_REVERSE_DOUBLE_BAT)
        {
          if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_BAT_RIGHT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_BAT_UP;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_BAT_LEFT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_BAT_DOWN;
          else
            new_entity_type = ENTITY_TYPE_NONE;
        }
        else if (e->type == ENTITY_TYPE_FAERIE_HORIZONTAL)
        {
          if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_FAERIE_HORIZONTAL_UP;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_FAERIE_HORIZONTAL_DOWN;
          else
            new_entity_type = ENTITY_TYPE_NONE;
        }
        else if (e->type == ENTITY_TYPE_FAERIE_VERTICAL)
        {
          if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_FAERIE_VERTICAL_RIGHT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_FAERIE_VERTICAL_LEFT;
          else
            new_entity_type = ENTITY_TYPE_NONE;
        }
        else if (e->type == ENTITY_TYPE_VENUSIAN)
        {
          new_entity_type = ENTITY_TYPE_ICE_CUBE_VENUSIAN;
        }
        else if (e->type == ENTITY_TYPE_WITCH)
        {
          if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_WITCH_RIGHT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_WITCH_UP;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_WITCH_LEFT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_WITCH_DOWN;
          else
            new_entity_type = ENTITY_TYPE_NONE;
        }
        else if (e->type == ENTITY_TYPE_SORCERESS)
        {
          if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_SORCERESS_RIGHT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_SORCERESS_UP;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_SORCERESS_LEFT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_SORCERESS_DOWN;
          else
            new_entity_type = ENTITY_TYPE_NONE;
        }
        else if (e->type == ENTITY_TYPE_FROG)
        {
          if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_FROG_RIGHT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_FROG_UP;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_FROG_LEFT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_FROG_DOWN;
          else
            new_entity_type = ENTITY_TYPE_NONE;
        }
        else if (e->type == ENTITY_TYPE_IMP_LT)
        {
          if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_IMP_LT_RIGHT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_IMP_LT_UP;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_IMP_LT_LEFT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_IMP_LT_DOWN;
          else
            new_entity_type = ENTITY_TYPE_NONE;
        }
        else if (e->type == ENTITY_TYPE_IMP_RT)
        {
          if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_IMP_RT_RIGHT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_IMP_RT_UP;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_IMP_RT_LEFT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_IMP_RT_DOWN;
          else
            new_entity_type = ENTITY_TYPE_NONE;
        }
        else if (e->type == ENTITY_TYPE_LIL_BOT)
        {
          if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_LIL_BOT_RIGHT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_LIL_BOT_UP;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_LIL_BOT_LEFT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_LIL_BOT_DOWN;
          else
            new_entity_type = ENTITY_TYPE_NONE;
        }
        else if (e->type == ENTITY_TYPE_JIANGSHI_LT)
        {
          if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
            new_entity_type = ENTITY_TYPE_ICE_CUBE_JIANGSHI_LT_STOPPED;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_JIANGSHI_LT_RIGHT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_JIANGSHI_LT_UP;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_JIANGSHI_LT_LEFT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_JIANGSHI_LT_DOWN;
          else
            new_entity_type = ENTITY_TYPE_NONE;
        }
        else if (e->type == ENTITY_TYPE_JIANGSHI_RT)
        {
          if (e->update_flags & ENTITY_UPDATE_FLAG_ACTIVE)
            new_entity_type = ENTITY_TYPE_ICE_CUBE_JIANGSHI_RT_STOPPED;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_JIANGSHI_RT_RIGHT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_JIANGSHI_RT_UP;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_JIANGSHI_RT_LEFT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_JIANGSHI_RT_DOWN;
          else
            new_entity_type = ENTITY_TYPE_NONE;
        }
        else if (e->type == ENTITY_TYPE_MUMMY_LT)
        {
          new_entity_type = ENTITY_TYPE_ICE_CUBE_MUMMY_LT;
        }
        else if (e->type == ENTITY_TYPE_MUMMY_RT)
        {
          new_entity_type = ENTITY_TYPE_ICE_CUBE_MUMMY_RT;
        }
        else if (e->type == ENTITY_TYPE_PLAYER_VAMPIRE)
        {
          if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_PLAYER_VAMPIRE_RIGHT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_PLAYER_VAMPIRE_UP;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_PLAYER_VAMPIRE_LEFT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_PLAYER_VAMPIRE_DOWN;
          else
            new_entity_type = ENTITY_TYPE_NONE;
        }
        else if (e->type == ENTITY_TYPE_PLAYER_BAT)
        {
          if (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_PLAYER_BAT_RIGHT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_PLAYER_BAT_UP;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_PLAYER_BAT_LEFT;
          else if (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN))
            new_entity_type = ENTITY_TYPE_ICE_CUBE_PLAYER_BAT_DOWN;
          else
            new_entity_type = ENTITY_TYPE_NONE;
        }
        else
          new_entity_type = ENTITY_TYPE_NONE;

        /* transform to ice cube */
        if (new_entity_type != ENTITY_TYPE_NONE)
        {
          doremi_play_sfx(SFX_INDEX_FREEZING);

          new_e = world_spawn_entity( new_entity_type, 
                                      e->pos_x, e->pos_y);

          /* if entity was moving, jump ice cube to end of that move */
          if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
          {
            new_e->pos_x += e->vel_x * e->move_count;
            new_e->pos_y += e->vel_y * e->move_count;
          }

          /* if entity was moving into water, jump additional amount */
          if (e->update_flags & ENTITY_UPDATE_FLAG_MOVING_INTO_WATER)
          {
            if (e->vel_x > 0)
              new_e->pos_x += 16;
            else if (e->vel_x < 0)
              new_e->pos_x -= 16;

            if (e->vel_y > 0)
              new_e->pos_y += 16;
            else if (e->vel_y < 0)
              new_e->pos_y -= 16;
          }

          animation_setup(new_e);
          collide_grid_add_entity(new_e);

          /* set initial cooldown for ice cube */
          new_e->update_flags |= ENTITY_UPDATE_FLAG_COOLDOWN;
          new_e->cooldown_count = ENTITY_COOLDOWN_TIME_ICE_CUBE;

          /* if the player was frozen, update G_player accordingly  */
          if (e == G_player)
          {
            G_player = new_e;
          }

          /* if a warp caster is frozen, nullify cast warps */
          if (ENTITY_TYPE_IS_WARP_CASTER(e->type))
          {
            pair_trees_and_lists_remove_all_cast_warps_by_caster(e);
          }

          /* if venusian was frozen, set roots */
          if (e->type == ENTITY_TYPE_VENUSIAN)
          {
            logic_set_venusian_roots(e);
          }

          collide_grid_remove_entity(e);
          world_despawn_entity(e);

          /* check if this entity was frozen over water */
          /* or in another problematic location         */
          logic_check_if_over_water(new_e);

          if (!(new_e->update_flags & ENTITY_UPDATE_FLAG_FELL_INTO_WATER))
          {
            logic_check_post_freeze_location(new_e);

            if (!(new_e->collision_flags & ENTITY_COLLISION_FLAG_DESTROYED))
            {
              logic_press_switches(new_e);
              logic_check_if_over_conveyer(new_e);
            }
          }
        }

        e->collision_flags &= ~ENTITY_COLLISION_FLAG_ICE;
      }
      /* other transformations */
      else if (e->update_flags & ENTITY_UPDATE_FLAG_TRANSFORMING)
      {
        /* portcullis, floor spikes, bridges */
        if ((e->type == ENTITY_TYPE_PORTCULLIS_CLOSED)      ||
            ENTITY_TYPE_IS_FLOOR_SPIKE_DOWN(e->type)        ||
            ENTITY_TYPE_IS_FLOOR_SPIKE_UP(e->type)          ||
            ENTITY_TYPE_IS_WOOD_OR_CRACKED_BRIDGE(e->type))
        {
          if (e->type == ENTITY_TYPE_PORTCULLIS_CLOSED)
            new_entity_type = ENTITY_TYPE_PORTCULLIS_OPEN;
          else if (e->type == ENTITY_TYPE_FLOOR_SPIKE_DOWN_WHITE)
            new_entity_type = ENTITY_TYPE_FLOOR_SPIKE_UP_WHITE;
          else if (e->type == ENTITY_TYPE_FLOOR_SPIKE_DOWN_CYAN)
            new_entity_type = ENTITY_TYPE_FLOOR_SPIKE_UP_CYAN;
          else if (e->type == ENTITY_TYPE_FLOOR_SPIKE_DOWN_MAGENTA)
            new_entity_type = ENTITY_TYPE_FLOOR_SPIKE_UP_MAGENTA;
          else if (e->type == ENTITY_TYPE_FLOOR_SPIKE_UP_WHITE)
            new_entity_type = ENTITY_TYPE_FLOOR_SPIKE_DOWN_WHITE;
          else if (e->type == ENTITY_TYPE_FLOOR_SPIKE_UP_CYAN)
            new_entity_type = ENTITY_TYPE_FLOOR_SPIKE_DOWN_CYAN;
          else if (e->type == ENTITY_TYPE_FLOOR_SPIKE_UP_MAGENTA)
            new_entity_type = ENTITY_TYPE_FLOOR_SPIKE_DOWN_MAGENTA;
          else if (e->type == ENTITY_TYPE_BRIDGE_WOOD_VERTICAL)
            new_entity_type = ENTITY_TYPE_BRIDGE_CRACKED_VERTICAL;
          else if (e->type == ENTITY_TYPE_BRIDGE_WOOD_HORIZONTAL)
            new_entity_type = ENTITY_TYPE_BRIDGE_CRACKED_HORIZONTAL;
          else
            new_entity_type = ENTITY_TYPE_NONE;

          if (new_entity_type != ENTITY_TYPE_NONE)
          {
            if (ENTITY_TYPE_IS_FLOOR_SPIKE_DOWN(e->type))
              doremi_play_sfx(SFX_INDEX_SPIKE_RAISE);
            else if (ENTITY_TYPE_IS_FLOOR_SPIKE_UP(e->type))
              doremi_play_sfx(SFX_INDEX_SPIKE_LOWER);
            else if (new_entity_type == ENTITY_TYPE_BRIDGE_CRACKED_VERTICAL)
              doremi_play_sfx(SFX_INDEX_BRIDGE_CRACK);
            else if (new_entity_type == ENTITY_TYPE_BRIDGE_CRACKED_HORIZONTAL)
              doremi_play_sfx(SFX_INDEX_BRIDGE_CRACK);

            new_e = world_spawn_entity( new_entity_type, 
                                        e->pos_x, e->pos_y);
            collide_grid_add_entity(new_e);

            collide_grid_remove_entity(e);
            world_despawn_entity(e);
          }
        }
        /* dice vanishing / solidifying */
        else if ( ENTITY_TYPE_IS_SOLID_DIE(e->type)               ||
                  ENTITY_TYPE_IS_SOLID_DIE_SUBMERGED(e->type)     ||
                  ENTITY_TYPE_IS_VANISHED_DIE(e->type)            ||
                  ENTITY_TYPE_IS_VANISHED_DIE_SUBMERGED(e->type))
        {
          if (e->type == ENTITY_TYPE_DIE_SOLID_1)
            new_entity_type = ENTITY_TYPE_DIE_VANISHED_1;
          else if (e->type == ENTITY_TYPE_DIE_SOLID_2)
            new_entity_type = ENTITY_TYPE_DIE_VANISHED_2;
          else if (e->type == ENTITY_TYPE_DIE_SOLID_3)
            new_entity_type = ENTITY_TYPE_DIE_VANISHED_3;
          else if (e->type == ENTITY_TYPE_DIE_SOLID_4)
            new_entity_type = ENTITY_TYPE_DIE_VANISHED_4;
          else if (e->type == ENTITY_TYPE_DIE_SOLID_5)
            new_entity_type = ENTITY_TYPE_DIE_VANISHED_5;
          else if (e->type == ENTITY_TYPE_DIE_SOLID_6)
            new_entity_type = ENTITY_TYPE_DIE_VANISHED_6;
          else if (e->type == ENTITY_TYPE_DIE_SOLID_1_SUBMERGED)
            new_entity_type = ENTITY_TYPE_DIE_VANISHED_1_SUBMERGED;
          else if (e->type == ENTITY_TYPE_DIE_SOLID_2_SUBMERGED)
            new_entity_type = ENTITY_TYPE_DIE_VANISHED_2_SUBMERGED;
          else if (e->type == ENTITY_TYPE_DIE_SOLID_3_SUBMERGED)
            new_entity_type = ENTITY_TYPE_DIE_VANISHED_3_SUBMERGED;
          else if (e->type == ENTITY_TYPE_DIE_SOLID_4_SUBMERGED)
            new_entity_type = ENTITY_TYPE_DIE_VANISHED_4_SUBMERGED;
          else if (e->type == ENTITY_TYPE_DIE_SOLID_5_SUBMERGED)
            new_entity_type = ENTITY_TYPE_DIE_VANISHED_5_SUBMERGED;
          else if (e->type == ENTITY_TYPE_DIE_SOLID_6_SUBMERGED)
            new_entity_type = ENTITY_TYPE_DIE_VANISHED_6_SUBMERGED;
          else if (e->type == ENTITY_TYPE_DIE_VANISHED_1)
            new_entity_type = ENTITY_TYPE_DIE_SOLID_1;
          else if (e->type == ENTITY_TYPE_DIE_VANISHED_2)
            new_entity_type = ENTITY_TYPE_DIE_SOLID_2;
          else if (e->type == ENTITY_TYPE_DIE_VANISHED_3)
            new_entity_type = ENTITY_TYPE_DIE_SOLID_3;
          else if (e->type == ENTITY_TYPE_DIE_VANISHED_4)
            new_entity_type = ENTITY_TYPE_DIE_SOLID_4;
          else if (e->type == ENTITY_TYPE_DIE_VANISHED_5)
            new_entity_type = ENTITY_TYPE_DIE_SOLID_5;
          else if (e->type == ENTITY_TYPE_DIE_VANISHED_6)
            new_entity_type = ENTITY_TYPE_DIE_SOLID_6;
          else if (e->type == ENTITY_TYPE_DIE_VANISHED_1_SUBMERGED)
            new_entity_type = ENTITY_TYPE_DIE_SOLID_1_SUBMERGED;
          else if (e->type == ENTITY_TYPE_DIE_VANISHED_2_SUBMERGED)
            new_entity_type = ENTITY_TYPE_DIE_SOLID_2_SUBMERGED;
          else if (e->type == ENTITY_TYPE_DIE_VANISHED_3_SUBMERGED)
            new_entity_type = ENTITY_TYPE_DIE_SOLID_3_SUBMERGED;
          else if (e->type == ENTITY_TYPE_DIE_VANISHED_4_SUBMERGED)
            new_entity_type = ENTITY_TYPE_DIE_SOLID_4_SUBMERGED;
          else if (e->type == ENTITY_TYPE_DIE_VANISHED_5_SUBMERGED)
            new_entity_type = ENTITY_TYPE_DIE_SOLID_5_SUBMERGED;
          else if (e->type == ENTITY_TYPE_DIE_VANISHED_6_SUBMERGED)
            new_entity_type = ENTITY_TYPE_DIE_SOLID_6_SUBMERGED;
          else
            new_entity_type = ENTITY_TYPE_NONE;

          if (new_entity_type != ENTITY_TYPE_NONE)
          {
            if (ENTITY_TYPE_IS_VANISHED_DIE(e->type) ||
                ENTITY_TYPE_IS_VANISHED_DIE_SUBMERGED(e->type))
            {
              doremi_play_sfx(SFX_INDEX_DICE_APPEAR);
            }

            new_e = world_spawn_entity( new_entity_type, 
                                        e->pos_x, e->pos_y);
            collide_grid_add_entity(new_e);

            /* submerged solid die vanishing spawns water tiles */
            if (ENTITY_TYPE_IS_SOLID_DIE_SUBMERGED(e->type))
            {
              new_e = world_spawn_entity( ENTITY_TYPE_WATER, 
                                          e->pos_x - 8, e->pos_y - 8);
              collide_grid_add_entity(new_e);
              new_e->frame_count = water_frame_count;

              new_e = world_spawn_entity( ENTITY_TYPE_WATER, 
                                          e->pos_x + 8, e->pos_y - 8);
              collide_grid_add_entity(new_e);
              new_e->frame_count = water_frame_count;

              new_e = world_spawn_entity( ENTITY_TYPE_WATER, 
                                          e->pos_x - 8, e->pos_y + 8);
              collide_grid_add_entity(new_e);
              new_e->frame_count = water_frame_count;

              new_e = world_spawn_entity( ENTITY_TYPE_WATER, 
                                          e->pos_x + 8, e->pos_y + 8);
              collide_grid_add_entity(new_e);
              new_e->frame_count = water_frame_count;
            }

            collide_grid_remove_entity(e);
            world_despawn_entity(e);

            /* check if this die was solidified over water  */
            /* or on top of a switch                        */
            if (ENTITY_TYPE_IS_SOLID_DIE(new_entity_type))
            {
              logic_check_if_over_water(new_e);

              if (!(new_e->update_flags & ENTITY_UPDATE_FLAG_FELL_INTO_WATER))
              {
                logic_press_switches(new_e);
                logic_check_if_over_conveyer(new_e);
              }
            }
          }
        }
        /* candles lighting / unlighting */
        else if ( (e->type == ENTITY_TYPE_CANDLE_UNLIT) ||
                  (e->type == ENTITY_TYPE_CANDLE_LIT))
        {
          if (e->type == ENTITY_TYPE_CANDLE_UNLIT)
            new_entity_type = ENTITY_TYPE_CANDLE_LIT;
          else if (e->type == ENTITY_TYPE_CANDLE_LIT)
            new_entity_type = ENTITY_TYPE_CANDLE_UNLIT;
          else
            new_entity_type = ENTITY_TYPE_NONE;

          if (new_entity_type != ENTITY_TYPE_NONE)
          {
            if (e->type == ENTITY_TYPE_CANDLE_UNLIT)
              doremi_play_sfx(SFX_INDEX_CANDLE_LIGHT);

            new_e = world_spawn_entity( new_entity_type, 
                                        e->pos_x, e->pos_y);

            /* if candle was moving, jump to end of that movement */
            if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
            {
              new_e->pos_x += e->vel_x * e->move_count;
              new_e->pos_y += e->vel_y * e->move_count;
            }

            /* if candle was moving into water, jump additional amount */
            if (e->update_flags & ENTITY_UPDATE_FLAG_MOVING_INTO_WATER)
            {
              if (e->vel_x > 0)
                new_e->pos_x += 16;
              else if (e->vel_x < 0)
                new_e->pos_x -= 16;

              if (e->vel_y > 0)
                new_e->pos_y += 16;
              else if (e->vel_y < 0)
                new_e->pos_y -= 16;
            }

            animation_setup(new_e);
            collide_grid_add_entity(new_e);

            collide_grid_remove_entity(e);
            world_despawn_entity(e);

            /* check for flying entities above a newly lit candle */
            if (new_entity_type == ENTITY_TYPE_CANDLE_LIT)
              logic_check_lit_candle(new_e);

            /* check if candle is over water */
            logic_check_if_over_water(new_e);

            if (!(new_e->update_flags & ENTITY_UPDATE_FLAG_FELL_INTO_WATER))
            {
              logic_press_switches(new_e);
              logic_check_if_over_conveyer(new_e);
            }
          }
        }
        /* ice cubes thawing */
        else if (ENTITY_TYPE_IS_ICE_CUBE(e->type))
        {
          /* determine original entity type */
          if (e->type == ENTITY_TYPE_ICE_CUBE_PUMPKIN)
          {
            new_entity_type = ENTITY_TYPE_PUMPKIN;
          }
          else if ( (e->type == ENTITY_TYPE_ICE_CUBE_GHOST_RIGHT) ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_GHOST_UP)    ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_GHOST_LEFT)  ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_GHOST_DOWN))
          {
            new_entity_type = ENTITY_TYPE_GHOST;
          }
          else if ( (e->type == ENTITY_TYPE_ICE_CUBE_MASK_HORIZONTAL_RIGHT) ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_MASK_HORIZONTAL_LEFT))
          {
            new_entity_type = ENTITY_TYPE_MASK_HORIZONTAL;
          }
          else if ( (e->type == ENTITY_TYPE_ICE_CUBE_MASK_VERTICAL_UP)    ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_MASK_VERTICAL_DOWN))
          {
            new_entity_type = ENTITY_TYPE_MASK_VERTICAL;
          }
          else if ( (e->type == ENTITY_TYPE_ICE_CUBE_SNAKE_RIGHT) ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_SNAKE_UP)    ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_SNAKE_LEFT)  ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_SNAKE_DOWN))
          {
            new_entity_type = ENTITY_TYPE_SNAKE;
          }
          else if ( (e->type == ENTITY_TYPE_ICE_CUBE_DOUBLE_VAMPIRE_RIGHT)  ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_DOUBLE_VAMPIRE_UP)     ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_DOUBLE_VAMPIRE_LEFT)   ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_DOUBLE_VAMPIRE_DOWN))
          {
            new_entity_type = ENTITY_TYPE_DOUBLE_VAMPIRE;
          }
          else if ( (e->type == ENTITY_TYPE_ICE_CUBE_DOUBLE_BAT_RIGHT)  ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_DOUBLE_BAT_UP)     ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_DOUBLE_BAT_LEFT)   ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_DOUBLE_BAT_DOWN))
          {
            new_entity_type = ENTITY_TYPE_DOUBLE_BAT;
          }
          else if ( (e->type == ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_VAMPIRE_RIGHT)  ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_VAMPIRE_UP)     ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_VAMPIRE_LEFT)   ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_VAMPIRE_DOWN))
          {
            new_entity_type = ENTITY_TYPE_REVERSE_DOUBLE_VAMPIRE;
          }
          else if ( (e->type == ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_BAT_RIGHT)  ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_BAT_UP)     ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_BAT_LEFT)   ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_BAT_DOWN))
          {
            new_entity_type = ENTITY_TYPE_REVERSE_DOUBLE_BAT;
          }
          else if ( (e->type == ENTITY_TYPE_ICE_CUBE_FAERIE_HORIZONTAL_UP)    ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_FAERIE_HORIZONTAL_DOWN))
          {
            new_entity_type = ENTITY_TYPE_FAERIE_HORIZONTAL;
          }
          else if ( (e->type == ENTITY_TYPE_ICE_CUBE_FAERIE_VERTICAL_RIGHT)   ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_FAERIE_VERTICAL_LEFT))
          {
            new_entity_type = ENTITY_TYPE_FAERIE_VERTICAL;
          }
          else if (e->type == ENTITY_TYPE_ICE_CUBE_VENUSIAN)
          {
            new_entity_type = ENTITY_TYPE_VENUSIAN;
          }
          else if ( (e->type == ENTITY_TYPE_ICE_CUBE_WITCH_RIGHT) ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_WITCH_UP)    ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_WITCH_LEFT)  ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_WITCH_DOWN))
          {
            new_entity_type = ENTITY_TYPE_WITCH;
          }
          else if ( (e->type == ENTITY_TYPE_ICE_CUBE_SORCERESS_RIGHT) ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_SORCERESS_UP)    ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_SORCERESS_LEFT)  ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_SORCERESS_DOWN))
          {
            new_entity_type = ENTITY_TYPE_SORCERESS;
          }
          else if ( (e->type == ENTITY_TYPE_ICE_CUBE_FROG_RIGHT)  ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_FROG_UP)     ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_FROG_LEFT)   ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_FROG_DOWN))
          {
            new_entity_type = ENTITY_TYPE_FROG;
          }
          else if ( (e->type == ENTITY_TYPE_ICE_CUBE_IMP_LT_RIGHT)  ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_IMP_LT_UP)     ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_IMP_LT_LEFT)   ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_IMP_LT_DOWN))
          {
            new_entity_type = ENTITY_TYPE_IMP_LT;
          }
          else if ( (e->type == ENTITY_TYPE_ICE_CUBE_IMP_RT_RIGHT)  ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_IMP_RT_UP)     ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_IMP_RT_LEFT)   ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_IMP_RT_DOWN))
          {
            new_entity_type = ENTITY_TYPE_IMP_RT;
          }
          else if ( (e->type == ENTITY_TYPE_ICE_CUBE_LIL_BOT_RIGHT) ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_LIL_BOT_UP)    ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_LIL_BOT_LEFT)  ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_LIL_BOT_DOWN))
          {
            new_entity_type = ENTITY_TYPE_LIL_BOT;
          }
          else if ( (e->type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_LT_STOPPED) ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_LT_RIGHT)   ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_LT_UP)      ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_LT_LEFT)    ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_LT_DOWN))
          {
            new_entity_type = ENTITY_TYPE_JIANGSHI_LT;
          }
          else if ( (e->type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_RT_STOPPED) ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_RT_RIGHT)   ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_RT_UP)      ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_RT_LEFT)    ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_RT_DOWN))
          {
            new_entity_type = ENTITY_TYPE_JIANGSHI_RT;
          }
          else if (e->type == ENTITY_TYPE_ICE_CUBE_MUMMY_LT)
          {
            new_entity_type = ENTITY_TYPE_MUMMY_LT;
          }
          else if (e->type == ENTITY_TYPE_ICE_CUBE_MUMMY_RT)
          {
            new_entity_type = ENTITY_TYPE_MUMMY_RT;
          }
          else if ( (e->type == ENTITY_TYPE_ICE_CUBE_PLAYER_VAMPIRE_RIGHT)  ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_PLAYER_VAMPIRE_UP)     ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_PLAYER_VAMPIRE_LEFT)   ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_PLAYER_VAMPIRE_DOWN))
          {
            new_entity_type = ENTITY_TYPE_PLAYER_VAMPIRE;
          }
          else if ( (e->type == ENTITY_TYPE_ICE_CUBE_PLAYER_BAT_RIGHT)  ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_PLAYER_BAT_UP)     ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_PLAYER_BAT_LEFT)   ||
                    (e->type == ENTITY_TYPE_ICE_CUBE_PLAYER_BAT_DOWN))
          {
            new_entity_type = ENTITY_TYPE_PLAYER_BAT;
          }
          else
            new_entity_type = ENTITY_TYPE_NONE;

          /* transform back to original entity */
          if (new_entity_type != ENTITY_TYPE_NONE)
          {
            new_e = world_spawn_entity( new_entity_type, 
                                        e->pos_x, e->pos_y);

            /* set facing if necessary */
            if ((e->type == ENTITY_TYPE_ICE_CUBE_GHOST_RIGHT)                   ||
                (e->type == ENTITY_TYPE_ICE_CUBE_SNAKE_RIGHT)                   ||
                (e->type == ENTITY_TYPE_ICE_CUBE_DOUBLE_VAMPIRE_RIGHT)          ||
                (e->type == ENTITY_TYPE_ICE_CUBE_DOUBLE_BAT_RIGHT)              ||
                (e->type == ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_VAMPIRE_RIGHT)  ||
                (e->type == ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_BAT_RIGHT)      ||
                (e->type == ENTITY_TYPE_ICE_CUBE_FAERIE_VERTICAL_RIGHT)         ||
                (e->type == ENTITY_TYPE_ICE_CUBE_WITCH_RIGHT)                   ||
                (e->type == ENTITY_TYPE_ICE_CUBE_SORCERESS_RIGHT)               ||
                (e->type == ENTITY_TYPE_ICE_CUBE_FROG_RIGHT)                    ||
                (e->type == ENTITY_TYPE_ICE_CUBE_IMP_LT_RIGHT)                  ||
                (e->type == ENTITY_TYPE_ICE_CUBE_IMP_RT_RIGHT)                  ||
                (e->type == ENTITY_TYPE_ICE_CUBE_LIL_BOT_RIGHT)                 ||
                (e->type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_LT_RIGHT)             ||
                (e->type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_RT_RIGHT)             ||
                (e->type == ENTITY_TYPE_ICE_CUBE_PLAYER_VAMPIRE_RIGHT)          ||
                (e->type == ENTITY_TYPE_ICE_CUBE_PLAYER_BAT_RIGHT))
            {
              entity_set_facing(new_e, ENTITY_FACING_RIGHT);
            }
            else if ( (e->type == ENTITY_TYPE_ICE_CUBE_GHOST_UP)                    ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_SNAKE_UP)                    ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_DOUBLE_VAMPIRE_UP)           ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_DOUBLE_BAT_UP)               ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_VAMPIRE_UP)   ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_BAT_UP)       ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_FAERIE_HORIZONTAL_UP)        ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_WITCH_UP)                    ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_SORCERESS_UP)                ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_FROG_UP)                     ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_IMP_LT_UP)                   ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_IMP_RT_UP)                   ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_LIL_BOT_UP)                  ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_LT_UP)              ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_RT_UP)              ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_PLAYER_VAMPIRE_UP)           ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_PLAYER_BAT_UP))
            {
              entity_set_facing(new_e, ENTITY_FACING_UP);
            }
            else if ( (e->type == ENTITY_TYPE_ICE_CUBE_GHOST_LEFT)                  ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_SNAKE_LEFT)                  ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_DOUBLE_VAMPIRE_LEFT)         ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_DOUBLE_BAT_LEFT)             ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_VAMPIRE_LEFT) ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_BAT_LEFT)     ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_FAERIE_VERTICAL_LEFT)        ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_WITCH_LEFT)                  ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_SORCERESS_LEFT)              ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_FROG_LEFT)                   ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_IMP_LT_LEFT)                 ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_IMP_RT_LEFT)                 ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_LIL_BOT_LEFT)                ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_LT_LEFT)            ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_RT_LEFT)            ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_PLAYER_VAMPIRE_LEFT)         ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_PLAYER_BAT_LEFT))
            {
              entity_set_facing(new_e, ENTITY_FACING_LEFT);
            }
            else if ( (e->type == ENTITY_TYPE_ICE_CUBE_GHOST_DOWN)                  ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_SNAKE_DOWN)                  ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_DOUBLE_VAMPIRE_DOWN)         ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_DOUBLE_BAT_DOWN)             ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_VAMPIRE_DOWN) ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_BAT_DOWN)     ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_FAERIE_HORIZONTAL_DOWN)      ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_WITCH_DOWN)                  ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_SORCERESS_DOWN)              ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_FROG_DOWN)                   ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_IMP_LT_DOWN)                 ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_IMP_RT_DOWN)                 ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_LIL_BOT_DOWN)                ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_LT_DOWN)            ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_RT_DOWN)            ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_PLAYER_VAMPIRE_DOWN)         ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_PLAYER_BAT_DOWN))
            {
              entity_set_facing(new_e, ENTITY_FACING_DOWN);
            }

            /* awaken ghosts, snakes, imps, witches if necessary */
            if ((new_entity_type == ENTITY_TYPE_GHOST)  ||
                (new_entity_type == ENTITY_TYPE_SNAKE)  ||
                (new_entity_type == ENTITY_TYPE_WITCH)  ||
                (new_entity_type == ENTITY_TYPE_IMP_LT) ||
                (new_entity_type == ENTITY_TYPE_IMP_RT))
            {
              if (G_vials_remaining == 0)
                new_e->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
            }

            /* activate jiangshis if necessary */
            if ((e->type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_LT_STOPPED) ||
                (e->type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_RT_STOPPED))
            {
              new_e->update_flags |= ENTITY_UPDATE_FLAG_ACTIVE;
              animation_setup(new_e);
              new_e->frame_count = 0;
            }
            /* set mummies to disintegrate if necessary */
            else if ( (e->type == ENTITY_TYPE_ICE_CUBE_MUMMY_LT) ||
                      (e->type == ENTITY_TYPE_ICE_CUBE_MUMMY_RT))
            {
              new_e->update_flags |= ENTITY_UPDATE_FLAG_COOLDOWN;
              new_e->cooldown_count = ENTITY_COOLDOWN_TIME_MUMMY;
              animation_setup(new_e);
              doremi_play_sfx(SFX_INDEX_MUMMY_COLLAPSE);
            }
            /* otherwise, setup animations */
            else
            {
              animation_setup(new_e);
            }

            /* sync animation if necessary */
            if (new_entity_type == ENTITY_TYPE_VENUSIAN)
              new_e->frame_count = venusian_frame_count;

            /* add entity to collision grid */
            collide_grid_add_entity(new_e);

            /* if the player (as an ice cube) is thawing, */
            /* update G_player accordingly                */
            if (e == G_player)
            {
              G_player = new_e;
            }

            /* check if entity thawed on a switch or a conveyer belt */
            logic_press_switches(new_e);
            logic_check_if_over_conveyer(new_e);

            /* set mask movement direction if necessary */
            if (e->type == ENTITY_TYPE_ICE_CUBE_MASK_HORIZONTAL_RIGHT)
            {
              new_e->orientation &= ~ENTITY_DIRECTION_MASK;
              new_e->orientation |= ENTITY_DIRECTION_RIGHT;
            }
            else if (e->type == ENTITY_TYPE_ICE_CUBE_MASK_HORIZONTAL_LEFT)
            {
              new_e->orientation &= ~ENTITY_DIRECTION_MASK;
              new_e->orientation |= ENTITY_DIRECTION_LEFT;
            }
            else if (e->type == ENTITY_TYPE_ICE_CUBE_MASK_VERTICAL_UP)
            {
              new_e->orientation &= ~ENTITY_DIRECTION_MASK;
              new_e->orientation |= ENTITY_DIRECTION_UP;
            }
            else if (e->type == ENTITY_TYPE_ICE_CUBE_MASK_VERTICAL_DOWN)
            {
              new_e->orientation &= ~ENTITY_DIRECTION_MASK;
              new_e->orientation |= ENTITY_DIRECTION_DOWN;
            }

            collide_grid_remove_entity(e);
            world_despawn_entity(e);
          }
        }
        /* fire and ice spells */
        else if ( (e->type == ENTITY_TYPE_FIRE_SPELL) ||
                  (e->type == ENTITY_TYPE_ICE_SPELL))
        {
          if (e->type == ENTITY_TYPE_FIRE_SPELL)
            new_entity_type = ENTITY_TYPE_ICE_SPELL;
          else if (e->type == ENTITY_TYPE_ICE_SPELL)
            new_entity_type = ENTITY_TYPE_FIRE_SPELL;
          else
            new_entity_type = ENTITY_TYPE_NONE;

          if (new_entity_type != ENTITY_TYPE_NONE)
          {
            doremi_play_sfx(SFX_INDEX_YIN_YANG_ACTIVATE);

            new_e = world_spawn_entity( new_entity_type, 
                                        e->pos_x, e->pos_y);
            entity_set_facing(new_e, e->orientation & ENTITY_FACING_MASK);
            animation_setup(new_e);
            collide_grid_add_entity(new_e);
            new_e->orientation &= ~ENTITY_DIRECTION_MASK;
            new_e->orientation |= e->orientation & ENTITY_DIRECTION_MASK;

            collide_grid_remove_entity(e);
            world_despawn_entity(e);
          }
        }
        /* player, doubles */
        else if (ENTITY_TYPE_IS_PLAYER_OR_DOUBLE(e->type))
        {
          world_spawn_particles_transform(e);

          if (e->type == ENTITY_TYPE_PLAYER_VAMPIRE)
            new_entity_type = ENTITY_TYPE_PLAYER_BAT;
          else if (e->type == ENTITY_TYPE_PLAYER_BAT)
            new_entity_type = ENTITY_TYPE_PLAYER_VAMPIRE;
          else if (e->type == ENTITY_TYPE_DOUBLE_VAMPIRE)
            new_entity_type = ENTITY_TYPE_DOUBLE_BAT;
          else if (e->type == ENTITY_TYPE_DOUBLE_BAT)
            new_entity_type = ENTITY_TYPE_DOUBLE_VAMPIRE;
          else if (e->type == ENTITY_TYPE_REVERSE_DOUBLE_VAMPIRE)
            new_entity_type = ENTITY_TYPE_REVERSE_DOUBLE_BAT;
          else if (e->type == ENTITY_TYPE_REVERSE_DOUBLE_BAT)
            new_entity_type = ENTITY_TYPE_REVERSE_DOUBLE_VAMPIRE;
          else
            new_entity_type = ENTITY_TYPE_NONE;

          if (new_entity_type != ENTITY_TYPE_NONE)
          {
            if (ENTITY_TYPE_IS_VAMPIRE(e->type))
              doremi_play_sfx(SFX_INDEX_TRANSFORM_TO_BAT);
            else if (ENTITY_TYPE_IS_BAT(e->type))
              doremi_play_sfx(SFX_INDEX_TRANSFORM_TO_VAMPIRE);

            new_e = world_spawn_entity(new_entity_type, e->pos_x, e->pos_y);
            entity_set_facing(new_e, e->orientation & ENTITY_FACING_MASK);
            animation_setup(new_e);
            collide_grid_add_entity(new_e);

            if (G_player == e)
              G_player = new_e;

            pair_trees_and_lists_update_cast_warps(e, new_e);

            if ((new_e->type == ENTITY_TYPE_PLAYER_VAMPIRE)         ||
                (new_e->type == ENTITY_TYPE_DOUBLE_VAMPIRE)         ||
                (new_e->type == ENTITY_TYPE_REVERSE_DOUBLE_VAMPIRE))
            {
              logic_set_floor_triggers(new_e);
              logic_press_switches(new_e);
              logic_check_if_over_conveyer(new_e);
            }

            collide_grid_remove_entity(e);
            world_despawn_entity(e);
          }
        }
      }

      e = next_e;
    }
  }

  /* set spells to move */
  e = G_entity_active_list_head[CATEGORY_INDEX_SPELLS];

  while (e != NULL)
  {
    if ((!(e->action_flags & ENTITY_ACTION_FLAG_MOVING)) &&
        (!(e->update_flags & ENTITY_UPDATE_FLAG_STOPPED_MOVEMENT)))
    {
      logic_attempt_move(e, e->orientation & ENTITY_DIRECTION_MASK);
    }

    e = e->next;
  }

  /* check damage for explosions spawned this frame */
  e = G_entity_active_list_head[CATEGORY_INDEX_EXPLOSIONS];

  while (e != NULL)
  {
    if (e->cooldown_count == ENTITY_COOLDOWN_TIME_EXPLOSION)
    {
      logic_check_damage_on_spawn(e);
    }

    e = e->next;
  }

  return 0;
}

/*******************************************************************************
** logic_setup_level()
*******************************************************************************/
short int logic_setup_level()
{
  entity* e;

  /* check if level loaded with no blood or bat vials */
  if (G_vials_remaining == 0)
  {
    logic_all_vials_collected();
  }

  /* check if mahjong tile spawned next to a matching tile */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_PUSHABLE_OBJECTS];
        e != NULL;
        e = e->next)
  {
    if (ENTITY_TYPE_IS_MAHJONG_TILE(e->type))
      logic_check_if_touching_mahjong_tile(e);
  }

  /* set initial facing for laser guns */
  if (G_player != NULL)
  {
    for ( e = G_entity_active_list_head[CATEGORY_INDEX_LASER_GUNS];
          e != NULL;
          e = e->next)
    {
      if ((G_player->pos_x > e->pos_x) && (G_player->pos_y == e->pos_y))
      {
        entity_set_facing(e, ENTITY_FACING_RIGHT);
      }
      else if ((G_player->pos_x > e->pos_x) && (G_player->pos_y < e->pos_y))
      {
        if (G_player->pos_x - e->pos_x <= e->pos_y - G_player->pos_y)
          entity_set_facing(e, ENTITY_FACING_UP);
        else
          entity_set_facing(e, ENTITY_FACING_RIGHT);
      }
      else if ((G_player->pos_x == e->pos_x) && (G_player->pos_y < e->pos_y))
      {
        entity_set_facing(e, ENTITY_FACING_UP);
      }
      else if ((G_player->pos_x < e->pos_x) && (G_player->pos_y < e->pos_y))
      {
        if (e->pos_x - G_player->pos_x <= e->pos_y - G_player->pos_y)
          entity_set_facing(e, ENTITY_FACING_UP);
        else
          entity_set_facing(e, ENTITY_FACING_LEFT);
      }
      else if ((G_player->pos_x < e->pos_x) && (G_player->pos_y == e->pos_y))
      {
        entity_set_facing(e, ENTITY_FACING_LEFT);
      }
      else if ((G_player->pos_x < e->pos_x) && (G_player->pos_y > e->pos_y))
      {
        if (e->pos_x - G_player->pos_x <= G_player->pos_y - e->pos_y)
          entity_set_facing(e, ENTITY_FACING_DOWN);
        else
          entity_set_facing(e, ENTITY_FACING_LEFT);
      }
      else if ((G_player->pos_x == e->pos_x) && (G_player->pos_y > e->pos_y))
      {
        entity_set_facing(e, ENTITY_FACING_DOWN);
      }
      else if ((G_player->pos_x > e->pos_x) && (G_player->pos_y > e->pos_y))
      {
        if (G_player->pos_x - e->pos_x <= G_player->pos_y - e->pos_y)
          entity_set_facing(e, ENTITY_FACING_DOWN);
        else
          entity_set_facing(e, ENTITY_FACING_RIGHT);
      }

      animation_setup(e);
      e->frame_count = 0;
    }
  }

  return 0;
}

/*******************************************************************************
** logic_movement_conclusions()
*******************************************************************************/
short int logic_movement_conclusions()
{
  int     i;
  entity* e;

  for (i = 0; i < CATEGORY_NUM_INDICES; i++)
  {
    if (!(CATEGORY_INDEX_CAN_MOVE(i)))
      continue;

    for ( e = G_entity_active_list_head[i];
          e != NULL;
          e = e->next)
    {
      if (e->update_flags & ENTITY_UPDATE_FLAG_STOPPED_MOVEMENT)
      {
        /* if this is the player, see if open portcullis reached */
        if ((e->type == ENTITY_TYPE_PLAYER_VAMPIRE) || 
            (e->type == ENTITY_TYPE_PLAYER_BAT))
        {
          logic_check_if_over_portcullis(e);
        }

        /* see if this entity is falling into water */
        logic_check_if_over_water(e);

        if (e->update_flags & ENTITY_UPDATE_FLAG_FELL_INTO_WATER)
          continue;

        /* see if this entity is slipping on ice */
        logic_check_if_over_ice(e);

        /* if this is the player, collect pickups */
        if (e->type == ENTITY_TYPE_PLAYER_VAMPIRE)
          logic_collect_pickups(e);

        /* try to set off any floor triggers or switches */
        logic_set_floor_triggers(e);
        logic_press_switches(e);

        /* clear pushing / being pushed flags */
        if (e->action_flags & ENTITY_ACTION_FLAG_PUSHING)
          e->action_flags &= ~ENTITY_ACTION_FLAG_PUSHING;

        if (e->action_flags & ENTITY_ACTION_FLAG_BEING_PUSHED)
          e->action_flags &= ~ENTITY_ACTION_FLAG_BEING_PUSHED;

        /* if entity has moved halfway into the water, it goes all the way in */
        if (e->update_flags & ENTITY_UPDATE_FLAG_MOVING_INTO_WATER)
        {
          collide_grid_remove_entity(e);
          e->update_flags &= ~ENTITY_UPDATE_FLAG_MOVING_INTO_WATER;
          collide_grid_add_entity(e);
          e->update_flags |= ENTITY_UPDATE_FLAG_MOVING_INTO_WATER;
          logic_attempt_move(e, e->orientation & ENTITY_DIRECTION_MASK);
        }

        /* if entity is slipping, continue its move */
        if (e->action_flags & ENTITY_ACTION_FLAG_SLIPPING)
        {
          logic_attempt_move(e, e->orientation & ENTITY_DIRECTION_MASK);

          if (!(e->action_flags & ENTITY_ACTION_FLAG_MOVING))
          {
            e->action_flags &= ~ENTITY_ACTION_FLAG_SLIPPING;
            e->animation_flags &= ~ENTITY_ANIMATION_FLAG_PAUSED;
          }
          else
            e->animation_flags |= ENTITY_ANIMATION_FLAG_PAUSED;
        }
        else
          e->animation_flags &= ~ENTITY_ANIMATION_FLAG_PAUSED;

        /* clear conveyance flag to handle case of player bat */
        /* being conveyed by two frogs at once                */
        if (e->action_flags & ENTITY_ACTION_FLAG_BEING_CONVEYED)
          e->action_flags &= ~ENTITY_ACTION_FLAG_BEING_CONVEYED;

        /* see if this entity is over a conveyer belt */
        logic_check_if_over_conveyer(e);

        /* handle rolling (eight balls) */
        if (e->special_flags & ENTITY_SPECIAL_FLAG_ROLLING)
        {
          /* set facing based on direction */
          if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_RIGHT))
            entity_set_facing(e, ENTITY_FACING_RIGHT);
          else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_UP))
            entity_set_facing(e, ENTITY_FACING_UP);
          else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_LEFT))
            entity_set_facing(e, ENTITY_FACING_LEFT);
          else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_DOWN))
            entity_set_facing(e, ENTITY_FACING_DOWN);

          animation_setup(e);

          /* attempt roll */
          logic_attempt_move(e, e->orientation & ENTITY_DIRECTION_MASK);

          if (!(e->action_flags & ENTITY_ACTION_FLAG_MOVING))
          {
            e->special_flags &= ~ENTITY_SPECIAL_FLAG_ROLLING;
            animation_setup(e);
          }
        }

        /* if this is a spell, continue its movement if     */
        /* it is not transforming (fire <-> ice) this frame */
        if (ENTITY_TYPE_IS_SPELL(e->type))
        {
          if ((e->type == ENTITY_TYPE_FIRE_SPELL) ||
              (e->type == ENTITY_TYPE_ICE_SPELL))
          {
            logic_check_if_over_yin_yang(e);
          }

          if (!(e->update_flags & ENTITY_UPDATE_FLAG_TRANSFORMING))
            logic_attempt_move(e, e->orientation & ENTITY_DIRECTION_MASK);
        }

        /* check if flying entity is over a lit candle */
        if (ENTITY_TYPE_IS_FLYING(e->type))
          logic_check_if_over_candle(e);

        /* check if lit candle is under a flying entity */
        if (e->type == ENTITY_TYPE_CANDLE_LIT)
          logic_check_lit_candle(e);

        /* check if bat is over a joker card */
        if (ENTITY_TYPE_IS_BAT(e->type))
          logic_check_if_over_joker_card(e);

        /* check if mahjong tile is touching another mahjong tile */
        if (ENTITY_TYPE_IS_MAHJONG_TILE(e->type))
          logic_check_if_touching_mahjong_tile(e);

        /* finished processing this entity */
        e->update_flags &= ~ENTITY_UPDATE_FLAG_STOPPED_MOVEMENT;
      }
    }
  }

  return 0;
}

/*******************************************************************************
** logic_process_reflections()
*******************************************************************************/
short int logic_process_reflections()
{
  entity* e;

  /* cycle over spells */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_SPELLS];
        e != NULL;
        e = e->next)
  {
    /* check if spell is reflecting */
    if ((e->special_flags & ENTITY_SPECIAL_FLAG_REFLECT_REVERSE) ||
        (e->special_flags & ENTITY_SPECIAL_FLAG_REFLECT_BANK))
    {
      doremi_play_sfx(SFX_INDEX_REFLECT);

      collide_grid_remove_entity(e);

      /* if spell was moving, finish move */
      if (e->action_flags & ENTITY_ACTION_FLAG_MOVING)
      {
        e->pos_x += e->vel_x * e->move_count;
        e->pos_y += e->vel_y * e->move_count;
        e->move_count = 0;
        e->vel_x = 0;
        e->vel_y = 0;
        e->action_flags &= ~ENTITY_ACTION_FLAG_MOVING;

        collide_grid_add_entity(e);
        logic_check_if_over_yin_yang(e);
        collide_grid_remove_entity(e);
      }

      /* set initial position based on overlap */
      if (e->special_flags & ENTITY_SPECIAL_FLAG_OVERLAP)
      {
        if (e->action_flags & ENTITY_ACTION_FLAG_MODE)
        {
          if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_RIGHT))
            e->pos_x -= 32;
          else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_UP))
            e->pos_y += 32;
          else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_LEFT))
            e->pos_x += 32;
          else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_DOWN))
            e->pos_y -= 32;

          e->action_flags &= ~ENTITY_ACTION_FLAG_MODE;
        }
        else
        {
          if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_RIGHT))
            e->pos_x -= 16;
          else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_UP))
            e->pos_y += 16;
          else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_LEFT))
            e->pos_x += 16;
          else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_DOWN))
            e->pos_y -= 16;
        }

        e->special_flags &= ~ENTITY_SPECIAL_FLAG_OVERLAP;
      }

      /* clockwise bank shot */
      if ((e->special_flags & ENTITY_SPECIAL_FLAG_REFLECT_REVERSE)  &&
          (e->special_flags & ENTITY_SPECIAL_FLAG_REFLECT_BANK))
      {
        /* set new position */
        if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_RIGHT))
        {
          e->pos_x += 32;
          e->pos_y -= 32;
          entity_set_facing(e, ENTITY_FACING_UP);
          animation_setup(e);
          e->orientation &= ~ENTITY_DIRECTION_MASK;
          e->orientation |= ENTITY_DIRECTION_UP;
        }
        else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_UP))
        {
          e->pos_x -= 32;
          e->pos_y -= 32;
          entity_set_facing(e, ENTITY_FACING_LEFT);
          animation_setup(e);
          e->orientation &= ~ENTITY_DIRECTION_MASK;
          e->orientation |= ENTITY_DIRECTION_LEFT;
        }
        else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_LEFT))
        {
          e->pos_x -= 32;
          e->pos_y += 32;
          entity_set_facing(e, ENTITY_FACING_DOWN);
          animation_setup(e);
          e->orientation &= ~ENTITY_DIRECTION_MASK;
          e->orientation |= ENTITY_DIRECTION_DOWN;
        }
        else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_DOWN))
        {
          e->pos_x += 32;
          e->pos_y += 32;
          entity_set_facing(e, ENTITY_FACING_RIGHT);
          animation_setup(e);
          e->orientation &= ~ENTITY_DIRECTION_MASK;
          e->orientation |= ENTITY_DIRECTION_RIGHT;
        }
      }
      /* counterclockwise bank shot */
      else if (e->special_flags & ENTITY_SPECIAL_FLAG_REFLECT_BANK)
      {
        /* set new position */
        if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_RIGHT))
        {
          e->pos_x += 32;
          e->pos_y += 32;
          entity_set_facing(e, ENTITY_FACING_DOWN);
          animation_setup(e);
          e->orientation &= ~ENTITY_DIRECTION_MASK;
          e->orientation |= ENTITY_DIRECTION_DOWN;
        }
        else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_UP))
        {
          e->pos_x += 32;
          e->pos_y -= 32;
          entity_set_facing(e, ENTITY_FACING_RIGHT);
          animation_setup(e);
          e->orientation &= ~ENTITY_DIRECTION_MASK;
          e->orientation |= ENTITY_DIRECTION_RIGHT;
        }
        else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_LEFT))
        {
          e->pos_x -= 32;
          e->pos_y -= 32;
          entity_set_facing(e, ENTITY_FACING_UP);
          animation_setup(e);
          e->orientation &= ~ENTITY_DIRECTION_MASK;
          e->orientation |= ENTITY_DIRECTION_UP;
        }
        else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_DOWN))
        {
          e->pos_x -= 32;
          e->pos_y += 32;
          entity_set_facing(e, ENTITY_FACING_LEFT);
          animation_setup(e);
          e->orientation &= ~ENTITY_DIRECTION_MASK;
          e->orientation |= ENTITY_DIRECTION_LEFT;
        }
      }
      /* reversal */
      else if (e->special_flags & ENTITY_SPECIAL_FLAG_REFLECT_REVERSE)
      {
        /* change direction */
        if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_RIGHT))
        {
          entity_set_facing(e, ENTITY_FACING_LEFT);
          animation_setup(e);
          e->orientation &= ~ENTITY_DIRECTION_MASK;
          e->orientation |= ENTITY_DIRECTION_LEFT;
        }
        else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_UP))
        {
          entity_set_facing(e, ENTITY_FACING_DOWN);
          animation_setup(e);
          e->orientation &= ~ENTITY_DIRECTION_MASK;
          e->orientation |= ENTITY_DIRECTION_DOWN;
        }
        else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_LEFT))
        {
          entity_set_facing(e, ENTITY_FACING_RIGHT);
          animation_setup(e);
          e->orientation &= ~ENTITY_DIRECTION_MASK;
          e->orientation |= ENTITY_DIRECTION_RIGHT;
        }
        else if (ENTITY_DIRECTION_CHECK(e, ENTITY_DIRECTION_DOWN))
        {
          entity_set_facing(e, ENTITY_FACING_UP);
          animation_setup(e);
          e->orientation &= ~ENTITY_DIRECTION_MASK;
          e->orientation |= ENTITY_DIRECTION_UP;
        }
      }

      collide_grid_add_entity(e);

      /* check if reflected over a yin yang after a bank shot */
      if (e->special_flags & ENTITY_SPECIAL_FLAG_REFLECT_BANK)
      {
        logic_check_if_over_yin_yang(e);

        e->special_flags &= ~ENTITY_SPECIAL_FLAG_REFLECT_REVERSE;
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_REFLECT_BANK;

        logic_check_damage_on_spawn(e);
      }
      /* check if reflected into another reversal after a reversal */
      else
      {
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_REFLECT_REVERSE;
        e->special_flags &= ~ENTITY_SPECIAL_FLAG_REFLECT_BANK;

        logic_check_damage_on_spawn(e);

        if ((e->special_flags & ENTITY_SPECIAL_FLAG_REFLECT_REVERSE) &&
            (!(e->special_flags & ENTITY_SPECIAL_FLAG_REFLECT_BANK)))
        {
          if (e->type == ENTITY_TYPE_WARP_SPELL)
            e->special_flags |= ENTITY_SPECIAL_FLAG_WARP_NULLIFY;

          e->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
        }
      }
    }
  }

  /* set spells to move */
  for ( e = G_entity_active_list_head[CATEGORY_INDEX_SPELLS];
        e != NULL;
        e = e->next)
  {
    /* if spell reflected into another reflecter, */
    /* wait until next frame to update            */
    if ((e->special_flags & ENTITY_SPECIAL_FLAG_REFLECT_REVERSE) ||
        (e->special_flags & ENTITY_SPECIAL_FLAG_REFLECT_BANK))
    {
      continue;
    }

    /* move spell if necessary */
    if ((!(e->action_flags & ENTITY_ACTION_FLAG_MOVING)) &&
        (!(e->update_flags & ENTITY_UPDATE_FLAG_STOPPED_MOVEMENT)))
    {
      logic_attempt_move(e, e->orientation & ENTITY_DIRECTION_MASK);
    }
  }

  return 0;
}

/*******************************************************************************
** logic_process_warps()
*******************************************************************************/
short int logic_process_warps()
{
  entity*     e1;
  entity*     e2;
  pair_node*  current;
  int         tmp_x;
  int         tmp_y;

  current = G_pair_list_head_activated_warps;

  while (current != NULL)
  {
    e1 = current->e1;
    e2 = current->e2;

    doremi_play_sfx(SFX_INDEX_WARP_ACTIVATE);

    /* if venusian is being warped, set roots before warping */
    if (e2->type == ENTITY_TYPE_VENUSIAN)
    {
      logic_set_venusian_roots(e2);
    }

    /* remove entities from collision grid */
    collide_grid_remove_entity(e1);
    collide_grid_remove_entity(e2);

    /* if entity is moving, complete move before warping */
    if (e1->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      e1->pos_x += e1->vel_x * e1->move_count;
      e1->pos_y += e1->vel_y * e1->move_count;
      e1->move_count = 0;
      e1->vel_x = 0;
      e1->vel_y = 0;
    }

    if (e2->action_flags & ENTITY_ACTION_FLAG_MOVING)
    {
      e2->pos_x += e2->vel_x * e2->move_count;
      e2->pos_y += e2->vel_y * e2->move_count;
      e2->move_count = 0;
      e2->vel_x = 0;
      e2->vel_y = 0;
    }

    /* swap entity positions */
    tmp_x = e1->pos_x;
    tmp_y = e1->pos_y;

    e1->pos_x = e2->pos_x;
    e1->pos_y = e2->pos_y;

    e2->pos_x = tmp_x;
    e2->pos_y = tmp_y;

    /* add entities back to collision grid */
    collide_grid_add_entity(e1);
    collide_grid_add_entity(e2);

    /* spawn particles */
    world_spawn_particles_warp_effect(e1, e2);

    /* check if entities warped into damaging situations  */
    /* or otherwise problematic positions                 */
    logic_check_if_over_water(e1);

    if (!(e1->update_flags & ENTITY_UPDATE_FLAG_FELL_INTO_WATER))
    {
      logic_check_post_warp_location(e1);

      /* set floor triggers */
      if (!(e1->collision_flags & ENTITY_COLLISION_FLAG_DESTROYED))
      {
        logic_set_floor_triggers(e1);
        logic_press_switches(e1);
        logic_check_if_over_conveyer(e1);

        if (ENTITY_TYPE_IS_MAHJONG_TILE(e1->type))
          logic_check_if_touching_mahjong_tile(e1);

        /* sorceress changes facing direction after casting successful warp */
        if (e1->type == ENTITY_TYPE_SORCERESS)
        {
          if (ENTITY_FACING_CHECK(e1, ENTITY_FACING_RIGHT))
            entity_set_facing(e1, ENTITY_FACING_LEFT);
          else if (ENTITY_FACING_CHECK(e1, ENTITY_FACING_UP))
            entity_set_facing(e1, ENTITY_FACING_DOWN);
          else if (ENTITY_FACING_CHECK(e1, ENTITY_FACING_LEFT))
            entity_set_facing(e1, ENTITY_FACING_RIGHT);
          else if (ENTITY_FACING_CHECK(e1, ENTITY_FACING_DOWN))
            entity_set_facing(e1, ENTITY_FACING_UP);

          animation_setup(e1);
        }
      }
    }

    logic_check_if_over_water(e2);

    if (!(e2->update_flags & ENTITY_UPDATE_FLAG_FELL_INTO_WATER))
    {
      logic_check_post_warp_location(e2);

      /* set floor triggers */
      if (!(e2->collision_flags & ENTITY_COLLISION_FLAG_DESTROYED))
      {
        logic_set_floor_triggers(e2);
        logic_press_switches(e2);
        logic_check_if_over_conveyer(e2);

        if (ENTITY_TYPE_IS_MAHJONG_TILE(e2->type))
          logic_check_if_touching_mahjong_tile(e2);
      }
    }

    current = current->right;
  }

  /* clear all activated warps, as they have been processed */
  pair_trees_and_lists_clear_activated_warps();

  return 0;
}

/*******************************************************************************
** logic_evil_eye_update()
*******************************************************************************/
short int logic_evil_eye_update()
{
  entity* e;

  /* there should only be one evil eye spell spawned */
  e = G_entity_active_list_head[CATEGORY_INDEX_EVIL_EYES];

  /* make sure there is at least one evil eye */
  if (e == NULL)
  {
    G_game_state_flags &= ~GLOBAL_GAME_STATE_FLAG_EVIL_EYE_CAST;
    return 0;
  }

  /* make sure player is spawned */
  if (G_player == NULL)
  {
    e->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
    G_game_state_flags &= ~GLOBAL_GAME_STATE_FLAG_EVIL_EYE_CAST;
    return 0;
  }

  /* make sure evil eye has velocity set */
  if ((e->vel_x == 0) && (e->vel_y == 0))
  {
    G_player->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
    e->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
    G_game_state_flags &= ~GLOBAL_GAME_STATE_FLAG_EVIL_EYE_CAST;
    return 0;
  }

  /* make sure evil eye is onscreen */
  if ((e->pos_x < 16) || (e->pos_x > 400) ||
      (e->pos_y < 16) || (e->pos_y > 464))
  {
    G_player->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
    e->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
    G_game_state_flags &= ~GLOBAL_GAME_STATE_FLAG_EVIL_EYE_CAST;
    return 0;
  }

  /* update position of evil eye */
  e->pos_x += e->vel_x;
  e->pos_y += e->vel_y;

  /* check if evil eye has reached or is past the player */
  if ((e->pos_x + e->rx - 1 >= G_player->pos_x - G_player->rx) && 
      (ENTITY_FACING_CHECK(e, ENTITY_FACING_RIGHT)))
  {
    G_player->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
    e->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
    G_game_state_flags &= ~GLOBAL_GAME_STATE_FLAG_EVIL_EYE_CAST;
    return 0;
  }
  else if ( (e->pos_y - e->ry <= G_player->pos_y + G_player->ry - 1) && 
            (ENTITY_FACING_CHECK(e, ENTITY_FACING_UP)))
  {
    G_player->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
    e->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
    G_game_state_flags &= ~GLOBAL_GAME_STATE_FLAG_EVIL_EYE_CAST;
    return 0;
  }
  else if ( (e->pos_x - e->rx <= G_player->pos_x + G_player->rx - 1) && 
            (ENTITY_FACING_CHECK(e, ENTITY_FACING_LEFT)))
  {
    G_player->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
    e->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
    G_game_state_flags &= ~GLOBAL_GAME_STATE_FLAG_EVIL_EYE_CAST;
    return 0;
  }
  else if ( (e->pos_y + e->ry - 1 >= G_player->pos_y - G_player->ry) && 
            (ENTITY_FACING_CHECK(e, ENTITY_FACING_DOWN)))
  {
    G_player->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
    e->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
    G_game_state_flags &= ~GLOBAL_GAME_STATE_FLAG_EVIL_EYE_CAST;
    return 0;
  }

  return 0;
}

