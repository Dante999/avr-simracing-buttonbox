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

// static functions
static uint8_t _is_bit_set(uint8_t byte, uint8_t bit_mask);


/*******************************************************************************
 * @brief  checks if the masked bit is set in the given byte
 * 
 * @param  byte         the byte which should be checked
 * @param  bit_mask     the bit-mask 
 *
 * @return  0 -> the bit is not set
 *          1 -> the bit is set
 ******************************************************************************/
uint8_t _is_bit_set(uint8_t byte, uint8_t bit_mask) {
    
    if( (byte & bit_mask) != 0) {
        return 1;
    }
    else {
        return 0;
    }
    
}


/*******************************************************************************
 * @brief initializes the module 
 * 
 * @param  none
 *
 * @return none
 ******************************************************************************/
void flipswitch_init() {
    REG_DDR_SWITCH_1   &= ~BIT_SWITCH_1;            // set pin as input
    REG_PORT_SWITCH_1  |=  BIT_SWITCH_1;            // enable pullup
    
    REG_DDR_SWITCH_2   &= ~BIT_SWITCH_2;            // set pin as input
    REG_PORT_SWITCH_2  |=  BIT_SWITCH_2;            // enable pullup    
    
    REG_DDR_SWITCH_3   &= ~BIT_SWITCH_3;            // set pin as input
    REG_PORT_SWITCH_3  |=  BIT_SWITCH_3;            // enable pullup
    
    REG_DDR_SWITCH_4   &= ~BIT_SWITCH_4;            // set pin as input
    REG_PORT_SWITCH_4  |=  BIT_SWITCH_4;            // enable pullup
    
    REG_DDR_SWITCH_5   &= ~BIT_SWITCH_5;            // set pin as input
    REG_PORT_SWITCH_5  |=  BIT_SWITCH_5;            // enable pullup
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
uint8_t flipswitch_read(enum FLIPSWITCH flip_switch) {


   switch(flip_switch) {

       case FLIP_SWITCH_1:        
            return _is_bit_set(REG_PIN_SWITCH_1, BIT_SWITCH_1);
            break;
        case FLIP_SWITCH_2:
            return _is_bit_set(REG_PIN_SWITCH_2, BIT_SWITCH_2);
            break;
        case FLIP_SWITCH_3:
            return _is_bit_set(REG_PIN_SWITCH_3, BIT_SWITCH_3);
            break;
        case FLIP_SWITCH_4:
            return _is_bit_set(REG_PIN_SWITCH_4, BIT_SWITCH_4);
            break;
        case FLIP_SWITCH_5:
            return _is_bit_set(REG_PIN_SWITCH_5, BIT_SWITCH_5);
            break;
    }
    
    return -1;
}


