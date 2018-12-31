#include <avr/io.h>

#ifndef UTIL_H_
#define UTIL_H_

    uint8_t util_is_bit_set(uint8_t byte, uint8_t bit_mask);
    uint8_t util_not_zero(uint8_t byte);
    uint8_t util_is_zero(uint8_t byte);
    
#endif
