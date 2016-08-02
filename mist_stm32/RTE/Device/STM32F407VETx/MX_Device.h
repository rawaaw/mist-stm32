/******************************************************************************
 * File Name   : MX_Device.h
 * Date        : 02/08/2016 22:15:22
 * Description : STM32Cube MX parameter definitions
 * Note        : This file is generated by STM32CubeMX (DO NOT EDIT!)
 ******************************************************************************/

#ifndef __MX_DEVICE_H
#define __MX_DEVICE_H

/*---------------------------- Clock Configuration ---------------------------*/

#define MX_LSI_VALUE                            32000
#define MX_LSE_VALUE                            32768
#define MX_HSI_VALUE                            16000000
#define MX_HSE_VALUE                            8000000
#define MX_EXTERNAL_CLOCK_VALUE                 12288000
#define MX_PLLCLKFreq_Value                     168000000
#define MX_SYSCLKFreq_VALUE                     168000000
#define MX_HCLKFreq_Value                       168000000
#define MX_FCLKCortexFreq_Value                 168000000
#define MX_CortexFreq_Value                     168000000
#define MX_AHBFreq_Value                        168000000
#define MX_APB1Freq_Value                       42000000
#define MX_APB2Freq_Value                       84000000
#define MX_APB1TimFreq_Value                    84000000
#define MX_APB2TimFreq_Value                    168000000
#define MX_48MHZClocksFreq_Value                48000000
#define MX_EthernetFreq_Value                   168000000
#define MX_I2SClocksFreq_Value                  96000000
#define MX_RTCFreq_Value                        32000
#define MX_WatchDogFreq_Value                   32000
#define MX_MCO1PinFreq_Value                    16000000
#define MX_MCO2PinFreq_Value                    168000000

/*-------------------------------- NVIC       --------------------------------*/

#define MX_NVIC                                 1

/*-------------------------------- SDIO       --------------------------------*/

#define MX_SDIO                                 1

/* GPIO Configuration */

/* Pin PD2 */
#define MX_SDIO_CMD_Pin                         PD2
#define MX_SDIO_CMD_GPIOx                       GPIOD
#define MX_SDIO_CMD_GPIO_PuPd                   GPIO_NOPULL
#define MX_SDIO_CMD_GPIO_Speed_High_Default     GPIO_SPEED_FREQ_VERY_HIGH
#define MX_SDIO_CMD_GPIO_Pin                    GPIO_PIN_2
#define MX_SDIO_CMD_GPIO_AF                     GPIO_AF12_SDIO
#define MX_SDIO_CMD_GPIO_Mode                   GPIO_MODE_AF_PP

/* Pin PC12 */
#define MX_SDIO_CK_Pin                          PC12
#define MX_SDIO_CK_GPIOx                        GPIOC
#define MX_SDIO_CK_GPIO_PuPd                    GPIO_NOPULL
#define MX_SDIO_CK_GPIO_Speed_High_Default      GPIO_SPEED_FREQ_VERY_HIGH
#define MX_SDIO_CK_GPIO_Pin                     GPIO_PIN_12
#define MX_SDIO_CK_GPIO_AF                      GPIO_AF12_SDIO
#define MX_SDIO_CK_GPIO_Mode                    GPIO_MODE_AF_PP

/* Pin PC8 */
#define MX_SDIO_D0_Pin                          PC8
#define MX_SDIO_D0_GPIOx                        GPIOC
#define MX_SDIO_D0_GPIO_PuPd                    GPIO_NOPULL
#define MX_SDIO_D0_GPIO_Speed_High_Default      GPIO_SPEED_FREQ_VERY_HIGH
#define MX_SDIO_D0_GPIO_Pin                     GPIO_PIN_8
#define MX_SDIO_D0_GPIO_AF                      GPIO_AF12_SDIO
#define MX_SDIO_D0_GPIO_Mode                    GPIO_MODE_AF_PP

/* Pin PC9 */
#define MX_SDIO_D1_Pin                          PC9
#define MX_SDIO_D1_GPIOx                        GPIOC
#define MX_SDIO_D1_GPIO_PuPd                    GPIO_NOPULL
#define MX_SDIO_D1_GPIO_Speed_High_Default      GPIO_SPEED_FREQ_VERY_HIGH
#define MX_SDIO_D1_GPIO_Pin                     GPIO_PIN_9
#define MX_SDIO_D1_GPIO_AF                      GPIO_AF12_SDIO
#define MX_SDIO_D1_GPIO_Mode                    GPIO_MODE_AF_PP

