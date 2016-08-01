/**
 * @file   timer.h
 * @brief  This file contains the timer driver declarations.
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

#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>
#include <stdint.h>

typedef enum timer_number_e
{
    TIMER_NUM_0 = 0U,
    TIMER_NUM_1 = 1U,
    TIMER_NUM_2 = 2U,
    TIMER_NUM_3 = 3U,
    TIMER_NUM_4 = 4U,
    TIMER_NUM_5 = 5U,
    TIMER_NUM_6 = 6U,
    TIMER_NUM_7 = 7U
} timer_number_t;

typedef enum timer_prescaler_e
{
    TIMER_PRE_1 = 1U,
    TIMER_PRE_2 = 2U,
    TIMER_PRE_4 = 3U,
    TIMER_PRE_8 = 4U,
    TIMER_PRE_16 = 5U,
    TIMER_PRE_32 = 6U,
    TIMER_PRE_64 = 7U,
    TIMER_PRE_128 = 8U,
    TIMER_PRE_256 = 9U,
    TIMER_PRE_512 = 10U,
    TIMER_PRE_1024 = 11U,
    TIMER_PRE_2048 = 12U,
    TIMER_PRE_4096 = 13U,
    TIMER_PRE_8192 = 14U,
    TIMER_PRE_16384 = 15U
} timer_prescaler_t;

typedef struct timer_s
{
    timer_number_t number;
    timer_prescaler_t prescaler;
    bool reset_on_match;
} timer_t;

bool timer_init( const timer_t * const ptimer );
bool timer_enable_int( const timer_t * const ptimer );
bool timer_disable_int( const timer_t * const ptimer );
bool timer_start( const timer_t * const ptimer );
bool timer_pause( const timer_t * const ptimer );
bool timer_reset( const timer_t * const ptimer );
bool timer_set_compare( const timer_t * const ptimer, const uint8_t value );
bool timer_get_compare( const timer_t * const ptimer, uint8_t * const pvalue );
bool timer_set_timer( const timer_t * const ptimer, const uint8_t value );
bool timer_get_timer( const timer_t * const ptimer, uint8_t * const pvalue );

#endif /* TIMER_H */