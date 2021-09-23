// Code to drive the test piece hardware
// Aiming to test 2x ServoEasing servos + Neopixel (built-in) + Neopixel strip (external)
// Code mostly lifted from conNecT_test_Easing.ino, but with networking stripped out
// ...though I do eventually want to include networking and MQTT receive.

#include <Kniwwelino.h>
#include <ServoEasing.h> // Added
#include "arduino_secrets.h" // defines MQTT_PASS

#define VERSION "0.02"

#define WIFI_ON 1

// FIXME: Horrid mess here, see "2021-06-23 Testing against NUSTEM again.md" for notes

// Below set to defaults, will need overriding for conNecT
// (these are defined in Kniwwelino.h)
// TODO: check Kniwwelino.MQTTsetup()
// DONE: MQTTsetup() was removed in ~1.3.1, drat.
// New equivalent is MQTTUserSetup(), which doesn't do the same thing.
// This is now all in arduinosecrets.h, because it doesn't 'stick'
// if here, even if we wrap with #ifdef / #undef and so on.
// Nope, still doesn't work.
// #define DEF_UPDATESERVER		"connect.nustem.uk"
// #define DEF_MQTTSERVER		 	"connect.nustem.uk"
// #define DEF_MQTTPORT			1883
// #define DEF_MQTTUSER			"connect"
// #define DEF_MQTTPW		        "MQTT_PASS"
// #define DEF_MQTTPUBLICDELAY		300
// #define DEF_MQTTBASETOPIC		"kniwwelino/"
// #define DEF_FWUPDATEURL      	"/updateFW"
// #define DEF_CONFUPDATEURL       "/updateConf"

#define NTP_SERVER			  	"lu.pool.ntp.org"
#define NTP_PORT			  	8888
#define NTP_TIMEZONE			1
#define NTP_PACKET_SIZE			48 // NTP time is in the first 48 bytes of message


int my_mood;
String my_icon;
String network_mood;
String displayed_mood;
String received_string;

ServoEasing Servo1;
ServoEasing Servo2;
//TODO: What happens if we have a third servo? @done
// Pull in changes from KW_flap4.ino

int servo1Speed = 20;
int servo2Speed = 20;

// TODO: refactor some of this into a sensible library
// NB. Can't move these lines into an included header, it doeesn't work.
#define HAPPY "B0000001010000001000101110"
#define SAD "B0000001010000000111010001"
#define HEART "B0101011111111110111000100"
#define SKULL "B0111010101111110111001110"
#define DUCK "B0110011100011110111000000"


void setup() {

    Kniwwelino.begin("conNecT_test_piece_1", WIFI_ON, true, false); // Wifi=true, Fastboot=true, MQTT Logging=false

    Serial.begin(115200);
    Serial.println();
    Serial.println("---------");
    Serial.println(F("START " __FILE__ "\r\nVersion " VERSION " from " __DATE__));

    // FIXME: Removed this because for now we're overriding defaults directly
    //        in KniwwelinoLib/Kniwwelino.h.
    // Set up custom broker for messages, at least.
    // TODO: Decide whether to revert to KniwwelinoLib ~1.2.1, since MQTTUserSetup()
    // was removed in 1.3.x. Or fork KniwwelinoLib, which would likely also work.
    // Kniwwelino.MQTTUserSetup(DEF_MQTTSERVER, DEF_MQTTPORT, DEF_MQTTUSER, DEF_MQTTPW);

    Serial.println("---------");
    Serial.println("MQTT server overridden in custom KniwwelinoLib");
    Serial.println(DEF_MQTTSERVER);
    Serial.println(DEF_MQTTPORT);
    Serial.println(DEF_MQTTUSER);
    // Serial.println(DEF_MQTTPW);
    Serial.println("---------");


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
