/*******************************************************************************
** savegame.c (save games)
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "savegame.h"

unsigned char G_save_game_number;

unsigned char G_save_game_percentage;
unsigned char G_save_game_3_and_1_2_floppies;
unsigned char G_save_game_5_and_1_4_floppies;

unsigned char G_save_game_flags[22];
unsigned char G_save_game_best_times[330];

/*******************************************************************************
** save_game_init()
*******************************************************************************/
short int save_game_init()
{
  int i;

  G_save_game_number = 0;

  G_save_game_percentage = 0;
  G_save_game_3_and_1_2_floppies = 0;
  G_save_game_5_and_1_4_floppies = 0;

  for (i = 0; i < 22; i++)
    G_save_game_flags[i] = SAVE_GAME_FLAGS_CLEAR;

  for (i = 0; i < 330; i++)
    G_save_game_best_times[i] = 0;

  return 0;
}

/*******************************************************************************
** save_game_deinit()
*******************************************************************************/
short int save_game_deinit()
{
  int i;

  G_save_game_number = 0;

  G_save_game_percentage = 0;
  G_save_game_3_and_1_2_floppies = 0;
  G_save_game_5_and_1_4_floppies = 0;

  for (i = 0; i < 22; i++)
    G_save_game_flags[i] = SAVE_GAME_FLAGS_CLEAR;

  for (i = 0; i < 330; i++)
    G_save_game_best_times[i] = 0;

  return 0;
}

/*******************************************************************************
** save_game_reset()
*******************************************************************************/
short int save_game_reset()
{
  int i;

  G_save_game_percentage = 0;
  G_save_game_3_and_1_2_floppies = 0;
  G_save_game_5_and_1_4_floppies = 0;

  for (i = 0; i < 22; i++)
    G_save_game_flags[i] = SAVE_GAME_FLAGS_CLEAR;

  for (i = 0; i < 330; i++)
    G_save_game_best_times[i] = 0;

  return 0;
}

/*******************************************************************************
** save_game_compute_completion_percentage_and_floppy_counts()
*******************************************************************************/
short int save_game_compute_completion_percentage_and_floppy_counts()
{
  int i;
  int levels_completed;

  /* compute completion percentage */
  levels_completed = 0;

  for (i = 0; i < 22; i++)
  {
    if (G_save_game_flags[i] & SAVE_GAME_FLAG_FLOOR_1)
      levels_completed += 5;

    if (G_save_game_flags[i] & SAVE_GAME_FLAG_FLOOR_2)
      levels_completed += 5;

    if (G_save_game_flags[i] & SAVE_GAME_FLAG_ROOM_1)
      levels_completed += 1;

    if (G_save_game_flags[i] & SAVE_GAME_FLAG_ROOM_2)
      levels_completed += 1;

    if (G_save_game_flags[i] & SAVE_GAME_FLAG_ROOM_3)
      levels_completed += 1;

    if (G_save_game_flags[i] & SAVE_GAME_FLAG_ROOM_4)
      levels_completed += 1;

    if (G_save_game_flags[i] & SAVE_GAME_FLAG_ROOM_5)
      levels_completed += 1;
  }

  if (levels_completed < 0)
    levels_completed = 0;
  else if (levels_completed > 330)
    levels_completed = 330;

  G_save_game_percentage = (levels_completed * 100) / 330;

  /* compute number of 3 1/2 inch floppy disks collected */
  G_save_game_3_and_1_2_floppies = 0;

  for (i = 0; i < 18; i++)
  {
    if (G_save_game_flags[i] & SAVE_GAME_FLAG_FLOPPY)
      G_save_game_3_and_1_2_floppies += 1;
  }

  if (G_save_game_3_and_1_2_floppies < 0)
    G_save_game_3_and_1_2_floppies = 0;
  else if (G_save_game_3_and_1_2_floppies > 18)
    G_save_game_3_and_1_2_floppies = 18;

  /* compute number of 5 1/4 inch floppy disks collected */
  G_save_game_5_and_1_4_floppies = 0;

  for (i = 18; i < 21; i++)
  {
    if (G_save_game_flags[i] & SAVE_GAME_FLAG_FLOPPY)
      G_save_game_5_and_1_4_floppies += 1;
  }

  if (G_save_game_5_and_1_4_floppies < 0)
    G_save_game_5_and_1_4_floppies = 0;
  else if (G_save_game_5_and_1_4_floppies > 3)
    G_save_game_5_and_1_4_floppies = 3;

  return 0;
}

