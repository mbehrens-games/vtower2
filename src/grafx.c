/*******************************************************************************
** grafx.c (opengl objects)
*******************************************************************************/

#include <SDL2/SDL.h>
/*#include <SDL2/SDL_opengl.h>*/
#include <glad/glad.h>

#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "grafx.h"

SDL_Window*       G_sdl_window;

unsigned char     G_fullscreen_flag;

int               G_window_w;
int               G_window_h;

int               G_desktop_w;
int               G_desktop_h;

int               G_viewport_w;
int               G_viewport_h;

GLuint            G_texture_id_vga;

GLuint            G_vertex_array_id;

GLuint            G_vertex_buffer_id_sprites;
GLuint            G_texcoord_buffer_id_sprites;
GLuint            G_color_buffer_id_sprites;
GLuint            G_index_buffer_id_sprites;

GLuint            G_vertex_buffer_id_window;
GLuint            G_texcoord_buffer_id_window;
GLuint            G_index_buffer_id_window;

GLuint            G_framebuffer_id_vga;
GLuint            G_renderbuffer_id_vga;

GLuint            G_program_id_A;
GLuint            G_program_id_B;

GLuint            G_uniform_A_mvp_matrix_id;
GLuint            G_uniform_A_texture_sampler_id;

GLuint            G_uniform_B_mvp_matrix_id;

GLfloat*          G_vertex_buffer_sprites;
GLfloat*          G_texcoord_buffer_sprites;
GLfloat*          G_color_buffer_sprites;
unsigned short*   G_index_buffer_sprites;

GLfloat           G_vertex_buffer_window[12];
GLfloat           G_texcoord_buffer_window[8];
unsigned short    G_index_buffer_window[6];

GLfloat           G_projection_matrix_vga[16];
GLfloat           G_projection_matrix_window[16];

/*******************************************************************************
** grafx_compile_program()
*******************************************************************************/
short int grafx_compile_program(GLuint  program_id, 
                                GLchar* vs_source_string, 
                                GLint   vs_source_length, 
                                GLchar* fs_source_string, 
                                GLint   fs_source_length)
{
  GLuint  vertex_shader_id;
  GLuint  fragment_shader_id;

  const GLchar* string_array[1];
  GLint         length_array[1];

  GLint   compile_status;
  GLint   link_status;
  char    info_log[256];

  /* create and compile vertex shader */
  vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);

  string_array[0] = vs_source_string;
  length_array[0] = vs_source_length;

  glShaderSource(vertex_shader_id, 1, string_array, length_array);
  glCompileShader(vertex_shader_id);

  /* make sure the shader compiled correctly */
  glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &compile_status);

  if (compile_status != GL_TRUE)
  {
    printf("Failed to compile vertex shader.\n");

    glGetShaderInfoLog(vertex_shader_id, 256, NULL, info_log);
    printf("Info Log: %s\n", info_log);

    glDeleteShader(vertex_shader_id);

    return 1;
  }

  /* create and compile fragment shader */
  fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

  string_array[0] = fs_source_string;
  length_array[0] = fs_source_length;

  glShaderSource(fragment_shader_id, 1, string_array, length_array);
  glCompileShader(fragment_shader_id);

  /* make sure the shader compiled correctly */
  glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &compile_status);

  if (compile_status != GL_TRUE)
  {
    printf("Failed to compile fragment shader.\n");

    glGetShaderInfoLog(fragment_shader_id, 256, NULL, info_log);
    printf("Info Log: %s\n", info_log);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return 1;
  }

  /* link program */
  glAttachShader(program_id, vertex_shader_id);
  glAttachShader(program_id, fragment_shader_id);
  glLinkProgram(program_id);

  /* make sure the program was linked correctly */
  glGetProgramiv(program_id, GL_LINK_STATUS, &link_status);

  if (link_status != GL_TRUE)
  {
    printf("Failed to link OpenGL program.\n");

    glGetProgramInfoLog(program_id, 256, NULL, info_log);
    printf("Info Log: %s\n", info_log);

    glDetachShader(program_id, vertex_shader_id);
    glDetachShader(program_id, fragment_shader_id);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    glDeleteProgram(program_id);
    return 1;
  }

  /* cleanup */
  glDetachShader(program_id, vertex_shader_id);
  glDetachShader(program_id, fragment_shader_id);

  glDeleteShader(vertex_shader_id);
  glDeleteShader(fragment_shader_id);

  return 0;
}

