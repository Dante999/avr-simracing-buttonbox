#include "rotary_encoder.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "util.h"


#define VAL_OCR     (F_CPU / 64.0 * 1e-3 - 0.5)

#define ROTARY_1_CW     (PIND & 1<<PD4)
#define ROTARY_1_CCW    (PIND & 1<<PD5)
#define ROTARY_1_SWITCH (PIND & 1<<PD6)

#define ROTARY_2_CW     (PINC & 1<<PC2)
#define ROTARY_2_CCW    (PINC & 1<<PC3)
#define ROTARY_2_SWITCH (PINC & 1<<PC4)

#define ROTARY_3_CW     (PINC & 1<<PC6)
#define ROTARY_3_CCW    (PINC & 1<<PC7)
#define ROTARY_3_SWITCH (PINA & 1<<PA7)

#define ROTARY_4_CW     (PINA & 1<<PA5)
#define ROTARY_4_CCW    (PINA & 1<<PA4)
#define ROTARY_4_SWITCH (PINA & 1<<PA3)

#define ROTARY_5_CW     (PINA & 1<<PA1)
#define ROTARY_5_CCW    (PINA & 1<<PA0)
#define ROTARY_5_SWITCH (PINB & 1<<PB0)

static int8_t calculate_delta( int8_t *last, uint8_t cw, uint8_t ccw );


volatile int8_t m_enc_delta;                        // -128 ... 127
static int8_t m_last;



void encode_init() {
    int8_t new = 0;

    if(ROTARY_1_CW)  new  = 3;
    if(ROTARY_1_CCW) new ^= 1;                      // convert gray to binary

    m_last = new;                                   // power on state
    m_enc_delta = 0;                                // reset delta steps

    TCCR0 = (1<<WGM01) | (1<<CS01) | (1<<CS00);     // CTC, prescaler 64
    OCR0 = (uint8_t) VAL_OCR;                       // 1ms
    TIMSK |= 1<<OCIE0;
    
}


static int8_t calculate_delta( int8_t *last, uint8_t cw, uint8_t ccw ) {

    int8_t new, diff;

    new = 0;
    if(cw)  new  = 3;
    if(ccw) new ^= 1;                               // convert gray to binary

    diff = *last - new;                             // difference m_last - new

    if( diff & 1 ) {                                // bit 0 = value (1)
        *last = new;                                // store new as next m_last
        return (diff & 2) - 1;                      // bit 1 = direction (+/-)
    }
    else {
        return 0;
    }

}


ISR( TIMER0_COMP_vect ) {
    m_enc_delta += calculate_delta(&m_last, ROTARY_1_CW, ROTARY_1_CCW);
}


int8_t encode_is_pressed(enum ROTARY_ENCODER rotary_encoder) {

    switch(rotary_encoder) {
        
        case ROTARY_ENCODER_1:
            return util_is_zero(ROTARY_1_SWITCH);
            break;
        
        case ROTARY_ENCODER_2:
            return util_is_zero(ROTARY_2_SWITCH);
            break;
        
        case ROTARY_ENCODER_3:
            return util_is_zero(ROTARY_3_SWITCH);
            break;
        
        case ROTARY_ENCODER_4:
            return util_is_zero(ROTARY_4_SWITCH);
            break;
        
        case ROTARY_ENCODER_5:
            return util_is_zero(ROTARY_5_SWITCH);
            break;
        
        default:
            return -1;
            break;
    }

}

int8_t encode_read(void) {
    int8_t val;

    cli();
    val = m_enc_delta;
    m_enc_delta = val & 3;
    sei();
    return val >> 2;
}
