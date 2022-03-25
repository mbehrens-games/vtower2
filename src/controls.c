/*******************************************************************************
** controls.h (keyboard / joystick input)
*******************************************************************************/

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "animate.h"
#include "controls.h"
#include "entity.h"
#include "global.h"
#include "logic.h"

unsigned char G_last_input_flags;
unsigned char G_current_input_flags;
unsigned char G_last_hud_flags;
unsigned char G_current_hud_flags;

const Uint8*  G_keyboard_state;

/*******************************************************************************
** controls_init()
*******************************************************************************/
short int controls_init()
{
  G_last_input_flags = CONTROLS_INPUT_FLAGS_CLEAR;
  G_current_input_flags = CONTROLS_INPUT_FLAGS_CLEAR;
  G_last_hud_flags = CONTROLS_HUD_FLAGS_CLEAR;
  G_current_hud_flags = CONTROLS_HUD_FLAGS_CLEAR;

  /* initalize keyboard state pointer */
  G_keyboard_state = SDL_GetKeyboardState(NULL);

  return 0;
}

/*******************************************************************************
** controls_update_from_keyboard()
*******************************************************************************/
short int controls_update_from_keyboard()
{
  /* input keys */
  G_last_input_flags = G_current_input_flags;
  G_current_input_flags = CONTROLS_INPUT_FLAGS_CLEAR;

  if (G_keyboard_state[SDL_SCANCODE_RIGHT])
    G_current_input_flags |= CONTROLS_INPUT_FLAG_RIGHT;

  if (G_keyboard_state[SDL_SCANCODE_UP])
    G_current_input_flags |= CONTROLS_INPUT_FLAG_UP;

  if (G_keyboard_state[SDL_SCANCODE_LEFT])
    G_current_input_flags |= CONTROLS_INPUT_FLAG_LEFT;

  if (G_keyboard_state[SDL_SCANCODE_DOWN])
    G_current_input_flags |= CONTROLS_INPUT_FLAG_DOWN;

  if (G_keyboard_state[SDL_SCANCODE_Z])
    G_current_input_flags |= CONTROLS_INPUT_FLAG_BAT;

  if (G_keyboard_state[SDL_SCANCODE_X])
    G_current_input_flags |= CONTROLS_INPUT_FLAG_ICE;

  if (G_keyboard_state[SDL_SCANCODE_C])
    G_current_input_flags |= CONTROLS_INPUT_FLAG_WARP;

  if (G_keyboard_state[SDL_SCANCODE_LSHIFT])
    G_current_input_flags |= CONTROLS_INPUT_FLAG_HOLD;

  if (G_keyboard_state[SDL_SCANCODE_RSHIFT])
    G_current_input_flags |= CONTROLS_INPUT_FLAG_HOLD;

  /* hud keys */
  G_last_hud_flags = G_current_hud_flags;
  G_current_hud_flags = CONTROLS_HUD_FLAGS_CLEAR;

  if (G_keyboard_state[SDL_SCANCODE_RETURN])
    G_current_hud_flags |= CONTROLS_HUD_FLAG_CONFIRM;

  if (G_keyboard_state[SDL_SCANCODE_SPACE])
    G_current_hud_flags |= CONTROLS_HUD_FLAG_CONFIRM;

  if (G_keyboard_state[SDL_SCANCODE_ESCAPE])
    G_current_hud_flags |= CONTROLS_HUD_FLAG_CANCEL;

  if (G_keyboard_state[SDL_SCANCODE_F1])
    G_current_hud_flags |= CONTROLS_HUD_FLAG_HELP;

  if (G_keyboard_state[SDL_SCANCODE_H])
    G_current_hud_flags |= CONTROLS_HUD_FLAG_HELP;

  if (G_keyboard_state[SDL_SCANCODE_TAB])
    G_current_hud_flags |= CONTROLS_HUD_FLAG_ROOM_SELECT;

  if (G_keyboard_state[SDL_SCANCODE_R])
    G_current_hud_flags |= CONTROLS_HUD_FLAG_RESTART;

  if (G_keyboard_state[SDL_SCANCODE_P])
    G_current_hud_flags |= CONTROLS_HUD_FLAG_PAUSE;

  if (G_keyboard_state[SDL_SCANCODE_O])
    G_current_hud_flags |= CONTROLS_HUD_FLAG_OPTIONS;

  if (G_keyboard_state[SDL_SCANCODE_BACKSLASH])
    G_current_hud_flags |= CONTROLS_HUD_FLAG_FULLSCREEN;

  return 0;
}

