/*******************************************************************************
** entity.h (entity)
*******************************************************************************/

#ifndef ENTITY_H
#define ENTITY_H

#define ENTITY_UPDATE_FLAGS_CLEAR               0x00
#define ENTITY_UPDATE_FLAGS_ALL                 0xFF

#define ENTITY_UPDATE_FLAG_ACTIVE               0x01
#define ENTITY_UPDATE_FLAG_STARTED_MOVEMENT     0x02
#define ENTITY_UPDATE_FLAG_STOPPED_MOVEMENT     0x04
#define ENTITY_UPDATE_FLAG_WALKING_IN_PLACE     0x08
#define ENTITY_UPDATE_FLAG_MOVING_INTO_WATER    0x10
#define ENTITY_UPDATE_FLAG_FELL_INTO_WATER      0x20
#define ENTITY_UPDATE_FLAG_TRANSFORMING         0x40
#define ENTITY_UPDATE_FLAG_COOLDOWN             0x80

#define ENTITY_ACTION_FLAGS_CLEAR               0x00
#define ENTITY_ACTION_FLAGS_ALL                 0xFF

#define ENTITY_ACTION_FLAG_MOVING               0x01
#define ENTITY_ACTION_FLAG_PUSHING              0x02
#define ENTITY_ACTION_FLAG_SLIPPING             0x04
#define ENTITY_ACTION_FLAG_CASTING              0x08
#define ENTITY_ACTION_FLAG_ROTATING             0x10
#define ENTITY_ACTION_FLAG_BEING_PUSHED         0x20
#define ENTITY_ACTION_FLAG_BEING_CONVEYED       0x40
#define ENTITY_ACTION_FLAG_MODE                 0x80

#define ENTITY_SPECIAL_FLAGS_CLEAR              0x00
#define ENTITY_SPECIAL_FLAGS_ALL                0xFF

#define ENTITY_SPECIAL_FLAG_ROLLING             0x01
#define ENTITY_SPECIAL_FLAG_OVERLAP             0x02
#define ENTITY_SPECIAL_FLAG_AWAITING_DESTROY    0x04
#define ENTITY_SPECIAL_FLAG_AWAITING_TRANSFORM  0x08
#define ENTITY_SPECIAL_FLAG_WARP_NULLIFY        0x10
#define ENTITY_SPECIAL_FLAG_WARP_OVERLOAD       0x20
#define ENTITY_SPECIAL_FLAG_REFLECT_REVERSE     0x40
#define ENTITY_SPECIAL_FLAG_REFLECT_BANK        0x80

#define ENTITY_ANIMATION_FLAGS_CLEAR            0x00
#define ENTITY_ANIMATION_FLAGS_ALL              0xFF

#define ENTITY_ANIMATION_FLAG_ON                0x01
#define ENTITY_ANIMATION_FLAG_LOOPING           0x02
#define ENTITY_ANIMATION_FLAG_ONLY_WHEN_MOVING  0x04
#define ENTITY_ANIMATION_FLAG_PAUSED            0x08
#define ENTITY_ANIMATION_FLAG_CARRY_OVER        0x10
#define ENTITY_ANIMATION_FLAG_RESTART           0x20

#define ENTITY_MOVE_FLAGS_CLEAR                 0x00
#define ENTITY_MOVE_FLAGS_ALL                   0xFF

#define ENTITY_MOVE_FLAG_VAMPIRE                0x01
#define ENTITY_MOVE_FLAG_PLAYER_BAT             0x02
#define ENTITY_MOVE_FLAG_ENEMY                  0x04
#define ENTITY_MOVE_FLAG_ENEMY_BAT              0x08
#define ENTITY_MOVE_FLAG_PUSHABLE_LOW           0x10
#define ENTITY_MOVE_FLAG_PUSHABLE_HIGH          0x20
#define ENTITY_MOVE_FLAG_SPELL                  0x40
#define ENTITY_MOVE_FLAG_EVIL_EYE               0x80

#define ENTITY_TRIGGER_FLAGS_CLEAR              0x00
#define ENTITY_TRIGGER_FLAGS_ALL                0xFF

#define ENTITY_TRIGGER_FLAG_PUSHABLE            0x01
#define ENTITY_TRIGGER_FLAG_EIGHT_BALLS         0x02
#define ENTITY_TRIGGER_FLAG_LEVERS              0x04
#define ENTITY_TRIGGER_FLAG_BALLISTAS           0x08
#define ENTITY_TRIGGER_FLAG_WISPS               0x10
#define ENTITY_TRIGGER_FLAG_JIANGSHIS           0x20
#define ENTITY_TRIGGER_FLAG_PLAYER              0x40
#define ENTITY_TRIGGER_FLAG_REFLECTER           0x80

#define ENTITY_DAMAGE_FLAGS_CLEAR               0x00
#define ENTITY_DAMAGE_FLAGS_ALL                 0xFF

#define ENTITY_DAMAGE_FLAG_WEAK_TO_FIRE         0x01
#define ENTITY_DAMAGE_FLAG_WEAK_TO_ICE          0x02
#define ENTITY_DAMAGE_FLAG_WEAK_TO_NEUTRAL      0x04
#define ENTITY_DAMAGE_FLAG_WEAK_TO_BOLT         0x08
#define ENTITY_DAMAGE_FLAG_SPELL                0x10
#define ENTITY_DAMAGE_FLAG_FLOOR_SPIKE          0x20
#define ENTITY_DAMAGE_FLAG_FLASK                0x40
#define ENTITY_DAMAGE_FLAG_EXPLODABLE           0x80

#define ENTITY_COLLISION_FLAGS_CLEAR            0x00
#define ENTITY_COLLISION_FLAGS_ALL              0xFF

#define ENTITY_COLLISION_FLAG_COLLECTED         0x01
#define ENTITY_COLLISION_FLAG_LOST_1_HP         0x02
#define ENTITY_COLLISION_FLAG_LOST_2_HP         0x04
#define ENTITY_COLLISION_FLAG_DESTROYED         0x08
#define ENTITY_COLLISION_FLAG_FIRE              0x10
#define ENTITY_COLLISION_FLAG_ICE               0x20
#define ENTITY_COLLISION_FLAG_NEUTRAL           0x40
#define ENTITY_COLLISION_FLAG_BOLT              0x80

#define ENTITY_COLLISION_MASK_ELEMENTAL         0xF0

#define ENTITY_FACING_MASK                      0x07
#define ENTITY_FACING_RIGHT                     0x00
#define ENTITY_FACING_UP_RIGHT                  0x01
#define ENTITY_FACING_UP                        0x02
#define ENTITY_FACING_UP_LEFT                   0x03
#define ENTITY_FACING_LEFT                      0x04
#define ENTITY_FACING_DOWN_LEFT                 0x05
#define ENTITY_FACING_DOWN                      0x06
#define ENTITY_FACING_DOWN_RIGHT                0x07

#define ENTITY_THETA_MASK                       0x18
#define ENTITY_THETA_0                          0x00
#define ENTITY_THETA_90                         0x08
#define ENTITY_THETA_180                        0x10
#define ENTITY_THETA_270                        0x18

#define ENTITY_DIRECTION_MASK                   0x60
#define ENTITY_DIRECTION_RIGHT                  0x00
#define ENTITY_DIRECTION_UP                     0x20
#define ENTITY_DIRECTION_LEFT                   0x40
#define ENTITY_DIRECTION_DOWN                   0x60

#define ENTITY_SPEED_FLAG                       0x80

