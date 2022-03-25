/*******************************************************************************
** grafx.h (opengl objects)
*******************************************************************************/

#ifndef GRAFX_H
#define GRAFX_H

#include <SDL2/SDL.h>
/*#include <SDL2/SDL_opengl.h>*/
#include <glad/glad.h>

#define GRAFX_WINDOW_WIDTH_OPTION_1   640
#define GRAFX_WINDOW_HEIGHT_OPTION_1  480

#define GRAFX_WINDOW_WIDTH_OPTION_2   960
#define GRAFX_WINDOW_HEIGHT_OPTION_2  720

#define GRAFX_WINDOW_WIDTH_OPTION_3   1024
#define GRAFX_WINDOW_HEIGHT_OPTION_3  768

#define GRAFX_WINDOW_WIDTH_OPTION_4   1440
#define GRAFX_WINDOW_HEIGHT_OPTION_4  1080

#define GRAFX_VGA_OUTPUT_WIDTH      640
#define GRAFX_VGA_OUTPUT_HEIGHT     480

#define GRAFX_VGA_TEXTURE_WIDTH     1024
#define GRAFX_VGA_TEXTURE_HEIGHT    512

#define GRAFX_MAX_SPRITES           500

extern SDL_Window*      G_sdl_window;

extern unsigned char    G_fullscreen_flag;

extern int              G_window_w;
extern int              G_window_h;

extern int              G_desktop_w;
extern int              G_desktop_h;

extern int              G_viewport_w;
extern int              G_viewport_h;

extern GLuint           G_texture_id_vga;

extern GLuint           G_vertex_array_id;

extern GLuint           G_vertex_buffer_id_sprites;
extern GLuint           G_texcoord_buffer_id_sprites;
extern GLuint           G_color_buffer_id_sprites;
extern GLuint           G_index_buffer_id_sprites;

extern GLuint           G_vertex_buffer_id_window;
extern GLuint           G_texcoord_buffer_id_window;
extern GLuint           G_index_buffer_id_window;

extern GLuint           G_framebuffer_id_vga;
extern GLuint           G_renderbuffer_id_vga;

extern GLuint           G_program_id_A;
extern GLuint           G_program_id_B;

extern GLuint           G_uniform_A_mvp_matrix_id;
extern GLuint           G_uniform_A_texture_sampler_id;

extern GLuint           G_uniform_B_mvp_matrix_id;

extern GLfloat*         G_vertex_buffer_sprites;
extern GLfloat*         G_texcoord_buffer_sprites;
extern GLfloat*         G_color_buffer_sprites;
extern unsigned short*  G_index_buffer_sprites;

extern GLfloat          G_vertex_buffer_window[12];
extern GLfloat          G_texcoord_buffer_window[8];
extern unsigned short   G_index_buffer_window[6];

extern GLfloat          G_projection_matrix_vga[16];
extern GLfloat          G_projection_matrix_window[16];

/* function declarations */
short int grafx_load_shaders(char* filename);
short int grafx_create_opengl_objects();
short int grafx_destroy_opengl_objects();

short int grafx_check_desktop_resolution();
short int grafx_setup_desktop_resolution();
short int grafx_setup_windowed();
short int grafx_setup_fullscreen();
short int grafx_decrease_window_size();
short int grafx_increase_window_size();

#endif
