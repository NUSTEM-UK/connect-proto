/**
 * Connect.h - Library for Connect devices
 * Created by Jonathan Sanderson, July 2021
 * Northumbria University
 * See https://nustem.uk/connect
 * TODO: License
 *
 * Based on connect_test_piece_2
 * Most of this _nearly_ works, but there are issues:
 *   - Pointers to class methods aren't interchangeable with pointers to
 *     general functions, so even if I can get performedMood.callback() to
 *     execute properly, I don't think I can readily override the action
 *     functions in the way I want (even with declaring virtual).
 *   - Similar issue arises for registering my callback with
 *     Kniwwelino.MQTTonMessage(messageReceived); that fails within the class
 *     implementation.
 *
 * Somewhere around here, I have a big 'what's the point?' vibe. test_piece_2 works
 * as required, so let's go back to that and continue hacking on it.
*/

#ifndef Connect_h
#define Connect_h

#include <Kniwwelino.h>         // Includes Arduino.h for us
#include <ServoEasing.h>
#include "arduino_secrets.h"    // define MQTT_PASS, .gitignored

#define VERSION "0.02"
#define WIFI_ON 1
#define NUMBER_OF_MOODS 5

// Redefine MQTT stuff previously set in Kniwwelino.h
// TODO: check Kniwwelino.MQTTsetup()
// FIXME: Horrid mess here, see "2021-06-23 Testing against NUSTEM again.md" for notes
// TL;DR: MQTTsetup() has been removed, so the only way to set this stuff is to
//        hard-code it in KniwwelinoLib. Ugh.
// #define DEF_UPDATESERVER		"connect.nustem.uk"
// #define DEF_MQTTSERVER		 	"connect.nustem.uk"
// #define DEF_MQTTPORT			1883
// #define DEF_MQTTUSER			"connect"
// #define DEF_MQTTPW		        "MQTT_PASS"
// #define DEF_MQTTPUBLICDELAY		300
// #define DEF_MQTTBASETOPIC		"kniwwelino/"
// #define DEF_FWUPDATEURL      	"/updateFW"
// #define DEF_CONFUPDATEURL       "/updateConf"

#define NTP_SERVER			  	"uk.pool.ntp.org"
#define NTP_PORT			  	8888
// TODO: work out what this is and if it's used:
// (NTP_TIMEZONE doesn't appear to be used by Kniwwelino or Timezone libraries.
// Check against actual time received. May need to do something clever with BST,
// But that should be baked into the Timezone library if we call it correctly.)
#define NTP_TIMEZONE			1
#define NTP_PACKET_SIZE			48 // NTP time is in the first 48 bytes of message


class ConnectLib{
    public:
        typedef void (ConnectLib::*CallbackFunction)(void);

        typedef struct {
            int index;
            String text;
            String icon;
            CallbackFunction callback;
        } Mood;
        ConnectLib(); // Root object, needs variable stubs

        void begin();
        void loop();

        // Getters and setters
        String getMood();               // TODO: Implement
        String setMood();               // TODO: Implement
        String getDisplayedMood();      // TODO: Implement
        String getNetworkMood();        // TODO: Implement
        String sendMoodToNetwork();     // TODO: Implement

        // Utility
        // void servosEngage();            // TODO: Implement
        // void servosDisengage();         // TODO: Implement

        // Moods
        // Declared virtual so they can be overridden
        void doHappy();
        void doSad();
        void doHeart();
        void doSkull();
        void doDuck();

    private:
        static Mood moods[NUMBER_OF_MOODS];
        // ConnectLib() : moods();
        Mood myMood;
        Mood extrinsicMood;
        Mood performedMood;
        String receivedString;

        void messageReceived(String &s, String &t);
        void handleButtons();
        void changeMood();
        void checkMood();
        int getMoodIndexFromString(String moodString);
};

extern ConnectLib Connect;

#endif
