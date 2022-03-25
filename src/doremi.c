/*******************************************************************************
** doremi.c (sound and music)
*******************************************************************************/

#ifdef VT2_MAC_OSX
  #include <SDL2_mixer/SDL_mixer.h>
#else
  #include <SDL2/SDL_mixer.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "doremi.h"
#include "global.h"

Mix_Chunk G_sfx_all[SFX_NUM_INDICES];
Mix_Music *G_music;

/*******************************************************************************
** doremi_init_all_sfx()
*******************************************************************************/
short int doremi_init_all_sfx()
{
  int         i;
  Mix_Chunk*  chunk;

  for (i = 0; i < SFX_NUM_INDICES; i++)
  {
    chunk = &G_sfx_all[i];

    chunk->allocated = 0;
    chunk->abuf = NULL;
    chunk->alen = 0;
    chunk->volume = 0;
  }

  return 0;
}

/*******************************************************************************
** doremi_deinit_all_sfx()
*******************************************************************************/
short int doremi_deinit_all_sfx()
{
  int         i;
  Mix_Chunk*  chunk;

  for (i = 0; i < SFX_NUM_INDICES; i++)
  {
    chunk = &G_sfx_all[i];

    if (chunk->allocated == 1)
    {
      if (chunk->abuf != NULL)
      {
        free(chunk->abuf);
        chunk->abuf = NULL;
      }

      chunk->alen = 0;
      chunk->volume = 0;
      chunk->allocated = 0;
    }
  }

  return 0;
}

/*******************************************************************************
** doremi_load_all_sfx_from_file()
*******************************************************************************/
short int doremi_load_all_sfx_from_file(char* filename)
{
  FILE*         fp;
  int           i;
  int           j;
  int           num_samples;
  short int     tmp_int;
  unsigned int  tmp_uint;
  unsigned char msb;
  unsigned char lsb;
  char          signature[4];
  char          type[6];
  unsigned char num_sfx;
  Mix_Chunk*    chunk;

  if (filename == NULL)
    return 1;

  /* open file */
  fp = fopen(filename, "rb");

  /* if file did not open, return error */
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

  if ((type[0] != 'S') || (type[1] != 'F') || (type[2] != 'X') ||
      (type[3] != ' ') || (type[4] != ' ') || (type[5] != ' '))
  {
    fclose(fp);
    return 1;
  }

  /* read number of sfx */
  if (fread(&num_sfx, 1, 1, fp) == 0)
  {
    fclose(fp);
    return 1;
  }

  if (num_sfx != SFX_NUM_INDICES)
  {
    fclose(fp);
    return 1;
  }

  /* cycle through sfx */
  for (i = 0; i < num_sfx; i++)
  {
    chunk = &G_sfx_all[i];

    /* read number of samples */
    if (fread(&tmp_uint, 4, 1, fp) == 0)
    {
      fclose(fp);
      return 1;
    }

    num_samples = (int) tmp_uint;

    /* initialize chunk */
    chunk->allocated = 1;
    chunk->abuf = malloc(sizeof(short int) * 2 * num_samples);
    chunk->alen = sizeof(short int) * 2 * num_samples;
    chunk->volume = 64;

    /* load mono sfx data to 16 bit stereo audio in sdl */
    for (j = 0; j < num_samples; j++)
    {
      if (fread(&tmp_int, 2, 1, fp) == 0)
      {
        fclose(fp);
        return 1;
      }

      tmp_int = (int) (tmp_int * 0.70710678118655);

      lsb = tmp_int % 256;
      msb = tmp_int / 256;

      chunk->abuf[(4 * j) + 0] = lsb;
      chunk->abuf[(4 * j) + 1] = msb;
      chunk->abuf[(4 * j) + 2] = lsb;
      chunk->abuf[(4 * j) + 3] = msb;
    }
  }

  /* close file */
  fclose(fp);

  /* set volume for all sfx */
  Mix_Volume(-1, G_sfx_volume);

  return 0;
}

