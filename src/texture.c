/*******************************************************************************
** texture.c (opengl texture management)
*******************************************************************************/

/*#include <SDL2/SDL_opengl.h>*/
#include <glad/glad.h>

#include <stdio.h>
#include <stdlib.h>

#include "texture.h"

GLuint* G_texture_ids;

/*******************************************************************************
** textures_init()
*******************************************************************************/
short int textures_init()
{
  int i;

  G_texture_ids = malloc(sizeof(GLuint) * TEXTURE_NUM_INDICES);

  for (i = 0; i < TEXTURE_NUM_INDICES; i++)
  {
    G_texture_ids[i] = 0;
  }

  return 0;
}

/*******************************************************************************
** textures_deinit()
*******************************************************************************/
short int textures_deinit()
{
  int i;

  if (G_texture_ids != NULL)
  {
    /* clear all texture ids from opengl */
    for (i = 0; i < TEXTURE_NUM_INDICES; i++)
    {
      if (G_texture_ids[i] != 0)
      {
        glDeleteTextures(1, &(G_texture_ids[i]));
        G_texture_ids[i] = 0;
      }
    }

    free(G_texture_ids);
    G_texture_ids = NULL;
  }

  return 0;
}

/*******************************************************************************
** texture_load_all_from_file()
*******************************************************************************/
short int texture_load_all_from_file(char* filename)
{
  FILE*         fp;
  int           i;
  int           j;
  char          signature[4];
  char          type[6];
  unsigned char num_textures;
  unsigned char texture_flags;

  GLuint        image_format;
  short int     w;
  short int     h;
  GLubyte*      pixel_data;
  int           num_bytes;
  GLubyte       alpha_color[3];
  GLubyte       buffer[3];

  if (filename == NULL)
    return 1;

  /* initialize variables */
  num_textures = 0;
  texture_flags = 0x00;

  image_format = GL_BGR;
  w = 0;
  h = 0;
  pixel_data = NULL;

  /* open file */
  fp = fopen(filename, "rb");

  /* if file did not open, return error */
  if (fp == NULL)
  {
    fclose(fp);
    return 1;
  }

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

  if ((type[0] != 'G') || (type[1] != 'F') || (type[2] != 'X') ||
      (type[3] != ' ') || (type[4] != ' ') || (type[5] != ' '))
  {
    fclose(fp);
    return 1;
  }

  /* read number of textures */
  if (fread(&num_textures, 1, 1, fp) == 0)
  {
    fclose(fp);
    return 1;
  }

  if (num_textures != TEXTURE_NUM_INDICES)
  {
    fclose(fp);
    return 1;
  }

  /* cycle through textures */
  for (i = 0; i < num_textures; i++)
  {
    /* read texture flags */
    if (fread(&texture_flags, 1, 1, fp) == 0)
    {
      fclose(fp);
      return 1;
    }

    /* set up variables based on flags */
    if (texture_flags & TEXTURE_FLAG_SIZE_256_X_256)
    {
      w = 256;
      h = 256;
    }
    else
    {
      w = 128;
      h = 128;
    }

    if (texture_flags & TEXTURE_FLAG_HAS_ALPHA_CHANNEL)
    {
      image_format = GL_RGBA;
      num_bytes = 4 * w * h;
    }
    else
    {
      image_format = GL_RGB;
      num_bytes = 3 * w * h;
    }

    alpha_color[0] = ((texture_flags & 0x30) >> 4) * 85;
    alpha_color[1] = ((texture_flags & 0x0C) >> 2) * 85;
    alpha_color[2] = (texture_flags & 0x03) * 85;

    /* allocate pixel data */
    pixel_data = malloc(sizeof(GLubyte) * num_bytes);

    /* read 6 bit rgb data from file          */
    /* R1-G1-B1-R2, G2-B2-R3-G3, B3-R4-G4-B4  */
    if (texture_flags & TEXTURE_FLAG_HAS_ALPHA_CHANNEL)
    {
      for (j = 0; j < num_bytes; j = j + (4 * 4))
      {
        if (fread(buffer, 1, 3, fp) == 0)
        {
          free(pixel_data);
          fclose(fp);
          return 1;
        }

        pixel_data[j + 0]  = ((buffer[0] & 0xC0) >> 6) * 85;  /* R1 */
        pixel_data[j + 1]  = ((buffer[0] & 0x30) >> 4) * 85;  /* G1 */
        pixel_data[j + 2]  = ((buffer[0] & 0x0C) >> 2) * 85;  /* B1 */

        pixel_data[j + 4]  = (buffer[0] & 0x03) * 85;         /* R2 */
        pixel_data[j + 5]  = ((buffer[1] & 0xC0) >> 6) * 85;  /* G2 */
        pixel_data[j + 6]  = ((buffer[1] & 0x30) >> 4) * 85;  /* B2 */

        pixel_data[j + 8]  = ((buffer[1] & 0x0C) >> 2) * 85;  /* R3 */
        pixel_data[j + 9]  = (buffer[1] & 0x03) * 85;         /* G3 */
        pixel_data[j + 10] = ((buffer[2] & 0xC0) >> 6) * 85;  /* B3 */

        pixel_data[j + 12] = ((buffer[2] & 0x30) >> 4) * 85;  /* R4 */
        pixel_data[j + 13] = ((buffer[2] & 0x0C) >> 2) * 85;  /* G4 */
        pixel_data[j + 14] = (buffer[2] & 0x03) * 85;         /* B4 */

        if ((pixel_data[j + 0] == alpha_color[0]) &&
            (pixel_data[j + 1] == alpha_color[1]) &&
            (pixel_data[j + 2] == alpha_color[2]))
        {
          pixel_data[j + 3] = 0;
        }
        else
        {
          pixel_data[j + 3] = 255;
        }

        if ((pixel_data[j + 4] == alpha_color[0]) &&
            (pixel_data[j + 5] == alpha_color[1]) &&
            (pixel_data[j + 6] == alpha_color[2]))
        {
          pixel_data[j + 7] = 0;
        }
        else
        {
          pixel_data[j + 7] = 255;
        }

        if ((pixel_data[j + 8]  == alpha_color[0]) &&
            (pixel_data[j + 9]  == alpha_color[1]) &&
            (pixel_data[j + 10] == alpha_color[2]))
        {
          pixel_data[j + 11] = 0;
        }
        else
        {
          pixel_data[j + 11] = 255;
        }

        if ((pixel_data[j + 12] == alpha_color[0]) &&
            (pixel_data[j + 13] == alpha_color[1]) &&
            (pixel_data[j + 14] == alpha_color[2]))
        {
          pixel_data[j + 15] = 0;
        }
        else
        {
          pixel_data[j + 15] = 255;
        }
      }
    }
    else
    {
      for (j = 0; j < num_bytes; j = j + (4 * 3))
      {
        if (fread(buffer, 1, 3, fp) == 0)
        {
          free(pixel_data);
          fclose(fp);
          return 1;
        }

        pixel_data[j + 0]  = ((buffer[0] & 0xC0) >> 6) * 85;  /* R1 */
        pixel_data[j + 1]  = ((buffer[0] & 0x30) >> 4) * 85;  /* G1 */
        pixel_data[j + 2]  = ((buffer[0] & 0x0C) >> 2) * 85;  /* B1 */

        pixel_data[j + 3]  = (buffer[0] & 0x03) * 85;         /* R2 */
        pixel_data[j + 4]  = ((buffer[1] & 0xC0) >> 6) * 85;  /* G2 */
        pixel_data[j + 5]  = ((buffer[1] & 0x30) >> 4) * 85;  /* B2 */

        pixel_data[j + 6]  = ((buffer[1] & 0x0C) >> 2) * 85;  /* R3 */
        pixel_data[j + 7]  = (buffer[1] & 0x03) * 85;         /* G3 */
        pixel_data[j + 8]  = ((buffer[2] & 0xC0) >> 6) * 85;  /* B3 */

        pixel_data[j + 9]  = ((buffer[2] & 0x30) >> 4) * 85;  /* R4 */
        pixel_data[j + 10] = ((buffer[2] & 0x0C) >> 2) * 85;  /* G4 */
        pixel_data[j + 11] = (buffer[2] & 0x03) * 85;         /* B4 */
      }
    }

    /* assign gl texture id to this texture, set it to the current gl texture */
    glGenTextures(1, &(G_texture_ids[i]));
    glBindTexture(GL_TEXTURE_2D, G_texture_ids[i]);

    /* set up texture in opengl */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    /* load the texture to opengl from the image data */
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, w, h, 
                  0, image_format, GL_UNSIGNED_BYTE, pixel_data);

    /* clear image data */
    if (pixel_data != NULL)
    {
      free(pixel_data);
      pixel_data = NULL;
    }
  }

  /* close file */
  fclose(fp);

  return 0;
}
