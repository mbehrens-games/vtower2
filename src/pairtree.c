/*******************************************************************************
** pairtree.c (entity pair trees and lists)
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "entity.h"
#include "pairtree.h"

#define PAIR_TREE_SET_SPELLBINDER_FLAGS(e1, e2)                                \
  if (((e1->pos_y % 16 == 0) && (e1->pos_y == e2->pos_y) &&                    \
      ENTITY_FACING_CHECK(e2, ENTITY_FACING_RIGHT)) ||                         \
      ((e1->pos_x % 16 == 0) && (e1->pos_x == e2->pos_x) &&                    \
      ENTITY_FACING_CHECK(e2, ENTITY_FACING_UP))    ||                         \
      ((e1->pos_y % 16 == 0) && (e1->pos_y == e2->pos_y) &&                    \
      ENTITY_FACING_CHECK(e2, ENTITY_FACING_LEFT))  ||                         \
      ((e1->pos_x % 16 == 0) && (e1->pos_x == e2->pos_x) &&                    \
      ENTITY_FACING_CHECK(e2, ENTITY_FACING_DOWN)))                            \
  {                                                                            \
    if (!((e1->update_flags & ENTITY_UPDATE_FLAG_TRANSFORMING) &&              \
          (e1->action_flags & ENTITY_ACTION_FLAG_MODE)))                       \
    {                                                                          \
      if (e2->type == ENTITY_TYPE_FIRE_SPELL)                                  \
        e1->collision_flags |= ENTITY_COLLISION_FLAG_FIRE;                     \
      else if (e2->type == ENTITY_TYPE_ICE_SPELL)                              \
        e1->collision_flags |= ENTITY_COLLISION_FLAG_ICE;                      \
      else if (e2->type == ENTITY_TYPE_NEUTRAL_SPELL)                          \
        e1->collision_flags |= ENTITY_COLLISION_FLAG_NEUTRAL;                  \
      else if (e2->type == ENTITY_TYPE_BALLISTA_BOLT)                          \
        e1->collision_flags |= ENTITY_COLLISION_FLAG_BOLT;                     \
    }                                                                          \
                                                                               \
    if (e1->update_flags & ENTITY_UPDATE_FLAG_TRANSFORMING)                    \
    {                                                                          \
      if (!(e1->action_flags & ENTITY_ACTION_FLAG_MODE))                       \
      {                                                                        \
        e1->collision_flags |= ENTITY_COLLISION_FLAG_FIRE;                     \
        e1->collision_flags |= ENTITY_COLLISION_FLAG_ICE;                      \
        e1->collision_flags |= ENTITY_COLLISION_FLAG_NEUTRAL;                  \
        e1->collision_flags |= ENTITY_COLLISION_FLAG_BOLT;                     \
      }                                                                        \
    }                                                                          \
    else if (e1->action_flags & ENTITY_ACTION_FLAG_CASTING)                    \
    {                                                                          \
      e1->collision_flags |= ENTITY_COLLISION_FLAG_FIRE;                       \
      e1->collision_flags |= ENTITY_COLLISION_FLAG_ICE;                        \
      e1->collision_flags |= ENTITY_COLLISION_FLAG_NEUTRAL;                    \
      e1->collision_flags |= ENTITY_COLLISION_FLAG_BOLT;                       \
      e1->update_flags |= ENTITY_UPDATE_FLAG_TRANSFORMING;                     \
      e1->action_flags &= ~ENTITY_ACTION_FLAG_CASTING;                         \
    }                                                                          \
    else if (e1->type == ENTITY_TYPE_SPELLBINDER_EMPTY)                        \
    {                                                                          \
      if (e2->type != ENTITY_TYPE_BALLISTA_BOLT)                               \
        e1->update_flags |= ENTITY_UPDATE_FLAG_TRANSFORMING;                   \
    }                                                                          \
    else                                                                       \
    {                                                                          \
      e1->action_flags |= ENTITY_ACTION_FLAG_CASTING;                          \
      entity_set_facing(e1, e2->orientation & ENTITY_FACING_MASK);             \
    }                                                                          \
  }

#define PAIR_TREE_SET_ELEMENTAL_COLLISION_FLAGS(e1, e2)                        \
  damage_result = e1->damage_affect & e2->damage_attribute;                    \
                                                                               \
  if (damage_result & ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE)                         \
    e2->collision_flags |= ENTITY_COLLISION_FLAG_FIRE;                         \
                                                                               \
  if (damage_result & ENTITY_DAMAGE_FLAG_WEAK_TO_ICE)                          \
    e2->collision_flags |= ENTITY_COLLISION_FLAG_ICE;                          \
                                                                               \
  if (damage_result & ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL)                      \
    e2->collision_flags |= ENTITY_COLLISION_FLAG_NEUTRAL;                      \
                                                                               \
  if (damage_result & ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT)                         \
    e2->collision_flags |= ENTITY_COLLISION_FLAG_BOLT;                         \

#define PAIR_TREE_SET_NONELEMENTAL_COLLISION_FLAGS(e1, e2)                     \
  damage_result = e1->damage_affect & e2->damage_attribute;                    \
                                                                               \
  if (damage_result & ENTITY_DAMAGE_FLAG_SPELL)                                \
    e2->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;                    \
                                                                               \
  if (damage_result & ENTITY_DAMAGE_FLAG_FLOOR_SPIKE)                          \
    e2->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;                    \
                                                                               \
  if (damage_result & ENTITY_DAMAGE_FLAG_FLASK)                                \
  {                                                                            \
    /* if damaged by a floor spike, increment lost hp count */                 \
    if ((e1->type == ENTITY_TYPE_FLOOR_SPIKE_UP_WHITE)    ||                   \
        (e1->type == ENTITY_TYPE_FLOOR_SPIKE_UP_CYAN)     ||                   \
        (e1->type == ENTITY_TYPE_FLOOR_SPIKE_UP_MAGENTA))                      \
    {                                                                          \
      if ((!(e2->collision_flags & ENTITY_COLLISION_FLAG_LOST_1_HP))  &&       \
          (!(e2->collision_flags & ENTITY_COLLISION_FLAG_LOST_2_HP)))          \
      {                                                                        \
        e2->collision_flags |= ENTITY_COLLISION_FLAG_LOST_1_HP;                \
      }                                                                        \
      else if ( (e2->collision_flags & ENTITY_COLLISION_FLAG_LOST_1_HP)     && \
                (!(e2->collision_flags & ENTITY_COLLISION_FLAG_LOST_2_HP)))    \
      {                                                                        \
        e2->collision_flags &= ~ENTITY_COLLISION_FLAG_LOST_1_HP;               \
        e2->collision_flags |= ENTITY_COLLISION_FLAG_LOST_2_HP;                \
      }                                                                        \
      else if ( (!(e2->collision_flags & ENTITY_COLLISION_FLAG_LOST_1_HP))  && \
                (e2->collision_flags & ENTITY_COLLISION_FLAG_LOST_2_HP))       \
      {                                                                        \
        e2->collision_flags |= ENTITY_COLLISION_FLAG_LOST_1_HP;                \
      }                                                                        \
      else if ( (e2->collision_flags & ENTITY_COLLISION_FLAG_LOST_1_HP)     && \
                (e2->collision_flags & ENTITY_COLLISION_FLAG_LOST_2_HP))       \
      {                                                                        \
        e2->collision_flags &= ~ENTITY_COLLISION_FLAG_LOST_1_HP;               \
        e2->collision_flags &= ~ENTITY_COLLISION_FLAG_LOST_2_HP;               \
        e2->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;                \
      }                                                                        \
    }                                                                          \
    /* otherwise, flask is destroyed */                                        \
    else                                                                       \
    {                                                                          \
      e2->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;                  \
    }                                                                          \
  }                                                                            \
                                                                               \
  if (damage_result & ENTITY_DAMAGE_FLAG_EXPLODABLE)                           \
  {                                                                            \
    if (ENTITY_TYPE_IS_BRIDGE(e2->type)     ||                                 \
        ENTITY_TYPE_IS_SUBMERGED(e2->type))                                    \
    {                                                                          \
      e2->special_flags |= ENTITY_SPECIAL_FLAG_AWAITING_DESTROY;               \
    }                                                                          \
    else                                                                       \
    {                                                                          \
      e2->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;                  \
    }                                                                          \
  }

