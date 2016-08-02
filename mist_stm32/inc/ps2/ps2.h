/*
 * ps2.h
 *
 *  Created on: Oct 28, 2010
 *      Author: User
 */
#ifndef __PS2_H__
#define __PS2_H__

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include "stm32f4xx_hal.h"

uint32_t PS2_GetCounter(void);
void PS2_IncCounter(void);

/** Exported_Types		*/
/** Exported_Functions	*/
void PS2_Initialize(void);
void PS2_Kbd_Interrupt(void);
uint8_t PS2_keyboard_getchar(void);
void PS2_scancode_decode(uint8_t scan);
void PS2_put_to_buff(uint8_t ch);
void PS2_check_alive(void);

#define	PS2_BUFSIZE		16


void ps2_set_kbd_led(unsigned char led, bool on);
int8_t ps2_keyboard_present(void);


#endif /* __PS2_H__ */
