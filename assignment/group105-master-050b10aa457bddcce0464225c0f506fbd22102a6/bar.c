/* @ file bar.c
 * @ author Nam Vu & Sunesh Parbhu
 * @ date October 2018
 */
 
#include "bar.h"
#include "navswitch.h"
#include  "display.h"
#include "tinygl.h"
#include "../fonts/font5x5_1.h"

#define BAR_COLUMN 4


static int currentCenter;

void bar_init(void)
{

    // Display
    display_init();

    display_clear();
    display_pixel_set(BAR_COLUMN, 2, 1); // Bar begins at center
    display_pixel_set(BAR_COLUMN, 3, 1);
    display_pixel_set(BAR_COLUMN, 4, 1);

    currentCenter = 3;

    // Controller
    navswitch_init();

}


int get_currentCenter(void)
{
    return currentCenter;
}


/* Moves the bar one unit to the left.
 * returns the new current position of the center of bar. */
int go_left(int *currentCenter)
{
    // case 1: On left edge
    if (*currentCenter >= 5 ) {
        return *currentCenter;

        //  case 2: Not on left edge
    } else {
        switch(*currentCenter) {
        case 1:
            display_pixel_set(BAR_COLUMN, 0, 0);
            display_pixel_set(BAR_COLUMN, 3, 1);
            break;
        case 2:
            display_pixel_set(BAR_COLUMN, 1, 0);
            display_pixel_set(BAR_COLUMN, 4, 1);
            break;
        case 3:
            display_pixel_set(BAR_COLUMN, 2, 0);
            display_pixel_set(BAR_COLUMN, 5, 1);
            break;
        case 4:
            display_pixel_set(BAR_COLUMN, 3, 0);
            display_pixel_set(BAR_COLUMN, 6, 1);
            break;
        }
    }

    return *currentCenter + 1;
}



/* Moves the bar one unit to the right.
 * return the new current position of the center of bar. */
int go_right(int* currentCenter)
{
    // Case 1: On right edge
    if (*currentCenter <= 1 ) {
        return *currentCenter;

        // Case 2: Not on right edge
    } else {
        switch(*currentCenter) {
        case 5 :
            display_pixel_set(BAR_COLUMN, 6, 0);
            display_pixel_set(BAR_COLUMN, 3, 1);
            break;
        case 4:
            display_pixel_set(BAR_COLUMN, 5, 0);
            display_pixel_set(BAR_COLUMN, 2, 1);
            break;
        case 3:
            display_pixel_set(BAR_COLUMN, 4, 0);
            display_pixel_set(BAR_COLUMN, 1, 1);
            break;
        case 2:
            display_pixel_set(BAR_COLUMN, 3, 0);
            display_pixel_set(BAR_COLUMN, 0, 1);
            break;
        }
    }

    return *currentCenter - 1;
}

/* Full bar movement,
   to be called in main, while(1)
*/
void bar_task(void)
{
    navswitch_update();
    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        currentCenter = go_left(&currentCenter);
    }
    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        currentCenter = go_right(&currentCenter);
    }
}



uint8_t start_game(uint8_t currentState)
{
    navswitch_update();
    if (currentState == 0) {
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 1;
    }
}

void start_routine(uint8_t currentState)
{
    //tinygl_init
    tinygl_init (3000);                                     //Replace in module
    tinygl_font_set(&font5x5_1);
    tinygl_text_speed_set(10);
    char* text = "Push Down";
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
    tinygl_text(text);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);

    while(currentState == 0) {
        currentState = start_game(currentState);
        tinygl_update();


    }
}


uint8_t release_routine(void)
{
    uint8_t releaseBall = 0;

    if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        releaseBall = 1;
    }

    return releaseBall;
}


