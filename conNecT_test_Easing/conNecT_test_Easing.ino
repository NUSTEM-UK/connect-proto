#include <Kniwwelino.h>
#include <ServoEasing.h>

#define VERSION "0.01"

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

void setup() {
    Kniwwelino.begin("conNecT_test_Easing", true, true, false); // Wifi=true, Fastboot=true, MQTT Logging=false

    Serial.begin(115200);
    Serial.println();
    Serial.println(F("START " __FILE__ "\r\nVersion " VERSION " from " __DATE__));

    Kniwwelino.MQTTsetGroup(String("NUSTEM"));
    Kniwwelino.MQTTonMessage(messageReceived);
    Kniwwelino.MQTTsubscribe("MESSAGE");
    Kniwwelino.MQTTsubscribe("MOOD");

    Servo1.attach(D5);
    Servo2.attach(D7);

    Servo1.write(0);
    Servo2.write(0);
    delay(500);
    Servo1.setEasingType(EASE_CUBIC_IN_OUT);
    Servo2.setEasingType(EASE_CUBIC_IN_OUT);

    Kniwwelino.MATRIXdrawIcon(ICON_SMILE);
    Kniwwelino.MQTTpublish("hello_my_name_is", String(Kniwwelino.getMAC()));
    // animation_rate = 100;
    my_mood = 0;
    my_icon = String(HAPPY);
    network_mood = String("B0000000000000000000000000");
    displayed_mood = String("B0000000000000000000000000");
}

void loop() {
    if (Kniwwelino.BUTTONAclicked()) {
        change_mood();
    }
    if (Kniwwelino.BUTTONBclicked()) {
        Kniwwelino.MATRIXdrawIcon(ICON_ARROW_UP);
        Kniwwelino.sleep((unsigned long) 500);
        Kniwwelino.MQTTpublish("MOOD", String(my_icon)); // May need to reorder this
    }
    if (network_mood != displayed_mood) {
        displayed_mood = network_mood;
        Kniwwelino.MATRIXdrawIcon(displayed_mood);
        if (displayed_mood == String(HAPPY)) {
            // HAPPY response goes here
            Serial.println("New mood received: HAPPY");
            Servo1.setEasingType(EASE_CUBIC_IN_OUT);
            servo1Speed = 100;
            for (int i = 0; i < 3 ; i++) {
                Servo1.startEaseTo(180, servo1Speed, true);
                while (Servo1.isMovingAndCallYield()) {
                    // Nothing here
                }
                Servo1.startEaseTo(0, servo1Speed, true);
                while (Servo1.isMovingAndCallYield()) {
                    // Nothing here
                }
            }
            
        }
        else if (displayed_mood == String(SAD)) {
            // SAD response goes here
            Serial.println("New mood received: SAD");
        }
        else if (displayed_mood == String(HEART)) {
            // HEART response goes here
            Serial.println("New mood received: HEART");
        }
        else if (displayed_mood == String(SKULL)) {
            // SKULL response goes here
            Serial.println("New mood received: SKULL");
        }
        else if (displayed_mood == String(DUCK)) {
            // DUCK response goes here
            Serial.println("New mood received: DUCK");
        }
    }
    Kniwwelino.loop();

}

static void messageReceived(String &topic, String &payload) {
  if (topic=="MESSAGE") {
    received_string = payload;
  } else if (topic=="MOOD") {
    network_mood = payload;
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