/* @ file message_task.c
 * @ author Nam Vu & Sunesh Parbhu
 * @ date October 2018
 */
 
#include "tinygl.h"
#include "../fonts/font5x5_1.h"

// display a message
void message_task(void)
{
    tinygl_init (500);
    tinygl_font_set(&font5x5_1);
    tinygl_text_speed_set(10);
    char* text = "Loser";
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
    tinygl_text(text);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
}

