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

#include <stdio.h>
#include "controller.h"


int main( int argc, char *argv[] )
{
	char major_version = LBJ_MAJOR_VERSION;
	char minor_version = LBJ_MINOR_VERSION;
	char patch_version = LBJ_PATCH_VERSION;
	
	printf( "hello\n" );
	printf( "version: %d.%d.%d\n", major_version, minor_version, patch_version );

	return 0;
}