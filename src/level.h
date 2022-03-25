/*******************************************************************************
** level.h (level)
*******************************************************************************/

#ifndef LEVEL_H
#define LEVEL_H

#define LEVEL_TILE_FLOOR                      0x00
#define LEVEL_TILE_GRASS                      0x01
#define LEVEL_TILE_WATER                      0x02
#define LEVEL_TILE_ICE                        0x03
#define LEVEL_TILE_COBWEB                     0x04
#define LEVEL_TILE_JOKER_CARD                 0x05
#define LEVEL_TILE_SEAL_OF_SOLOMON            0x06
#define LEVEL_TILE_YIN_YANG                   0x07
#define LEVEL_TILE_BLOCK                      0x08
#define LEVEL_TILE_PILLAR                     0x09
#define LEVEL_TILE_TREE                       0x0A
#define LEVEL_TILE_BRIDGE_STONE_VERTICAL      0x0B
#define LEVEL_TILE_BRIDGE_WOOD_VERTICAL       0x0C
#define LEVEL_TILE_BRIDGE_CRACKED_VERTICAL    0x0D

#define LEVEL_TILE_BOX_WOOD                   0x10
#define LEVEL_TILE_BOX_METAL                  0x11
#define LEVEL_TILE_BOX_TNT                    0x12
#define LEVEL_TILE_BOX_STONE                  0x13
#define LEVEL_TILE_POT_CLAY                   0x14
#define LEVEL_TILE_POT_METAL                  0x15
#define LEVEL_TILE_POT_TNT                    0x16
#define LEVEL_TILE_POT_STONE                  0x17
#define LEVEL_TILE_AQUA_FORTIS                0x18
#define LEVEL_TILE_AQUA_EXPLODIS              0x19
#define LEVEL_TILE_CANDLE_UNLIT               0x1A
#define LEVEL_TILE_CANDLE_LIT                 0x1B
#define LEVEL_TILE_PRISM_BLOCK_0              0x1C
#define LEVEL_TILE_PRISM_BLOCK_45             0x1D
#define LEVEL_TILE_PRISM_BLOCK_90             0x1E
#define LEVEL_TILE_PRISM_BLOCK_135            0x1F

#define LEVEL_TILE_EIGHT_BALL                 0x20
#define LEVEL_TILE_VANISHING_DIE_1            0x21
#define LEVEL_TILE_VANISHING_DIE_2            0x22
#define LEVEL_TILE_VANISHING_DIE_3            0x23
#define LEVEL_TILE_VANISHING_DIE_4            0x24
#define LEVEL_TILE_VANISHING_DIE_5            0x25
#define LEVEL_TILE_VANISHING_DIE_6            0x26
#define LEVEL_TILE_MAHJONG_EAST               0x27
#define LEVEL_TILE_MAHJONG_NORTH              0x28
#define LEVEL_TILE_MAHJONG_WEST               0x29
#define LEVEL_TILE_MAHJONG_SOUTH              0x2A
#define LEVEL_TILE_SPELLBINDER                0x2B
#define LEVEL_TILE_BRIDGE_STONE_HORIZONTAL    0x2C
#define LEVEL_TILE_BRIDGE_WOOD_HORIZONTAL     0x2D
#define LEVEL_TILE_BRIDGE_CRACKED_HORIZONTAL  0x2E

