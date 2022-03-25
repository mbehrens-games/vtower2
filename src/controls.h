/*******************************************************************************
** controls.h (keyboard / joystick input)
*******************************************************************************/

#ifndef CONTROLS_H
#define CONTROLS_H

#include <SDL2/SDL.h>

#define CONTROLS_INPUT_FLAGS_CLEAR  0x00
#define CONTROLS_INPUT_FLAG_RIGHT   0x01
#define CONTROLS_INPUT_FLAG_UP      0x02
#define CONTROLS_INPUT_FLAG_LEFT    0x04
#define CONTROLS_INPUT_FLAG_DOWN    0x08
#define CONTROLS_INPUT_FLAG_BAT     0x10
#define CONTROLS_INPUT_FLAG_ICE     0x20
#define CONTROLS_INPUT_FLAG_WARP    0x40
#define CONTROLS_INPUT_FLAG_HOLD    0x80

#define CONTROLS_HUD_FLAGS_CLEAR      0x00
#define CONTROLS_HUD_FLAG_CONFIRM     0x01
#define CONTROLS_HUD_FLAG_CANCEL      0x02
#define CONTROLS_HUD_FLAG_HELP        0x04
#define CONTROLS_HUD_FLAG_ROOM_SELECT 0x08
#define CONTROLS_HUD_FLAG_RESTART     0x10
#define CONTROLS_HUD_FLAG_PAUSE       0x20
#define CONTROLS_HUD_FLAG_OPTIONS     0x40
#define CONTROLS_HUD_FLAG_FULLSCREEN  0x80

extern unsigned char  G_last_input_flags;
extern unsigned char  G_current_input_flags;
extern unsigned char  G_last_hud_flags;
extern unsigned char  G_current_hud_flags;
extern const Uint8*   G_keyboard_state;

/* function declarations */
short int controls_init();
short int controls_update_from_keyboard();
short int controls_process_player_input();

#endif
