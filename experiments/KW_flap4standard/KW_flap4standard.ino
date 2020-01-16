#include <Kniwwelino.h>
#include <Servo.h>

#define VERSION "0.01"

const int NUM_SERVOS = 4;
byte myServoPins[NUM_SERVOS] = {D5, D7, D0, D6};

Servo myServos[NUM_SERVOS];


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
        myServos[i].write(0);
    }
    delay(500);
    
}

void loop() {
    for (int pos = 0; pos < 180; pos++) {
        for (int j = 0; j < NUM_SERVOS; j++) {
            myServos[j].write(pos);            
        }
        delay(30);
    }
    for (int pos = 180; pos >0; pos--) {
        for (int j = 0; j < NUM_SERVOS; j++)
        {
            myServos[j].write(pos); 
        }
        delay(30);
    }
    
}