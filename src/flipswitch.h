/*******************************************************************************
 * 
 * File    : flipswitch.h
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

#ifndef FLIPSWITCH_H_
#define FLIPSWITCH_H_

// Enumartion of all available flipswitches
enum FLIPSWITCH {
    FLIP_SWITCH_1,
    FLIP_SWITCH_2,
    FLIP_SWITCH_3,
    FLIP_SWITCH_4,
    FLIP_SWITCH_5    
};

extern void flipswitch_init();
extern uint8_t flipswitch_read(enum FLIPSWITCH flip_switch);


#endif
