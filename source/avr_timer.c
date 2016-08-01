/**
 * @file   avr_timer.c
 * @brief  This file contains the AVR timer1 driver implementation.
 * @author Liam Bucci <liam.bucci@gmail.com>
 * @date   2015-09-13
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

#include "timer.h"


bool timer_init( const timer_t * const ptimer )
{
    bool retval = false;

    if( ptimer != NULL )
    {
        switch( ptimer->number )
        {
        case TIMER_NUM_0:
            /* Not implemented yet */

            break;

        case TIMER_NUM_1:
            /* Timer/counter1 */
            /* Pause timer and set reset on match option */
            TCCR1 = ptimer->reset_on_match ? TCCR1 | (1<<CTC1) : TCCR1 & ~(1<<CTC1);

            /* Reset prescaler */
            GTCCR = (1<<PSR1);

            /* Reset timer value */
            TCNT1 = 0x00U;

            /* Reset compare values */
            OCR1A = 0x00U;
            OCR1B = 0x00U;
            OCR1C = 0x00U;

            retval = true;

            break;

        case TIMER_NUM_2: /* Intentional fallthrough */
        case TIMER_NUM_3: /* Intentional fallthrough */
        case TIMER_NUM_4: /* Intentional fallthrough */
        case TIMER_NUM_5: /* Intentional fallthrough */
        case TIMER_NUM_6: /* Intentional fallthrough */
        case TIMER_NUM_7: /* Intentional fallthrough */
        default:
            /* Unknown timer */
            break;
        }
    }

    return retval;
}

bool timer_enable_int( const timer_t * const ptimer )
{
    bool retval = false;

    if( ptimer != NULL )
    {
        switch( ptimer->number )
        {
        case TIMER_NUM_0:
            /* Not implemented yet */

            break;

        case TIMER_NUM_1:
            /* Timer/counter1 */
            /* Enable OCIE1A interrupt */
            TIMSK |= (1<<OCIE1A);

            break;

        case TIMER_NUM_2: /* Intentional fallthrough */
        case TIMER_NUM_3: /* Intentional fallthrough */
        case TIMER_NUM_4: /* Intentional fallthrough */
        case TIMER_NUM_5: /* Intentional fallthrough */
        case TIMER_NUM_6: /* Intentional fallthrough */
        case TIMER_NUM_7: /* Intentional fallthrough */
        default:
            /* Unknown timer */
            break;
        }
    }

    return retval;
}

bool timer_disable_int( const timer_t * const ptimer )
{
    bool retval = false;

    if( ptimer != NULL )
    {
        switch( ptimer->number )
        {
        case TIMER_NUM_0:
            /* Not implemented yet */

            break;

        case TIMER_NUM_1:
            /* Timer/counter1 */
            /* Disable OCIE1A interrupt */
            TIMSK &= ~(1<<OCIE1A);

            break;

        case TIMER_NUM_2: /* Intentional fallthrough */
        case TIMER_NUM_3: /* Intentional fallthrough */
        case TIMER_NUM_4: /* Intentional fallthrough */
        case TIMER_NUM_5: /* Intentional fallthrough */
        case TIMER_NUM_6: /* Intentional fallthrough */
        case TIMER_NUM_7: /* Intentional fallthrough */
        default:
            /* Unknown timer */
            break;
        }
    }

    return retval;
}

bool timer_start( const timer_t * const ptimer )
{
    bool retval = false;

    if( ptimer != NULL )
    {
        switch( ptimer->number )
        {
        case TIMER_NUM_0:
            /* Not implemented yet */

            break;

        case TIMER_NUM_1:
            /* Timer/counter1 */
            /* Set prescaler configuration (which starts timer) */
            TCCR1 |= ptimer->prescaler;

            retval = true;

            break;

        case TIMER_NUM_2: /* Intentional fallthrough */
        case TIMER_NUM_3: /* Intentional fallthrough */
        case TIMER_NUM_4: /* Intentional fallthrough */
        case TIMER_NUM_5: /* Intentional fallthrough */
        case TIMER_NUM_6: /* Intentional fallthrough */
        case TIMER_NUM_7: /* Intentional fallthrough */
        default:
            /* Unknown timer */
            break;
        }
    }

    return retval;
}

bool timer_pause( const timer_t * const ptimer )
{
    bool retval = false;

    if( ptimer != NULL )
    {
        switch( ptimer->number )
        {
        case TIMER_NUM_0:
            /* Not implemented yet */

            break;

        case TIMER_NUM_1:
            /* Timer/counter1 */
            /* Clear prescaler configuration (which pauses timer) */
            TCCR1 &= ~( (1<<CS13) | (1<<CS12) | (1<<CS11) | (1<<CS10) );

            retval = true;

            break;

        case TIMER_NUM_2: /* Intentional fallthrough */
        case TIMER_NUM_3: /* Intentional fallthrough */
        case TIMER_NUM_4: /* Intentional fallthrough */
        case TIMER_NUM_5: /* Intentional fallthrough */
        case TIMER_NUM_6: /* Intentional fallthrough */
        case TIMER_NUM_7: /* Intentional fallthrough */
        default:
            /* Unknown timer */
            break;
        }
    }

    return retval;
}

