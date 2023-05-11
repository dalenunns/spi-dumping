#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"

#define BUF_LEN 128

void printbuf_simple(uint8_t buf[], size_t len)
{
    for (int i = 0; i < len; ++i)
    {
        printf("%02x ", buf[i]);
    }

    putchar('\n');
}

int main()
{
    // Enable UART so we can print
    stdio_init_all();

    // Enable SPI 0 at 1 MHz and connect to GPIOs
    spi_init(spi_default, 16000 * 1000);
    spi_set_slave(spi_default, true);
    spi_set_format(spi_default, 8, SPI_CPOL_0, SPI_CPHA_1, SPI_MSB_FIRST); // Changing CPHA to 1, essentially setting SPI to Mode1 gets better results even though this is "wrong"

    gpio_set_function(PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_CSN_PIN, GPIO_FUNC_SPI);
    // Make the SPI pins available to picotool
    bi_decl(bi_4pins_with_func(PICO_DEFAULT_SPI_RX_PIN, PICO_DEFAULT_SPI_TX_PIN, PICO_DEFAULT_SPI_SCK_PIN, PICO_DEFAULT_SPI_CSN_PIN, GPIO_FUNC_SPI));

    uint8_t in_buf[BUF_LEN];

    for (size_t i = 0;; ++i)
    {
        spi_read_blocking(spi_default, 0, in_buf, BUF_LEN);
        printbuf_simple(in_buf, BUF_LEN);
    }
}