#define LEVEL_TILE_ARROWS_RED_RIGHT           0x30
#define LEVEL_TILE_ARROWS_RED_UP              0x31
#define LEVEL_TILE_ARROWS_RED_LEFT            0x32
#define LEVEL_TILE_ARROWS_RED_DOWN            0x33
#define LEVEL_TILE_ARROWS_GREEN_RIGHT         0x34
#define LEVEL_TILE_ARROWS_GREEN_UP            0x35
#define LEVEL_TILE_ARROWS_GREEN_LEFT          0x36
#define LEVEL_TILE_ARROWS_GREEN_DOWN          0x37
#define LEVEL_TILE_ARROWS_BROWN_RIGHT         0x38
#define LEVEL_TILE_ARROWS_BROWN_UP            0x39
#define LEVEL_TILE_ARROWS_BROWN_LEFT          0x3A
#define LEVEL_TILE_ARROWS_BROWN_DOWN          0x3B
#define LEVEL_TILE_BAR_KICKER_RED_0           0x3C
#define LEVEL_TILE_BAR_KICKER_RED_45          0x3D
#define LEVEL_TILE_BAR_KICKER_RED_90          0x3E
#define LEVEL_TILE_BAR_KICKER_RED_135         0x3F

#define LEVEL_TILE_BAR_KICKER_GREEN_0         0x40
#define LEVEL_TILE_BAR_KICKER_GREEN_45        0x41
#define LEVEL_TILE_BAR_KICKER_GREEN_90        0x42
#define LEVEL_TILE_BAR_KICKER_GREEN_135       0x43
#define LEVEL_TILE_BAR_KICKER_BROWN_0         0x44
#define LEVEL_TILE_BAR_KICKER_BROWN_45        0x45
#define LEVEL_TILE_BAR_KICKER_BROWN_90        0x46
#define LEVEL_TILE_BAR_KICKER_BROWN_135       0x47
#define LEVEL_TILE_TRIANGLE_KICKER_RED_45     0x48
#define LEVEL_TILE_TRIANGLE_KICKER_RED_135    0x49
#define LEVEL_TILE_TRIANGLE_KICKER_RED_225    0x4A
#define LEVEL_TILE_TRIANGLE_KICKER_RED_315    0x4B
#define LEVEL_TILE_TRIANGLE_KICKER_GREEN_45   0x4C
#define LEVEL_TILE_TRIANGLE_KICKER_GREEN_135  0x4D
#define LEVEL_TILE_TRIANGLE_KICKER_GREEN_225  0x4E
#define LEVEL_TILE_TRIANGLE_KICKER_GREEN_315  0x4F

#define LEVEL_TILE_BALLISTA_RED_RIGHT         0x50
#define LEVEL_TILE_BALLISTA_RED_UP            0x51
#define LEVEL_TILE_BALLISTA_RED_LEFT          0x52
#define LEVEL_TILE_BALLISTA_RED_DOWN          0x53
#define LEVEL_TILE_BALLISTA_GREEN_RIGHT       0x54
#define LEVEL_TILE_BALLISTA_GREEN_UP          0x55
#define LEVEL_TILE_BALLISTA_GREEN_LEFT        0x56
#define LEVEL_TILE_BALLISTA_GREEN_DOWN        0x57
#define LEVEL_TILE_BALLISTA_BROWN_RIGHT       0x58
#define LEVEL_TILE_BALLISTA_BROWN_UP          0x59
#define LEVEL_TILE_BALLISTA_BROWN_LEFT        0x5A
#define LEVEL_TILE_BALLISTA_BROWN_DOWN        0x5B
#define LEVEL_TILE_CONVEYER_OFF_RIGHT_WHITE   0x5C
#define LEVEL_TILE_CONVEYER_OFF_UP_WHITE      0x5D
#define LEVEL_TILE_CONVEYER_OFF_LEFT_WHITE    0x5E
#define LEVEL_TILE_CONVEYER_OFF_DOWN_WHITE    0x5F