/*******************************************************************************
** grafx_load_shaders()
*******************************************************************************/
short int grafx_load_shaders(char* filename)
{
  FILE*         fp;
  int           i;
  char          signature[4];
  char          type[6];
  unsigned char num_programs;

  GLchar*       vs_source_string[2];
  GLint         vs_source_length[2];

  GLchar*       fs_source_string[2];
  GLint         fs_source_length[2];

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

  if ((type[0] != 'S') || (type[1] != 'H') || (type[2] != 'A') ||
      (type[3] != 'D') || (type[4] != 'E') || (type[5] != 'R'))
  {
    fclose(fp);
    return 1;
  }

  /* read number of programs */
  if (fread(&num_programs, 1, 1, fp) == 0)
  {
    fclose(fp);
    return 1;
  }

  if (num_programs != 2)
  {
    fclose(fp);
    return 1;
  }

  /* initialize source variables */
  for (i = 0; i < 2; i++)
  {
    vs_source_string[i] = NULL;
    vs_source_length[i] = 0;

    fs_source_string[i] = NULL;
    fs_source_length[i] = 0;
  }

  /* read shader sources */
  for (i = 0; i < 2; i++)
  {
    /* vertex shader */
    if (fread(&vs_source_length[i], 4, 1, fp) == 0)
    {
      fclose(fp);
      return 1;
    }

    vs_source_string[i] = malloc(sizeof(GLchar) * (unsigned int) vs_source_length[i]);

    if (fread(vs_source_string[i], 1, vs_source_length[i], fp) < (unsigned int) vs_source_length[i])
    {
      fclose(fp);
      return 1;
    }

    /* fragment shader */
    if (fread(&fs_source_length[i], 4, 1, fp) == 0)
    {
      fclose(fp);
      return 1;
    }

    fs_source_string[i] = malloc(sizeof(GLchar) * (unsigned int) fs_source_length[i]);

    if (fread(fs_source_string[i], 1, fs_source_length[i], fp) < (unsigned int) fs_source_length[i])
    {
      fclose(fp);
      return 1;
    }
  }

  /* close file */
  fclose(fp);

  /* create and compile sprites program */
  G_program_id_A = glCreateProgram();

  if (grafx_compile_program(G_program_id_A, 
                            vs_source_string[0],
                            vs_source_length[0],
                            fs_source_string[0],
                            fs_source_length[0]))
  {
    printf("Failed to compile OpenGL program (sprites).\n");
    glDeleteProgram(G_program_id_A);
    return 1;
  }

  /* create and compile particles program */
  G_program_id_B = glCreateProgram();

  if (grafx_compile_program(G_program_id_B, 
                            vs_source_string[1],
                            vs_source_length[1],
                            fs_source_string[1],
                            fs_source_length[1]))
  {
    printf("Failed to compile OpenGL program (particles).\n");
    glDeleteProgram(G_program_id_A);
    glDeleteProgram(G_program_id_B);
    return 1;
  }

  /* free shader source strings */
  for (i = 0; i < 2; i++)
  {
    if (vs_source_string[i] != NULL)
    {
      free(vs_source_string[i]);
      vs_source_string[i] = NULL;
    }

    if (fs_source_string[i] != NULL)
    {
      free(fs_source_string[i]);
      fs_source_string[i] = NULL;
    }
  }

  return 0;
}

