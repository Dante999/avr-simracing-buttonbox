
#include <util/delay.h>
#include <avr/interrupt.h>
#include "flipswitch.h"
#include "rotary_encoder.h"
#include "uart.h"
#include "event_handler.h"






static void init() {
    uart_init();
    flipswitch_init();
    encode_init();
}


int main(void) {

    init();
    uart_putsln("Initializing done...");

    sei();

    while(1) {
        event_handler();
    }

}
