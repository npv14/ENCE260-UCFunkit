/** @file   ir_uart.c
    @author Michael Hayes
    @date   10 December 2004
*/
#include "system.h"
#include "ir_uart.h"
#include "usart1.h"
#include "timer0.h"
#include "pio.h"
#include "delay.h"


/* Return non-zero if there is a character ready to be read.  */
bool
ir_uart_read_ready_p (void)
{
    return usart1_read_ready_p ();
}


/* Read character from IR_UART.  This blocks if nothing
   is available to read.  */
int8_t
ir_uart_getc (void)
{
    return usart1_getc ();
}


/* Return non-zero if a character can be written without blocking.  */
bool
ir_uart_write_ready_p (void)
{
    return usart1_write_ready_p ();
}


/* Return non-zero if transmitter finished.  */
bool
ir_uart_write_finished_p (void)
{
    return usart1_write_finished_p ();
}


/* Write character to IR_UART.  This returns zero if
   the character could not be written.  */
int8_t
ir_uart_putc (char ch)
{
    usart1_putc (ch);

    /* Gobble echoed character.  The echoing is due to an electrical
       common-path interference problem caused by a poor PCB layout of the
       track powering the IR receiver.  Unfortunately, it does not always
       occur with some combination of UCFK4 boards and laptops.  Perhaps
       some laptops are more miserly with their current allocation and
       some IR LEDs do not draw as much current?  So as a workaround
       we need to wait until the transmission has finished and then check
       if something was immediately received. 

       Having said all this, it is possible to get an optical reflection
       of the transmitted signal.  The following code should handle this 
       as well.  */

    while (! ir_uart_write_finished_p ())
        continue;

    /* Play safe and wait for receive complete flag to be set.  */
    DELAY_US (1);
    
    if (ir_uart_read_ready_p ())
        ir_uart_getc ();

    return 1;
}


/* Write string to IR_UART.  */
void
ir_uart_puts (const char *str)
{
    usart1_puts (str);
}


/* Initialise ir_uart and set baud rate.  */
uint8_t
ir_uart_init (void)
{
    usart1_cfg_t usart1_cfg = 
        {
            .baud_divisor = USART1_BAUD_DIVISOR (IR_UART_BAUD_RATE),
            .bits = 8
        };


    /* Need to configure DDR so pin is an output.
       The state is controlled by the timer.  */
    pio_config_set (IR_TX_HIGH_PIO, PIO_OUTPUT_HIGH);
    timer0_init ();

    timer0_period_set (F_CPU / (IR_MODULATION_FREQ * 2));
    timer0_mode_set (TIMER0_MODE_CTC);
    timer0_output_set (TIMER0_OUTPUT_B, TIMER0_OUTPUT_MODE_TOGGLE);

    timer0_start ();

    return usart1_init (&usart1_cfg);
}
