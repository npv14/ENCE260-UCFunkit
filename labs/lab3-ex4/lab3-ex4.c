#include "system.h"
#include "button.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"


#define PACER_RATE 2000
#define MESSAGE_RATE 10

#define BUTTON_TASK_RATE 100

#define DISPLAY_TASK_RATE 250

#define TIMER_TASK_RATE 100
static bool run;

static void timer_task (void)
{
    static uint16_t time;
    char str[3];

    if (!run) {
        time = 0;
        return;
    }

    str[0] = ((time / 10) % 10) + '0';
    str[1] = (time % 10) + '0';
    str[2] = 0;

    tinygl_text (str);

    time++;
}



static void display_task (void )
{
    tinygl_update ();
}


static void button_task (void)
{
    button_update ();

    if (button_push_event_p (BUTTON1))
    {
        run = !run;
    }
}

int main (void)
{
    system_init();

    /* TODO: Initialise the button driver, tinygl, and the pacer.  */

    button_init ();
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);

    pacer_init (PACER_RATE);
    tinygl_text ("00");
    uint8_t button_tick = 0;
    uint8_t display_tick = 0;
    uint8_t timer_tick = 0;

    while(1) {
        pacer_wait();



        /* TODO: Implement the functionality of the tasks in the
               stopwatch1 program.  */
        if (display_tick >=  2) {
            display_tick = 0;
            display_task();
        }
        if (button_tick >=  50) {
            button_tick = 0;
            button_task();
        }
        if (timer_tick >=  50) {
            timer_tick = 0;
            timer_task();
        }
        display_tick++;
        timer_tick++;
        button_tick++;



    }
    return 0;
}
