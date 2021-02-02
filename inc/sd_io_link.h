/**
  ******************************************************************************
  * @file    sd_io_link.h
  * @author  MCD Application Team
  * @brief   Header for sd_io_link.c
  *
  * @note This file was modified by LucasHaug <lucas.haug@thunderat.org>, it's
  *       original name was stm32g0xx_nucleo.h
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SD_IO_LINK_H
#define SD_IO_LINK_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup BSP
  * @{
  */

/** @defgroup SD_IO_LINK STM32G0XX-NUCLEO
  * @{
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"


/** @defgroup SD_IO_LINK_Exported_Constants Exported Constants
  * @{
  */

/**
* @brief	Define for SD_IO_LINK board
  */
#if !defined (USE_SD_IO_LINK)
 #define USE_SD_IO_LINK
#endif

/** @defgroup SD_IO_LINK_BUS BUS Constants
  * @{
  */
/*###################### SPI1 ###################################*/
#define NUCLEO_SPIx                                 SPI1
#define NUCLEO_SPIx_CLK_ENABLE()                  __HAL_RCC_SPI1_CLK_ENABLE()

#define NUCLEO_SPIx_SCK_AF                          GPIO_AF0_SPI1
#define NUCLEO_SPIx_SCK_GPIO_PORT                   GPIOA
#define NUCLEO_SPIx_SCK_PIN                         GPIO_PIN_5
#define NUCLEO_SPIx_SCK_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOA_CLK_ENABLE()
#define NUCLEO_SPIx_SCK_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOA_CLK_DISABLE()

#define NUCLEO_SPIx_MISO_MOSI_AF                    GPIO_AF0_SPI1
#define NUCLEO_SPIx_MISO_MOSI_GPIO_PORT             GPIOA
#define NUCLEO_SPIx_MISO_MOSI_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()
#define NUCLEO_SPIx_MISO_MOSI_GPIO_CLK_DISABLE()  __HAL_RCC_GPIOA_CLK_DISABLE()
#define NUCLEO_SPIx_MISO_PIN                        GPIO_PIN_6
#define NUCLEO_SPIx_MOSI_PIN                        GPIO_PIN_7
/* Maximum Timeout values for flags waiting loops. These timeouts are not based
   on accurate values, they just guarantee that the application will not remain
   stuck if the SPI communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */
#define NUCLEO_SPIx_TIMEOUT_MAX                   1000


/**
  * @brief  SD Control Lines management
  */
#define SD_CS_LOW()       HAL_GPIO_WritePin(SD_CS_GPIO_PORT, SD_CS_PIN, GPIO_PIN_RESET)
#define SD_CS_HIGH()      HAL_GPIO_WritePin(SD_CS_GPIO_PORT, SD_CS_PIN, GPIO_PIN_SET)

/**
  * @brief  SD Control Interface pins (shield D4)
  */
#define SD_CS_PIN                                 GPIO_PIN_5
#define SD_CS_GPIO_PORT                           GPIOB
#define SD_CS_GPIO_CLK_ENABLE()                 __HAL_RCC_GPIOB_CLK_ENABLE()
#define SD_CS_GPIO_CLK_DISABLE()                __HAL_RCC_GPIOB_CLK_DISABLE()

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* SD_IO_LINK_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
