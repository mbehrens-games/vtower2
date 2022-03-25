/*******************************************************************************
** world.h (entity and particle lists)
*******************************************************************************/

#ifndef WORLD_H
#define WORLD_H

#include "entity.h"
#include "particle.h"

#define CATEGORY_INDEX_CAN_MOVE(i)                                             \
  (i == CATEGORY_INDEX_PUSHABLE_OBJECTS)                      ||               \
  (i == CATEGORY_INDEX_PUMPKINS_GHOSTS_MASKS)                 ||               \
  (i == CATEGORY_INDEX_DOUBLES)                               ||               \
  (i == CATEGORY_INDEX_SNAKES_FAERIES_VENUSIANS)              ||               \
  (i == CATEGORY_INDEX_REVERSE_DOUBLES)                       ||               \
  (i == CATEGORY_INDEX_LIL_BOTS_WISPS_FROGS)                  ||               \
  (i == CATEGORY_INDEX_IMPS_JIANGSHIS)                        ||               \
  (i == CATEGORY_INDEX_UNDINES_SORCERESSES_WITCHES)           ||               \
  (i == CATEGORY_INDEX_GUARDIANS)                             ||               \
  (i == CATEGORY_INDEX_MUMMIES_POLTERGEISTS)                  ||               \
  (i == CATEGORY_INDEX_PLAYER)                                ||               \
  (i == CATEGORY_INDEX_SPELLS)

#define CATEGORY_INDEX_CAN_BE_CONVEYED(i)                                      \
  (i == CATEGORY_INDEX_PUSHABLE_OBJECTS)                      ||               \
  (i == CATEGORY_INDEX_PUMPKINS_GHOSTS_MASKS)                 ||               \
  (i == CATEGORY_INDEX_DOUBLES)                               ||               \
  (i == CATEGORY_INDEX_SNAKES_FAERIES_VENUSIANS)              ||               \
  (i == CATEGORY_INDEX_REVERSE_DOUBLES)                       ||               \
  (i == CATEGORY_INDEX_LIL_BOTS_WISPS_FROGS)                  ||               \
  (i == CATEGORY_INDEX_IMPS_JIANGSHIS)                        ||               \
  (i == CATEGORY_INDEX_UNDINES_SORCERESSES_WITCHES)           ||               \
  (i == CATEGORY_INDEX_GUARDIANS)                             ||               \
  (i == CATEGORY_INDEX_MUMMIES_POLTERGEISTS)                  ||               \
  (i == CATEGORY_INDEX_PLAYER)

#define CATEGORY_INDEX_CAN_ANIMATE(i)                                          \
  (i == CATEGORY_INDEX_PORTCULLIS)                            ||               \
  (i == CATEGORY_INDEX_WATER)                                 ||               \
  (i == CATEGORY_INDEX_SYMBOLS)                               ||               \
  (i == CATEGORY_INDEX_BRIDGES_SUBMERGED)                     ||               \
  (i == CATEGORY_INDEX_PUSHABLE_OBJECTS)                      ||               \
  (i == CATEGORY_INDEX_BALLISTAS)                             ||               \
  (i == CATEGORY_INDEX_FLOOR_SPIKES)                          ||               \
  (i == CATEGORY_INDEX_CONVEYERS)                             ||               \
  (i == CATEGORY_INDEX_LEVERS)                                ||               \
  (i == CATEGORY_INDEX_SWITCHES)                              ||               \
  (i == CATEGORY_INDEX_PUMPKINS_GHOSTS_MASKS)                 ||               \
  (i == CATEGORY_INDEX_DOUBLES)                               ||               \
  (i == CATEGORY_INDEX_SNAKES_FAERIES_VENUSIANS)              ||               \
  (i == CATEGORY_INDEX_VENUSIAN_ROOTS)                        ||               \
  (i == CATEGORY_INDEX_REVERSE_DOUBLES)                       ||               \
  (i == CATEGORY_INDEX_LIL_BOTS_WISPS_FROGS)                  ||               \
  (i == CATEGORY_INDEX_IMPS_JIANGSHIS)                        ||               \
  (i == CATEGORY_INDEX_UNDINES_SORCERESSES_WITCHES)           ||               \
  (i == CATEGORY_INDEX_GUARDIANS)                             ||               \
  (i == CATEGORY_INDEX_MUMMIES_POLTERGEISTS)                  ||               \
  (i == CATEGORY_INDEX_LASER_GUNS)                            ||               \
  (i == CATEGORY_INDEX_PICKUPS)                               ||               \
  (i == CATEGORY_INDEX_PLAYER)                                ||               \
  (i == CATEGORY_INDEX_SPELLS)                                ||               \
  (i == CATEGORY_INDEX_EXPLOSIONS)

