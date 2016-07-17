/**
  ******************************************************************************
  * File Name          : mxconstants.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MXCONSTANT_H
#define __MXCONSTANT_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define BTN1_Pin GPIO_PIN_3
#define BTN1_GPIO_Port GPIOE
#define BTN2_Pin GPIO_PIN_4
#define BTN2_GPIO_Port GPIOE
#define PS2_KBD_SCK_Pin GPIO_PIN_0
#define PS2_KBD_SCK_GPIO_Port GPIOA
#define PS2_KBD_DATA_Pin GPIO_PIN_1
#define PS2_KBD_DATA_GPIO_Port GPIOA
#define PS2_MOUSE_SCK_Pin GPIO_PIN_2
#define PS2_MOUSE_SCK_GPIO_Port GPIOA
#define PS2_MOUSE_DATA_Pin GPIO_PIN_3
#define PS2_MOUSE_DATA_GPIO_Port GPIOA
#define DISKLED_Pin GPIO_PIN_6
#define DISKLED_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_7
#define LED_GPIO_Port GPIOA
#define SS0_Pin GPIO_PIN_4
#define SS0_GPIO_Port GPIOC
#define SS2_FPGA_Pin GPIO_PIN_5
#define SS2_FPGA_GPIO_Port GPIOC
#define SS3_OSD_Pin GPIO_PIN_0
#define SS3_OSD_GPIO_Port GPIOB
#define SS4_SD_DIRECT_Pin GPIO_PIN_1
#define SS4_SD_DIRECT_GPIO_Port GPIOB
#define none_Pin GPIO_PIN_2
#define none_GPIO_Port GPIOB
#define CONF_NCONFIG_Pin GPIO_PIN_7
#define CONF_NCONFIG_GPIO_Port GPIOE
#define CONF_DATA0_Pin GPIO_PIN_8
#define CONF_DATA0_GPIO_Port GPIOE
#define CONF_DONE_Pin GPIO_PIN_9
#define CONF_DONE_GPIO_Port GPIOE
#define CONF_DCLK_Pin GPIO_PIN_10
#define CONF_DCLK_GPIO_Port GPIOE
#define nCS_Pin GPIO_PIN_11
#define nCS_GPIO_Port GPIOE
#define nCE_Pin GPIO_PIN_12
#define nCE_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MXCONSTANT_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
