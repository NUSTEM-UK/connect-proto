// Code to drive the test piece hardware
// Aiming to test 2x ServoEasing servos + Neopixel (built-in) + Neopixel strip (external)
// Code mostly lifted from conNecT_test_Easing.ino, but with networking stripped out
// ...though I do eventually want to include networking and MQTT receive.

#include <Kniwwelino.h>
#include <ServoEasing.h> // Added

#define VERSION "0.02"

#define WIFI_ON 0

int my_mood;
String my_icon;
String network_mood;
String displayed_mood;
String received_string;

ServoEasing Servo1;
ServoEasing Servo2;
//TODO: What happens if we have a third servo?

int servo1Speed = 20;
int servo2Speed = 20;

// TODO: refactor some of this into a sensible library
#define HAPPY "B0000001010000001000101110"
#define SAD "B0000001010000000111010001"
#define HEART "B0101011111111110111000100"
#define SKULL "B0111010101111110111001110" 
#define DUCK "B0110011100011110111000000"


void setup() {
    Kniwwelino.begin("conNecT_test_piece_1", WIFI_ON, true, false); // Wifi=true, Fastboot=true, MQTT Logging=false

    Serial.begin(115200);
    Serial.println();
    Serial.println(F("START " __FILE__ "\r\nVersion " VERSION " from " __DATE__));

    #if WIFI_ON
        Kniwwelino.MQTTsetGroup(String("NUSTEM"));
        Kniwwelino.MQTTonMessage(messageReceived);
        Kniwwelino.MQTTsubscribe("MESSAGE");
        Kniwwelino.MQTTsubscribe("MOOD");
    #endif

    Servo1.attach(D5);
    Servo2.attach(D7);

    Servo1.write(0);
    Servo2.write(0);
    delay(500);
    Servo1.setEasingType(EASE_CUBIC_IN_OUT);
    Servo2.setEasingType(EASE_CUBIC_IN_OUT);

    Kniwwelino.RGBsetBrightness((int)200);
    Kniwwelino.RGBclear();

    Kniwwelino.MATRIXdrawIcon(ICON_SMILE);
    #if WIFI_ON
    Kniwwelino.MQTTpublish("hello_my_name_is", String(Kniwwelino.getMAC()));
    #endif
    // animation_rate = 100;
    my_mood = 0;
    my_icon = String(HAPPY);
    network_mood = String("B0000000000000000000000000");
    displayed_mood = String("B0000000000000000000000000");
}

void loop() {
    connectHandleButtons();
    connectCheckMood();
    
    Kniwwelino.loop();

}


void goBeHappy() {
    Serial.println("New mood received: HAPPY");
    servos_engage();
    servo1Speed = 100;
    for (int i = 0; i < 3; i++) {
        Servo1.startEaseTo(180, servo1Speed, true);
        Kniwwelino.RGBsetColorEffect(String("00FF00"), RGB_BLINK, -1);
        while (Servo1.isMovingAndCallYield()) {
            // Nothing here, intentionally
        }
        Servo1.startEaseTo(0, servo1Speed, true);
        Kniwwelino.RGBsetColorEffect(String("FF0000"), RGB_GLOW, -1);
        while (Servo1.isMovingAndCallYield()) {
            // Nothing here, intentionally
        }
    }
    Kniwwelino.RGBclear(); // Turn the LED off.
    servos_disengage();
}

void goBeSad() {
    Serial.println("New mood received: SAD");
    servos_engage();
    servo1Speed = 100;
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