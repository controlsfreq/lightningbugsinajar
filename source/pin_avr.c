/**
 * @file   pin_avr.c
 * @brief  This file contains AVR pin function definitions.
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

#include <stdbool.h>
#include <stddef.h>
#include <avr/io.h>
#include "pin.h"


/* API Function Definitions ==================================================================== */

/**
 * @brief Set the pin mode.
 */
bool pin_set_mode( const pin_t * const pin, const pin_mode_t mode )
{
    bool retval = false;

    if( pin != NULL )
    {
        switch( pin->bank )
        {
        case PIN_BANK_A:
            break;

        case PIN_BANK_B:
            if( mode == PIN_MODE_INPUT )
            {
                DDRB &= ~(1<<(pin->num));
                retval = true;
            }
            else if( mode == PIN_MODE_OUTPUT )
            {
                DDRB |= (1<<(pin->num));
                retval = true;
            }
            else if( mode == PIN_MODE_ALTERNATE )
            {
                /* Nothing to do */
                retval = true;
            }
            else
            {
                /* Unknown mode, default to an error */
            }

            break;

        case PIN_BANK_C: /* Intentional fall-through */
        case PIN_BANK_D: /* Intentional fall-through */
        case PIN_BANK_E: /* Intentional fall-through */
        case PIN_BANK_F: /* Intentional fall-through */
        case PIN_BANK_G: /* Intentional fall-through */
        case PIN_BANK_H: /* Intentional fall-through */
        default:
            break;
        }
    }

    return retval;
}

/**
 * @brief Set the pin's pull up or pull down setting.
 */
bool pin_set_pupd( const pin_t * const pin, const pin_pupd_t pupd )
{
    bool retval = false;

    if( pin != NULL )
    {
        switch( pin->bank )
        {
        case PIN_BANK_A:
            break;

        case PIN_BANK_B:
            if( pupd == PIN_PUPD_NONE )
            {
                PORTB &= ~(1<<(pin->num));
                retval = true;
            }
            else if( pupd == PIN_PUPD_PULLUP )
            {
                PORTB |= (1<<(pin->num));
                retval = true;
            }
            else
            {
                /* Unknown or invalid pupd, default to an error */
            }

            break;

        case PIN_BANK_C: /* Intentional fall-through */
        case PIN_BANK_D: /* Intentional fall-through */
        case PIN_BANK_E: /* Intentional fall-through */
        case PIN_BANK_F: /* Intentional fall-through */
        case PIN_BANK_G: /* Intentional fall-through */
        case PIN_BANK_H: /* Intentional fall-through */
        default:
            break;
        }
    }

    return retval;
}

/**
 * @brief Read the value at the pin (whether input or output).
 */
bool pin_read( const pin_t * const pin, bool * const is_asserted )
{
    bool retval = false;

    if( (pin != NULL) &&
        (is_asserted != NULL) )
    {
        switch( pin->bank )
        {
        case PIN_BANK_A:
            break;

        case PIN_BANK_B:
            *is_asserted = (PINB & (1<<(pin->num)));
            retval = true;

            break;

        case PIN_BANK_C: /* Intentional fall-through */
        case PIN_BANK_D: /* Intentional fall-through */
        case PIN_BANK_E: /* Intentional fall-through */
        case PIN_BANK_F: /* Intentional fall-through */
        case PIN_BANK_G: /* Intentional fall-through */
        case PIN_BANK_H: /* Intentional fall-through */
        default:
            break;
        }
    }

    return retval;
}

/**
 * @brief Assert the pin (output only).
 */
bool pin_assert( const pin_t * const pin )
{
    bool retval = false;

    if( pin != NULL )
    {
        switch( pin->bank )
        {
        case PIN_BANK_A:
            break;

        case PIN_BANK_B:
            PORTB = pin->is_asserted_low ? (PORTB & ~(1<<(pin->num))) : (PORTB | (1<<(pin->num)));
            retval = true;

            break;

        case PIN_BANK_C: /* Intentional fall-through */
        case PIN_BANK_D: /* Intentional fall-through */
        case PIN_BANK_E: /* Intentional fall-through */
        case PIN_BANK_F: /* Intentional fall-through */
        case PIN_BANK_G: /* Intentional fall-through */
        case PIN_BANK_H: /* Intentional fall-through */
        default:
            break;
        }
    }

    return retval;
}

/**
 * @brief Deassert the pin (output only).
 */
bool pin_deassert( const pin_t * const pin )
{
    bool retval = false;

    if( pin != NULL )
    {
        switch( pin->bank )
        {
        case PIN_BANK_A:
            break;

        case PIN_BANK_B:
            PORTB = pin->is_asserted_low ? (PORTB | (1<<(pin->num))) : (PORTB & ~(1<<(pin->num)));
            retval = true;

            break;

        case PIN_BANK_C: /* Intentional fall-through */
        case PIN_BANK_D: /* Intentional fall-through */
        case PIN_BANK_E: /* Intentional fall-through */
        case PIN_BANK_F: /* Intentional fall-through */
        case PIN_BANK_G: /* Intentional fall-through */
        case PIN_BANK_H: /* Intentional fall-through */
        default:
            break;
        }
    }

    return retval;
}

/**
 * @brief Toggle the value of the pin (output only).
 */
bool pin_toggle( const pin_t * const pin )
{
    bool retval = false;

    if( pin != NULL )
    {
        switch( pin->bank )
        {
        case PIN_BANK_A:
            break;

        case PIN_BANK_B:
            PINB |= (1<<(pin->num));
            retval = true;

            break;

        case PIN_BANK_C: /* Intentional fall-through */
        case PIN_BANK_D: /* Intentional fall-through */
        case PIN_BANK_E: /* Intentional fall-through */
        case PIN_BANK_F: /* Intentional fall-through */
        case PIN_BANK_G: /* Intentional fall-through */
        case PIN_BANK_H: /* Intentional fall-through */
        default:
            break;
        }
    }

    return retval;
}
