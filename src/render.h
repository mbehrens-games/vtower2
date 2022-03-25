/*******************************************************************************
** render.h (opengl rendering)
*******************************************************************************/

#ifndef RENDER_H
#define RENDER_H

/*#include <SDL2/SDL_opengl.h>*/
#include <glad/glad.h>

/* function declarations */
short int render_generate_tables();
short int render_scene();

short int render_pause_panel();
short int render_room_select_panel();
short int render_options_panel();
short int render_try_again_panel();
short int render_menu_panel();

short int render_room_transition();

short int render_title_screen();
short int render_credits_screen();
short int render_world_select_screen();
short int render_story_select_screen();
short int render_story_screen();
short int render_help_screen();

short int render_vga_to_window();

#endif
