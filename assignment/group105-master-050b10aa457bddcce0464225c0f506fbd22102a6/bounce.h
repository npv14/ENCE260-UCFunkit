/* @ file bounce.h
 * @ author Nam Vu & Sunesh Parbhu
 * @ date October 2018
 */
 
#include "ir_uart.h"
#include "system.h"
#include "display.h"

// Move ball with no special conditions
void bounce_normal(char* col, char* row, char* colSpeed, char* rowSpeed, uint8_t* game_over);

// Ball collision with bar
void bounce_collision(char* col, char* row, char* colSpeed, uint8_t currentCenter);

// Send ball to other board
void bounce_send(char* col, char* row, char* rowSpeed);

// Full bounce task
void bounce_task(char *col, char *row, char *colSpeed, char *rowSpeed, uint8_t currentCenter, uint8_t* game_over);

