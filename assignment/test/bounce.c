#include "ir_uart.h"
#include "system.h"
#include "display.h"

/*
void bounce_init(void)
{
    static char row = 3;
    static char col = 2;
    static char colSpeed = 1;
    static char rowSpeed = 1;

    display_pixel_set (col, row, 1);
    uint8_t bounce_tick = 0;
    uint8_t bar_tick = 0;
}
*/




void bounce_normal(char* col, char* row, char* colSpeed, char* rowSpeed, uint8_t* game_over)
{

    *col += *colSpeed;
    *row += *rowSpeed;

    if (*row > 6 || *row < 0) {
        *row -= *rowSpeed * 2;
        *rowSpeed = -*rowSpeed;
    }

    if (*col > 4 ) {
        *game_over = 2;
        ir_uart_putc('w');
    }
}

void bounce_collision(char* col, char* row, char* colSpeed, uint8_t currentCenter)
{
    //collision
    if (*col == 4 ) {
        if( *row == currentCenter + 1) {
            *col -= *colSpeed * 2;
            *colSpeed = -*colSpeed;

        }
        if (*row == currentCenter) {
            *col -= *colSpeed * 2;
            *colSpeed = -*colSpeed;
        }

        if (*row == currentCenter - 1) {
            *col -= *colSpeed * 2;
            *colSpeed = -*colSpeed;
        }

    }
}



void bounce_send(char* col, char* row, char* rowSpeed)
{
    if (*col == 0) {
        int sendRow = *row;
        ir_uart_putc('b');
        char invert_array[] = {6, 5, 4, 3, 2, 1, 0};
        char send_ball_row;
        send_ball_row = invert_array[sendRow];
        ir_uart_putc(send_ball_row);


        char send_ball_row_speed;
        send_ball_row_speed = - *rowSpeed;
        ir_uart_putc(send_ball_row_speed);

    }
}




void bounce_task(char *col, char *row, char *colSpeed, char *rowSpeed, uint8_t currentCenter, uint8_t* game_over)
{
    display_pixel_set (*col, *row, 0);
    bounce_normal(col, row, colSpeed, rowSpeed, game_over);
    bounce_collision(col, row, colSpeed , currentCenter);
    bounce_send(col, row, rowSpeed);
    display_pixel_set (*col, *row, 1);


}


