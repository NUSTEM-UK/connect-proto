#include "Arduino.h"


struct mood {
    int mood_index;
    String mood_icon;
    String mood_text;
} ;

mood mood_happy;
mood_happy.mood_index = 1;
mood_happy.mood_icon = "B0000001010000001000101110";
