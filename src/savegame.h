/*******************************************************************************
** savegame.h (save games)
*******************************************************************************/

#ifndef SAVE_GAME_H
#define SAVE_GAME_H

#define SAVE_GAME_FLAGS_CLEAR     0x00
#define SAVE_GAME_FLAG_ROOM_1     0x01
#define SAVE_GAME_FLAG_ROOM_2     0x02
#define SAVE_GAME_FLAG_ROOM_3     0x04
#define SAVE_GAME_FLAG_ROOM_4     0x08
#define SAVE_GAME_FLAG_ROOM_5     0x10
#define SAVE_GAME_FLAG_FLOOR_1    0x20
#define SAVE_GAME_FLAG_FLOOR_2    0x40
#define SAVE_GAME_FLAG_FLOPPY     0x80

#define SAVE_GAME_MASK_ROOMS      0x1F
#define SAVE_GAME_MASK_FLOORS     0x60

#if 0
#define SAVE_GAME_WORLD_IS_COMPLETE(num)                                       \
  (G_save_game_flags[num] & (SAVE_GAME_MASK_FLOORS | SAVE_GAME_MASK_ROOMS)) == \
  (SAVE_GAME_MASK_FLOORS | SAVE_GAME_MASK_ROOMS)
#endif

#define SAVE_GAME_WORLD_IS_COMPLETE(num)                                       \
  (G_save_game_flags[num] & SAVE_GAME_MASK_FLOORS) == SAVE_GAME_MASK_FLOORS

extern unsigned char  G_save_game_number;

extern unsigned char  G_save_game_percentage;
extern unsigned char  G_save_game_3_and_1_2_floppies;
extern unsigned char  G_save_game_5_and_1_4_floppies;

extern unsigned char  G_save_game_flags[22];
extern unsigned char  G_save_game_best_times[330];

/* function declarations */
short int save_game_init();
short int save_game_deinit();
short int save_game_reset();
short int save_game_compute_completion_percentage_and_floppy_counts();
short int save_game_mark_current_level_complete();
short int save_game_mark_current_floppy_obtained();
short int save_game_record_best_time(unsigned char new_time);
short int save_game_read();
short int save_game_write();

#endif
