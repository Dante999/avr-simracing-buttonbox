
#include "uart.h"
#include <stdio.h>

#ifndef F_CPU
    #error F_CPU is not defined!! 
#endif



#define BAUD 9600UL      // Baudrate

// Berechnungen
#define UBRR_VAL    ((F_CPU+BAUD*8)/(BAUD*16)-1)    // clever runden
#define BAUD_REAL   (F_CPU/(16*(UBRR_VAL+1)))       // Reale Baudrate
#define BAUD_ERROR  ((BAUD_REAL*1000)/BAUD)         // Fehler in Promille, 1000 = kein Fehler.

#if ((BAUD_ERROR<990) || (BAUD_ERROR>1010))
    #error Systematischer Fehler der Baudrate grösser 1% und damit zu hoch! 
#endif


void uart_init() {
    UBRRH = UBRR_VAL >> 8;
    UBRRL = UBRR_VAL & 0xFF;

    UCSRB |= (1<<TXEN);                         // enable UART TX
    UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);   // Asynchron 8N1 
}


void uart_putc(char c) {

    while (!(UCSRA & (1<<UDRE)))
    {
        // waiting until sender is free...
    }                             

    UDR = c;                                    // save character for sending
}

void uart_puti(uint8_t i) {
    
    char buffer[4];
    
    sprintf(buffer, "%d", i);
    
    uart_puts(buffer);
    /*
    
    if(0 <= i && i <= 9) {
        uart_putc((char) i+48);    
    }
    else {
        uart_puts("#uart_puti_fail");
    }
    */
}

void uart_puts(char *s) {

    while(*s != '\0') {
        uart_putc(*s);
        s++;
    }

}









