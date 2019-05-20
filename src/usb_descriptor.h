#ifndef USB_DESCRIPTOR_H
#define USB_DESCRIPTOR_H

#define MASK0_ENCODER1_LEFT     (1<<0)
#define MASK0_ENCODER1_BUTTON   (1<<1)
#define MASK0_ENCODER1_RIGHT    (1<<2)
#define MASK0_ENCODER2_LEFT     (1<<3)
#define MASK0_ENCODER2_BUTTON   (1<<4)
#define MASK0_ENCODER2_RIGHT    (1<<5)
#define MASK0_BUTTON01          (1<<6)
#define MASK0_BUTTON02          (1<<7)

#define MASK1_ENCODER3_LEFT     (1<<0)
#define MASK1_ENCODER3_BUTTON   (1<<1)
#define MASK1_ENCODER3_RIGHT    (1<<2)
#define MASK1_ENCODER4_LEFT     (1<<3)
#define MASK1_ENCODER4_BUTTON   (1<<4)
#define MASK1_ENCODER4_RIGHT    (1<<5)
#define MASK1_BUTTON03          (1<<6)
#define MASK1_BUTTON04          (1<<7)

#define MASK2_ENCODER5_LEFT     (1<<0)
#define MASK2_ENCODER5_BUTTON   (1<<1)
#define MASK2_ENCODER5_RIGHT    (1<<2)
#define MASK2_BUTTON05          (1<<3)
#define MASK2_BUTTON06          (1<<4)
#define MASK2_BUTTON07          (1<<5)
#define MASK2_BUTTON08          (1<<6)
#define MASK2_BUTTON09          (1<<7)

#define MASK3_BUTTON10          (1<<0)
#define MASK3_SWITCH01          (1<<1)
#define MASK3_SWITCH02          (1<<2)
#define MASK3_SWITCH03          (1<<3)
#define MASK3_SWITCH04          (1<<4)
#define MASK3_SWITCH05          (1<<5)

/**
 * @brief The usb_report struct
 *
 * button mask for 32 button gamepads
 *
 */
struct usb_report {
    uint8_t button_mask0;
    uint8_t button_mask1;
    uint8_t button_mask2;
    uint8_t button_mask3;
}

#endif // USB_DESCRIPTOR_H