bool timer_reset( const timer_t * const ptimer )
{
    bool retval = false;

    if( ptimer != NULL )
    {
        switch( ptimer->number )
        {
        case TIMER_NUM_0:
            /* Not implemented yet */

            break;

        case TIMER_NUM_1:
            /* Timer/counter1 */
            /* Clear prescaler configuration (which pauses timer) */
            TCCR1 &= ~( (1<<CS13) | (1<<CS12) | (1<<CS11) | (1<<CS10) );

            /* Reset prescaler */
            GTCCR = (1<<PSR1);

            /* Reset timer value */
            TCNT1 = 0x00U;

            retval = true;

            break;

        case TIMER_NUM_2: /* Intentional fallthrough */
        case TIMER_NUM_3: /* Intentional fallthrough */
        case TIMER_NUM_4: /* Intentional fallthrough */
        case TIMER_NUM_5: /* Intentional fallthrough */
        case TIMER_NUM_6: /* Intentional fallthrough */
        case TIMER_NUM_7: /* Intentional fallthrough */
        default:
            /* Unknown timer */
            break;
        }
    }

    return retval;
}

bool timer_set_compare( const timer_t * const ptimer, const uint8_t value )
{
    bool retval = false;

    if( ptimer != NULL )
    {
        switch( ptimer->number )
        {
        case TIMER_NUM_0:
            /* Not implemented yet */

            break;

        case TIMER_NUM_1:
            /* Timer/counter1 */
            /* Set OCR1A as the normal match register  */
            OCR1A = value;

            /* Set OCR1C as the reset on match register */
            OCR1C = value;

            retval = true;

            break;

        case TIMER_NUM_2: /* Intentional fallthrough */
        case TIMER_NUM_3: /* Intentional fallthrough */
        case TIMER_NUM_4: /* Intentional fallthrough */
        case TIMER_NUM_5: /* Intentional fallthrough */
        case TIMER_NUM_6: /* Intentional fallthrough */
        case TIMER_NUM_7: /* Intentional fallthrough */
        default:
            /* Unknown timer */
            break;
        }
    }

    return retval;
}

bool timer_get_compare( const timer_t * const ptimer, uint8_t * const pvalue )
{
    bool retval = false;

    if( (ptimer != NULL) &&
        (pvalue != NULL) )
    {
        switch( ptimer->number )
        {
        case TIMER_NUM_0:
            /* Not implemented yet */

            break;

        case TIMER_NUM_1:
            /* Timer/counter1 */
            /* Get OCR1A as the normal match register  */
            *pvalue = OCR1A;

            retval = true;

            break;

        case TIMER_NUM_2: /* Intentional fallthrough */
        case TIMER_NUM_3: /* Intentional fallthrough */
        case TIMER_NUM_4: /* Intentional fallthrough */
        case TIMER_NUM_5: /* Intentional fallthrough */
        case TIMER_NUM_6: /* Intentional fallthrough */
        case TIMER_NUM_7: /* Intentional fallthrough */
        default:
            /* Unknown timer */
            break;
        }
    }

    return retval;
}

bool timer_set_timer( const timer_t * const ptimer, const uint8_t value )
{
    bool retval = false;

    if( ptimer != NULL )
    {
        switch( ptimer->number )
        {
        case TIMER_NUM_0:
            /* Not implemented yet */

            break;

        case TIMER_NUM_1:
            /* Timer/counter1 */
            /* Reset prescaler */
            GTCCR = (1<<PSR1);

            /* Set new timer value */
            TCNT1 = value;

            retval = true;

            break;

        case TIMER_NUM_2: /* Intentional fallthrough */
        case TIMER_NUM_3: /* Intentional fallthrough */
        case TIMER_NUM_4: /* Intentional fallthrough */
        case TIMER_NUM_5: /* Intentional fallthrough */
        case TIMER_NUM_6: /* Intentional fallthrough */
        case TIMER_NUM_7: /* Intentional fallthrough */
        default:
            /* Unknown timer */
            break;
        }
    }

    return retval;
}

bool timer_get_timer( const timer_t * const ptimer, uint8_t * const pvalue )
{
    bool retval = false;

    if( (ptimer != NULL) &&
        (pvalue != NULL) )
    {
        switch( ptimer->number )
        {
        case TIMER_NUM_0:
            /* Not implemented yet */

            break;

        case TIMER_NUM_1:
            /* Timer/counter1 */
            /* Get current timer value */
            *pvalue = TCNT1;

            retval = true;

            break;

        case TIMER_NUM_2: /* Intentional fallthrough */
        case TIMER_NUM_3: /* Intentional fallthrough */
        case TIMER_NUM_4: /* Intentional fallthrough */
        case TIMER_NUM_5: /* Intentional fallthrough */
        case TIMER_NUM_6: /* Intentional fallthrough */
        case TIMER_NUM_7: /* Intentional fallthrough */
        default:
            /* Unknown timer */
            break;
        }
    }

    return retval;
}