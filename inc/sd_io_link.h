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

/** @defgroup SD_IO_LINK
  * @{
  */

/* Includes ------------------------------------------------------------------*/

#include "spi.h"
#include "gpio.h"

/** @defgroup SD_IO_LINK_Exported_Constants Exported Constants
  * @{
  */

/**
* @brief	Define for SD_IO_LINK board
  */
#if !defined (USE_SD_IO_LINK)
 #define USE_SD_IO_LINK
#endif

/** @defgroup SD_IO_LINK_Exported_Functions
  * @{
  */

/**
 * @brief Initialize memory card platform.
 *        This function is used for the user to define which
 *        SPI instance and CS pin are being used.
 *
 * @param hspi SPI instance handler
 * @param cs_port Chip select port
 * @param cs_pin Chip select pin number
 */
void mem_card_init(SPI_HandleTypeDef* hspi, GPIO_TypeDef* cs_port, uint16_t cs_pin);

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
