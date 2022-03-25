/*******************************************************************************
** logic.h (game logic)
*******************************************************************************/

#ifndef LOGOS_H
#define LOGOS_H

#include "entity.h"

/* function declarations */
short int logic_player_key_move(unsigned char direction);
short int logic_player_key_turn(unsigned char facing);
short int logic_player_key_bat_transform();
short int logic_player_key_ice_spell();
short int logic_player_key_warp_spell();
short int logic_set_enemy_animations_based_on_player_position();
short int logic_check_spell_casters();
short int logic_check_evil_eye_casters();
short int logic_check_frogs();
short int logic_enemy_movements();
short int logic_convey_entities();
short int logic_activate_floor_triggers();
short int logic_set_floor_triggers(entity* e1);
short int logic_activate_venusian_roots();
short int logic_check_active_switches();
short int logic_process_lever_and_switch_flags();
short int logic_process_awaiting();
short int logic_process_solomons_seals();
short int logic_process_spell_casting();
short int logic_process_damage_and_transformations();
short int logic_movement_conclusions();
short int logic_setup_level();
short int logic_process_reflections();
short int logic_process_warps();
short int logic_evil_eye_update();

#endif
