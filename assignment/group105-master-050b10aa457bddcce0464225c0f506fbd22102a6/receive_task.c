/* @ file receive_tack.c
 * @ author Nam Vu & Sunesh Parbhu
 * @ date October 2018
 */
 
#include "receive_task.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "display.h"

// Receive ball and game data from other board
void receive_task(char* col, char* row, char* colSpeed, char* rowSpeed, uint8_t* currentState, uint8_t* game_over)
{

    char noti = ir_uart_getc();
    if (noti == 'b') {
        char reciever_row;
        reciever_row = ir_uart_getc();
        *row = reciever_row;
        *col = 0;
        *colSpeed = 1;
        *rowSpeed = ir_uart_getc();
        display_pixel_set (*col, *row, 1);
    }
    if (noti == 'w') {
        *game_over = 2;
        tinygl_text("Winner");
        tinygl_update();
        *currentState = 0;

    }
}

