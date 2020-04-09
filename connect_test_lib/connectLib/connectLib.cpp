// Save this to Libraries directory

#include "Arduino.h"
#include "Kniwwlino.h"
#include "Connect.h"

#define WIFI_ON 1

// Below set to defaults, will need overriding for conNecT
// (these are defined in Kniwwelino.h)
// TODO: check Kniwwelino.MQTTsetup()
#define DEF_UPDATESERVER		"connect.nustem.uk"
#define DEF_MQTTSERVER		 	"connect.nustem.uk"
#define DEF_MQTTPORT			1883
#define DEF_MQTTUSER			"connect"
#define DEF_MQTTPW		        "4AsrtshR3ci9LfTuJh4q"
#define DEF_MQTTPUBLICDELAY		300
#define DEF_MQTTBASETOPIC		"kniwwelino/"
#define DEF_FWUPDATEURL      	"/updateFW"
#define DEF_CONFUPDATEURL       "/updateConf"

#define NTP_SERVER			  	"uk.pool.ntp.org"
#define NTP_PORT			  	8888
#define NTP_TIMEZONE			1
#define NTP_PACKET_SIZE			48 // NTP time is in the first 48 bytes of message

// Constructor
Connect::Connect(int pin)
{
    // Setup stuff here
}

void Connect::method()
{
    // Method code
}

