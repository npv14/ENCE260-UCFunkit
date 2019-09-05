#include "system.h"
#include "pacer.h"
#include <string.h>
#include "tinygl.h"
#include "../fonts/font5x5_1.h"
#include "ir_uart.h"
#include "display.h"
#include "bar.h"
#include "led.h"
#include "message_task.h"
#include "bounce.h"
#include "receive_task.h"
#define PACER_RATE 500

int main (void)
{

    led_init ();
    system_init ();
    display_init ();
    pacer_init (PACER_RATE);
    ir_uart_init ();

    uint8_t currentState = 0;  // Game is not playing
    uint8_t game_over = 0;

    /* ******************* Start Routine***************** */

    start_routine(currentState);

    message_task();
    char row = 0;
    char col = -2;
    char colSpeed = -1;
    char rowSpeed = 1;
    display_pixel_set (col, row, 1);


    //Bar
    bar_init();

    //Led
    uint8_t state = 0;


    //timer
    uint8_t bounce_tick = 0;
    uint8_t bar_tick = 0;
    uint8_t lose_tick = 0;
    uint8_t led_tick = 0;
    int led_tick_rate = 200;
    while (1) {


        pacer_wait(); // wait for 5ms
        bounce_tick++;
        bar_tick++;
        lose_tick++;
        led_tick++;


        if (release_routine()) {
            row = 5;
            col = 1;
            colSpeed = 1;
            rowSpeed = 1;
            display_pixel_set (col, row, 1);
        }


        if (game_over ==  0) {

            // Bounce Task
            if (bounce_tick >=  100) {
                int currentCenter1 = get_currentCenter();
                bounce_task(&col,  &row,  &colSpeed,  &rowSpeed, currentCenter1, &game_over);
                bounce_tick = 0;
            }
            // Bar Task
            if (bar_tick >=  10) {
                bar_task();
                bar_tick = 0;
            }
            // Receive Task

            if (ir_uart_read_ready_p()) {
                receive_task(&col, &row, &colSpeed, &rowSpeed, &currentState, &game_over);
            }
            // Update Display
            display_update ();

        }


        if(game_over == 2) {
            tinygl_update();
            led_tick_rate = 50;
        }


        if (led_tick >=  led_tick_rate) {
            led_tick = 0;
            led_set  (LED1, state);
            state = !state;
        }

    }
}