#define LEVEL_TILE_CONVEYER_ON_RIGHT_WHITE    0x60
#define LEVEL_TILE_CONVEYER_ON_UP_WHITE       0x61
#define LEVEL_TILE_CONVEYER_ON_LEFT_WHITE     0x62
#define LEVEL_TILE_CONVEYER_ON_DOWN_WHITE     0x63
#define LEVEL_TILE_CONVEYER_OFF_RIGHT_CYAN    0x64
#define LEVEL_TILE_CONVEYER_OFF_UP_CYAN       0x65
#define LEVEL_TILE_CONVEYER_OFF_LEFT_CYAN     0x66
#define LEVEL_TILE_CONVEYER_OFF_DOWN_CYAN     0x67
#define LEVEL_TILE_CONVEYER_ON_RIGHT_CYAN     0x68
#define LEVEL_TILE_CONVEYER_ON_UP_CYAN        0x69
#define LEVEL_TILE_CONVEYER_ON_LEFT_CYAN      0x6A
#define LEVEL_TILE_CONVEYER_ON_DOWN_CYAN      0x6B
#define LEVEL_TILE_CONVEYER_OFF_RIGHT_MAGENTA 0x6C
#define LEVEL_TILE_CONVEYER_OFF_UP_MAGENTA    0x6D
#define LEVEL_TILE_CONVEYER_OFF_LEFT_MAGENTA  0x6E
#define LEVEL_TILE_CONVEYER_OFF_DOWN_MAGENTA  0x6F

#define LEVEL_TILE_CONVEYER_ON_RIGHT_MAGENTA  0x70
#define LEVEL_TILE_CONVEYER_ON_UP_MAGENTA     0x71
#define LEVEL_TILE_CONVEYER_ON_LEFT_MAGENTA   0x72
#define LEVEL_TILE_CONVEYER_ON_DOWN_MAGENTA   0x73
#define LEVEL_TILE_FLOOR_SPIKES_DOWN_WHITE    0x74
#define LEVEL_TILE_FLOOR_SPIKES_DOWN_CYAN     0x75
#define LEVEL_TILE_FLOOR_SPIKES_DOWN_MAGENTA  0x76
#define LEVEL_TILE_FLOOR_SPIKES_UP_WHITE      0x77
#define LEVEL_TILE_FLOOR_SPIKES_UP_CYAN       0x78
#define LEVEL_TILE_FLOOR_SPIKES_UP_MAGENTA    0x79
#define LEVEL_TILE_LEVER_LEFT_WHITE           0x7A
#define LEVEL_TILE_LEVER_LEFT_CYAN            0x7B
#define LEVEL_TILE_LEVER_LEFT_MAGENTA         0x7C
#define LEVEL_TILE_LEVER_RIGHT_WHITE          0x7D
#define LEVEL_TILE_LEVER_RIGHT_CYAN           0x7E
#define LEVEL_TILE_LEVER_RIGHT_MAGENTA        0x7F

#define LEVEL_TILE_SPIN_SWITCH_RED_CCW        0x80
#define LEVEL_TILE_SPIN_SWITCH_RED_CW         0x81
#define LEVEL_TILE_SPIN_SWITCH_GREEN_CCW      0x82
#define LEVEL_TILE_SPIN_SWITCH_GREEN_CW       0x83
#define LEVEL_TILE_SPIN_SWITCH_BROWN_CCW      0x84
#define LEVEL_TILE_SPIN_SWITCH_BROWN_CW       0x85
#define LEVEL_TILE_NUMBER_SWITCH_EVEN         0x86
#define LEVEL_TILE_NUMBER_SWITCH_ODD          0x87
#define LEVEL_TILE_NUMBER_SWITCH_PRIME        0x88
#define LEVEL_TILE_NUMBER_SWITCH_COMPOSITE    0x89
#define LEVEL_TILE_NUMBER_SWITCH_SQUARE       0x8A
#define LEVEL_TILE_NUMBER_SWITCH_TRIANGULAR   0x8B
#define LEVEL_TILE_TRIANGLE_KICKER_BROWN_45   0x8C
#define LEVEL_TILE_TRIANGLE_KICKER_BROWN_135  0x8D
#define LEVEL_TILE_TRIANGLE_KICKER_BROWN_225  0x8E
#define LEVEL_TILE_TRIANGLE_KICKER_BROWN_315  0x8F