pair_node* G_pair_tree_root_collisions;
pair_node* G_pair_list_head_cast_warps;
pair_node* G_pair_list_head_activated_warps;
pair_node* G_pair_list_head_vacant;

/* stack for non-recursive tree traversal */
static pair_node**  S_stack;
static int          S_stack_size;
static int          S_stack_top;

/*******************************************************************************
** pair_node_init()
*******************************************************************************/
short int pair_node_init(pair_node* node)
{
  if (node == NULL)
    return 1;

  node->e1 = NULL;
  node->e2 = NULL;

  node->left  = NULL;
  node->right = NULL;

  return 0;
}

/*******************************************************************************
** pair_node_create()
*******************************************************************************/
pair_node* pair_node_create()
{
  pair_node* node;

  node = malloc(sizeof(pair_node));
  pair_node_init(node);

  return node;
}

/*******************************************************************************
** pair_node_deinit()
*******************************************************************************/
short int pair_node_deinit(pair_node* node)
{
  if (node == NULL)
    return 1;

  node->e1 = NULL;
  node->e2 = NULL;

  node->left  = NULL;
  node->right = NULL;

  return 0;
}

/*******************************************************************************
** pair_node_destroy()
*******************************************************************************/
short int pair_node_destroy(pair_node* node)
{
  if (node == NULL)
    return 1;

  pair_node_deinit(node);
  free(node);

  return 0;
}