/*******************************************************************************
** grafx_create_opengl_objects()
*******************************************************************************/
short int grafx_create_opengl_objects()
{
  int i;
  int j;

  /* create vertex array object */
  glGenVertexArrays(1, &G_vertex_array_id);
  glBindVertexArray(G_vertex_array_id);

  /* compile glsl shaders */
  if (grafx_load_shaders(G_path_shader_data))
  {
    printf("Failed to compile GLSL shaders.\n");
    glDeleteVertexArrays(1, &G_vertex_array_id);
    return 1;
  }

  /* obtain ids for uniform variables in the shaders */
  G_uniform_A_mvp_matrix_id = glGetUniformLocation(G_program_id_A, "mvp_matrix");
  G_uniform_A_texture_sampler_id = glGetUniformLocation(G_program_id_A, "texture_sampler");

  G_uniform_B_mvp_matrix_id = glGetUniformLocation(G_program_id_B, "mvp_matrix");

  /* create vga texture */
  glGenTextures(1, &G_texture_id_vga);
  glBindTexture(GL_TEXTURE_2D, G_texture_id_vga);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, GRAFX_VGA_TEXTURE_WIDTH, 
                GRAFX_VGA_TEXTURE_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);

  /* create framebuffer object */
  glGenFramebuffers(1, &G_framebuffer_id_vga);
  glBindFramebuffer(GL_FRAMEBUFFER, G_framebuffer_id_vga);

  glGenRenderbuffers(1, &G_renderbuffer_id_vga);
  glBindRenderbuffer(GL_RENDERBUFFER, G_renderbuffer_id_vga);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 
                        GRAFX_VGA_TEXTURE_WIDTH, GRAFX_VGA_TEXTURE_HEIGHT);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, 
                            GL_RENDERBUFFER, G_renderbuffer_id_vga);
  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, G_texture_id_vga, 0);
  glDrawBuffer(GL_COLOR_ATTACHMENT0);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
  {
    printf("Error: Framebuffer Object is not complete!\n");
    return 1;
  }

  /* orthographic projection matrix (vga) */
  G_projection_matrix_vga[0]  = 2.0f / GRAFX_VGA_TEXTURE_WIDTH;
  G_projection_matrix_vga[1]  = 0.0f;
  G_projection_matrix_vga[2]  = 0.0f;
  G_projection_matrix_vga[3]  = 0.0f;

  G_projection_matrix_vga[4]  = 0.0f;
  G_projection_matrix_vga[5]  = -2.0f / GRAFX_VGA_TEXTURE_HEIGHT;
  G_projection_matrix_vga[6]  = 0.0f;
  G_projection_matrix_vga[7]  = 0.0f;

  G_projection_matrix_vga[8]  = 0.0f;
  G_projection_matrix_vga[9]  = 0.0f;
  G_projection_matrix_vga[10] = 2.0f;
  G_projection_matrix_vga[11] = 0.0f;

  G_projection_matrix_vga[12] = -1.0f;
  G_projection_matrix_vga[13] = 1.0f;
  G_projection_matrix_vga[14] = -1.0f;
  G_projection_matrix_vga[15] = 1.0f;

  /* orthographic projection matrix (window) */
  G_projection_matrix_window[0]  = 2.0f / G_window_w;
  G_projection_matrix_window[1]  = 0.0f;
  G_projection_matrix_window[2]  = 0.0f;
  G_projection_matrix_window[3]  = 0.0f;

  G_projection_matrix_window[4]  = 0.0f;
  G_projection_matrix_window[5]  = -2.0f / G_window_h;
  G_projection_matrix_window[6]  = 0.0f;
  G_projection_matrix_window[7]  = 0.0f;

  G_projection_matrix_window[8]  = 0.0f;
  G_projection_matrix_window[9]  = 0.0f;
  G_projection_matrix_window[10] = 2.0f;
  G_projection_matrix_window[11] = 0.0f;

  G_projection_matrix_window[12] = -1.0f;
  G_projection_matrix_window[13] = 1.0f;
  G_projection_matrix_window[14] = -1.0f;
  G_projection_matrix_window[15] = 1.0f;

  /* create buffer objects */
  glGenBuffers(1, &G_vertex_buffer_id_sprites);
  glGenBuffers(1, &G_texcoord_buffer_id_sprites);
  glGenBuffers(1, &G_color_buffer_id_sprites);
  glGenBuffers(1, &G_index_buffer_id_sprites);

  glGenBuffers(1, &G_vertex_buffer_id_window);
  glGenBuffers(1, &G_texcoord_buffer_id_window);
  glGenBuffers(1, &G_index_buffer_id_window);

  /* allocate buffers */
  G_vertex_buffer_sprites = malloc(sizeof(GLfloat) * 3 * 4 * GRAFX_MAX_SPRITES);
  G_texcoord_buffer_sprites = malloc(sizeof(GLfloat) * 2 * 4 * GRAFX_MAX_SPRITES);
  G_color_buffer_sprites = malloc(sizeof(GLfloat) * 4 * 4 * GRAFX_MAX_SPRITES);
  G_index_buffer_sprites = malloc(sizeof(unsigned short) * 6 * GRAFX_MAX_SPRITES);

  /* initialize buffers */
  for (i = 0; i < GRAFX_MAX_SPRITES; i++)
  {
    for (j = 0; j < 12; j++)
      G_vertex_buffer_sprites[(i * 12) + j] = 0.0f;

    for (j = 0; j < 8; j++)
      G_texcoord_buffer_sprites[(i * 8) + j] = 0.0f;

    for (j = 0; j < 16; j++)
      G_color_buffer_sprites[(i * 16) + j] = 0.0f;

    for (j = 0; j < 6; j++)
      G_index_buffer_sprites[(i * 6) + j] = 0;
  }

  glBindBuffer(GL_ARRAY_BUFFER, G_vertex_buffer_id_sprites);
  glBufferData( GL_ARRAY_BUFFER, GRAFX_MAX_SPRITES * 12 * sizeof(GLfloat),
                G_vertex_buffer_sprites, GL_DYNAMIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, G_texcoord_buffer_id_sprites);
  glBufferData( GL_ARRAY_BUFFER, GRAFX_MAX_SPRITES * 8 * sizeof(GLfloat),
                G_texcoord_buffer_sprites, GL_DYNAMIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, G_color_buffer_id_sprites);
  glBufferData( GL_ARRAY_BUFFER, GRAFX_MAX_SPRITES * 16 * sizeof(GLfloat),
                G_color_buffer_sprites, GL_DYNAMIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, G_index_buffer_id_sprites);
  glBufferData( GL_ELEMENT_ARRAY_BUFFER, GRAFX_MAX_SPRITES * 6 * sizeof(unsigned short),
                G_index_buffer_sprites, GL_DYNAMIC_DRAW);

  /* set up window vertex buffer object */
  G_vertex_buffer_window[0] = 0.0f;
  G_vertex_buffer_window[1] = 0.0f;
  G_vertex_buffer_window[2] = 0.0f;

  G_vertex_buffer_window[3] = (GLfloat) G_window_w;
  G_vertex_buffer_window[4] = 0.0f;
  G_vertex_buffer_window[5] = 0.0f;

  G_vertex_buffer_window[6] = 0.0f;
  G_vertex_buffer_window[7] = (GLfloat) G_window_h;
  G_vertex_buffer_window[8] = 0.0f;

  G_vertex_buffer_window[9] = (GLfloat) G_window_w;
  G_vertex_buffer_window[10] = (GLfloat) G_window_h;
  G_vertex_buffer_window[11] = 0.0f;

  glBindBuffer(GL_ARRAY_BUFFER, G_vertex_buffer_id_window);
  glBufferData( GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), 
                G_vertex_buffer_window, GL_STATIC_DRAW);

  /* set up window texture coordinate buffer object */
  G_texcoord_buffer_window[0] = 0.0f;
  G_texcoord_buffer_window[1] = 1.0f;

  G_texcoord_buffer_window[2] = (GLfloat) GRAFX_VGA_OUTPUT_WIDTH / GRAFX_VGA_TEXTURE_WIDTH;
  G_texcoord_buffer_window[3] = 1.0f;

  G_texcoord_buffer_window[4] = 0.0f;
  G_texcoord_buffer_window[5] = 1.0f - (GLfloat) GRAFX_VGA_OUTPUT_HEIGHT / GRAFX_VGA_TEXTURE_HEIGHT;

  G_texcoord_buffer_window[6] = (GLfloat) GRAFX_VGA_OUTPUT_WIDTH / GRAFX_VGA_TEXTURE_WIDTH;
  G_texcoord_buffer_window[7] = 1.0f - (GLfloat) GRAFX_VGA_OUTPUT_HEIGHT / GRAFX_VGA_TEXTURE_HEIGHT;

  glBindBuffer(GL_ARRAY_BUFFER, G_texcoord_buffer_id_window);
  glBufferData( GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), 
                G_texcoord_buffer_window, GL_STATIC_DRAW);

  /* set up window index buffer object */
  G_index_buffer_window[0] = 0;
  G_index_buffer_window[1] = 2;
  G_index_buffer_window[2] = 1;

  G_index_buffer_window[3] = 1;
  G_index_buffer_window[4] = 2;
  G_index_buffer_window[5] = 3;

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, G_index_buffer_id_window);
  glBufferData( GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned short), 
                G_index_buffer_window, GL_STATIC_DRAW);

  return 0;
}

