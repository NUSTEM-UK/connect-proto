/*
 *  PinDefinitionsAndMore.h
 *
 *  Contains SERVOX_PIN definitions for ServoEasing examples for various platforms
 *  as well as includes and definitions for LED_BUILTIN
 *
 *  Copyright (C) 2020  Armin Joachimsmeyer
 *  armin.joachimsmeyer@gmail.com
 *
 *  This file is part of ServoEasing https://github.com/ArminJo/ServoEasing.
 *
 *  IRMP is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/gpl.html>.
 *
 */

/*
 * Pin mapping table for different platforms
 *
 * Platform         Servo1      Servo2      Servo3      Analog
 * -----------------------------------------------------------
 * (Mega)AVR + SAMD   9           10          11          A0
 * ESP8266            14 // D5    12 // D6    13 // D7    0
 * ESP32              5           18          19          A0
 * BluePill           PB7         PB8         PB9         PA0
 * APOLLO3            11          12          13          A3
 */

#if defined(ESP8266)
#define SERVO1_PIN 14 // D5
#define SERVO2_PIN 13 // D7
#define SERVO3_PIN 12 // D6
#define SPEED_IN_PIN 0

#else
#warning Board / CPU is not detected using pre-processor symbols -> using default values, which may not fit. Please extend PinDefinitionsAndMore.h.
// Default valued for unidentified boards
#define SERVO1_PIN 9
#define SERVO2_PIN 10
#define SERVO3_PIN 11
#define SPEED_IN_PIN A0
#define MODE_ANALOG_INPUT_PIN A1

#endif

#define SERVO_UNDER_TEST_PIN SERVO1_PIN
#define SPEED_OR_POSITION_ANALOG_INPUT_PIN SPEED_IN_PIN
#define POSITION_ANALOG_INPUT_PIN SPEED_IN_PIN
