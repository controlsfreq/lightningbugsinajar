/**
 * @file   tlc591x.h
 * @brief  This file contains the TLC591x driver declaration.
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

#ifndef TLC591x_H
#define TLC591x_H

#include <stdint.h>
#include "spi.h"

typedef struct tlc591x_s
{
    spi_t spi;
    pin_t le;
    pin_t oe_;
} tlc591x_t;

bool tlc591x_init( tlc591x_t * const tlc );
bool tlc591x_enable_output( tlc591x_t * const tlc );
bool tlc591x_disable_output( tlc591x_t * const tlc );
bool tlc591x_write_values( tlc591x_t * const tlc, const uint8_t values );

#endif // TLC591x_H
