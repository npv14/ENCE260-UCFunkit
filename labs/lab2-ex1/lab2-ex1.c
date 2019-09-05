#include <avr/io.h>
#include "system.h"
#include "led.h"
#include "pio.h"
void timer_delay (uint16_t ticks)
{
    TCNT1 = 0;
    while (TCNT1 < ticks) {
        continue;
    }

}

int main (void)
{
    system_init ();
    led_init ();

    /* TODO: Initialise timer/counter1.  */

    TCCR1A = 0x00;
    TCCR1B = 0x05;
    TCCR1C = 0x00;


    while (1) {

        /* Turn LED on.  */
        led_set (LED1, 1);


        /* TODO: wait for 500 milliseconds.  */
        timer_delay(58.59);
        /* Turn LED off.  */
        led_set (LED1, 0);


        /* TODO: wait for 500 milliseconds.  */
        timer_delay(19.53);

    }

}
