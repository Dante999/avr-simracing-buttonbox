#ifndef FLIPSWITCH_H_
#define FLIPSWITCH_H_


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
