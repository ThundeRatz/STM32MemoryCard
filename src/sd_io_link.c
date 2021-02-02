/**
  ******************************************************************************
  * @file    sd_io_link.c
  * @author  MCD Application Team
  * @brief   This file provides set of firmware functions to manage microSD
  *
  * @note This file was modified by LucasHaug <lucas.haug@thunderat.org>, it's
  *       original name was stm32g0xx_nucleo.c
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

/* Includes ------------------------------------------------------------------*/
#include "sd_io_link.h"
#include "mem_card_platform.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup SD_IO_LINK
  * @{
  */

/** @defgroup SD_IO_LINK_Private_Defines Private Defines
  * @{
  */

/**
  * @brief LINK SD Card
  */
#define SD_DUMMY_BYTE            0xFF
#define SD_NO_RESPONSE_EXPECTED  0x80

/**
  * @}
  */

/** @defgroup SD_IO_LINK_BUS BUS Constants
  * @{
  */

/* Maximum Timeout values for flags waiting loops. These timeouts are not based
   on accurate values, they just guarantee that the application will not remain
   stuck if the SPI communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */
#define SPIx_TIMEOUT_MS                   1000U

/**
  * @}
  */

/** @defgroup SD_IO_LINK_Private_Variables Private Variables
  * @{
  */

/**
 * @brief BUS variables
 */

#ifdef HAL_SPI_MODULE_ENABLED
mem_card_platform_t card_setup;
#endif /* HAL_SPI_MODULE_ENABLED */

/**
  * @}
  */

/** @defgroup SD_IO_LINK_Private_Functions Private Functions
  * @{
  */
#ifdef HAL_SPI_MODULE_ENABLED

/* SD IO functions */
void                      SD_IO_Init(void);
void                      SD_IO_CSState(uint8_t state);
void                      SD_IO_WriteReadData(const uint8_t *DataIn, uint8_t *DataOut, uint16_t DataLength);
void                      SD_IO_ReadData(uint8_t *DataOut, uint16_t DataLength);
void                      SD_IO_WriteData(const uint8_t *Data, uint16_t DataLength);
uint8_t                   SD_IO_WriteByte(uint8_t Data);
uint8_t                   SD_IO_ReadByte(void);

/**
  * @}
  */

 /** @defgroup SD_IO_LINK_Exported_Functions
  * @{
  */

void mem_card_init(SPI_HandleTypeDef* hspi, GPIO_TypeDef* cs_port, uint16_t cs_pin) {
    card_setup.cs_port = cs_port;
    card_setup.cs_pin = cs_pin;
    card_setup.hspi = hspi;
    card_setup.spi_timeout = SPIx_TIMEOUT_MS;
}

/**
  * @}
  */

/** @addtogroup SD_IO_LINK_Private_Functions
  * @{
  */

/******************************************************************************
                            LINK OPERATIONS
*******************************************************************************/

/********************************* LINK SD ************************************/
/**
  * @brief  Initialize the SD Card and put it into StandBy State (Ready for
  *         data transfer).
  * @retval None
  */
void SD_IO_Init(void)
{
  uint8_t counter = 0;

  /* Send dummy byte 0xFF, 10 times with CS high */
  /* Rise CS and MOSI for 80 clocks cycles */
  for (counter = 0; counter <= 9; counter++)
  {
    /* Send dummy byte 0xFF */
    SD_IO_WriteByte(SD_DUMMY_BYTE);
  }
}

/**
  * @brief  Set the SD_CS pin.
  * @param  val: pin value.
  * @retval None
  */
void SD_IO_CSState(uint8_t val)
{
  if(val == 1)
  {
    SPIx_CS_High(&card_setup);
  }
  else
  {
    SPIx_CS_Low(&card_setup);
  }
}

/**
  * @brief  Write byte(s) on the SD
  * @param  DataIn: Pointer to data buffer to write
  * @param  DataOut: Pointer to data buffer for read data
  * @param  DataLength: number of bytes to write
  * @retval None
  */
void SD_IO_WriteReadData(const uint8_t *DataIn, uint8_t *DataOut, uint16_t DataLength)
{
  /* Send the byte */
  SPIx_WriteReadData(&card_setup, DataIn, DataOut, DataLength);
}

/**
  * @brief  Write a byte on the SD.
  * @param  Data: byte to send.
  * @retval Data written
  */
uint8_t SD_IO_WriteByte(uint8_t Data)
{
  uint8_t tmp;

  /* Send the byte */
  SPIx_WriteReadData(&card_setup, &Data,&tmp,1);
  return tmp;
  }

/**
  * @brief  Write an amount of data on the SD.
  * @param  DataOut: byte to send.
  * @param  DataLength: number of bytes to write
  * @retval none
  */
void SD_IO_ReadData(uint8_t *DataOut, uint16_t DataLength)
  {
  /* Send the byte */
  SD_IO_WriteReadData(DataOut, DataOut, DataLength);
}

/**
  * @brief  Write an amount of data on the SD.
  * @param  Data: byte to send.
  * @param  DataLength: number of bytes to write
  * @retval none
  */
void SD_IO_WriteData(const uint8_t *Data, uint16_t DataLength)
{
  /* Send the byte */
  SPIx_WriteData(&card_setup, (uint8_t *)Data, DataLength);
}

#endif /* HAL_SPI_MODULE_ENABLED */

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