enum
{
  ENTITY_TYPE_NONE,
  /* walls */
  ENTITY_TYPE_OUTER_WALL_TOP_LEFT,
  ENTITY_TYPE_OUTER_WALL_TOP,
  ENTITY_TYPE_OUTER_WALL_TOP_RIGHT,
  ENTITY_TYPE_OUTER_WALL_RIGHT,
  ENTITY_TYPE_OUTER_WALL_LEFT,
  ENTITY_TYPE_OUTER_WALL_BOTTOM_LEFT,
  ENTITY_TYPE_OUTER_WALL_BOTTOM,
  ENTITY_TYPE_OUTER_WALL_BOTTOM_RIGHT,
  ENTITY_TYPE_INNER_WALL_TOP,
  ENTITY_TYPE_INNER_WALL_BOTTOM,
  /* portcullis */
  ENTITY_TYPE_PORTCULLIS_CLOSED,
  ENTITY_TYPE_PORTCULLIS_OPEN,
  /* floor, floor borders */
  ENTITY_TYPE_FLOOR,
  ENTITY_TYPE_FLOOR_BORDER_TOP_LEFT,
  ENTITY_TYPE_FLOOR_BORDER_TOP,
  ENTITY_TYPE_FLOOR_BORDER_TOP_RIGHT,
  ENTITY_TYPE_FLOOR_BORDER_LEFT,
  ENTITY_TYPE_FLOOR_BORDER_RIGHT,
  ENTITY_TYPE_FLOOR_BORDER_BOTTOM_LEFT,
  ENTITY_TYPE_FLOOR_BORDER_BOTTOM,
  ENTITY_TYPE_FLOOR_BORDER_BOTTOM_RIGHT,
  /* environment, environment borders */
  ENTITY_TYPE_GRASS,
  ENTITY_TYPE_WATER,
  ENTITY_TYPE_ICE,
  ENTITY_TYPE_GRASS_BORDER_TOP_LEFT,
  ENTITY_TYPE_GRASS_BORDER_TOP,
  ENTITY_TYPE_GRASS_BORDER_TOP_RIGHT,
  ENTITY_TYPE_GRASS_BORDER_LEFT,
  ENTITY_TYPE_GRASS_BORDER_RIGHT,
  ENTITY_TYPE_GRASS_BORDER_BOTTOM_LEFT,
  ENTITY_TYPE_GRASS_BORDER_BOTTOM,
  ENTITY_TYPE_GRASS_BORDER_BOTTOM_RIGHT,
  ENTITY_TYPE_ICE_BORDER_TOP_LEFT,
  ENTITY_TYPE_ICE_BORDER_TOP,
  ENTITY_TYPE_ICE_BORDER_TOP_RIGHT,
  ENTITY_TYPE_ICE_BORDER_LEFT,
  ENTITY_TYPE_ICE_BORDER_RIGHT,
  ENTITY_TYPE_ICE_BORDER_BOTTOM_LEFT,
  ENTITY_TYPE_ICE_BORDER_BOTTOM,
  ENTITY_TYPE_ICE_BORDER_BOTTOM_RIGHT,
  /* obstacles */
  ENTITY_TYPE_BLOCK,
  ENTITY_TYPE_PILLAR,
  ENTITY_TYPE_TREE,
  /* symbols */
  ENTITY_TYPE_COBWEB,
  ENTITY_TYPE_JOKER_CARD,
  ENTITY_TYPE_SEAL_OF_SOLOMON,
  ENTITY_TYPE_YIN_YANG,
  /* bridges */
  ENTITY_TYPE_BRIDGE_STONE_VERTICAL,
  ENTITY_TYPE_BRIDGE_WOOD_VERTICAL,
  ENTITY_TYPE_BRIDGE_CRACKED_VERTICAL,
  ENTITY_TYPE_BRIDGE_STONE_HORIZONTAL,
  ENTITY_TYPE_BRIDGE_WOOD_HORIZONTAL,
  ENTITY_TYPE_BRIDGE_CRACKED_HORIZONTAL,
  /* submerged */
  ENTITY_TYPE_BOX_WOOD_SUBMERGED,
  ENTITY_TYPE_BOX_METAL_SUBMERGED,
  ENTITY_TYPE_BOX_TNT_SUBMERGED,
  ENTITY_TYPE_BOX_STONE_SUBMERGED,
  ENTITY_TYPE_PRISM_BLOCK_0_SUBMERGED,
  ENTITY_TYPE_PRISM_BLOCK_45_SUBMERGED,
  ENTITY_TYPE_PRISM_BLOCK_90_SUBMERGED,
  ENTITY_TYPE_PRISM_BLOCK_135_SUBMERGED,
  ENTITY_TYPE_DIE_SOLID_1_SUBMERGED,
  ENTITY_TYPE_DIE_SOLID_2_SUBMERGED,
  ENTITY_TYPE_DIE_SOLID_3_SUBMERGED,
  ENTITY_TYPE_DIE_SOLID_4_SUBMERGED,
  ENTITY_TYPE_DIE_SOLID_5_SUBMERGED,
  ENTITY_TYPE_DIE_SOLID_6_SUBMERGED,
  ENTITY_TYPE_MAHJONG_TILE_EAST_SUBMERGED,
  ENTITY_TYPE_MAHJONG_TILE_NORTH_SUBMERGED,
  ENTITY_TYPE_MAHJONG_TILE_WEST_SUBMERGED,
  ENTITY_TYPE_MAHJONG_TILE_SOUTH_SUBMERGED,
  ENTITY_TYPE_SPELLBINDER_EMPTY_SUBMERGED,
  ENTITY_TYPE_SPELLBINDER_FIRE_SUBMERGED,
  ENTITY_TYPE_SPELLBINDER_ICE_SUBMERGED,
  ENTITY_TYPE_SPELLBINDER_NEUTRAL_SUBMERGED,
  ENTITY_TYPE_ICE_CUBE_SUBMERGED,
  /* pushable objects */
  ENTITY_TYPE_BOX_WOOD,
  ENTITY_TYPE_BOX_METAL,
  ENTITY_TYPE_BOX_TNT,
  ENTITY_TYPE_BOX_STONE,
  ENTITY_TYPE_POT_CLAY,
  ENTITY_TYPE_POT_METAL,
  ENTITY_TYPE_POT_TNT,
  ENTITY_TYPE_POT_STONE,
  ENTITY_TYPE_AQUA_FORTIS,
  ENTITY_TYPE_AQUA_EXPLODIS,
  ENTITY_TYPE_CANDLE_UNLIT,
  ENTITY_TYPE_CANDLE_LIT,
  ENTITY_TYPE_PRISM_BLOCK_0,
  ENTITY_TYPE_PRISM_BLOCK_45,
  ENTITY_TYPE_PRISM_BLOCK_90,
  ENTITY_TYPE_PRISM_BLOCK_135,
  ENTITY_TYPE_EIGHT_BALL,
  ENTITY_TYPE_DIE_SOLID_1,
  ENTITY_TYPE_DIE_SOLID_2,
  ENTITY_TYPE_DIE_SOLID_3,
  ENTITY_TYPE_DIE_SOLID_4,
  ENTITY_TYPE_DIE_SOLID_5,
  ENTITY_TYPE_DIE_SOLID_6,
  ENTITY_TYPE_MAHJONG_TILE_EAST,
  ENTITY_TYPE_MAHJONG_TILE_NORTH,
  ENTITY_TYPE_MAHJONG_TILE_WEST,
  ENTITY_TYPE_MAHJONG_TILE_SOUTH,
  ENTITY_TYPE_SPELLBINDER_EMPTY,
  ENTITY_TYPE_SPELLBINDER_FIRE,
  ENTITY_TYPE_SPELLBINDER_ICE,
  ENTITY_TYPE_SPELLBINDER_NEUTRAL,
  /* vanished dice */
  ENTITY_TYPE_DIE_VANISHED_1,
  ENTITY_TYPE_DIE_VANISHED_2,
  ENTITY_TYPE_DIE_VANISHED_3,
  ENTITY_TYPE_DIE_VANISHED_4,
  ENTITY_TYPE_DIE_VANISHED_5,
  ENTITY_TYPE_DIE_VANISHED_6,
  ENTITY_TYPE_DIE_VANISHED_1_SUBMERGED,
  ENTITY_TYPE_DIE_VANISHED_2_SUBMERGED,
  ENTITY_TYPE_DIE_VANISHED_3_SUBMERGED,
  ENTITY_TYPE_DIE_VANISHED_4_SUBMERGED,
  ENTITY_TYPE_DIE_VANISHED_5_SUBMERGED,
  ENTITY_TYPE_DIE_VANISHED_6_SUBMERGED,
  /* ice cubes */
  ENTITY_TYPE_ICE_CUBE_PUMPKIN,
  ENTITY_TYPE_ICE_CUBE_GHOST_RIGHT,
  ENTITY_TYPE_ICE_CUBE_GHOST_UP,
  ENTITY_TYPE_ICE_CUBE_GHOST_LEFT,
  ENTITY_TYPE_ICE_CUBE_GHOST_DOWN,
  ENTITY_TYPE_ICE_CUBE_MASK_HORIZONTAL_RIGHT,
  ENTITY_TYPE_ICE_CUBE_MASK_HORIZONTAL_LEFT,
  ENTITY_TYPE_ICE_CUBE_MASK_VERTICAL_UP,
  ENTITY_TYPE_ICE_CUBE_MASK_VERTICAL_DOWN,
  ENTITY_TYPE_ICE_CUBE_SNAKE_RIGHT,
  ENTITY_TYPE_ICE_CUBE_SNAKE_UP,
  ENTITY_TYPE_ICE_CUBE_SNAKE_LEFT,
  ENTITY_TYPE_ICE_CUBE_SNAKE_DOWN,
  ENTITY_TYPE_ICE_CUBE_DOUBLE_VAMPIRE_RIGHT,
  ENTITY_TYPE_ICE_CUBE_DOUBLE_VAMPIRE_UP,
  ENTITY_TYPE_ICE_CUBE_DOUBLE_VAMPIRE_LEFT,
  ENTITY_TYPE_ICE_CUBE_DOUBLE_VAMPIRE_DOWN,
  ENTITY_TYPE_ICE_CUBE_DOUBLE_BAT_RIGHT,
  ENTITY_TYPE_ICE_CUBE_DOUBLE_BAT_UP,
  ENTITY_TYPE_ICE_CUBE_DOUBLE_BAT_LEFT,
  ENTITY_TYPE_ICE_CUBE_DOUBLE_BAT_DOWN,
  ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_VAMPIRE_RIGHT,
  ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_VAMPIRE_UP,
  ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_VAMPIRE_LEFT,
  ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_VAMPIRE_DOWN,
  ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_BAT_RIGHT,
  ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_BAT_UP,
  ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_BAT_LEFT,
  ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_BAT_DOWN,
  ENTITY_TYPE_ICE_CUBE_FAERIE_HORIZONTAL_UP,
  ENTITY_TYPE_ICE_CUBE_FAERIE_HORIZONTAL_DOWN,
  ENTITY_TYPE_ICE_CUBE_FAERIE_VERTICAL_RIGHT,
  ENTITY_TYPE_ICE_CUBE_FAERIE_VERTICAL_LEFT,
  ENTITY_TYPE_ICE_CUBE_VENUSIAN,
  ENTITY_TYPE_ICE_CUBE_WITCH_RIGHT,
  ENTITY_TYPE_ICE_CUBE_WITCH_UP,
  ENTITY_TYPE_ICE_CUBE_WITCH_LEFT,
  ENTITY_TYPE_ICE_CUBE_WITCH_DOWN,
  ENTITY_TYPE_ICE_CUBE_SORCERESS_RIGHT,
  ENTITY_TYPE_ICE_CUBE_SORCERESS_UP,
  ENTITY_TYPE_ICE_CUBE_SORCERESS_LEFT,
  ENTITY_TYPE_ICE_CUBE_SORCERESS_DOWN,
  ENTITY_TYPE_ICE_CUBE_FROG_RIGHT,
  ENTITY_TYPE_ICE_CUBE_FROG_UP,
  ENTITY_TYPE_ICE_CUBE_FROG_LEFT,
  ENTITY_TYPE_ICE_CUBE_FROG_DOWN,
  ENTITY_TYPE_ICE_CUBE_IMP_LT_RIGHT,
  ENTITY_TYPE_ICE_CUBE_IMP_LT_UP,
  ENTITY_TYPE_ICE_CUBE_IMP_LT_LEFT,
  ENTITY_TYPE_ICE_CUBE_IMP_LT_DOWN,
  ENTITY_TYPE_ICE_CUBE_IMP_RT_RIGHT,
  ENTITY_TYPE_ICE_CUBE_IMP_RT_UP,
  ENTITY_TYPE_ICE_CUBE_IMP_RT_LEFT,
  ENTITY_TYPE_ICE_CUBE_IMP_RT_DOWN,
  ENTITY_TYPE_ICE_CUBE_LIL_BOT_RIGHT,
  ENTITY_TYPE_ICE_CUBE_LIL_BOT_UP,
  ENTITY_TYPE_ICE_CUBE_LIL_BOT_LEFT,
  ENTITY_TYPE_ICE_CUBE_LIL_BOT_DOWN,
  ENTITY_TYPE_ICE_CUBE_JIANGSHI_LT_RIGHT,
  ENTITY_TYPE_ICE_CUBE_JIANGSHI_LT_UP,
  ENTITY_TYPE_ICE_CUBE_JIANGSHI_LT_LEFT,
  ENTITY_TYPE_ICE_CUBE_JIANGSHI_LT_DOWN,
  ENTITY_TYPE_ICE_CUBE_JIANGSHI_LT_STOPPED,
  ENTITY_TYPE_ICE_CUBE_JIANGSHI_RT_RIGHT,
  ENTITY_TYPE_ICE_CUBE_JIANGSHI_RT_UP,
  ENTITY_TYPE_ICE_CUBE_JIANGSHI_RT_LEFT,
  ENTITY_TYPE_ICE_CUBE_JIANGSHI_RT_DOWN,
  ENTITY_TYPE_ICE_CUBE_JIANGSHI_RT_STOPPED,
  ENTITY_TYPE_ICE_CUBE_MUMMY_LT,
  ENTITY_TYPE_ICE_CUBE_MUMMY_RT,
  ENTITY_TYPE_ICE_CUBE_GUARDIAN_LT_RIGHT,
  ENTITY_TYPE_ICE_CUBE_GUARDIAN_LT_UP,
  ENTITY_TYPE_ICE_CUBE_GUARDIAN_LT_LEFT,
  ENTITY_TYPE_ICE_CUBE_GUARDIAN_LT_DOWN,
  ENTITY_TYPE_ICE_CUBE_GUARDIAN_RT_RIGHT,
  ENTITY_TYPE_ICE_CUBE_GUARDIAN_RT_UP,
  ENTITY_TYPE_ICE_CUBE_GUARDIAN_RT_LEFT,
  ENTITY_TYPE_ICE_CUBE_GUARDIAN_RT_DOWN,
  ENTITY_TYPE_ICE_CUBE_PLAYER_VAMPIRE_RIGHT,
  ENTITY_TYPE_ICE_CUBE_PLAYER_VAMPIRE_UP,
  ENTITY_TYPE_ICE_CUBE_PLAYER_VAMPIRE_LEFT,
  ENTITY_TYPE_ICE_CUBE_PLAYER_VAMPIRE_DOWN,
  ENTITY_TYPE_ICE_CUBE_PLAYER_BAT_RIGHT,
  ENTITY_TYPE_ICE_CUBE_PLAYER_BAT_UP,
  ENTITY_TYPE_ICE_CUBE_PLAYER_BAT_LEFT,
  ENTITY_TYPE_ICE_CUBE_PLAYER_BAT_DOWN,
  /* arrows */
  ENTITY_TYPE_ARROWS_RED,
  ENTITY_TYPE_ARROWS_GREEN,
  ENTITY_TYPE_ARROWS_BROWN,
  /* ballistas */
  ENTITY_TYPE_BALLISTA_RED,
  ENTITY_TYPE_BALLISTA_GREEN,
  ENTITY_TYPE_BALLISTA_BROWN,
  /* pinball kickers */
  ENTITY_TYPE_BAR_KICKER_RED,
  ENTITY_TYPE_BAR_KICKER_GREEN,
  ENTITY_TYPE_BAR_KICKER_BROWN,
  ENTITY_TYPE_TRIANGLE_KICKER_RED,
  ENTITY_TYPE_TRIANGLE_KICKER_GREEN,
  ENTITY_TYPE_TRIANGLE_KICKER_BROWN,
  /* conveyers */
  ENTITY_TYPE_CONVEYER_WHITE,
  ENTITY_TYPE_CONVEYER_CYAN,
  ENTITY_TYPE_CONVEYER_MAGENTA,
  /* floor spikes */
  ENTITY_TYPE_FLOOR_SPIKE_DOWN_WHITE,
  ENTITY_TYPE_FLOOR_SPIKE_DOWN_CYAN,
  ENTITY_TYPE_FLOOR_SPIKE_DOWN_MAGENTA,
  ENTITY_TYPE_FLOOR_SPIKE_UP_WHITE,
  ENTITY_TYPE_FLOOR_SPIKE_UP_CYAN,
  ENTITY_TYPE_FLOOR_SPIKE_UP_MAGENTA,
  /* levers */
  ENTITY_TYPE_LEVER_WHITE,
  ENTITY_TYPE_LEVER_CYAN,
  ENTITY_TYPE_LEVER_MAGENTA,
  /* switches */
  ENTITY_TYPE_SPIN_SWITCH_RED_CCW,
  ENTITY_TYPE_SPIN_SWITCH_RED_CW,
  ENTITY_TYPE_SPIN_SWITCH_GREEN_CCW,
  ENTITY_TYPE_SPIN_SWITCH_GREEN_CW,
  ENTITY_TYPE_SPIN_SWITCH_BROWN_CCW,
  ENTITY_TYPE_SPIN_SWITCH_BROWN_CW,
  ENTITY_TYPE_NUMBER_SWITCH_EVEN,
  ENTITY_TYPE_NUMBER_SWITCH_ODD,
  ENTITY_TYPE_NUMBER_SWITCH_PRIME,
  ENTITY_TYPE_NUMBER_SWITCH_COMPOSITE,
  ENTITY_TYPE_NUMBER_SWITCH_SQUARE,
  ENTITY_TYPE_NUMBER_SWITCH_TRIANGULAR,
  /* enemies */
  ENTITY_TYPE_PUMPKIN,
  ENTITY_TYPE_GHOST,
  ENTITY_TYPE_MASK_HORIZONTAL,
  ENTITY_TYPE_MASK_VERTICAL,
  ENTITY_TYPE_SNAKE,
  ENTITY_TYPE_DOUBLE_VAMPIRE,
  ENTITY_TYPE_DOUBLE_BAT,
  ENTITY_TYPE_REVERSE_DOUBLE_VAMPIRE,
  ENTITY_TYPE_REVERSE_DOUBLE_BAT,
  ENTITY_TYPE_FAERIE_HORIZONTAL,
  ENTITY_TYPE_FAERIE_VERTICAL,
  ENTITY_TYPE_VENUSIAN,
  ENTITY_TYPE_VENUSIAN_ROOT,
  ENTITY_TYPE_WITCH,
  ENTITY_TYPE_UNDINE,
  ENTITY_TYPE_SORCERESS,
  ENTITY_TYPE_FROG,
  ENTITY_TYPE_IMP_LT,
  ENTITY_TYPE_IMP_RT,
  ENTITY_TYPE_LIL_BOT,
  ENTITY_TYPE_POLTERGEIST,
  ENTITY_TYPE_WISP_LEFT_WALL,
  ENTITY_TYPE_WISP_RIGHT_WALL,
  ENTITY_TYPE_JIANGSHI_LT,
  ENTITY_TYPE_JIANGSHI_RT,
  ENTITY_TYPE_MUMMY_LT,
  ENTITY_TYPE_MUMMY_RT,
  ENTITY_TYPE_GUARDIAN_LT,
  ENTITY_TYPE_GUARDIAN_RT,
  ENTITY_TYPE_LASER_GUN,
  /* pickups */
  ENTITY_TYPE_BLOOD_VIAL,
  ENTITY_TYPE_BAT_VIAL,
  ENTITY_TYPE_BLUE_MANA,
  ENTITY_TYPE_GREEN_MANA,
  ENTITY_TYPE_FLOPPY_DISK_3_AND_1_2,
  ENTITY_TYPE_FLOPPY_DISK_5_AND_1_4,
  /* player */
  ENTITY_TYPE_PLAYER_VAMPIRE,
  ENTITY_TYPE_PLAYER_BAT,
  /* spells */
  ENTITY_TYPE_FIRE_SPELL,
  ENTITY_TYPE_ICE_SPELL,
  ENTITY_TYPE_NEUTRAL_SPELL,
  ENTITY_TYPE_WARP_SPELL,
  ENTITY_TYPE_BALLISTA_BOLT,
  ENTITY_TYPE_LASER_SHOT,
  ENTITY_TYPE_EVIL_EYE,
  /* explosion */
  ENTITY_TYPE_EXPLOSION
};

