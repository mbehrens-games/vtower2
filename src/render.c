/*******************************************************************************
** render.c (opengl rendering)
*******************************************************************************/

/*#include <SDL2/SDL_opengl.h>*/
#include <glad/glad.h>

#include <stdio.h>
#include <stdlib.h>

#include "entity.h"
#include "global.h"
#include "grafx.h"
#include "savegame.h"
#include "texture.h"
#include "world.h"

#define RENDER_LEVEL_BACKGROUND     1.000f
#define RENDER_LEVEL_BORDER         0.875f
#define RENDER_LEVEL_FLOOR          0.750f
#define RENDER_LEVEL_LOW            0.625f
#define RENDER_LEVEL_MIDDLE         0.500f
#define RENDER_LEVEL_HIGH           0.375f
#define RENDER_LEVEL_PARTICLE       0.250f
#define RENDER_LEVEL_HUD_BACKGROUND 0.125f
#define RENDER_LEVEL_HUD_FOREGROUND 0.000f

#define RENDER_FLUSH_SPRITES()                                                 \
  if (S_num_sprites > 0)                                                       \
  {                                                                            \
    glBindBuffer(GL_ARRAY_BUFFER, G_vertex_buffer_id_sprites);                 \
    glBufferSubData(GL_ARRAY_BUFFER, 0,                                        \
                    S_num_sprites * 12 * sizeof(GLfloat),                      \
                    G_vertex_buffer_sprites);                                  \
                                                                               \
    glBindBuffer(GL_ARRAY_BUFFER, G_texcoord_buffer_id_sprites);               \
    glBufferSubData(GL_ARRAY_BUFFER, 0,                                        \
                    S_num_sprites * 8 * sizeof(GLfloat),                       \
                    G_texcoord_buffer_sprites);                                \
                                                                               \
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, G_index_buffer_id_sprites);          \
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0,                                \
                    S_num_sprites * 6 * sizeof(unsigned short),                \
                    G_index_buffer_sprites);                                   \
                                                                               \
    glDrawElements(GL_TRIANGLES, S_num_sprites * 6, GL_UNSIGNED_SHORT, NULL);  \
                                                                               \
    S_num_sprites = 0;                                                         \
  }

#define RENDER_FLUSH_PARTICLES()                                               \
  if (S_num_sprites > 0)                                                       \
  {                                                                            \
    glBindBuffer(GL_ARRAY_BUFFER, G_vertex_buffer_id_sprites);                 \
    glBufferSubData(GL_ARRAY_BUFFER, 0,                                        \
                    S_num_sprites * 12 * sizeof(GLfloat),                      \
                    G_vertex_buffer_sprites);                                  \
                                                                               \
    glBindBuffer(GL_ARRAY_BUFFER, G_color_buffer_id_sprites);                  \
    glBufferSubData(GL_ARRAY_BUFFER, 0,                                        \
                    S_num_sprites * 16 * sizeof(GLfloat),                      \
                    G_color_buffer_sprites);                                   \
                                                                               \
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, G_index_buffer_id_sprites);          \
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0,                                \
                    S_num_sprites * 6 * sizeof(unsigned short),                \
                    G_index_buffer_sprites);                                   \
                                                                               \
    glDrawElements(GL_TRIANGLES, S_num_sprites * 6, GL_UNSIGNED_SHORT, NULL);  \
                                                                               \
    S_num_sprites = 0;                                                         \
  }

#define RENDER_ADD_VERTICES_TO_BUFFER(x1, y1, x2, y2, z)                       \
  G_vertex_buffer_sprites[12 * S_num_sprites + 0]   = x1;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 1]   = y1;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 2]   = z;                       \
                                                                               \
  G_vertex_buffer_sprites[12 * S_num_sprites + 3]   = x2;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 4]   = y1;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 5]   = z;                       \
                                                                               \
  G_vertex_buffer_sprites[12 * S_num_sprites + 6]   = x1;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 7]   = y2;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 8]   = z;                       \
                                                                               \
  G_vertex_buffer_sprites[12 * S_num_sprites + 9]   = x2;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 10]  = y2;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 11]  = z;

#define RENDER_ADD_VERTICES_TO_BUFFER_90(x1, y1, x2, y2, z)                    \
  G_vertex_buffer_sprites[12 * S_num_sprites + 0]   = x1;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 1]   = y2;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 2]   = z;                       \
                                                                               \
  G_vertex_buffer_sprites[12 * S_num_sprites + 3]   = x1;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 4]   = y1;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 5]   = z;                       \
                                                                               \
  G_vertex_buffer_sprites[12 * S_num_sprites + 6]   = x2;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 7]   = y2;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 8]   = z;                       \
                                                                               \
  G_vertex_buffer_sprites[12 * S_num_sprites + 9]   = x2;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 10]  = y1;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 11]  = z;

#define RENDER_ADD_VERTICES_TO_BUFFER_180(x1, y1, x2, y2, z)                   \
  G_vertex_buffer_sprites[12 * S_num_sprites + 0]   = x2;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 1]   = y2;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 2]   = z;                       \
                                                                               \
  G_vertex_buffer_sprites[12 * S_num_sprites + 3]   = x1;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 4]   = y2;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 5]   = z;                       \
                                                                               \
  G_vertex_buffer_sprites[12 * S_num_sprites + 6]   = x2;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 7]   = y1;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 8]   = z;                       \
                                                                               \
  G_vertex_buffer_sprites[12 * S_num_sprites + 9]   = x1;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 10]  = y1;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 11]  = z;

#define RENDER_ADD_VERTICES_TO_BUFFER_270(x1, y1, x2, y2, z)                   \
  G_vertex_buffer_sprites[12 * S_num_sprites + 0]   = x2;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 1]   = y1;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 2]   = z;                       \
                                                                               \
  G_vertex_buffer_sprites[12 * S_num_sprites + 3]   = x2;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 4]   = y2;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 5]   = z;                       \
                                                                               \
  G_vertex_buffer_sprites[12 * S_num_sprites + 6]   = x1;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 7]   = y1;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 8]   = z;                       \
                                                                               \
  G_vertex_buffer_sprites[12 * S_num_sprites + 9]   = x1;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 10]  = y2;                      \
  G_vertex_buffer_sprites[12 * S_num_sprites + 11]  = z;

#define RENDER_ADD_TEXCOORDS_TO_BUFFER(u1, v1, u2, v2)                         \
  G_texcoord_buffer_sprites[8 * S_num_sprites + 0] = u1;                       \
  G_texcoord_buffer_sprites[8 * S_num_sprites + 1] = v1;                       \
                                                                               \
  G_texcoord_buffer_sprites[8 * S_num_sprites + 2] = u2;                       \
  G_texcoord_buffer_sprites[8 * S_num_sprites + 3] = v1;                       \
                                                                               \
  G_texcoord_buffer_sprites[8 * S_num_sprites + 4] = u1;                       \
  G_texcoord_buffer_sprites[8 * S_num_sprites + 5] = v2;                       \
                                                                               \
  G_texcoord_buffer_sprites[8 * S_num_sprites + 6] = u2;                       \
  G_texcoord_buffer_sprites[8 * S_num_sprites + 7] = v2;

#define RENDER_ADD_COLORS_TO_BUFFER(r, g, b)                                   \
  G_color_buffer_sprites[16 * S_num_sprites + 0]  = r;                         \
  G_color_buffer_sprites[16 * S_num_sprites + 1]  = g;                         \
  G_color_buffer_sprites[16 * S_num_sprites + 2]  = b;                         \
  G_color_buffer_sprites[16 * S_num_sprites + 3]  = 1.0f;                      \
                                                                               \
  G_color_buffer_sprites[16 * S_num_sprites + 4]  = r;                         \
  G_color_buffer_sprites[16 * S_num_sprites + 5]  = g;                         \
  G_color_buffer_sprites[16 * S_num_sprites + 6]  = b;                         \
  G_color_buffer_sprites[16 * S_num_sprites + 7]  = 1.0f;                      \
                                                                               \
  G_color_buffer_sprites[16 * S_num_sprites + 8]  = r;                         \
  G_color_buffer_sprites[16 * S_num_sprites + 9]  = g;                         \
  G_color_buffer_sprites[16 * S_num_sprites + 10] = b;                         \
  G_color_buffer_sprites[16 * S_num_sprites + 11] = 1.0f;                      \
                                                                               \
  G_color_buffer_sprites[16 * S_num_sprites + 12] = r;                         \
  G_color_buffer_sprites[16 * S_num_sprites + 13] = g;                         \
  G_color_buffer_sprites[16 * S_num_sprites + 14] = b;                         \
  G_color_buffer_sprites[16 * S_num_sprites + 15] = 1.0f;

#define RENDER_ADD_INDICES_TO_BUFFER()                                         \
  G_index_buffer_sprites[6 * S_num_sprites + 0] = 4 * S_num_sprites + 0;       \
  G_index_buffer_sprites[6 * S_num_sprites + 1] = 4 * S_num_sprites + 2;       \
  G_index_buffer_sprites[6 * S_num_sprites + 2] = 4 * S_num_sprites + 1;       \
                                                                               \
  G_index_buffer_sprites[6 * S_num_sprites + 3] = 4 * S_num_sprites + 1;       \
  G_index_buffer_sprites[6 * S_num_sprites + 4] = 4 * S_num_sprites + 2;       \
  G_index_buffer_sprites[6 * S_num_sprites + 5] = 4 * S_num_sprites + 3;       \
                                                                               \
  S_num_sprites += 1;

#define RENDER_CHECK_FOR_MAX_SPRITES()                                         \
  if (S_num_sprites == GRAFX_MAX_SPRITES)                                      \
  {                                                                            \
    RENDER_FLUSH_SPRITES()                                                     \
  }

#define RENDER_CHECK_FOR_MAX_PARTICLES()                                       \
  if (S_num_sprites == GRAFX_MAX_SPRITES)                                      \
  {                                                                            \
    RENDER_FLUSH_PARTICLES()                                                   \
  }

#define RENDER_ADD_SPRITE_TO_BUFFER(x1, y1, x2, y2, z, u1, v1, u2, v2)         \
  RENDER_ADD_VERTICES_TO_BUFFER(x1, y1, x2, y2, z)                             \
  RENDER_ADD_TEXCOORDS_TO_BUFFER(u1, v1, u2, v2)                               \
  RENDER_ADD_INDICES_TO_BUFFER()                                               \
  RENDER_CHECK_FOR_MAX_SPRITES()

#define RENDER_ADD_SPRITE_TO_BUFFER_90(x1, y1, x2, y2, z, u1, v1, u2, v2)      \
  RENDER_ADD_VERTICES_TO_BUFFER_90(x1, y1, x2, y2, z)                          \
  RENDER_ADD_TEXCOORDS_TO_BUFFER(u1, v1, u2, v2)                               \
  RENDER_ADD_INDICES_TO_BUFFER()                                               \
  RENDER_CHECK_FOR_MAX_SPRITES()

#define RENDER_ADD_SPRITE_TO_BUFFER_180(x1, y1, x2, y2, z, u1, v1, u2, v2)     \
  RENDER_ADD_VERTICES_TO_BUFFER_180(x1, y1, x2, y2, z)                         \
  RENDER_ADD_TEXCOORDS_TO_BUFFER(u1, v1, u2, v2)                               \
  RENDER_ADD_INDICES_TO_BUFFER()                                               \
  RENDER_CHECK_FOR_MAX_SPRITES()

#define RENDER_ADD_SPRITE_TO_BUFFER_270(x1, y1, x2, y2, z, u1, v1, u2, v2)     \
  RENDER_ADD_VERTICES_TO_BUFFER_270(x1, y1, x2, y2, z)                         \
  RENDER_ADD_TEXCOORDS_TO_BUFFER(u1, v1, u2, v2)                               \
  RENDER_ADD_INDICES_TO_BUFFER()                                               \
  RENDER_CHECK_FOR_MAX_SPRITES()

#define RENDER_ADD_PARTICLE_TO_BUFFER(x1, y1, x2, y2, z, r, g, b)              \
  RENDER_ADD_VERTICES_TO_BUFFER(x1, y1, x2, y2, z)                             \
  RENDER_ADD_COLORS_TO_BUFFER(r, g, b)                                         \
  RENDER_ADD_INDICES_TO_BUFFER()                                               \
  RENDER_CHECK_FOR_MAX_PARTICLES()