/*******************************************************************************
** pair_tree_destroy()
*******************************************************************************/
short int pair_tree_destroy(pair_node* root)
{
  pair_node* current;
  pair_node* previous;

  if (root == NULL)
    return 1;

  /* setup stack */
  S_stack_top = -1;

  /* push root node onto stack and begin traversing the subtree */
  PAIR_TREE_PUSH_NODE(S_stack, root)
  previous = NULL;
  current = root;

  while (S_stack_top >= 0)
  {
    if (current->left != NULL)
    {
      previous = current;
      current = current->left;
      previous->left = NULL;
      PAIR_TREE_PUSH_NODE(S_stack, current)
    }
    else if (current->right != NULL)
    {
      previous = current;
      current = current->right;
      previous->right = NULL;
      PAIR_TREE_PUSH_NODE(S_stack, current)
    }
    else
    {
      previous = current;
      PAIR_TREE_POP_NODE(S_stack)

      if (S_stack_top >= 0)
        current = S_stack[S_stack_top];
      else
        current = NULL;

      pair_node_destroy(previous);
    }
  }

  return 0;
}

/*******************************************************************************
** pair_list_destroy()
*******************************************************************************/
short int pair_list_destroy(pair_node* head)
{
  pair_node* current;
  pair_node* previous;

  current = head;
  previous = NULL;

  while (current != NULL)
  {
    previous = current;
    current = current->right;
    pair_node_destroy(previous);
  }

  return 0;
}

/*******************************************************************************
** pair_trees_and_lists_init()
*******************************************************************************/
short int pair_trees_and_lists_init()
{
  int         i;
  pair_node*  new_node;

  /* initialize pointers */
  G_pair_tree_root_collisions       = NULL;
  G_pair_list_head_cast_warps       = NULL;
  G_pair_list_head_activated_warps  = NULL;
  G_pair_list_head_vacant           = NULL;

  /* generate initial nodes in vacant tree */
  for (i = 0; i < PAIR_NODES_INITIAL_NUM; i++)
  {
    new_node = pair_node_create();

    if (G_pair_list_head_vacant != NULL)
      new_node->right = G_pair_list_head_vacant;

    G_pair_list_head_vacant = new_node;
  }

  /* initialize stack */
  S_stack = malloc(PAIR_TREE_STACK_INITIAL_SIZE * sizeof(pair_node*));
  S_stack_size = PAIR_TREE_STACK_INITIAL_SIZE;
  S_stack_top = -1;

  return 0;
}

/*******************************************************************************
** pair_trees_and_lists_deinit()
*******************************************************************************/
short int pair_trees_and_lists_deinit()
{
  /* deallocate trees and lists */
  if (G_pair_tree_root_collisions != NULL)
  {
    pair_tree_destroy(G_pair_tree_root_collisions);
    G_pair_tree_root_collisions = NULL;
  }

  if (G_pair_list_head_cast_warps != NULL)
  {
    pair_list_destroy(G_pair_list_head_cast_warps);
    G_pair_list_head_cast_warps = NULL;
  }

  if (G_pair_list_head_activated_warps != NULL)
  {
    pair_list_destroy(G_pair_list_head_activated_warps);
    G_pair_list_head_activated_warps = NULL;
  }

  if (G_pair_list_head_vacant != NULL)
  {
    pair_list_destroy(G_pair_list_head_vacant);
    G_pair_list_head_vacant = NULL;
  }

  /* deallocate stack */
  if (S_stack != NULL)
  {
    free(S_stack);
    S_stack = NULL;
    S_stack_size = 0;
    S_stack_top = -1;
  }

  return 0;
}

