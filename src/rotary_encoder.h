#ifndef ROTARY_ENCODER_H_
#define ROTARY_ENCODER_H_

#include <avr/io.h>

#define ROTARY_DEFAULT 0
#define ROTARY_PRESSED 1
#define ROTARY_HOLD 2
#define ROTARY_RELEASED 3



enum ROTARY_ENCODER {
    ROTARY_ENCODER_1,
    ROTARY_ENCODER_2,
    ROTARY_ENCODER_3,
    ROTARY_ENCODER_4,
    ROTARY_ENCODER_5,
    // ---------------
    ROTARY_ENCODER_MAX
};

extern void encode_init(void);
extern int8_t encode_read(enum ROTARY_ENCODER rotary_encoder);
extern int8_t encode_is_pressed(enum ROTARY_ENCODER rotary_encoder);
#endif