#define ENTITY_TYPE_IS_PLAYER(type)                                            \
  (type == ENTITY_TYPE_PLAYER_VAMPIRE)              ||                         \
  (type == ENTITY_TYPE_PLAYER_BAT)

#define ENTITY_TYPE_IS_PLAYER_OR_DOUBLE(type)                                  \
  (type == ENTITY_TYPE_PLAYER_VAMPIRE)              ||                         \
  (type == ENTITY_TYPE_PLAYER_BAT)                  ||                         \
  (type == ENTITY_TYPE_DOUBLE_VAMPIRE)              ||                         \
  (type == ENTITY_TYPE_DOUBLE_BAT)                  ||                         \
  (type == ENTITY_TYPE_REVERSE_DOUBLE_VAMPIRE)      ||                         \
  (type == ENTITY_TYPE_REVERSE_DOUBLE_BAT)

#define ENTITY_TYPE_IS_VAMPIRE(type)                                           \
  (type == ENTITY_TYPE_PLAYER_VAMPIRE)              ||                         \
  (type == ENTITY_TYPE_DOUBLE_VAMPIRE)              ||                         \
  (type == ENTITY_TYPE_REVERSE_DOUBLE_VAMPIRE)

#define ENTITY_TYPE_IS_BAT(type)                                               \
  (type == ENTITY_TYPE_PLAYER_BAT)                  ||                         \
  (type == ENTITY_TYPE_DOUBLE_BAT)                  ||                         \
  (type == ENTITY_TYPE_REVERSE_DOUBLE_BAT)