/*******************************************************************************
** grafx_destroy_opengl_objects()
*******************************************************************************/
short int grafx_destroy_opengl_objects()
{
  /* delete buffer objects */
  glDeleteBuffers(1, &G_vertex_buffer_id_sprites);
  glDeleteBuffers(1, &G_texcoord_buffer_id_sprites);
  glDeleteBuffers(1, &G_color_buffer_id_sprites);
  glDeleteBuffers(1, &G_index_buffer_id_sprites);

  glDeleteBuffers(1, &G_vertex_buffer_id_window);
  glDeleteBuffers(1, &G_texcoord_buffer_id_window);
  glDeleteBuffers(1, &G_index_buffer_id_window);

  /* delete framebuffer object */
  glDeleteFramebuffers(1, &G_framebuffer_id_vga);
  glDeleteRenderbuffers(1, &G_renderbuffer_id_vga);

  /* delete vga texture */
  glDeleteTextures(1, &G_texture_id_vga);

  /* delete opengl shader programs */
  glDeleteProgram(G_program_id_A);
  glDeleteProgram(G_program_id_B);

  /* delete vertex array object */
  glDeleteVertexArrays(1, &G_vertex_array_id);

  /* free buffers */
  if (G_vertex_buffer_sprites != NULL)
  {
    free(G_vertex_buffer_sprites);
    G_vertex_buffer_sprites = NULL;
  }

  if (G_texcoord_buffer_sprites != NULL)
  {
    free(G_texcoord_buffer_sprites);
    G_texcoord_buffer_sprites = NULL;
  }

  if (G_color_buffer_sprites != NULL)
  {
    free(G_color_buffer_sprites);
    G_color_buffer_sprites = NULL;
  }

  if (G_index_buffer_sprites != NULL)
  {
    free(G_index_buffer_sprites);
    G_index_buffer_sprites = NULL;
  }

  return 0;
}

