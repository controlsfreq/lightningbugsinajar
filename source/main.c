/**
 * @file   main.c
 * @brief  This file contains the main entry point to the LED Bugs In A Jar application.
 * @author Liam Bucci <liam.bucci@gmail.com>
 * @date   2015-08-23
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

#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "pin.h"
#include "spi.h"
#include "tlc591x.h"
#include "controller.h"
#include "timer.h"

volatile uint8_t g_timer_counter = 0;

pin_t debug_pin = {
    PIN_BANK_B,
    PIN_NUM_3,
    false
};

int main( int argc, char *argv[] )
{
	//char major_version = LBJ_MAJOR_VERSION;
	//char minor_version = LBJ_MINOR_VERSION;
	//char patch_version = LBJ_PATCH_VERSION;

    timer_t timer1 = {
        TIMER_NUM_1,
        TIMER_PRE_8,
        true
    };

    spi_t spi = {
        SPI_BAUD_1M,
        {
            PIN_BANK_B,
            PIN_NUM_3,
            true
        }, // SPI CS
        {
            PIN_BANK_B,
            PIN_NUM_1,
            false
        }, // SPI MOSI
        {
            PIN_BANK_B,
            PIN_NUM_0,
            false
        }, // SPI MISO
        {
            PIN_BANK_B,
            PIN_NUM_2,
            false
        } // SPI SCLK
    };

    tlc591x_t tlc = {
        spi,
        { PIN_BANK_B, PIN_NUM_0, true },
        { PIN_BANK_B, PIN_NUM_4, false }
    };

    (void)timer_init( &timer1 );
    (void)timer_set_compare( &timer1, 125 );
    (void)tlc591x_init( &tlc );
    (void)tlc591x_enable_output( &tlc );

    sei();

    (void)timer_enable_int( &timer1 );
    (void)timer_start( &timer1 );

    (void)controller_init( &tlc );
    (void)controller_loop();

	return 0;
}



ISR(INT0_vect)
{
    (void)pin_assert( &debug_pin );
    while(1); /* Trap */
}

ISR(PCINT0_vect)
{
    (void)pin_assert( &debug_pin );
    while(1); /* Trap */
}

ISR(TIM1_OVF_vect)
{
    (void)pin_assert( &debug_pin );
    while(1); /* Trap */
}

ISR(TIM0_OVF_vect)
{
    (void)pin_assert( &debug_pin );
    while(1); /* Trap */
}

ISR(EE_RDY_vect)
{
    (void)pin_assert( &debug_pin );
    while(1); /* Trap */
}

ISR(ANA_COMP_vect)
{
    (void)pin_assert( &debug_pin );
    while(1); /* Trap */
}

ISR(ADC_vect)
{
    (void)pin_assert( &debug_pin );
    while(1); /* Trap */
}

ISR(TIM1_COMPB_vect)
{
    (void)pin_assert( &debug_pin );
    while(1); /* Trap */
}

ISR(TIM0_COMPA_vect)
{
    (void)pin_assert( &debug_pin );
    while(1); /* Trap */
}

ISR(TIM0_COMPB_vect)
{
    (void)pin_assert( &debug_pin );
    while(1); /* Trap */
}

ISR(WDT_vect)
{
    (void)pin_assert( &debug_pin );
    while(1); /* Trap */
}

ISR(USI_START_vect)
{
    (void)pin_assert( &debug_pin );
    while(1); /* Trap */
}

ISR(USI_OVF_vect)
{
    (void)pin_assert( &debug_pin );
    while(1); /* Trap */
}