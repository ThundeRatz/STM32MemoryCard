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

/** @defgroup SD_IO_LINK_Private_Variables Private Variables
  * @{
  */

/**
 * @brief BUS variables
 */

#ifdef HAL_SPI_MODULE_ENABLED
uint32_t SpixTimeout = NUCLEO_SPIx_TIMEOUT_MAX; /*<! Value of Timeout when SPI communication fails */
static SPI_HandleTypeDef hnucleo_Spi;
#endif /* HAL_SPI_MODULE_ENABLED */

/**
  * @}
  */

/** @defgroup SD_IO_LINK_Private_Functions Private Functions
  * @{
  */
#ifdef HAL_SPI_MODULE_ENABLED
static void               SPIx_Init(void);
static void               SPIx_Write(uint8_t Value);
static void               SPIx_WriteData(uint8_t *DataIn, uint16_t DataLength);
static void               SPIx_WriteReadData(const uint8_t *DataIn, uint8_t *DataOut, uint16_t DataLegnth);
static void               SPIx_Error (void);
static void               SPIx_MspInit(void);

/* SD IO functions */
void                      SD_IO_Init(void);
void                      SD_IO_CSState(uint8_t state);
void                      SD_IO_WriteReadData(const uint8_t *DataIn, uint8_t *DataOut, uint16_t DataLength);
void                      SD_IO_ReadData(uint8_t *DataOut, uint16_t DataLength);
void                      SD_IO_WriteData(const uint8_t *Data, uint16_t DataLength);
uint8_t                   SD_IO_WriteByte(uint8_t Data);
uint8_t                   SD_IO_ReadByte(void);

#endif /* HAL_SPI_MODULE_ENABLED */
/**
  * @}
  */

/** @addtogroup SD_IO_LINK_Private_Functions
  * @{
  */

#ifdef HAL_SPI_MODULE_ENABLED
/******************************************************************************
                            BUS OPERATIONS
*******************************************************************************/

/**
  * @brief  SPI Write a byte to device
  * @param  DataIn: value to be written
  * @param  DataOut: read value
  * @param  DataLength: value data length
  * @retval None
  */
static void SPIx_WriteReadData(const uint8_t *DataIn, uint8_t *DataOut, uint16_t DataLength)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_SPI_TransmitReceive(&hnucleo_Spi, (uint8_t*) DataIn, DataOut, DataLength, SpixTimeout);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    SPIx_Error();
  }
}

/**
  * @brief  SPI Write an amount of data to device
  * @param  DataIn: value to be written
  * @param  DataLength: number of bytes to write
  * @retval None
  */
static void SPIx_WriteData(uint8_t *DataIn, uint16_t DataLength)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_SPI_Transmit(&hnucleo_Spi, DataIn, DataLength, SpixTimeout);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    SPIx_Error();
  }
}

/**
  * @brief  SPI Write a byte to device
  * @param  Value: value to be written
  * @retval None
  */
static void SPIx_Write(uint8_t Value)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint8_t data;

  status = HAL_SPI_TransmitReceive(&hnucleo_Spi, (uint8_t*) &Value, &data, 1, SpixTimeout);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    SPIx_Error();
  }
}

/**
  * @brief  SPI error treatment function
  * @retval None
  */
static void SPIx_Error (void)
{
  /* De-initialize the SPI communication BUS */
  HAL_SPI_DeInit(&hnucleo_Spi);

  /* Re-Initiaize the SPI communication BUS */
  SPIx_Init();
}

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
  GPIO_InitTypeDef  gpioinitstruct = {0};
  uint8_t counter = 0;

  /* SD_CS_PIN and LCD_CS_PIN Periph clock enable */
  SD_CS_GPIO_CLK_ENABLE();
  LCD_CS_GPIO_CLK_ENABLE();

  /* Set chip selects to high before IO init in order to be sure no transition to 0 occurs */
  SD_CS_HIGH();

  /* Configure SD_CS_PIN pin: SD Card CS pin */
  gpioinitstruct.Pin = SD_CS_PIN;
  gpioinitstruct.Mode = GPIO_MODE_OUTPUT_PP;
  gpioinitstruct.Pull = GPIO_PULLUP;
  gpioinitstruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(SD_CS_GPIO_PORT, &gpioinitstruct);

  /* Configure LCD_CS_PIN pin: LCD CS pin */
  gpioinitstruct.Pin   = LCD_CS_PIN;
  HAL_GPIO_Init(SD_CS_GPIO_PORT, &gpioinitstruct);

  /* SD SPI Config */
  SPIx_Init();

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
    SD_CS_HIGH();
  }
  else
  {
    SD_CS_LOW();
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
  SPIx_WriteReadData(DataIn, DataOut, DataLength);
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
  SPIx_WriteReadData(&Data,&tmp,1);
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
  SPIx_WriteData((uint8_t *)Data, DataLength);
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
