#include "pio.h"
#include "system.h"


int main (void)
{
    system_init ();

    while (1)
    {


        pio_config_set(LEDMAT_COL1_PIO, PIO_OUTPUT_HIGH);
        pio_config_set(LEDMAT_COL2_PIO, PIO_OUTPUT_HIGH);
        pio_config_set(LEDMAT_COL3_PIO, PIO_OUTPUT_HIGH);
        pio_config_set(LEDMAT_COL4_PIO, PIO_OUTPUT_HIGH);
        pio_config_set(LEDMAT_COL5_PIO, PIO_OUTPUT_HIGH);


        pio_config_set(LEDMAT_ROW1_PIO, PIO_OUTPUT_HIGH);
        pio_config_set(LEDMAT_ROW2_PIO, PIO_OUTPUT_HIGH);
        pio_config_set(LEDMAT_ROW3_PIO, PIO_OUTPUT_HIGH);
        pio_config_set(LEDMAT_ROW4_PIO, PIO_OUTPUT_HIGH);
        pio_config_set(LEDMAT_ROW5_PIO, PIO_OUTPUT_HIGH);
        pio_config_set(LEDMAT_ROW6_PIO, PIO_OUTPUT_HIGH);
        pio_config_set(LEDMAT_ROW7_PIO, PIO_OUTPUT_HIGH);


        pio_config_set(LEDMAT_ROW1_PIO, PIO_OUTPUT_LOW);

        pio_config_set(LEDMAT_COL1_PIO, PIO_OUTPUT_LOW);
        pio_config_set(LEDMAT_COL2_PIO, PIO_OUTPUT_LOW);

        pio_config_set(LEDMAT_COL3_PIO, PIO_OUTPUT_LOW);

        pio_config_set(LEDMAT_COL4_PIO, PIO_OUTPUT_LOW);

        pio_config_set(LEDMAT_COL5_PIO, PIO_OUTPUT_HIGH);





        /* TODO.  Use PIO module to turn on LEDs in
           LED matrix.  */

    }
}
