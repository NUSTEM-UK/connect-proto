#include <Kniwwelino.h>
#include <ServoEasing.h>
#include "Connect.h"

#define WIFI_ON 1
#define VERSION "0.02"

ServoEasing Servo1;
ServoEasing Servo2;

int servo1Speed = 20;
int servo2Speed = 20;

void setup() {
    connectSetup();

    Servo1.attach(D5);
    Servo2.attach(D7);
    Servo1.write(0);
    Servo2.write(0);
    delay(500);
    Servo1.setEasingType(EASE_CUBIC_IN_OUT);
    Servo2.setEasingType(EASE_CUBIC_IN_OUT);

    Kniwwelino.MATRIXdrawIcon(ICON_SMILE);
    #if WIFI_ON
    Kniwwelino.MQTTpublish("hello_my_name_is", String(Kniwwelino.getMAC()));
    #endif

    servos_disengage();

}

void loop() {
    handleButtons();
    // TODO: Think about whether this gets called in the loop,
    //       or only from messageReceived(). The latter would
    //       seem more appropriate and performative?
    checkMood();
    Kniwwelino.loop();
    delay(500);
}

void doHappy() {
    Serial.println(F("New mood received: HAPPY"));
    // servos_engage();
    // servo1Speed = 100;)
    // for (int i = 0; i < 3; i++) {
    //     Servo1.startEaseTo(180, servo1Speed, true);
    //     Kniwwelino.RGBsetColorEffect(String("00FF00"), RGB_BLINK, -1);
    //     while (Servo1.isMovingAndCallYield()) {
    //         // Nothing here, intentionally
    //     }
    //     Servo1.startEaseTo(0, servo1Speed, true);
    //     Kniwwelino.RGBsetColorEffect(String("FF0000"), RGB_GLOW, -1);
    //     while (Servo1.isMovingAndCallYield()) {
    //         // Nothing here, intentionally
    //     }
    // }
    // Kniwwelino.RGBclear(); // Turn the LED off.
    // servos_disengage();
}

void doSad() {
    Serial.println(F("New mood received: SAD"));
    // servos_engage();
    // servo1Speed = 100;
    // servo2Speed = 200;
    // for (int i = 0; i < 3; i++) {
    //     Servo2.startEaseTo(180, servo2Speed, true);
    //     Servo1.startEaseTo(180, servo1Speed, true);
    //     while (Servo1.isMovingAndCallYield()) {
    //         // Nothing here
    //     }
    //     Servo1.startEaseTo(0, servo1Speed, true);
    //     Servo2.startEaseTo(0, servo2Speed, true);
    //     while (Servo1.isMovingAndCallYield()) {
    //         // Nothing here
    //     }
    // }
    // Kniwwelino.RGBclear(); // Turn the LED off
    // servos_disengage();
}

void doHeart() {
    Serial.println(F("New mood received: HEART"));
}

void doSkull() {
    Serial.println(F("New mood received: SKULL"));
}

void doDuck() {
    Serial.println(F("New mood received: DUCK"));
}
