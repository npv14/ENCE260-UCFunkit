#include "ir_uart.h"
#include "system.h"
#include "display.h"

void bounce_init(void);

void bounce_normal(char* col, char* row, char* colSpeed, char* rowSpeed, uint8_t* game_over);

void bounce_collision(char* col, char* row, char* colSpeed, uint8_t currentCenter);

void bounce_send(char* col, char* row, char* rowSpeed);

void bounce_task(char *col, char *row, char *colSpeed, char *rowSpeed, uint8_t currentCenter, uint8_t* game_over);

