/**
 * @file mem_card_platform.c
 *
 * @brief Memory card SPI platform related.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 * @author Lucas Schneider <lucas.schneider@thunderatz.org>
 *
 * @date 01/2021
 */

#include "mem_card_platform.h"

/*****************************************
 * Private Functions Prototypes
 *****************************************/

/**
 * @brief  SPI error treatment function
 *
 * @retval None
 */
void SPIx_Error(mem_card_platform_t* pSetup);

/*****************************************
 * Public Functions Bodies Definitions
 *****************************************/

void SPIx_CS_Low(mem_card_platform_t* pSetup) {
    HAL_GPIO_WritePin(pSetup->cs_port, pSetup->cs_pin, GPIO_PIN_RESET);
}

void SPIx_CS_High(mem_card_platform_t* pSetup) {
    HAL_GPIO_WritePin(pSetup->cs_port, pSetup->cs_pin, GPIO_PIN_SET);
}

void SPIx_WriteReadData(mem_card_platform_t* pSetup, const uint8_t* DataIn, uint8_t* DataOut, uint16_t DataLength) {
    HAL_StatusTypeDef status = HAL_OK;

    status = HAL_SPI_TransmitReceive(pSetup->hspi, (uint8_t*) DataIn, DataOut, DataLength, pSetup->spi_timeout);

    /* Check the communication status */
    if (status != HAL_OK) {
        /* Execute user timeout callback */
        SPIx_Error(pSetup);
    }
}

void SPIx_WriteData(mem_card_platform_t* pSetup, uint8_t* DataIn, uint16_t DataLength) {
    HAL_StatusTypeDef status = HAL_OK;

    status = HAL_SPI_Transmit(pSetup->hspi, DataIn, DataLength, pSetup->spi_timeout);

    /* Check the communication status */
    if (status != HAL_OK) {
        /* Execute user timeout callback */
        SPIx_Error(pSetup);
    }
}

/*****************************************
 * Private Functions Bodies Definitions
 *****************************************/

void SPIx_Error(mem_card_platform_t* pSetup) {
    /* De-initialize the SPI communication BUS */
    HAL_SPI_DeInit(pSetup->hspi);

    /* Re-Initiaize the SPI communication BUS */
    HAL_SPI_Init(pSetup->hspi);
}
