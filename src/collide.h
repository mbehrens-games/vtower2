/*******************************************************************************
** collide.h (spatial partitioning grid and collision checking)
*******************************************************************************/

#ifndef COLLIDE_H
#define COLLIDE_H

#include "entity.h"

/* partitioning the 352x352 play field into 16x16 spaces gives 22x22 grid   */
/* then, adding on an additional space for an outer border gives 24x24 grid */
#define COLLIDE_GRID_WIDTH    24
#define COLLIDE_GRID_HEIGHT   24
#define COLLIDE_GRID_SIZE     (COLLIDE_GRID_WIDTH * COLLIDE_GRID_HEIGHT)

#define COLLIDE_GRID_SPACE_INITIAL_NUM    4
#define COLLIDE_GRID_SPACE_RESIZE_NUM     2

typedef struct collide_grid_space
{
  entity**  entities;
  int       num_entities;
  int       max_entities;
} collide_grid_space;

extern collide_grid_space G_collide_grid[COLLIDE_GRID_SIZE];

/* function declarations */
short int collide_grid_init();
short int collide_grid_deinit();
short int collide_grid_reset();
short int collide_grid_update();
short int collide_grid_add_entity(entity* e);
short int collide_grid_remove_entity(entity* e);

#endif
