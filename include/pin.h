/**
 * @file   pin.h
 * @brief  This file contains generic pin definitions.
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

#ifndef PIN_H
#define PIN_H

#include <stdbool.h>

typedef enum pin_bank_
{
    PIN_BANK_A = 0U,
    PIN_BANK_B = 1U,
    PIN_BANK_C = 2U,
    PIN_BANK_D = 3U,
    PIN_BANK_E = 4U,
    PIN_BANK_F = 5U,
    PIN_BANK_G = 6U,
    PIN_BANK_H = 7U
} pin_bank_t;

typedef enum pin_num_
{
    PIN_NUM_0 = 0U,
    PIN_NUM_1 = 1U,
    PIN_NUM_2 = 2U,
    PIN_NUM_3 = 3U,
    PIN_NUM_4 = 4U,
    PIN_NUM_5 = 5U,
    PIN_NUM_6 = 6U,
    PIN_NUM_7 = 7U
} pin_num_t;

typedef struct pin_
{
    pin_bank_t bank;
    pin_num_t  num;
    bool is_asserted_low;
} pin_t;

typedef enum pin_mode_
{
    PIN_MODE_INPUT  = 0U,
    PIN_MODE_OUTPUT = 1U,
    PIN_MODE_ALTERNATE = 2U
} pin_mode_t;

typedef enum pin_pupd_
{
    PIN_PUPD_NONE     = 0U,
    PIN_PUPD_PULLDOWN = 1U,
    PIN_PUPD_PULLUP   = 2U
} pin_pupd_t;


bool pin_set_mode( const pin_t * const pin, const pin_mode_t mode );
bool pin_set_pupd( const pin_t * const pin, const pin_pupd_t pupd );
bool pin_read( const pin_t * const pin, bool * const is_asserted );
bool pin_assert( const pin_t * const pin );
bool pin_deassert( const pin_t * const pin );
bool pin_toggle( const pin_t * const pin );

#endif // PIN_H