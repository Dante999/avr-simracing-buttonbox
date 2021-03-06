/*******************************************************************************
 *
 * File    : flipswitch.c
 *
 * Author  : Dante999
 * Date    : 28.12.2018
 *
 * Tabsize : 4
 * License : GNU GPL v2
 *
 * Reads the state of flipswitches (on/off)
 *
 * This module is designed to read the state of 5 flipswitches. Each flipswitch
 * can be read one by one.
 *
 ******************************************************************************/

#include <avr/io.h>
#include "flipswitch.h"

// mapping of Flipswitch 1
#define REG_DDR_SWITCH_1    DDRD
#define REG_PORT_SWITCH_1   PORTD
#define REG_PIN_SWITCH_1    PIND
#define BIT_SWITCH_1        (1<<PD7)

// mapping of Flipswitch 2
#define REG_DDR_SWITCH_2    DDRC
#define REG_PORT_SWITCH_2   PORTC
#define REG_PIN_SWITCH_2    PINC
#define BIT_SWITCH_2        (1<<PC5)

// mapping of Flipswitch 3
#define REG_DDR_SWITCH_3    DDRA
#define REG_PORT_SWITCH_3   PORTA
#define REG_PIN_SWITCH_3    PINA
#define BIT_SWITCH_3        (1<<PA6)

// mapping of Flipswitch 4
#define REG_DDR_SWITCH_4    DDRA
#define REG_PORT_SWITCH_4   PORTA
#define REG_PIN_SWITCH_4    PINA
#define BIT_SWITCH_4        (1<<PA2)

// mapping of Flipswitch 5
#define REG_DDR_SWITCH_5    DDRB
#define REG_PORT_SWITCH_5   PORTB
#define REG_PIN_SWITCH_5    PINB
#define BIT_SWITCH_5        (1<<PB1)



struct Flipswitch {
    uint8_t bit;
    volatile uint8_t *ddrx;
    volatile uint8_t *portx;
    volatile uint8_t *pinx;
};

static struct Flipswitch g_flipswitches[FLIP_SWITCH_MAX];


static void set_pinout() {
    g_flipswitches[FLIP_SWITCH_1].bit   = (1<<PD7);
    g_flipswitches[FLIP_SWITCH_1].ddrx  = &DDRD;
    g_flipswitches[FLIP_SWITCH_1].portx = &PORTD;
    g_flipswitches[FLIP_SWITCH_1].pinx  = &PIND;

    g_flipswitches[FLIP_SWITCH_2].bit   = (1<<PC5);
    g_flipswitches[FLIP_SWITCH_2].ddrx  = &DDRC;
    g_flipswitches[FLIP_SWITCH_2].portx = &PORTC;
    g_flipswitches[FLIP_SWITCH_2].pinx  = &PINC;

    g_flipswitches[FLIP_SWITCH_3].bit   = (1<<PA6);
    g_flipswitches[FLIP_SWITCH_3].ddrx  = &DDRA;
    g_flipswitches[FLIP_SWITCH_3].portx = &PORTA;
    g_flipswitches[FLIP_SWITCH_3].pinx  = &PINA;

    g_flipswitches[FLIP_SWITCH_4].bit   = (1<<PA2);
    g_flipswitches[FLIP_SWITCH_4].ddrx  = &DDRA;
    g_flipswitches[FLIP_SWITCH_4].portx = &PORTA;
    g_flipswitches[FLIP_SWITCH_4].pinx  = &PINA;

    g_flipswitches[FLIP_SWITCH_5].bit   = (1<<PB1);
    g_flipswitches[FLIP_SWITCH_5].ddrx  = &DDRB;
    g_flipswitches[FLIP_SWITCH_5].portx = &PORTB;
    g_flipswitches[FLIP_SWITCH_5].pinx  = &PINB;
}



/*******************************************************************************
 * @brief initializes the module
 *
 * @param  none
 *
 * @return none
 ******************************************************************************/
void flipswitch_init() {

    set_pinout();

    for(uint8_t i=0; i<FLIP_SWITCH_MAX; i++) {
        *g_flipswitches[i].ddrx &= ~(g_flipswitches[i].bit);
        *g_flipswitches[i].portx |=  (g_flipswitches[i].bit);
    }

//    REG_DDR_SWITCH_1   &= ~BIT_SWITCH_1;            // set pin as input
//    REG_PORT_SWITCH_1  |=  BIT_SWITCH_1;            // enable pullup

//    REG_DDR_SWITCH_2   &= ~BIT_SWITCH_2;            // set pin as input
//    REG_PORT_SWITCH_2  |=  BIT_SWITCH_2;            // enable pullup

//    REG_DDR_SWITCH_3   &= ~BIT_SWITCH_3;            // set pin as input
//    REG_PORT_SWITCH_3  |=  BIT_SWITCH_3;            // enable pullup

//    REG_DDR_SWITCH_4   &= ~BIT_SWITCH_4;            // set pin as input
//    REG_PORT_SWITCH_4  |=  BIT_SWITCH_4;            // enable pullup

//    REG_DDR_SWITCH_5   &= ~BIT_SWITCH_5;            // set pin as input
//    REG_PORT_SWITCH_5  |=  BIT_SWITCH_5;            // enable pullup
}


/*******************************************************************************
 * @brief  returns the state of the given flipswitch
 *
 * @param  flip_switch  the flipswitch which should be checked
 *
 * @return 0 -> the switch is set to off
 *         1 -> the switch is set to on
 *        -1 -> undefined flipswitch
 ******************************************************************************/
int8_t flipswitch_is_flipped(enum FLIPSWITCH flip_switch) {

   uint8_t state = -1;

   switch(flip_switch) {

       case FLIP_SWITCH_1:
            state = (REG_PIN_SWITCH_1 & BIT_SWITCH_1);
            break;

        case FLIP_SWITCH_2:
            state = (REG_PIN_SWITCH_2 & BIT_SWITCH_2);
            break;

        case FLIP_SWITCH_3:
            state = (REG_PIN_SWITCH_3 & BIT_SWITCH_3);
            break;

        case FLIP_SWITCH_4:
            state = (REG_PIN_SWITCH_4 & BIT_SWITCH_4);
            break;

        case FLIP_SWITCH_5:
            state = (REG_PIN_SWITCH_5 & BIT_SWITCH_5);
            break;

        default:
            return -1;
            break;

    }

    if(state) {
        return 0;
    }
    else {
        return 1;
    }

}

