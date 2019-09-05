#include <avr/io.h>
#include "timer.h"

/* Initialise timer.  */
void timer_init (void)
{
    /* TODO */
    TCCR1A = 0x00;
    TCCR1B = 0x05;
    TCCR1C = 0x00;

}


/* Wait for the specified length of time.  */
void timer_delay_ms (uint16_t milliseconds)
{
    uint16_t ticks = milliseconds * (1000  / 128.0);
    /* TODO: Calculate the timer/counter value needed
       for the given number of milliseconds. */

    /* TODO: Wait for the timer/couter to reach the
       value calculated above.  */
    TCNT1 = 0;
    while (TCNT1 < ticks) {
        continue;
    }

}