/*******************************************************************************
** grafx_check_desktop_resolution()
*******************************************************************************/
short int grafx_check_desktop_resolution()
{
  int             index;
  SDL_DisplayMode mode;

  /* determine display resolution */
  index = SDL_GetWindowDisplayIndex(G_sdl_window);
  SDL_GetDesktopDisplayMode(index, &mode);

  /* make sure display resolution is at least 640x480 */
  if ((mode.w < 640) || (mode.h < 480))
  {
    printf("Current Display Resolution must be at least 640x480.\n");
    return 1;
  }

  return 0;
}

/*******************************************************************************
** grafx_setup_desktop_resolution()
*******************************************************************************/
short int grafx_setup_desktop_resolution()
{
  int             index;
  SDL_DisplayMode mode;

  /* determine display resolution */
  index = SDL_GetWindowDisplayIndex(G_sdl_window);
  SDL_GetDesktopDisplayMode(index, &mode);

  /* set desktop resolution */
  G_desktop_w = mode.w;
  G_desktop_h = mode.h;

  return 0;
}

/*******************************************************************************
** grafx_setup_windowed()
*******************************************************************************/
short int grafx_setup_windowed()
{
  if ((G_window_w <= 0) || (G_window_h <= 0))
    return 1;

  /* orthographic projection matrix (window) */
  G_projection_matrix_window[0]  = 2.0f / G_window_w;
  G_projection_matrix_window[1]  = 0.0f;
  G_projection_matrix_window[2]  = 0.0f;
  G_projection_matrix_window[3]  = 0.0f;

  G_projection_matrix_window[4]  = 0.0f;
  G_projection_matrix_window[5]  = -2.0f / G_window_h;
  G_projection_matrix_window[6]  = 0.0f;
  G_projection_matrix_window[7]  = 0.0f;

  G_projection_matrix_window[8]  = 0.0f;
  G_projection_matrix_window[9]  = 0.0f;
  G_projection_matrix_window[10] = 2.0f;
  G_projection_matrix_window[11] = 0.0f;

  G_projection_matrix_window[12] = -1.0f;
  G_projection_matrix_window[13] = 1.0f;
  G_projection_matrix_window[14] = -1.0f;
  G_projection_matrix_window[15] = 1.0f;

  /* set up window vertex buffer object */
  G_vertex_buffer_window[0] = 0.0f;
  G_vertex_buffer_window[1] = 0.0f;
  G_vertex_buffer_window[2] = 0.0f;

  G_vertex_buffer_window[3] = (GLfloat) G_window_w;
  G_vertex_buffer_window[4] = 0.0f;
  G_vertex_buffer_window[5] = 0.0f;

  G_vertex_buffer_window[6] = 0.0f;
  G_vertex_buffer_window[7] = (GLfloat) G_window_h;
  G_vertex_buffer_window[8] = 0.0f;

  G_vertex_buffer_window[9] = (GLfloat) G_window_w;
  G_vertex_buffer_window[10] = (GLfloat) G_window_h;
  G_vertex_buffer_window[11] = 0.0f;

  glBindBuffer(GL_ARRAY_BUFFER, G_vertex_buffer_id_window);
  glBufferSubData(GL_ARRAY_BUFFER, 0, 12 * sizeof(GLfloat), 
                  G_vertex_buffer_window);

  /* set up viewport width and height */
  G_viewport_w = G_window_w;
  G_viewport_h = G_window_h;

  return 0;
}

