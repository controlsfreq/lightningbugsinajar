/**
 * @file   ufprng.h
 * @brief  This file contains the Ultra Fast PRNG declarations.
 * @author Liam Bucci <liam.bucci@gmail.com>
 * @date   2015-09-24
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

typedef struct ufprng_s
{
    uint8_t x;
    uint8_t a;
    uint8_t b;
    uint8_t c;
} ufprng_t;

void ufprng_seed( ufprng_t *ufprng,
                  uint32_t seed );
uint8_t ufprng_rand( ufprng_t *ufprng );