/*******************************************************************************
** pair_trees_and_lists_get_new_node()
*******************************************************************************/
pair_node* pair_trees_and_lists_get_new_node()
{
  int         i;
  pair_node*  new_node;

  /* generate additional nodes in vacant list, if necessary */
  if (G_pair_list_head_vacant == NULL)
  {
    for (i = 0; i < PAIR_NODES_INITIAL_NUM; i++)
    {
      new_node = pair_node_create();

      if (G_pair_list_head_vacant != NULL)
        new_node->right = G_pair_list_head_vacant;

      G_pair_list_head_vacant = new_node;
    }
  }

  new_node = G_pair_list_head_vacant;
  G_pair_list_head_vacant = G_pair_list_head_vacant->right;

  new_node->left = NULL;
  new_node->right = NULL;

  return new_node;
}

/*******************************************************************************
** pair_trees_and_lists_add_collision()
*******************************************************************************/
short int pair_trees_and_lists_add_collision(entity* e1, entity* e2)
{
  pair_node*  new_node;
  pair_node*  current;
  pair_node*  previous;
  entity*     e_low;
  entity*     e_high;

  if ((e1 == NULL) || (e2 == NULL))
    return 0;

  /* entity cannot collide with itself */
  if (e1 == e2)
    return 0;

  /* sort ids */
  if (e1->id < e2->id)
  {
    e_low = e1;
    e_high = e2;
  }
  else
  {
    e_low = e2;
    e_high = e1;
  }

  /* if collision tree is empty, make this collision the root */
  if (G_pair_tree_root_collisions == NULL)
  {
    new_node = pair_trees_and_lists_get_new_node();

    if (new_node == NULL)
      return 1;

    new_node->e1 = e_low;
    new_node->e2 = e_high;

    G_pair_tree_root_collisions = new_node;

    return 0;
  }

  /* otherwise, find place to insert pair into the tree */
  previous = NULL;
  current = G_pair_tree_root_collisions;

  while (current != NULL)
  {
    /* if id is less than the current node, go to the left */
    if ((e_low->id < current->e1->id)   ||
        ((e_low->id == current->e1->id) && (e_high->id < current->e2->id)))
    {
      if (current->left != NULL)
      {
        previous = current;
        current = current->left;
      }
      else
      {
        new_node = pair_trees_and_lists_get_new_node();

        if (new_node == NULL)
          return 1;

        new_node->e1 = e_low;
        new_node->e2 = e_high;

        current->left = new_node;

        return 0;
      }
    }
    /* if id is greater than the current node, go to the right */
    else if ( (e_low->id > current->e1->id)   ||
              ((e_low->id == current->e1->id) && (e_high->id > current->e2->id)))
    {
      if (current->right != NULL)
      {
        previous = current;
        current = current->right;
      }
      else
      {
        new_node = pair_trees_and_lists_get_new_node();

        if (new_node == NULL)
          return 1;

        new_node->e1 = e_low;
        new_node->e2 = e_high;

        current->right = new_node;

        return 0;
      }
    }
    /* otherwise, this collision is already in the tree, so return */
    else
    {
      return 0;
    }
  }

  return 0;
}

