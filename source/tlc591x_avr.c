/**
 * @file   tlc591x_avr.c
 * @brief  This file contains the TLC591x driver implementation for the AVR.
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
#include <stdint.h>
#include "spi.h"
#include "tlc591x.h"

bool tlc591x_init( tlc591x_t * const tlc )
{
    bool retval = false;

    if( tlc != NULL )
    {
        /* Initialize SPI device */
        retval = spi_init( &(tlc->spi) );

        /* Initialize LE pin */
        if( retval == true )
        {
            retval = pin_set_mode( &(tlc->le), PIN_MODE_OUTPUT );
            retval = pin_deassert( &(tlc->le) ) && retval;
        }

        /* Initialize nOE pin */
        if( retval == true )
        {
            retval = pin_set_mode( &(tlc->oe_), PIN_MODE_OUTPUT );
            retval = pin_deassert( &(tlc->oe_) ) && retval;
        }
    }

    return retval;
}

bool tlc591x_enable_output( tlc591x_t * const tlc )
{
    bool retval = false;

    if( tlc != NULL )
    {
        retval = pin_assert( &(tlc->oe_) );
    }

    return retval;
}

bool tlc591x_disable_output( tlc591x_t * const tlc )
{
    bool retval = false;

    if( tlc != NULL )
    {
        retval = pin_deassert( &(tlc->oe_) );
    }

    return retval;
}

bool tlc591x_write_values( tlc591x_t * const tlc, const uint8_t values )
{
    bool retval = false;

    if( tlc != NULL )
    {
        retval = spi_write( &(tlc->spi), values );

        if( retval == true )
        {
            retval = pin_assert( &(tlc->le) );
            retval = pin_deassert( &(tlc->le) ) && retval;
        }
    }

    return retval;
}