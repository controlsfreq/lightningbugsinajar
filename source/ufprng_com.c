/**
 * @file   ufprng_com.c
 * @brief  This file contains the common Ultra Fast PRNG implementation.
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
 *
 * Random number generator algorithm used:
 * http://www.electro-tech-online.com/threads/ultra-fast-pseudorandom-number-generator-for-8-bit.124249/
 */

#include <stddef.h>
#include <stdint.h>
#include "ufprng.h"

void ufprng_seed( ufprng_t *ufprng,
                  uint32_t seed )
{
    //XOR new entropy into key state
    ufprng->a ^= (seed & 0x000000FF);
    ufprng->b ^= (seed & 0x0000FF00)>>8;
    ufprng->c ^= (seed & 0x00FF0000)>>16;
    ufprng->x  = (seed & 0xFF000000)>>24;

    (void)ufprng_rand( ufprng );
}

uint8_t ufprng_rand( ufprng_t *ufprng )
{
    ufprng->x++;               //x is incremented every round and is not affected by any other variable
    ufprng->a = ( (ufprng->a) ^ (ufprng->c) ^ (ufprng->x) );       //note the mix of addition and XOR
    ufprng->b = ( ufprng->b + ufprng->a);         //And the use of very few instructions
    ufprng->c = ( ufprng->c + ( (ufprng->b>>1) ^ ufprng->a ) );  //the right shift is to ensure that high-order bits from b can affect
    return ufprng->c;         //low order bits of other variables
}