#define ENTITY_TYPE_IS_ENEMY(type)                                             \
  (type == ENTITY_TYPE_PUMPKIN)                     ||                         \
  (type == ENTITY_TYPE_GHOST)                       ||                         \
  (type == ENTITY_TYPE_MASK_HORIZONTAL)             ||                         \
  (type == ENTITY_TYPE_MASK_VERTICAL)               ||                         \
  (type == ENTITY_TYPE_SNAKE)                       ||                         \
  (type == ENTITY_TYPE_DOUBLE_VAMPIRE)              ||                         \
  (type == ENTITY_TYPE_DOUBLE_BAT)                  ||                         \
  (type == ENTITY_TYPE_REVERSE_DOUBLE_VAMPIRE)      ||                         \
  (type == ENTITY_TYPE_REVERSE_DOUBLE_BAT)          ||                         \
  (type == ENTITY_TYPE_FAERIE_HORIZONTAL)           ||                         \
  (type == ENTITY_TYPE_FAERIE_VERTICAL)             ||                         \
  (type == ENTITY_TYPE_VENUSIAN)                    ||                         \
  (type == ENTITY_TYPE_WITCH)                       ||                         \
  (type == ENTITY_TYPE_UNDINE)                      ||                         \
  (type == ENTITY_TYPE_SORCERESS)                   ||                         \
  (type == ENTITY_TYPE_FROG)                        ||                         \
  (type == ENTITY_TYPE_IMP_LT)                      ||                         \
  (type == ENTITY_TYPE_IMP_RT)                      ||                         \
  (type == ENTITY_TYPE_LIL_BOT)                     ||                         \
  (type == ENTITY_TYPE_POLTERGEIST)                 ||                         \
  (type == ENTITY_TYPE_WISP_LEFT_WALL)              ||                         \
  (type == ENTITY_TYPE_WISP_RIGHT_WALL)             ||                         \
  (type == ENTITY_TYPE_JIANGSHI_LT)                 ||                         \
  (type == ENTITY_TYPE_JIANGSHI_RT)                 ||                         \
  (type == ENTITY_TYPE_MUMMY_LT)                    ||                         \
  (type == ENTITY_TYPE_MUMMY_RT)                    ||                         \
  (type == ENTITY_TYPE_GUARDIAN_LT)                 ||                         \
  (type == ENTITY_TYPE_GUARDIAN_RT)                 ||                         \
  (type == ENTITY_TYPE_LASER_GUN)

#define ENTITY_TYPE_IS_WARP_CASTER(type)                                       \
  (type == ENTITY_TYPE_PLAYER_VAMPIRE)              ||                         \
  (type == ENTITY_TYPE_PLAYER_BAT)                  ||                         \
  (type == ENTITY_TYPE_DOUBLE_VAMPIRE)              ||                         \
  (type == ENTITY_TYPE_DOUBLE_BAT)                  ||                         \
  (type == ENTITY_TYPE_REVERSE_DOUBLE_VAMPIRE)      ||                         \
  (type == ENTITY_TYPE_REVERSE_DOUBLE_BAT)          ||                         \
  (type == ENTITY_TYPE_SORCERESS)

#define ENTITY_TYPE_IS_PUSHABLE_OBJECT(type)                                   \
  (type == ENTITY_TYPE_BOX_WOOD)            ||                                 \
  (type == ENTITY_TYPE_BOX_METAL)           ||                                 \
  (type == ENTITY_TYPE_BOX_TNT)             ||                                 \
  (type == ENTITY_TYPE_BOX_STONE)           ||                                 \
  (type == ENTITY_TYPE_POT_CLAY)            ||                                 \
  (type == ENTITY_TYPE_POT_METAL)           ||                                 \
  (type == ENTITY_TYPE_POT_TNT)             ||                                 \
  (type == ENTITY_TYPE_POT_STONE)           ||                                 \
  (type == ENTITY_TYPE_AQUA_FORTIS)         ||                                 \
  (type == ENTITY_TYPE_AQUA_EXPLODIS)       ||                                 \
  (type == ENTITY_TYPE_CANDLE_UNLIT)        ||                                 \
  (type == ENTITY_TYPE_CANDLE_LIT)          ||                                 \
  (type == ENTITY_TYPE_PRISM_BLOCK_0)       ||                                 \
  (type == ENTITY_TYPE_PRISM_BLOCK_45)      ||                                 \
  (type == ENTITY_TYPE_PRISM_BLOCK_90)      ||                                 \
  (type == ENTITY_TYPE_PRISM_BLOCK_135)     ||                                 \
  (type == ENTITY_TYPE_EIGHT_BALL)          ||                                 \
  (type == ENTITY_TYPE_DIE_SOLID_1)         ||                                 \
  (type == ENTITY_TYPE_DIE_SOLID_2)         ||                                 \
  (type == ENTITY_TYPE_DIE_SOLID_3)         ||                                 \
  (type == ENTITY_TYPE_DIE_SOLID_4)         ||                                 \
  (type == ENTITY_TYPE_DIE_SOLID_5)         ||                                 \
  (type == ENTITY_TYPE_DIE_SOLID_6)         ||                                 \
  (type == ENTITY_TYPE_MAHJONG_TILE_EAST)   ||                                 \
  (type == ENTITY_TYPE_MAHJONG_TILE_NORTH)  ||                                 \
  (type == ENTITY_TYPE_MAHJONG_TILE_WEST)   ||                                 \
  (type == ENTITY_TYPE_MAHJONG_TILE_SOUTH)  ||                                 \
  (type == ENTITY_TYPE_SPELLBINDER_EMPTY)   ||                                 \
  (type == ENTITY_TYPE_SPELLBINDER_FIRE)    ||                                 \
  (type == ENTITY_TYPE_SPELLBINDER_ICE)     ||                                 \
  (type == ENTITY_TYPE_SPELLBINDER_NEUTRAL)

#define ENTITY_TYPE_IS_SPELLBINDER(type)                                       \
  (type == ENTITY_TYPE_SPELLBINDER_EMPTY)   ||                                 \
  (type == ENTITY_TYPE_SPELLBINDER_FIRE)    ||                                 \
  (type == ENTITY_TYPE_SPELLBINDER_ICE)     ||                                 \
  (type == ENTITY_TYPE_SPELLBINDER_NEUTRAL)

#define ENTITY_TYPE_IS_SOLID_DIE(type)                                         \
  (type == ENTITY_TYPE_DIE_SOLID_1)             ||                             \
  (type == ENTITY_TYPE_DIE_SOLID_2)             ||                             \
  (type == ENTITY_TYPE_DIE_SOLID_3)             ||                             \
  (type == ENTITY_TYPE_DIE_SOLID_4)             ||                             \
  (type == ENTITY_TYPE_DIE_SOLID_5)             ||                             \
  (type == ENTITY_TYPE_DIE_SOLID_6)

#define ENTITY_TYPE_IS_SOLID_DIE_SUBMERGED(type)                               \
  (type == ENTITY_TYPE_DIE_SOLID_1_SUBMERGED)   ||                             \
  (type == ENTITY_TYPE_DIE_SOLID_2_SUBMERGED)   ||                             \
  (type == ENTITY_TYPE_DIE_SOLID_3_SUBMERGED)   ||                             \
  (type == ENTITY_TYPE_DIE_SOLID_4_SUBMERGED)   ||                             \
  (type == ENTITY_TYPE_DIE_SOLID_5_SUBMERGED)   ||                             \
  (type == ENTITY_TYPE_DIE_SOLID_6_SUBMERGED)

#define ENTITY_TYPE_IS_VANISHED_DIE(type)                                      \
  (type == ENTITY_TYPE_DIE_VANISHED_1)            ||                           \
  (type == ENTITY_TYPE_DIE_VANISHED_2)            ||                           \
  (type == ENTITY_TYPE_DIE_VANISHED_3)            ||                           \
  (type == ENTITY_TYPE_DIE_VANISHED_4)            ||                           \
  (type == ENTITY_TYPE_DIE_VANISHED_5)            ||                           \
  (type == ENTITY_TYPE_DIE_VANISHED_6)

#define ENTITY_TYPE_IS_VANISHED_DIE_SUBMERGED(type)                            \
  (type == ENTITY_TYPE_DIE_VANISHED_1_SUBMERGED)  ||                           \
  (type == ENTITY_TYPE_DIE_VANISHED_2_SUBMERGED)  ||                           \
  (type == ENTITY_TYPE_DIE_VANISHED_3_SUBMERGED)  ||                           \
  (type == ENTITY_TYPE_DIE_VANISHED_4_SUBMERGED)  ||                           \
  (type == ENTITY_TYPE_DIE_VANISHED_5_SUBMERGED)  ||                           \
  (type == ENTITY_TYPE_DIE_VANISHED_6_SUBMERGED)

#define ENTITY_TYPE_IS_MAHJONG_TILE(type)                                      \
  (type == ENTITY_TYPE_MAHJONG_TILE_EAST)         ||                           \
  (type == ENTITY_TYPE_MAHJONG_TILE_NORTH)        ||                           \
  (type == ENTITY_TYPE_MAHJONG_TILE_WEST)         ||                           \
  (type == ENTITY_TYPE_MAHJONG_TILE_SOUTH)

#define ENTITY_TYPE_IS_MAHJONG_TILE_SUBMERGED(type)                            \
  (type == ENTITY_TYPE_MAHJONG_TILE_EAST_SUBMERGED)   ||                       \
  (type == ENTITY_TYPE_MAHJONG_TILE_NORTH_SUBMERGED)  ||                       \
  (type == ENTITY_TYPE_MAHJONG_TILE_WEST_SUBMERGED)   ||                       \
  (type == ENTITY_TYPE_MAHJONG_TILE_SOUTH_SUBMERGED)

