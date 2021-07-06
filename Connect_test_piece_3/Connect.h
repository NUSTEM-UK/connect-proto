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
