#include "tinygl.h"
#include "ir_uart.h"
#include "display.h"


void receive_task(char* col, char* row, char* colSpeed, char* rowSpeed, uint8_t* currentState, uint8_t* game_over);
