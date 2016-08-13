/*
*
*/
#include "ps2_tables.h"

static const uint8_t s_ps2_to_hid[PS2_TO_HID_TABLE_SIZE] = {
/* 00 */   '\x00',  /* */
/* 01 */   '\x42',  /*         (F001) F9  */
/* 02 */   '\x00',  /* */
/* 03 */   '\x3E',  /*         (F003) F5  */
/* 04 */   '\x3C',  /*         (F004) F3  */
/* 05 */   '\x3A',  /*         (F005) F1  */
/* 06 */   '\x3B',  /*         (F006) F2  */
/* 07 */   '\x45',  /*         (F007) F12 */
/* 08 */   '\x00',  /* */
/* 09 */   '\x43',  /*         (F009) F10 */
/* 0A */   '\x41',  /*         (F00A) F8  */
/* 0B */   '\x3F',  /*         (F00B) F6  */
/* 0C */   '\x3D',  /*         (F00C) F4  */
/* 0D */   '\x2B',  /*         (F00D) Tab */
/* 0E */   '\x35',  /*         (F00E) `~  */
/* 0F */   '\x00',  /* */
/* 10 */   '\x00',  /* */
/* 11 */   '\xE2',  /*         (F011) Alt_(left) */
/* 12 */   '\xE1',  /*         (F012) Shift_(Left)*/
/* 13 */   '\x00',  /* */
/* 14 */   '\xE0',  /*         (F014) Ctrl_(left) */
/* 15 */   '\x14',  /*         (F015) Q   */
/* 16 */   '\x1E',  /*         (F016) 1 ! */
/* 17 */   '\x00',  /* */
/* 18 */   '\x00',  /* */
/* 19 */   '\x00',  /* */
/* 1A */   '\x1D',  /*         (F01A) Z   */
/* 1B */   '\x16',  /*         (F01B) S   */
/* 1C */   '\x04',  /*         (F01C) A   */
/* 1D */   '\x1A',  /*         (F01D) W   */
/* 1E */   '\x1F',  /*         (F01E) 2 @ */
/* 1F */   '\x00',  /* */
/* 20 */   '\x00',  /* */
/* 21 */   '\x06',  /*         (F021) C   */
/* 22 */   '\x1B',  /*         (F022) X   */
/* 23 */   '\x07',  /*         (F023) D   */
/* 24 */   '\x08',  /*         (F024) E   */
/* 25 */   '\x21',  /*         (F025) 4 $ */
/* 26 */   '\x20',  /*         (F026) 3 # */
/* 27 */   '\x00',  /* */
/* 28 */   '\x00',  /* */
/* 29 */   '\x2C',  /*         (F029) Spacebar */
/* 2A */   '\x19',  /*         (F02A) V   */
/* 2B */   '\x09',  /*         (F02B) F   */
/* 2C */   '\x17',  /*         (F02C) T   */
/* 2D */   '\x15',  /*         (F02D) R   */
/* 2E */   '\x22',  /*         (F02E) 5 % */
/* 2F */   '\x00',  /* */
/* 30 */   '\x00',  /* */
/* 31 */   '\x11',  /*         (F031) N   */
/* 32 */   '\x05',  /*         (F032) B   */
/* 33 */   '\x0B',  /*         (F033) H   */
/* 34 */   '\x0A',  /*         (F034) G   */
/* 35 */   '\x1C',  /*         (F035) Y   */
/* 36 */   '\x23',  /*         (F036) 6 ^ */
/* 37 */   '\x00',  /* */
/* 38 */   '\x00',  /* */
/* 39 */   '\x00',  /* */
/* 3A */   '\x10',  /*         (F03A) M   */
/* 3B */   '\x0D',  /*         (F03B) J   */
/* 3C */   '\x18',  /*         (F03C) U   */
/* 3D */   '\x24',  /*         (F03D) 7 & */
/* 3E */   '\x25',  /*         (F03E) 8 * */
/* 3F */   '\x00',  /* */
/* 40 */   '\x00',  /* */
/* 41 */   '\x36',  /*         (F041) , < */
/* 42 */   '\x0E',  /*         (F042) K   */
/* 43 */   '\x0C',  /*         (F043) I   */
/* 44 */   '\x12',  /*         (F044) O   */
/* 45 */   '\x27',  /*         (F045) 0 ) */
/* 46 */   '\x26',  /*         (F046) 9 ( */
/* 47 */   '\x00',  /* */
/* 48 */   '\x00',  /* */
/* 49 */   '\x37',  /*         (F049) . > */
/* 4A */   '\x38',  /*         (F04A) / ? */
/* 4B */   '\x0F',  /*         (F04B) L   */
/* 4C */   '\x33',  /*         (F04C) ; : */
/* 4D */   '\x13',  /*         (F04D) P   */
/* 4E */   '\x2D',  /*         (F04E) - _ */
/* 4F */   '\x00',  /* */
/* 50 */   '\x00',  /* */
/* 51 */   '\x00',  /* */
/* 52 */   '\x34',  /*         (F052) ' " */
/* 53 */   '\x00',  /* */
/* 54 */   '\x2F',  /*         (F054) [ { */
/* 55 */   '\x2E',  /*         (F055) = + */
/* 56 */   '\x00',  /* */
/* 57 */   '\x00',  /* */
/* 58 */   '\x39',  /*         (F058) Caps_Lock */
/* 59 */   '\xE5',  /*         (F059) Shift_(Right) */
/* 5A */   '\x28',  /*         (F05A) Enter */
/* 5B */   '\x30',  /*         (F05B) ] } */
/* 5C */   '\x00',  /* */
/* 5D */   '\x31',  /*         (F05D) \ | */
/* 5E */   '\x00',  /* */
/* 5F */   '\x00',  /* */
/* 60 */   '\x00',  /* */
/* 61 */   '\x00',  /* */
/* 62 */   '\x00',  /* */
/* 63 */   '\x00',  /* */
/* 64 */   '\x00',  /* */
/* 65 */   '\x00',  /* */
/* 66 */   '\x2A',  /*         (F066) Backspace */
/* 67 */   '\x00',  /* */
/* 68 */   '\x00',  /* */
/* 69 */   '\x4D',  /* HP keyboard. End (keypad) */
/* 6A */   '\x00',  /* */
/* 6B */   '\x50',  /* HP keyboard. Left Arrow (keypad) */
/* 6C */   '\x4A',  /* HP keyboard. Home (keypad) */
/* 6D */   '\x00',  /* */
/* 6E */   '\x00',  /* */
/* 6F */   '\x00',  /* */

/* keypad -> */
/* 70 */   '\x62',  /*         (F070) 0 Insert  */
/* 71 */   '\x63',  /*         (F071) . Del     */
/* 72 */   '\x5A',  /*         (F072) 2 Down    */
/* 73 */   '\x5D',  /*         (F073) 5         */
/* 74 */   '\x5E',  /*         (F074) 6 Right   */
/* 75 */   '\x60',  /*         (F075) 8 Up      */
/* <- keypad */

/* 76 */   '\x29',  /*         (F076) ESC */
/* 77 */   '\x53',  /*         (F077) Num_Lock  */
/* 78 */   '\x44',  /*         (F078) F11 */

/* keypad -> */
/* 79 */   '\x57',  /*         (F079) +         */
/* 7A */   '\x5B',  /*         (F07A) 3 PgDown  */
/* 7B */   '\x56',  /*         (F07B) -         */
/* 7C */   '\x55',  /*         (F07C) *         */
/* 7D */   '\x61',  /*         (F07D) 9 PgUp    */
/* <- keypad */

/* 7E */   '\x47',  /*         (F07E) Scroll_Lock */
/* 7F */   '\x00',  /* */
/* 80 */   '\x00',  /* */
/* 81 */   '\x00',  /* */
/* 82 */   '\x00',  /* */
/* 83 */   '\x40'   /*         (F083) F7 */
};