#define ENTITY_TYPE_IS_ICE_CUBE(type)                                          \
  (type == ENTITY_TYPE_ICE_CUBE_PUMPKIN)                        ||             \
  (type == ENTITY_TYPE_ICE_CUBE_GHOST_RIGHT)                    ||             \
  (type == ENTITY_TYPE_ICE_CUBE_GHOST_UP)                       ||             \
  (type == ENTITY_TYPE_ICE_CUBE_GHOST_LEFT)                     ||             \
  (type == ENTITY_TYPE_ICE_CUBE_GHOST_DOWN)                     ||             \
  (type == ENTITY_TYPE_ICE_CUBE_MASK_HORIZONTAL_RIGHT)          ||             \
  (type == ENTITY_TYPE_ICE_CUBE_MASK_HORIZONTAL_LEFT)           ||             \
  (type == ENTITY_TYPE_ICE_CUBE_MASK_VERTICAL_UP)               ||             \
  (type == ENTITY_TYPE_ICE_CUBE_MASK_VERTICAL_DOWN)             ||             \
  (type == ENTITY_TYPE_ICE_CUBE_SNAKE_RIGHT)                    ||             \
  (type == ENTITY_TYPE_ICE_CUBE_SNAKE_UP)                       ||             \
  (type == ENTITY_TYPE_ICE_CUBE_SNAKE_LEFT)                     ||             \
  (type == ENTITY_TYPE_ICE_CUBE_SNAKE_DOWN)                     ||             \
  (type == ENTITY_TYPE_ICE_CUBE_DOUBLE_VAMPIRE_RIGHT)           ||             \
  (type == ENTITY_TYPE_ICE_CUBE_DOUBLE_VAMPIRE_UP)              ||             \
  (type == ENTITY_TYPE_ICE_CUBE_DOUBLE_VAMPIRE_LEFT)            ||             \
  (type == ENTITY_TYPE_ICE_CUBE_DOUBLE_VAMPIRE_DOWN)            ||             \
  (type == ENTITY_TYPE_ICE_CUBE_DOUBLE_BAT_RIGHT)               ||             \
  (type == ENTITY_TYPE_ICE_CUBE_DOUBLE_BAT_UP)                  ||             \
  (type == ENTITY_TYPE_ICE_CUBE_DOUBLE_BAT_LEFT)                ||             \
  (type == ENTITY_TYPE_ICE_CUBE_DOUBLE_BAT_DOWN)                ||             \
  (type == ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_VAMPIRE_RIGHT)   ||             \
  (type == ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_VAMPIRE_UP)      ||             \
  (type == ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_VAMPIRE_LEFT)    ||             \
  (type == ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_VAMPIRE_DOWN)    ||             \
  (type == ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_BAT_RIGHT)       ||             \
  (type == ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_BAT_UP)          ||             \
  (type == ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_BAT_LEFT)        ||             \
  (type == ENTITY_TYPE_ICE_CUBE_REVERSE_DOUBLE_BAT_DOWN)        ||             \
  (type == ENTITY_TYPE_ICE_CUBE_FAERIE_HORIZONTAL_UP)           ||             \
  (type == ENTITY_TYPE_ICE_CUBE_FAERIE_HORIZONTAL_DOWN)         ||             \
  (type == ENTITY_TYPE_ICE_CUBE_FAERIE_VERTICAL_RIGHT)          ||             \
  (type == ENTITY_TYPE_ICE_CUBE_FAERIE_VERTICAL_LEFT)           ||             \
  (type == ENTITY_TYPE_ICE_CUBE_VENUSIAN)                       ||             \
  (type == ENTITY_TYPE_ICE_CUBE_WITCH_RIGHT)                    ||             \
  (type == ENTITY_TYPE_ICE_CUBE_WITCH_UP)                       ||             \
  (type == ENTITY_TYPE_ICE_CUBE_WITCH_LEFT)                     ||             \
  (type == ENTITY_TYPE_ICE_CUBE_WITCH_DOWN)                     ||             \
  (type == ENTITY_TYPE_ICE_CUBE_SORCERESS_RIGHT)                ||             \
  (type == ENTITY_TYPE_ICE_CUBE_SORCERESS_UP)                   ||             \
  (type == ENTITY_TYPE_ICE_CUBE_SORCERESS_LEFT)                 ||             \
  (type == ENTITY_TYPE_ICE_CUBE_SORCERESS_DOWN)                 ||             \
  (type == ENTITY_TYPE_ICE_CUBE_FROG_RIGHT)                     ||             \
  (type == ENTITY_TYPE_ICE_CUBE_FROG_UP)                        ||             \
  (type == ENTITY_TYPE_ICE_CUBE_FROG_LEFT)                      ||             \
  (type == ENTITY_TYPE_ICE_CUBE_FROG_DOWN)                      ||             \
  (type == ENTITY_TYPE_ICE_CUBE_IMP_LT_RIGHT)                   ||             \
  (type == ENTITY_TYPE_ICE_CUBE_IMP_LT_UP)                      ||             \
  (type == ENTITY_TYPE_ICE_CUBE_IMP_LT_LEFT)                    ||             \
  (type == ENTITY_TYPE_ICE_CUBE_IMP_LT_DOWN)                    ||             \
  (type == ENTITY_TYPE_ICE_CUBE_IMP_RT_RIGHT)                   ||             \
  (type == ENTITY_TYPE_ICE_CUBE_IMP_RT_UP)                      ||             \
  (type == ENTITY_TYPE_ICE_CUBE_IMP_RT_LEFT)                    ||             \
  (type == ENTITY_TYPE_ICE_CUBE_IMP_RT_DOWN)                    ||             \
  (type == ENTITY_TYPE_ICE_CUBE_LIL_BOT_RIGHT)                  ||             \
  (type == ENTITY_TYPE_ICE_CUBE_LIL_BOT_UP)                     ||             \
  (type == ENTITY_TYPE_ICE_CUBE_LIL_BOT_LEFT)                   ||             \
  (type == ENTITY_TYPE_ICE_CUBE_LIL_BOT_DOWN)                   ||             \
  (type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_LT_RIGHT)              ||             \
  (type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_LT_UP)                 ||             \
  (type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_LT_LEFT)               ||             \
  (type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_LT_DOWN)               ||             \
  (type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_LT_STOPPED)            ||             \
  (type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_RT_RIGHT)              ||             \
  (type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_RT_UP)                 ||             \
  (type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_RT_LEFT)               ||             \
  (type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_RT_DOWN)               ||             \
  (type == ENTITY_TYPE_ICE_CUBE_JIANGSHI_RT_STOPPED)            ||             \
  (type == ENTITY_TYPE_ICE_CUBE_MUMMY_LT)                       ||             \
  (type == ENTITY_TYPE_ICE_CUBE_MUMMY_RT)                       ||             \
  (type == ENTITY_TYPE_ICE_CUBE_GUARDIAN_LT_RIGHT)              ||             \
  (type == ENTITY_TYPE_ICE_CUBE_GUARDIAN_LT_UP)                 ||             \
  (type == ENTITY_TYPE_ICE_CUBE_GUARDIAN_LT_LEFT)               ||             \
  (type == ENTITY_TYPE_ICE_CUBE_GUARDIAN_LT_DOWN)               ||             \
  (type == ENTITY_TYPE_ICE_CUBE_GUARDIAN_RT_RIGHT)              ||             \
  (type == ENTITY_TYPE_ICE_CUBE_GUARDIAN_RT_UP)                 ||             \
  (type == ENTITY_TYPE_ICE_CUBE_GUARDIAN_RT_LEFT)               ||             \
  (type == ENTITY_TYPE_ICE_CUBE_GUARDIAN_RT_DOWN)               ||             \
  (type == ENTITY_TYPE_ICE_CUBE_PLAYER_VAMPIRE_RIGHT)           ||             \
  (type == ENTITY_TYPE_ICE_CUBE_PLAYER_VAMPIRE_UP)              ||             \
  (type == ENTITY_TYPE_ICE_CUBE_PLAYER_VAMPIRE_LEFT)            ||             \
  (type == ENTITY_TYPE_ICE_CUBE_PLAYER_VAMPIRE_DOWN)            ||             \
  (type == ENTITY_TYPE_ICE_CUBE_PLAYER_BAT_RIGHT)               ||             \
  (type == ENTITY_TYPE_ICE_CUBE_PLAYER_BAT_UP)                  ||             \
  (type == ENTITY_TYPE_ICE_CUBE_PLAYER_BAT_LEFT)                ||             \
  (type == ENTITY_TYPE_ICE_CUBE_PLAYER_BAT_DOWN)

#define ENTITY_TYPE_IS_FLASK(type)                                             \
  (type == ENTITY_TYPE_AQUA_FORTIS)       ||                                   \
  (type == ENTITY_TYPE_AQUA_EXPLODIS)

#define ENTITY_TYPE_IS_SPIKE_DESTROYING(type)                                  \
  (type == ENTITY_TYPE_BOX_METAL)         ||                                   \
  (type == ENTITY_TYPE_POT_METAL)         ||                                   \
  (type == ENTITY_TYPE_AQUA_FORTIS)       ||                                   \
  (type == ENTITY_TYPE_AQUA_EXPLODIS)

#define ENTITY_TYPE_IS_FLYING(type)                                            \
  (type == ENTITY_TYPE_PLAYER_BAT)          ||                                 \
  (type == ENTITY_TYPE_DOUBLE_BAT)          ||                                 \
  (type == ENTITY_TYPE_REVERSE_DOUBLE_BAT)

