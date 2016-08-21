/*
* stubs
*/
#include <string.h>
#include "stm32f4xx_hal.h"
#include "usbd_cdc_if.h"



uint8_t StateJoyGet (uint8_t joy_num){
  return 0;
}

uint8_t StateJoyGetExtra (uint8_t joy_num){
  return 0;
}

#if 0
uint8_t StateKeyboardModifiers (void){
  return 0;
}

void StateKeyboardPressed (uint8_t *pressed){
  *pressed = 0;
  return;
}
#endif

uint8_t StateNumJoysticks (void){
  return 0;
}

void StateNumJoysticksSet (uint8_t num){
  return;
}

uint8_t StateUsbGetNumButtons (uint8_t joy_num){
  return 0;
}

uint8_t StateUsbJoyGet (uint8_t joy_num){
  return 0;
}

uint8_t StateUsbJoyGetExtra (uint8_t joy_num){
  return 0;
}

uint16_t StateUsbPidGet (uint8_t joy_num){
  return 0;
}

uint16_t StateUsbVidGet (uint8_t joy_num){
  return 0;
}

void StateJoySet (uint8_t c, uint8_t joy_num){
  return;
}

#if 0
void StateKeyboardSet (uint8_t modifier, uint8_t* pressed, uint16_t* pressed_ps2){
  return;
}
#endif

void StateJoySetExtra (uint8_t c, uint8_t joy_num){
  return;
}

void StateUsbIdSet (uint16_t vid, uint16_t pid, uint8_t num_buttons, uint8_t joy_num){
  return;
}

void StateUsbJoySet (uint8_t usbjoy, uint8_t usbextra, uint8_t joy_num){
  return;
}

char* itoa (int value, char * str, int base){
  if (base == 10)
    sprintf(str, "%d", value);
  else if (base == 16)
    sprintf(str, "%x", value);
  else if (base == 8)
    sprintf(str, "%o", value);
  else
    sprintf(str, "%d", value);
  return str;
}

void bzero (void *s, uint32_t n){
  int i;
  for (i = 0; i < n; i ++){
    *(((char*)s) + i) = 0;
  }
  return;
}

uint8_t hid_get_joysticks(void){
  return 0;
}


/* from usb/usbrtc.c: */

/* RTC functions */
extern RTC_HandleTypeDef hrtc;

uint8_t usb_rtc_get_time(uint8_t *d){
  HAL_StatusTypeDef  rc;
  RTC_DateTypeDef sDate;
  RTC_TimeTypeDef sTime;
  rc = HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
  if (rc == HAL_OK) {
    rc = HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    if (rc == HAL_OK) {
      d[0] = sDate.Year;    /* YY */ 
      d[1] = sDate.Month;   /* MM */ 
      d[2] = sDate.Date;    /* DD */ 
      d[3] = sTime.Hours;   /* HH */ 
      d[4] = sTime.Minutes; /* MI */ 
      d[5] = sTime.Seconds; /* SS */ 
    } 
  }
  if (rc != HAL_OK)
    memset(d, 0, 6);
  return (rc == HAL_OK);
}

uint8_t usb_rtc_set_time(uint8_t *d){
  HAL_StatusTypeDef  rc;
  RTC_DateTypeDef sDate;
  RTC_TimeTypeDef sTime;

  memset(&sDate, 0, sizeof(sDate));
  memset(&sTime, 0, sizeof(sTime));

  sDate.Year  = d[0];
  sDate.Month = d[1];
  sDate.Date  = d[2];
  sTime.Hours = d[3];
  sTime.Minutes = d[4];
  sTime.Seconds = d[5];

  rc = HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
  if (rc == HAL_OK)
    rc = HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);

  return (rc == HAL_OK);
}

/* from cdc_enumerate.c : */
typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;

void usb_cdc_open(void) {
  return;
}

//*----------------------------------------------------------------------------
//* \fn    usb_cdc_is_configured
//* \brief Test if the device is configured
//*----------------------------------------------------------------------------
uchar usb_cdc_is_configured(void) {
  return 0;
//  return (CDC_IsTransmitterBusy() != -1); /* -1 means CDC is not initialized */
}

uint16_t usb_cdc_read(char *pData, uint16_t length) {
  uint32_t nbBytesRcv = 0;
  
  if ( !usb_cdc_is_configured() )
    return 0;
  nbBytesRcv = CDC_GetRxBufferChars();
  if (nbBytesRcv > 0){
    memcpy(pData, CDC_GetRxBuffer(), (nbBytesRcv < length)? nbBytesRcv:length);
    CDC_ClearRxBufferChars();
  }
  return (uint16_t)((nbBytesRcv < length)? nbBytesRcv:length);
}


uint usb_cdc_write(const char *pData, uint length) {
  uint8_t *dt_buf;
  uint dt_size = 0;
  uint32_t portion_size;
  uint8_t rc = USBD_OK;

  if(usb_cdc_is_configured()) {
    
    dt_buf = CDC_GetTxBuffer();
    while (dt_size < length){
      if (CDC_IsTransmitterBusy() == 0){

        if (rc == USBD_OK){
          portion_size = (CDC_GetTxBufferSize() < length)? CDC_GetTxBufferSize():length;
          memcpy(dt_buf, pData, portion_size);
        }

        rc = CDC_Transmit_FS(dt_buf, portion_size);

        if (rc == USBD_OK) {
          pData += portion_size;
          dt_size += portion_size;
        }else{
          /* EP busy ?*/
          HAL_Delay(1);
        }
      }else{
        /* EP busy ?*/
        HAL_Delay(1);
      }
    }
  }
  return dt_size;
}

/* from pl2303.c: */

int8_t pl2303_is_blocked(void) {
  return 0;
}

void pl2303_tx_byte(uint8_t byte) {
  return;
}

int8_t pl2303_present(void) {
  return 0;
}
