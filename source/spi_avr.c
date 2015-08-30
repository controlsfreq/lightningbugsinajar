/**
 * @file   spi_avr.c
 * @brief  This file contains the AVR spi driver implementation.
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

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>
#include "spi.h"

/* API Function Definitions ==================================================================== */

bool spi_init( spi_t * const spi )
{
    bool retval = false;

    if( spi != NULL )
    {
        /* Initialize CS pin */
        retval = pin_set_mode( &(spi->cs), PIN_MODE_OUTPUT );
        retval = pin_deassert( &(spi->cs) ) && retval;

        /* Initialize MOSI pin */
        if( retval == true )
        {
            retval = pin_set_mode( &(spi->mosi), PIN_MODE_OUTPUT );
            retval = pin_deassert( &(spi->mosi) ) && retval;
        }

        /* Initialize MISO pin */
        if( retval == true )
        {
            retval = pin_set_mode( &(spi->miso), PIN_MODE_INPUT );
        }

        /* Initialize SCLK pin */
        if( retval == true )
        {
            retval = pin_set_mode( &(spi->sclk), PIN_MODE_OUTPUT );
            retval = pin_deassert( &(spi->sclk) ) && retval;
        }

        /* Initialize USI registers */
        if( retval == true )
        {
            /* Three-wire mode, USI software clock */
            USICR = (1<<USIWM0) | (1<<USICLK);
        }
    }

    return retval;
}

bool spi_enable_cs( spi_t * const spi )
{
    bool retval = false;

    if( spi != NULL )
    {
        /* Assert CS pin */
        retval = pin_assert( &(spi->cs) );
    }

    return retval;
}

bool spi_disable_cs( spi_t * const spi )
{
    bool retval = false;

    if( spi != NULL )
    {
        /* Deassert CS pin */
        retval = pin_deassert( &(spi->cs) );
    }

    return retval;
}

bool spi_write_read( spi_t * const spi, char * const read_byte, const char write_byte )
{
    bool retval = false;

    if( (spi != NULL) &&
        (read_byte != NULL) )
    {

        /* Write byte to USI register */
        USIDR = write_byte;

        /* Clear 4-bit counter and overflow flag */
        USISR = (1<<USIOIF);

        while( (USISR & (1<<USIOIF)) == 0 )
        {
            /* Strobe clock and shift next bit out */
            USICR = (1<<USIWM0) | (1<<USICS1) | (1<<USICLK) | (1<<USITC);
        }

        *read_byte = USIDR;

        retval = true;
    }

    return retval;
}

bool spi_write( spi_t * const spi, const char write_byte )
{
    char dummy_read;

    return spi_write_read( spi, &dummy_read, write_byte );
}

bool spi_read( spi_t * const spi, char * const read_byte )
{
    return spi_write_read( spi, read_byte, 0U );
}