#include <avr/io.h>
#include "uart.h"

void debug_print_header() {
    uart_putsln("Press a key for monitoring:");
    uart_putsln("[0] Flipswitches");
    uart_putsln("[1] Rotary Encoder (SW)");
    uart_putsln("[2] Rotary Encoder (ENC)");
}


void debug_flipswitch() {
    uart_putsln("Flipswitches: ");
    uart_puti(flipswitch_is_flipped(FLIP_SWITCH_5));
    uart_puti(flipswitch_is_flipped(FLIP_SWITCH_4));
    uart_puti(flipswitch_is_flipped(FLIP_SWITCH_3));
    uart_puti(flipswitch_is_flipped(FLIP_SWITCH_2));
    uart_puti(flipswitch_is_flipped(FLIP_SWITCH_1));
    uart_putsln("");
}


void debug_rotary_switch() {
    uart_putsln("Rotary Encoder (SW): ");
    uart_puti(encode_is_pressed(ROTARY_ENCODER_5);
    uart_puti(encode_is_pressed(ROTARY_ENCODER_4);
    uart_puti(encode_is_pressed(ROTARY_ENCODER_3);
    uart_puti(encode_is_pressed(ROTARY_ENCODER_2);
    uart_puti(encode_is_pressed(ROTARY_ENCODER_1);
    uart_putsln("");
}
    
    
void debug_rotary_encoder() {
    static int8_t delta = 0;
    
    delta += encode_read();
    
    uart_puti(encode_switch());
    uart_puts(" -> ");
    uart_puti(delta);
    uart_putc('\n');
}
