// Code to drive the test piece hardware
// Aiming to test 2x ServoEasing servos + Neopixel (built-in) + Neopixel strip (external)
// Code mostly lifted from conNecT_test_Easing.ino, but with networking stripped out
// ...though I do eventually want to include networking and MQTT receive.

#include <Connect.h>

#define VERSION "0.0a-app"

ServoEasing Servo1;
ServoEasing Servo2;

int servo1Speed = 20;
int servo2Speed = 20;

void setup() {
    Connect.begin();
    Serial.println(F("START " __FILE__ "\r\nVersion " VERSION " from " __DATE__));

    Servo1.attach(D5);
    Servo2.attach(D7);

    Servo1.write(0);
    Servo2.write(0);
    delay(500);
    Servo1.setEasingType(EASE_CUBIC_IN_OUT);
    Servo2.setEasingType(EASE_CUBIC_IN_OUT);

    // animation_rate = 100;
    Connect.setMood(0);
    my_icon = String(HAPPY);
    network_mood = String("B0000000000000000000000000");
    displayed_mood = String("B0000000000000000000000000");

    Kniwwelino.MQTTonMessage(handleMood);

    Connect.setMoodHandler("HAPPY", "beHappy");


}

void loop() {
    Connect.handleButtons();
    checkMood();

    Kniwwelino.loop();

}

void goBeHappy() {
    Serial.println("New mood received: HAPPY");
    servos_engage();
    servo1Speed = 200;
    for (int i = 0; i < 3; i++) {
        Servo1.startEaseTo(180, servo1Speed, true);
        // Kniwwelino.RGBsetColorEffect(String("00FF00"), RGB_BLINK, -1);
        while (Servo1.isMovingAndCallYield()) {
            // Nothing here, intentionally
        }
        Servo1.startEaseTo(0, servo1Speed, true);
        // Kniwwelino.RGBsetColorEffect(String("FF0000"), RGB_GLOW, -1);
        while (Servo1.isMovingAndCallYield()) {
            // Nothing here, intentionally
        }
    }
    // Kniwwelino.RGBclear(); // Turn the LED off.
    servos_disengage();
}

void goBeSad() {
    Serial.println("New mood received: SAD");
    servos_engage();
    servo1Speed = 20;
    servo2Speed = 200;
    for (int i = 0; i < 3; i++) {
        Servo2.startEaseTo(180, servo2Speed, true);
        Servo1.startEaseTo(180, servo1Speed, true);
        while (Servo1.isMovingAndCallYield()) {
            // Nothing here
        }
        Servo1.startEaseTo(0, servo1Speed, true);
        Servo2.startEaseTo(0, servo2Speed, true);
        while (Servo1.isMovingAndCallYield()) {
            // Nothing here
        }
    }
    Kniwwelino.RGBclear(); // Turn the LED off
    servos_disengage();
}

void goBeLove() {
    Serial.println("New mood received: HEART");
}

void goBeDead() {
    Serial.println("New mood received: SKULL");
}

void goBeDuck() {
    Serial.println("New mood received: DUCK");
}

void servos_engage() {
    Servo1.attach(D5);
    Servo2.attach(D7);
}

void servos_disengage() {
    Servo1.detach();
    Servo2.detach();
}


void checkMood() {
    if (network_mood != displayed_mood) {
        displayed_mood = network_mood;
        Kniwwelino.MATRIXdrawIcon(displayed_mood);
        if (displayed_mood == String(HAPPY)) {
            // HAPPY response goes here
            goBeHappy();
        }
        else if (displayed_mood == String(SAD)) {
            // SAD response goes here
            goBeSad();
        }
        else if (displayed_mood == String(HEART)) {
            // HEART response goes here
            goBeLove();
        }
        else if (displayed_mood == String(SKULL)) {
            // SKULL response goes here
            goBeDead();
        }
        else if (displayed_mood == String(DUCK)) {
            // DUCK response goes here
            goBeDuck();
        }
        // Additional responses would go here
        Kniwwelino.MATRIXdrawIcon(displayed_mood);
    }
}