/*******************************************************************************
** grafx_setup_fullscreen()
*******************************************************************************/
short int grafx_setup_fullscreen()
{
  int output_w;
  int output_h;

  /* setup desktop resolution */
  grafx_setup_desktop_resolution();

  /* 4:3 aspect ratio */
  if ((G_desktop_w / 4) == (G_desktop_h / 3))
  {
    output_w = G_desktop_w;
    output_h = G_desktop_h;
  }
  /* widescreen */
  else if ((G_desktop_w / 4) > (G_desktop_h / 3))
  {
    output_w = 4 * (G_desktop_h / 3);
    output_h = G_desktop_h;
  }
  /* tate */
  else
  {
    output_w = G_desktop_w;
    output_h = 3 * (G_desktop_w / 4);
  }

  /* orthographic projection matrix (window) */
  G_projection_matrix_window[0]  = 2.0f / G_desktop_w;
  G_projection_matrix_window[1]  = 0.0f;
  G_projection_matrix_window[2]  = 0.0f;
  G_projection_matrix_window[3]  = 0.0f;

  G_projection_matrix_window[4]  = 0.0f;
  G_projection_matrix_window[5]  = -2.0f / G_desktop_h;
  G_projection_matrix_window[6]  = 0.0f;
  G_projection_matrix_window[7]  = 0.0f;

  G_projection_matrix_window[8]  = 0.0f;
  G_projection_matrix_window[9]  = 0.0f;
  G_projection_matrix_window[10] = 2.0f;
  G_projection_matrix_window[11] = 0.0f;

  G_projection_matrix_window[12] = -1.0f;
  G_projection_matrix_window[13] = 1.0f;
  G_projection_matrix_window[14] = -1.0f;
  G_projection_matrix_window[15] = 1.0f;

  /* set up window vertex buffer object */
  G_vertex_buffer_window[0] = (GLfloat) (G_desktop_w - output_w) / 2.0f;
  G_vertex_buffer_window[1] = (GLfloat) (G_desktop_h - output_h) / 2.0f;
  G_vertex_buffer_window[2] = 0.0f;

  G_vertex_buffer_window[3] = (GLfloat) (G_desktop_w + output_w) / 2.0f;
  G_vertex_buffer_window[4] = (GLfloat) (G_desktop_h - output_h) / 2.0f;
  G_vertex_buffer_window[5] = 0.0f;

  G_vertex_buffer_window[6] = (GLfloat) (G_desktop_w - output_w) / 2.0f;
  G_vertex_buffer_window[7] = (GLfloat) (G_desktop_h + output_h) / 2.0f;
  G_vertex_buffer_window[8] = 0.0f;

  G_vertex_buffer_window[9] = (GLfloat) (G_desktop_w + output_w) / 2.0f;
  G_vertex_buffer_window[10] = (GLfloat) (G_desktop_h + output_h) / 2.0f;
  G_vertex_buffer_window[11] = 0.0f;

  glBindBuffer(GL_ARRAY_BUFFER, G_vertex_buffer_id_window);
  glBufferSubData(GL_ARRAY_BUFFER, 0, 12 * sizeof(GLfloat), 
                  G_vertex_buffer_window);

  /* set up viewport width and height */
  G_viewport_w = G_desktop_w;
  G_viewport_h = G_desktop_h;

  return 0;
}

