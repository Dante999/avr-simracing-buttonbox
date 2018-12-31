#include "util.h"
/*******************************************************************************
 * @brief  checks if the masked bit is set in the given byte
 * 
 * @param  byte         the byte which should be checked
 * @param  bit_mask     the bit-mask 
 *
 * @return  0 -> the bit is not set
 *          1 -> the bit is set
 ******************************************************************************/
uint8_t util_is_bit_set(uint8_t byte, uint8_t bit_mask) {
    return util_not_zero(byte & bit_mask);
}

uint8_t util_not_zero(uint8_t byte) {

    if( byte != 0 )  {
        return 1;
    }
    else {
        return 0;
    }
    
}

uint8_t util_is_zero(uint8_t byte) {
    
    if( byte == 0 ) {
        return 1;
    }
    else {
        return 0;
    }
}