#define RENDER_ADD_SPRITES_FROM_CATEGORY(category, z, layout)                  \
  e = G_entity_active_list_head[category];                                     \
                                                                               \
  while (e != NULL)                                                            \
  {                                                                            \
    RENDER_ADD_SPRITE_TO_BUFFER(112.0f + e->pos_x - e->rx,                     \
                                e->pos_y - e->ry,                              \
                                112.0f + e->pos_x + e->rx,                     \
                                e->pos_y + e->ry,                              \
                                z,                                             \
                                S_texcoord_table_##layout[e->tile][0],         \
                                S_texcoord_table_##layout[e->tile][1],         \
                                S_texcoord_table_##layout[e->tile][2],         \
                                S_texcoord_table_##layout[e->tile][3])         \
                                                                               \
    e = e->next;                                                               \
  }

#define RENDER_ADD_SPRITES_FROM_CATEGORY_WITH_ROTATION(category, z, layout)    \
  e = G_entity_active_list_head[category];                                     \
                                                                               \
  while (e != NULL)                                                            \
  {                                                                            \
    if ((e->orientation & ENTITY_THETA_MASK) == ENTITY_THETA_90)               \
    {                                                                          \
      RENDER_ADD_VERTICES_TO_BUFFER_90( 112.0f + e->pos_x - e->rx,             \
                                        e->pos_y - e->ry,                      \
                                        112.0f + e->pos_x + e->rx,             \
                                        e->pos_y + e->ry,                      \
                                        z)                                     \
    }                                                                          \
    else if ((e->orientation & ENTITY_THETA_MASK) == ENTITY_THETA_180)         \
    {                                                                          \
      RENDER_ADD_VERTICES_TO_BUFFER_180(112.0f + e->pos_x - e->rx,             \
                                        e->pos_y - e->ry,                      \
                                        112.0f + e->pos_x + e->rx,             \
                                        e->pos_y + e->ry,                      \
                                        z)                                     \
    }                                                                          \
    else if ((e->orientation & ENTITY_THETA_MASK) == ENTITY_THETA_270)         \
    {                                                                          \
      RENDER_ADD_VERTICES_TO_BUFFER_270(112.0f + e->pos_x - e->rx,             \
                                        e->pos_y - e->ry,                      \
                                        112.0f + e->pos_x + e->rx,             \
                                        e->pos_y + e->ry,                      \
                                        z)                                     \
    }                                                                          \
    else                                                                       \
    {                                                                          \
      RENDER_ADD_VERTICES_TO_BUFFER(112.0f + e->pos_x - e->rx,                 \
                                    e->pos_y - e->ry,                          \
                                    112.0f + e->pos_x + e->rx,                 \
                                    e->pos_y + e->ry,                          \
                                    z)                                         \
    }                                                                          \
                                                                               \
    RENDER_ADD_TEXCOORDS_TO_BUFFER( S_texcoord_table_##layout[e->tile][0],     \
                                    S_texcoord_table_##layout[e->tile][1],     \
                                    S_texcoord_table_##layout[e->tile][2],     \
                                    S_texcoord_table_##layout[e->tile][3])     \
    RENDER_ADD_INDICES_TO_BUFFER()                                             \
    RENDER_CHECK_FOR_MAX_SPRITES()                                             \
                                                                               \
    e = e->next;                                                               \
  }

#define RENDER_ADD_SPRITE_BY_TILE_INDEX(x, y, z, width, layout, tile)          \
  RENDER_ADD_SPRITE_TO_BUFFER(x, y, x + width, y + width,                      \
                              z,                                               \
                              S_texcoord_table_##layout[tile][0],              \
                              S_texcoord_table_##layout[tile][1],              \
                              S_texcoord_table_##layout[tile][2],              \
                              S_texcoord_table_##layout[tile][3])

#define RENDER_ADD_SPRITE_BY_TILE_INDEX_90(x, y, z, width, layout, tile)       \
  RENDER_ADD_SPRITE_TO_BUFFER_90( x, y, x + width, y + width,                  \
                                  z,                                           \
                                  S_texcoord_table_##layout[tile][0],          \
                                  S_texcoord_table_##layout[tile][1],          \
                                  S_texcoord_table_##layout[tile][2],          \
                                  S_texcoord_table_##layout[tile][3])

#define RENDER_ADD_SPRITE_BY_TILE_INDEX_180(x, y, z, width, layout, tile)      \
  RENDER_ADD_SPRITE_TO_BUFFER_180(x, y, x + width, y + width,                  \
                                  z,                                           \
                                  S_texcoord_table_##layout[tile][0],          \
                                  S_texcoord_table_##layout[tile][1],          \
                                  S_texcoord_table_##layout[tile][2],          \
                                  S_texcoord_table_##layout[tile][3])

#define RENDER_ADD_SPRITE_BY_TILE_INDEX_270(x, y, z, width, layout, tile)      \
  RENDER_ADD_SPRITE_TO_BUFFER_270(x, y, x + width, y + width,                  \
                                  z,                                           \
                                  S_texcoord_table_##layout[tile][0],          \
                                  S_texcoord_table_##layout[tile][1],          \
                                  S_texcoord_table_##layout[tile][2],          \
                                  S_texcoord_table_##layout[tile][3])

#define RENDER_CHANGE_TEXTURE(name)                                            \
  glActiveTexture(GL_TEXTURE0);                                                \
  glBindTexture(GL_TEXTURE_2D, G_texture_ids[name]);                           \
  glUniform1i(G_uniform_A_texture_sampler_id, 0);

#define RENDER_SETUP_VGA_OUTPUT()                                              \
  glBindFramebuffer(GL_FRAMEBUFFER, G_framebuffer_id_vga);                     \
  glViewport(0, 0,  (GLsizei) GRAFX_VGA_TEXTURE_WIDTH,                         \
                    (GLsizei) GRAFX_VGA_TEXTURE_HEIGHT);                       \
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#define RENDER_BEGIN_SPRITE_RENDERING()                                        \
  glUseProgram(G_program_id_A);                                                \
                                                                               \
  glUniformMatrix4fv( G_uniform_A_mvp_matrix_id, 1,                            \
                      GL_FALSE, G_projection_matrix_vga);                      \
                                                                               \
  glEnableVertexAttribArray(0);                                                \
  glBindBuffer(GL_ARRAY_BUFFER, G_vertex_buffer_id_sprites);                   \
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);                    \
                                                                               \
  glEnableVertexAttribArray(1);                                                \
  glBindBuffer(GL_ARRAY_BUFFER, G_texcoord_buffer_id_sprites);                 \
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

#define RENDER_END_SPRITE_RENDERING()                                          \
  glDisableVertexAttribArray(0);                                               \
  glDisableVertexAttribArray(1);

#define RENDER_BEGIN_PARTICLE_RENDERING()                                      \
  glUseProgram(G_program_id_B);                                                \
                                                                               \
  glUniformMatrix4fv( G_uniform_B_mvp_matrix_id, 1,                            \
                      GL_FALSE, G_projection_matrix_vga);                      \
                                                                               \
  glEnableVertexAttribArray(0);                                                \
  glBindBuffer(GL_ARRAY_BUFFER, G_vertex_buffer_id_sprites);                   \
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);                    \
                                                                               \
  glEnableVertexAttribArray(1);                                                \
  glBindBuffer(GL_ARRAY_BUFFER, G_color_buffer_id_sprites);                    \
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);

#define RENDER_END_PARTICLE_RENDERING()                                        \
  glDisableVertexAttribArray(0);                                               \
  glDisableVertexAttribArray(1);

static GLfloat  S_texcoord_table_4x4[16][4];
static GLfloat  S_texcoord_table_8x8[64][4];
static GLfloat  S_texcoord_table_16x16[256][4];
static GLfloat  S_texcoord_table_floor_border[8][4];
static GLfloat  S_texcoord_table_ice_border[8][4];
static GLfloat  S_texcoord_table_grass_border[4 * 8][4];

static GLfloat  S_color_table[4] = {0.0f, 
                                    0.33333333333333f, 
                                    0.66666666666667f, 
                                    1.0f};

static int      S_num_sprites;

/*******************************************************************************
** render_generate_tables()
*******************************************************************************/
short int render_generate_tables()
{
  int i;
  GLfloat texcoords[17] = { 0.0f,     0.0625f,  0.1250f,  0.1875f,
                            0.2500f,  0.3125f,  0.3750f,  0.4375f,
                            0.5000f,  0.5625f,  0.6250f,  0.6875f,
                            0.7500f,  0.8125f,  0.8750f,  0.9375f,
                            1.0f};
  GLfloat borders[25] = { 0.0f,     0.015625f,  0.109375f,
                          0.1250f,  0.140625f,  0.234375f,
                          0.2500f,  0.265625f,  0.359375f,
                          0.3750f,  0.390625f,  0.484375f,
                          0.5000f,  0.515625f,  0.609375f,
                          0.6250f,  0.640625f,  0.734375f,
                          0.7500f,  0.765625f,  0.859375f,
                          0.8750f,  0.890625f,  0.984375f,
                          1.0f};

  /* 32x32 tiles in 128x128 texture */
  for (i = 0; i < 16; i++)
  {
    /* set x coordinates */
    S_texcoord_table_4x4[i][0] = texcoords[4 * (i % 4)];
    S_texcoord_table_4x4[i][2] = texcoords[4 * ((i % 4) + 1)];

    /* set y coordinates */
    S_texcoord_table_4x4[i][1] = texcoords[4 * (4 - (i / 4))];
    S_texcoord_table_4x4[i][3] = texcoords[4 * (3 - (i / 4))];
  }

  /* 32x32 tiles in 256x256 texture */
  for (i = 0; i < 64; i++)
  {
    /* set x coordinates */
    S_texcoord_table_8x8[i][0] = texcoords[2 * (i % 8)];
    S_texcoord_table_8x8[i][2] = texcoords[2 * ((i % 8) + 1)];

    /* set y coordinates */
    S_texcoord_table_8x8[i][1] = texcoords[2 * (8 - (i / 8))];
    S_texcoord_table_8x8[i][3] = texcoords[2 * (7 - (i / 8))];
  }

  /* 16x16 tiles in 256x256 texture */
  for (i = 0; i < 256; i++)
  {
    /* set x coordinates */
    S_texcoord_table_16x16[i][0] = texcoords[i % 16];
    S_texcoord_table_16x16[i][2] = texcoords[(i % 16) + 1];

    /* set y coordinates */
    S_texcoord_table_16x16[i][1] = texcoords[16 - (i / 16)];
    S_texcoord_table_16x16[i][3] = texcoords[15 - (i / 16)];
  }

  /* floor border on theme texture */
  S_texcoord_table_floor_border[0][0] = texcoords[12];
  S_texcoord_table_floor_border[0][2] = texcoords[13];
  S_texcoord_table_floor_border[0][1] = texcoords[16 - 8];
  S_texcoord_table_floor_border[0][3] = texcoords[16 - 9];

  S_texcoord_table_floor_border[1][0] = texcoords[13];
  S_texcoord_table_floor_border[1][2] = texcoords[15];
  S_texcoord_table_floor_border[1][1] = texcoords[16 - 8];
  S_texcoord_table_floor_border[1][3] = texcoords[16 - 9];

  S_texcoord_table_floor_border[2][0] = texcoords[15];
  S_texcoord_table_floor_border[2][2] = texcoords[16];
  S_texcoord_table_floor_border[2][1] = texcoords[16 - 8];
  S_texcoord_table_floor_border[2][3] = texcoords[16 - 9];

  S_texcoord_table_floor_border[3][0] = texcoords[12];
  S_texcoord_table_floor_border[3][2] = texcoords[13];
  S_texcoord_table_floor_border[3][1] = texcoords[16 - 9];
  S_texcoord_table_floor_border[3][3] = texcoords[16 - 11];

  S_texcoord_table_floor_border[4][0] = texcoords[15];
  S_texcoord_table_floor_border[4][2] = texcoords[16];
  S_texcoord_table_floor_border[4][1] = texcoords[16 - 9];
  S_texcoord_table_floor_border[4][3] = texcoords[16 - 11];

  S_texcoord_table_floor_border[5][0] = texcoords[12];
  S_texcoord_table_floor_border[5][2] = texcoords[13];
  S_texcoord_table_floor_border[5][1] = texcoords[16 - 11];
  S_texcoord_table_floor_border[5][3] = texcoords[16 - 12];

  S_texcoord_table_floor_border[6][0] = texcoords[13];
  S_texcoord_table_floor_border[6][2] = texcoords[15];
  S_texcoord_table_floor_border[6][1] = texcoords[16 - 11];
  S_texcoord_table_floor_border[6][3] = texcoords[16 - 12];

  S_texcoord_table_floor_border[7][0] = texcoords[15];
  S_texcoord_table_floor_border[7][2] = texcoords[16];
  S_texcoord_table_floor_border[7][1] = texcoords[16 - 11];
  S_texcoord_table_floor_border[7][3] = texcoords[16 - 12];

  /* ice border on environment texture */
  S_texcoord_table_ice_border[0][0] = borders[9];
  S_texcoord_table_ice_border[0][2] = borders[10];
  S_texcoord_table_ice_border[0][1] = borders[24 - 0];
  S_texcoord_table_ice_border[0][3] = borders[24 - 1];

  S_texcoord_table_ice_border[1][0] = borders[10];
  S_texcoord_table_ice_border[1][2] = borders[11];
  S_texcoord_table_ice_border[1][1] = borders[24 - 0];
  S_texcoord_table_ice_border[1][3] = borders[24 - 1];

  S_texcoord_table_ice_border[2][0] = borders[11];
  S_texcoord_table_ice_border[2][2] = borders[12];
  S_texcoord_table_ice_border[2][1] = borders[24 - 0];
  S_texcoord_table_ice_border[2][3] = borders[24 - 1];

  S_texcoord_table_ice_border[3][0] = borders[9];
  S_texcoord_table_ice_border[3][2] = borders[10];
  S_texcoord_table_ice_border[3][1] = borders[24 - 1];
  S_texcoord_table_ice_border[3][3] = borders[24 - 2];

  S_texcoord_table_ice_border[4][0] = borders[11];
  S_texcoord_table_ice_border[4][2] = borders[12];
  S_texcoord_table_ice_border[4][1] = borders[24 - 1];
  S_texcoord_table_ice_border[4][3] = borders[24 - 2];

  S_texcoord_table_ice_border[5][0] = borders[9];
  S_texcoord_table_ice_border[5][2] = borders[10];
  S_texcoord_table_ice_border[5][1] = borders[24 - 2];
  S_texcoord_table_ice_border[5][3] = borders[24 - 3];

  S_texcoord_table_ice_border[6][0] = borders[10];
  S_texcoord_table_ice_border[6][2] = borders[11];
  S_texcoord_table_ice_border[6][1] = borders[24 - 2];
  S_texcoord_table_ice_border[6][3] = borders[24 - 3];

  S_texcoord_table_ice_border[7][0] = borders[11];
  S_texcoord_table_ice_border[7][2] = borders[12];
  S_texcoord_table_ice_border[7][1] = borders[24 - 2];
  S_texcoord_table_ice_border[7][3] = borders[24 - 3];

  /* grass, sand, dirt, snow borders on environment texture */
  for (i = 0; i < 4; i++)
  {
    S_texcoord_table_grass_border[8 * i + 0][0] = borders[3 + 6 * i];
    S_texcoord_table_grass_border[8 * i + 0][2] = borders[4 + 6 * i];
    S_texcoord_table_grass_border[8 * i + 0][1] = borders[24 - 6];
    S_texcoord_table_grass_border[8 * i + 0][3] = borders[24 - 7];

    S_texcoord_table_grass_border[8 * i + 1][0] = borders[4 + 6 * i];
    S_texcoord_table_grass_border[8 * i + 1][2] = borders[5 + 6 * i];
    S_texcoord_table_grass_border[8 * i + 1][1] = borders[24 - 6];
    S_texcoord_table_grass_border[8 * i + 1][3] = borders[24 - 7];

    S_texcoord_table_grass_border[8 * i + 2][0] = borders[5 + 6 * i];
    S_texcoord_table_grass_border[8 * i + 2][2] = borders[6 + 6 * i];
    S_texcoord_table_grass_border[8 * i + 2][1] = borders[24 - 6];
    S_texcoord_table_grass_border[8 * i + 2][3] = borders[24 - 7];

    S_texcoord_table_grass_border[8 * i + 3][0] = borders[3 + 6 * i];
    S_texcoord_table_grass_border[8 * i + 3][2] = borders[4 + 6 * i];
    S_texcoord_table_grass_border[8 * i + 3][1] = borders[24 - 7];
    S_texcoord_table_grass_border[8 * i + 3][3] = borders[24 - 8];

    S_texcoord_table_grass_border[8 * i + 4][0] = borders[5 + 6 * i];
    S_texcoord_table_grass_border[8 * i + 4][2] = borders[6 + 6 * i];
    S_texcoord_table_grass_border[8 * i + 4][1] = borders[24 - 7];
    S_texcoord_table_grass_border[8 * i + 4][3] = borders[24 - 8];

    S_texcoord_table_grass_border[8 * i + 5][0] = borders[3 + 6 * i];
    S_texcoord_table_grass_border[8 * i + 5][2] = borders[4 + 6 * i];
    S_texcoord_table_grass_border[8 * i + 5][1] = borders[24 - 8];
    S_texcoord_table_grass_border[8 * i + 5][3] = borders[24 - 9];

    S_texcoord_table_grass_border[8 * i + 6][0] = borders[4 + 6 * i];
    S_texcoord_table_grass_border[8 * i + 6][2] = borders[5 + 6 * i];
    S_texcoord_table_grass_border[8 * i + 6][1] = borders[24 - 8];
    S_texcoord_table_grass_border[8 * i + 6][3] = borders[24 - 9];

    S_texcoord_table_grass_border[8 * i + 7][0] = borders[5 + 6 * i];
    S_texcoord_table_grass_border[8 * i + 7][2] = borders[6 + 6 * i];
    S_texcoord_table_grass_border[8 * i + 7][1] = borders[24 - 8];
    S_texcoord_table_grass_border[8 * i + 7][3] = borders[24 - 9];
  }

  return 0;
}

/*******************************************************************************
** render_text_string()
*******************************************************************************/
short int render_text_string(char* str, int x, int y, GLfloat z)
{
  int index;
  int current_x;
  int ascii_code;

  if (str == NULL)
    return 1;

  /* initialize variables */
  index = 0;
  current_x = x;
  ascii_code = 0;

  while (str[index] != '\0')
  {
    if ((str[index] >= 0) && (str[index] <= 127))
      ascii_code = (int) str[index];
    else
      ascii_code = (int) (str[index] + 256);

    RENDER_ADD_SPRITE_TO_BUFFER(current_x, y,
                                current_x + 16.0f, y + 16.0f, z,
                                S_texcoord_table_16x16[ascii_code][0],
                                S_texcoord_table_16x16[ascii_code][1],
                                S_texcoord_table_16x16[ascii_code][2],
                                S_texcoord_table_16x16[ascii_code][3])

    current_x += 16;
    index++;
  }

  return 0;
}

/*******************************************************************************
** render_text_single_digit()
*******************************************************************************/
short int render_text_single_digit(int val, int x, int y, GLfloat z)
{
  int ascii_code;

  if (val < 0)
    return 1;

  /* determine ascii code */
  if (val == 0)
    ascii_code = '0';
  else if (val == 1)
    ascii_code = '1';
  else if (val == 2)
    ascii_code = '2';
  else if (val == 3)
    ascii_code = '3';
  else if (val == 4)
    ascii_code = '4';
  else if (val == 5)
    ascii_code = '5';
  else if (val == 6)
    ascii_code = '6';
  else if (val == 7)
    ascii_code = '7';
  else if (val == 8)
    ascii_code = '8';
  else
    ascii_code = '9';

  /* print character */
  RENDER_ADD_SPRITE_TO_BUFFER(x, y, x + 16.0f, y + 16.0f, z,
                              S_texcoord_table_16x16[ascii_code][0],
                              S_texcoord_table_16x16[ascii_code][1],
                              S_texcoord_table_16x16[ascii_code][2],
                              S_texcoord_table_16x16[ascii_code][3])

  return 0;
}

/*******************************************************************************
** render_text_double_digit()
*******************************************************************************/
short int render_text_double_digit(int val, int x, int y, GLfloat z)
{
  int ascii_code;

  if (val < 0)
    return 1;

  /* single digit value */
  if ((val >= 0) && (val < 10))
  {
    /* determine ascii code of units place */
    if (val % 10 == 0)
      ascii_code = '0';
    else if (val % 10 == 1)
      ascii_code = '1';
    else if (val % 10 == 2)
      ascii_code = '2';
    else if (val % 10 == 3)
      ascii_code = '3';
    else if (val % 10 == 4)
      ascii_code = '4';
    else if (val % 10 == 5)
      ascii_code = '5';
    else if (val % 10 == 6)
      ascii_code = '6';
    else if (val % 10 == 7)
      ascii_code = '7';
    else if (val % 10 == 8)
      ascii_code = '8';
    else
      ascii_code = '9';

    /* print units place character */
    RENDER_ADD_SPRITE_TO_BUFFER(x + 8.0f, y, x + 24.0f, y + 16.0f, z,
                                S_texcoord_table_16x16[ascii_code][0],
                                S_texcoord_table_16x16[ascii_code][1],
                                S_texcoord_table_16x16[ascii_code][2],
                                S_texcoord_table_16x16[ascii_code][3])
  }
  /* double digit value */
  else if ((val >= 10) && (val < 100))
  {
    /* determine ascii code of tens place */
    if (val / 10 == 0)
      ascii_code = '0';
    else if (val / 10 == 1)
      ascii_code = '1';
    else if (val / 10 == 2)
      ascii_code = '2';
    else if (val / 10 == 3)
      ascii_code = '3';
    else if (val / 10 == 4)
      ascii_code = '4';
    else if (val / 10 == 5)
      ascii_code = '5';
    else if (val/ 10  == 6)
      ascii_code = '6';
    else if (val / 10 == 7)
      ascii_code = '7';
    else if (val / 10 == 8)
      ascii_code = '8';
    else
      ascii_code = '9';

    /* print tens place character */
    RENDER_ADD_SPRITE_TO_BUFFER(x, y, x + 16.0f, y + 16.0f, z,
                                S_texcoord_table_16x16[ascii_code][0],
                                S_texcoord_table_16x16[ascii_code][1],
                                S_texcoord_table_16x16[ascii_code][2],
                                S_texcoord_table_16x16[ascii_code][3])

    /* determine ascii code of units place */
    if (val % 10 == 0)
      ascii_code = '0';
    else if (val % 10 == 1)
      ascii_code = '1';
    else if (val % 10 == 2)
      ascii_code = '2';
    else if (val % 10 == 3)
      ascii_code = '3';
    else if (val % 10 == 4)
      ascii_code = '4';
    else if (val % 10 == 5)
      ascii_code = '5';
    else if (val % 10 == 6)
      ascii_code = '6';
    else if (val % 10 == 7)
      ascii_code = '7';
    else if (val % 10 == 8)
      ascii_code = '8';
    else
      ascii_code = '9';

    /* print units place character */
    RENDER_ADD_SPRITE_TO_BUFFER(x + 16.0f, y, x + 32.0f, y + 16.0f, z,
                                S_texcoord_table_16x16[ascii_code][0],
                                S_texcoord_table_16x16[ascii_code][1],
                                S_texcoord_table_16x16[ascii_code][2],
                                S_texcoord_table_16x16[ascii_code][3])
  }
  /* otherwise, cap displayed value at 99 */
  else
  {
    ascii_code = '9';

    RENDER_ADD_SPRITE_TO_BUFFER(x, y, x + 16.0f, y + 16.0f, z,
                                S_texcoord_table_16x16[ascii_code][0],
                                S_texcoord_table_16x16[ascii_code][1],
                                S_texcoord_table_16x16[ascii_code][2],
                                S_texcoord_table_16x16[ascii_code][3])

    RENDER_ADD_SPRITE_TO_BUFFER(x + 16.0f, y, x + 32.0f, y + 16.0f, z,
                                S_texcoord_table_16x16[ascii_code][0],
                                S_texcoord_table_16x16[ascii_code][1],
                                S_texcoord_table_16x16[ascii_code][2],
                                S_texcoord_table_16x16[ascii_code][3])
  }

  return 0;
}

/*******************************************************************************
** render_text_triple_digit()
*******************************************************************************/
short int render_text_triple_digit(int val, int x, int y, GLfloat z)
{
  int ascii_code;

  if (val < 0)
    return 1;

  /* single digit value */
  if ((val >= 0) && (val < 10))
  {
    /* determine ascii code of units place */
    if (val % 10 == 0)
      ascii_code = '0';
    else if (val % 10 == 1)
      ascii_code = '1';
    else if (val % 10 == 2)
      ascii_code = '2';
    else if (val % 10 == 3)
      ascii_code = '3';
    else if (val % 10 == 4)
      ascii_code = '4';
    else if (val % 10 == 5)
      ascii_code = '5';
    else if (val % 10 == 6)
      ascii_code = '6';
    else if (val % 10 == 7)
      ascii_code = '7';
    else if (val % 10 == 8)
      ascii_code = '8';
    else
      ascii_code = '9';

    /* print units place character */
    RENDER_ADD_SPRITE_TO_BUFFER(x + 16.0f, y, x + 32.0f, y + 16.0f, z,
                                S_texcoord_table_16x16[ascii_code][0],
                                S_texcoord_table_16x16[ascii_code][1],
                                S_texcoord_table_16x16[ascii_code][2],
                                S_texcoord_table_16x16[ascii_code][3])
  }
  /* double digit value */
  else if ((val >= 10) && (val < 100))
  {
    /* determine ascii code of tens place */
    if (val / 10 == 0)
      ascii_code = '0';
    else if (val / 10 == 1)
      ascii_code = '1';
    else if (val / 10 == 2)
      ascii_code = '2';
    else if (val / 10 == 3)
      ascii_code = '3';
    else if (val / 10 == 4)
      ascii_code = '4';
    else if (val / 10 == 5)
      ascii_code = '5';
    else if (val/ 10  == 6)
      ascii_code = '6';
    else if (val / 10 == 7)
      ascii_code = '7';
    else if (val / 10 == 8)
      ascii_code = '8';
    else
      ascii_code = '9';

    /* print tens place character */
    RENDER_ADD_SPRITE_TO_BUFFER(x + 8.0f, y, x + 24.0f, y + 16.0f, z,
                                S_texcoord_table_16x16[ascii_code][0],
                                S_texcoord_table_16x16[ascii_code][1],
                                S_texcoord_table_16x16[ascii_code][2],
                                S_texcoord_table_16x16[ascii_code][3])

    /* determine ascii code of units place */
    if (val % 10 == 0)
      ascii_code = '0';
    else if (val % 10 == 1)
      ascii_code = '1';
    else if (val % 10 == 2)
      ascii_code = '2';
    else if (val % 10 == 3)
      ascii_code = '3';
    else if (val % 10 == 4)
      ascii_code = '4';
    else if (val % 10 == 5)
      ascii_code = '5';
    else if (val % 10 == 6)
      ascii_code = '6';
    else if (val % 10 == 7)
      ascii_code = '7';
    else if (val % 10 == 8)
      ascii_code = '8';
    else
      ascii_code = '9';

    /* print units place character */
    RENDER_ADD_SPRITE_TO_BUFFER(x + 24.0f, y, x + 40.0f, y + 16.0f, z,
                                S_texcoord_table_16x16[ascii_code][0],
                                S_texcoord_table_16x16[ascii_code][1],
                                S_texcoord_table_16x16[ascii_code][2],
                                S_texcoord_table_16x16[ascii_code][3])
  }
  /* triple digit value */
  else if ((val >= 100) && (val < 1000))
  {
    /* determine ascii code of hundreds place */
    if (val / 100 == 0)
      ascii_code = '0';
    else if (val / 100 == 1)
      ascii_code = '1';
    else if (val / 100 == 2)
      ascii_code = '2';
    else if (val / 100 == 3)
      ascii_code = '3';
    else if (val / 100 == 4)
      ascii_code = '4';
    else if (val / 100 == 5)
      ascii_code = '5';
    else if (val / 100 == 6)
      ascii_code = '6';
    else if (val / 100 == 7)
      ascii_code = '7';
    else if (val / 100 == 8)
      ascii_code = '8';
    else
      ascii_code = '9';

    /* print hundred place character */
    RENDER_ADD_SPRITE_TO_BUFFER(x, y, x + 16.0f, y + 16.0f, z,
                                S_texcoord_table_16x16[ascii_code][0],
                                S_texcoord_table_16x16[ascii_code][1],
                                S_texcoord_table_16x16[ascii_code][2],
                                S_texcoord_table_16x16[ascii_code][3])

    /* determine ascii code of tens place */
    if ((val / 10) % 10 == 0)
      ascii_code = '0';
    else if ((val / 10) % 10 == 1)
      ascii_code = '1';
    else if ((val / 10) % 10 == 2)
      ascii_code = '2';
    else if ((val / 10) % 10 == 3)
      ascii_code = '3';
    else if ((val / 10) % 10 == 4)
      ascii_code = '4';
    else if ((val / 10) % 10 == 5)
      ascii_code = '5';
    else if ((val / 10) % 10 == 6)
      ascii_code = '6';
    else if ((val / 10) % 10 == 7)
      ascii_code = '7';
    else if ((val / 10) % 10 == 8)
      ascii_code = '8';
    else
      ascii_code = '9';

    /* print tens place character */
    RENDER_ADD_SPRITE_TO_BUFFER(x + 16.0f, y, x + 32.0f, y + 16.0f, z,
                                S_texcoord_table_16x16[ascii_code][0],
                                S_texcoord_table_16x16[ascii_code][1],
                                S_texcoord_table_16x16[ascii_code][2],
                                S_texcoord_table_16x16[ascii_code][3])

    /* determine ascii code of units place */
    if (val % 10 == 0)
      ascii_code = '0';
    else if (val % 10 == 1)
      ascii_code = '1';
    else if (val % 10 == 2)
      ascii_code = '2';
    else if (val % 10 == 3)
      ascii_code = '3';
    else if (val % 10 == 4)
      ascii_code = '4';
    else if (val % 10 == 5)
      ascii_code = '5';
    else if (val % 10 == 6)
      ascii_code = '6';
    else if (val % 10 == 7)
      ascii_code = '7';
    else if (val % 10 == 8)
      ascii_code = '8';
    else
      ascii_code = '9';

    /* print units place character */
    RENDER_ADD_SPRITE_TO_BUFFER(x + 32.0f, y, x + 48.0f, y + 16.0f, z,
                                S_texcoord_table_16x16[ascii_code][0],
                                S_texcoord_table_16x16[ascii_code][1],
                                S_texcoord_table_16x16[ascii_code][2],
                                S_texcoord_table_16x16[ascii_code][3])
  }
  /* otherwise, cap displayed value at 999 */
  else
  {
    ascii_code = '9';

    RENDER_ADD_SPRITE_TO_BUFFER(x, y, x + 16.0f, y + 16.0f, z,
                                S_texcoord_table_16x16[ascii_code][0],
                                S_texcoord_table_16x16[ascii_code][1],
                                S_texcoord_table_16x16[ascii_code][2],
                                S_texcoord_table_16x16[ascii_code][3])

    RENDER_ADD_SPRITE_TO_BUFFER(x + 16.0f, y, x + 32.0f, y + 16.0f, z,
                                S_texcoord_table_16x16[ascii_code][0],
                                S_texcoord_table_16x16[ascii_code][1],
                                S_texcoord_table_16x16[ascii_code][2],
                                S_texcoord_table_16x16[ascii_code][3])

    RENDER_ADD_SPRITE_TO_BUFFER(x + 32.0f, y, x + 48.0f, y + 16.0f, z,
                                S_texcoord_table_16x16[ascii_code][0],
                                S_texcoord_table_16x16[ascii_code][1],
                                S_texcoord_table_16x16[ascii_code][2],
                                S_texcoord_table_16x16[ascii_code][3])
  }

  return 0;
}

/*******************************************************************************
** render_full_screen_panel()
*******************************************************************************/
short int render_full_screen_panel()
{
  int i;
  int j;

  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_HUD_PICKUPS)

  /* top */
  RENDER_ADD_SPRITE_TO_BUFFER(0.0f, 0.0f, 16.0f, 16.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 1.0f, 0.0625f, 0.9375f)

  RENDER_ADD_SPRITE_TO_BUFFER(16.0f, 0.0f, 208.0f, 8.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.84375f, 0.875f, 0.8125f)

  RENDER_ADD_SPRITE_TO_BUFFER(208.0f, 0.0f, 400.0f, 8.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.84375f, 0.875f, 0.8125f)

  RENDER_ADD_SPRITE_TO_BUFFER(400.0f, 0.0f, 592.0f, 8.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.84375f, 0.875f, 0.8125f)

  RENDER_ADD_SPRITE_TO_BUFFER(592.0f, 0.0f, 624.0f, 8.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.84375f, 0.25f, 0.8125f)

  RENDER_ADD_SPRITE_TO_BUFFER(16.0f, 8.0f, 208.0f, 16.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.78125f, 0.875f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(208.0f, 8.0f, 400.0f, 16.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.78125f, 0.875f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(400.0f, 8.0f, 592.0f, 16.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.78125f, 0.875f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(592.0f, 8.0f, 624.0f, 16.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.78125f, 0.25f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(624.0f, 0.0f, 640.0f, 16.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 1.0f, 0.125f, 0.9375f)

  /* bottom */
  RENDER_ADD_SPRITE_TO_BUFFER(0.0f, 464.0f, 16.0f, 480.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.9375f, 0.0625f, 0.875f)

  RENDER_ADD_SPRITE_TO_BUFFER(16.0f, 472.0f, 208.0f, 480.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.8125f, 0.875f, 0.78125f)

  RENDER_ADD_SPRITE_TO_BUFFER(208.0f, 472.0f, 400.0f, 480.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.8125f, 0.875f, 0.78125f)

  RENDER_ADD_SPRITE_TO_BUFFER(400.0f, 472.0f, 592.0f, 480.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.8125f, 0.875f, 0.78125f)

  RENDER_ADD_SPRITE_TO_BUFFER(592.0f, 472.0f, 624.0f, 480.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.8125f, 0.25f, 0.78125f)

  RENDER_ADD_SPRITE_TO_BUFFER(16.0f, 464.0f, 208.0f, 472.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.78125f, 0.875f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(208.0f, 464.0f, 400.0f, 472.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.78125f, 0.875f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(400.0f, 464.0f, 592.0f, 472.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.78125f, 0.875f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(592.0f, 464.0f, 624.0f, 472.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.78125f, 0.25f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(624.0f, 464.0f, 640.0f, 480.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.9375f, 0.125f, 0.875f)

  /* left */
  RENDER_ADD_SPRITE_TO_BUFFER(0.0f, 16.0f, 8.0f, 112.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.875f, 0.03125f, 0.5f)

  RENDER_ADD_SPRITE_TO_BUFFER(0.0f, 112.0f, 8.0f, 208.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.875f, 0.03125f, 0.5f)

  RENDER_ADD_SPRITE_TO_BUFFER(0.0f, 208.0f, 8.0f, 304.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.875f, 0.03125f, 0.5f)

  RENDER_ADD_SPRITE_TO_BUFFER(0.0f, 304.0f, 8.0f, 400.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.875f, 0.03125f, 0.5f)

  RENDER_ADD_SPRITE_TO_BUFFER(0.0f, 400.0f, 8.0f, 464.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.875f, 0.03125f, 0.625f)

  RENDER_ADD_SPRITE_TO_BUFFER(8.0f, 16.0f, 16.0f, 112.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.5f)

  RENDER_ADD_SPRITE_TO_BUFFER(8.0f, 112.0f, 16.0f, 208.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.5f)

  RENDER_ADD_SPRITE_TO_BUFFER(8.0f, 208.0f, 16.0f, 304.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.5f)

  RENDER_ADD_SPRITE_TO_BUFFER(8.0f, 304.0f, 16.0f, 400.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.5f)

  RENDER_ADD_SPRITE_TO_BUFFER(8.0f, 400.0f, 16.0f, 464.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.625f)

  /* right */
  RENDER_ADD_SPRITE_TO_BUFFER(632.0f, 16.0f, 640.0f, 112.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.03125f, 0.875f, 0.0625f, 0.5f)

  RENDER_ADD_SPRITE_TO_BUFFER(632.0f, 112.0f, 640.0f, 208.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.03125f, 0.875f, 0.0625f, 0.5f)

  RENDER_ADD_SPRITE_TO_BUFFER(632.0f, 208.0f, 640.0f, 304.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.03125f, 0.875f, 0.0625f, 0.5f)

  RENDER_ADD_SPRITE_TO_BUFFER(632.0f, 304.0f, 640.0f, 400.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.03125f, 0.875f, 0.0625f, 0.5f)

  RENDER_ADD_SPRITE_TO_BUFFER(632.0f, 400.0f, 640.0f, 464.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.03125f, 0.875f, 0.0625f, 0.625f)

  RENDER_ADD_SPRITE_TO_BUFFER(624.0f, 16.0f, 632.0f, 112.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.5f)

  RENDER_ADD_SPRITE_TO_BUFFER(624.0f, 112.0f, 632.0f, 208.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.5f)

  RENDER_ADD_SPRITE_TO_BUFFER(624.0f, 208.0f, 632.0f, 304.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.5f)

  RENDER_ADD_SPRITE_TO_BUFFER(624.0f, 304.0f, 632.0f, 400.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.5f)

  RENDER_ADD_SPRITE_TO_BUFFER(624.0f, 400.0f, 632.0f, 464.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.625f)

  /* backdrop */
  for (i = 0; i < 19; i++)
  {
    for (j = 0; j < 14; j++)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(16.0f + (32.0f * i), 
                                      16.0f + (32.0f * j), 
                                      RENDER_LEVEL_HUD_FOREGROUND, 
                                      32.0f, 8x8, 22)
    }
  }

  /* title bar divider */
  RENDER_ADD_SPRITE_TO_BUFFER(32.0f, 72.0f, 224.0f, 80.0f, 
                              RENDER_LEVEL_HUD_FOREGROUND,
                              0.125f, 0.875f, 0.875f, 0.84375f)

  RENDER_ADD_SPRITE_TO_BUFFER(224.0f, 72.0f, 416.0f, 80.0f, 
                              RENDER_LEVEL_HUD_FOREGROUND,
                              0.125f, 0.875f, 0.875f, 0.84375f)

  RENDER_ADD_SPRITE_TO_BUFFER(416.0f, 72.0f, 608.0f, 80.0f, 
                              RENDER_LEVEL_HUD_FOREGROUND,
                              0.125f, 0.875f, 0.875f, 0.84375f)

  RENDER_FLUSH_SPRITES()

  return 0;
}

/*******************************************************************************
** render_scene()
*******************************************************************************/
short int render_scene()
{
  int       i;
  entity*   e;
  particle* p;

  /* initialize variables */
  S_num_sprites = 0;

  /* start rendering */
  RENDER_SETUP_VGA_OUTPUT()

  /* begin textured rendering */
  RENDER_BEGIN_SPRITE_RENDERING()

  /* render sprites */

  /* background, floor border, walls, portcullis */
  if (G_theme == THEME_FOYER)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_THEME_FOYER)
  }
  else if (G_theme == THEME_CRYPT)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_THEME_CRYPT)
  }
  else if (G_theme == THEME_WATERS)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_THEME_WATERS)
  }
  else if (G_theme == THEME_PERISTYLE)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_THEME_PERISTYLE)
  }
  else if (G_theme == THEME_LIBRARY)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_THEME_LIBRARY)
  }
  else if (G_theme == THEME_GARDENS)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_THEME_GARDENS)
  }
  else if (G_theme == THEME_DUNGEON)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_THEME_DUNGEON)
  }
  else if (G_theme == THEME_SHRINE)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_THEME_SHRINE)
  }
  else if (G_theme == THEME_LABYRINTH)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_THEME_LABYRINTH)
  }
  else if (G_theme == THEME_BALLROOM)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_THEME_BALLROOM)
  }
  else if (G_theme == THEME_PENTOMINO)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_THEME_PENTOMINO)
  }
  else if (G_theme == THEME_ARMORY)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_THEME_ARMORY)
  }
  else if (G_theme == THEME_YGGDRASIL)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_THEME_YGGDRASIL)
  }
  else if (G_theme == THEME_HEAVEN)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_THEME_HEAVEN)
  }
  else if (G_theme == THEME_FUTURE)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_THEME_FUTURE)
  }
  else if (G_theme == THEME_ALCHEMY)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_THEME_ALCHEMY)
  }
  else if (G_theme == THEME_ARENA)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_THEME_ARENA)
  }
  else if (G_theme == THEME_APOGEE)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_THEME_APOGEE)
  }
  else if (G_theme == THEME_PAGAN)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_THEME_PAGAN)
  }
  else if (G_theme == THEME_TIBET)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_THEME_TIBET)
  }
  else if (G_theme == THEME_GOLDEN)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_THEME_GOLDEN)
  }
  else if (G_theme == THEME_DESSERTS)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_THEME_DESSERTS)
  }
  else
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_THEME_FOYER)
  }

  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_BACKGROUND, 
                                    RENDER_LEVEL_BACKGROUND, 4x4)
  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_WALLS, 
                                    RENDER_LEVEL_BACKGROUND, 4x4)
  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_PORTCULLIS, 
                                    RENDER_LEVEL_BACKGROUND, 4x4)
  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_FLOOR_BORDERS, 
                                    RENDER_LEVEL_BORDER, floor_border)
  RENDER_FLUSH_SPRITES()

  /* water, environment, bridges, submerged objects, symbols */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_ENVIRONMENT_SYMBOLS_SUBMERGED)

  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_WATER, 
                                    RENDER_LEVEL_BACKGROUND, 16x16)
  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_GRASS_ICE, 
                                    RENDER_LEVEL_BACKGROUND, 8x8)
  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_GRASS_BORDERS, 
                                    RENDER_LEVEL_BORDER, grass_border)
  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_ICE_BORDERS, 
                                    RENDER_LEVEL_BORDER, ice_border)
  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_BRIDGES_SUBMERGED, 
                                    RENDER_LEVEL_FLOOR, 8x8)
  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_SYMBOLS, 
                                    RENDER_LEVEL_FLOOR, 8x8)
  RENDER_FLUSH_SPRITES()

  /* venusian roots */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_DOUBLE_SNAKE_FAERIE_VENUSIAN)

  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_VENUSIAN_ROOTS, 
                                    RENDER_LEVEL_FLOOR, 8x8)
  RENDER_FLUSH_SPRITES()

  /* traps (conveyers, arrows, floor spikes) */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_TRAPS)

  RENDER_ADD_SPRITES_FROM_CATEGORY_WITH_ROTATION( CATEGORY_INDEX_CONVEYERS, 
                                                  RENDER_LEVEL_BACKGROUND, 8x8)
  RENDER_ADD_SPRITES_FROM_CATEGORY_WITH_ROTATION( CATEGORY_INDEX_ARROWS, 
                                                  RENDER_LEVEL_FLOOR, 8x8)
  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_FLOOR_SPIKES, 
                                    RENDER_LEVEL_FLOOR, 16x16)
  RENDER_FLUSH_SPRITES()

  /* floor switches */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_SWITCHES)

  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_SWITCHES, 
                                    RENDER_LEVEL_FLOOR, 8x8)
  RENDER_FLUSH_SPRITES()

  /* vanished dice */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_PUSHABLE_OBJECTS)

  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_VANISHED_DICE, 
                                    RENDER_LEVEL_LOW, 8x8)
  RENDER_FLUSH_SPRITES()

  /* pushable objects */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_PUSHABLE_OBJECTS)

  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_PUSHABLE_OBJECTS,
                                    RENDER_LEVEL_MIDDLE, 8x8)
  RENDER_FLUSH_SPRITES()

  /* levers */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_SWITCHES)

  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_LEVERS, 
                                    RENDER_LEVEL_MIDDLE, 8x8)
  RENDER_FLUSH_SPRITES()

  /* pickups */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_HUD_PICKUPS)

  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_PICKUPS, 
                                    RENDER_LEVEL_MIDDLE, 8x8)
  RENDER_FLUSH_SPRITES()

  /* traps (ballistas, pinball kickers) */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_TRAPS)

  RENDER_ADD_SPRITES_FROM_CATEGORY_WITH_ROTATION( CATEGORY_INDEX_BALLISTAS, 
                                                  RENDER_LEVEL_HIGH, 8x8)
  RENDER_ADD_SPRITES_FROM_CATEGORY_WITH_ROTATION( CATEGORY_INDEX_PINBALL_KICKERS, 
                                                  RENDER_LEVEL_HIGH, 8x8)
  RENDER_FLUSH_SPRITES()

  /* obstacles, spells, explosions */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_OBSTACLES_SPELLS)

  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_OBSTACLES, 
                                    RENDER_LEVEL_HIGH, 8x8)
  RENDER_ADD_SPRITES_FROM_CATEGORY_WITH_ROTATION( CATEGORY_INDEX_SPELLS, 
                                                  RENDER_LEVEL_HIGH, 8x8)
  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_EVIL_EYES, 
                                    RENDER_LEVEL_HIGH, 8x8)
  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_EXPLOSIONS, 
                                    RENDER_LEVEL_HIGH, 8x8)
  RENDER_FLUSH_SPRITES()

  /* player */
  /* pumpkins, ghosts, masks */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_PLAYER_GHOST_PUMPKIN_MASK)

  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_PLAYER, 
                                    RENDER_LEVEL_HIGH, 8x8)
  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_PUMPKINS_GHOSTS_MASKS, 
                                    RENDER_LEVEL_HIGH, 8x8)
  RENDER_FLUSH_SPRITES()

  /* doubles, snakes, faeries, venusians */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_DOUBLE_SNAKE_FAERIE_VENUSIAN)

  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_DOUBLES, 
                                    RENDER_LEVEL_HIGH, 8x8)
  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_SNAKES_FAERIES_VENUSIANS, 
                                    RENDER_LEVEL_HIGH, 8x8)
  RENDER_FLUSH_SPRITES()

  /* reverse doubles, lil bots, wisps, frogs */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_REVERSE_DOUBLE_LIL_BOT_WISP_FROG)

  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_REVERSE_DOUBLES, 
                                    RENDER_LEVEL_HIGH, 8x8)
  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_LIL_BOTS_WISPS_FROGS, 
                                    RENDER_LEVEL_HIGH, 8x8)
  RENDER_FLUSH_SPRITES()

  /* imps, jiangshis */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_IMP_JIANGSHI)

  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_IMPS_JIANGSHIS, 
                                    RENDER_LEVEL_HIGH, 8x8)
  RENDER_FLUSH_SPRITES()

  /* undines, sorceresses, witches, guardians */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_UNDINE_SORCERESS_WITCH_GUARDIAN)

  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_UNDINES_SORCERESSES_WITCHES, 
                                    RENDER_LEVEL_HIGH, 8x8)
  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_GUARDIANS, 
                                    RENDER_LEVEL_HIGH, 8x8)
  RENDER_FLUSH_SPRITES()

  /* mummies, poltergeists, laser guns */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_MUMMY_POLTERGEIST_LASER_GUNS)

  RENDER_ADD_SPRITES_FROM_CATEGORY( CATEGORY_INDEX_MUMMIES_POLTERGEISTS, 
                                    RENDER_LEVEL_HIGH, 8x8)
  RENDER_ADD_SPRITES_FROM_CATEGORY_WITH_ROTATION( CATEGORY_INDEX_LASER_GUNS, 
                                                  RENDER_LEVEL_HIGH, 8x8)
  RENDER_FLUSH_SPRITES()

  /* render hud */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_HUD_PICKUPS)

  /* dividers */
  RENDER_ADD_SPRITE_TO_BUFFER(16.0f, 116.0f, 96.0f, 124.0f, 
                              RENDER_LEVEL_HUD_FOREGROUND,
                              0.125f, 0.875f, 0.4375f, 0.84375f)

  RENDER_ADD_SPRITE_TO_BUFFER(16.0f, 276.0f, 96.0f, 284.0f, 
                              RENDER_LEVEL_HUD_FOREGROUND,
                              0.125f, 0.875f, 0.4375f, 0.84375f)

  /* potions */
  RENDER_ADD_SPRITE_TO_BUFFER(24.0f, 136.0f, 56.0f, 168.0f, 
                              RENDER_LEVEL_HUD_FOREGROUND,
                              S_texcoord_table_8x8[26][0],
                              S_texcoord_table_8x8[26][1],
                              S_texcoord_table_8x8[26][2],
                              S_texcoord_table_8x8[26][3])

  RENDER_ADD_SPRITE_TO_BUFFER(24.0f, 184.0f, 56.0f, 216.0f, 
                              RENDER_LEVEL_HUD_FOREGROUND,
                              S_texcoord_table_8x8[27][0],
                              S_texcoord_table_8x8[27][1],
                              S_texcoord_table_8x8[27][2],
                              S_texcoord_table_8x8[27][3])

  RENDER_ADD_SPRITE_TO_BUFFER(24.0f, 232.0f, 56.0f, 264.0f, 
                              RENDER_LEVEL_HUD_FOREGROUND,
                              S_texcoord_table_8x8[28][0],
                              S_texcoord_table_8x8[28][1],
                              S_texcoord_table_8x8[28][2],
                              S_texcoord_table_8x8[28][3])

  RENDER_FLUSH_SPRITES()

  /* render text */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_FONT)

  render_text_string("World", 16, 16, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("Room", 24, 64, RENDER_LEVEL_HUD_FOREGROUND);

  render_text_string("-", 48, 40, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("-", 48, 88, RENDER_LEVEL_HUD_FOREGROUND);

  render_text_single_digit( G_current_episode, 
                            32, 40, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_single_digit( G_current_world, 
                            64, 40, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_single_digit( G_current_floor, 
                            32, 88, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_single_digit( G_current_room, 
                            64, 88, RENDER_LEVEL_HUD_FOREGROUND);

  render_text_single_digit( G_bat_transforms, 
                            72, 144, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_single_digit( G_blue_mana, 
                            72, 192, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_single_digit( G_green_mana, 
                            72, 240, RENDER_LEVEL_HUD_FOREGROUND);

  render_text_string("Time", 24, 296, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("Par", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("Best", 24, 392, RENDER_LEVEL_HUD_FOREGROUND);

  render_text_triple_digit( G_time_elapsed_ms / 1000, 
                            32, 320, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_triple_digit( G_par_time_ms / 1000, 
                            32, 368, RENDER_LEVEL_HUD_FOREGROUND);

  if (G_save_game_best_times[G_current_level_index] != 0)
  {
    render_text_triple_digit( G_save_game_best_times[G_current_level_index], 
                              32, 416, RENDER_LEVEL_HUD_FOREGROUND);
  }

  RENDER_FLUSH_SPRITES()

  /* end textured rendering */
  RENDER_END_SPRITE_RENDERING()

  /* begin particle rendering */
  RENDER_BEGIN_PARTICLE_RENDERING()

  /* render particles */
  for ( i = G_particle_start_i;
        i != G_particle_end_i;
        i = (i + 1) % WORLD_PARTICLES_MAX)
  {
    p = &G_particle_array[i];

    if (p->life_count <= 0)
      continue;

    RENDER_ADD_PARTICLE_TO_BUFFER((112.0f + (p->pos_x >> PARTICLE_MANTISSA) - 1),
                                  ((p->pos_y >> PARTICLE_MANTISSA) - 1),
                                  (112.0f + ((p->pos_x >> PARTICLE_MANTISSA) + 1)),
                                  ((p->pos_y >> PARTICLE_MANTISSA) + 1),
                                  RENDER_LEVEL_PARTICLE,
                                  S_color_table[p->color_r],
                                  S_color_table[p->color_g],
                                  S_color_table[p->color_b])
  }

  RENDER_FLUSH_PARTICLES()

  /* end particle rendering */
  RENDER_END_PARTICLE_RENDERING()

  return 0;
}

/*******************************************************************************
** render_pause_panel()
*******************************************************************************/
short int render_pause_panel()
{
  int i;

  /* initialize variables */
  S_num_sprites = 0;

  /* begin textured rendering */
  RENDER_BEGIN_SPRITE_RENDERING()

  /* render window */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_HUD_PICKUPS)

  /* top */
  RENDER_ADD_SPRITE_TO_BUFFER(256.0f, 208.0f, 272.0f, 224.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 1.0f, 0.0625f, 0.9375f)

  RENDER_ADD_SPRITE_TO_BUFFER(272.0f, 208.0f, 368.0f, 216.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.84375f, 0.5f, 0.8125f)

  RENDER_ADD_SPRITE_TO_BUFFER(272.0f, 216.0f, 368.0f, 224.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.78125f, 0.5f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(368.0f, 208.0f, 384.0f, 224.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 1.0f, 0.125f, 0.9375f)

  /* bottom */
  RENDER_ADD_SPRITE_TO_BUFFER(256.0f, 256.0f, 272.0f, 272.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.9375f, 0.0625f, 0.875f)

  RENDER_ADD_SPRITE_TO_BUFFER(272.0f, 256.0f, 368.0f, 264.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.78125f, 0.5f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(272.0f, 264.0f, 368.0f, 272.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.8125f, 0.5f, 0.78125f)

  RENDER_ADD_SPRITE_TO_BUFFER(368.0f, 256.0f, 384.0f, 272.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.9375f, 0.125f, 0.875f)

  /* left and right */
  RENDER_ADD_SPRITE_TO_BUFFER(256.0f, 224.0f, 264.0f, 256.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.875f, 0.03125f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(264.0f, 224.0f, 272.0f, 256.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(368.0f, 224.0f, 376.0f, 256.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(376.0f, 224.0f, 384.0f, 256.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.03125f, 0.875f, 0.0625f, 0.75f)

  /* center (backdrop) */
  for (i = 0; i < 3; i++)
  {
    RENDER_ADD_SPRITE_BY_TILE_INDEX(272.0f + (32.0f * i), 224.0f, 
                                    RENDER_LEVEL_HUD_FOREGROUND, 32.0f, 8x8, 22)
  }

  RENDER_FLUSH_SPRITES()

  /* render text */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_FONT)

  render_text_string("Paused", 272, 232, RENDER_LEVEL_HUD_FOREGROUND);

  RENDER_FLUSH_SPRITES()

  /* end textured rendering */
  RENDER_END_SPRITE_RENDERING()

  return 0;
}

/*******************************************************************************
** render_room_select_panel()
*******************************************************************************/
short int render_room_select_panel()
{
  int           i;
  int           j;
  unsigned char current_world_flags;

  /* initialize variables */
  S_num_sprites = 0;

  /* begin textured rendering */
  RENDER_BEGIN_SPRITE_RENDERING()

  /* render window */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_HUD_PICKUPS)

  /* top */
  RENDER_ADD_SPRITE_TO_BUFFER(160.0f, 160.0f, 176.0f, 176.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 1.0f, 0.0625f, 0.9375f)

  RENDER_ADD_SPRITE_TO_BUFFER(176.0f, 160.0f, 336.0f, 168.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.84375f, 0.75f, 0.8125f)

  RENDER_ADD_SPRITE_TO_BUFFER(336.0f, 160.0f, 464.0f, 168.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.84375f, 0.625f, 0.8125f)

  RENDER_ADD_SPRITE_TO_BUFFER(176.0f, 168.0f, 336.0f, 176.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.78125f, 0.75f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(336.0f, 168.0f, 464.0f, 176.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.78125f, 0.625f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(464.0f, 160.0f, 480.0f, 176.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 1.0f, 0.125f, 0.9375f)

  /* bottom */
  RENDER_ADD_SPRITE_TO_BUFFER(160.0f, 304.0f, 176.0f, 320.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.9375f, 0.0625f, 0.875f)

  RENDER_ADD_SPRITE_TO_BUFFER(176.0f, 304.0f, 336.0f, 312.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.78125f, 0.75f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(336.0f, 304.0f, 464.0f, 312.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.78125f, 0.625f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(176.0f, 312.0f, 336.0f, 320.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.8125f, 0.75f, 0.78125f)

  RENDER_ADD_SPRITE_TO_BUFFER(336.0f, 312.0f, 464.0f, 320.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.8125f, 0.625f, 0.78125f)

  RENDER_ADD_SPRITE_TO_BUFFER(464.0f, 304.0f, 480.0f, 320.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.9375f, 0.125f, 0.875f)

  /* left */
  RENDER_ADD_SPRITE_TO_BUFFER(160.0f, 176.0f, 168.0f, 240.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.875f, 0.03125f, 0.625f)

  RENDER_ADD_SPRITE_TO_BUFFER(160.0f, 240.0f, 168.0f, 304.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.875f, 0.03125f, 0.625f)

  RENDER_ADD_SPRITE_TO_BUFFER(168.0f, 176.0f, 176.0f, 240.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.625f)

  RENDER_ADD_SPRITE_TO_BUFFER(168.0f, 240.0f, 176.0f, 304.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.625f)

  /* right */
  RENDER_ADD_SPRITE_TO_BUFFER(464.0f, 176.0f, 472.0f, 240.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.625f)

  RENDER_ADD_SPRITE_TO_BUFFER(464.0f, 240.0f, 472.0f, 304.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.625f)

  RENDER_ADD_SPRITE_TO_BUFFER(472.0f, 176.0f, 480.0f, 240.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.03125f, 0.875f, 0.0625f, 0.625f)

  RENDER_ADD_SPRITE_TO_BUFFER(472.0f, 240.0f, 480.0f, 304.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.03125f, 0.875f, 0.0625f, 0.625f)

  /* center (backdrop) */
  for (i = 0; i < 9; i++)
  {
    for (j = 0; j < 4; j++)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(176.0f + (32.0f * i), 
                                      176.0f + (32.0f * j), 
                                      RENDER_LEVEL_HUD_FOREGROUND, 
                                      32.0f, 8x8, 22)
    }
  }

  RENDER_FLUSH_SPRITES()

  /* render text */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_FONT)

  render_text_string("Select Room:", 224, 184, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("F3:", 176, 216, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("F2:", 176, 248, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("F1:", 176, 280, RENDER_LEVEL_HUD_FOREGROUND);

  current_world_flags = G_save_game_flags[G_current_level_index / 15];

  for (i = 0; i < 5; i++)
  {
    for (j = 0; j < 3; j++)
    {
      /* render cursor */
      if (G_cursor_position == ((j * 5) + i))
      {
        render_text_string( ">", 
                            224 + (48 * i), 280 - (32 * j), 
                            RENDER_LEVEL_HUD_FOREGROUND);
      }

      /* render room numbers, if available */
      if ((j == 0) ||
          ((j == 1) && (current_world_flags & SAVE_GAME_FLAG_FLOOR_1)) ||
          ((j == 2) && (current_world_flags & SAVE_GAME_FLAG_FLOOR_2)))
      {
        render_text_single_digit( i + 1, 
                                  240 + (48 * i), 280 - (32 * j), 
                                  RENDER_LEVEL_HUD_FOREGROUND);
      }
      else
      {
        render_text_string( "-", 240 + (48 * i), 280 - (32 * j), 
                            RENDER_LEVEL_HUD_FOREGROUND);
      }
    }
  }

  /* render asterisks by incomplete rooms */
  if (!(current_world_flags & SAVE_GAME_FLAG_FLOOR_1))
  {
    if (!(current_world_flags & SAVE_GAME_FLAG_ROOM_1))
      render_text_string("*", 256, 280, RENDER_LEVEL_HUD_FOREGROUND);
    if (!(current_world_flags & SAVE_GAME_FLAG_ROOM_2))
      render_text_string("*", 304, 280, RENDER_LEVEL_HUD_FOREGROUND);
    if (!(current_world_flags & SAVE_GAME_FLAG_ROOM_3))
      render_text_string("*", 352, 280, RENDER_LEVEL_HUD_FOREGROUND);
    if (!(current_world_flags & SAVE_GAME_FLAG_ROOM_4))
      render_text_string("*", 400, 280, RENDER_LEVEL_HUD_FOREGROUND);
    if (!(current_world_flags & SAVE_GAME_FLAG_ROOM_5))
      render_text_string("*", 448, 280, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (!(current_world_flags & SAVE_GAME_FLAG_FLOOR_2))
  {
    if (!(current_world_flags & SAVE_GAME_FLAG_ROOM_1))
      render_text_string("*", 256, 248, RENDER_LEVEL_HUD_FOREGROUND);
    if (!(current_world_flags & SAVE_GAME_FLAG_ROOM_2))
      render_text_string("*", 304, 248, RENDER_LEVEL_HUD_FOREGROUND);
    if (!(current_world_flags & SAVE_GAME_FLAG_ROOM_3))
      render_text_string("*", 352, 248, RENDER_LEVEL_HUD_FOREGROUND);
    if (!(current_world_flags & SAVE_GAME_FLAG_ROOM_4))
      render_text_string("*", 400, 248, RENDER_LEVEL_HUD_FOREGROUND);
    if (!(current_world_flags & SAVE_GAME_FLAG_ROOM_5))
      render_text_string("*", 448, 248, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else
  {
    if (!(current_world_flags & SAVE_GAME_FLAG_ROOM_1))
      render_text_string("*", 256, 216, RENDER_LEVEL_HUD_FOREGROUND);
    if (!(current_world_flags & SAVE_GAME_FLAG_ROOM_2))
      render_text_string("*", 304, 216, RENDER_LEVEL_HUD_FOREGROUND);
    if (!(current_world_flags & SAVE_GAME_FLAG_ROOM_3))
      render_text_string("*", 352, 216, RENDER_LEVEL_HUD_FOREGROUND);
    if (!(current_world_flags & SAVE_GAME_FLAG_ROOM_4))
      render_text_string("*", 400, 216, RENDER_LEVEL_HUD_FOREGROUND);
    if (!(current_world_flags & SAVE_GAME_FLAG_ROOM_5))
      render_text_string("*", 448, 216, RENDER_LEVEL_HUD_FOREGROUND);
  }

  RENDER_FLUSH_SPRITES()

  /* end textured rendering */
  RENDER_END_SPRITE_RENDERING()

  return 0;
}

/*******************************************************************************
** render_options_panel()
*******************************************************************************/
short int render_options_panel()
{
  int i;
  int j;

  /* initialize variables */
  S_num_sprites = 0;

  /* begin textured rendering */
  RENDER_BEGIN_SPRITE_RENDERING()

  /* render window */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_HUD_PICKUPS)

  /* top */
  RENDER_ADD_SPRITE_TO_BUFFER(160.0f, 160.0f, 176.0f, 176.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 1.0f, 0.0625f, 0.9375f)

  RENDER_ADD_SPRITE_TO_BUFFER(176.0f, 160.0f, 336.0f, 168.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.84375f, 0.75f, 0.8125f)

  RENDER_ADD_SPRITE_TO_BUFFER(336.0f, 160.0f, 464.0f, 168.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.84375f, 0.625f, 0.8125f)

  RENDER_ADD_SPRITE_TO_BUFFER(176.0f, 168.0f, 336.0f, 176.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.78125f, 0.75f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(336.0f, 168.0f, 464.0f, 176.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.78125f, 0.625f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(464.0f, 160.0f, 480.0f, 176.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 1.0f, 0.125f, 0.9375f)

  /* bottom */
  RENDER_ADD_SPRITE_TO_BUFFER(160.0f, 304.0f, 176.0f, 320.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.9375f, 0.0625f, 0.875f)

  RENDER_ADD_SPRITE_TO_BUFFER(176.0f, 304.0f, 336.0f, 312.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.78125f, 0.75f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(336.0f, 304.0f, 464.0f, 312.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.78125f, 0.625f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(176.0f, 312.0f, 336.0f, 320.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.8125f, 0.75f, 0.78125f)

  RENDER_ADD_SPRITE_TO_BUFFER(336.0f, 312.0f, 464.0f, 320.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.8125f, 0.625f, 0.78125f)

  RENDER_ADD_SPRITE_TO_BUFFER(464.0f, 304.0f, 480.0f, 320.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.9375f, 0.125f, 0.875f)

  /* left */
  RENDER_ADD_SPRITE_TO_BUFFER(160.0f, 176.0f, 168.0f, 240.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.875f, 0.03125f, 0.625f)

  RENDER_ADD_SPRITE_TO_BUFFER(160.0f, 240.0f, 168.0f, 304.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.875f, 0.03125f, 0.625f)

  RENDER_ADD_SPRITE_TO_BUFFER(168.0f, 176.0f, 176.0f, 240.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.625f)

  RENDER_ADD_SPRITE_TO_BUFFER(168.0f, 240.0f, 176.0f, 304.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.625f)

  /* right */
  RENDER_ADD_SPRITE_TO_BUFFER(464.0f, 176.0f, 472.0f, 240.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.625f)

  RENDER_ADD_SPRITE_TO_BUFFER(464.0f, 240.0f, 472.0f, 304.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.625f)

  RENDER_ADD_SPRITE_TO_BUFFER(472.0f, 176.0f, 480.0f, 240.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.03125f, 0.875f, 0.0625f, 0.625f)

  RENDER_ADD_SPRITE_TO_BUFFER(472.0f, 240.0f, 480.0f, 304.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.03125f, 0.875f, 0.0625f, 0.625f)

  /* center (backdrop) */
  for (i = 0; i < 9; i++)
  {
    for (j = 0; j < 4; j++)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(176.0f + (32.0f * i), 
                                      176.0f + (32.0f * j), 
                                      RENDER_LEVEL_HUD_FOREGROUND, 
                                      32.0f, 8x8, 22)
    }
  }

  RENDER_FLUSH_SPRITES()

  /* render text */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_FONT)

  render_text_string("Options", 264, 184, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("Music:", 192, 216, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("SFX:", 192, 248, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("Window:", 192, 280, RENDER_LEVEL_HUD_FOREGROUND);

  for (i = 0; i < 9; i++)
  {
    if (G_music_volume == (i * 16))
      render_text_string("|", 320 + (i * 16), 216, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string(".", 320 + (i * 16), 216, RENDER_LEVEL_HUD_FOREGROUND);

    if (G_sfx_volume == (i * 16))
      render_text_string("|", 320 + (i * 16), 248, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string(".", 320 + (i * 16), 248, RENDER_LEVEL_HUD_FOREGROUND);
  }

  if (G_fullscreen_flag == 0x01)
    render_text_string("Full", 320, 280, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_window_h == GRAFX_WINDOW_HEIGHT_OPTION_1)
    render_text_string("640x480", 320, 280, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_window_h == GRAFX_WINDOW_HEIGHT_OPTION_2)
    render_text_string("960x720", 320, 280, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_window_h == GRAFX_WINDOW_HEIGHT_OPTION_3)
    render_text_string("1024x768", 320, 280, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_window_h == GRAFX_WINDOW_HEIGHT_OPTION_4)
    render_text_string("1440x1080", 320, 280, RENDER_LEVEL_HUD_FOREGROUND);

  if (G_cursor_position == 0)
    render_text_string(">", 176, 216, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_cursor_position == 1)
    render_text_string(">", 176, 248, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_cursor_position == 2)
    render_text_string(">", 176, 280, RENDER_LEVEL_HUD_FOREGROUND);

  RENDER_FLUSH_SPRITES()

  /* end textured rendering */
  RENDER_END_SPRITE_RENDERING()

  return 0;
}

/*******************************************************************************
** render_try_again_panel()
*******************************************************************************/
short int render_try_again_panel()
{
  int i;
  int j;

  /* initialize variables */
  S_num_sprites = 0;

  /* begin textured rendering */
  RENDER_BEGIN_SPRITE_RENDERING()

  /* render window */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_HUD_PICKUPS)

  /* top */
  RENDER_ADD_SPRITE_TO_BUFFER(224.0f, 176.0f, 240.0f, 192.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 1.0f, 0.0625f, 0.9375f)

  RENDER_ADD_SPRITE_TO_BUFFER(240.0f, 176.0f, 400.0f, 184.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.1875f, 0.84375f, 0.875f, 0.8125f)

  RENDER_ADD_SPRITE_TO_BUFFER(240.0f, 184.0f, 400.0f, 192.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.1875f, 0.78125f, 0.875f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(400.0f, 176.0f, 416.0f, 192.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 1.0f, 0.125f, 0.9375f)

  /* bottom */
  RENDER_ADD_SPRITE_TO_BUFFER(224.0f, 288.0f, 240.0f, 304.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.9375f, 0.0625f, 0.875f)

  RENDER_ADD_SPRITE_TO_BUFFER(240.0f, 288.0f, 400.0f, 296.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.1875f, 0.78125f, 0.75f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(240.0f, 296.0f, 400.0f, 304.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.1875f, 0.8125f, 0.75f, 0.78125f)

  RENDER_ADD_SPRITE_TO_BUFFER(400.0f, 288.0f, 416.0f, 304.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.9375f, 0.125f, 0.875f)

  /* left */
  RENDER_ADD_SPRITE_TO_BUFFER(224.0f, 192.0f, 232.0f, 224.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.875f, 0.03125f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(232.0f, 192.0f, 240.0f, 224.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(224.0f, 224.0f, 232.0f, 256.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.875f, 0.03125f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(232.0f, 224.0f, 240.0f, 256.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(224.0f, 256.0f, 232.0f, 288.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.875f, 0.03125f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(232.0f, 256.0f, 240.0f, 288.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.75f)

  /* right */
  RENDER_ADD_SPRITE_TO_BUFFER(400.0f, 192.0f, 408.0f, 224.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(408.0f, 192.0f, 416.0f, 224.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.03125f, 0.875f, 0.0625f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(400.0f, 224.0f, 408.0f, 256.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(408.0f, 224.0f, 416.0f, 256.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.03125f, 0.875f, 0.0625f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(400.0f, 256.0f, 408.0f, 288.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(408.0f, 256.0f, 416.0f, 288.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.03125f, 0.875f, 0.0625f, 0.75f)

  /* center (backdrop) */
  for (i = 0; i < 5; i++)
  {
    for (j = 0; j < 3; j++)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(240.0f + (32.0f * i), 
                                      192.0f + (32.0f * j), 
                                      RENDER_LEVEL_HUD_FOREGROUND, 
                                      32.0f, 8x8, 22)
    }
  }

  RENDER_FLUSH_SPRITES()

  /* render text */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_FONT)

  render_text_string("Try Again?", 240, 200, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("Yes", 296, 232, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("No", 296, 264, RENDER_LEVEL_HUD_FOREGROUND);

  if (G_cursor_position == 0)
    render_text_string(">", 280, 232, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_cursor_position == 1)
    render_text_string(">", 280, 264, RENDER_LEVEL_HUD_FOREGROUND);

  RENDER_FLUSH_SPRITES()

  /* end textured rendering */
  RENDER_END_SPRITE_RENDERING()

  return 0;
}

/*******************************************************************************
** render_menu_panel()
*******************************************************************************/
short int render_menu_panel()
{
  int i;
  int j;

  /* initialize variables */
  S_num_sprites = 0;

  /* begin textured rendering */
  RENDER_BEGIN_SPRITE_RENDERING()

  /* render window */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_HUD_PICKUPS)

  /* top */
  RENDER_ADD_SPRITE_TO_BUFFER(192.0f, 112.0f, 208.0f, 128.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 1.0f, 0.0625f, 0.9375f)

  RENDER_ADD_SPRITE_TO_BUFFER(208.0f, 112.0f, 400.0f, 120.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.84375f, 0.875f, 0.8125f)

  RENDER_ADD_SPRITE_TO_BUFFER(208.0f, 120.0f, 400.0f, 128.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.78125f, 0.875f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(400.0f, 112.0f, 432.0f, 120.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.84375f, 0.250f, 0.8125f)

  RENDER_ADD_SPRITE_TO_BUFFER(400.0f, 120.0f, 432.0f, 128.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.78125f, 0.250f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(432.0f, 112.0f, 448.0f, 128.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 1.0f, 0.125f, 0.9375f)

  /* bottom */
  RENDER_ADD_SPRITE_TO_BUFFER(192.0f, 352.0f, 208.0f, 368.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.9375f, 0.0625f, 0.875f)

  RENDER_ADD_SPRITE_TO_BUFFER(208.0f, 352.0f, 400.0f, 360.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.78125f, 0.875f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(208.0f, 360.0f, 400.0f, 368.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.8125f, 0.875f, 0.78125f)

  RENDER_ADD_SPRITE_TO_BUFFER(400.0f, 352.0f, 432.0f, 360.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.78125f, 0.250f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(400.0f, 360.0f, 432.0f, 368.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.125f, 0.8125f, 0.250f, 0.78125f)

  RENDER_ADD_SPRITE_TO_BUFFER(432.0f, 352.0f, 448.0f, 368.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.9375f, 0.125f, 0.875f)

  /* left */
  RENDER_ADD_SPRITE_TO_BUFFER(192.0f, 128.0f, 200.0f, 160.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.875f, 0.03125f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(200.0f, 128.0f, 208.0f, 160.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(192.0f, 160.0f, 200.0f, 192.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.875f, 0.03125f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(200.0f, 160.0f, 208.0f, 192.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(192.0f, 192.0f, 200.0f, 224.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.875f, 0.03125f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(200.0f, 192.0f, 208.0f, 224.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(192.0f, 224.0f, 200.0f, 256.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.875f, 0.03125f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(200.0f, 224.0f, 208.0f, 256.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(192.0f, 256.0f, 200.0f, 288.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.875f, 0.03125f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(200.0f, 256.0f, 208.0f, 288.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(192.0f, 288.0f, 200.0f, 320.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.875f, 0.03125f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(200.0f, 288.0f, 208.0f, 320.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(192.0f, 320.0f, 200.0f, 352.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0f, 0.875f, 0.03125f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(200.0f, 320.0f, 208.0f, 352.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.75f)

  /* right */
  RENDER_ADD_SPRITE_TO_BUFFER(432.0f, 128.0f, 440.0f, 160.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(440.0f, 128.0f, 448.0f, 160.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.03125f, 0.875f, 0.0625f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(432.0f, 160.0f, 440.0f, 192.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(440.0f, 160.0f, 448.0f, 192.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.03125f, 0.875f, 0.0625f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(432.0f, 192.0f, 440.0f, 224.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(440.0f, 192.0f, 448.0f, 224.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.03125f, 0.875f, 0.0625f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(432.0f, 224.0f, 440.0f, 256.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(440.0f, 224.0f, 448.0f, 256.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.03125f, 0.875f, 0.0625f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(432.0f, 256.0f, 440.0f, 288.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(440.0f, 256.0f, 448.0f, 288.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.03125f, 0.875f, 0.0625f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(432.0f, 288.0f, 440.0f, 320.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(440.0f, 288.0f, 448.0f, 320.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.03125f, 0.875f, 0.0625f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(432.0f, 320.0f, 440.0f, 352.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.0625f, 0.875f, 0.09375f, 0.75f)

  RENDER_ADD_SPRITE_TO_BUFFER(440.0f, 320.0f, 448.0f, 352.0f, 
                              RENDER_LEVEL_HUD_BACKGROUND,
                              0.03125f, 0.875f, 0.0625f, 0.75f)

  /* center (backdrop) */
  for (i = 0; i < 7; i++)
  {
    for (j = 0; j < 7; j++)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(208.0f + (32.0f * i), 
                                      128.0f + (32.0f * j), 
                                      RENDER_LEVEL_HUD_FOREGROUND, 
                                      32.0f, 8x8, 22)
    }
  }

  RENDER_FLUSH_SPRITES()

  /* render text */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_FONT)

  render_text_string("Menu", 288, 136, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("Back to Game", 224, 168, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("Retry Room", 224, 200, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("Room Select", 224, 232, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("Help", 224, 264, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("Options", 224, 296, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("Quit", 224, 328, RENDER_LEVEL_HUD_FOREGROUND);

  if (G_cursor_position == 0)
    render_text_string(">", 208, 168, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_cursor_position == 1)
    render_text_string(">", 208, 200, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_cursor_position == 2)
    render_text_string(">", 208, 232, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_cursor_position == 3)
    render_text_string(">", 208, 264, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_cursor_position == 4)
    render_text_string(">", 208, 296, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_cursor_position == 5)
    render_text_string(">", 208, 328, RENDER_LEVEL_HUD_FOREGROUND);

  RENDER_FLUSH_SPRITES()

  /* end textured rendering */
  RENDER_END_SPRITE_RENDERING()

  return 0;
}

/*******************************************************************************
** render_room_transition()
*******************************************************************************/
short int render_room_transition()
{
  int i;
  int j;

  if ((G_room_transition_frame < 0) || (G_room_transition_frame >= 60))
    return 0;

  /* initialize variables */
  S_num_sprites = 0;

  /* begin textured rendering */
  RENDER_BEGIN_SPRITE_RENDERING()

  /* set texture */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_HUD_PICKUPS)

  /* old room curtains */
  if (G_room_transition_frame > 30)
  {
    for (i = 0; i < 13; i++)
    {
      for (j = 0; j < 15; j++)
      {
        if ((i + j) > (60 - G_room_transition_frame))
          continue;

        if ((i + j) == (60 - G_room_transition_frame))
        {
          RENDER_ADD_SPRITE_TO_BUFFER(112.0f + (32.0f * i), 
                                      32.0f * j, 
                                      112.0f + (32.0f * (i + 1)), 
                                      32.0f * (j + 1),
                                      RENDER_LEVEL_HUD_FOREGROUND,
                                      0.875f, 1.0f, 1.0f, 0.875f)
        }
        else if ((i + j) == (59 - G_room_transition_frame))
        {
          RENDER_ADD_SPRITE_TO_BUFFER(112.0f + (32.0f * i), 
                                      32.0f * j, 
                                      112.0f + (32.0f * (i + 1)), 
                                      32.0f * (j + 1),
                                      RENDER_LEVEL_HUD_FOREGROUND,
                                      0.875f, 0.75f, 1.0f, 0.625f)
        }
        else
        {
          RENDER_ADD_SPRITE_TO_BUFFER(112.0f + (32.0f * i), 
                                      32.0f * j, 
                                      112.0f + (32.0f * (i + 1)), 
                                      32.0f * (j + 1),
                                      RENDER_LEVEL_HUD_FOREGROUND,
                                      0.75f, 0.75f, 0.875f, 0.625f)
        }
      }
    }
  }
  /* new room reveal */
  else
  {
    for (i = 0; i < 13; i++)
    {
      for (j = 0; j < 15; j++)
      {
        if ((i + j) < (27 - G_room_transition_frame))
          continue;

        if ((i + j) == (27 - G_room_transition_frame))
        {
          RENDER_ADD_SPRITE_TO_BUFFER(112.0f + (32.0f * i), 
                                      32.0f * j, 
                                      112.0f + (32.0f * (i + 1)), 
                                      32.0f * (j + 1),
                                      RENDER_LEVEL_HUD_FOREGROUND,
                                      0.875f, 0.25f, 1.0f, 0.125f)
        }
        else if ((i + j) == (28 - G_room_transition_frame))
        {
          RENDER_ADD_SPRITE_TO_BUFFER(112.0f + (32.0f * i), 
                                      32.0f * j, 
                                      112.0f + (32.0f * (i + 1)), 
                                      32.0f * (j + 1),
                                      RENDER_LEVEL_HUD_FOREGROUND,
                                      0.875f, 0.5f, 1.0f, 0.375f)
        }
        else
        {
          RENDER_ADD_SPRITE_TO_BUFFER(112.0f + (32.0f * i), 
                                      32.0f * j, 
                                      112.0f + (32.0f * (i + 1)), 
                                      32.0f * (j + 1),
                                      RENDER_LEVEL_HUD_FOREGROUND,
                                      0.75f, 0.75f, 0.875f, 0.625f)
        }
      }
    }
  }

  RENDER_FLUSH_SPRITES()

  /* end textured rendering */
  RENDER_END_SPRITE_RENDERING()

  return 0;
}

/*******************************************************************************
** render_title_screen()
*******************************************************************************/
short int render_title_screen()
{
  int cursor_x;
  int cursor_y;

  /* initialize variables */
  S_num_sprites = 0;

  /* start rendering */
  RENDER_SETUP_VGA_OUTPUT()

  /* begin textured rendering */
  RENDER_BEGIN_SPRITE_RENDERING()

  /* render window and cursor */
  render_full_screen_panel();

  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_HUD_PICKUPS)

  /* cursor */
  if (((G_cursor_position >= 0) && (G_cursor_position <= 2))  ||
      ((G_cursor_position >= 6) && (G_cursor_position <= 7)))
  {
    if ((G_cursor_position >= 0) && (G_cursor_position <= 2))
    {
      cursor_x = 232;
      cursor_y = 192 + (32 * G_cursor_position);
    }
    else if ((G_cursor_position >= 6) && (G_cursor_position <= 7))
    {
      cursor_x = 192;
      cursor_y = 208 + (32 * (G_cursor_position - 6));
    }

    if (G_silver_cursor_frame >= 36)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(cursor_x, cursor_y, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 32)
    }
    else if (G_silver_cursor_frame >= 24)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(cursor_x, cursor_y, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 40)
    }
    else if (G_silver_cursor_frame >= 12)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(cursor_x, cursor_y, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 48)
    }
    else
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(cursor_x, cursor_y, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 56)
    }
  }

  /* title */
  RENDER_ADD_SPRITE_TO_BUFFER(224.0f, 24.0f, 416.0f, 56.0f, 
                              RENDER_LEVEL_HUD_FOREGROUND,
                              0.125f, 1.0f, 0.875f, 0.875f)

  RENDER_FLUSH_SPRITES()

  /* render text */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_FONT)

  if ((G_cursor_position >= 0) && (G_cursor_position <= 2))
  {
    render_text_string("Play", 288, 200, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Credits", 264, 232, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Quit", 288, 264, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if ((G_cursor_position >= 3) && (G_cursor_position <= 5))
  {
    render_text_string("Select Save Slot", 192, 200, RENDER_LEVEL_HUD_FOREGROUND);

    if (G_cursor_position == 3)
      render_text_string("No. 1", 280, 232, RENDER_LEVEL_HUD_FOREGROUND);
    else if (G_cursor_position == 4)
      render_text_string("No. 2", 280, 232, RENDER_LEVEL_HUD_FOREGROUND);
    else if (G_cursor_position == 5)
      render_text_string("No. 3", 280, 232, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if ((G_cursor_position >= 6) && (G_cursor_position <= 7))
  {
    render_text_string("World Select", 224, 216, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Story Scenes", 224, 248, RENDER_LEVEL_HUD_FOREGROUND);
  }

  render_text_string("Version 1.2", 232, 408, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("2018-2021 Michael Behrens", 120, 440, RENDER_LEVEL_HUD_FOREGROUND);

  RENDER_FLUSH_SPRITES()

  /* render save game info */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_FONT)

  if ((G_cursor_position >= 3) && (G_cursor_position <= 5))
  {
    if (G_save_game_percentage == 255)
      render_text_string("* New Game *", 224, 264, RENDER_LEVEL_HUD_FOREGROUND);
    else
    {
      render_text_triple_digit( G_save_game_percentage, 216, 264, 
                                RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("%", 264, 264, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_double_digit( G_save_game_3_and_1_2_floppies, 320, 264, 
                                RENDER_LEVEL_HUD_FOREGROUND);
      render_text_double_digit( G_save_game_5_and_1_4_floppies, 392, 264, 
                                RENDER_LEVEL_HUD_FOREGROUND);

      RENDER_FLUSH_SPRITES()

      RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_HUD_PICKUPS)

      RENDER_ADD_SPRITE_BY_TILE_INDEX(288.0f, 256.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 29)

      RENDER_ADD_SPRITE_BY_TILE_INDEX(360.0f, 256.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 30)
    }
  }

  RENDER_FLUSH_SPRITES()

  /* render arrows by save game select */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_TRAPS)

  if ((G_cursor_position >= 3) && (G_cursor_position < 5))
  {
    RENDER_ADD_SPRITE_BY_TILE_INDEX(432.0f, 240.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 5)
  }

  if ((G_cursor_position > 3) && (G_cursor_position <= 5))
  {
    RENDER_ADD_SPRITE_BY_TILE_INDEX_180(176.0f, 240.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                        32.0f, 8x8, 5)
  }

  RENDER_FLUSH_SPRITES()

  /* vampires and bats for flavor */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_PLAYER_GHOST_PUMPKIN_MASK)

  RENDER_ADD_SPRITE_BY_TILE_INDEX(72.0f, 24.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                  32.0f, 8x8, 5)

  RENDER_ADD_SPRITE_BY_TILE_INDEX(144.0f, 24.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                  32.0f, 8x8, 0)

  RENDER_ADD_SPRITE_BY_TILE_INDEX(464.0f, 24.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                  32.0f, 8x8, 0)

  RENDER_ADD_SPRITE_BY_TILE_INDEX(536.0f, 24.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                  32.0f, 8x8, 5)

  RENDER_FLUSH_SPRITES()

  /* end textured rendering */
  RENDER_END_SPRITE_RENDERING()

  return 0;
}

/*******************************************************************************
** render_credits_screen()
*******************************************************************************/
short int render_credits_screen()
{
  /* initialize variables */
  S_num_sprites = 0;

  /* start rendering */
  RENDER_SETUP_VGA_OUTPUT()

  /* begin textured rendering */
  RENDER_BEGIN_SPRITE_RENDERING()

  /* render window */
  render_full_screen_panel();

  /* render text */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_FONT)

  render_text_string("Credits", 264, 32, RENDER_LEVEL_HUD_FOREGROUND);

  render_text_string("Design", 272, 104, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("Programming", 232, 136, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("Graphics", 256, 168, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("Sound Effects & Music", 152, 200, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("and Story by", 224, 232, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("Michael Behrens", 200, 264, RENDER_LEVEL_HUD_FOREGROUND);

  render_text_string("Thank you to everyone who gave", 80, 320, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("useful advice and moral support.", 64, 352, RENDER_LEVEL_HUD_FOREGROUND);

  render_text_string("No humans were bitten during the", 64, 408, RENDER_LEVEL_HUD_FOREGROUND);
  render_text_string("creation of this game.", 144, 440, RENDER_LEVEL_HUD_FOREGROUND);

  RENDER_FLUSH_SPRITES()

  /* faeries, etc for flavor */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_DOUBLE_SNAKE_FAERIE_VENUSIAN)

  RENDER_ADD_SPRITE_BY_TILE_INDEX(48.0f, 24.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                  32.0f, 8x8, 48)

  RENDER_ADD_SPRITE_BY_TILE_INDEX(104.0f, 24.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                  32.0f, 8x8, 34)

  RENDER_ADD_SPRITE_BY_TILE_INDEX(160.0f, 24.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                  32.0f, 8x8, 54)

  RENDER_ADD_SPRITE_BY_TILE_INDEX(216.0f, 24.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                  32.0f, 8x8, 56)

  RENDER_ADD_SPRITE_BY_TILE_INDEX(392.0f, 24.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                  32.0f, 8x8, 56)

  RENDER_ADD_SPRITE_BY_TILE_INDEX(448.0f, 24.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                  32.0f, 8x8, 54)

  RENDER_ADD_SPRITE_BY_TILE_INDEX(504.0f, 24.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                  32.0f, 8x8, 34)

  RENDER_ADD_SPRITE_BY_TILE_INDEX(560.0f, 24.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                  32.0f, 8x8, 52)

  RENDER_FLUSH_SPRITES()

  /* end textured rendering */
  RENDER_END_SPRITE_RENDERING()

  return 0;
}

/*******************************************************************************
** render_world_select_screen()
*******************************************************************************/
short int render_world_select_screen()
{
  int cursor_y;

  /* initialize variables */
  S_num_sprites = 0;

  /* start rendering */
  RENDER_SETUP_VGA_OUTPUT()

  /* begin textured rendering */
  RENDER_BEGIN_SPRITE_RENDERING()

  /* render cursor and windows */
  render_full_screen_panel();

  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_HUD_PICKUPS)

  /* dividers */
  RENDER_ADD_SPRITE_TO_BUFFER(128.0f, 176.0f, 320.0f, 184.0f, 
                              RENDER_LEVEL_HUD_FOREGROUND,
                              0.125f, 0.875f, 0.875f, 0.84375f)

  RENDER_ADD_SPRITE_TO_BUFFER(320.0f, 176.0f, 512.0f, 184.0f, 
                              RENDER_LEVEL_HUD_FOREGROUND,
                              0.125f, 0.875f, 0.875f, 0.84375f)

  RENDER_ADD_SPRITE_TO_BUFFER(128.0f, 344.0f, 320.0f, 352.0f, 
                              RENDER_LEVEL_HUD_FOREGROUND,
                              0.125f, 0.875f, 0.875f, 0.84375f)

  RENDER_ADD_SPRITE_TO_BUFFER(320.0f, 344.0f, 512.0f, 352.0f, 
                              RENDER_LEVEL_HUD_FOREGROUND,
                              0.125f, 0.875f, 0.875f, 0.84375f)

  /* cursor */
  if ((G_cursor_position >= 0) && (G_cursor_position <= 21))
  {
    if ((G_cursor_position >= 0) && (G_cursor_position < 18))
      cursor_y = 216 + (32 * (G_cursor_position % 3));
    else if ((G_cursor_position >= 18) && (G_cursor_position <= 21))
    {
      if (G_save_game_5_and_1_4_floppies == 3)
        cursor_y = 200 + (32 * (G_cursor_position - 18));
      else
        cursor_y = 216 + (32 * (G_cursor_position % 3));
    }

    if (G_silver_cursor_frame >= 36)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(32.0f, cursor_y, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 32)
    }
    else if (G_silver_cursor_frame >= 24)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(32.0f, cursor_y, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 40)
    }
    else if (G_silver_cursor_frame >= 12)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(32.0f, cursor_y, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 48)
    }
    else
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(32.0f, cursor_y, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 56)
    }
  }

  /* floppy disks */
  if ((G_cursor_position >= 0) && (G_cursor_position < 3))
  {
    if (G_save_game_flags[0] & SAVE_GAME_FLAG_FLOPPY)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(576.0f, 216.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 29)
    }

    if (G_save_game_flags[1] & SAVE_GAME_FLAG_FLOPPY)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(576.0f, 248.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 29)
    }

    if (G_save_game_flags[2] & SAVE_GAME_FLAG_FLOPPY)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(576.0f, 280.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 29)
    }
  }
  else if ((G_cursor_position >= 3) && (G_cursor_position < 6))
  {
    if (G_save_game_flags[3] & SAVE_GAME_FLAG_FLOPPY)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(576.0f, 216.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 29)
    }

    if (G_save_game_flags[4] & SAVE_GAME_FLAG_FLOPPY)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(576.0f, 248.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 29)
    }

    if (G_save_game_flags[5] & SAVE_GAME_FLAG_FLOPPY)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(576.0f, 280.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 29)
    }
  }
  else if ((G_cursor_position >= 6) && (G_cursor_position < 9))
  {
    if (G_save_game_flags[6] & SAVE_GAME_FLAG_FLOPPY)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(576.0f, 216.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 29)
    }

    if (G_save_game_flags[7] & SAVE_GAME_FLAG_FLOPPY)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(576.0f, 248.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 29)
    }

    if (G_save_game_flags[8] & SAVE_GAME_FLAG_FLOPPY)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(576.0f, 280.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 29)
    }
  }
  else if ((G_cursor_position >= 9) && (G_cursor_position < 12))
  {
    if (G_save_game_flags[9] & SAVE_GAME_FLAG_FLOPPY)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(576.0f, 216.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 29)
    }

    if (G_save_game_flags[10] & SAVE_GAME_FLAG_FLOPPY)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(576.0f, 248.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 29)
    }

    if (G_save_game_flags[11] & SAVE_GAME_FLAG_FLOPPY)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(576.0f, 280.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 29)
    }
  }
  else if ((G_cursor_position >= 12) && (G_cursor_position < 15))
  {
    if (G_save_game_flags[12] & SAVE_GAME_FLAG_FLOPPY)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(576.0f, 216.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 29)
    }

    if (G_save_game_flags[13] & SAVE_GAME_FLAG_FLOPPY)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(576.0f, 248.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 29)
    }

    if (G_save_game_flags[14] & SAVE_GAME_FLAG_FLOPPY)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(576.0f, 280.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 29)
    }
  }
  else if ((G_cursor_position >= 15) && (G_cursor_position < 18))
  {
    if (G_save_game_flags[15] & SAVE_GAME_FLAG_FLOPPY)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(576.0f, 216.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 29)
    }

    if (G_save_game_flags[16] & SAVE_GAME_FLAG_FLOPPY)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(576.0f, 248.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 29)
    }

    if (G_save_game_flags[17] & SAVE_GAME_FLAG_FLOPPY)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(576.0f, 280.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 29)
    }
  }
  else if ((G_cursor_position >= 18) && (G_cursor_position <= 21))
  {
    if (G_save_game_5_and_1_4_floppies == 3)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(576.0f, 200.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 30)

      RENDER_ADD_SPRITE_BY_TILE_INDEX(576.0f, 232.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 30)

      RENDER_ADD_SPRITE_BY_TILE_INDEX(576.0f, 264.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 30)
    }
    else
    {
      if (G_save_game_flags[18] & SAVE_GAME_FLAG_FLOPPY)
      {
        RENDER_ADD_SPRITE_BY_TILE_INDEX(576.0f, 216.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                        32.0f, 8x8, 30)
      }

      if (G_save_game_flags[19] & SAVE_GAME_FLAG_FLOPPY)
      {
        RENDER_ADD_SPRITE_BY_TILE_INDEX(576.0f, 248.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                        32.0f, 8x8, 30)
      }

      if (G_save_game_flags[20] & SAVE_GAME_FLAG_FLOPPY)
      {
        RENDER_ADD_SPRITE_BY_TILE_INDEX(576.0f, 280.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                        32.0f, 8x8, 30)
      }
    }
  }

  RENDER_FLUSH_SPRITES()

  /* render text */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_FONT)

  render_text_string("Select World!", 216, 32, RENDER_LEVEL_HUD_FOREGROUND);

  /* episode and world titles */
  if ((G_cursor_position >= 0) && (G_cursor_position < 3))
  {
    render_text_string("Episode 1", 248, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("When Bats Fly", 216, 136, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("World 1: Foyer of the Gods", 64, 224, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(0))
      render_text_string("World 2: The Crypt", 64, 256, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("World 2: ???", 64, 256, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(1))
      render_text_string("World 3: Charon's Waters", 64, 288, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("World 3: ???", 64, 288, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if ((G_cursor_position >= 3) && (G_cursor_position < 6))
  {
    render_text_string("Episode 2", 248, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Rumble in Romania", 184, 136, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(2))
      render_text_string("World 1: In The Peristyle", 64, 224, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("World 1: ???", 64, 224, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(3))
      render_text_string("World 2: The Duchess's Archives", 64, 256, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("World 2: ???", 64, 256, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(4))
      render_text_string("World 3: Gardens of Venus", 64, 288, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("World 3: ???", 64, 288, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if ((G_cursor_position >= 6) && (G_cursor_position < 9))
  {
    render_text_string("Episode 3", 248, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Elsewhere", 248, 136, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(5))
      render_text_string("World 1: Dimensional Prison", 64, 224, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("World 1: ???", 64, 224, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(6))
      render_text_string("World 2: Sunken Shrine", 64, 256, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("World 2: ???", 64, 256, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(7))
      render_text_string("World 3: The Labyrinth", 64, 288, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("World 3: ???", 64, 288, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if ((G_cursor_position >= 9) && (G_cursor_position < 12))
  {
    render_text_string("Episode 4", 248, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Death of the Party", 176, 136, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(8))
      render_text_string("World 1: The Silver Ballroom", 64, 224, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("World 1: ???", 64, 224, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(9))
      render_text_string("World 2: Pentomino's Quarters", 64, 256, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("World 2: ???", 64, 256, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(10))
      render_text_string("World 3: Armory d'Amour", 64, 288, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("World 3: ???", 64, 288, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if ((G_cursor_position >= 12) && (G_cursor_position < 15))
  {
    render_text_string("Episode 5", 248, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("To Heck With This!", 176, 136, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(11))
      render_text_string("World 1: Yggdrasil's Appendix", 64, 224, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("World 1: ???", 64, 224, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(12))
      render_text_string("World 2: Heaven", 64, 256, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("World 2: ???", 64, 256, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(13))
      render_text_string("World 3: The Far Future", 64, 288, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("World 3: ???", 64, 288, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if ((G_cursor_position >= 15) && (G_cursor_position < 18))
  {
    render_text_string("Episode 6", 248, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("G\x94ttervampyrung", 200, 136, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(14))
      render_text_string("World 1: Alchemy Lab", 64, 224, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("World 1: ???", 64, 224, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(15))
      render_text_string("World 2: Temple of Mars", 64, 256, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("World 2: ???", 64, 256, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(16))
      render_text_string("World 3: The Apogee", 64, 288, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("World 3: ???", 64, 288, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if ((G_cursor_position >= 18) && (G_cursor_position <= 21))
  {
    render_text_string("Episode 7", 248, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Please Insert Disk 2", 160, 136, RENDER_LEVEL_HUD_FOREGROUND);

    if (G_save_game_5_and_1_4_floppies == 3)
    {
      render_text_string("World 1: Vaults of Montezuma", 64, 208, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("World 2: Frozen Peak", 64, 240, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("World 3: The Golden Dawn", 64, 272, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("World 4: Just Desserts", 64, 304, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else
    {
      if (G_save_game_3_and_1_2_floppies >= 6)
        render_text_string("World 1: Vaults of Montezuma", 64, 224, RENDER_LEVEL_HUD_FOREGROUND);
      else
        render_text_string("World 1: ???", 64, 224, RENDER_LEVEL_HUD_FOREGROUND);

      if (G_save_game_3_and_1_2_floppies >= 12)
        render_text_string("World 2: Frozen Peak", 64, 256, RENDER_LEVEL_HUD_FOREGROUND);
      else
        render_text_string("World 2: ???", 64, 256, RENDER_LEVEL_HUD_FOREGROUND);

      if (G_save_game_3_and_1_2_floppies == 18)
        render_text_string("World 3: The Golden Dawn", 64, 288, RENDER_LEVEL_HUD_FOREGROUND);
      else
        render_text_string("World 3: ???", 64, 288, RENDER_LEVEL_HUD_FOREGROUND);
    }
  }

  /* world descriptions */
  if (G_cursor_position == 0)
  {
    render_text_string("The entrance to the tower.", 112, 388, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("What mysteries lie beyond?", 112, 420, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 1)
  {
    render_text_string("The land of the dead, the undead,", 56, 388, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("and the undecided.", 176, 420, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 2)
  {
    render_text_string("I sure hope the ferryman", 128, 388, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("has change for a 50.", 160, 420, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 3)
  {
    render_text_string("On the tower's grounds.", 136, 388, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("That's a bright moon tonight!", 88, 420, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 4)
  {
    render_text_string("The Duchess likes to read!", 112, 388, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("(They're mostly bodice rippers.)", 64, 420, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 5)
  {
    render_text_string("Why does the goddess of love", 96, 388, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("have man-eating plants?", 136, 420, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 6)
  {
    render_text_string("In a parallel dimension", 136, 388, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("somewhere in space and time.", 96, 420, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 7)
  {
    render_text_string("The lost shrine of the tritons.", 72, 388, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("(They're on vacation right now.)", 64, 420, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 8)
  {
    render_text_string("A puzzle made of puzzles.", 120, 388, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Daedalus needed to get out more!", 64, 420, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 9)
  {
    render_text_string("These flying chairs", 168, 388, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("are so annoying!", 192, 420, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 10)
  {
    render_text_string("Where the mad wizard Pentomino", 80, 388, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("performs his studies.", 152, 420, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 11)
  {
    render_text_string("The Armorer armors the world.", 88, 388, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("But who armors the Armorer?", 104, 420, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 12)
  {
    render_text_string("It's the end of the world...", 96, 388, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Literally!", 240, 420, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 13)
  {
    render_text_string("They really like harps up here.", 72, 388, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Big fans of arpeggios, I guess!", 72, 420, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 14)
  {
    render_text_string("So this is where", 192, 388, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("the lil' bots come from!", 128, 420, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 15)
  {
    render_text_string("The alchemists have transmuted", 80, 388, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("gold to toaster pastries. Far out!", 48, 420, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 16)
  {
    render_text_string("They say life is a battle.", 112, 388, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("But what about un-life?", 136, 420, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 17)
  {
    render_text_string("The top of the tower.", 152, 388, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("It's a long way down!", 152, 420, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 18)
  {
    render_text_string("This game takes place in 1337.", 80, 388, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("When did Montezuma reign?", 120, 420, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 19)
  {
    render_text_string("It's full of mysterious 'snow',", 72, 388, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("unknown to Southern California.", 72, 420, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 20)
  {
    render_text_string("Some of these levels", 160, 388, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("are a bit much!", 200, 420, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 21)
  {
    render_text_string("Outtakes, silliness,", 160, 388, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("& odds and ends.", 192, 420, RENDER_LEVEL_HUD_FOREGROUND);
  }

  RENDER_FLUSH_SPRITES()

  /* right arrows by episode select */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_TRAPS)

  if ((G_cursor_position >= 0) && (G_cursor_position < 3))
  {
    if ((SAVE_GAME_WORLD_IS_COMPLETE(2)) ||
        (G_save_game_3_and_1_2_floppies >= 6))
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(512.0f, 112.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 5)
    }
  }
  else if ((G_cursor_position >= 3) && (G_cursor_position < 6))
  {
    if ((SAVE_GAME_WORLD_IS_COMPLETE(5)) ||
        (G_save_game_3_and_1_2_floppies >= 6))
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(512.0f, 112.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 5)
    }
  }
  else if ((G_cursor_position >= 6) && (G_cursor_position < 9))
  {
    if ((SAVE_GAME_WORLD_IS_COMPLETE(8)) ||
        (G_save_game_3_and_1_2_floppies >= 6))
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(512.0f, 112.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 5)
    }
  }
  else if ((G_cursor_position >= 9) && (G_cursor_position < 12))
  {
    if ((SAVE_GAME_WORLD_IS_COMPLETE(11)) ||
        (G_save_game_3_and_1_2_floppies >= 6))
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(512.0f, 112.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 5)
    }
  }
  else if ((G_cursor_position >= 12) && (G_cursor_position < 15))
  {
    if ((SAVE_GAME_WORLD_IS_COMPLETE(14)) ||
        (G_save_game_3_and_1_2_floppies >= 6))
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(512.0f, 112.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 5)
    }
  }
  else if ((G_cursor_position >= 15) && (G_cursor_position < 18))
  {
    if (G_save_game_3_and_1_2_floppies >= 6)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(512.0f, 112.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 5)
    }
  }

  /* left arrows by episode select */
  if ((G_cursor_position >= 3) && (G_cursor_position <= 21))
  {
    RENDER_ADD_SPRITE_BY_TILE_INDEX_180(80.0f, 112.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                        32.0f, 8x8, 5)
  }

  RENDER_FLUSH_SPRITES()

  /* pumpkins, etc for flavor */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_PLAYER_GHOST_PUMPKIN_MASK)

  RENDER_ADD_SPRITE_BY_TILE_INDEX(48.0f, 24.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                  32.0f, 8x8, 32)

  RENDER_ADD_SPRITE_BY_TILE_INDEX(104.0f, 24.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                  32.0f, 8x8, 48)

  RENDER_ADD_SPRITE_BY_TILE_INDEX(160.0f, 24.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                  32.0f, 8x8, 34)

  RENDER_ADD_SPRITE_BY_TILE_INDEX(448.0f, 24.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                  32.0f, 8x8, 34)

  RENDER_ADD_SPRITE_BY_TILE_INDEX(504.0f, 24.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                  32.0f, 8x8, 48)

  RENDER_ADD_SPRITE_BY_TILE_INDEX(560.0f, 24.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                  32.0f, 8x8, 32)

  RENDER_FLUSH_SPRITES()

  /* end textured rendering */
  RENDER_END_SPRITE_RENDERING()

  return 0;
}

/*******************************************************************************
** render_story_select_screen()
*******************************************************************************/
short int render_story_select_screen()
{
  int cursor_x;
  int cursor_y;

  /* initialize variables */
  S_num_sprites = 0;

  /* start rendering */
  RENDER_SETUP_VGA_OUTPUT()

  /* begin textured rendering */
  RENDER_BEGIN_SPRITE_RENDERING()

  /* render window */
  render_full_screen_panel();

  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_HUD_PICKUPS)

  /* cursor */
  if ((G_cursor_position >= 0) && (G_cursor_position <= 19))
  {
    if ((G_cursor_position >= 0) && (G_cursor_position <= 9))
    {
      cursor_x = 128;
      cursor_y = 96 + (32 * G_cursor_position);
    }
    else if ((G_cursor_position >= 10) && (G_cursor_position <= 19))
    {
      cursor_x = 88;
      cursor_y = 96 + (32 * (G_cursor_position - 10));
    }

    if (G_silver_cursor_frame >= 36)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(cursor_x, cursor_y, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 32)
    }
    else if (G_silver_cursor_frame >= 24)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(cursor_x, cursor_y, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 40)
    }
    else if (G_silver_cursor_frame >= 12)
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(cursor_x, cursor_y, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 48)
    }
    else
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(cursor_x, cursor_y, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 56)
    }
  }

  RENDER_FLUSH_SPRITES()

  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_FONT)

  render_text_string("Story Scenes", 224, 32, RENDER_LEVEL_HUD_FOREGROUND);

  if ((G_cursor_position >= 0) && (G_cursor_position <= 9))
  {
    render_text_string("Prelude", 264, 104, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(0))
      render_text_string("You Shall Not Pass", 176, 136, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("???", 296, 136, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(1))
      render_text_string("Rise From Your Grave", 160, 168, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("???", 296, 168, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(2))
      render_text_string("Breaking The Law", 192, 200, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("???", 296, 200, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(3))
      render_text_string("Knock Knock", 232, 232, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("???", 296, 232, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(4))
      render_text_string("Too Hot to Handle", 184, 264, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("???", 296, 264, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(5))
      render_text_string("Queen of the Nymphs", 168, 296, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("???", 296, 296, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(6))
      render_text_string("Medusa's Brownies", 184, 328, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("???", 296, 328, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(7))
      render_text_string("\xADSilencio!", 240, 360, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("???", 296, 360, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(8))
      render_text_string("Negative Stereotypes", 160, 392, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("???", 296, 392, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 1", 272, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if ((G_cursor_position >= 10) && (G_cursor_position <= 19))
  {
    if (SAVE_GAME_WORLD_IS_COMPLETE(9))
      render_text_string("Her Soul is Still Dancing", 120, 104, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("???", 296, 104, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(10))
      render_text_string("Mental Gymnastics", 184, 136, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("???", 296, 136, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(11))
      render_text_string("The Armorer's Lament", 160, 168, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("???", 296, 168, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(12))
      render_text_string("End of the Line", 200, 200, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("???", 296, 200, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(13))
      render_text_string("Judgment Day", 224, 232, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("???", 296, 232, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(14))
      render_text_string("I Like Big Bots", 200, 264, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("???", 296, 264, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(15))
      render_text_string("An Eternal Question", 168, 296, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("???", 296, 296, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(16))
      render_text_string("Ode to War", 240, 328, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("???", 296, 328, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(17))
      render_text_string("The World Dies Screaming", 128, 360, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("???", 296, 360, RENDER_LEVEL_HUD_FOREGROUND);

    if (SAVE_GAME_WORLD_IS_COMPLETE(21))
      render_text_string("Afterword", 248, 392, RENDER_LEVEL_HUD_FOREGROUND);
    else
      render_text_string("???", 296, 392, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 2", 272, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }

  RENDER_FLUSH_SPRITES()

  /* left / right arrows by page number */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_TRAPS)

  if (((G_cursor_position >= 0) && (G_cursor_position <= 9))  &&
      (SAVE_GAME_WORLD_IS_COMPLETE(9)))
  {
    RENDER_ADD_SPRITE_BY_TILE_INDEX(384.0f, 432.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 5)
  }

  if ((G_cursor_position >= 10) && (G_cursor_position <= 19))
  {
    RENDER_ADD_SPRITE_BY_TILE_INDEX_180(224.0f, 432.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                        32.0f, 8x8, 5)
  }

  RENDER_FLUSH_SPRITES()

  /* undines, etc for flavor */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_UNDINE_SORCERESS_WITCH_GUARDIAN)

  RENDER_ADD_SPRITE_BY_TILE_INDEX(48.0f, 24.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                  32.0f, 8x8, 3)

  RENDER_ADD_SPRITE_BY_TILE_INDEX(104.0f, 24.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                  32.0f, 8x8, 7)

  RENDER_ADD_SPRITE_BY_TILE_INDEX(160.0f, 24.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                  32.0f, 8x8, 25)

  RENDER_ADD_SPRITE_BY_TILE_INDEX(448.0f, 24.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                  32.0f, 8x8, 25)

  RENDER_ADD_SPRITE_BY_TILE_INDEX(504.0f, 24.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                  32.0f, 8x8, 15)

  RENDER_ADD_SPRITE_BY_TILE_INDEX(560.0f, 24.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                  32.0f, 8x8, 3)

  RENDER_FLUSH_SPRITES()

  /* end textured rendering */
  RENDER_END_SPRITE_RENDERING()

  return 0;
}

/*******************************************************************************
** render_story_screen()
*******************************************************************************/
short int render_story_screen()
{
  /* initialize variables */
  S_num_sprites = 0;

  /* start rendering */
  RENDER_SETUP_VGA_OUTPUT()

  /* begin textured rendering */
  RENDER_BEGIN_SPRITE_RENDERING()

  /* render window */
  render_full_screen_panel();

  /* render text */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_FONT)

  /* title */
  if (G_story_scene == STORY_SCENE_PRELUDE)
    render_text_string("Prelude", 264, 32, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_story_scene == STORY_SCENE_WORLD_01)
    render_text_string("You Shall Not Pass", 176, 32, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_story_scene == STORY_SCENE_WORLD_02)
    render_text_string("Rise From Your Grave", 160, 32, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_story_scene == STORY_SCENE_WORLD_03)
    render_text_string("Breaking The Law", 192, 32, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_story_scene == STORY_SCENE_WORLD_04)
    render_text_string("Knock Knock", 232, 32, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_story_scene == STORY_SCENE_WORLD_05)
    render_text_string("Too Hot to Handle", 184, 32, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_story_scene == STORY_SCENE_WORLD_06)
    render_text_string("Queen of the Nymphs", 168, 32, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_story_scene == STORY_SCENE_WORLD_07)
    render_text_string("Medusa's Brownies", 184, 32, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_story_scene == STORY_SCENE_WORLD_08)
    render_text_string("\xADSilencio!", 240, 32, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_story_scene == STORY_SCENE_WORLD_09)
    render_text_string("Negative Stereotypes", 160, 32, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_story_scene == STORY_SCENE_WORLD_10)
    render_text_string("Her Soul is Still Dancing", 120, 32, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_story_scene == STORY_SCENE_WORLD_11)
    render_text_string("Mental Gymnastics", 184, 32, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_story_scene == STORY_SCENE_WORLD_12)
    render_text_string("The Armorer's Lament", 160, 32, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_story_scene == STORY_SCENE_WORLD_13)
    render_text_string("End of the Line", 200, 32, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_story_scene == STORY_SCENE_WORLD_14)
    render_text_string("Judgment Day", 224, 32, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_story_scene == STORY_SCENE_WORLD_15)
    render_text_string("I Like Big Bots", 200, 32, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_story_scene == STORY_SCENE_WORLD_16)
    render_text_string("An Eternal Question", 168, 32, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_story_scene == STORY_SCENE_WORLD_17)
    render_text_string("Ode to War", 240, 32, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_story_scene == STORY_SCENE_WORLD_18)
    render_text_string("The World Dies Screaming", 128, 32, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_story_scene == STORY_SCENE_AFTERWORD)
    render_text_string("Afterword", 248, 32, RENDER_LEVEL_HUD_FOREGROUND);

  /* main text */
  if (G_story_scene == STORY_SCENE_PRELUDE)
  {
    if (G_cursor_position == 0)
    {
      render_text_string("Transylvania, 1337 A.D.", 136, 104, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("The human race was dying out...", 32, 152, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Its grand kingdoms in ruins. Its", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("great rulers captured. The vampire", 32, 232, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("alchemists had found that the blood", 32, 264, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("of royalty was the key to creating", 32, 296, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("the Philosopher's Blood. With this,", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("they could create a limitless amount", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("of blood, enough for all to drink.", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 1)
    {
      render_text_string("Their usefulness exhausted, humanity", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("stood on the precipice of oblivion.", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("But one bravely fought for the human", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("race.", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Princess Carmen, last of the human", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("royalty, stole all of the vials of", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Philosopher's Blood from the", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("vampires, hiding them in an ancient", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("tower filled with puzzles and traps.", 32, 376, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 2)
    {
      render_text_string("Now, even though the vampires had", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("more than enough captured humans to", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("live off of forever, they still felt", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("that the Blood needed to be retaken,", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("just on principle.", 32, 232, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Enter Victoria. Born under a blood", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("moon 18 years ago, she is a magical,", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("mystical woman who knows a grand", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("total of three spells.", 32, 376, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 3)
    {
      render_text_string("Armed with nothing but her wits,", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Victoria valiantly enters the tower", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("to recover the lost vials.", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("For any battle of importance is", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("fought not with steel, but with the", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("mind, and Victoria is perhaps the", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("only vampire clever enough to ascend", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("the...", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("VAMPIRIC TOWER!", 200, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
  }
  else if (G_story_scene == STORY_SCENE_WORLD_01)
  {
    if (G_cursor_position == 0)
    {
      render_text_string("As Victoria ventured towards the", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("exit of the foyer, she was accosted", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("by none other than Princess Carmen", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("herself!", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"You shall not pass!\" Carmen stated", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("quite emphatically.", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("In a similar fashion, Victoria", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("replied, \"Bite me!\"", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 1)
    {
      render_text_string("And thus, a spirited conversation", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("ensued about the proper etiquette", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("for vampires entering buildings.", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Because APPARENTLY, vampires need to", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("ask for permission before coming in.", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Who made this rule? When did this", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("start? Did Victoria miss a memo?", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"What is this nonsense?\" asked", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Victoria. She was quite perturbed.", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 2)
    {
      render_text_string("Anyway, as a result of this", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("COMPLETELY UNFAIR POLICY, Carmen", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("was able to roll a 20-sided die and", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("cast a magic spell that sent", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Victoria spiraling down to the", 32, 232, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("lowest level of the tower...", 32, 264, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("The Crypt!", 240, 312, RENDER_LEVEL_HUD_FOREGROUND);
    }
  }
  else if (G_story_scene == STORY_SCENE_WORLD_02)
  {
    if (G_cursor_position == 0)
    {
      render_text_string("In the depths of the Crypt, Anubis", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("looked down at Victoria from his", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("golden throne and commanded:", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"Rise from your grave!\"", 136, 216, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"Way ahead of you, chief!\", replied", 32, 264, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Victoria.", 32, 296, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("The god seemed puzzled. \"If you've", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("already risen, why are you here?\"", 32, 376, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 1)
    {
      render_text_string("\"I'm lost, and trying to find my way", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("out. Care to help?\"", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"Sure, but...\" Anubis's curiosity", 32, 184, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("got the best of him. \"How was it", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("that you rose from your grave?\"", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"I was dead, and then a cat jumped", 32, 296, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("over me!\"", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"Ah. The old cat trick. A classic.\"", 32, 376, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 2)
    {
      render_text_string("Through the course of a riveting", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("conversation, with Anubis's speech", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("sounding garbled (as it was being", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("played through an old sound card),", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Victoria learned the way out.", 32, 232, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"I can't believe all that speech", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("fit on a single floppy disk!\" she", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("exclaimed, as she ventured into...", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Charon's Waters!", 192, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
  }
  else if (G_story_scene == STORY_SCENE_WORLD_03)
  {
    if (G_cursor_position == 0)
    {
      render_text_string("Victoria encountered the ferryman", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Charon on the banks of the river", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Styx. He appeared frustrated.", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"I am LATE for my daughter's soccer", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("game. I do not have TIME for this.", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("I do not want to go to Hades. May I", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("speak with your manager?\"", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Charon sighed. It was going to be", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("one of those days.", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 1)
    {
      render_text_string("\"You...\", he rasped. \"You...", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("died... your SUV... exploded...\"", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"My SUV? Oh God! Do you think my", 32, 184, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("insurance covers that? Where's my", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("phone?\"", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("The people waiting in line behind", 32, 296, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("her grumbled. A gentleman in a", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("tracksuit offered some sage advice.", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 2)
    {
      render_text_string("\"Hey lady! Get on the boat! I'm", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("dying here!\"", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Just then, Charon noticed Victoria.", 32, 184, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("It had been a long time since he had", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("seen an entity coming BACK from the", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("underworld. In fact, it was against", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("the law.", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"Breaking... the law...\", he said,", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("a lone finger pointing at Victoria.", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 3)
    {
      render_text_string("\"Breaking the law! Breaking the", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("law!\" Victoria sang, as she started", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("headbanging.", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("The people in line groaned all over", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("again as Victoria strolled past them", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("back into the land of the living,", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("emerging In The Peristyle near the", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Tower on a quiet, moonlit night...", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);
    }
  }
  else if (G_story_scene == STORY_SCENE_WORLD_04)
  {
    if (G_cursor_position == 0)
    {
      render_text_string("At the entrance to the Tower,", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Victoria knocked twice and waited", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("patiently for an answer.", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"Hey, man!\" said the hippie at the", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("door. \"We're going to listen to Dark", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Star. Wanna check it out?\"", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"Is that an invitation?\" Victoria", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("asked. The policy stated she had to", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("be invited in by the owner to enter.", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 1)
    {
      render_text_string("\"You can't OWN things, man. That's", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("just what the Establishment says.", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Divide and conquer, you know?\"", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Why was he responding to lines that", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("weren't placed between quotation", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("marks as dialogue? What was in that", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("strangely shaped pipe he held in", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("his hand?", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"Fresh from NorCal, man. Want some?\"", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 2)
    {
      render_text_string("Victoria was beyond confused, but", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("the invitation seemed real enough", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("to her. She entered as a 23 minute", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("version of the song commenced. The", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("smoke-filled air began to swirl", 32, 232, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("about her in psychedelic colors.", 32, 264, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Three days later, she finally", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("remembered to enter...", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("The Duchess's Archives!", 136, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
  }
  else if (G_story_scene == STORY_SCENE_WORLD_05)
  {
    if (G_cursor_position == 0)
    {
      render_text_string("Victoria happened upon the Duchess", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("relaxing in a comfy chair. She was", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("reading \"The Magus of Venice Beach\".", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"He placed his hands on her bosom", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("and began reciting the spell, as if", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("he was playing the bongo drums...\"", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"Whoa!\" exclaimed Victoria. \"What", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("are you reading over here? It's not", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("inappropriate or anything, is it?\"", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 1)
    {
      render_text_string("Startled by Victoria's outburst, the", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Duchess quickly placed the book", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("face-down on a nearby endtable.", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("\"What book? I've no idea what you're", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("referring to!\", she claimed.", 32, 232, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Unconvinced, Victoria asked a more", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("interesting question. \"I thought", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Princess Carmen was the last of the", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("royalty. Are you really a Duchess?\"", 32, 376, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 2)
    {
      render_text_string("\"Well, I think the designer of this", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("game just wanted to name this world", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("after a level from one of his", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("favorite games.\"", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"Are you saying the integrity of the", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("story was sacrificed for the sake of", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("a lame joke? Shocking!\" Unsurprised,", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Victoria moseyed on over to the...", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Gardens of Venus!", 184, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
  }
  else if (G_story_scene == STORY_SCENE_WORLD_06)
  {
    if (G_cursor_position == 0)
    {
      render_text_string("In the heart of the gardens, the", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Queen of the Nymphs reclined in her", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("flowery bed. She motioned towards", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Victoria seductively.", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"Do you know what a woman feels", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("like?\" she asked. \"I can show you", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("what a woman feels like...\"", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("The Queen made a sound reminiscent", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("of a cat purring. Oh dear.", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 1)
    {
      render_text_string("Victoria fell under a spell cast by", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("the Queen. Yes, that's what it was!", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("She found herself in the Queen's", 32, 184, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("embraces as an electric bass started", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("playing. The Queen was fixing the", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("cable. Their hearts were beating in", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("unison. Their mutual desire was on", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("the verge of passionate release...", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 2)
    {
      render_text_string("Just then, a loud warp magic sound", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("effect played! Princess Carmen stood", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("before them, disapproving.", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"Undead abomination! You do not have", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("a heart that can beat! Who is", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("writing this trash?\"", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Why does she always have to ruin", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("everything? Exasperated, Victoria", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("told Carmen to get lost.", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 3)
    {
      render_text_string("\"I was lost, but I am found.\"", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("With that, Carmen rolled an even", 32, 152, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("bigger 20-sided die. A magical", 32, 184, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("gravity well appeared overhead,", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("capturing Victoria in its pull!", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("She found herself tumbling through", 32, 296, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("a void, beyond time and space.", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("When Victoria came to, she was", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("locked in the Dimensional Prison!", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
  }
  else if (G_story_scene == STORY_SCENE_WORLD_07)
  {
    if (G_cursor_position == 0)
    {
      render_text_string("Deep within the Dimensional Prison,", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Victoria ran into none other than", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Medusa. She was petting her hair,", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("and the snakes were flicking their", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("tongues out inquisitively.", 32, 232, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"Want to try my brownies?\" she", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("asked Victoria. \"They'll get you", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("stoned, LOL!\"", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("She really said \"LOL\". No joke.", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 1)
    {
      render_text_string("Victoria was about to reply, but", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("her eye was drawn to the curiously", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("life-like statues that stood in", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Medusa's lair. They appeared to be", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("hippies! One had been frozen in the", 32, 232, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("middle of kicking a hacky sack.", 32, 264, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Victoria politely declined the", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("offer. She was trying to watch her", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("weight!", 32, 376, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 2)
    {
      render_text_string("In the center of Medusa's lair,", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("a fountain filled with pure blue", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("water flowed. The water was quite", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("clearly made out of polygons, as", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("in a 3D video game from the 90s.", 32, 232, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Since it wasn't real water, it", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("couldn't hurt Victoria! She dove", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("into it and was warped to the...", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Sunken Shrine!", 208, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
  }
  else if (G_story_scene == STORY_SCENE_WORLD_08)
  {
    if (G_cursor_position == 0)
    {
      render_text_string("Near the surface, Victoria met a", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("banshee. Have you ever tried talking", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("to a banshee? It's an experience,", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("let me tell you!", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"AIEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE!\"", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"\xADSilencio! \xADSilencio!\" Victoria", 32, 296, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("cried, to no avail. She just wanted", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("to ask for directions, and now she", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("had to deal with this nonsense!", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 1)
    {
      render_text_string("Suddenly, the banshee calmed down", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("and asked Victoria a question:", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("\"\xA8Hablas espa\xA4ol?\"", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"Un poquito\", replied Victoria.", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("A mischievious grin flashed across", 32, 264, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("the banshee's face. Then, without", 32, 296, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("warning, she began screeching at", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("the top of her lungs in Spanish!", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("I don't even know what that means!", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 2)
    {
      render_text_string("Victoria was tired of listening to", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("that racket, so she wandered off", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("and sat down to watch a movie.", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("But her viewing of Lifeforce, one of", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("the greatest films ever made, was", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("interrupted as the floor opened up", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("beneath her and she fell into...", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("The Labyrinth!", 208, 360, RENDER_LEVEL_HUD_FOREGROUND);
    }
  }
  else if (G_story_scene == STORY_SCENE_WORLD_09)
  {
    if (G_cursor_position == 0)
    {
      render_text_string("In the heart of the Labyrinth,", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Victoria encountered the fearsome", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Minotaur sipping tea from a teacup", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("and saucer made of finest china.", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"Aren't you worried you're going", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("to break that?\" asked Victoria.", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("The Minotaur seemed offended. \"It's", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("because I'm part bull, right? Bulls", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("always break china, is that it?\"", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 1)
    {
      render_text_string("Victoria was nonplussed. The", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Minotaur chuckled darkly and said,", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("\"You know what that is?\" After a", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("dramatic pause, he solemnly intoned:", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"That's a negative stereotype.\"", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"So are you only going to half-", 32, 296, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("break it, then?\" Clearly, Victoria", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("did not understand the Minotaur's", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("plight.", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 2)
    {
      render_text_string("\"How would you feel if everyone", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("assumed that you sparkled in the", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("sunlight?\"", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"Vampires don't sparkle in the", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("sunlight. Only an idiot would think", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("that. Are you ok?\"", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("The Minotaur sighed. A profound", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("disappointment swept over him. Was", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Victoria beyond all hope?", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 3)
    {
      render_text_string("While the Minotaur contemplated the", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("history of societal development and", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("its relation to this state of", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("affairs, Victoria solved a magical", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("cube puzzle that opened up a portal.", 32, 232, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Beyond the portal, Victoria found", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("herself back in the Tower. In the", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Silver Ballroom, they celebrated", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("her banishment! But not for long...", 32, 376, RENDER_LEVEL_HUD_FOREGROUND);
    }
  }
  else if (G_story_scene == STORY_SCENE_WORLD_10)
  {
    if (G_cursor_position == 0)
    {
      render_text_string("It occurred to Victoria that she had", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("gone halfway through this game", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("without biting anyone. No wonder she", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("was thirsty!", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("She walked up to a nearby human and", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("bit into their neck. After drinking", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("deeply, the woman fell limp to the", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("floor. Dead already! They just don't", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("make people like they used to!", 32, 376, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 1)
    {
      render_text_string("Satiated, Victoria looked around and", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("noticed a god from a future age", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("standing by the window. He told her:", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"Bite her again. Her soul is still", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("dancing.\"", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Sure enough, a ghostly apparition of", 32, 296, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("the woman stood above her corpse,", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("grasping an invisible pole whilst", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("gyrating vigorously.", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 2)
    {
      render_text_string("\"My word!\" Victoria gasped. She", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("quickly bit into the woman to remove", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("the last of her life force.", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("The ghostly dancer fell to the", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("floor, and a silence swept through", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("the dance hall. The god, a veteran", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("of vampire stories himself, bid", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Victoria adieu as she entered...", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Pentomino's Quarters!", 152, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
  }
  else if (G_story_scene == STORY_SCENE_WORLD_11)
  {
    if (G_cursor_position == 0)
    {
      render_text_string("Victoria walked in on the mad wizard", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Pentomino staring intently at a", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("nearby wall.", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"I'm not mad. I'm calmer than you", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("are!\" he giggled.", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Pentomino's eyes looked everywhere", 32, 296, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("and nowhere, at Victoria and past", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Victoria, at this world and at the", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("next. The wizard fidgeted softly.", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 1)
    {
      render_text_string("Victoria blurted out, \"I think this", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("guy's a few cans short of a six", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("pack!\"", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"So have you come back from the Far", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Future?\" asked the wizard.", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Victoria was very confused. The", 32, 296, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("wizard sensed her confusion and", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("laughed. \"No, of course, that's in", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("the future!\"", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 2)
    {
      render_text_string("Victoria backed away slowly. \"Time", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("is an illusion, my dear. The faster", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("we move, the slower it does!\"", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Victoria nodded politely and opened", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("a nearby door. It didn't really", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("matter where it led, as long as it", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("was somewhere else! On the other", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("side, she found herself in the...", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Armory d'Amour!", 200, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
  }
  else if (G_story_scene == STORY_SCENE_WORLD_12)
  {
    if (G_cursor_position == 0)
    {
      render_text_string("The Armorer sat forlorn in the", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("corner, the weight of the world upon", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("his pauldrons.", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"Oh, my princess. I have failed", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("you.\" A single tear escaped from", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("behind his visor and ran softly", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("along the cold metal.", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"An emotional scene? Uh oh. Where's", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("the fast forward button?\"", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 1)
    {
      render_text_string("\"You!\" snapped the Armorer. \"How", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("can you show your face after what", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("you've done? Have you no shame?\"", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Victoria had no idea what he was", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("talking about. Maybe she should", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("have been paying attention?", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"Aren't you a magically animated", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("suit of armor? How can you cry", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("tears? I don't get it...\"", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 2)
    {
      render_text_string("Just then, Princess Carmen appeared!", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("She looked different this time,", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("though. More... transparent. Maybe", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("she did something with her hair?", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"My princess! You are risen!\"", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Carmen pointed at Victoria angrily", 32, 296, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("and yelled in an otherworldly voice,", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("\"I shall banish you to the very ends", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("of the Earth!\"", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 3)
    {
      render_text_string("Princess Carmen took out an", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("absolutely massive 20-sided die and", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("rolled it.", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"Look at the size of that", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("icosahedron!\" exclaimed Victoria.", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("The spell cast, Victoria was yanked", 32, 296, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("to a part of the World Tree that", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("had been forgotten long ago known", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("only as Yggdrasil's Appendix!", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
  }
  else if (G_story_scene == STORY_SCENE_WORLD_13)
  {
    if (G_cursor_position == 0)
    {
      render_text_string("There are times in one's life when", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("they come to a crossroads. Here at", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("the end of the world, Victoria stood", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("on the edge of destiny.", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("From the foreboding void below, the", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("primordial goddess Tiamat appeared.", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Her body swayed with the rhythm of", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("the Sea of Chaos.", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 1)
    {
      render_text_string("Suddenly, Tiamat produced a pair of", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("handcuffs, locking one cuff on", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Victoria's wrist and the other cuff", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("on hers.", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"Do you want to jump? Let's do it!\"", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Before Victoria could respond,", 32, 296, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Tiamat lept into the void, taking", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Victoria along with her into the", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("maw of oblivion.", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 2)
    {
      render_text_string("\"I'm getting too old for this", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("nonsense!\" yelled Victoria.", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("She fell into the Sea of Chaos, the", 32, 184, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("indigo waves reclaiming the matter", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("of her body, as they shall with all", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("things in time. Without a physical", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("form to bind it, her spirit drifted", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("upwards to...", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Heaven!", 264, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
  }
  else if (G_story_scene == STORY_SCENE_WORLD_14)
  {
    if (G_cursor_position == 0)
    {
      render_text_string("At Heaven's pearly gates, St. Peter", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("stood holding a roll of parchment,", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("waiting patiently for Victoria's", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("approach.", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"You stand accused of innumerable", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("counts of biting humans, willful", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("usage of psychotropic plant life,", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("and two unpaid parking tickets", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("issued by the city of West Covina.\"", 32, 376, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 1)
    {
      render_text_string("What was Victoria supposed to do?", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Was she supposed to apologize for", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("biting people? Was she supposed to", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("apologize for existing?", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Suddenly, the sound of trumpets", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("blared overhead, and the big man", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Himself looked down from the sky", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("above and proclaimed:", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"We cannot judge.\"", 176, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 2)
    {
      render_text_string("Redeemed, Victoria walked towards", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("the edge of Heaven, crossing the", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("boundary between Heaven & Earth.", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("But time passes differently in the", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("immaterial world, and Victoria did", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("not return to where she came from,", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("instead finding herself in...", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("The Far Future!", 200, 360, RENDER_LEVEL_HUD_FOREGROUND);
    }
  }
  else if (G_story_scene == STORY_SCENE_WORLD_15)
  {
    if (G_cursor_position == 0)
    {
      render_text_string("In the year 2600, robots reign", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("supreme. But one robot stands above", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("the rest, controlling all of the", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("lil' bots. Its name?", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Big Bot.", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Fluent in 8,675,309 programming", 32, 296, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("languages, Big Bot also controls the", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Existential Folding Machine, capable", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("of warping time and space.", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 1)
    {
      render_text_string("Those who wish to use the machine", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("must sing Big Bot's favorite song.", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Unfortunately, no one can remember", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("what this mysterious song is.", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("As Victoria tried to figure it out,", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("she noticed two girl bots having a", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("conversation. How do you tell the", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("difference between a girl bot and a", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("lil' bot? Very carefully.", 32, 376, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 2)
    {
      render_text_string("\"Oh. My. God. B3CK-E. Look at that", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("bot. It is so... big!\"", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Something awakened deep within the", 32, 184, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("recesses of Victoria's mind. It had", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("been forgotten long ago, but never", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("truly lost, for how could something", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("so beautiful and pure ever leave", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("one's heart?", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 3)
    {
      render_text_string("Victoria stood before Big Bot", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("proudly and sang:", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"I LIKE BIG BOTS AND I CANNOT LIE!\"", 32, 184, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Big Bot's light bulb lit up in joy.", 32, 232, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("The dial on the Existential Folding", 32, 264, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Machine was turned to Channel 13.", 32, 296, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("When the computerized voice called", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("out the number 37, Victoria felt", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("herself folded into the Alchemy Lab!", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
  }
  else if (G_story_scene == STORY_SCENE_WORLD_16)
  {
    if (G_cursor_position == 0)
    {
      render_text_string("Amongst the many strange wonders of", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("the Alchemy Lab, Victoria found a", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("little man made out of clay.", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"Look what I can do!\" he said", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("excitedly.", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("The clay man took pieces of himself", 32, 296, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("and formed them into a second clay", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("man. Each of them was half the size", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("of the original.", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 1)
    {
      render_text_string("The second clay man then exclaimed,", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("\"Let's see that again!\"", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("He proceeded to form a third clay", 32, 184, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("man, losing half of his clay to make", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("a new man of half his original size.", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("How long could this continue? Due to", 32, 296, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("the alchemists' experiments with", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("time, it could apparently continue", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("until after forever.", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 2)
    {
      render_text_string("Suddenly, a wild Zeno appeared!", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"Impossible! If there are infinitely", 32, 152, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("many clay men, they must have been", 32, 184, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("made from an infinite amount of", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("clay, but the first man was finite!\"", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Victoria said, \"You need to get out", 32, 296, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("more!\" and sauntered off to the...", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Temple of Mars!", 200, 376, RENDER_LEVEL_HUD_FOREGROUND);
    }
  }
  else if (G_story_scene == STORY_SCENE_WORLD_17)
  {
    if (G_cursor_position == 0)
    {
      render_text_string("In the heart of the Temple, Victoria", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("saw Mars surrounded by hippies! They", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("were airing their grievances to him", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("quite fearsomely.", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"War is like, bad, man.\"", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"The poor die just to make the rich", 32, 296, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("more money. It's not cool, bro.\"", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"Make love, dude, not... whatever.\"", 32, 376, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 1)
    {
      render_text_string("Mars closed his eyes and took a deep", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("breath. In his mind, he heard a soft", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("voice echoing from long ago and far", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("away:", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"And Alexander wept, for there were", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("no more worlds to conquer...\"", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Was this the pot of gold at the end", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("of the rainbow, then? Was there", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("nothing more than this, after all?", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 2)
    {
      render_text_string("Nearby, a hippie girl bounded up to", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("him, her movements free from any", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("kind of self-doubt. She made a peace", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("sign with one hand and placed a", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("flower in his hair with the other.", 32, 232, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Mars could not even find the energy", 32, 264, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("to sigh. It was all just too much.", 32, 296, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Amused, Victoria ascended to...", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("The Apogee!", 232, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
  }
  else if (G_story_scene == STORY_SCENE_WORLD_18)
  {
    if (G_cursor_position == 0)
    {
      render_text_string("Victoria confronted Princess Carmen", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("on the top of the Vampiric Tower!", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"How did you get here?\" asked the", 32, 184, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("princess. \"After banishing you to", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("to the Dimensional Prison, I folded", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("some of the floors of the tower into", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("a pocket dimension. The only way up", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("here is to have the alchemists fold", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("you into their lab...\"", 32, 376, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 1)
    {
      render_text_string("As Carmen monologued, Victoria", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("noticed the princess slowly moving", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("towards a nearby bag of dice.", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("But Victoria came prepared! She took", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("out a blue mana potion, drank it,", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("and cast an ice spell at Carmen,", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("freezing the princess before she", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("could wield her precious Platonic", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("solids!", 32, 376, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 2)
    {
      render_text_string("Victoria had only 6 seconds before", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("the ice cube thawed, but that was", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("more than enough time to push it...", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("off the top of the Vampiric Tower!", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Princess Carmen's memories flashed", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("before her eyes as she fell. Her", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("most cherished one was of her mom", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("saying:", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"I love you.\"", 216, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 3)
    {
      render_text_string("Princess Carmen shattered into a", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("thousand pieces upon the ground,", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("along with humanity's hopes and", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("dreams.", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("And as the world died screaming, one", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("vampire was heralded as a true hero,", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("for the world was finally rid of the", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("human race. History knew her as...", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Victoria!", 248, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
  }
  else if (G_story_scene == STORY_SCENE_AFTERWORD)
  {
    if (G_cursor_position == 0)
    {
      render_text_string("\"Congratulations!\"", 176, 104, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("\"You are now the master", 136, 152, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("of the Vampiric Tower.\"", 136, 184, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Such was the ending of the original", 32, 232, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Vampiric Tower 18 years ago. Perhaps", 32, 264, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("now, that message is truly accurate.", 32, 296, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Of course, you DID complete all 330", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("rooms before getting here, RIGHT?", 32, 376, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 1)
    {
      render_text_string("It's been a journey to get here.", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Let's hope it doesn't take another", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("18 years to finish another game!", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Of course, the game before you did", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("not take 18 years to finish. It was", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("around a year and a half ago that I", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("threw out the forever-unfinished", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("Vampiric Tower 3D and started over", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("from scratch.", 32, 376, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 2)
    {
      render_text_string("From drawing the sprites, to coding", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("my own custom emulation of old FM", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("sound chips to allow for musical", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("tunings beyond equal temperament, to", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("coding the game and spending Lord", 32, 232, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("knows how long getting all the warp", 32, 264, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("spell edge cases figured out, to", 32, 296, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("designing all 330 rooms, it's been a", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("blast! You know, it was going to be", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("666 rooms, but I'd had enough!", 32, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
    else if (G_cursor_position == 3)
    {
      render_text_string("Anyway, I hope you enjoyed my game!", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("By the way, if you thought the", 32, 152, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("ending was a tad depressing (what", 32, 184, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("with the death of the entire human", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("race and all), I may be making", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("another game in the future where you", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("can change that...", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);

      render_text_string("Michael Behrens", 200, 360, RENDER_LEVEL_HUD_FOREGROUND);
      render_text_string("October 2018", 224, 392, RENDER_LEVEL_HUD_FOREGROUND);
    }
  }

  /* page number */
  if (G_cursor_position == 0)
    render_text_string("Page 1", 272, 440, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_cursor_position == 1)
    render_text_string("Page 2", 272, 440, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_cursor_position == 2)
    render_text_string("Page 3", 272, 440, RENDER_LEVEL_HUD_FOREGROUND);
  else if (G_cursor_position == 3)
    render_text_string("Page 4", 272, 440, RENDER_LEVEL_HUD_FOREGROUND);

  RENDER_FLUSH_SPRITES()

  /* left / right arrows by page number */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_TRAPS)

  if (STORY_SCENE_HAS_3_PAGES())
  {
    if ((G_cursor_position >= 0) && (G_cursor_position < 2))
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(384.0f, 432.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 5)
    }

    if ((G_cursor_position > 0) && (G_cursor_position <= 2))
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX_180(224.0f, 432.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                          32.0f, 8x8, 5)
    }
  }
  else if (STORY_SCENE_HAS_4_PAGES())
  {
    if ((G_cursor_position >= 0) && (G_cursor_position < 3))
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX(384.0f, 432.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                      32.0f, 8x8, 5)
    }

    if ((G_cursor_position > 0) && (G_cursor_position <= 3))
    {
      RENDER_ADD_SPRITE_BY_TILE_INDEX_180(224.0f, 432.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                          32.0f, 8x8, 5)
    }
  }

  RENDER_FLUSH_SPRITES()

  /* end textured rendering */
  RENDER_END_SPRITE_RENDERING()

  return 0;
}

/*******************************************************************************
** render_help_screen()
*******************************************************************************/
short int render_help_screen()
{
  /* initialize variables */
  S_num_sprites = 0;

  /* start rendering */
  RENDER_SETUP_VGA_OUTPUT()

  /* begin textured rendering */
  RENDER_BEGIN_SPRITE_RENDERING()

  /* render window */
  render_full_screen_panel();

  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_HUD_PICKUPS)

  /* dividers */
  if (G_cursor_position == 0)
  {
    RENDER_ADD_SPRITE_TO_BUFFER(128.0f, 272.0f, 320.0f, 280.0f, 
                                RENDER_LEVEL_HUD_FOREGROUND,
                                0.125f, 0.875f, 0.875f, 0.84375f)

    RENDER_ADD_SPRITE_TO_BUFFER(320.0f, 272.0f, 512.0f, 280.0f, 
                                RENDER_LEVEL_HUD_FOREGROUND,
                                0.125f, 0.875f, 0.875f, 0.84375f)
  }

  RENDER_FLUSH_SPRITES()

  /* render text */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_FONT)

  if (G_cursor_position == 0)
  {
    render_text_string("Controls", 256, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Arrow Keys: Move", 128, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Z: Bat Transform", 272, 136, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("X: Cast Ice Spell", 272, 168, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("C: Cast Warp Spell", 272, 200, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Shift + Arrow: Turn w/o Moving", 80, 232, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Enter: Menu Confirm", 32, 304, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Esc: Menu Cancel", 64, 336, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("F1, H: Help", 32, 368, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Tab: Room Select", 64, 400, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("R: Restart Level", 352, 304, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("P: Pause", 352, 336, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("O: Options", 352, 368, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("\\: Fullscreen", 352, 400, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 1", 272, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 1)
  {
    render_text_string("The Game", 256, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Victoria the Vampire needs to", 80, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("collect all of the blood vials", 80, 136, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("in each room.", 80, 168, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("When they are all collected,", 80, 252, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("the portcullis will open!", 80, 284, RENDER_LEVEL_HUD_FOREGROUND);

    RENDER_ADD_SPRITE_BY_TILE_INDEX(312.0f, 326.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    16.0f, 16x16, 26)

    render_text_string("Walk into the portcullis to", 80, 368, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("complete the room.", 80, 400, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 2", 272, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 2)
  {
    render_text_string("Powerups", 256, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Bat Vial:  Lets Victoria turn into", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("a bat. As a bat, she can", 208, 136, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("fly over obstacles, but", 208, 168, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("she can't collect items.", 208, 200, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Blue Mana: Lets Victoria cast an", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("ice spell, which can", 208, 280, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("freeze other characters", 208, 312, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("and turn them into ice", 208, 344, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("cubes.", 208, 376, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 3", 272, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 3)
  {
    render_text_string("Powerups", 256, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Green Mana:  Lets Victoria cast a", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("warp spell, which", 240, 136, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("allows her to trade", 240, 168, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("places with whatever", 240, 200, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("it hits.", 240, 232, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Floppy Disk: Mysterious relic from", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("a bygone age.", 240, 312, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Collect to unlock", 240, 344, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("secret worlds!", 240, 376, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 4", 272, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 4)
  {
    render_text_string("Environment", 232, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Block:  Nothing can pass through", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("it.", 160, 136, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Pillar: Like the block, but it does", 32, 184, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("not stop evil eye spells.", 160, 216, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Tree:   Like the pillar, but it can", 32, 264, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("be burned down by fireballs.", 160, 296, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Cobweb: Disappears after Victoria", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("walks through it.", 160, 376, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 5", 272, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 5)
  {
    render_text_string("Environment", 232, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Water:  Victoria can fly over it", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("as a bat.", 160, 136, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Grass:  Victoria can move across it,", 32, 184, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("but other characters cannot.", 160, 216, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Sand, dirt, and snow act", 160, 248, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("the same way.", 160, 280, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Ice:    A moving character or object", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("will slip and keep moving", 160, 360, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("in the same direction.", 160, 392, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 6", 272, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 6)
  {
    render_text_string("Bridges", 264, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Stone Bridge:   Can be walked", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("across many times.", 288, 136, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Wooden Bridge:  Will crack after", 32, 184, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("being walked on.", 288, 216, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Cracked Bridge: Will crumble after", 32, 264, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("being walked on.", 288, 296, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 7", 272, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 7)
  {
    render_text_string("Symbols", 264, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Joker Card:     Turns a bat back", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("into a vampire.", 288, 136, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Solomon's Seal: Provides protection", 32, 184, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("from all damage.", 288, 216, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Yin Yang:       Will change an", 32, 264, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("ice spell into a", 288, 296, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("fireball, and vice", 288, 328, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("versa.", 288, 360, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 8", 272, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 8)
  {
    render_text_string("Traps", 280, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Floor Spikes: They pop up after", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("being stepped on (once", 256, 136, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("the coast is clear).", 256, 168, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Conveyer:     Forces an object to", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("to move in that", 256, 248, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("direction.", 256, 280, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Arrows:       Victoria and other", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("characters can't move", 256, 360, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("against its direction.", 256, 392, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 9", 272, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 9)
  {
    render_text_string("Traps", 280, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Ballista:       Victoria can fire", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("it by trying to walk", 288, 136, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("into it.", 288, 168, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Pinball Kicker: Bounces a spell", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("in a new direction!", 288, 248, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Laser Gun:      Tracks Victoria's", 32, 296, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("location. Fires high", 288, 328, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("explosive rounds.", 288, 360, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 10", 264, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 10)
  {
    render_text_string("Levers & Switches", 184, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Lever:       Victoria can toggle it", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("by trying to walk into", 240, 136, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("it. Affects floor", 240, 168, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("spikes and conveyers", 240, 200, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("with the same color.", 240, 232, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Spin Switch: Rotates arrows,", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("ballistas, and pinball", 240, 312, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("kickers with the same", 240, 344, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("color when stepped on.", 240, 376, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 11", 264, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 11)
  {
    render_text_string("Levers & Switches", 184, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Number Switch: A die with the same", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("number on it will", 272, 136, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("become solid as long", 272, 168, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("as the switch is", 272, 200, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("held down.", 272, 232, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 12", 264, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 12)
  {
    render_text_string("Pushable Objects", 192, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Box:    Blocks all spells and", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("characters.", 160, 136, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Pot:    Like the box, but it does", 32, 184, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("not stop evil eye spells.", 160, 216, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Victoria can fly over it", 160, 248, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("as a bat.", 160, 280, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("There are 4 types of boxes and pots:", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Wood, Metal, TNT, and Stone.", 32, 360, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 13", 264, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 13)
  {
    render_text_string("Pushable Objects", 192, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Wood:     Can be destroyed by", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("fireballs.", 192, 136, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Metal:    Breaks floor spikes when", 32, 184, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("pushed over them.", 192, 216, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("TNT:      Explodes when hit with a", 32, 264, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("fireball.", 192, 296, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Stone:    Does not slip on ice.", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 14", 264, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 14)
  {
    render_text_string("Pushable Objects", 192, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Eight Ball: Keeps rolling once", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("pushed. If one eight", 224, 136, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("ball hits another, the", 224, 168, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("second one will start", 224, 200, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("rolling.", 224, 232, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Candle:     Victoria can fly over", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("an unlit candle.", 224, 312, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Fireballs light them up.", 224, 344, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Ice spells put them out.", 224, 376, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 15", 264, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 15)
  {
    render_text_string("Pushable Objects", 192, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Aqua Fortis:   Dissolves spikes when", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("broken over them.", 272, 136, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Victoria can fly over", 272, 168, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("it as a bat.", 272, 200, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Aqua Explodis: Like aqua fortis, but", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("explodes when broken.", 272, 280, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Ice Cube:      Thaws in 6 seconds.", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("A fireball will thaw", 272, 360, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("it instantly.", 272, 392, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 16", 264, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 16)
  {
    render_text_string("Pushable Objects", 192, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Mahjong Tile:  If it touches a", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("matching tile, both", 272, 136, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("tiles will flash", 272, 168, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("and disappear.", 272, 200, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Vanishing Die: Becomes solid as long", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("as a number switch", 272, 280, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("with the same number", 272, 312, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("on it is held down.", 272, 344, RENDER_LEVEL_HUD_FOREGROUND);

    RENDER_ADD_SPRITE_BY_TILE_INDEX(136.0f, 280.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    16.0f, 16x16, 29)

    render_text_string("Page 17", 264, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 17)
  {
    render_text_string("Pushable Objects", 192, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Prism Block: Reflects a spell", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("in a new direction!", 240, 136, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Spellbinder: Captures a spell that", 32, 184, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("hits it. If the", 240, 216, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("spellbinder already", 240, 248, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("contains a spell,", 240, 280, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("that spell is released", 240, 312, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("to make space for the", 240, 344, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("new one.", 240, 376, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 18", 264, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 18)
  {
    render_text_string("Denizens of the Tower", 152, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Pumpkin: Casts an evil eye spell", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("at Victoria if there is a", 176, 136, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("clear shot. He can cast", 176, 168, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("the spell up, down, left,", 176, 200, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("or right.", 176, 232, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Ghost:   Awakes when all vials", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("are collected.", 176, 312, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Casts an evil eye spell", 176, 344, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("in the direction he faces.", 176, 376, RENDER_LEVEL_HUD_FOREGROUND);

    RENDER_ADD_SPRITE_BY_TILE_INDEX(88.0f, 312.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    16.0f, 16x16, 26)

    render_text_string("Page 19", 264, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 19)
  {
    render_text_string("Denizens of the Tower", 152, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Mask:           Like the pumpkin,", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("but he moves", 288, 136, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("back and forth.", 288, 168, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Double:         Copies Victoria's", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("movements and", 288, 248, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("actions.", 288, 280, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Reverse Double: Like the double, but", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("she moves in the", 288, 360, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("opposite direction.", 288, 392, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 20", 264, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 20)
  {
    render_text_string("Denizens of the Tower", 152, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Snake:    Awakes when all vials", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("are collected. Breathes", 192, 136, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("fireballs at Victoria.", 192, 168, RENDER_LEVEL_HUD_FOREGROUND);

    RENDER_ADD_SPRITE_BY_TILE_INDEX(96.0f, 136.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    16.0f, 16x16, 26)

    render_text_string("Faerie:   Moves up & down or", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("left & right to get in", 192, 248, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Victoria's way.", 192, 280, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Venusian: A weed from the planet", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Venus. Grows back after", 192, 360, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("being moved or destroyed.", 192, 392, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 21", 264, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 21)
  {
    render_text_string("Denizens of the Tower", 152, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Lil' Bot: Bops back and forth. He", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("can push various objects.", 192, 136, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Frog:     Will try to pull Victoria", 32, 184, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("towards him.", 192, 216, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Wisp:     Does not like to be", 32, 264, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("touched. He will start", 192, 296, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("flashing red and explode", 192, 328, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("in protest.", 192, 360, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 22", 264, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 22)
  {
    render_text_string("Denizens of the Tower", 152, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Imp:      Awakes when all vials are", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("collected. Runs around.", 192, 136, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("He is the only character", 192, 168, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("that can hurt Victoria", 192, 200, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("by running into her.", 192, 232, RENDER_LEVEL_HUD_FOREGROUND);

    RENDER_ADD_SPRITE_BY_TILE_INDEX(104.0f, 136.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    16.0f, 16x16, 26)

    render_text_string("Jiangshi: Hops around. If she runs", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("into Victoria, she will", 192, 312, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("stop there and block", 192, 344, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Victoria's path.", 192, 376, RENDER_LEVEL_HUD_FOREGROUND);

    RENDER_ADD_SPRITE_BY_TILE_INDEX(104.0f, 312.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    16.0f, 16x16, 26)

    render_text_string("Page 23", 264, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 23)
  {
    render_text_string("Denizens of the Tower", 152, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Mummy:       Runs around. Falls", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("apart when thawed.", 240, 136, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Poltergeist: Floats back and forth.", 32, 184, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Stops near Victoria", 240, 216, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("and gets in the way.", 240, 248, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Cannot be frozen.", 240, 280, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Undine:      Casts ice spells at", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Victoria. Cannot be", 240, 360, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("frozen.", 240, 392, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 24", 264, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 24)
  {
    render_text_string("Denizens of the Tower", 152, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Witch:     Stops reading when all", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("vials are collected.", 208, 136, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Casts a slow-moving spell", 208, 168, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("at Victoria.", 208, 200, RENDER_LEVEL_HUD_FOREGROUND);

    RENDER_ADD_SPRITE_BY_TILE_INDEX(104.0f, 136.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    16.0f, 16x16, 26)

    render_text_string("Sorceress: Casts warp spells at", 32, 248, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Victoria. Ridiculous!", 208, 280, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Guardian:  Reflects spells back", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("with his mirror shield.", 208, 360, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Impervious to all magic.", 208, 392, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 25", 264, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 25)
  {
    render_text_string("The Secret Worlds", 184, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("There is a 3 1/2\" floppy disk in", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("each world. In order to obtain it,", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("Victoria must collect it, and then", 32, 168, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("exit the room successfully through", 32, 200, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("the portcullis.", 32, 232, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("For every six floppy disks obtained,", 32, 280, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("a new secret world in Episode 7 will", 32, 312, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("be unlocked.", 32, 344, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 26", 264, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 26)
  {
    render_text_string("The Secret Worlds", 184, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("The three secret worlds each have a", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("5 1/4\" floppy disk in them.", 32, 136, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Could there be a super-secret world", 32, 184, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("unlocked by these coveted disks?", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("(I'm going to guess \"maybe\".)", 32, 264, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 27", 264, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 27)
  {
    render_text_string("Vampiric Wisdom", 200, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("*", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("One box can block two pumpkins", 64, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("that are sitting next to each", 64, 136, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("other.", 64, 168, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("*", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("If a blood vial is destroyed, the", 64, 216, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("portcullis cannot be opened, and", 64, 248, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("the room must be restarted.", 64, 280, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("*", 32, 328, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Pushable objects are not affected", 64, 328, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("by arrows.", 64, 360, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 28", 264, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }
  else if (G_cursor_position == 28)
  {
    render_text_string("Vampiric Wisdom", 200, 32, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("*", 32, 104, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("A die cannot appear if something", 64, 104, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("is within it, and cannot disappear", 64, 136, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("if something is on top of it.", 64, 168, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("*", 32, 216, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Pay close attention to the hand", 64, 216, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("in which the imp holds his fork.", 64, 248, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("*", 32, 296, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Have fun! And remember: it's just", 64, 296, RENDER_LEVEL_HUD_FOREGROUND);
    render_text_string("a game!", 64, 328, RENDER_LEVEL_HUD_FOREGROUND);

    render_text_string("Page 29", 264, 440, RENDER_LEVEL_HUD_FOREGROUND);
  }

  RENDER_FLUSH_SPRITES()

  /* render page specific sprites */
  if (G_cursor_position == 1)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_HUD_PICKUPS)

    /* blood and bat vials */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(272.0f, 202.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 25)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(336.0f, 202.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 26)

    RENDER_FLUSH_SPRITES()

    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_THEME_FOYER)

    /* portcullis */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(272.0f, 318.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 4x4, 12)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(336.0f, 318.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 4x4, 15)

    RENDER_FLUSH_SPRITES()
  }
  else if (G_cursor_position == 2)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_HUD_PICKUPS)

    /* bat vial */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(96.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 26)

    /* blue mana */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(96.0f, 272.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 27)

    RENDER_FLUSH_SPRITES()
  }
  else if (G_cursor_position == 3)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_HUD_PICKUPS)

    /* green mana */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(112.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 28)

    /* floppy disks */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(80.0f, 304.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 29)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(144.0f, 304.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 30)

    RENDER_FLUSH_SPRITES()
  }
  else if (G_cursor_position == 4)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_OBSTACLES_SPELLS)

    /* block */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(72.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 4)

    /* pillar */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(72.0f, 208.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 20)

    /* tree */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(72.0f, 288.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 13)

    RENDER_FLUSH_SPRITES()

    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_ENVIRONMENT_SYMBOLS_SUBMERGED)

    /* cobweb */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(72.0f, 368.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 4)

    RENDER_FLUSH_SPRITES()
  }
  else if (G_cursor_position == 5)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_ENVIRONMENT_SYMBOLS_SUBMERGED)

    /* water */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(72.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    16.0f, 16x16, 0)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(88.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    16.0f, 16x16, 0)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(72.0f, 144.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    16.0f, 16x16, 0)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(88.0f, 144.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    16.0f, 16x16, 0)

    /* grass */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(72.0f, 208.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 16)

    /* ice */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(72.0f, 352.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 2)

    RENDER_FLUSH_SPRITES()
  }
  else if (G_cursor_position == 6)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_ENVIRONMENT_SYMBOLS_SUBMERGED)

    /* stone bridges */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(96.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 24)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(176.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 27)

    /* wooden bridges */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(96.0f, 208.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 25)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(176.0f, 208.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 28)

    /* cracked bridges */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(96.0f, 288.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 26)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(176.0f, 288.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 29)

    RENDER_FLUSH_SPRITES()
  }
  else if (G_cursor_position == 7)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_ENVIRONMENT_SYMBOLS_SUBMERGED)

    /* joker card */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(136.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 5)

    /* solomon's seal */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(136.0f, 208.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 6)

    /* yin yang */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(136.0f, 288.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 8)

    RENDER_FLUSH_SPRITES()
  }
  else if (G_cursor_position == 8)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_TRAPS)

    /* floor spikes (depressed) */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(88.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    16.0f, 16x16, 192)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(104.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    16.0f, 16x16, 192)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(88.0f, 144.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    16.0f, 16x16, 192)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(104.0f, 144.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    16.0f, 16x16, 192)

    /* floor spikes (raised) */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(152.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    16.0f, 16x16, 209)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(168.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    16.0f, 16x16, 209)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(152.0f, 144.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    16.0f, 16x16, 209)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(168.0f, 144.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    16.0f, 16x16, 209)

    /* conveyer */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(120.0f, 240.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 57)

    /* arrows */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(120.0f, 352.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 6)

    RENDER_FLUSH_SPRITES()
  }
  else if (G_cursor_position == 9)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_TRAPS)

    /* ballista */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(136.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 0)

    /* pinball kicker */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(104.0f, 240.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 30)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(168.0f, 240.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 46)

    RENDER_FLUSH_SPRITES()

    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_MUMMY_POLTERGEIST_LASER_GUNS)

    /* laser gun */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(136.0f, 320.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 48)

    RENDER_FLUSH_SPRITES()
  }
  else if (G_cursor_position == 10)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_SWITCHES)

    /* levers */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(56.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 0)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(112.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 8)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(168.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 16)

    /* spin switches */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(56.0f, 304.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 24)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(112.0f, 304.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 25)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(168.0f, 304.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 26)

    RENDER_FLUSH_SPRITES()
  }
  else if (G_cursor_position == 11)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_SWITCHES)

    /* number switches */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(64.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 27)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(128.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 35)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(192.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 43)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(64.0f, 176.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 51)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(128.0f, 176.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 59)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(192.0f, 176.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 31)

    RENDER_FLUSH_SPRITES()
  }
  else if (G_cursor_position == 12)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_PUSHABLE_OBJECTS)

    /* box */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(72.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 0)

    /* pot */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(72.0f, 206.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 8)

    RENDER_FLUSH_SPRITES()
  }
  else if (G_cursor_position == 13)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_PUSHABLE_OBJECTS)

    /* wood */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(56.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 0)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(120.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 8)

    /* metal */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(56.0f, 208.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 1)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(120.0f, 208.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 9)

    /* tnt */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(56.0f, 288.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 2)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(120.0f, 288.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 10)

    /* stone */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(56.0f, 368.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 3)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(120.0f, 368.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 11)

    RENDER_FLUSH_SPRITES()
  }
  else if (G_cursor_position == 14)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_PUSHABLE_OBJECTS)

    /* eight ball */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(104.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 40)

    /* candles */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(72.0f, 304.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 16)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(136.0f, 304.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 17)

    RENDER_FLUSH_SPRITES()
  }
  else if (G_cursor_position == 15)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_PUSHABLE_OBJECTS)

    /* aqua fortis */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(128.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 6)

    /* aqua fortis */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(128.0f, 272.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 38)

    /* ice cube */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(128.0f, 352.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 20)

    RENDER_FLUSH_SPRITES()
  }
  else if (G_cursor_position == 16)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_PUSHABLE_OBJECTS)

    /* mahjong tiles */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(96.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 24)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(160.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 26)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(96.0f, 176.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 32)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(160.0f, 176.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 34)

    /* vanishing die */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(96.0f, 272.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 58)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(160.0f, 272.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 50)

    RENDER_FLUSH_SPRITES()
  }
  else if (G_cursor_position == 17)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_PUSHABLE_OBJECTS)

    /* prism block */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(112.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 12)

    /* spellbinder */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(112.0f, 208.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 28)

    RENDER_FLUSH_SPRITES()
  }
  else if (G_cursor_position == 18)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_PLAYER_GHOST_PUMPKIN_MASK)

    /* pumpkin */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(80.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 32)

    /* ghosts */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(48.0f, 304.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 48)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(112.0f, 304.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 49)

    RENDER_FLUSH_SPRITES()
  }
  else if (G_cursor_position == 19)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_PLAYER_GHOST_PUMPKIN_MASK)

    /* masks */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(104.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 34)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(168.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 42)

    RENDER_FLUSH_SPRITES()

    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_DOUBLE_SNAKE_FAERIE_VENUSIAN)

    /* double */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(136.0f, 240.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 0)

    RENDER_FLUSH_SPRITES()

    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_REVERSE_DOUBLE_LIL_BOT_WISP_FROG)

    /* reverse double */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(136.0f, 352.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 0)

    RENDER_FLUSH_SPRITES()
  }
  else if (G_cursor_position == 20)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_DOUBLE_SNAKE_FAERIE_VENUSIAN)

    /* snakes */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(56.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 32)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(120.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 33)

    /* faeries */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(56.0f, 240.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 54)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(120.0f, 240.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 48)

    /* venusian */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(88.0f, 352.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 56)

    RENDER_FLUSH_SPRITES()
  }
  else if (G_cursor_position == 21)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_REVERSE_DOUBLE_LIL_BOT_WISP_FROG)

    /* lil bot */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(88.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 32)

    /* frog */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(88.0f, 208.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 59)

    /* wisp */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(88.0f, 288.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 37)

    RENDER_FLUSH_SPRITES()
  }
  else if (G_cursor_position == 22)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_IMP_JIANGSHI)

    /* imps */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(64.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 27)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(128.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 24)

    /* jiangshis */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(64.0f, 304.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 56)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(128.0f, 304.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 35)

    RENDER_FLUSH_SPRITES()
  }
  else if (G_cursor_position == 23)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_MUMMY_POLTERGEIST_LASER_GUNS)

    /* mummy */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(112.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 24)

    /* poltergeist */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(112.0f, 208.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 32)

    RENDER_FLUSH_SPRITES()

    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_UNDINE_SORCERESS_WITCH_GUARDIAN)

    /* undine */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(112.0f, 352.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 3)

    RENDER_FLUSH_SPRITES()
  }
  else if (G_cursor_position == 24)
  {
    RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_UNDINE_SORCERESS_WITCH_GUARDIAN)

    /* witches */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(64.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 24)

    RENDER_ADD_SPRITE_BY_TILE_INDEX(128.0f, 128.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 25)

    /* sorceress */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(96.0f, 272.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 7)

    /* guardian */
    RENDER_ADD_SPRITE_BY_TILE_INDEX(96.0f, 352.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 43)

    RENDER_FLUSH_SPRITES()
  }

  /* left / right arrows by page number */
  RENDER_CHANGE_TEXTURE(TEXTURE_INDEX_TRAPS)

  if ((G_cursor_position >= 0) && (G_cursor_position < 28))
  {
    RENDER_ADD_SPRITE_BY_TILE_INDEX(384.0f, 432.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                    32.0f, 8x8, 5)
  }

  if ((G_cursor_position > 0) && (G_cursor_position <= 28))
  {
    RENDER_ADD_SPRITE_BY_TILE_INDEX_180(224.0f, 432.0f, RENDER_LEVEL_HUD_FOREGROUND,
                                        32.0f, 8x8, 5)
  }

  RENDER_FLUSH_SPRITES()

  /* end textured rendering */
  RENDER_END_SPRITE_RENDERING()

  return 0;
}

/*******************************************************************************
** render_vga_to_window()
*******************************************************************************/
short int render_vga_to_window()
{
  /* select window framebuffer */
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glViewport(0, 0, (GLsizei) G_viewport_w, (GLsizei) G_viewport_h);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* set shader program */
  glUseProgram(G_program_id_A);

  /* set model view projection matrix */
  glUniformMatrix4fv(G_uniform_A_mvp_matrix_id, 1, GL_FALSE, G_projection_matrix_window);

  /* bind framebuffer texture */
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, G_texture_id_vga);
  glUniform1i(G_uniform_A_texture_sampler_id, 0);

  /* set up vertex buffer */
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, G_vertex_buffer_id_window);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  /* set up texcoord buffer */
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, G_texcoord_buffer_id_window);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

  /* render texture to screen */
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, G_index_buffer_id_window);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);

  /* disable vertex and texture coordinate arrays */
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);

  return 0;
}
