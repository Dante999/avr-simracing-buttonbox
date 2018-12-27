
#include <util/delay.h>
#include <avr/interrupt.h>
#include "rotary_encoder.h"
#include "uart.h"
#include "flipswitch.h"





void init() {
    uart_init();
    flipswitch_init();
    encode_init();
}


int main(void) {

    init();

    uart_puts("Initializing done...\n");

    
    sei();

    while(1) {
        //nothing to do
    }

}