/* Pin PC10 */
#define MX_SDIO_D2_Pin                          PC10
#define MX_SDIO_D2_GPIOx                        GPIOC
#define MX_SDIO_D2_GPIO_PuPd                    GPIO_NOPULL
#define MX_SDIO_D2_GPIO_Speed_High_Default      GPIO_SPEED_FREQ_VERY_HIGH
#define MX_SDIO_D2_GPIO_Pin                     GPIO_PIN_10
#define MX_SDIO_D2_GPIO_AF                      GPIO_AF12_SDIO
#define MX_SDIO_D2_GPIO_Mode                    GPIO_MODE_AF_PP

/* Pin PC11 */
#define MX_SDIO_D3_Pin                          PC11
#define MX_SDIO_D3_GPIOx                        GPIOC
#define MX_SDIO_D3_GPIO_PuPd                    GPIO_NOPULL
#define MX_SDIO_D3_GPIO_Speed_High_Default      GPIO_SPEED_FREQ_VERY_HIGH
#define MX_SDIO_D3_GPIO_Pin                     GPIO_PIN_11
#define MX_SDIO_D3_GPIO_AF                      GPIO_AF12_SDIO
#define MX_SDIO_D3_GPIO_Mode                    GPIO_MODE_AF_PP

/*-------------------------------- SPI2       --------------------------------*/

#define MX_SPI2                                 1

/* GPIO Configuration */

/* Pin PB13 */
#define MX_SPI2_SCK_GPIO_Speed                  GPIO_SPEED_FREQ_VERY_HIGH
#define MX_SPI2_SCK_Pin                         PB13
#define MX_SPI2_SCK_GPIOx                       GPIOB
#define MX_SPI2_SCK_GPIO_PuPd                   GPIO_NOPULL
#define MX_SPI2_SCK_GPIO_Pin                    GPIO_PIN_13
#define MX_SPI2_SCK_GPIO_AF                     GPIO_AF5_SPI2
#define MX_SPI2_SCK_GPIO_Mode                   GPIO_MODE_AF_PP

/* Pin PB12 */
#define MX_SPI2_NSS_GPIO_Speed                  GPIO_SPEED_FREQ_VERY_HIGH
#define MX_SPI2_NSS_Pin                         PB12
#define MX_SPI2_NSS_GPIOx                       GPIOB
#define MX_SPI2_NSS_GPIO_PuPd                   GPIO_NOPULL
#define MX_SPI2_NSS_GPIO_Pin                    GPIO_PIN_12
#define MX_SPI2_NSS_GPIO_AF                     GPIO_AF5_SPI2
#define MX_SPI2_NSS_GPIO_Mode                   GPIO_MODE_AF_PP

/* Pin PB14 */
#define MX_SPI2_MISO_GPIO_Speed                 GPIO_SPEED_FREQ_VERY_HIGH
#define MX_SPI2_MISO_Pin                        PB14
#define MX_SPI2_MISO_GPIOx                      GPIOB
#define MX_SPI2_MISO_GPIO_PuPd                  GPIO_NOPULL
#define MX_SPI2_MISO_GPIO_Pin                   GPIO_PIN_14
#define MX_SPI2_MISO_GPIO_AF                    GPIO_AF5_SPI2
#define MX_SPI2_MISO_GPIO_Mode                  GPIO_MODE_AF_PP

/* Pin PB15 */
#define MX_SPI2_MOSI_GPIO_Speed                 GPIO_SPEED_FREQ_VERY_HIGH
#define MX_SPI2_MOSI_Pin                        PB15
#define MX_SPI2_MOSI_GPIOx                      GPIOB
#define MX_SPI2_MOSI_GPIO_PuPd                  GPIO_NOPULL
#define MX_SPI2_MOSI_GPIO_Pin                   GPIO_PIN_15
#define MX_SPI2_MOSI_GPIO_AF                    GPIO_AF5_SPI2
#define MX_SPI2_MOSI_GPIO_Mode                  GPIO_MODE_AF_PP

/*-------------------------------- SYS        --------------------------------*/

#define MX_SYS                                  1

/* GPIO Configuration */

/*-------------------------------- USART1     --------------------------------*/

#define MX_USART1                               1

#define MX_USART1_VM                            VM_ASYNC

/* GPIO Configuration */

/* Pin PA9 */
#define MX_USART1_TX_GPIO_Speed                 GPIO_SPEED_FREQ_VERY_HIGH
#define MX_USART1_TX_Pin                        PA9
#define MX_USART1_TX_GPIOx                      GPIOA
#define MX_USART1_TX_GPIO_PuPd                  GPIO_PULLUP
#define MX_USART1_TX_GPIO_Pin                   GPIO_PIN_9
#define MX_USART1_TX_GPIO_AF                    GPIO_AF7_USART1
#define MX_USART1_TX_GPIO_Mode                  GPIO_MODE_AF_PP

