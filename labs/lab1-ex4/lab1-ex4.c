#include "button.h"
#include "led.h"
#include "system.h"


int main (void)
{
    system_init ();

    led_init ();
    button_init ();

    while (1)
    {
        if (button_pressed_p ())
        {
            led_on ();
        }
        if (button_pressed_p ())
        {
            led_off ();
        }
    }
}
