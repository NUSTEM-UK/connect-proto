// Code to drive the test piece hardware
// Aiming to test 2x ServoEasing servos + Neopixel (built-in) + Neopixel strip (external)
// Code mostly lifted from conNecT_test_Easing.ino, but with networking stripped out
// ...though I do eventually want to include networking and MQTT receive.

#include <Kniwwelino.h>
#include <ServoEasing.h>

#define VERSION "0.01"

#define WIFI_ON 0

int my_mood;
String my_icon;
String network_mood;
String displayed_mood;
String received_string;

ServoEasing Servo1;
ServoEasing Servo2;

int servo1Speed = 20;
int servo2Speed = 20;

#define HAPPY "B0000001010000001000101110"
#define SAD "B0000001010000000111010001"
#define HEART "B0101011111111110111000100"
#define SKULL "B0111010101111110111001110" 
#define DUCK "B0110011100011110111000000"

void servos_engage() {
    Servo1.attach(D5);
    Servo2.attach(D7);
}

void servos_disengage() {
    Servo1.detach();
    Servo2.detach();
}

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

    // TODO: refactor buttons clicks into a conNecT library call @done
    connectHandleButtons();
    connectCheckMood();
    
    Kniwwelino.loop();

}

static void messageReceived(String &topic, String &payload) {
  if (topic=="MESSAGE") {
    received_string = payload;
  } else if (topic=="MOOD") {
    network_mood = payload;
  }
}

void connectHandleButtons() {
    if (Kniwwelino.BUTTONAclicked()) {
        change_mood();
    }
    if (Kniwwelino.BUTTONBclicked()) {
        Kniwwelino.MATRIXdrawIcon(ICON_ARROW_UP);
        Kniwwelino.sleep((unsigned long)500);
        #if WIFI_ON
        Kniwwelino.MQTTpublish("MOOD", String(my_icon)); // May need to reorder this
        #else
        network_mood = String(my_icon);
        #endif
    }
}

void connectCheckMood() {
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
    }
}

void change_mood() {
    my_mood += 1;
    // Loop around moods
    if (my_mood > 4) {
        my_mood = 0;
    }
    if (my_mood == 0) {my_icon = String(HAPPY);}
    else if (my_mood == 1) {my_icon = String(SAD);}
    else if (my_mood == 2) {my_icon = String(HEART);}
    else if (my_mood == 3) {my_icon = String(SKULL);}
    else if (my_mood == 4) {my_icon = String(DUCK);}
    Kniwwelino.MATRIXdrawIcon(my_icon);
    Kniwwelino.sleep((unsigned long) 1000);
    Kniwwelino.MATRIXdrawIcon(network_mood);
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