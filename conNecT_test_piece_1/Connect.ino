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

void connectHandleButtons() {
    if (Kniwwelino.BUTTONAclicked()) {
        change_mood();
    }
    if (Kniwwelino.BUTTONBclicked()) {
        Kniwwelino.MATRIXdrawIcon(ICON_ARROW_UP);
        Kniwwelino.sleep((unsigned long)500);
        #if WIFI_ON
        Kniwwelino.MQTTpublish("MOOD", String(my_icon)); // May need to reorder this
        #else
        network_mood = String(my_icon);
        #endif
    }
}

void connectCheckMood() {
    if (network_mood != displayed_mood) {
        displayed_mood = network_mood;
        Kniwwelino.MATRIXdrawIcon(displayed_mood);
        if (displayed_mood == String(HAPPY)) {
            // HAPPY response goes here
            goBeHappy();
        }
        else if (displayed_mood == String(SAD)) {
            // SAD response goes here
            goBeSad();
        }
        else if (displayed_mood == String(HEART)) {
            // HEART response goes here
            goBeLove();
        }
        else if (displayed_mood == String(SKULL)) {
            // SKULL response goes here
            goBeDead();
        }
        else if (displayed_mood == String(DUCK)) {
            // DUCK response goes here
            goBeDuck();
        }
        // Additional responses would go here
    }
}

