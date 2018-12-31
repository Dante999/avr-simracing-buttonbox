#ifndef ROTARY_ENCODER_H_
#define ROTARY_ENCODER_H_

#include <avr/io.h>

enum ROTARY_ENCODER {
    ROTARY_ENCODER_1,
    ROTARY_ENCODER_2,
    ROTARY_ENCODER_3,
    ROTARY_ENCODER_4,
    ROTARY_ENCODER_5,
};

extern void encode_init(void);
extern int8_t encode_read(void);
extern int8_t encode_is_pressed(enum ROTARY_ENCODER rotary_encoder);
#endif