/*******************************************************************************
** pair_trees_and_lists_process_collisions()
*******************************************************************************/
short int pair_trees_and_lists_process_collisions()
{
  pair_node*    current;
  pair_node*    previous;
  entity*       e1;
  entity*       e2;
  unsigned char damage_result;

  if (G_pair_tree_root_collisions == NULL)
    return 0;

  /* setup stack */
  S_stack_top = -1;

  /* push root node onto stack and begin traversing the subtree */
  PAIR_TREE_PUSH_NODE(S_stack, G_pair_tree_root_collisions)
  previous = NULL;
  current = G_pair_tree_root_collisions;

  while (S_stack_top >= 0)
  {
    if (current->left != NULL)
    {
      previous = current;
      current = current->left;
      previous->left = NULL;
      PAIR_TREE_PUSH_NODE(S_stack, current)
    }
    else if (current->right != NULL)
    {
      previous = current;
      current = current->right;
      previous->right = NULL;
      PAIR_TREE_PUSH_NODE(S_stack, current)
    }
    else
    {
      previous = current;
      PAIR_TREE_POP_NODE(S_stack)

      if (S_stack_top >= 0)
        current = S_stack[S_stack_top];
      else
        current = NULL;

      /* process this node */
      e1 = previous->e1;
      e2 = previous->e2;

      if (e1->type == ENTITY_TYPE_WARP_SPELL)
      {
        if (ENTITY_TYPE_IS_UNWARPABLE(e2->type))
          e1->special_flags |= ENTITY_SPECIAL_FLAG_WARP_NULLIFY;

        pair_trees_and_lists_activate_warp(e1, e2);
        e1->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
      }

      if (e2->type == ENTITY_TYPE_WARP_SPELL)
      {
        if (ENTITY_TYPE_IS_UNWARPABLE(e1->type))
          e2->special_flags |= ENTITY_SPECIAL_FLAG_WARP_NULLIFY;

        pair_trees_and_lists_activate_warp(e2, e1);
        e2->collision_flags |= ENTITY_COLLISION_FLAG_DESTROYED;
      }

      if ((ENTITY_TYPE_IS_SPELLBINDER(e1->type)) &&
          (ENTITY_TYPE_IS_ELEMENTAL_SPELL(e2->type)))
      {
        PAIR_TREE_SET_SPELLBINDER_FLAGS(e1, e2)
      }
      else if ( (ENTITY_TYPE_IS_ELEMENTAL_SPELL(e1->type)) &&
                (ENTITY_TYPE_IS_SPELLBINDER(e2->type)))
      {
        PAIR_TREE_SET_SPELLBINDER_FLAGS(e2, e1)
      }
      else
      {
        PAIR_TREE_SET_ELEMENTAL_COLLISION_FLAGS(e1, e2)
        PAIR_TREE_SET_ELEMENTAL_COLLISION_FLAGS(e2, e1)
      }

      PAIR_TREE_SET_NONELEMENTAL_COLLISION_FLAGS(e1, e2)
      PAIR_TREE_SET_NONELEMENTAL_COLLISION_FLAGS(e2, e1)

      /* insert processed node into vacant list */
      if (G_pair_list_head_vacant != NULL)
      {
        previous->left  = NULL;
        previous->right = G_pair_list_head_vacant;
      }
      else
      {
        previous->left  = NULL;
        previous->right = NULL;
      }

      G_pair_list_head_vacant = previous;
    }
  }

  G_pair_tree_root_collisions = NULL;

  return 0;
}

/*******************************************************************************
** pair_trees_and_lists_add_cast_warp()
*******************************************************************************/
short int pair_trees_and_lists_add_cast_warp(entity* e1, entity* e2)
{
  pair_node*  new_node;
  pair_node*  current;

  if ((e1 == NULL) || (e2 == NULL))
    return 0;

  /* clear warp related flags on each entity */
  e1->special_flags &= ~ENTITY_SPECIAL_FLAG_WARP_NULLIFY;
  e1->special_flags &= ~ENTITY_SPECIAL_FLAG_WARP_OVERLOAD;
  e2->special_flags &= ~ENTITY_SPECIAL_FLAG_WARP_NULLIFY;
  e2->special_flags &= ~ENTITY_SPECIAL_FLAG_WARP_OVERLOAD;

  /* create node for this warp */
  new_node = pair_trees_and_lists_get_new_node();

  if (new_node == NULL)
    return 1;

  new_node->e1 = e1;
  new_node->e2 = e2;

  /* if cast warps list is empty, make this warp the head of the list */
  if (G_pair_list_head_cast_warps == NULL)
  {
    G_pair_list_head_cast_warps = new_node;
    return 0;
  }

  /* otherwise, find place to insert warp into the list */
  current = G_pair_list_head_cast_warps;

  while (current != NULL)
  {
    if (e1->id > current->e1->id)
    {
      if (current->right == NULL)
      {
        current->right = new_node;
        new_node->left = current;
        return 0;
      }
      else
      {
        current = current->right;
      }
    }
    else if (e1->id < current->e1->id)
    {
      if (current->left == NULL)
      {
        new_node->right = current;
        current->left = new_node;
        G_pair_list_head_cast_warps = new_node;
        return 0;
      }
      else
      {
        new_node->left = current->left;
        current->left->right = new_node;
        new_node->right = current;
        current->left = new_node;
        return 0;
      }
    }
    else
      return 0;
  }

  return 0;
}