/*******************************************************************************
** controls_process_player_input()
*******************************************************************************/
short int controls_process_player_input()
{
  /* make sure player exists */
  if (G_player == NULL)
    return 0;

  /* make sure player is not marked for death */
  if (G_player->collision_flags & ENTITY_COLLISION_FLAG_DESTROYED)
    return 0;

  /* make sure player is a vampire or a bat */
  if ((G_player->type != ENTITY_TYPE_PLAYER_VAMPIRE) &&
      (G_player->type != ENTITY_TYPE_PLAYER_BAT))
  {
    return 0;
  }

  /* bat transform (on rising edge) */
  if ((G_current_input_flags & CONTROLS_INPUT_FLAG_BAT) &&
      (!(G_last_input_flags & CONTROLS_INPUT_FLAG_BAT)))
  {
    /* if player is acting, but not transforming, */
    /* carry button press to next frame           */
    if (ENTITY_IS_PERFORMING_ACTION(G_player))
    {
      if (!(G_player->update_flags & ENTITY_UPDATE_FLAG_TRANSFORMING))
        G_current_input_flags &= ~CONTROLS_INPUT_FLAG_BAT;

      return 0;
    }

    logic_player_key_bat_transform();

    /* if transform was successful, return */
    if (G_player->update_flags & ENTITY_UPDATE_FLAG_TRANSFORMING)
      return 0;
  }

  /* ice spell (on rising edge) */
  if ((G_current_input_flags & CONTROLS_INPUT_FLAG_ICE) &&
      (!(G_last_input_flags & CONTROLS_INPUT_FLAG_ICE)))
  {
    /* if player is acting, but not casting,  */
    /* carry button press to next frame       */
    if (ENTITY_IS_PERFORMING_ACTION(G_player))
    {
      if (!(G_player->action_flags & ENTITY_ACTION_FLAG_CASTING))
        G_current_input_flags &= ~CONTROLS_INPUT_FLAG_ICE;

      return 0;
    }

    logic_player_key_ice_spell();

    /* if spell cast was successful, return */
    if (G_player->action_flags & ENTITY_ACTION_FLAG_CASTING)
      return 0;
  }

  /* warp spell (on rising edge) */
  if ((G_current_input_flags & CONTROLS_INPUT_FLAG_WARP) &&
      (!(G_last_input_flags & CONTROLS_INPUT_FLAG_WARP)))
  {
    /* if player is acting, but not casting,  */
    /* carry button press to next frame       */
    if (ENTITY_IS_PERFORMING_ACTION(G_player))
    {
      if (!(G_player->action_flags & ENTITY_ACTION_FLAG_CASTING))
        G_current_input_flags &= ~CONTROLS_INPUT_FLAG_WARP;

      return 0;
    }

    logic_player_key_warp_spell();

    /* if spell cast was successful, return */
    if (G_player->action_flags & ENTITY_ACTION_FLAG_CASTING)
      return 0;
  }

  /* hold on (change facing direction without moving) */
  if (G_current_input_flags & CONTROLS_INPUT_FLAG_HOLD)
  {
    if (G_current_input_flags & CONTROLS_INPUT_FLAG_RIGHT)
      logic_player_key_turn(ENTITY_FACING_RIGHT);

    if (G_current_input_flags & CONTROLS_INPUT_FLAG_UP)
      logic_player_key_turn(ENTITY_FACING_UP);

    if (G_current_input_flags & CONTROLS_INPUT_FLAG_LEFT)
      logic_player_key_turn(ENTITY_FACING_LEFT);

    if (G_current_input_flags & CONTROLS_INPUT_FLAG_DOWN)
      logic_player_key_turn(ENTITY_FACING_DOWN);
  }
  /* hold off (attempt move in direction pressed) */
  else
  {
    if (G_current_input_flags & CONTROLS_INPUT_FLAG_RIGHT)
      logic_player_key_move(ENTITY_DIRECTION_RIGHT);

    if (G_current_input_flags & CONTROLS_INPUT_FLAG_UP)
      logic_player_key_move(ENTITY_DIRECTION_UP);

    if (G_current_input_flags & CONTROLS_INPUT_FLAG_LEFT)
      logic_player_key_move(ENTITY_DIRECTION_LEFT);

    if (G_current_input_flags & CONTROLS_INPUT_FLAG_DOWN)
      logic_player_key_move(ENTITY_DIRECTION_DOWN);
  }

  return 0;
}
