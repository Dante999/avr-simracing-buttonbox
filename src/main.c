
#include <util/delay.h>
#include <avr/interrupt.h>
#include "rotary_encoder.h"
#include "uart.h"
#include "flipswitch.h"


void debug_flipswitch() {

    uart_puti(flipswitch_read(FLIP_SWITCH_1));
    uart_puti(flipswitch_read(FLIP_SWITCH_2));
    uart_puti(flipswitch_read(FLIP_SWITCH_3));
    uart_puti(flipswitch_read(FLIP_SWITCH_4));
    uart_puti(flipswitch_read(FLIP_SWITCH_5));
    uart_putc('\n');

}

void debug_rotary_encoder() {
    static int8_t delta = 0;
    
    delta += encode_read();
    
    uart_puti(encode_switch());
    uart_puts(" -> ");
    uart_puti(delta);
    uart_putc('\n');
}


void init() {
    uart_init();
    flipswitch_init();
    encode_init();
}


int main(void) {

    init();

    uart_puts("Initializing done...\n");

    //usbInit();
    sei();

    while(1) {

      //  usbPoll();

        _delay_ms(100);        
        debug_rotary_encoder();
    }

}
