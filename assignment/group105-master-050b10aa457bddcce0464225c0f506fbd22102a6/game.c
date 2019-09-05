
/* @ file game.c
 * @ author Nam Vu & Sunesh Parbhu
 * @ date October 2018
 * @ brief:
 * 
 *          This program is a a pong based game to be played between two
 *          UCFK4 boards. To begin both players must push the navswitch
 *          down to 'ready up', then to release the ball one of the
 *          players is to pull the navswitch towards them to release the
 *          ball.
 * */


// ENCE 260 provided modules
#include "system.h"
#include "pacer.h"
#include <string.h>
#include "tinygl.h"
#include "../fonts/font5x5_1.h"
#include "ir_uart.h"
#include "display.h"
#include "led.h"

// Self written modules
#include "bar.h"
#include "message_task.h"
#include "bounce.h"
#include "receive_task.h"


#define PACER_RATE 500



int main (void)
{
    // initalise ENCE 260 modules
    led_init ();
    system_init ();
    display_init ();
    pacer_init (PACER_RATE);
    ir_uart_init ();

    // initalise game states
    uint8_t currentState = 0;  
    uint8_t game_over = 0;


    start_routine(currentState);

    message_task();
    char row = 0;
    char col = -2;
    char colSpeed = -1;
    char rowSpeed = 1;
    display_pixel_set (col, row, 1);

    // initalise bar/ paddle
    bar_init();
    // initalise variables
    uint8_t state = 0;
    uint8_t bounce_tick = 0;
    uint8_t bar_tick = 0;
    uint8_t lose_tick = 0;
    uint8_t led_tick = 0;
    int led_tick_rate = 200;
   

    while (1) {

        // Wait 5ms
        pacer_wait(); 
        bounce_tick++;
        bar_tick++;
        lose_tick++;
        led_tick++;

        // Checking for a new ball to be released
        if (release_routine()) {
            row = 5;
            col = 1;
            colSpeed = 1;
            rowSpeed = 1;
            display_pixel_set (col, row, 1);
        }

        // Game not over, continue game
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
        
        // Game Over, display ending message 
        if(game_over == 2) {
            tinygl_update();
            led_tick_rate = 50;
        }
        // Flash LED
        if (led_tick >=  led_tick_rate) {
            led_tick = 0;
            led_set  (LED1, state);
            state = !state;
        }
    }
}