/* Pin PA10 */
#define MX_USART1_RX_GPIO_Speed                 GPIO_SPEED_FREQ_VERY_HIGH
#define MX_USART1_RX_Pin                        PA10
#define MX_USART1_RX_GPIOx                      GPIOA
#define MX_USART1_RX_GPIO_PuPd                  GPIO_PULLUP
#define MX_USART1_RX_GPIO_Pin                   GPIO_PIN_10
#define MX_USART1_RX_GPIO_AF                    GPIO_AF7_USART1
#define MX_USART1_RX_GPIO_Mode                  GPIO_MODE_AF_PP

/*-------------------------------- USB_DEVICE --------------------------------*/

#define MX_USB_DEVICE                           1

/* GPIO Configuration */

/*-------------------------------- GPIO       --------------------------------*/

#define MX_GPIO                                 1

/* GPIO Configuration */

/* Pin PA2 */
#define MX_PA2_Pin                              PA2
#define MX_PA2_GPIOx                            GPIOA
#define MX_PA2_GPIO_PuPd                        GPIO_PULLUP
#define MX_PS2_MOUSE_SCK                        PA2
#define MX_PA2_GPIO_Pin                         GPIO_PIN_2
#define MX_PA2_GPIO_ModeDefaultEXTI             GPIO_MODE_IT_RISING

/* Pin PC4 */
#define MX_PC4_GPIO_Speed                       GPIO_SPEED_FREQ_LOW
#define MX_PC4_Pin                              PC4
#define MX_PC4_GPIOx                            GPIOC
#define MX_PC4_PinState                         GPIO_PIN_RESET
#define MX_PC4_GPIO_PuPd                        GPIO_NOPULL
#define MX_SS0                                  PC4
#define MX_PC4_GPIO_Pin                         GPIO_PIN_4
#define MX_PC4_GPIO_ModeDefaultOutputPP         GPIO_MODE_OUTPUT_PP

/* Pin PA1 */
#define MX_PA1_Pin                              PA1
#define MX_PA1_GPIOx                            GPIOA
#define MX_PA1_GPIO_PuPd                        GPIO_PULLUP
#define MX_PS2_KBD_DATA                         PA1
#define MX_PA1_GPIO_Pin                         GPIO_PIN_1
#define MX_PA1_GPIO_Mode                        GPIO_MODE_INPUT

/* Pin PE8 */
#define MX_PE8_Pin                              PE8
#define MX_PE8_GPIOx                            GPIOE
#define MX_PE8_GPIO_PuPd                        GPIO_NOPULL
#define MX_JTAG_TDO                             PE8
#define MX_PE8_GPIO_Pin                         GPIO_PIN_8
#define MX_PE8_GPIO_Mode                        GPIO_MODE_INPUT

/* Pin PA0-WKUP */
#define MX_PA0_WKUP_Pin                         PA0_WKUP
#define MX_PA0_WKUP_GPIOx                       GPIOA
#define MX_PA0_WKUP_GPIO_PuPd                   GPIO_PULLUP
#define MX_PS2_KBD_SCK                          PA0_WKUP
#define MX_PA0_WKUP_GPIO_Pin                    GPIO_PIN_0
#define MX_PA0_WKUP_GPIO_ModeDefaultEXTI        GPIO_MODE_IT_RISING

/* Pin PA3 */
#define MX_PA3_Pin                              PA3
#define MX_PA3_GPIOx                            GPIOA
#define MX_PA3_GPIO_PuPd                        GPIO_PULLUP
#define MX_PS2_MOUSE_DATA                       PA3
#define MX_PA3_GPIO_Pin                         GPIO_PIN_3
#define MX_PA3_GPIO_Mode                        GPIO_MODE_INPUT

/* Pin PC5 */
#define MX_PC5_GPIO_Speed                       GPIO_SPEED_FREQ_LOW
#define MX_PC5_Pin                              PC5
#define MX_PC5_GPIOx                            GPIOC
#define MX_PC5_PinState                         GPIO_PIN_RESET
#define MX_PC5_GPIO_PuPd                        GPIO_NOPULL
#define MX_SS2_FPGA                             PC5
#define MX_PC5_GPIO_Pin                         GPIO_PIN_5
#define MX_PC5_GPIO_ModeDefaultOutputPP         GPIO_MODE_OUTPUT_PP

/* Pin PE7 */
#define MX_PE7_GPIO_Speed                       GPIO_SPEED_FREQ_LOW
#define MX_PE7_Pin                              PE7
#define MX_PE7_GPIOx                            GPIOE
#define MX_PE7_PinState                         GPIO_PIN_RESET
#define MX_PE7_GPIO_PuPd                        GPIO_NOPULL
#define MX_JTAG_TCK                             PE7
#define MX_PE7_GPIO_Pin                         GPIO_PIN_7
#define MX_PE7_GPIO_ModeDefaultOutputPP         GPIO_MODE_OUTPUT_PP