/*******************************************************************************
** doremi_play_sfx()
*******************************************************************************/
short int doremi_play_sfx(int type)
{
  int         i;
  int         num_channels;
  Mix_Chunk*  chunk;

  if ((type < 0) || (type >= SFX_NUM_INDICES))
    return 1;

  /* get number of currently allocated channels */
  num_channels = Mix_AllocateChannels(-1);

  /* set chunk pointer */
  chunk = &G_sfx_all[type];

  /* check if this sample is already playing */
  for (i = 0; i < num_channels; i++)
  {
    if ((Mix_Playing(i)) && (Mix_GetChunk(i) == chunk))
    {
      Mix_HaltChannel(i);
      Mix_PlayChannel(i, chunk, 0);
      return 0;
    }
  }

  /* otherwise, play sample on first available channel */
  Mix_PlayChannel(-1, chunk, 0);

  return 0;
}

/*******************************************************************************
** doremi_set_sfx_volume()
*******************************************************************************/
short int doremi_set_sfx_volume()
{
  Mix_Volume(-1, G_sfx_volume);

  return 0;
}

/*******************************************************************************
** doremi_init_music()
*******************************************************************************/
short int doremi_init_music()
{
  G_music = NULL;

  return 0;
}

/*******************************************************************************
** doremi_deinit_music()
*******************************************************************************/
short int doremi_deinit_music()
{
  if (G_music != NULL)
  {
    Mix_FreeMusic(G_music);
    G_music = NULL;
  }

  return 0;
}