#define ENTITY_TYPE_IS_FLOATING(type)                                          \
  (type == ENTITY_TYPE_GHOST)                   ||                             \
  (type == ENTITY_TYPE_MASK_HORIZONTAL)         ||                             \
  (type == ENTITY_TYPE_MASK_VERTICAL)           ||                             \
  (type == ENTITY_TYPE_FAERIE_HORIZONTAL)       ||                             \
  (type == ENTITY_TYPE_FAERIE_VERTICAL)         ||                             \
  (type == ENTITY_TYPE_UNDINE)                  ||                             \
  (type == ENTITY_TYPE_POLTERGEIST)             ||                             \
  (type == ENTITY_TYPE_WISP_LEFT_WALL)          ||                             \
  (type == ENTITY_TYPE_WISP_RIGHT_WALL)         ||                             \
  (type == ENTITY_TYPE_BLOOD_VIAL)              ||                             \
  (type == ENTITY_TYPE_BAT_VIAL)                ||                             \
  (type == ENTITY_TYPE_BLUE_MANA)               ||                             \
  (type == ENTITY_TYPE_GREEN_MANA)              ||                             \
  (type == ENTITY_TYPE_FLOPPY_DISK_3_AND_1_2)   ||                             \
  (type == ENTITY_TYPE_FLOPPY_DISK_5_AND_1_4)

#define ENTITY_TYPE_IS_CONVEYABLE(type)                                        \
  ENTITY_TYPE_IS_PUSHABLE_OBJECT(type)          ||                             \
  ENTITY_TYPE_IS_ICE_CUBE(type)                 ||                             \
  (type == ENTITY_TYPE_PLAYER_VAMPIRE)          ||                             \
  (type == ENTITY_TYPE_PUMPKIN)                 ||                             \
  (type == ENTITY_TYPE_SNAKE)                   ||                             \
  (type == ENTITY_TYPE_DOUBLE_VAMPIRE)          ||                             \
  (type == ENTITY_TYPE_REVERSE_DOUBLE_VAMPIRE)  ||                             \
  (type == ENTITY_TYPE_VENUSIAN)                ||                             \
  (type == ENTITY_TYPE_WITCH)                   ||                             \
  (type == ENTITY_TYPE_SORCERESS)               ||                             \
  (type == ENTITY_TYPE_FROG)                    ||                             \
  (type == ENTITY_TYPE_IMP_LT)                  ||                             \
  (type == ENTITY_TYPE_IMP_RT)                  ||                             \
  (type == ENTITY_TYPE_LIL_BOT)                 ||                             \
  (type == ENTITY_TYPE_JIANGSHI_LT)             ||                             \
  (type == ENTITY_TYPE_JIANGSHI_RT)             ||                             \
  (type == ENTITY_TYPE_MUMMY_LT)                ||                             \
  (type == ENTITY_TYPE_MUMMY_RT)                ||                             \
  (type == ENTITY_TYPE_GUARDIAN_LT)             ||                             \
  (type == ENTITY_TYPE_GUARDIAN_RT)

#define ENTITY_TYPE_IS_SPELL(type)                                             \
  (type == ENTITY_TYPE_FIRE_SPELL)              ||                             \
  (type == ENTITY_TYPE_ICE_SPELL)               ||                             \
  (type == ENTITY_TYPE_NEUTRAL_SPELL)           ||                             \
  (type == ENTITY_TYPE_WARP_SPELL)              ||                             \
  (type == ENTITY_TYPE_BALLISTA_BOLT)           ||                             \
  (type == ENTITY_TYPE_LASER_SHOT)              ||                             \
  (type == ENTITY_TYPE_EVIL_EYE)

#define ENTITY_TYPE_IS_ELEMENTAL_SPELL(type)                                   \
  (type == ENTITY_TYPE_FIRE_SPELL)              ||                             \
  (type == ENTITY_TYPE_ICE_SPELL)               ||                             \
  (type == ENTITY_TYPE_NEUTRAL_SPELL)           ||                             \
  (type == ENTITY_TYPE_BALLISTA_BOLT)

#define ENTITY_TYPE_IS_STONE(type)                                             \
  (type == ENTITY_TYPE_BOX_STONE)     ||                                       \
  (type == ENTITY_TYPE_POT_STONE)

#define ENTITY_TYPE_IS_ARROWS(type)                                            \
  (type == ENTITY_TYPE_ARROWS_RED)    ||                                       \
  (type == ENTITY_TYPE_ARROWS_GREEN)  ||                                       \
  (type == ENTITY_TYPE_ARROWS_BROWN)

#define ENTITY_TYPE_IS_BALLISTA(type)                                          \
  (type == ENTITY_TYPE_BALLISTA_RED)    ||                                     \
  (type == ENTITY_TYPE_BALLISTA_GREEN)  ||                                     \
  (type == ENTITY_TYPE_BALLISTA_BROWN)

#define ENTITY_TYPE_IS_PINBALL_KICKER(type)                                    \
  (type == ENTITY_TYPE_BAR_KICKER_RED)          ||                             \
  (type == ENTITY_TYPE_BAR_KICKER_GREEN)        ||                             \
  (type == ENTITY_TYPE_BAR_KICKER_BROWN)        ||                             \
  (type == ENTITY_TYPE_TRIANGLE_KICKER_RED)     ||                             \
  (type == ENTITY_TYPE_TRIANGLE_KICKER_GREEN)   ||                             \
  (type == ENTITY_TYPE_TRIANGLE_KICKER_BROWN)

#define ENTITY_TYPE_IS_ONE_SIDED_REFLECTER(type)                               \
  (type == ENTITY_TYPE_GUARDIAN_LT)               ||                           \
  (type == ENTITY_TYPE_GUARDIAN_RT)               ||                           \
  (type == ENTITY_TYPE_TRIANGLE_KICKER_RED)       ||                           \
  (type == ENTITY_TYPE_TRIANGLE_KICKER_GREEN)     ||                           \
  (type == ENTITY_TYPE_TRIANGLE_KICKER_BROWN)

#define ENTITY_TYPE_IS_DOUBLE_SIDED_REFLECTER(type)                            \
  (type == ENTITY_TYPE_PRISM_BLOCK_0)           ||                             \
  (type == ENTITY_TYPE_PRISM_BLOCK_45)          ||                             \
  (type == ENTITY_TYPE_PRISM_BLOCK_90)          ||                             \
  (type == ENTITY_TYPE_PRISM_BLOCK_135)         ||                             \
  (type == ENTITY_TYPE_BAR_KICKER_RED)          ||                             \
  (type == ENTITY_TYPE_BAR_KICKER_GREEN)        ||                             \
  (type == ENTITY_TYPE_BAR_KICKER_BROWN)

#define ENTITY_TYPE_IS_LEVER(type)                                             \
  (type == ENTITY_TYPE_LEVER_WHITE)   ||                                       \
  (type == ENTITY_TYPE_LEVER_CYAN)    ||                                       \
  (type == ENTITY_TYPE_LEVER_MAGENTA)

#define ENTITY_TYPE_IS_SPIN_SWITCH(type)                                       \
  (type == ENTITY_TYPE_SPIN_SWITCH_RED_CCW)     ||                             \
  (type == ENTITY_TYPE_SPIN_SWITCH_RED_CW)      ||                             \
  (type == ENTITY_TYPE_SPIN_SWITCH_GREEN_CCW)   ||                             \
  (type == ENTITY_TYPE_SPIN_SWITCH_GREEN_CW)    ||                             \
  (type == ENTITY_TYPE_SPIN_SWITCH_BROWN_CCW)   ||                             \
  (type == ENTITY_TYPE_SPIN_SWITCH_BROWN_CW)

#define ENTITY_TYPE_IS_NUMBER_SWITCH(type)                                     \
  (type == ENTITY_TYPE_NUMBER_SWITCH_EVEN)        ||                           \
  (type == ENTITY_TYPE_NUMBER_SWITCH_ODD)         ||                           \
  (type == ENTITY_TYPE_NUMBER_SWITCH_PRIME)       ||                           \
  (type == ENTITY_TYPE_NUMBER_SWITCH_COMPOSITE)   ||                           \
  (type == ENTITY_TYPE_NUMBER_SWITCH_SQUARE)      ||                           \
  (type == ENTITY_TYPE_NUMBER_SWITCH_TRIANGULAR)

#define ENTITY_TYPE_IS_CONVEYER(type)                                          \
  (type == ENTITY_TYPE_CONVEYER_WHITE)            ||                           \
  (type == ENTITY_TYPE_CONVEYER_CYAN)             ||                           \
  (type == ENTITY_TYPE_CONVEYER_MAGENTA)

#define ENTITY_TYPE_IS_FLOOR_SPIKE_DOWN(type)                                  \
  (type == ENTITY_TYPE_FLOOR_SPIKE_DOWN_WHITE)    ||                           \
  (type == ENTITY_TYPE_FLOOR_SPIKE_DOWN_CYAN)     ||                           \
  (type == ENTITY_TYPE_FLOOR_SPIKE_DOWN_MAGENTA)

#define ENTITY_TYPE_IS_FLOOR_SPIKE_UP(type)                                    \
  (type == ENTITY_TYPE_FLOOR_SPIKE_UP_WHITE)      ||                           \
  (type == ENTITY_TYPE_FLOOR_SPIKE_UP_CYAN)       ||                           \
  (type == ENTITY_TYPE_FLOOR_SPIKE_UP_MAGENTA)

#define ENTITY_TYPE_IS_BRIDGE(type)                                            \
  (type == ENTITY_TYPE_BRIDGE_STONE_VERTICAL)     ||                           \
  (type == ENTITY_TYPE_BRIDGE_WOOD_VERTICAL)      ||                           \
  (type == ENTITY_TYPE_BRIDGE_CRACKED_VERTICAL)   ||                           \
  (type == ENTITY_TYPE_BRIDGE_STONE_HORIZONTAL)   ||                           \
  (type == ENTITY_TYPE_BRIDGE_WOOD_HORIZONTAL)    ||                           \
  (type == ENTITY_TYPE_BRIDGE_CRACKED_HORIZONTAL)

#define ENTITY_TYPE_IS_WOOD_OR_CRACKED_BRIDGE(type)                            \
  (type == ENTITY_TYPE_BRIDGE_WOOD_VERTICAL)      ||                           \
  (type == ENTITY_TYPE_BRIDGE_CRACKED_VERTICAL)   ||                           \
  (type == ENTITY_TYPE_BRIDGE_WOOD_HORIZONTAL)    ||                           \
  (type == ENTITY_TYPE_BRIDGE_CRACKED_HORIZONTAL)

