/*
 * TwoServos.cpp
 *
 *  Shows smooth movement from one servo position to another for 2 servos synchronously.
 *  Operate the first servo from -90 to +90 degree
 *
 *  Copyright (C) 2019  Armin Joachimsmeyer
 *  armin.joachimsmeyer@gmail.com
 *
 *  This file is part of ServoEasing https://github.com/ArminJo/ServoEasing.
 *
 *  ServoEasing is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/gpl.html>.
 */

#include <Arduino.h>
#include "ServoEasing.h"

#define SERVO1_PIN 14 // D5
#define SERVO2_PIN 13 // D7
#define SERVO3_PIN 12 // D6
#define SPEED_IN_PIN 0

ServoEasing servo1;
ServoEasing servo2;

void blinkLED();

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_SERVO_EASING));

    Serial.print(F("Attach servo at pin "));
    Serial.println(SERVO1_PIN);
    if (servo1.attach(SERVO1_PIN) == INVALID_SERVO) {
        Serial.println(F("Error attaching servo"));
    }

    Serial.print(F("Attach servo at pin "));
    Serial.println(SERVO2_PIN);
    if (servo2.attach(SERVO2_PIN) == INVALID_SERVO) {
        Serial.println(F("Error attaching servo"));
    }

    /*
     * Operate servo1 from -90 to +90 degree
     * Instead of specifying a trim you can use above:
     *   if (servo1.attach(SERVO1_PIN, DEFAULT_MICROSECONDS_FOR_0_DEGREE, DEFAULT_MICROSECONDS_FOR_180_DEGREE, -90, 90) == INVALID_SERVO) {
     */
    servo1.setTrim(90);


    /**************************************************
     * Set servos to start position.
     * This is the position where the movement starts.
     *************************************************/
    servo1.write(-90);
    servo2.write(0);
    setSpeedForAllServos(30);

    // Just wait for servos to reach position.
    delay(500);
}

void blinkLED() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
}

void loop() {

    /*
     * Move both servos blocking
     */
    Serial.println(F("Move to 0/90 degree with 30 degree per second blocking"));
    setSpeedForAllServos(30);
    servo1.setEaseTo(0);
    servo2.setEaseTo(90);
    synchronizeAllServosStartAndWaitForAllServosToStop();

    /*
     * Now continue faster.
     */
    Serial.println(F("Move to 90/10 degree with 60 degree per second using interrupts"));
    servo1.setEaseTo(90, 60);
    /*
     * An alternative method to synchronize and start
     * Synchronize by simply using the same duration
     */
    servo2.startEaseToD(10, servo1.mMillisForCompleteMove); // This start interrupt for all servos
    /*
     * Now you can run your program while the servos are moving.
     * Just let the LED blink until servos stop.
     */
    while (areInterruptsActive()) {
        blinkLED();
    }

    /*
     * Move servo1 using cubic easing. Use interrupts for update.
     *  The first servo moves with the specified speed.
     *  The second will be synchronized to slower speed (longer duration, than specified) because it has to move only 80 degree.
     */
    Serial.println(F("Move to 0/90 degree with 90 degree per second using interrupts. Use cubic easing for first servo."));
    servo1.setEasingType(EASE_CUBIC_IN_OUT);
    /*
     * Another method to specify moves
     * Use the sServoNextPositionArray and then call the appropriate function
     */
    sServoNextPositionArray[0] = 0;
    sServoNextPositionArray[1] = 90;
    setEaseToForAllServosSynchronizeAndStartInterrupt(90);

    // Must call yield here for the ESP boards, since we have no delay called
    while (areInterruptsActive()) {
        ;
    }
    servo1.setEasingType(EASE_LINEAR);

    delay(300);

    /*
     * Move both servos independently
     */
    Serial.println(F("Move independently to -90/0 degree with 60/80 degree per second using interrupts"));
    servo1.setEaseTo(-90, 60);
    servo2.startEaseTo(0, 80); // This start interrupt for all servos
    // blink until both servos stop
    while (areInterruptsActive()) {
        blinkLED();
    }

    delay(500);

}
