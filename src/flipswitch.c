/*
 * flipswitch.c
 * 
 * Copyright 2018 Dante999 <dante999@dante999-MS-7A71>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <avr/io.h>
#include "flipswitch.h"

#define REG_DDR_SWITCH_1    DDRD
#define REG_PORT_SWITCH_1   PORTD
#define REG_PIN_SWITCH_1    PIND
#define BIT_SWITCH_1        (1<<PD7)

#define REG_DDR_SWITCH_2    DDRC
#define REG_PORT_SWITCH_2   PORTC
#define REG_PIN_SWITCH_2    PINC
#define BIT_SWITCH_2        (1<<PC5)

#define REG_DDR_SWITCH_3    DDRA
#define REG_PORT_SWITCH_3   PORTA
#define REG_PIN_SWITCH_3    PINA
#define BIT_SWITCH_3        (1<<PA6)

#define REG_DDR_SWITCH_4    DDRA
#define REG_PORT_SWITCH_4   PORTA
#define REG_PIN_SWITCH_4    PINA
#define BIT_SWITCH_4        (1<<PA2)

#define REG_DDR_SWITCH_5    DDRB
#define REG_PORT_SWITCH_5   PORTB
#define REG_PIN_SWITCH_5    PINB
#define BIT_SWITCH_5        (1<<PB1)






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


uint8_t is_set(uint8_t byte, uint8_t bit_mask) {
    
    if( (byte & bit_mask) != 0) {
        return 1;
    }
    else {
        return 0;
    }
    
}
    
    
    
uint8_t flipswitch_read(enum FLIPSWITCH flip_switch) {


   switch(flip_switch) {

       case FLIP_SWITCH_1:        
            return is_set(REG_PIN_SWITCH_1, BIT_SWITCH_1);
            break;
        case FLIP_SWITCH_2:
            return is_set(REG_PIN_SWITCH_2, BIT_SWITCH_2);
            break;
        case FLIP_SWITCH_3:
            return is_set(REG_PIN_SWITCH_3, BIT_SWITCH_3);
            break;
        case FLIP_SWITCH_4:
            return is_set(REG_PIN_SWITCH_4, BIT_SWITCH_4);
            break;
        case FLIP_SWITCH_5:
            return is_set(REG_PIN_SWITCH_5, BIT_SWITCH_5);
            break;
    }
    
    return -1;

}
