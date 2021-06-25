#include <Arduino.h>

#define VERSION "0.01"


typedef struct {
    int index;
    String text;
    String icon;
    String callback;
} Mood;

Mood moods[5] = {
    {0, "HAPPY", "B0000001010000001000101110", "doHappy"},
    {1, "SAD", "B0000001010000000111010001", "doSad"},
    {2, "HEART", "B0101011111111110111000100", "doLove"},
    {3, "SKULL", "B0111010101111110111001110", "doDead"},
    {4, "DUCK", "B0110011100011110111000000", "doDuck"}
};
int numberOfMoods = 5; // Have to keep track of this manually, because C.

String networkMoodText;
int receivedMoodIndex;

Mood my_mood;

void setup() {
    delay(250);
    Serial.begin(115200);
    Serial.println();
    Serial.println("-------");
    Serial.println(F("START " __FILE__ "\r\nVersion " VERSION " from " __DATE__));
    Serial.println("-------");

    delay(250);

    my_mood = moods[0];
    networkMoodText = "SKULL";

    receivedMoodIndex = getMoodIndexFromString(networkMoodText);
    Serial.println(moods[receivedMoodIndex].index);
    Serial.println(moods[receivedMoodIndex].text);
    Serial.println(moods[receivedMoodIndex].icon);
    Serial.println(moods[receivedMoodIndex].callback);

    delay(500);
    networkMoodText = "HAPPY";
    receivedMoodIndex = getMoodIndexFromString(networkMoodText);
    Serial.println(moods[receivedMoodIndex].index);
    Serial.println(moods[receivedMoodIndex].text);
    Serial.println(moods[receivedMoodIndex].icon);
    Serial.println(moods[receivedMoodIndex].callback);


}

void loop() {

}

int getMoodIndexFromString (String moodString) {
    int foundMoodIndex = -1; // Initialise
    int i = 0;

    while (i < numberOfMoods) {
        // This is ugly because we always loop through the entire array,
        // but the obvious alternatives seem worse
        // TODO: find an obvious alternative that isn't worse.
        Serial.print("Stepping through: ");
        Serial.print(i);

        if (moodString == moods[i].text) {
            Serial.print("  Found a match at ");
            Serial.println(i);
            foundMoodIndex = i;
        } else {
            Serial.print("  Did not find a match at ");
            Serial.println(i);
        }
        i++;
    }
    // Will return match or -1 if no match
    if (foundMoodIndex != -1) {
        Serial.print("Got a matching mood: ");
        Serial.println(moods[foundMoodIndex].text);
    }

    return foundMoodIndex;
}

