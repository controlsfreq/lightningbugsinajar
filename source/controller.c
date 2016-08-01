/**
 * @file   controller.c
 * @brief  This file contains the controller for 2, 4, or 8 LEDs.
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

#include <avr/io.h>
#include <avr/interrupt.h>
#include "tlc591x.h"
#include "pin.h"
#include "ufprng.h"
#include "controller.h"

#define PWM_CHANNELS     8U
#define PWM_RESOLUTION   128U    ///< Must be a power of 2
#define WAVEFORM_UPDATE_COUNT 2U ///< Must be a power of 2
#define WAVEFORM_LENGTH  64U     ///< Must be a power of 2
#define WAVEFORM_ACTIVE_MASK 0x1FU
#define PRNG_UPDATE_COUNT 64U    ///< Must be a power of 2

#ifndef PRNG_SEED
#define PRNG_SEED 1
#endif

/*
 * Use a software counter to implement PWM. Every Timer1 overflow the PWM counter will increment
 * and the controller_loop will update the output values of all PWM channels according to their
 * current duty cycle values.
 *
 * The duty cycle values are taken from the waveform values. The current index of the waveform is
 * stored in g_waveform_index for each LED channel. The waveform index for each channel is only
 * incremented passed zero if the channel is marked active in g_waveform_active. When a channel is
 * marked active it increments it's waveform index every WAVEFORM_UPDATE_COUNT PWM periods.
 *
 * PWM bit = 125us
 * PWM period = 128 * 125us = 16ms
 * Waveform update = 2 * 16ms = 32ms
 * Waveform rollover = 64 * 32ms = 2.048s
 */
static volatile uint8_t g_pwm_dutycycle_counter = 0;
static volatile bool g_pwm_update_flag = false;
static volatile uint8_t g_waveform_update_counter = 0;
static volatile uint8_t g_waveform_index[PWM_CHANNELS] = { 0 };
static volatile bool g_waveform_active[PWM_CHANNELS] = { false, false, false, false, false, false, false, false };
static const uint8_t WAVEFORM_VALUES[WAVEFORM_LENGTH] = {   0,   2,   4,   8,  14,  22,  30,  40,
                                                           50,  60,  72,  82,  94, 102, 110, 118,
                                                          122, 126, 128, 126, 126, 122, 118, 114,
                                                          108, 102,  96,  88,  82,  74,  68,  60,
                                                           54,  48,  42,  38,  34,  28,  26,  22,
                                                           18,  16,  14,  12,  10,   8,   6,   5,
                                                            4,   3,   2,   2,   1,   0,   0,   0,
                                                            0,   0,   0,   0,   0,   0,   0,   0 };
static uint8_t g_prng_update_counter = 0;
static uint8_t g_output_value = 0x00U;
static tlc591x_t * g_ptlc;
static bool g_run = true;
static ufprng_t g_prng;

pin_t debug_pin_test = {
    PIN_BANK_B,
    PIN_NUM_3,
    false
};

bool controller_init( tlc591x_t * const tlc )
{
    g_ptlc = tlc;

    // Seed prng
    ufprng_seed( &g_prng, PRNG_SEED );

    return true;
}

bool controller_loop( void )
{
    bool error_code = false;
    uint8_t local_pwm_dutycycle_counter = 0;
    uint8_t i = 0;

    while( g_run )
    {
        // Busy wait until next pwm update
        while( g_pwm_update_flag == false );

        // Get a local copy of the PWM duty cycle counter in case we don't finish before the next interrupt
        local_pwm_dutycycle_counter = g_pwm_dutycycle_counter;

        // Mark PWM as not ready to update as soon as possible so we don't miss a count
        g_pwm_update_flag = false;

        // Debug
        pin_toggle( &debug_pin_test );

        // Update waveform and prng update counters
        if( local_pwm_dutycycle_counter == 0 )
        {
            g_waveform_update_counter++;
            g_waveform_update_counter &= WAVEFORM_UPDATE_COUNT-1;

            g_prng_update_counter++;
            g_prng_update_counter &= PRNG_UPDATE_COUNT-1;
        }

        // Update the active waveforms according to prng
        if( (local_pwm_dutycycle_counter == 0) &&
            (g_prng_update_counter == 0)       )
        {
            uint8_t randnum = ufprng_rand( &g_prng );

            for( i = 0; i < PWM_CHANNELS; i++ )
            {
                if( (randnum & WAVEFORM_ACTIVE_MASK) == i )
                {
                    g_waveform_active[i] = true;
                }
            }
        }

        // Update the relevant waveform indexes
        if( (local_pwm_dutycycle_counter == 0) &&
            (g_waveform_update_counter == 0)   )
        {
            for( i = 0; i < PWM_CHANNELS; i++ )
            {
                if( g_waveform_active[i] == true )
                {
                    g_waveform_index[i]++;
                    g_waveform_index[i] &= WAVEFORM_LENGTH-1;

                    // Must disable waveform if we wrap here
                    if( g_waveform_index[i] == 0 )
                    {
                        g_waveform_active[i] = false;
                    }
                }
            }
        }

        // Update PWM values according to waveform values
        for( i = 0; i < PWM_CHANNELS; i++ )
        {
            g_output_value = (local_pwm_dutycycle_counter >= WAVEFORM_VALUES[g_waveform_index[i]]) ?
                             g_output_value & ~(1<<i) :
                             g_output_value | (1<<i);
        }

        // Update LED display
        tlc591x_write_values( g_ptlc, g_output_value );

        // Debug
        pin_toggle( &debug_pin_test );
    }

    return error_code;
}

ISR(TIM1_COMPA_vect)
{
    // Increment PWM counter
    g_pwm_dutycycle_counter++;

    // Rollover counter on last valid duty cycle
    g_pwm_dutycycle_counter &= PWM_RESOLUTION-1;

    // Mark PWM values as ready to update
    g_pwm_update_flag = true;
}