#include <Arduino.h>
#include <ConnectServo.h>

ConnectServo servo1;

void setup() {
    servo1.attach(D5);
    servo1.write(0);
    delay(500);
}

void loop() {
    servo1.startEaseTo(180, 30);
    while (servo1.isMovingAndCallYield() ) {
        delay(10);
    }
    servo1.startEaseTo(0, 200);
    while (servo1.isMovingAndCallYield() ) {
        delay(10);
    }
}

