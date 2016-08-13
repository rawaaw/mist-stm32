/*
* used code:
* http://hackaday.com/2010/11/08/czech-discovery-ressurects-ps2-keyboard/
*/
#include <string.h>
#include "ps2.h"
#include "ps2_tables.h"

static uint32_t s_PS2_Tick = 0;
static uint8_t bits_count = 11;
static uint32_t num_PS2_interrupt;
static uint8_t received_char;

static t_ps2_kbd_report ps2_kbd_buf[PS2_KBD_BUF_SIZE] = {0};
static volatile uint8_t ps2_kbd_rd_pos  = 0;
static volatile uint8_t ps2_kbd_wr_pos = 0;
static volatile PS_KBD_STATE ps2_kbd_state = PS2_KBD_NORMAL;
static volatile uint8_t ps2_kbd_prev_scancode = 0;
static volatile uint8_t ps2_kbd_modifier = 0;


/**
  * @brief  PS2 Keyboard interface initialization
  * @param  none
  * @retval : none
  */
void PS2_kbd_init(void){
  ps2_kbd_rd_pos  = 0;
  ps2_kbd_wr_pos = 0;
  ps2_kbd_state = PS2_KBD_NORMAL;
  ps2_kbd_prev_scancode = 0;
  ps2_kbd_modifier = 0;
  memset(&ps2_kbd_buf, 0, sizeof(ps2_kbd_buf));
  return;
}


/**
  * @brief  Inserting decoding character in the ring buffer
  * @param  IN: HID modifier, IN: HID Scancode
  * @retval : 0 - buffer overflow; 1 - write success
  */
uint8_t PS2_kbd_put_hid_buf(uint8_t modifier, uint8_t ch)
{
  ps2_kbd_rd_pos  = 0;
  ps2_kbd_wr_pos = 0;

  if (ps2_kbd_wr_pos < (PS2_KBD_BUF_SIZE - 1)){
    if (ps2_kbd_wr_pos + 1 == ps2_kbd_rd_pos){ /* buffer overflow */
      return 0;
    }
    ps2_kbd_wr_pos ++;
    ps2_kbd_buf[ps2_kbd_wr_pos].key_rep_arr[0] = modifier;
    ps2_kbd_buf[ps2_kbd_wr_pos].key_rep.key_arr[0] = ch;
  }else{
    if (ps2_kbd_rd_pos == 0){ /* buffer overflow */
      return 0;
    }
    ps2_kbd_wr_pos = 0;
    ps2_kbd_buf[ps2_kbd_wr_pos].key_rep_arr[0] = modifier;
    ps2_kbd_buf[ps2_kbd_wr_pos].key_rep.key_arr[0] = ch;
  }
  return 1;
}

/**
  * @brief  Reading from the ring buffer
  * @param  OUT: HID modifier, OUT: HID scancode
  * @retval : 1 - read success; 0 - buffer empty
  */
uint8_t PS2_kbd_get_hid_buf(uint8_t *modifier, uint8_t *ch) {
  if (ps2_kbd_rd_pos == ps2_kbd_wr_pos){
    return 0xFF; /* buffer empty */
  }
  if (ps2_kbd_rd_pos < (PS2_KBD_BUF_SIZE - 1)){
    ps2_kbd_rd_pos ++;
  }else{
    ps2_kbd_rd_pos = 0;
  }
  *modifier = ps2_kbd_buf[ps2_kbd_rd_pos].key_rep_arr[0];
  *ch = ps2_kbd_buf[ps2_kbd_rd_pos].key_rep.key_arr[0];
  return ps2_kbd_rd_pos;
}


/**
  * @brief  Reading from the ring buffer
  * @param  IN:  buffer position
  * @retval : t_ps_kbd_report*
  */
t_ps2_kbd_report* PS2_kbd_get_hid_buf_entry(uint8_t buf_pos) {
  if (buf_pos < PS2_KBD_BUF_SIZE)
    return &ps2_kbd_buf[buf_pos];
  else
    return NULL;
}


/**
* @brief  Any switch clock with low to high queried this interruption
* @param  None
* @retval : None
*/

void PS2_kbd_interrupt(void)
{
  GPIO_PinState data_pin_state;

  num_PS2_interrupt = PS2_GetCounter();

  data_pin_state =  HAL_GPIO_ReadPin(PS2_KBD_DATA_GPIO_Port, PS2_KBD_DATA_Pin);
  if (bits_count == 11) { /* start bit must be LOW */
    received_char = 0x00;
    if (data_pin_state == 0) {
      bits_count --;
    }
  } else {
    if (bits_count < 11 && bits_count > 2) { /* data bits */
    	received_char = (received_char >> 1);
    	if (data_pin_state)
    	  received_char = received_char | 0x80;
    	bits_count --;
    } else { /* stop bit */
    	if (--bits_count == 0) { /* all bits received. */
          PS2_scancode_decode(received_char);
          bits_count = 11;
    	}
    }
  }

  return;
}


