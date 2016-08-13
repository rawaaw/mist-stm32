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

#define PS2_KBD_BUF_SIZE 4

/** Exported_Types		*/
typedef enum PS_KBD_STATE {
  PS2_KBD_NORMAL = 0,
  PS2_KBD_E0 = 1,
  PS2_KBD_BRK_WAIT_E0F07E = 2,
  PS2_KBD_E1 = 3,
  PS2_KBD_E1_WAIT_F077 = 4
} PS_KBD_STATE;


typedef union t_ps2_kbd_report {
  struct {
    struct {
      uint8_t gui_r:1;   /*Right GUI  */
      uint8_t alt_r:1;   /*Right Alt  */
      uint8_t shift_r:1; /*Right Shift*/
      uint8_t ctrl_r:1;  /*Right Ctrl */
      uint8_t gui_l:1;   /*Left GUI   */
      uint8_t alt_l:1;   /*Left Alt   */
      uint8_t shift_l:1; /*Left Shift */
      uint8_t ctrl_l:1;  /*Left Ctrl  */
    } modifier;
    uint8_t reserved;
    uint8_t key_arr[6];
  } key_rep;

  uint8_t key_rep_arr[8];
}t_ps2_kbd_report;

/** Exported_Functions	*/
void PS2_kbd_init(void);
uint8_t PS2_kbd_put_hid_buf(uint8_t modifier, uint8_t ch);
uint8_t PS2_kbd_get_hid_buf(uint8_t *modifier, uint8_t *ch);
t_ps2_kbd_report* PS2_kbd_get_hid_buf_entry(uint8_t buf_pos);
void PS2_kbd_interrupt(void);
void PS2_scancode_decode(uint8_t scancode);
void PS2_check_alive(void);
uint32_t PS2_GetCounter(void);
void PS2_IncCounter(void);

void ps2_set_kbd_led(unsigned char led, bool on);
int8_t ps2_keyboard_present(void);

#endif /* __PS2_H__ */
