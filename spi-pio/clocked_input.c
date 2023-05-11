#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "hardware/spi.h"
#include "clocked_input.pio.h"

// GPIO 4 for PIO data input, GPIO 5 for clock input:
#define PIO_INPUT_PIN_BASE 4

#define BUF_SIZE 8

void printbuf_simple(uint8_t buf[], size_t len) {
    for (int i = 0; i < len; ++i) {
            printf("%02x ", buf[i]);
    }

    putchar('\n');
}

int main()
{
    stdio_init_all();
    set_sys_clock_khz(131000, true); //overclocking to get a few more cycles

    PIO pio = pio0;
    uint offset = pio_add_program(pio, &clocked_input_program);
    uint sm = pio_claim_unused_sm(pio, true);
    clocked_input_program_init(pio, sm, offset, PIO_INPUT_PIN_BASE);

    uint8_t in_buf[BUF_SIZE];

    while (true)
    {
        for (int i = 0; i < BUF_SIZE; ++i)
        {
            in_buf[i] = pio_sm_get_blocking(pio, sm);
        }        
        printbuf_simple(in_buf, BUF_SIZE);
        
    }
}
