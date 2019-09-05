#include "pio.h"
#include "button.h"
#define BNT_PIO PIO_DEFINE(PORT_D, 7)
/** Return non-zero if button pressed.  */
int button_pressed_p (void)
{
    if(pio_input_get(BNT_PIO)){
        return 12;
    }
    return 0;

    /* TODO.  */
}


/** Initialise button1.  */
void button_init (void)
{
    pio_config_set(BNT_PIO, PIO_INPUT);

    /* TODO.  */
}

