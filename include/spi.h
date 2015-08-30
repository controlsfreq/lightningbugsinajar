/**
 * @file   spi.h
 * @brief  This file contains the SPI driver declaration.
 * @author Liam Bucci <liam.bucci@gmail.com>
 * @date   2015-08-29
 * @copyright
 * {
 *     Copyright 2015 Liam Bucci
 *
 *     Licensed under the Apache License, Version 2.0 (the "License");
 *     you may not use this file except in compliance with the License.
 *     You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0
 *
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 * }
 */

#ifndef SPI_H
#define SPI_H

#include <stdbool.h>
#include "pin.h"

typedef enum spi_baud_
{
    SPI_BAUD_100K = 0U,
    SPI_BAUD_200K = 1U,
    SPI_BAUD_500K = 2U,
    SPI_BAUD_1M   = 3U
} spi_baud_t;

typedef struct spi_
{
    spi_baud_t baudrate;
    pin_t cs;
    pin_t mosi;
    pin_t miso;
    pin_t sclk;

} spi_t;

bool spi_init( spi_t * const spi );
bool spi_enable_cs( spi_t * const spi );
bool spi_disable_cs( spi_t * const spi );
bool spi_write_read( spi_t * const spi, char * const read_byte, const char write_byte );
bool spi_write( spi_t * const spi, const char write_byte );
bool spi_read( spi_t * const spi, char * const read_byte );

#endif /* SPI_H */