/*******************************************************************************
** pair_trees_and_lists_remove_cast_warp()
*******************************************************************************/
short int pair_trees_and_lists_remove_cast_warp(entity* e1)
{
  pair_node*  current;

  if (e1 == NULL)
    return 0;

  /* lookup warp in the list */
  current = G_pair_list_head_cast_warps;

  while (current != NULL)
  {
    if (e1->id == current->e1->id)
    {
      /* remove warp from the cast warps list */
      if ((current->left == NULL) && (current->right == NULL))
      {
        G_pair_list_head_cast_warps = NULL;
      }
      else if (current->left == NULL)
      {
        current->right->left = NULL;
        G_pair_list_head_cast_warps = current->right;
      }
      else if (current->right == NULL)
      {
        current->left->right = NULL;
      }
      else
      {
        current->left->right = current->right;
        current->right->left = current->left;
      }

      /* add warp to the vacant list */
      if (G_pair_list_head_vacant != NULL)
      {
        current->left  = NULL;
        current->right = G_pair_list_head_vacant;
      }
      else
      {
        current->left  = NULL;
        current->right = NULL;
      }

      G_pair_list_head_vacant = current;

      return 0;
    }

    current = current->right;
  }

  return 0;
}

/*******************************************************************************
** pair_trees_and_lists_remove_all_cast_warps_by_caster()
*******************************************************************************/
short int pair_trees_and_lists_remove_all_cast_warps_by_caster(entity* e2)
{
  pair_node*  current;
  pair_node*  next;

  if (e2 == NULL)
    return 0;

  /* lookup caster in the list */
  current = G_pair_list_head_cast_warps;

  while (current != NULL)
  {
    next = current->right;

    if (e2->id == current->e2->id)
    {
      /* remove warp from the cast warps list */
      if ((current->left == NULL) && (current->right == NULL))
      {
        G_pair_list_head_cast_warps = NULL;
      }
      else if (current->left == NULL)
      {
        current->right->left = NULL;
        G_pair_list_head_cast_warps = current->right;
      }
      else if (current->right == NULL)
      {
        current->left->right = NULL;
      }
      else
      {
        current->left->right = current->right;
        current->right->left = current->left;
      }

      /* add warp to the vacant list */
      if (G_pair_list_head_vacant != NULL)
      {
        current->left  = NULL;
        current->right = G_pair_list_head_vacant;
      }
      else
      {
        current->left  = NULL;
        current->right = NULL;
      }

      G_pair_list_head_vacant = current;
    }

    current = next;
  }

  return 0;
}

/*******************************************************************************
** pair_trees_and_lists_update_cast_warps()
*******************************************************************************/
short int pair_trees_and_lists_update_cast_warps(entity* old_e2, entity* new_e2)
{
  pair_node* current;

  if ((old_e2 == NULL) || (new_e2 == NULL))
    return 0;

  /* if cast warps list is empty, return */
  if (G_pair_list_head_cast_warps == NULL)
    return 0;

  /* cycle through cast warps */
  for ( current = G_pair_list_head_cast_warps;
        current != NULL;
        current = current->right)
  {
    if ((current->e2 != NULL) && (current->e2->id == old_e2->id))
    {
      current->e2 = new_e2;
    }
  }

  return 0;
}

/*******************************************************************************
** pair_trees_and_lists_activate_warp()
*******************************************************************************/
short int pair_trees_and_lists_activate_warp(entity* e1, entity* e2)
{
  entity*     e_caster;
  pair_node*  new_node;
  pair_node*  current;

  if ((e1 == NULL) || (e2 == NULL))
    return 0;

  /* lookup warp in the cast warps list */
  e_caster = NULL;
  current = G_pair_list_head_cast_warps;

  while (current != NULL)
  {
    if ((current->e1 != NULL) && (current->e1->id == e1->id))
    {
      e_caster = current->e2;
      break;
    }

    current = current->right;
  }

  /* if warp was not found (or caster was lost), return */
  if (e_caster == NULL)
    return 0;

  /* clear warp related flags on caster and object */
  e_caster->special_flags &= ~ENTITY_SPECIAL_FLAG_WARP_NULLIFY;
  e_caster->special_flags &= ~ENTITY_SPECIAL_FLAG_WARP_OVERLOAD;
  e2->special_flags &= ~ENTITY_SPECIAL_FLAG_WARP_NULLIFY;
  e2->special_flags &= ~ENTITY_SPECIAL_FLAG_WARP_OVERLOAD;

  /* if activated warps list is empty, make this warp the head of the list */
  if (G_pair_list_head_activated_warps == NULL)
  {
    new_node = pair_trees_and_lists_get_new_node();

    if (new_node == NULL)
      return 1;

    new_node->e1 = e_caster;
    new_node->e2 = e2;

    G_pair_list_head_activated_warps = new_node;

    return 0;
  }

  /* otherwise, find place to insert activated warp into the list */
  current = G_pair_list_head_activated_warps;

  while (current != NULL)
  {
    if (e_caster->id > current->e1->id)
    {
      /* inserting new node at tail of the list */
      if (current->right == NULL)
      {
        new_node = pair_trees_and_lists_get_new_node();

        if (new_node == NULL)
          return 1;

        new_node->e1 = e_caster;
        new_node->e2 = e2;

        current->right = new_node;
        new_node->left = current;

        return 0;
      }
      else
      {
        current = current->right;
      }
    }
    else
    {
      /* if this warp is already activated, return */
      if ((e_caster->id == current->e1->id) && (e2->id == current->e2->id))
      {
        return 0;
      }
      /* inserting new node at head of the list */
      else if (current->left == NULL)
      {
        new_node = pair_trees_and_lists_get_new_node();

        if (new_node == NULL)
          return 1;

        new_node->e1 = e_caster;
        new_node->e2 = e2;

        new_node->right = current;
        current->left = new_node;
        G_pair_list_head_activated_warps = new_node;

        return 0;
      }
      /* inserting new node in the middle of the list */
      else
      {
        new_node = pair_trees_and_lists_get_new_node();

        if (new_node == NULL)
          return 1;

        new_node->e1 = e_caster;
        new_node->e2 = e2;

        new_node->left = current->left;
        current->left->right = new_node;
        new_node->right = current;
        current->left = new_node;

        return 0;
      }
    }
  }

  return 0;
}

