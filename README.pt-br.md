[![forthebadge](https://forthebadge.com/images/badges/open-source.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/for-you.svg)](https://forthebadge.com)

# STM32MemoryCard

## 📜 Índice

- [🎉 Introdução](#-introdução)
- [➕ Requisitos](#-requisitos)
- [📦 Submódulos com Git](#-submódulos-com-git)
  - [💥 Adicionando um submódulo](#-adicionando-um-submódulo)
  - [✅ Inicializando um submódulo já existente](#-inicializando-um-submódulo-já-existente)
- [🔌 Configuração de Hardware](#-configuração-de-hardware)
- [📚 Usando a biblioteca](#-usando-a-biblioteca)

## 🎉 Introdução

Esse repositório contém uma biblioteca para conectar os arquivos de FATFS gerados pelo CubeMX com uma camada de SPI, para que se possa usar um módulo de SDCard baseado em SPI com os microcontroladores da família [STM32](https://www.st.com/en/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus.html).

A documentação do CubeMX para FATFS pode ser encontrada [aqui](docs/dm00105259-developing-applications-on-stm32cube-with-fatfs-stmicroelectronics.pdf). A maior parte dos aquivos dessa biblioteca foram desenvolvidos pela ST para um shild da Adafruit e foram modificados para que se fosse possível utilizá-los para qualquer aplicação com um SDCard.

Essa biblioteca foi feita para ser utilizada como submódulo no [STM32ProjectTemplate](https://github.com/ThundeRatz/STM32ProjectTemplate).

## ➕ Requisitos

Essa biblioteca não requer, para funcionar, nenhum requisito extra, além dos já listados [requisitos do STM32ProjectTemplate](https://github.com/ThundeRatz/STM32ProjectTemplate#requisitos).

## 📦 Submódulos com Git

Como dito, essa biblioteca funciona como um submódulo. Dessa forma se facilita escolher a versão da biblioteca que será utilizada no projeto, permitindo também o desenvolvimento em paralelo dela.

### 💥 Adicionando um submódulo

Crie um diretório chamado `lib`, caso não exista:

```bash
mkdir lib
```

E adicione o submódulo fazendo:

* Com HTTPS:
```bash
git submodule add --name STM32MemoryCard https://github.com/ThundeRatz/STM32MemoryCard.git lib/STM32MemoryCard
```

* Com SSH:
```bash
git submodule add --name STM32MemoryCard git@github.com:ThundeRatz/STM32MemoryCard.git lib/STM32MemoryCard
```

### ✅ Inicializando um submódulo já existente

Ao clonar um repositório que já tenha submódulos, é necessário clonar os repositórios desse submódulo. Isso pode ser feito de duas formas, clonando junto com o repositório do projeto ou depois de já ter clonado.

Exemplo:

Para se clonar junto, rode o seguinte comando, trocando para o link do repositório do seu projeto:

```bash
git clone --recurse-submodules git@github.com:ThundeRatz/STM32ProjectTemplate.git
```

Para se clonar depois de já ter clonado o repositório do projeto, dentro dele, deve-se fazer:

```bash
git submodule update --init
```

## 🔌 Configuração de Hardware

Para esta biblioteca, você precisa configurar o FATFS, o SPI e um pino GPIO (o pino de seleção do chip SPI).

Primeiro abra seu projeto do CubeMX, então para configurar o FATFS abra a seção "Middleware" e habilite o FATFS como "user-defined". Depois disso, nos parâmetros do drive físico, verifique se o tamanho do setor (mínimo e máximo) é 512.

Para o SPI, abra a seção "Connctivity" e selecione o SPI de sua preferência e habilite-o no modo "Full-Duplex-Master". Nas configurações dos parâmetros do SPI, defina o tamanho dos dados para 8 bits e a taxa de transmissão para um máximo de 25 MHz.

Finalmente, para configurar o pino CS, primeiro escolha um pino GPIO disponível e defina-o como "GPIO_Output". Em seguida, na seção de configuração dos pinos GPIO dentro da seção "System Core", selecione seu pino e configure a "Maximum output speed" para "Very high".

## 📚 Usando a biblioteca

Para usar a biblioteca, inclua o cabeçalho `app_fatfs_spi.h` em seu arquivo e inicialize sua aplicação com a seguinte função:

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

Por exemplo:

```C
APP_FATFS_SPI_Init(&hspi1, GPIOA, GPIO_PIN_10);
```

Observe que o SPI e o GPIO já devem ter sido inicializados antes desta chamada de função.

O cabeçalho `app_fatfs_spi.h` já inclui os arquivos necessários para o usuário acessar os volumes FAT. Todas as funções disponíveis para lidar com os volumes FAT estão listadas na página 13 do [Manual do usuário para FATFS da ST](docs/dm00105259-developing-applications-on-stm32cube-with-fatfs-stmicroelectronics.pdf).

Um exemplo de código pode ser encontrado [aqui](https://github.com/LucasHaug/SDCardTest).

---------------------

<img src="https://static.thunderatz.org/teamassets/logo-simples.png" width="200px" />