#define CATEGORY_INDEX_CAN_HAVE_COOLDOWN(i)                                    \
  (i == CATEGORY_INDEX_SYMBOLS)                               ||               \
  (i == CATEGORY_INDEX_BRIDGES_SUBMERGED)                     ||               \
  (i == CATEGORY_INDEX_PUSHABLE_OBJECTS)                      ||               \
  (i == CATEGORY_INDEX_ARROWS)                                ||               \
  (i == CATEGORY_INDEX_BALLISTAS)                             ||               \
  (i == CATEGORY_INDEX_PINBALL_KICKERS)                       ||               \
  (i == CATEGORY_INDEX_LEVERS)                                ||               \
  (i == CATEGORY_INDEX_SWITCHES)                              ||               \
  (i == CATEGORY_INDEX_DOUBLES)                               ||               \
  (i == CATEGORY_INDEX_SNAKES_FAERIES_VENUSIANS)              ||               \
  (i == CATEGORY_INDEX_VENUSIAN_ROOTS)                        ||               \
  (i == CATEGORY_INDEX_REVERSE_DOUBLES)                       ||               \
  (i == CATEGORY_INDEX_LIL_BOTS_WISPS_FROGS)                  ||               \
  (i == CATEGORY_INDEX_UNDINES_SORCERESSES_WITCHES)           ||               \
  (i == CATEGORY_INDEX_GUARDIANS)                             ||               \
  (i == CATEGORY_INDEX_MUMMIES_POLTERGEISTS)                  ||               \
  (i == CATEGORY_INDEX_LASER_GUNS)                            ||               \
  (i == CATEGORY_INDEX_PLAYER)                                ||               \
  (i == CATEGORY_INDEX_EXPLOSIONS)

#define CATEGORY_INDEX_CAN_SPIN(i)                                             \
  (i == CATEGORY_INDEX_ARROWS)                                ||               \
  (i == CATEGORY_INDEX_BALLISTAS)                             ||               \
  (i == CATEGORY_INDEX_PINBALL_KICKERS)                       ||               \
  (i == CATEGORY_INDEX_LASER_GUNS)

#define CATEGORY_INDEX_CAN_CAST_SPELLS(i)                                      \
  (i == CATEGORY_INDEX_PUSHABLE_OBJECTS)                      ||               \
  (i == CATEGORY_INDEX_BALLISTAS)                             ||               \
  (i == CATEGORY_INDEX_PUMPKINS_GHOSTS_MASKS)                 ||               \
  (i == CATEGORY_INDEX_DOUBLES)                               ||               \
  (i == CATEGORY_INDEX_SNAKES_FAERIES_VENUSIANS)              ||               \
  (i == CATEGORY_INDEX_REVERSE_DOUBLES)                       ||               \
  (i == CATEGORY_INDEX_UNDINES_SORCERESSES_WITCHES)           ||               \
  (i == CATEGORY_INDEX_GUARDIANS)                             ||               \
  (i == CATEGORY_INDEX_LASER_GUNS)                            ||               \
  (i == CATEGORY_INDEX_PLAYER)

