#include <avr/io.h>
#include "rotary_encoder.h"
#include "flipswitch.h"
#include "uart.h"

static void check_encoder_switches() {
    if(encode_is_pressed(ROTARY_ENCODER_1)) uart_putsln("ENC_1_SW");
    if(encode_is_pressed(ROTARY_ENCODER_2)) uart_putsln("ENC_2_SW");
    if(encode_is_pressed(ROTARY_ENCODER_3)) uart_putsln("ENC_3_SW");
    if(encode_is_pressed(ROTARY_ENCODER_4)) uart_putsln("ENC_4_SW");
    if(encode_is_pressed(ROTARY_ENCODER_5)) uart_putsln("ENC_5_SW");
}


static void print_encoder_ticks(char *name, int8_t value) {

    if( value != 0) {
        uart_puts(name);
        uart_putc('[');
        uart_puti(value);
        uart_putsln("]");
    }
}

static void check_encoder_ticks() {
    print_encoder_ticks("ENC1_TC", encode_read(ROTARY_ENCODER_1));
    print_encoder_ticks("ENC2_TC", encode_read(ROTARY_ENCODER_2));
    print_encoder_ticks("ENC3_TC", encode_read(ROTARY_ENCODER_3));
    print_encoder_ticks("ENC4_TC", encode_read(ROTARY_ENCODER_4));
    print_encoder_ticks("ENC5_TC", encode_read(ROTARY_ENCODER_5));
}

static void check_flip_switches() {
    if(flipswitch_is_flipped(FLIP_SWITCH_1)) uart_putsln("FLIPSWITCH_1");
    if(flipswitch_is_flipped(FLIP_SWITCH_2)) uart_putsln("FLIPSWITCH_2");
    if(flipswitch_is_flipped(FLIP_SWITCH_3)) uart_putsln("FLIPSWITCH_3");
    if(flipswitch_is_flipped(FLIP_SWITCH_4)) uart_putsln("FLIPSWITCH_4");
    if(flipswitch_is_flipped(FLIP_SWITCH_5)) uart_putsln("FLIPSWITCH_5");
}




void event_handler() {
    check_encoder_switches();
    check_encoder_ticks();
    check_flip_switches();
}


