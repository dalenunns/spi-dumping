# spi-dumping
Various attempts to dump SPI data using a Raspberry Pi Pico

### spi-pio

A modified version of the [Clocked Input Example](https://github.com/raspberrypi/pico-examples/tree/master/pio/clocked_input) code. This has been changed to clocked the data in and export it over USB Serial in 8 byte blocks.

This works well for my purposes however its still occasionally looses bytes or gets confused.

### spi-snoop

This uses the SPI hardware in the RP2040 in SPI Slave mode to listen to the data on the SPI bus and dump the data in 128 byte blocks over USB Serial. This doesn't work as well as the `spi-pio` but still catches some of the traffic.
