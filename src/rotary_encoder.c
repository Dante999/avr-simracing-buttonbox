#include "rotary_encoder.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "util.h"


#define VAL_OCR     (F_CPU / 64.0 * 1e-3 - 0.5)

#define DEBOUNCE_CYCLE 100


struct Encoder {
    volatile uint8_t *pinx_cw;
    volatile uint8_t *pinx_ccw;
    volatile uint8_t *pinx_sw;
    uint8_t bit_cw;
    uint8_t bit_ccw;
    uint8_t bit_sw;
    int8_t last;
    volatile int8_t delta;
    volatile int8_t switch_pressed;
};

static struct Encoder g_encoders[ROTARY_ENCODER_MAX];


static void set_initial_state(struct Encoder *pencoder) {

    int8_t new = 0;

    if( *pencoder->pinx_cw  & pencoder->bit_cw ) new  = 3;
    if( *pencoder->pinx_ccw & pencoder->bit_ccw) new ^= 1;

    pencoder->last = new;
    pencoder->delta = 0;
}



static void set_pinout() {
    g_encoders[ROTARY_ENCODER_1].bit_cw   = (1<<PD4);
    g_encoders[ROTARY_ENCODER_1].bit_ccw  = (1<<PD5);
    g_encoders[ROTARY_ENCODER_1].bit_sw   = (1<<PD6);
    g_encoders[ROTARY_ENCODER_1].pinx_cw  = &PIND;
    g_encoders[ROTARY_ENCODER_1].pinx_ccw = &PIND;
    g_encoders[ROTARY_ENCODER_1].pinx_sw  = &PIND;

    g_encoders[ROTARY_ENCODER_2].bit_cw   = (1<<PC2);
    g_encoders[ROTARY_ENCODER_2].bit_ccw  = (1<<PC3);
    g_encoders[ROTARY_ENCODER_2].bit_sw   = (1<<PC4);
    g_encoders[ROTARY_ENCODER_2].pinx_cw  = &PINC;
    g_encoders[ROTARY_ENCODER_2].pinx_ccw = &PINC;
    g_encoders[ROTARY_ENCODER_2].pinx_sw  = &PINC;

    g_encoders[ROTARY_ENCODER_3].bit_cw   = (1<<PC6);
    g_encoders[ROTARY_ENCODER_3].bit_ccw  = (1<<PC7);
    g_encoders[ROTARY_ENCODER_3].bit_sw   = (1<<PA7);
    g_encoders[ROTARY_ENCODER_3].pinx_cw  = &PINC;
    g_encoders[ROTARY_ENCODER_3].pinx_ccw = &PINC;
    g_encoders[ROTARY_ENCODER_3].pinx_sw  = &PINA;

    g_encoders[ROTARY_ENCODER_4].bit_cw   = (1<<PA5);
    g_encoders[ROTARY_ENCODER_4].bit_ccw  = (1<<PA4);
    g_encoders[ROTARY_ENCODER_4].bit_sw   = (1<<PA3);
    g_encoders[ROTARY_ENCODER_4].pinx_cw  = &PINA;
    g_encoders[ROTARY_ENCODER_4].pinx_ccw = &PINA;
    g_encoders[ROTARY_ENCODER_4].pinx_sw  = &PINA;

    g_encoders[ROTARY_ENCODER_5].bit_cw   = (1<<PA1);
    g_encoders[ROTARY_ENCODER_5].bit_ccw  = (1<<PA0);
    g_encoders[ROTARY_ENCODER_5].bit_sw   = (1<<PB0);
    g_encoders[ROTARY_ENCODER_5].pinx_cw  = &PINA;
    g_encoders[ROTARY_ENCODER_5].pinx_ccw = &PINA;
    g_encoders[ROTARY_ENCODER_5].pinx_sw  = &PINB;
}


void encode_init() {

    set_pinout();

    for( uint8_t i=0; i<ROTARY_ENCODER_MAX; i++) {
        set_initial_state(&g_encoders[i]);
    }

    TCCR0 = (1<<WGM01) | (1<<CS01) | (1<<CS00);     // CTC, prescaler 64
    OCR0 = (uint8_t) VAL_OCR;                       // 1ms
    TIMSK |= 1<<OCIE0;
}



static void check_movement(struct Encoder *pencoder) {

    int8_t new, diff;

    new = 0;

    if( *pencoder->pinx_cw  & pencoder->bit_cw ) new  = 3;
    if( *pencoder->pinx_ccw & pencoder->bit_ccw) new ^= 1;

    diff = pencoder->last - new;              // difference last - new
    if( diff & 1 ) {                        // bit 0 = value (1)
        pencoder->last = new;                 // store new as next last
        pencoder->delta += (diff & 2) - 1;    // bit 1 = direction (+/-)
    }

}




static void check_switches(struct Encoder *pencoder) {

    if( *pencoder->pinx_sw & pencoder->bit_sw ) {
        pencoder->switch_pressed = 0;
    }
    else {
        pencoder->switch_pressed = 1;
    }

}


ISR( TIMER0_COMP_vect ) {

    static uint8_t counter = 0;

    counter++;

    for( uint8_t i=0; i<ROTARY_ENCODER_MAX; i++) {
        check_movement(&g_encoders[i]);

        if( counter%DEBOUNCE_CYCLE == 0 ) {
            check_switches(&g_encoders[i]);
        }

    }


}


/*******************************************************************************
 * @brief  returns the state of the given rotary encoder switch
 *
 * The encoder switch is used in combination with an pullup resistor. Unpressed
 * the voltage level on the switch is 'high'. So when the switch is pressed,
 * the voltage level will drop to 'low'.
 *
 * @param  flip_switch  the flipswitch which should be checked
 *
 * @return 0 -> the switch is unpressed
 *         1 -> the switch is pressed
 *        -1 -> undefined switch given
 ******************************************************************************/
int8_t encode_is_pressed(enum ROTARY_ENCODER rotary_encoder) {
    return g_encoders[rotary_encoder].switch_pressed;
}



int8_t encode_read(enum ROTARY_ENCODER rotary_encoder) {

    int8_t val;

    cli();
    val = g_encoders[rotary_encoder].delta;
    g_encoders[rotary_encoder].delta = val & 3;
    sei();
    return val >> 2;
}
