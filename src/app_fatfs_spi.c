/**
 * @file app_fatfs_spi.c
 *
 * @brief FATFS with SPI driver
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 01/2021
 */

#include "app_fatfs_spi.h"

#include "sd_diskio.h"
#include "user_diskio.h"

#include "sd_io_link.h"

/*****************************************
 * Public Functions Bodies Definitions
 *****************************************/

void APP_FATFS_SPI_Init(SPI_HandleTypeDef* hspi, GPIO_TypeDef* cs_port, uint16_t cs_pin) {
    mem_card_init(hspi, cs_port, cs_pin);

    USER_Driver = SD_Driver;
    MX_FATFS_Init();
}