#define ENTITY_TYPE_IS_SUBMERGED(type)                                         \
  (type == ENTITY_TYPE_BOX_WOOD_SUBMERGED)            ||                       \
  (type == ENTITY_TYPE_BOX_METAL_SUBMERGED)           ||                       \
  (type == ENTITY_TYPE_BOX_TNT_SUBMERGED)             ||                       \
  (type == ENTITY_TYPE_BOX_STONE_SUBMERGED)           ||                       \
  (type == ENTITY_TYPE_PRISM_BLOCK_0_SUBMERGED)       ||                       \
  (type == ENTITY_TYPE_PRISM_BLOCK_45_SUBMERGED)      ||                       \
  (type == ENTITY_TYPE_PRISM_BLOCK_90_SUBMERGED)      ||                       \
  (type == ENTITY_TYPE_PRISM_BLOCK_135_SUBMERGED)     ||                       \
  ENTITY_TYPE_IS_SOLID_DIE_SUBMERGED(type)            ||                       \
  (type == ENTITY_TYPE_MAHJONG_TILE_EAST_SUBMERGED)   ||                       \
  (type == ENTITY_TYPE_MAHJONG_TILE_NORTH_SUBMERGED)  ||                       \
  (type == ENTITY_TYPE_MAHJONG_TILE_WEST_SUBMERGED)   ||                       \
  (type == ENTITY_TYPE_MAHJONG_TILE_SOUTH_SUBMERGED)  ||                       \
  (type == ENTITY_TYPE_SPELLBINDER_EMPTY_SUBMERGED)   ||                       \
  (type == ENTITY_TYPE_SPELLBINDER_FIRE_SUBMERGED)    ||                       \
  (type == ENTITY_TYPE_SPELLBINDER_ICE_SUBMERGED)     ||                       \
  (type == ENTITY_TYPE_SPELLBINDER_NEUTRAL_SUBMERGED) ||                       \
  (type == ENTITY_TYPE_ICE_CUBE_SUBMERGED)

#define ENTITY_TYPE_IS_SUBMERGABLE(type)                                       \
  (type == ENTITY_TYPE_BOX_WOOD)            ||                                 \
  (type == ENTITY_TYPE_BOX_METAL)           ||                                 \
  (type == ENTITY_TYPE_BOX_TNT)             ||                                 \
  (type == ENTITY_TYPE_BOX_STONE)           ||                                 \
  (type == ENTITY_TYPE_PRISM_BLOCK_0)       ||                                 \
  (type == ENTITY_TYPE_PRISM_BLOCK_45)      ||                                 \
  (type == ENTITY_TYPE_PRISM_BLOCK_90)      ||                                 \
  (type == ENTITY_TYPE_PRISM_BLOCK_135)     ||                                 \
  ENTITY_TYPE_IS_SOLID_DIE(type)            ||                                 \
  ENTITY_TYPE_IS_VANISHED_DIE(type)         ||                                 \
  (type == ENTITY_TYPE_MAHJONG_TILE_EAST)   ||                                 \
  (type == ENTITY_TYPE_MAHJONG_TILE_NORTH)  ||                                 \
  (type == ENTITY_TYPE_MAHJONG_TILE_WEST)   ||                                 \
  (type == ENTITY_TYPE_MAHJONG_TILE_SOUTH)  ||                                 \
  (type == ENTITY_TYPE_SPELLBINDER_EMPTY)   ||                                 \
  (type == ENTITY_TYPE_SPELLBINDER_FIRE)    ||                                 \
  (type == ENTITY_TYPE_SPELLBINDER_ICE)     ||                                 \
  (type == ENTITY_TYPE_SPELLBINDER_NEUTRAL) ||                                 \
  ENTITY_TYPE_IS_ICE_CUBE(type)

#define ENTITY_TYPE_IS_EXPLOSIVE(type)                                         \
  (type == ENTITY_TYPE_BOX_TNT)           ||                                   \
  (type == ENTITY_TYPE_POT_TNT)           ||                                   \
  (type == ENTITY_TYPE_AQUA_EXPLODIS)     ||                                   \
  (type == ENTITY_TYPE_WISP_LEFT_WALL)    ||                                   \
  (type == ENTITY_TYPE_WISP_RIGHT_WALL)   ||                                   \
  (type == ENTITY_TYPE_LASER_SHOT)

#define ENTITY_TYPE_IS_PICKUP(type)                                            \
  (type == ENTITY_TYPE_BLOOD_VIAL)                ||                           \
  (type == ENTITY_TYPE_BAT_VIAL)                  ||                           \
  (type == ENTITY_TYPE_BLUE_MANA)                 ||                           \
  (type == ENTITY_TYPE_GREEN_MANA)                ||                           \
  (type == ENTITY_TYPE_FLOPPY_DISK_3_AND_1_2)     ||                           \
  (type == ENTITY_TYPE_FLOPPY_DISK_5_AND_1_4)     ||                           \
  (type == ENTITY_TYPE_COBWEB)

#define ENTITY_TYPE_IS_LEVEL_BOUNDARY(type)                                    \
  (type == ENTITY_TYPE_OUTER_WALL_TOP_LEFT)       ||                           \
  (type == ENTITY_TYPE_OUTER_WALL_TOP)            ||                           \
  (type == ENTITY_TYPE_OUTER_WALL_TOP_RIGHT)      ||                           \
  (type == ENTITY_TYPE_OUTER_WALL_RIGHT)          ||                           \
  (type == ENTITY_TYPE_OUTER_WALL_LEFT)           ||                           \
  (type == ENTITY_TYPE_OUTER_WALL_BOTTOM_LEFT)    ||                           \
  (type == ENTITY_TYPE_OUTER_WALL_BOTTOM)         ||                           \
  (type == ENTITY_TYPE_OUTER_WALL_BOTTOM_RIGHT)   ||                           \
  (type == ENTITY_TYPE_INNER_WALL_TOP)            ||                           \
  (type == ENTITY_TYPE_INNER_WALL_BOTTOM)         ||                           \
  (type == ENTITY_TYPE_PORTCULLIS_CLOSED)         ||                           \
  (type == ENTITY_TYPE_PORTCULLIS_OPEN)

#define ENTITY_TYPE_IS_UNWARPABLE(type)                                        \
  ENTITY_TYPE_IS_LEVEL_BOUNDARY(type)             ||                           \
  (type == ENTITY_TYPE_WARP_SPELL)                ||                           \
  (type == ENTITY_TYPE_EXPLOSION)

#define ENTITY_TYPE_HAS_RED_FIREWORK(type)                                     \
  (type == ENTITY_TYPE_CANDLE_LIT)                ||                           \
  (type == ENTITY_TYPE_ARROWS_RED)                ||                           \
  (type == ENTITY_TYPE_BALLISTA_RED)              ||                           \
  (type == ENTITY_TYPE_BAR_KICKER_RED)            ||                           \
  (type == ENTITY_TYPE_TRIANGLE_KICKER_RED)       ||                           \
  (type == ENTITY_TYPE_SPIN_SWITCH_RED_CCW)       ||                           \
  (type == ENTITY_TYPE_SPIN_SWITCH_RED_CW)        ||                           \
  (type == ENTITY_TYPE_FAERIE_VERTICAL)           ||                           \
  (type == ENTITY_TYPE_JIANGSHI_LT)               ||                           \
  (type == ENTITY_TYPE_JIANGSHI_RT)               ||                           \
  (type == ENTITY_TYPE_FIRE_SPELL)

#define ENTITY_TYPE_HAS_CYAN_FIREWORK(type)                                    \
  ENTITY_TYPE_IS_ICE_CUBE(type)                   ||                           \
  (type == ENTITY_TYPE_BOX_METAL)                 ||                           \
  (type == ENTITY_TYPE_POT_METAL)                 ||                           \
  (type == ENTITY_TYPE_LEVER_CYAN)                ||                           \
  (type == ENTITY_TYPE_UNDINE)                    ||                           \
  (type == ENTITY_TYPE_ICE_SPELL)

#define ENTITY_TYPE_HAS_GREEN_FIREWORK(type)                                   \
  (type == ENTITY_TYPE_ARROWS_GREEN)              ||                           \
  (type == ENTITY_TYPE_BALLISTA_GREEN)            ||                           \
  (type == ENTITY_TYPE_BAR_KICKER_GREEN)          ||                           \
  (type == ENTITY_TYPE_TRIANGLE_KICKER_GREEN)     ||                           \
  (type == ENTITY_TYPE_SPIN_SWITCH_GREEN_CCW)     ||                           \
  (type == ENTITY_TYPE_SPIN_SWITCH_GREEN_CW)      ||                           \
  (type == ENTITY_TYPE_SNAKE)                     ||                           \
  (type == ENTITY_TYPE_VENUSIAN)                  ||                           \
  (type == ENTITY_TYPE_FROG)                      ||                           \
  (type == ENTITY_TYPE_IMP_LT)                    ||                           \
  (type == ENTITY_TYPE_IMP_RT)                    ||                           \
  (type == ENTITY_TYPE_WARP_SPELL)

#define ENTITY_TYPE_HAS_MAGENTA_FIREWORK(type)                                 \
  (type == ENTITY_TYPE_PRISM_BLOCK_0)             ||                           \
  (type == ENTITY_TYPE_PRISM_BLOCK_45)            ||                           \
  (type == ENTITY_TYPE_PRISM_BLOCK_90)            ||                           \
  (type == ENTITY_TYPE_PRISM_BLOCK_135)           ||                           \
  (type == ENTITY_TYPE_LEVER_MAGENTA)             ||                           \
  (type == ENTITY_TYPE_FAERIE_HORIZONTAL)         ||                           \
  (type == ENTITY_TYPE_VENUSIAN_ROOT)             ||                           \
  (type == ENTITY_TYPE_NEUTRAL_SPELL)

