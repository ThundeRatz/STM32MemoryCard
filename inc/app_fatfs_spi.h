/**
 * @file app_fatfs_spi.h
 *
 * @brief FATFS with SPI driver
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 01/2021
 */

#ifndef __APP_FATFS_SPI_H__
#define __APP_FATFS_SPI_H__

#include "app_fatfs.h"
#include "gpio.h"
#include "spi.h"

/*****************************************
 * Public Functions Prototypes
 *****************************************/

/**
 * @brief Initialize FATFS with SPI driver
 *
 * @note SPI and GPIO must have already been initialized
 *
 * @param hspi SPI instance handler
 * @param cs_port Chip select port
 * @param cs_pin Chip select pin number
 */
void APP_FATFS_SPI_Init(SPI_HandleTypeDef* hspi, GPIO_TypeDef* cs_port, uint16_t cs_pin);

#endif // __APP_FATFS_SPI_H__