/*******************************************************************************
** save_game_mark_current_level_complete()
*******************************************************************************/
short int save_game_mark_current_level_complete()
{
  int world_index;
  int floor_index;
  int room_index;

  /* make sure this is a valid level index */
  if ((G_current_level_index < 0) || (G_current_level_index >= 330))
    return 1;

  /* determine current world and room */
  world_index = G_current_level_index / 15;
  floor_index = (G_current_level_index % 15) / 5;
  room_index = G_current_level_index % 5;

  /* set room to complete */
  if ((floor_index == 2) ||
      ((floor_index == 1) && 
      (!(G_save_game_flags[world_index] & SAVE_GAME_FLAG_FLOOR_2))) ||
      ((floor_index == 0) && 
      (!(G_save_game_flags[world_index] & SAVE_GAME_FLAG_FLOOR_1))))
  {
    if (room_index == 0)
      G_save_game_flags[world_index] |= SAVE_GAME_FLAG_ROOM_1;
    else if (room_index == 1)
      G_save_game_flags[world_index] |= SAVE_GAME_FLAG_ROOM_2;
    else if (room_index == 2)
      G_save_game_flags[world_index] |= SAVE_GAME_FLAG_ROOM_3;
    else if (room_index == 3)
      G_save_game_flags[world_index] |= SAVE_GAME_FLAG_ROOM_4;
    else if (room_index == 4)
      G_save_game_flags[world_index] |= SAVE_GAME_FLAG_ROOM_5;
  }

  /* if all rooms on the floor are complete, unlock next floor if possible */
  if ((G_save_game_flags[world_index] & SAVE_GAME_MASK_ROOMS) == 
      SAVE_GAME_MASK_ROOMS)
  {
    if ((floor_index == 0) && 
        (!(G_save_game_flags[world_index] & SAVE_GAME_FLAG_FLOOR_1)))
    {
      G_save_game_flags[world_index] &= ~SAVE_GAME_MASK_FLOORS;
      G_save_game_flags[world_index] |= SAVE_GAME_FLAG_FLOOR_1;
      G_save_game_flags[world_index] &= ~SAVE_GAME_MASK_ROOMS;
    }
    else if ( (floor_index == 1) && 
              (!(G_save_game_flags[world_index] & SAVE_GAME_FLAG_FLOOR_2)))
    {
      G_save_game_flags[world_index] &= ~SAVE_GAME_MASK_FLOORS;
      G_save_game_flags[world_index] |= SAVE_GAME_FLAG_FLOOR_1;
      G_save_game_flags[world_index] |= SAVE_GAME_FLAG_FLOOR_2;
      G_save_game_flags[world_index] &= ~SAVE_GAME_MASK_ROOMS;
    }
  }

  return 0;
}

/*******************************************************************************
** save_game_mark_current_floppy_obtained()
*******************************************************************************/
short int save_game_mark_current_floppy_obtained()
{
  int world_index;

  /* make sure this is a valid level index */
  if ((G_current_level_index < 0) || (G_current_level_index >= 330))
    return 1;

  /* determine current world */
  world_index = G_current_level_index / 15;

  /* set floppy disk to obtained */
  G_save_game_flags[world_index] |= SAVE_GAME_FLAG_FLOPPY;

  return 0;
}

/*******************************************************************************
** save_game_record_best_time()
*******************************************************************************/
short int save_game_record_best_time(unsigned char new_time)
{
  /* make sure this is a valid level index */
  if ((G_current_level_index < 0) || (G_current_level_index >= 330))
    return 1;

  /* make sure this time is valid */
  if (new_time == 0)
    return 1;

  /* store the new time if it is better than the current best time */
  if ((G_save_game_best_times[G_current_level_index] == 0)  ||
      (new_time < G_save_game_best_times[G_current_level_index]))
  {
    G_save_game_best_times[G_current_level_index] = new_time;
  }

  return 0;
}