/*******************************************************************************
** doremi_play_music()
*******************************************************************************/
short int doremi_play_music(int type)
{
  char* path_music_track;

  /* stop currently playing music, if any */
  if (G_music != NULL)
  {
    Mix_FreeMusic(G_music);
    G_music = NULL;
  }

  /* allocate string for music filename */
  path_music_track = malloc(sizeof(char) * (strlen(G_path_ost) + 64 + 1));
  strcpy(path_music_track, G_path_ost);

  /* determine new music based on type */
  if (type == MUSIC_TYPE_MAIN_MENU)
    strcpy(path_music_track + strlen(G_path_ost), "marschner_der_vampyr_overture.xm");
  else if (type == MUSIC_TYPE_STORY_01)
    strcpy(path_music_track + strlen(G_path_ost), "saint_saens_op_16_prelude.xm");
  else if (type == MUSIC_TYPE_STORY_02)
    strcpy(path_music_track + strlen(G_path_ost), "mussorgsky_paae_promenade_01.xm");
  else if (type == MUSIC_TYPE_STORY_03)
    strcpy(path_music_track + strlen(G_path_ost), "mussorgsky_paae_promenade_02.xm");
  else if (type == MUSIC_TYPE_STORY_04)
    strcpy(path_music_track + strlen(G_path_ost), "mussorgsky_paae_promenade_03.xm");
  else if (type == MUSIC_TYPE_STORY_05)
    strcpy(path_music_track + strlen(G_path_ost), "mussorgsky_paae_promenade_04.xm");
  else if (type == MUSIC_TYPE_STORY_06)
    strcpy(path_music_track + strlen(G_path_ost), "mussorgsky_paae_promenade_05.xm");
  else if (type == MUSIC_TYPE_WORLD)
  {
    if ((G_current_episode == 1) && (G_current_world == 1))
      strcpy(path_music_track + strlen(G_path_ost), "mozart_fantasia_in_d_minor.xm");
    else if ((G_current_episode == 1) && (G_current_world == 2))
      strcpy(path_music_track + strlen(G_path_ost), "mussorgsky_paae_catacombs_cum_mortuis_in_lingua_mortua.xm");
    else if ((G_current_episode == 1) && (G_current_world == 3))
      strcpy(path_music_track + strlen(G_path_ost), "dvorak_ftbf_by_the_black_lake.xm");
    else if ((G_current_episode == 2) && (G_current_world == 1))
      strcpy(path_music_track + strlen(G_path_ost), "saint_saens_op_16_serenade.xm");
    else if ((G_current_episode == 2) && (G_current_world == 2))
      strcpy(path_music_track + strlen(G_path_ost), "dvorak_ftbf_witches_sabbath.xm");
    else if ((G_current_episode == 2) && (G_current_world == 3))
      strcpy(path_music_track + strlen(G_path_ost), "saint_saens_op_16_romance.xm");
    else if ((G_current_episode == 3) && (G_current_world == 1))
      strcpy(path_music_track + strlen(G_path_ost), "mussorgsky_paae_bydlo.xm");
    else if ((G_current_episode == 3) && (G_current_world == 2))
      strcpy(path_music_track + strlen(G_path_ost), "dvorak_ftbf_silent_woods.xm");
    else if ((G_current_episode == 3) && (G_current_world == 3))
      strcpy(path_music_track + strlen(G_path_ost), "mussorgsky_paae_gnomus.xm");
    else if ((G_current_episode == 4) && (G_current_world == 1))
      strcpy(path_music_track + strlen(G_path_ost), "saint_saens_danse_macabre.xm");
    else if ((G_current_episode == 4) && (G_current_world == 2))
      strcpy(path_music_track + strlen(G_path_ost), "saint_saens_op_16_scherzo.xm");
    else if ((G_current_episode == 4) && (G_current_world == 3))
      strcpy(path_music_track + strlen(G_path_ost), "dvorak_ftbf_on_the_watch.xm");
    else if ((G_current_episode == 5) && (G_current_world == 1))
      strcpy(path_music_track + strlen(G_path_ost), "mussorgsky_paae_the_great_gate_of_kiev.xm");
    else if ((G_current_episode == 5) && (G_current_world == 2))
      strcpy(path_music_track + strlen(G_path_ost), "pachelbel_canon_in_d.xm");
    else if ((G_current_episode == 5) && (G_current_world == 3))
      strcpy(path_music_track + strlen(G_path_ost), "mussorgsky_paae_samuel_goldenberg_and_schmuyle.xm");
    else if ((G_current_episode == 6) && (G_current_world == 1))
      strcpy(path_music_track + strlen(G_path_ost), "dvorak_ftbf_in_troubled_times.xm");
    else if ((G_current_episode == 6) && (G_current_world == 2))
      strcpy(path_music_track + strlen(G_path_ost), "mussorgsky_paae_baba_yaga.xm");
    else if ((G_current_episode == 6) && (G_current_world == 3))
      strcpy(path_music_track + strlen(G_path_ost), "saint_saens_op_16_finale.xm");
    else if ((G_current_episode == 7) && (G_current_world == 1))
      strcpy(path_music_track + strlen(G_path_ost), "mussorgsky_paae_catacombs_cum_mortuis_in_lingua_mortua.xm");
    else if ((G_current_episode == 7) && (G_current_world == 2))
      strcpy(path_music_track + strlen(G_path_ost), "dvorak_ftbf_silent_woods.xm");
    else if ((G_current_episode == 7) && (G_current_world == 3))
      strcpy(path_music_track + strlen(G_path_ost), "mussorgsky_paae_the_great_gate_of_kiev.xm");
    else if ((G_current_episode == 7) && (G_current_world == 4))
      strcpy(path_music_track + strlen(G_path_ost), "dvorak_ftbf_in_the_spinning_room.xm");
  }

  /* load music track */
  G_music = Mix_LoadMUS(path_music_track);

  /* check that music track was loaded */
  if (G_music == NULL)
  {
    fprintf(stdout, "Mix_LoadMUS Error: %s\n", Mix_GetError());

    return 0;
  }

  /* free music filename string */
  free(path_music_track);

  /* play music track */
  if (G_music != NULL)
  {
    if (Mix_PlayMusic(G_music, -1) == -1)
    {
      fprintf(stdout, "Mix_PlayMusic Error: %s\n", Mix_GetError());
      return 1;
    }

    Mix_VolumeMusic(G_music_volume);
  }
  else
  {
    fprintf(stdout, "Failed to load XM file.\n");
  }

  return 0;
}

/*******************************************************************************
** doremi_pause_music()
*******************************************************************************/
short int doremi_pause_music()
{
  if (G_music == NULL)
    return 0;

  Mix_PauseMusic();

  return 0;
}

/*******************************************************************************
** doremi_unpause_music()
*******************************************************************************/
short int doremi_unpause_music()
{
  if (G_music == NULL)
    return 0;

  Mix_ResumeMusic();

  return 0;
}

/*******************************************************************************
** doremi_set_music_volume()
*******************************************************************************/
short int doremi_set_music_volume()
{
  if (G_music == NULL)
    return 0;

  Mix_VolumeMusic(G_music_volume);

  return 0;
}