#define CATEGORY_INDEX_CAN_BE_DAMAGED(i)                                       \
  (i == CATEGORY_INDEX_WATER)                                 ||               \
  (i == CATEGORY_INDEX_OBSTACLES)                             ||               \
  (i == CATEGORY_INDEX_SYMBOLS)                               ||               \
  (i == CATEGORY_INDEX_BRIDGES_SUBMERGED)                     ||               \
  (i == CATEGORY_INDEX_PUSHABLE_OBJECTS)                      ||               \
  (i == CATEGORY_INDEX_VANISHED_DICE)                         ||               \
  (i == CATEGORY_INDEX_ARROWS)                                ||               \
  (i == CATEGORY_INDEX_BALLISTAS)                             ||               \
  (i == CATEGORY_INDEX_PINBALL_KICKERS)                       ||               \
  (i == CATEGORY_INDEX_FLOOR_SPIKES)                          ||               \
  (i == CATEGORY_INDEX_LEVERS)                                ||               \
  (i == CATEGORY_INDEX_SWITCHES)                              ||               \
  (i == CATEGORY_INDEX_PUMPKINS_GHOSTS_MASKS)                 ||               \
  (i == CATEGORY_INDEX_DOUBLES)                               ||               \
  (i == CATEGORY_INDEX_SNAKES_FAERIES_VENUSIANS)              ||               \
  (i == CATEGORY_INDEX_VENUSIAN_ROOTS)                        ||               \
  (i == CATEGORY_INDEX_REVERSE_DOUBLES)                       ||               \
  (i == CATEGORY_INDEX_LIL_BOTS_WISPS_FROGS)                  ||               \
  (i == CATEGORY_INDEX_IMPS_JIANGSHIS)                        ||               \
  (i == CATEGORY_INDEX_UNDINES_SORCERESSES_WITCHES)           ||               \
  (i == CATEGORY_INDEX_GUARDIANS)                             ||               \
  (i == CATEGORY_INDEX_MUMMIES_POLTERGEISTS)                  ||               \
  (i == CATEGORY_INDEX_LASER_GUNS)                            ||               \
  (i == CATEGORY_INDEX_PICKUPS)                               ||               \
  (i == CATEGORY_INDEX_PLAYER)                                ||               \
  (i == CATEGORY_INDEX_SPELLS)                                ||               \
  (i == CATEGORY_INDEX_EVIL_EYES)                             ||               \
  (i == CATEGORY_INDEX_EXPLOSIONS)

#define CATEGORY_INDEX_CAN_TRANSFORM(i)                                        \
  (i == CATEGORY_INDEX_PORTCULLIS)                            ||               \
  (i == CATEGORY_INDEX_BRIDGES_SUBMERGED)                     ||               \
  (i == CATEGORY_INDEX_PUSHABLE_OBJECTS)                      ||               \
  (i == CATEGORY_INDEX_VANISHED_DICE)                         ||               \
  (i == CATEGORY_INDEX_FLOOR_SPIKES)                          ||               \
  (i == CATEGORY_INDEX_PUMPKINS_GHOSTS_MASKS)                 ||               \
  (i == CATEGORY_INDEX_DOUBLES)                               ||               \
  (i == CATEGORY_INDEX_SNAKES_FAERIES_VENUSIANS)              ||               \
  (i == CATEGORY_INDEX_REVERSE_DOUBLES)                       ||               \
  (i == CATEGORY_INDEX_LIL_BOTS_WISPS_FROGS)                  ||               \
  (i == CATEGORY_INDEX_IMPS_JIANGSHIS)                        ||               \
  (i == CATEGORY_INDEX_UNDINES_SORCERESSES_WITCHES)           ||               \
  (i == CATEGORY_INDEX_GUARDIANS)                             ||               \
  (i == CATEGORY_INDEX_MUMMIES_POLTERGEISTS)                  ||               \
  (i == CATEGORY_INDEX_PLAYER)                                ||               \
  (i == CATEGORY_INDEX_SPELLS)

#define CATEGORY_INDEX_CAN_FALL_INTO_WATER(i)                                  \
  (i == CATEGORY_INDEX_OBSTACLES)                             ||               \
  (i == CATEGORY_INDEX_PUSHABLE_OBJECTS)                      ||               \
  (i == CATEGORY_INDEX_VANISHED_DICE)                         ||               \
  (i == CATEGORY_INDEX_BALLISTAS)                             ||               \
  (i == CATEGORY_INDEX_PINBALL_KICKERS)                       ||               \
  (i == CATEGORY_INDEX_LEVERS)                                ||               \
  (i == CATEGORY_INDEX_PUMPKINS_GHOSTS_MASKS)                 ||               \
  (i == CATEGORY_INDEX_DOUBLES)                               ||               \
  (i == CATEGORY_INDEX_SNAKES_FAERIES_VENUSIANS)              ||               \
  (i == CATEGORY_INDEX_REVERSE_DOUBLES)                       ||               \
  (i == CATEGORY_INDEX_LIL_BOTS_WISPS_FROGS)                  ||               \
  (i == CATEGORY_INDEX_IMPS_JIANGSHIS)                        ||               \
  (i == CATEGORY_INDEX_UNDINES_SORCERESSES_WITCHES)           ||               \
  (i == CATEGORY_INDEX_GUARDIANS)                             ||               \
  (i == CATEGORY_INDEX_MUMMIES_POLTERGEISTS)                  ||               \
  (i == CATEGORY_INDEX_LASER_GUNS)                            ||               \
  (i == CATEGORY_INDEX_PICKUPS)                               ||               \
  (i == CATEGORY_INDEX_PLAYER)

