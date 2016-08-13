/*
 * ps2_tables.h
 */
#ifndef __PS2_TABLES_H__
#define __PS2_TABLES_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

#define PS2_TO_HID_TABLE_SIZE 132

uint8_t ps2_to_hid(uint8_t scancode);
uint8_t ps2_to_hid_prefix_E0(uint8_t scancode);
uint8_t is_hid_modifier_key(uint8_t code, uint8_t *modifier, uint8_t press_flag);
uint8_t is_hid_modifier_key_E0(uint8_t code, uint8_t *modifier, uint8_t press_flag);

#endif /* __PS2_TABLES_H__ */