/* Pin PA6 */
#define MX_PA6_GPIO_Speed                       GPIO_SPEED_FREQ_LOW
#define MX_PA6_Pin                              PA6
#define MX_PA6_GPIOx                            GPIOA
#define MX_PA6_PinState                         GPIO_PIN_RESET
#define MX_PA6_GPIO_PuPd                        GPIO_NOPULL
#define MX_DISKLED                              PA6
#define MX_PA6_GPIO_Pin                         GPIO_PIN_6
#define MX_PA6_GPIO_ModeDefaultOutputPP         GPIO_MODE_OUTPUT_PP

/* Pin PE9 */
#define MX_PE9_GPIO_Speed                       GPIO_SPEED_FREQ_LOW
#define MX_PE9_Pin                              PE9
#define MX_PE9_GPIOx                            GPIOE
#define MX_PE9_PinState                         GPIO_PIN_RESET
#define MX_PE9_GPIO_PuPd                        GPIO_NOPULL
#define MX_JTAG_TMS                             PE9
#define MX_PE9_GPIO_Pin                         GPIO_PIN_9
#define MX_PE9_GPIO_ModeDefaultOutputPP         GPIO_MODE_OUTPUT_PP

/* Pin PA7 */
#define MX_PA7_GPIO_Speed                       GPIO_SPEED_FREQ_LOW
#define MX_PA7_Pin                              PA7
#define MX_PA7_GPIOx                            GPIOA
#define MX_PA7_PinState                         GPIO_PIN_RESET
#define MX_PA7_GPIO_PuPd                        GPIO_NOPULL
#define MX_LED                                  PA7
#define MX_PA7_GPIO_Pin                         GPIO_PIN_7
#define MX_PA7_GPIO_ModeDefaultOutputPP         GPIO_MODE_OUTPUT_PP

/* Pin PE11 */
#define MX_PE11_Pin                             PE11
#define MX_PE11_GPIOx                           GPIOE
#define MX_PE11_GPIO_PuPd                       GPIO_NOPULL
#define MX_ALT_CONF_DONE                        PE11
#define MX_PE11_GPIO_Pin                        GPIO_PIN_11
#define MX_PE11_GPIO_Mode                       GPIO_MODE_INPUT

/* Pin PE10 */
#define MX_PE10_GPIO_Speed                      GPIO_SPEED_FREQ_LOW
#define MX_PE10_Pin                             PE10
#define MX_PE10_GPIOx                           GPIOE
#define MX_PE10_PinState                        GPIO_PIN_RESET
#define MX_PE10_GPIO_PuPd                       GPIO_NOPULL
#define MX_JTAG_TDI                             PE10
#define MX_PE10_GPIO_Pin                        GPIO_PIN_10
#define MX_PE10_GPIO_ModeDefaultOutputPP        GPIO_MODE_OUTPUT_PP

/* Pin PE4 */
#define MX_PE4_Pin                              PE4
#define MX_PE4_GPIOx                            GPIOE
#define MX_PE4_GPIO_PuPd                        GPIO_NOPULL
#define MX_BTN2                                 PE4
#define MX_PE4_GPIO_Pin                         GPIO_PIN_4
#define MX_PE4_GPIO_Mode                        GPIO_MODE_INPUT

/* Pin PB1 */
#define MX_PB1_GPIO_Speed                       GPIO_SPEED_FREQ_LOW
#define MX_PB1_Pin                              PB1
#define MX_PB1_GPIOx                            GPIOB
#define MX_PB1_PinState                         GPIO_PIN_RESET
#define MX_PB1_GPIO_PuPd                        GPIO_NOPULL
#define MX_SS4_SD_DIRECT                        PB1
#define MX_PB1_GPIO_Pin                         GPIO_PIN_1
#define MX_PB1_GPIO_ModeDefaultOutputPP         GPIO_MODE_OUTPUT_PP

/* Pin PE3 */
#define MX_PE3_Pin                              PE3
#define MX_PE3_GPIOx                            GPIOE
#define MX_PE3_GPIO_PuPd                        GPIO_NOPULL
#define MX_BTN1                                 PE3
#define MX_PE3_GPIO_Pin                         GPIO_PIN_3
#define MX_PE3_GPIO_Mode                        GPIO_MODE_INPUT

/* Pin PB0 */
#define MX_PB0_GPIO_Speed                       GPIO_SPEED_FREQ_LOW
#define MX_PB0_Pin                              PB0
#define MX_PB0_GPIOx                            GPIOB
#define MX_PB0_PinState                         GPIO_PIN_RESET
#define MX_PB0_GPIO_PuPd                        GPIO_NOPULL
#define MX_SS3_OSD                              PB0
#define MX_PB0_GPIO_Pin                         GPIO_PIN_0
#define MX_PB0_GPIO_ModeDefaultOutputPP         GPIO_MODE_OUTPUT_PP

#endif  /* __MX_DEVICE_H */