#define LEVEL_TILE_PUMPKIN                    0x90
#define LEVEL_TILE_GHOST_RIGHT                0x91
#define LEVEL_TILE_GHOST_UP                   0x92
#define LEVEL_TILE_GHOST_LEFT                 0x93
#define LEVEL_TILE_GHOST_DOWN                 0x94
#define LEVEL_TILE_MASK_HORIZONTAL            0x95
#define LEVEL_TILE_MASK_VERTICAL              0x96
#define LEVEL_TILE_SNAKE_RIGHT                0x97
#define LEVEL_TILE_SNAKE_UP                   0x98
#define LEVEL_TILE_SNAKE_LEFT                 0x99
#define LEVEL_TILE_SNAKE_DOWN                 0x9A
#define LEVEL_TILE_DOUBLE                     0x9B
#define LEVEL_TILE_REVERSE_DOUBLE             0x9C
#define LEVEL_TILE_FAERIE_HORIZONTAL          0x9D
#define LEVEL_TILE_FAERIE_VERTICAL            0x9E
#define LEVEL_TILE_VENUSIAN                   0x9F

#define LEVEL_TILE_WITCH_RIGHT                0xA0
#define LEVEL_TILE_WITCH_UP                   0xA1
#define LEVEL_TILE_WITCH_LEFT                 0xA2
#define LEVEL_TILE_WITCH_DOWN                 0xA3
#define LEVEL_TILE_UNDINE_RIGHT               0xA4
#define LEVEL_TILE_UNDINE_UP                  0xA5
#define LEVEL_TILE_UNDINE_LEFT                0xA6
#define LEVEL_TILE_UNDINE_DOWN                0xA7
#define LEVEL_TILE_SORCERESS_RIGHT            0xA8
#define LEVEL_TILE_SORCERESS_UP               0xA9
#define LEVEL_TILE_SORCERESS_LEFT             0xAA
#define LEVEL_TILE_SORCERESS_DOWN             0xAB
#define LEVEL_TILE_FROG_RIGHT                 0xAC
#define LEVEL_TILE_FROG_UP                    0xAD
#define LEVEL_TILE_FROG_LEFT                  0xAE
#define LEVEL_TILE_FROG_DOWN                  0xAF

#define LEVEL_TILE_IMP_LEFT_TURN_0            0xB0
#define LEVEL_TILE_IMP_LEFT_TURN_90           0xB1
#define LEVEL_TILE_IMP_LEFT_TURN_180          0xB2
#define LEVEL_TILE_IMP_LEFT_TURN_270          0xB3
#define LEVEL_TILE_IMP_RIGHT_TURN_0           0xB4
#define LEVEL_TILE_IMP_RIGHT_TURN_90          0xB5
#define LEVEL_TILE_IMP_RIGHT_TURN_180         0xB6
#define LEVEL_TILE_IMP_RIGHT_TURN_270         0xB7
#define LEVEL_TILE_LIL_BOT_HORIZONTAL         0xB8
#define LEVEL_TILE_LIL_BOT_VERTICAL           0xB9
#define LEVEL_TILE_POLTERGEIST_HORIZONTAL     0xBA
#define LEVEL_TILE_POLTERGEIST_VERTICAL       0xBB
#define LEVEL_TILE_WISP_LEFT_WALL_0           0xBC
#define LEVEL_TILE_WISP_LEFT_WALL_90          0xBD
#define LEVEL_TILE_WISP_LEFT_WALL_180         0xBE
#define LEVEL_TILE_WISP_LEFT_WALL_270         0xBF