#define WORLD_ENTITIES_INITIAL_NUM    600
#define WORLD_ENTITIES_RESIZE_NUM     100
#define WORLD_PARTICLES_MAX           3000

enum
{
  CATEGORY_INDEX_WALLS = 0,
  CATEGORY_INDEX_PORTCULLIS,
  CATEGORY_INDEX_BACKGROUND,
  CATEGORY_INDEX_FLOOR_BORDERS,
  CATEGORY_INDEX_WATER,
  CATEGORY_INDEX_GRASS_ICE,
  CATEGORY_INDEX_GRASS_BORDERS,
  CATEGORY_INDEX_ICE_BORDERS,
  CATEGORY_INDEX_OBSTACLES,
  CATEGORY_INDEX_SYMBOLS,
  CATEGORY_INDEX_BRIDGES_SUBMERGED,
  CATEGORY_INDEX_PUSHABLE_OBJECTS,
  CATEGORY_INDEX_VANISHED_DICE,
  CATEGORY_INDEX_ARROWS,
  CATEGORY_INDEX_BALLISTAS,
  CATEGORY_INDEX_PINBALL_KICKERS,
  CATEGORY_INDEX_FLOOR_SPIKES,
  CATEGORY_INDEX_CONVEYERS,
  CATEGORY_INDEX_LEVERS,
  CATEGORY_INDEX_SWITCHES,
  CATEGORY_INDEX_PUMPKINS_GHOSTS_MASKS,
  CATEGORY_INDEX_DOUBLES,
  CATEGORY_INDEX_SNAKES_FAERIES_VENUSIANS,
  CATEGORY_INDEX_VENUSIAN_ROOTS,
  CATEGORY_INDEX_REVERSE_DOUBLES,
  CATEGORY_INDEX_LIL_BOTS_WISPS_FROGS,
  CATEGORY_INDEX_IMPS_JIANGSHIS,
  CATEGORY_INDEX_UNDINES_SORCERESSES_WITCHES,
  CATEGORY_INDEX_GUARDIANS,
  CATEGORY_INDEX_MUMMIES_POLTERGEISTS,
  CATEGORY_INDEX_LASER_GUNS,
  CATEGORY_INDEX_PICKUPS,
  CATEGORY_INDEX_PLAYER,
  CATEGORY_INDEX_SPELLS,
  CATEGORY_INDEX_EVIL_EYES,
  CATEGORY_INDEX_EXPLOSIONS,
  CATEGORY_NUM_INDICES
};

extern entity*    G_entity_active_list_head[];
extern entity*    G_entity_active_list_tail[];
extern entity*    G_entity_inactive_list_head;
extern entity*    G_entity_inactive_list_tail;

extern particle   G_particle_array[];
extern int        G_particle_start_i;
extern int        G_particle_end_i;

/* function declarations */
short int world_init();
short int world_deinit();
short int world_spawn_particles_trailing(entity* e);
short int world_spawn_particles_warp_effect(entity* e1, entity* e2);
short int world_spawn_particles_firework(entity* e);
short int world_spawn_particles_water_splash(entity* e);
short int world_spawn_particles_transform(entity* e);
short int world_spawn_particles_floor_spike(entity* e);
entity*   world_spawn_entity(int type, int pos_x, int pos_y);
short int world_despawn_entity(entity* e);
short int world_reset();
short int world_update_particles();
short int world_update_positions();
short int world_update_cooldowns();
short int world_update_spins();
short int world_update_animations();

#endif
