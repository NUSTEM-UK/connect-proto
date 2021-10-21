#include <Kniwwelino.h>
#include <ServoEasing.h>

#define VERSION "0.01"


// Set up servos (doing this messily so we can script the code generation later)
// const int NUM_SERVOS = 4;
const int NUM_SERVOS = 3;
// byte myServoPins[NUM_SERVOS] = {D5, D7, D0, D6};
byte myServoPins[NUM_SERVOS] = {D5, D7, D0};

// myServoPins[0] = D5;
// myServoPins[1] = D7;
// myServoPins[2] = D0;
// myServoPins[3] = D6;

ServoEasing myServos[NUM_SERVOS];

// int servoSpeed[4] = {10, 20, 30, 40}; // Degrees per second, sort-of.
int servoSpeed[4] = {20, 100, 200, 40}; // Degrees per second, sort-of.

int servoTarget[4] = {180, 180, 180, 180};

void setup() {
    Kniwwelino.begin(false, true, false); // Wifi=true, Fastboot=true, MQTT Logging=false
    Serial.begin(115200);
    // Omitted SERIAL_USB line here (from ServoEasing) -- not in KniwwelinoLib

    Serial.println(F("START " __FILE__ "\r\nVersion " VERSION " from " __DATE__));
    Serial.print(F("Operating "));
    Serial.print(NUM_SERVOS);
    Serial.println(F(" servos."));

    for (int i = 0; i < NUM_SERVOS; i++) {
        myServos[i].attach(myServoPins[i]);
        myServos[i].setEasingType(EASE_LINEAR);
        // myServos[i].easeTo(0);
        myServos[i].easeToD(0, 100); // Have to do this quickly or setup() takes forever
    }
    delay(500);

    // Start non-blocking move
    for (int i = 0; i < NUM_SERVOS; i++) {
        myServos[i].startEaseTo(servoTarget[i], servoSpeed[i], true);
        Serial.print(F("START MOVE SERVO "));
        Serial.print(i);
        Serial.print(F(" TO ANGLE "));
        Serial.println(servoTarget[i]);
    }    
}


void loop() {

    for (int i = 0; i < NUM_SERVOS; i++) {
        if (!myServos[i].isMoving()) // has a servo stopped moving?
        {
            // Yes, it has. Reset servo target angle
            if (servoTarget[i] == 180)
            {
                servoTarget[i] = 0;
            } else {
                servoTarget[i] = 180;
            }
            // Get servo moving again
            myServos[i].startEaseTo(servoTarget[i], servoSpeed[i], true);
            Serial.print(F("START MOVE SERVO "));
            Serial.print(i);
            Serial.print(F(" TO ANGLE "));
            Serial.println(servoTarget[i]);
        }
        yield(); // Needed to maintain ESP8266-ness.
    }
    
}
