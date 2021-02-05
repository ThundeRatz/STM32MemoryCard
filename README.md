[![forthebadge](https://forthebadge.com/images/badges/open-source.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/for-you.svg)](https://forthebadge.com)

# STM32MemoryCard

Para a versão em PT-BR 🇧🇷 desse documento, [veja aqui](./README.pt-br.md).

## 📜 Index

- [🎉 Intro](#-intro)
- [➕ Requirements](#-requirements)
- [📦 Git Submodules](#-git-submodules)
  - [💥 Adding a submodule](#-adding-a-submodule)
  - [✅ Initializing an existing submodule](#-initializing-a-existing-submodule)
- [🔌 Hardware Configuration](#-hardware-configuration)
- [📚 Using the library](#-using-the-library)

## 🎉 Intro

This repository contains a library to link the CubeMX FATFS generated files with a SPI layer, in order to use a SPI based SDCard module with the microcontrollers of the [STM32](https://www.st.com/en/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus.html) family.

The CubeMX FATFS documentation can be found [here](docs/dm00105259-developing-applications-on-stm32cube-with-fatfs-stmicroelectronics.pdf). Most of the library files were develop by ST for an Adafruit shield and modified to be used in any SDCard application.

This library was made to be used as a submodule in the [STM32ProjectTemplate](https://github.com/ThundeRatz/STM32ProjectTemplate).

## ➕ Requirements

This library does not require any extra requirements to function, in addition to those already listed [STM32ProjectTemplate requirements](https://github.com/ThundeRatz/STM32ProjectTemplate#requisitos).

## 📦 Git Submodules

As stated, this library functions as a submodule. In this way, it is easier to choose the version of the library that will be used in the project, also allowing its development in parallel.

### 💥 Adding a submodule

Create a directory called `lib`, if it does not exist:

```bash
mkdir lib
```

And add the submodule by doing:

* With HTTPS:
```bash
git submodule add --name STM32MemoryCard https://github.com/ThundeRatz/STM32MemoryCard.git lib/STM32MemoryCard
```

* With SSH:
```bash
git submodule add --name STM32MemoryCard git@github.com:ThundeRatz/STM32MemoryCard.git lib/STM32MemoryCard
```

### ✅ Initializing an existing submodule

When cloning a repository that already has submodules, it is necessary to clone the repositories of that submodule. This can be done in two ways, by cloning together with the project repository or after you have already cloned.

Example:

To clone together, run the following command, switching to the repository link of your project:

```bash
git clone --recurse-submodules git@github.com:ThundeRatz/STM32ProjectTemplate.git
```

To clone having already cloned the project repository, within it, you should do:

```bash
git submodule update --init
```

## 🔌 Hardware Configuration

For this library, you need to configurate FATFS, SPI and one GPIO pin (the SPI chip select pin).

First open your CubeMX project, then to configure the FATFS open the "Middleware" section and enable the "user-defined" FATFS. After that, in the physical drive parameters, make sure the sector size (minimum and maximum) is 512.

For the SPI, open the "Connctivity" section and select the SPI you prefer and enable it in the "Full-Duplex-Master" mode. In the SPI parameter settings, set the data size to 8 bits and the baud rate to a maximum of 25 MHz.

Finally, to configure the CS pin, first choose one available GPIO pin and set it as "GPIO_Output". Then in the GPIO pins configuration section inside the "System Core" section, select your pin and configure the "Maximum output speed" to "Very high".

## 📚 Using the library

To use the library include the `app_fatfs_spi.h` header in your file and initialize the application with the following function:

```C
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
```

For exemple:

```C
APP_FATFS_SPI_Init(&hspi1, GPIOA, GPIO_PIN_10);
```

Note that the SPI and GPIO must have already been initialized before this function call.

The `app_fatfs_spi.h` header already includes the necessary files for the user to access FAT volumes. All functions available for handling FAT volumes are listed on page 13 of the[ST`s FATFS User Manual](docs/dm00105259-developing-applications-on-stm32cube-with-fatfs-stmicroelectronics.pdf).

An example code can be found [here](https://github.com/LucasHaug/SDCardTest).

---------------------

<img src="https://static.thunderatz.org/teamassets/logo-simples.png" width="200px" />
