/* @ file receive_task.h
 * @ author Nam Vu & Sunesh Parbhu
 * @ date October 2018
 */
 
#include "tinygl.h"
#include "ir_uart.h"
#include "display.h"

// Receive ball and game data from other board
void receive_task(char* col, char* row, char* colSpeed, char* rowSpeed, uint8_t* currentState, uint8_t* game_over);
