/* Connect.ino - bundle of functions for conNecTed objects,
built on top of Kniwwelino.

Jonathan Sanderson, Northumbria University, 2020
TODO: License
*/

void servos_engage() {
    Servo1.attach(D5);
    Servo2.attach(D7);
}

void servos_disengage() {
    Servo1.detach();
    Servo2.detach();
}

// TODO: check if this is part of the Kniwwelino base code
static void messageReceived(String &topic, String &payload) {
    Serial.println(F("---> MESSAGE RECEIVED"));

  if (topic=="MESSAGE") {
    received_string = payload;
  } else if (topic=="MOOD") {
      //   Serial.println(F("Got a mood"));
      int tempIndex = getMoodIndexFromString(payload);
      if (tempIndex != -1) {
          extrinsicMood = moods[tempIndex];
      }
      // Serial.print(F("Mood is: "));
      // Serial.println(tempIndex);

      // network_mood = payload;
  }
}


int getMoodIndexFromString (String moodString) {
    int foundMoodIndex = -1; // Initialise
    int i = 0;
    // Serial.print(F("Checking for index for Mood: "));
    // Serial.println(moodString);

    while (i < numberOfMoods) {
        // This is ugly because we always loop through the entire array,
        // but the obvious alternatives seem worse
        // TODO: find an obvious alternative that isn't worse.
        // Serial.print(F("Stepping through: "));
        // Serial.print(i);
        // Serial.print(moods[i].text);

        if (moodString == moods[i].text) {
            // Serial.print(F("  Found a match at "));
            // Serial.println(i);
            foundMoodIndex = i;
        } else {
            // Serial.print(F("  Did not find a match at "));
            // Serial.println(i);
        }
        i++;
    }
    // Will return match or -1 if no match
    if (foundMoodIndex != -1) {
        // Serial.print(F("Got a matching mood: "));
        // Serial.println(moods[foundMoodIndex].text);
    }

    return foundMoodIndex;
}


void change_mood() {
    // Increment mood. Note that we can't just increment
    // myMood.index, that would break the connection to the
    // other data in the struct
    int tempMoodIndex = myMood.index;
    tempMoodIndex++;
    // Loop around moods (self-adjusting for number of moods.)
    // Note the obvious off-by-one error here, which took me
    // much longer to spot than now seems reasonable.
    if (tempMoodIndex > (numberOfMoods-1)) {
        tempMoodIndex = 0;
    }
    Serial.println(F(">>>Changing mood"));
    Serial.print(F(">>>New mood is: "));
    Serial.println(moods[tempMoodIndex].text);
    // Display our new internal mood
    myMood = moods[tempMoodIndex];
    Kniwwelino.MATRIXdrawIcon(myMood.icon);
    Kniwwelino.sleep((unsigned long) 1000);
    Serial.println(F(">>>Returning to extrinsicMood"));
    // Now return to the network mood
    Kniwwelino.MATRIXdrawIcon(extrinsicMood.icon);
}

void handleButtons() {
    // Serial.println("Button check");
    if (Kniwwelino.BUTTONAclicked()) {
        Serial.println(F(">>>BUTTON press: A"));
        change_mood();
    }
    if (Kniwwelino.BUTTONBclicked()) {
        Serial.println(F(">>>BUTTON press: B"));
        Kniwwelino.MATRIXdrawIcon(ICON_ARROW_UP);
        Kniwwelino.sleep((unsigned long)500);
        #if WIFI_ON
        Kniwwelino.MQTTpublish("MOOD", myMood.text); // May need to reorder this
        #else
        extrinsicMood = myMood;
        // network_mood = String(my_icon);
        #endif
    }
}

void checkMood() {
    // Serial.println("Mood check");
    if (extrinsicMood.index != performedMood.index) {
        // We have a new mood to represent
        performedMood = extrinsicMood;
        myMood = extrinsicMood;
        // Display the associated icon
        Kniwwelino.MATRIXdrawIcon(performedMood.icon);
        // Now call the associated action function.
        performedMood.callback();
        // Display the associated icon
        // Do this after the callback too, in case we want to do
        // something funky along the way.
        Kniwwelino.MATRIXdrawIcon(performedMood.icon);

        // TODO: Trash this now-unnecessary code
        // if (performedMood.text == "HAPPY") {
        //     // HAPPY response goes here
        //     doHappy();
        // }
        // else if (performedMood.text == "SAD") {
        //     // SAD response goes here
        //     doSad();
        // }
        // else if (performedMood.text == "HEART") {
        //     // HEART response goes here
        //     doLove();
        // }
        // else if (performedMood.text == "SKULL") {
        //     // SKULL response goes here
        //     doDead();
        // }
        // else if (performedMood.text == "DUCK") {
        //     // DUCK response goes here
        //     doDuck();
        // }
        // Additional responses would go here
        // Kniwwelino.MATRIXdrawIcon(performedMood.icon);
    }
}