/*
*
*/
uint8_t ps2_to_hid(uint8_t scancode){
  if (scancode < PS2_TO_HID_TABLE_SIZE){
    return s_ps2_to_hid[scancode];
  }else{
    return 0;
  }
}


/* 
*
* prefix E0 
*/
uint8_t ps2_to_hid_prefix_E0(uint8_t scancode){
  switch (scancode){
    case 0x11: return 0xE6; /* E011 (E0F011) Alt_(right) */
    case 0x14: return 0xE4; /* E0 (E0F014) Ctrl_(right)*/
    case 0x1F: return 0xE3; /* E0 (E0F01F) Windows_(left) / Left GUI */
    case 0x27: return 0xE7; /* E0 (E0F027) Windows_(right) / Right GUI */
    case 0x2F: return 0x65; /* E0 (E0F02F) Menus / App */
    case 0x4A: return 0x54; /* E0 (E0F04A) /          */
    case 0x5A: return 0x58; /* E0 (E0F05A) Enter*/
    case 0x69: return 0x59; /* E0 (E0F069) End      */
    case 0x6B: return 0x50; /* E0 (E0F06B) Left_Arrow */
    case 0x6C: return 0x5F; /* E0 (E0F06C) Home*/
    case 0x70: return 0x62; /* E0 (E0F070) Insert*/
    case 0x71: return 0x63; /* E0 (E0F071) Delete*/
    case 0x72: return 0x51; /* E0 (E0F072) Down_Arrow */
    case 0x74: return 0x4F; /* E0 (E0F074) Right_Arrow*/
    case 0x75: return 0x52; /* E0 (E0F075) Up_Arrow   */
    case 0x7A: return 0x4E; /* E0 (E0F07A) Page_Down*/
    case 0x7C: return 0x46; /* E0 (E0F07C) Print Screen */
    case 0x7D: return 0x4B; /* E0 (E0F07D) Page_Up*/
    default: return 0;
  }
};


