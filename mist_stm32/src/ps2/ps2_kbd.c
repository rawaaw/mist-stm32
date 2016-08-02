/*
* used code:
* http://hackaday.com/2010/11/08/czech-discovery-ressurects-ps2-keyboard/
*/
#include "ps2.h"

static uint32_t s_PS2_Tick = 0;


static uint8_t bits_count = 11;
static uint32_t num_PS2_interrupt;
static uint8_t received_char;

/** Private_Variables		*/
volatile uint8_t	buffer_pointer = 0;
volatile uint8_t	buffer[PS2_BUFSIZE];
volatile uint16_t	status = 0;

// Lookup Table for normal scan code is pressed
const uint8_t normal_scancodes[] = {
	0x0d,9,
	0x0e,'|',
	0x15,'q',
	0x16,'1',
	0x1a,'z',
	0x1b,'s',
	0x1c,'a',
	0x1d,'w',
	0x1e,'2',
	0x21,'c',
	0x22,'x',
	0x23,'d',
	0x24,'e',
	0x25,'4',
	0x26,'3',
	0x29,' ',
	0x2a,'v',
	0x2b,'f',
	0x2c,'t',
	0x2d,'r',
	0x2e,'5',
	0x31,'n',
	0x32,'b',
	0x33,'h',
	0x34,'g',
	0x35,'y',
	0x36,'6',
	0x39,',',
	0x3a,'m',
	0x3b,'j',
	0x3c,'u',
	0x3d,'7',
	0x3e,'8',
	0x41,',',
	0x42,'k',
	0x43,'i',
	0x44,'o',
	0x45,'0',
	0x46,'9',
	0x49,'.',
	0x4a,'-',
	0x4b,'l',
	0x4c,'ø',
	0x4d,'p',
	0x4e,'+',
	0x55,'\\',
	0x5a,13,
	0x5b,'¨',
	0x5d,'\'',
	0x61,'<',
	0x66,8,
	0x69,'1',
	0x6b,'4',
	0x6c,'7',
	0x70,'0',
	0x71,',',
	0x72,'2',
	0x73,'5',
	0x74,'6',
	0x75,'8',
	0x79,'+',
	0x7a,'3',
	0x7b,'-',
	0x7c,'*',
	0x7d,'9',
	0,0
};

// Lookup table for the scan code is pressed shift
const uint8_t shift_scancodes[] = {
	0x0d,9,
	0x0e,'§',
	0x15,'Q',
	0x16,'!',
	0x1a,'Z',
	0x1b,'S',
	0x1c,'A',
	0x1d,'W',
	0x1e,'"',
	0x21,'C',
	0x22,'X',
	0x23,'D',
	0x24,'E',
	0x25,'¤',
	0x26,'#',
	0x29,' ',
	0x2a,'V',
	0x2b,'F',
	0x2c,'T',
	0x2d,'R',
	0x2e,'%',
	0x31,'N',
	0x32,'B',
	0x33,'H',
	0x34,'G',
	0x35,'Y',
	0x36,'&',
	0x39,'L',
	0x3a,'M',
	0x3b,'J',
	0x3c,'U',
	0x3d,'/',
	0x3e,'(',
	0x41,';',
	0x42,'K',
	0x43,'I',
	0x44,'O',
	0x45,'=',
	0x46,')',
	0x49,':',
	0x4a,'_',
	0x4b,'L',
	0x4d,'P',
	0x4e,'?',
	0x55,'`',
	0x5a,13,
	0x5b,'^',
	0x5d,'*',
	0x61,'>',
	0x66,8,
	0x69,'1',
	0x6b,'4',
	0x6c,'7',
	0x70,'0',
	0x71,',',
	0x72,'2',
	0x73,'5',
	0x74,'6',
	0x75,'8',
	0x79,'+',
	0x7a,'3',
	0x7b,'-',
	0x7c,'*',
	0x7d,'9',
	0,0
};


/**
* @brief  Any switch clock with low to high queried this interruption
* @param  None
* @retval : None
*/

void PS2_Kbd_Interrupt(void)
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
void PS2_scancode_decode(uint8_t scan)
{
  static uint8_t is_up = 0, shift = 0;
  uint8_t i;

  if (!is_up) {
    switch (scan) {
      case 0xF0 :        // up-key
        is_up = 1;
        break;

      case 0x12 :        // Left SHIFT
        shift = 1;
        break;

      case 0x59 :        // Right SHIFT
        shift = 1;
        break;

      default:
        if(!shift) {
          for(i = 0; normal_scancodes[i]!=scan && normal_scancodes[i]!=0; i+=2);
          if (normal_scancodes[i] == scan) {
            PS2_put_to_buff(normal_scancodes[i+1]);
          }
        } else {
          for(i = 0; shift_scancodes[i]!=scan && shift_scancodes[i]!=0; i+=2);
          if (shift_scancodes[i] == scan) {
            PS2_put_to_buff(shift_scancodes[i+1]);
        }
      }
      break;
    }
  } else {
    is_up = 0;
    switch (scan) {
      case 0x12 :                        // Left SHIFT
        shift = 0;
        break;

      case 0x59 :                        // Right SHIFT
        shift = 0;
        break;
    }
  }
  return;
}


/**
  * @brief  Inserting decoding character in the buffer
  * @param  Scan kod klavesy
  * @retval : None
  */
void PS2_put_to_buff(uint8_t ch)
{
  if (buffer_pointer < PS2_BUFSIZE) {
    *buffer = ch;
    buffer_pointer++;
  }
  return;
}

/**
  * @brief  Reading from the keyboard
  * @param  None
  * @retval : return character or NULL 
  */
uint8_t PS2_keyboard_getchar(void) {
  uint8_t byte = 0;
  if (buffer_pointer>0) {
    byte = *buffer;
    buffer_pointer--;
  }
  return byte;
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
