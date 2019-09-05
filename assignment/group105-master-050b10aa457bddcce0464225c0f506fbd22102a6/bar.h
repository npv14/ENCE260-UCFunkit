/* @ file bar.h
 * @ author Nam Vu & Sunesh Parbhu
 * @ date October 2018
 */
 
#ifndef BAR_H
#define BAR_H

#include "system.h"
#include "pio.h"
#include "navswitch.h"
#include "display.h"
#include "tinygl.h"
#include "../fonts/font5x5_1.h"




void bar_init(void);

int get_currentCenter(void);

int go_left(int* currentCenter);

int go_right(int* currentCenter);

void bar_task(void);

uint8_t start_game(uint8_t currentCenter);

void start_routine(uint8_t currentCenter);

uint8_t releaseBall(void);

uint8_t release_routine(void);

#endif //BAR_H