/*******************************************************************************
** grafx_decrease_window_size()
*******************************************************************************/
short int grafx_decrease_window_size()
{
  if ((G_window_w <= 0) || (G_window_h <= 0))
    return 1;

  /* decrease window size, if possible */
  if (G_window_h == GRAFX_WINDOW_HEIGHT_OPTION_1)
    return 0;
  else if (G_window_h == GRAFX_WINDOW_HEIGHT_OPTION_2)
  {
    G_window_w = GRAFX_WINDOW_WIDTH_OPTION_1;
    G_window_h = GRAFX_WINDOW_HEIGHT_OPTION_1;
  }
  else if (G_window_h == GRAFX_WINDOW_HEIGHT_OPTION_3)
  {
    G_window_w = GRAFX_WINDOW_WIDTH_OPTION_2;
    G_window_h = GRAFX_WINDOW_HEIGHT_OPTION_2;
  }
  else if (G_window_h == GRAFX_WINDOW_HEIGHT_OPTION_4)
  {
    G_window_w = GRAFX_WINDOW_WIDTH_OPTION_3;
    G_window_h = GRAFX_WINDOW_HEIGHT_OPTION_3;
  }

  /* change the window size, if we are not in fullscreen mode */
  if (G_fullscreen_flag == 0x00)
  {
    SDL_SetWindowSize(G_sdl_window, G_window_w, G_window_h);
    grafx_setup_windowed();
  }

  return 0;
}

/*******************************************************************************
** grafx_increase_window_size()
*******************************************************************************/
short int grafx_increase_window_size()
{
  if ((G_window_w <= 0) || (G_window_h <= 0))
    return 1;

  /* increase window size, if possible */
  if ((G_window_h == GRAFX_WINDOW_HEIGHT_OPTION_1)  &&
      (G_desktop_w > GRAFX_WINDOW_WIDTH_OPTION_2)   &&
      (G_desktop_h > GRAFX_WINDOW_HEIGHT_OPTION_2))
  {
    G_window_w = GRAFX_WINDOW_WIDTH_OPTION_2;
    G_window_h = GRAFX_WINDOW_HEIGHT_OPTION_2;
  }
  else if ( (G_window_h == GRAFX_WINDOW_HEIGHT_OPTION_2)  &&
            (G_desktop_w > GRAFX_WINDOW_WIDTH_OPTION_3)   &&
            (G_desktop_h > GRAFX_WINDOW_HEIGHT_OPTION_3))
  {
    G_window_w = GRAFX_WINDOW_WIDTH_OPTION_3;
    G_window_h = GRAFX_WINDOW_HEIGHT_OPTION_3;
  }
  else if ( (G_window_h == GRAFX_WINDOW_HEIGHT_OPTION_3)  &&
            (G_desktop_w > GRAFX_WINDOW_WIDTH_OPTION_4)   &&
            (G_desktop_h > GRAFX_WINDOW_HEIGHT_OPTION_4))
  {
    G_window_w = GRAFX_WINDOW_WIDTH_OPTION_4;
    G_window_h = GRAFX_WINDOW_HEIGHT_OPTION_4;
  }
  else if (G_window_h == GRAFX_WINDOW_HEIGHT_OPTION_4)
    return 0;

  /* change the window size, if we are not in fullscreen mode */
  if (G_fullscreen_flag == 0x00)
  {
    SDL_SetWindowSize(G_sdl_window, G_window_w, G_window_h);
    grafx_setup_windowed();
  }

  return 0;
}
