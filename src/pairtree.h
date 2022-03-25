/*******************************************************************************
** pairtree.h (entity pair trees and lists)
*******************************************************************************/

#ifndef PAIR_TREE_H
#define PAIR_TREE_H

#include "entity.h"

#define PAIR_NODES_INITIAL_NUM        50
#define PAIR_TREE_STACK_INITIAL_SIZE  10

#define PAIR_TREE_PUSH_NODE(stack, node)                                       \
  if (stack##_top >= stack##_size - 1)                                         \
  {                                                                            \
    stack = realloc(stack,                                                     \
                    (stack##_size + PAIR_TREE_STACK_INITIAL_SIZE) *            \
                    sizeof(pair_node*));                                  \
  }                                                                            \
                                                                               \
  stack[++stack##_top] = node;

#define PAIR_TREE_POP_NODE(stack)                                              \
  if (stack##_top >= 0)                                                        \
    stack##_top--;

typedef struct pair_node
{
  entity* e1;
  entity* e2;

  struct pair_node* left;
  struct pair_node* right;
} pair_node;

extern pair_node* G_pair_tree_root_collisions;
extern pair_node* G_pair_list_head_cast_warps;
extern pair_node* G_pair_list_head_activated_warps;
extern pair_node* G_pair_list_head_vacant;

/* function declarations */
short int   pair_node_init(pair_node* node);
pair_node*  pair_node_create();
short int   pair_node_deinit(pair_node* node);
short int   pair_node_destroy(pair_node* node);

short int   pair_tree_destroy(pair_node* root);
short int   pair_list_destroy(pair_node* head);

short int   pair_trees_and_lists_init();
short int   pair_trees_and_lists_deinit();

short int   pair_trees_and_lists_add_collision(entity* e1, entity* e2);
short int   pair_trees_and_lists_process_collisions();

short int   pair_trees_and_lists_add_cast_warp(entity* e1, entity* e2);
short int   pair_trees_and_lists_remove_cast_warp(entity* e1);
short int   pair_trees_and_lists_remove_all_cast_warps_by_caster(entity* e2);
short int   pair_trees_and_lists_update_cast_warps( entity* old_e2, 
                                                    entity* new_e2);

short int   pair_trees_and_lists_activate_warp(entity* e1, entity* e2);
short int   pair_trees_and_lists_remove_activated_warp(entity* e1);

short int   pair_trees_and_lists_consolidate_warps();
short int   pair_trees_and_lists_clear_activated_warps();

#endif