#define ENTITY_TYPE_HAS_BROWN_FIREWORK(type)                                   \
  (type == ENTITY_TYPE_BRIDGE_WOOD_VERTICAL)      ||                           \
  (type == ENTITY_TYPE_BRIDGE_CRACKED_VERTICAL)   ||                           \
  (type == ENTITY_TYPE_BRIDGE_WOOD_HORIZONTAL)    ||                           \
  (type == ENTITY_TYPE_BRIDGE_CRACKED_HORIZONTAL) ||                           \
  (type == ENTITY_TYPE_BOX_WOOD)                  ||                           \
  (type == ENTITY_TYPE_POT_CLAY)                  ||                           \
  (type == ENTITY_TYPE_ARROWS_BROWN)              ||                           \
  (type == ENTITY_TYPE_BALLISTA_BROWN)            ||                           \
  (type == ENTITY_TYPE_BAR_KICKER_BROWN)          ||                           \
  (type == ENTITY_TYPE_TRIANGLE_KICKER_BROWN)     ||                           \
  (type == ENTITY_TYPE_SPIN_SWITCH_BROWN_CCW)     ||                           \
  (type == ENTITY_TYPE_SPIN_SWITCH_BROWN_CW)      ||                           \
  (type == ENTITY_TYPE_POLTERGEIST)

#define ENTITY_TYPE_HAS_GRAY_FIREWORK(type)                                    \
  (type == ENTITY_TYPE_BLOCK)                     ||                           \
  (type == ENTITY_TYPE_PILLAR)                    ||                           \
  (type == ENTITY_TYPE_TREE)                      ||                           \
  (type == ENTITY_TYPE_JOKER_CARD)                ||                           \
  (type == ENTITY_TYPE_YIN_YANG)                  ||                           \
  (type == ENTITY_TYPE_BRIDGE_STONE_VERTICAL)     ||                           \
  (type == ENTITY_TYPE_BRIDGE_STONE_HORIZONTAL)   ||                           \
  (type == ENTITY_TYPE_BOX_STONE)                 ||                           \
  (type == ENTITY_TYPE_POT_STONE)                 ||                           \
  (type == ENTITY_TYPE_CANDLE_UNLIT)              ||                           \
  (type == ENTITY_TYPE_DIE_SOLID_1)               ||                           \
  (type == ENTITY_TYPE_DIE_SOLID_2)               ||                           \
  (type == ENTITY_TYPE_DIE_SOLID_3)               ||                           \
  (type == ENTITY_TYPE_DIE_SOLID_4)               ||                           \
  (type == ENTITY_TYPE_DIE_SOLID_5)               ||                           \
  (type == ENTITY_TYPE_DIE_SOLID_6)               ||                           \
  (type == ENTITY_TYPE_MAHJONG_TILE_EAST)         ||                           \
  (type == ENTITY_TYPE_MAHJONG_TILE_NORTH)        ||                           \
  (type == ENTITY_TYPE_MAHJONG_TILE_WEST)         ||                           \
  (type == ENTITY_TYPE_MAHJONG_TILE_SOUTH)        ||                           \
  (type == ENTITY_TYPE_SPELLBINDER_EMPTY)         ||                           \
  (type == ENTITY_TYPE_SPELLBINDER_FIRE)          ||                           \
  (type == ENTITY_TYPE_SPELLBINDER_ICE)           ||                           \
  (type == ENTITY_TYPE_SPELLBINDER_NEUTRAL)       ||                           \
  (type == ENTITY_TYPE_LEVER_WHITE)               ||                           \
  (type == ENTITY_TYPE_GHOST)                     ||                           \
  (type == ENTITY_TYPE_MASK_VERTICAL)             ||                           \
  (type == ENTITY_TYPE_MASK_HORIZONTAL)           ||                           \
  (type == ENTITY_TYPE_LIL_BOT)                   ||                           \
  (type == ENTITY_TYPE_LASER_GUN)                 ||                           \
  (type == ENTITY_TYPE_BALLISTA_BOLT)

#define ENTITY_TYPE_HAS_BLACK_FIREWORK(type)                                   \
  (type == ENTITY_TYPE_EIGHT_BALL)                ||                           \
  (type == ENTITY_TYPE_NUMBER_SWITCH_EVEN)        ||                           \
  (type == ENTITY_TYPE_NUMBER_SWITCH_ODD)         ||                           \
  (type == ENTITY_TYPE_NUMBER_SWITCH_PRIME)       ||                           \
  (type == ENTITY_TYPE_NUMBER_SWITCH_COMPOSITE)   ||                           \
  (type == ENTITY_TYPE_NUMBER_SWITCH_SQUARE)      ||                           \
  (type == ENTITY_TYPE_NUMBER_SWITCH_TRIANGULAR)  ||                           \
  (type == ENTITY_TYPE_WITCH)                     ||                           \
  (type == ENTITY_TYPE_GUARDIAN_LT)               ||                           \
  (type == ENTITY_TYPE_GUARDIAN_RT)

#define ENTITY_TYPE_HAS_YELLOW_FIREWORK(type)                                  \
  ENTITY_TYPE_IS_EXPLOSIVE(type)                  ||                           \
  (type == ENTITY_TYPE_SORCERESS)                 ||                           \
  (type == ENTITY_TYPE_MUMMY_LT)                  ||                           \
  (type == ENTITY_TYPE_MUMMY_RT)

#define ENTITY_TYPE_HAS_ORANGE_FIREWORK(type)                                  \
  (type == ENTITY_TYPE_AQUA_FORTIS)               ||                           \
  (type == ENTITY_TYPE_PUMPKIN)

#define ENTITY_TYPE_HAS_PLAYER_FIREWORK(type)                                  \
  (type == ENTITY_TYPE_PLAYER_VAMPIRE)            ||                           \
  (type == ENTITY_TYPE_PLAYER_BAT)

#define ENTITY_TYPE_HAS_DOUBLE_FIREWORK(type)                                  \
  (type == ENTITY_TYPE_DOUBLE_VAMPIRE)            ||                           \
  (type == ENTITY_TYPE_DOUBLE_BAT)

#define ENTITY_TYPE_HAS_REVERSE_DOUBLE_FIREWORK(type)                          \
  (type == ENTITY_TYPE_REVERSE_DOUBLE_VAMPIRE)    ||                           \
  (type == ENTITY_TYPE_REVERSE_DOUBLE_BAT)

#define ENTITY_FACING_CHECK(e, facing)                                         \
  ((e->orientation & ENTITY_FACING_MASK) == facing)

#define ENTITY_THETA_CHECK(e, theta)                                           \
  ((e->orientation & ENTITY_THETA_MASK) == theta)

#define ENTITY_DIRECTION_CHECK(e, direction)                                   \
  ((e->orientation & ENTITY_DIRECTION_MASK) == direction)

#define ENTITY_IS_PERFORMING_ACTION(e)                                         \
  (e->action_flags & ENTITY_ACTION_FLAG_MOVING)           ||                   \
  (e->action_flags & ENTITY_ACTION_FLAG_CASTING)          ||                   \
  (e->action_flags & ENTITY_ACTION_FLAG_ROTATING)         ||                   \
  (e->update_flags & ENTITY_UPDATE_FLAG_TRANSFORMING)     ||                   \
  (e->update_flags & ENTITY_UPDATE_FLAG_WALKING_IN_PLACE)

#define ENTITY_IS_IN_COOLDOWN(e)                                               \
  (e->update_flags & ENTITY_UPDATE_FLAG_COOLDOWN)

#define ENTITY_COOLDOWN_TIME_MAHJONG_TILE 60
#define ENTITY_COOLDOWN_TIME_LEVER        24
#define ENTITY_COOLDOWN_TIME_SWITCH       24
#define ENTITY_COOLDOWN_TIME_BALLISTA     56
#define ENTITY_COOLDOWN_TIME_SNAKE        32
#define ENTITY_COOLDOWN_TIME_VENUSIAN     540
#define ENTITY_COOLDOWN_TIME_WITCH        32
#define ENTITY_COOLDOWN_TIME_UNDINE       32
#define ENTITY_COOLDOWN_TIME_SORCERESS    48
#define ENTITY_COOLDOWN_TIME_WISP         48
#define ENTITY_COOLDOWN_TIME_MUMMY        32
#define ENTITY_COOLDOWN_TIME_LASER_GUN    32
#define ENTITY_COOLDOWN_TIME_VAMPIRE      16
#define ENTITY_COOLDOWN_TIME_ICE_CUBE     360
#define ENTITY_COOLDOWN_TIME_EXPLOSION    48

#define ENTITY_SPIN_TIME_ARROWS           12
#define ENTITY_SPIN_TIME_BALLISTA         12
#define ENTITY_SPIN_TIME_PINBALL_KICKER   12
#define ENTITY_SPIN_TIME_LASER_GUN        12

typedef struct entity
{
  /* list pointers and id */
  struct entity*  next;
  struct entity*  prev;
  int             id;

  /* entity type and flags */
  int             type;
  unsigned char   update_flags;
  unsigned char   action_flags;
  unsigned char   special_flags;
  unsigned char   animation_flags;
  unsigned char   move_attribute;
  unsigned char   move_affect;
  unsigned char   trigger_attribute;
  unsigned char   trigger_affect;
  unsigned char   damage_attribute;
  unsigned char   damage_affect;
  unsigned char   collision_flags;
  unsigned char   orientation;

  /* position and velocity */
  int             pos_x;
  int             pos_y;
  int             vel_x;
  int             vel_y;

  /* hitpoints */
  int             hp;

  /* countdown timers */
  int             move_count;
  int             cooldown_count;
  int             spin_count;
  int             frame_count;

  /* half-width and half-height */
  int             rx;
  int             ry;

  /* current frame (tile number on sprite sheet) */
  int             tile;

  /* animation variables */
  unsigned char*  animation_array;
  int             frame_length;
  int             animation_length;
} entity;

/* function declarations */
short int entity_init(entity* e);
entity*   entity_create();
short int entity_deinit(entity* e);
short int entity_destroy(entity* e);

short int entity_reset(entity* e);
short int entity_set_type(entity* e, int type);
short int entity_set_facing(entity* e, unsigned char facing);

#endif
