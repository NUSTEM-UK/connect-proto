#include <Kniwwelino.h>
#include <ServoEasing.h>

#define WIFI_ON 1
#define VERSION "0.01"

ServoEasing Servo1;
ServoEasing Servo2;

int servo1Speed = 20;
int servo2Speed = 20;

// We need a function pointer type to include in our Mood struct
typedef void (*CallbackFunction)(void);

typedef struct {
    int index;
    String text;
    String icon;
    CallbackFunction callback;
} Mood;

// We need to keep track of the number of moods manually, because C
// ...and this has to be const for the array declaration to work
// ...and we need the array declaration here because we want moods[]
// to be global
const int numberOfMoods = 5; // Have to keep track of this manually, because C.
Mood moods[numberOfMoods];   // Initialiser has to be inside setup(), or bad things happen.

Mood myMood;        // Should really be intrinsicMood or internalMood
Mood extrinsicMood; // The current network mood. Should be externalMood?
Mood performedMood; // The current displayed mood

String received_string;
// static void messageReceived (String &t, String &p);
// void handleButtons();
// void checkMood();


void setup() {
    Kniwwelino.begin("Connect_test_piece_2", WIFI_ON, true, false); // Wifi=true, Fastboot=true, MQTT Logging=false

    Serial.begin(115200);
    Serial.println();
    Serial.println(F("-------"));
    Serial.println(F("START " __FILE__ "\r\nVersion " VERSION " from " __DATE__));
    Serial.println(F("-------"));
    Serial.println(F("MQTT server overridden in custom KniwwelinoLib"));
    Serial.println(DEF_MQTTSERVER);
    Serial.println(DEF_MQTTPORT);
    Serial.println(DEF_MQTTUSER);
    Serial.println(F("---------"));

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

    // Initialise the mood array. Doesn't work correctly if I move this to
    // above setup() (first string is truncated).
    // To add moods, append them to this array, and adjust numberOfMoods
    // accordingly.
    moods[0] = {0, "HAPPY", "B0000001010000001000101110", &doHappy};
    moods[1] = {1, "SAD", "B0000001010000000111010001", &doSad};
    moods[2] = {2, "HEART", "B0101011111111110111000100", &doLove};
    moods[3] = {3, "SKULL", "B0111010101111110111001110", &doDead};
    moods[4] = {4, "DUCK", "B0110011100011110111000000", &doDuck};

    // Start happy, because we're optimistic about the world
    myMood = moods[0];
    extrinsicMood = moods[0];
    performedMood = moods[0];

    // Cross-check that we have moods correctly.
    for (size_t i = 0; i < numberOfMoods; i++) {
        Serial.print(moods[i].text);
        Serial.print(F(" : "));
    }
    Serial.println();

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

void doLove() {
    Serial.println(F("New mood received: HEART"));
}

void doDead() {
    Serial.println(F("New mood received: SKULL"));
}

void doDuck() {
    Serial.println(F("New mood received: DUCK"));
}