/*
* check pressed key is modifier key
* returns 1/0
* IN: code - PS2 scancode
* INOUT: modifier - modifier byte state
* IN: key pressed /  released
*/
uint8_t is_hid_modifier_key(uint8_t code, uint8_t *modifier, uint8_t press_flag){
  if (code == 0x59){  /* (F059) Shift_(Right) */
    if (press_flag){
      *modifier |= 0x20; //00100000
    }else{
      *modifier &= 0xDF; //11011111
    }
    return 1;
  }
  if (code == 0x11){  /* (F011) Alt_(left) */
    if (press_flag){
      *modifier |= 0x04; //00000100
    }else{
      *modifier &= 0xFB; //11111011
    }
    return 1;
  }
  if (code == 0x12){  /* (F012) Shift_(Left)*/
    if (press_flag){
      *modifier |= 0x02; //00000010
    }else{
      *modifier &= 0xFD; //11111101
    }
    return 1;
  }
  if (code == 0x14){  /* (F014) Ctrl_(left) */
    if (press_flag){
      *modifier |= 0x01; //00000001
    }else{
      *modifier &= 0xFE; //11111110
    }
    return 1;
  }
  return 0;
}

/*
* check pressed key is modifier key (for extended scancodes)
* returns 1/0
* IN: code - PS2 scancode
* INOUT: modifier - modifier byte state
* IN: key pressed /  released
*/
uint8_t is_hid_modifier_key_E0(uint8_t code, uint8_t *modifier, uint8_t press_flag){
  if (code == 0x11){ /* E011 (E0F011) Alt_(right) */
    if (press_flag){
      *modifier |= 0x40; //01000000
    }else{
      *modifier &= 0xBF; //10111111
    }
    return 1;
  }
  if (code == 0x14){ /* E0 (E0F014) Ctrl_(right)*/
    if (press_flag){
      *modifier |= 0x10; //00010000
    }else{
      *modifier &= 0xEF; //11101111
    }
    return 1;
  }
  if (code == 0x1F){ /* E0 (E0F01F) Windows_(left) / Left GUI */
    if (press_flag){
      *modifier |= 0x08; //00001000
    }else{
      *modifier &= 0xF7; //11110111
    }
    return 1;
  }
  if (code == 0x27){ /* E0 (E0F027) Windows_(right) / Right GUI */
    if (press_flag){
      *modifier |= 0x80; //10000000
    }else{
      *modifier &= 0x7F; //01111111
    }
    return 1;
  }
  return 0;
}