/*******************************************************************************
** pair_trees_and_lists_remove_activated_warp()
*******************************************************************************/
short int pair_trees_and_lists_remove_activated_warp(entity* e1)
{
  pair_node*  current;

  if (e1 == NULL)
    return 0;

  /* lookup warp in the list */
  current = G_pair_list_head_activated_warps;

  while (current != NULL)
  {
    if (e1->id == current->e1->id)
    {
      /* remove warp from the activated warps list */
      if ((current->left == NULL) && (current->right == NULL))
      {
        G_pair_list_head_activated_warps = NULL;
      }
      else if (current->left == NULL)
      {
        current->right->left = NULL;
        G_pair_list_head_activated_warps = current->right;
      }
      else if (current->right == NULL)
      {
        current->left->right = NULL;
      }
      else
      {
        current->left->right = current->right;
        current->right->left = current->left;
      }

      /* add warp to the vacant list */
      if (G_pair_list_head_vacant != NULL)
      {
        current->left  = NULL;
        current->right = G_pair_list_head_vacant;
      }
      else
      {
        current->left  = NULL;
        current->right = NULL;
      }

      G_pair_list_head_vacant = current;

      return 0;
    }

    current = current->right;
  }

  return 0;
}

/*******************************************************************************
** pair_trees_and_lists_consolidate_warps()
*******************************************************************************/
short int pair_trees_and_lists_consolidate_warps()
{
  entity*     e_warp;
  entity*     e_caster;
  entity*     e_object;
  pair_node*  current_warp_1st;
  pair_node*  next_warp_1st;
  pair_node*  current_warp_2nd;
  pair_node*  next_warp_2nd;

  /* if warp spell was nullified, set nullify flag in the casters as well */
  for ( current_warp_1st = G_pair_list_head_cast_warps;
        current_warp_1st != NULL;
        current_warp_1st = current_warp_1st->right)
  {
    e_warp = current_warp_1st->e1;
    e_caster = current_warp_1st->e2;

    if (e_caster == NULL)
      continue;

    if (e_warp->special_flags & ENTITY_SPECIAL_FLAG_WARP_NULLIFY)
      e_caster->special_flags |= ENTITY_SPECIAL_FLAG_WARP_NULLIFY;
  }

  /* if the caster and the object are the same, nullify warp */
  for ( current_warp_1st = G_pair_list_head_activated_warps;
        current_warp_1st != NULL;
        current_warp_1st = current_warp_1st->right)
  {
    e_caster = current_warp_1st->e1;
    e_object = current_warp_1st->e2;

    if (e_caster == e_object)
      e_caster->special_flags |= ENTITY_SPECIAL_FLAG_WARP_NULLIFY;
  }

  /* if a caster appears more than once in the activated warps list,  */
  /* nullify all warps involving that caster                          */
  /* if an object appears more than once in the activated warps list, */
  /* toggle warp overload flag for that object                        */
  /* if two casters hit each other with warp spells,                  */
  /* nullify one of those spells                                      */
  for ( current_warp_1st = G_pair_list_head_activated_warps;
        current_warp_1st != NULL;
        current_warp_1st = current_warp_1st->right)
  {
    e_caster = current_warp_1st->e1;
    e_object = current_warp_1st->e2;

    for ( current_warp_2nd = current_warp_1st->right;
          current_warp_2nd != NULL;
          current_warp_2nd = current_warp_2nd->right)
    {
      if (e_caster == current_warp_2nd->e1)
        e_caster->special_flags |= ENTITY_SPECIAL_FLAG_WARP_NULLIFY;

      if (e_object == current_warp_2nd->e2)
        e_object->special_flags |= ENTITY_SPECIAL_FLAG_WARP_OVERLOAD;

      if ((e_caster == current_warp_2nd->e2) &&
          (e_object == current_warp_2nd->e1))
      {
        e_caster->special_flags |= ENTITY_SPECIAL_FLAG_WARP_NULLIFY;
      }
    }
  }

  /* clear all nullified warps and overloads from the activated warps lists */
  current_warp_1st = G_pair_list_head_activated_warps;

  while (current_warp_1st != NULL)
  {
    next_warp_1st = current_warp_1st->right;

    e_caster = current_warp_1st->e1;
    e_object = current_warp_1st->e2;

    if ((e_caster->special_flags & ENTITY_SPECIAL_FLAG_WARP_NULLIFY)  ||
        (e_object->special_flags & ENTITY_SPECIAL_FLAG_WARP_OVERLOAD))
    {
      pair_trees_and_lists_remove_activated_warp(e_caster);
    }

    current_warp_1st = next_warp_1st;
  }

  /* clear destroyed warps from the cast warps list */
  current_warp_1st = G_pair_list_head_cast_warps;

  while (current_warp_1st != NULL)
  {
    next_warp_1st = current_warp_1st->right;

    e_warp = current_warp_1st->e1;

    if (e_warp->collision_flags & ENTITY_COLLISION_FLAG_DESTROYED)
    {
      pair_trees_and_lists_remove_cast_warp(e_warp);
    }

    current_warp_1st = next_warp_1st;
  }

  /* rearrange activated warps so that entities that are both casters */
  /* and objects have their warp as a caster last                     */
  current_warp_1st = G_pair_list_head_activated_warps;

  while (current_warp_1st != NULL)
  {
    e_caster = current_warp_1st->e1;
    e_object = current_warp_1st->e2;

    current_warp_2nd = current_warp_1st->right;

    while (current_warp_2nd != NULL)
    {
      next_warp_2nd = current_warp_2nd->right;

      /* if this node involves a previous caster as an object,  */
      /* send the node to the front of the list                 */
      if (e_caster == current_warp_2nd->e2)
      {
        /* remove warp from the list */
        if (current_warp_2nd->left != NULL)
          current_warp_2nd->left->right = current_warp_2nd->right;

        if (current_warp_2nd->right != NULL)
          current_warp_2nd->right->left = current_warp_2nd->left;

        /* insert warp at front of the list */
        current_warp_2nd->left = NULL;
        current_warp_2nd->right = G_pair_list_head_activated_warps;
        G_pair_list_head_activated_warps->left = current_warp_2nd;
        G_pair_list_head_activated_warps = current_warp_2nd;
      }

      current_warp_2nd = next_warp_2nd;
    }

    current_warp_1st = current_warp_1st->right;
  }

  return 0;
}

/*******************************************************************************
** pair_trees_and_lists_clear_activated_warps()
*******************************************************************************/
short int pair_trees_and_lists_clear_activated_warps()
{
  pair_node*  current;

  /* lookup warp in the list */
  current = G_pair_list_head_activated_warps;

  while (current != NULL)
  {
    /* remove warp from the activated warps list */
    if ((current->left == NULL) && (current->right == NULL))
    {
      G_pair_list_head_activated_warps = NULL;
    }
    else if (current->left == NULL)
    {
      current->right->left = NULL;
      G_pair_list_head_activated_warps = current->right;
    }
    else if (current->right == NULL)
    {
      current->left->right = NULL;
    }
    else
    {
      current->left->right = current->right;
      current->right->left = current->left;
    }

    /* add warp to the vacant list */
    if (G_pair_list_head_vacant != NULL)
    {
      current->left  = NULL;
      current->right = G_pair_list_head_vacant;
    }
    else
    {
      current->left  = NULL;
      current->right = NULL;
    }

    G_pair_list_head_vacant = current;

    current = G_pair_list_head_activated_warps;
  }

  return 0;
}

