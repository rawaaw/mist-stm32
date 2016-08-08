/******************************************************************************/
/* RETARGET.C: 'Retarget' layer for target-dependent low level functions      */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2005 Keil Software. All rights reserved.                     */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/

#include <stdio.h>
#include <time.h>
#include <rt_misc.h>
#include "stm32f4xx_hal.h"

#pragma import(__use_no_semihosting_swi)


extern int  sendchar(int ch);  /* in Serial.c */
extern int  getkey(void);      /* in Serial.c */
extern long timeval;           /* in Time.c   */

extern UART_HandleTypeDef huart1;

struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;


int fputc(int ch, FILE *f) {
  HAL_UART_StateTypeDef rc;
  do {
    rc = HAL_UART_GetState(&huart1);
    if (rc == HAL_UART_STATE_RESET || rc == HAL_UART_STATE_ERROR)
      return EOF;
  }while (rc != HAL_UART_STATE_READY);
  HAL_UART_Transmit_IT(&huart1, (uint8_t*)&ch, 1);
  return 0;
//  return (sendchar(ch));
}

int fgetc(FILE *f) {
  return 0;
//  return (sendchar(getkey()));
}


int ferror(FILE *f) {
  /* Your implementation of ferror */
  return EOF;
}


void _ttywrch(int ch) {
  HAL_UART_StateTypeDef rc;
  do {
    rc = HAL_UART_GetState(&huart1);
    if (rc == HAL_UART_STATE_RESET || rc == HAL_UART_STATE_ERROR)
      return;
  }while (rc != HAL_UART_STATE_READY);
  HAL_UART_Transmit_IT(&huart1, (uint8_t*)&ch, 1);
//  sendchar (ch);
}


void _sys_exit(int return_code) {
  while (1);    /* endless loop */
}
