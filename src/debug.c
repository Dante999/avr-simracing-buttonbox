#include <avr/io.h>


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