/**
  * @brief  Decoding scan key code to the appropriate character
  * @param  Scan keycode
  * @retval : None
  */
void PS2_scancode_decode(uint8_t scancode)
{
  switch (ps2_kbd_state){
    case PS2_KBD_NORMAL:
      if (scancode == 0xE0){
        ps2_kbd_state = PS2_KBD_E0;
        return;
      }
      if (scancode == 0xE1){
        ps2_kbd_state = PS2_KBD_E1;
        return;
      }

      if (scancode != 0xF0){
        if (is_hid_modifier_key(scancode, &ps2_kbd_modifier, (ps2_kbd_prev_scancode != 0xF0))){
          PS2_kbd_put_hid_buf(ps2_kbd_modifier, 0x00); /* modifier key state changed */
        }else{
          if (ps2_kbd_prev_scancode == 0xF0){             /* key released */
            PS2_kbd_put_hid_buf(ps2_kbd_modifier, 0x00); 
          }else{                                          /* key pressed */
            PS2_kbd_put_hid_buf(ps2_kbd_modifier, ps2_to_hid(scancode));
          }
        }
      }
      ps2_kbd_prev_scancode = scancode;
    break;

    case PS2_KBD_E0:
      if (scancode == 0x7E){
        ps2_kbd_prev_scancode = scancode;
        ps2_kbd_state = PS2_KBD_BRK_WAIT_E0F07E;
        return;
      }
      if (scancode == 0xE1){
        ps2_kbd_prev_scancode = scancode;
        ps2_kbd_state = PS2_KBD_E1;
        return;
      }

      if (scancode != 0xF0){
        if (is_hid_modifier_key_E0(scancode, &ps2_kbd_modifier, (ps2_kbd_prev_scancode != 0xF0))){
          PS2_kbd_put_hid_buf(ps2_kbd_modifier, 0x00); /* modifier key state changed */
        }else{
          if (ps2_kbd_prev_scancode == 0xF0){             /* key released */
            PS2_kbd_put_hid_buf(ps2_kbd_modifier, 0x00); 
          }else{                                          /* key pressed */
            PS2_kbd_put_hid_buf(ps2_kbd_modifier, ps2_to_hid_prefix_E0(scancode));
          }
        }
        ps2_kbd_state = PS2_KBD_NORMAL;
      }
      ps2_kbd_prev_scancode = scancode;
    break;

    case PS2_KBD_BRK_WAIT_E0F07E:
      if (scancode == 0x7E){
        ps2_kbd_state = PS2_KBD_NORMAL;
      }
    break;

    case PS2_KBD_E1: /*E1 14 77 _E1_ F0 14 F0 77*/
      if (scancode == 0xE1){
        ps2_kbd_state = PS2_KBD_E1_WAIT_F077;
      }
    break;

    case PS2_KBD_E1_WAIT_F077: /*E1 14 77 E1 F0 14 _F0 77_*/
      if (scancode == 0x77){
        ps2_kbd_state = PS2_KBD_NORMAL;
      }
    break;

    default:
    break;
  }


}


/**
  * @brief  Check whether the keyboard is stuck
  * @param  None
  * @retval : None
  */
void PS2_check_alive(void)
{
  __IO uint32_t delta;
  if (bits_count != 11)	{
    delta = PS2_GetCounter();
    if (delta < num_PS2_interrupt)	{
      delta = (0xFFFFFFFF - num_PS2_interrupt) + delta;
    } else {
      delta = delta - num_PS2_interrupt;
    }
    if (delta > 2) {  /* 2 ms to send another bit !! */
      bits_count = 11;/* We try to wait for a new character */
    }
  }
  return;
}

/**
  * @brief  get PS2 watchdog counter
  * @param  None
  * @retval : None
  */
uint32_t PS2_GetCounter(void){
  return s_PS2_Tick;
}

/**
  * @brief  increment PS2 watchdog counter
  * @param  None
  * @retval : None
  */
void PS2_IncCounter(void){
  s_PS2_Tick ++;
}

/*********************/

void ps2_set_kbd_led(unsigned char led, bool on){
  return;
}


int8_t ps2_keyboard_present(void){
  return 0;
}
