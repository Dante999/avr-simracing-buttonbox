#include <avr/io.h>

#ifndef UART_H_
#define UART_H_

    extern void uart_init();
    extern void uart_putc(char c);
    extern void uart_puts(char *s);
    extern void uart_puti(uint8_t i);
#endif
