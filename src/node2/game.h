#include <stdint.h>
#include "adc.h"

#ifndef __GAME_H__
#define __GAME_H__

void ir_init();
uint8_t ir_get_game_over_flag();
void ir_reset_game_over_flag();

#endif