#define LEVEL_TILE_WISP_RIGHT_WALL_0          0xC0
#define LEVEL_TILE_WISP_RIGHT_WALL_90         0xC1
#define LEVEL_TILE_WISP_RIGHT_WALL_180        0xC2
#define LEVEL_TILE_WISP_RIGHT_WALL_270        0xC3
#define LEVEL_TILE_JIANGSHI_LEFT_TURN_0       0xC4
#define LEVEL_TILE_JIANGSHI_LEFT_TURN_90      0xC5
#define LEVEL_TILE_JIANGSHI_LEFT_TURN_180     0xC6
#define LEVEL_TILE_JIANGSHI_LEFT_TURN_270     0xC7
#define LEVEL_TILE_JIANGSHI_RIGHT_TURN_0      0xC8
#define LEVEL_TILE_JIANGSHI_RIGHT_TURN_90     0xC9
#define LEVEL_TILE_JIANGSHI_RIGHT_TURN_180    0xCA
#define LEVEL_TILE_JIANGSHI_RIGHT_TURN_270    0xCB
#define LEVEL_TILE_MUMMY_LEFT_TURN_0          0xCC
#define LEVEL_TILE_MUMMY_LEFT_TURN_90         0xCD
#define LEVEL_TILE_MUMMY_LEFT_TURN_180        0xCE
#define LEVEL_TILE_MUMMY_LEFT_TURN_270        0xCF

#define LEVEL_TILE_MUMMY_RIGHT_TURN_0         0xD0
#define LEVEL_TILE_MUMMY_RIGHT_TURN_90        0xD1
#define LEVEL_TILE_MUMMY_RIGHT_TURN_180       0xD2
#define LEVEL_TILE_MUMMY_RIGHT_TURN_270       0xD3
#define LEVEL_TILE_GUARDIAN_LEFT_TURN_0       0xD4
#define LEVEL_TILE_GUARDIAN_LEFT_TURN_90      0xD5
#define LEVEL_TILE_GUARDIAN_LEFT_TURN_180     0xD6
#define LEVEL_TILE_GUARDIAN_LEFT_TURN_270     0xD7
#define LEVEL_TILE_GUARDIAN_RIGHT_TURN_0      0xD8
#define LEVEL_TILE_GUARDIAN_RIGHT_TURN_90     0xD9
#define LEVEL_TILE_GUARDIAN_RIGHT_TURN_180    0xDA
#define LEVEL_TILE_GUARDIAN_RIGHT_TURN_270    0xDB
#define LEVEL_TILE_LASER_GUN                  0xDC

#define LEVEL_TILE_BLOOD_VIAL                 0xF0
#define LEVEL_TILE_BAT_VIAL                   0xF1
#define LEVEL_TILE_BLUE_MANA                  0xF2
#define LEVEL_TILE_GREEN_MANA                 0xF3
#define LEVEL_TILE_FLOPPY_DISK_3_AND_1_2      0xF4
#define LEVEL_TILE_FLOPPY_DISK_5_AND_1_4      0xF5

#define LEVEL_TILE_PLAYER_START               0xFF

#define LEVEL_WIDTH     11
#define LEVEL_HEIGHT    11
#define LEVEL_MAX_TILES (LEVEL_WIDTH * LEVEL_HEIGHT)

#define LEVEL_BORDER_FLAGS_CLEAR              0x00
#define LEVEL_BORDER_FLAG_TOP_LEFT            0x01
#define LEVEL_BORDER_FLAG_TOP                 0x02
#define LEVEL_BORDER_FLAG_TOP_RIGHT           0x04
#define LEVEL_BORDER_FLAG_LEFT                0x08
#define LEVEL_BORDER_FLAG_RIGHT               0x10
#define LEVEL_BORDER_FLAG_BOTTOM_LEFT         0x20
#define LEVEL_BORDER_FLAG_BOTTOM              0x40
#define LEVEL_BORDER_FLAG_BOTTOM_RIGHT        0x80

typedef struct level
{
  unsigned char tiles[LEVEL_MAX_TILES];
  unsigned char border[LEVEL_MAX_TILES];
  unsigned char portcullis_position;
  unsigned char par_time;
  int           theme;
} level;

extern level G_levels_all[330];

/* function declarations */
short int level_init(level* l);
level*    level_create();
short int level_deinit(level* l);
short int level_destroy(level* l);

short int level_generate_border(level* l);
short int level_load_to_world(level* l);

short int level_load_all_from_file(char* filename);

#endif
