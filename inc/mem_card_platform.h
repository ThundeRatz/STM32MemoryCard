/**
 * @file mem_card_platform.h
 *
 * @brief Memory card SPI platform related.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 * @author Lucas Schneider <lucas.schneider@thunderatz.org>
 *
 * @date 01/2021
 */

#ifndef __MEM_CARD_PLATFORM_H__
#define __MEM_CARD_PLATFORM_H__

#include <stdint.h>

#include "gpio.h"
#include "spi.h"

/*****************************************
 * Public Types
 *****************************************/

/**
 * @brief Platform hardware related.
 */
typedef struct mem_card_platform {
    GPIO_TypeDef*      cs_port;
    uint16_t           cs_pin;

    SPI_HandleTypeDef* hspi;
    uint16_t           spi_timeout;
} mem_card_platform_t;

/*****************************************
 * Public Functions Prototypes
 *****************************************/

/**
 * @brief Set chip select low
 *
 * @param pSetup: poiter to devide setup
 */
void SPIx_CS_Low(mem_card_platform_t* pSetup);

/**
 * @brief Set chip select high
 *
 * @param pSetup: poiter to devide setup
 */
void SPIx_CS_High(mem_card_platform_t* pSetup);

/**
  * @brief  SPI Write a byte to device
  *
  * @param  pSetup: poiter to devide setup
  * @param  DataIn: value to be written
  * @param  DataOut: read value
  * @param  DataLength: value data length
  *
  * @retval None
  */
void SPIx_WriteReadData(mem_card_platform_t* pSetup, const uint8_t *DataIn, uint8_t *DataOut, uint16_t DataLength);

/**
  * @brief  SPI Write an amount of data to device
  *
  * @param  pSetup: poiter to devide setup
  * @param  DataIn: value to be written
  * @param  DataLength: number of bytes to write
  *
  * @retval None
  */
void SPIx_WriteData(mem_card_platform_t* pSetup, uint8_t *DataIn, uint16_t DataLength);

#endif // __MEM_CARD_PLATFORM_H__