/*******************************************************************************
** save_game_read()
*******************************************************************************/
short int save_game_read()
{
  FILE* fp;
  int   i;
  int   j;
  char  signature[4];
  char  type[6];

  /* determine save game to read */
  if (G_save_game_number == 1)
    fp = fopen(G_path_save_game_1, "rb");
  else if (G_save_game_number == 2)
    fp = fopen(G_path_save_game_2, "rb");
  else if (G_save_game_number == 3)
    fp = fopen(G_path_save_game_3, "rb");
  else
    return 1;

  /* if save game did not open, return error */
  if (fp == NULL)
    return 1;

  /* read signature */
  if (fread(signature, 1, 4, fp) < 4)
  {
    fclose(fp);
    return 1;
  }

  if ((signature[0] != 'V') || (signature[1] != 'T') ||
      (signature[2] != '2') || (signature[3] != '!'))
  {
    fclose(fp);
    return 1;
  }

  /* read type */
  if (fread(type, 1, 6, fp) < 6)
  {
    fclose(fp);
    return 1;
  }

  if ((type[0] != 'S') || (type[1] != 'A') || (type[2] != 'V') ||
      (type[3] != 'E') || (type[4] != ' ') || (type[5] != ' '))
  {
    fclose(fp);
    return 1;
  }

  /* read progress flags */
  for (i = 0; i < 22; i++)
  {
    if (fread(&G_save_game_flags[i], 1, 1, fp) == 0)
    {
      save_game_reset();
      fclose(fp);
      return 1;
    }

    /* if floor 2 is marked open, but floor 1 is not, mark floor 1 open */
    if ((G_save_game_flags[i] & SAVE_GAME_MASK_FLOORS) == 
        SAVE_GAME_FLAG_FLOOR_2)
    {
      G_save_game_flags[i] |= SAVE_GAME_FLAG_FLOOR_1;
    }
  }

  /* read best times */
  for (i = 0; i < 330; i++)
  {
    if (fread(&G_save_game_best_times[i], 1, 1, fp) == 0)
    {
      save_game_reset();
      fclose(fp);
      return 1;
    }
  }

  /* close save game */
  fclose(fp);

  /* validate save game (make sure normal worlds were unlocked in order) */
  for (i = 0; i < 17; i++)
  {
    if (!(SAVE_GAME_WORLD_IS_COMPLETE(i)))
    {
      for (j = i + 1; j < 18; j++)
        G_save_game_flags[j] = SAVE_GAME_FLAGS_CLEAR;

      break;
    }
  }

  /* compute percentage and floppy disk counts */
  save_game_compute_completion_percentage_and_floppy_counts();

  /* validate save game (make sure secret worlds were not accessed early) */
  if ((G_save_game_3_and_1_2_floppies < 6) &&
      (G_save_game_flags[18] != SAVE_GAME_FLAGS_CLEAR))
  {
    G_save_game_flags[18] = SAVE_GAME_FLAGS_CLEAR;
    save_game_compute_completion_percentage_and_floppy_counts();
  }

  if ((G_save_game_3_and_1_2_floppies < 12) &&
      (G_save_game_flags[19] != SAVE_GAME_FLAGS_CLEAR))
  {
    G_save_game_flags[19] = SAVE_GAME_FLAGS_CLEAR;
    save_game_compute_completion_percentage_and_floppy_counts();
  }

  if ((G_save_game_3_and_1_2_floppies < 18) &&
      (G_save_game_flags[20] != SAVE_GAME_FLAGS_CLEAR))
  {
    G_save_game_flags[20] = SAVE_GAME_FLAGS_CLEAR;
    save_game_compute_completion_percentage_and_floppy_counts();
  }

  if ((G_save_game_5_and_1_4_floppies < 3) &&
      (G_save_game_flags[21] != SAVE_GAME_FLAGS_CLEAR))
  {
    G_save_game_flags[21] = SAVE_GAME_FLAGS_CLEAR;
    save_game_compute_completion_percentage_and_floppy_counts();
  }

  return 0;
}

/*******************************************************************************
** save_game_write()
*******************************************************************************/
short int save_game_write()
{
  FILE* fp;
  int   i;
  char  signature[4];
  char  type[6];

  /* determine save game to write */
  if (G_save_game_number == 1)
    fp = fopen(G_path_save_game_1, "wb");
  else if (G_save_game_number == 2)
    fp = fopen(G_path_save_game_2, "wb");
  else if (G_save_game_number == 3)
    fp = fopen(G_path_save_game_3, "wb");
  else
    return 1;

  /* if save game did not open, return error */
  if (fp == NULL)
    return 1;

  /* write signature */
  signature[0] = 'V';
  signature[1] = 'T';
  signature[2] = '2';
  signature[3] = '!';

  if (fwrite(signature, 1, 4, fp) < 4)
  {
    fclose(fp);
    return 1;
  }

  /* write file type */
  type[0] = 'S';
  type[1] = 'A';
  type[2] = 'V';
  type[3] = 'E';
  type[4] = ' ';
  type[5] = ' ';

  if (fwrite(type, 1, 6, fp) < 6)
  {
    fclose(fp);
    return 1;
  }

  /* write progress flags */
  for (i = 0; i < 22; i++)
  {
    /* if floor 2 is marked open, but floor 1 is not, mark floor 1 open */
    if ((G_save_game_flags[i] & SAVE_GAME_MASK_FLOORS) == 
        SAVE_GAME_FLAG_FLOOR_2)
    {
      G_save_game_flags[i] |= SAVE_GAME_FLAG_FLOOR_1;
    }

    if (fwrite(&G_save_game_flags[i], 1, 1, fp) == 0)
    {
      fclose(fp);
      return 1;
    }
  }

  /* write best times */
  for (i = 0; i < 330; i++)
  {
    if (fwrite(&G_save_game_best_times[i], 1, 1, fp) == 0)
    {
      fclose(fp);
      return 1;
    }
  }

  /* close save game */
  fclose(fp);

  return 0;
}

