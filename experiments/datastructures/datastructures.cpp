#include <string>
#include <iostream>
#include <sstream>
using namespace std;

struct Mood {
    int index;
    string text;
    string icon;
};



int main() {
    Mood mood_happy;
    mood_happy.index = 1;
    mood_happy.icon = "B0000001010000001000101110";

    cout << mood_happy.icon;
    cout << endl;

    Mood moods[5] = {
        {0, "HAPPY", ""},
        {1, "SAD", ""},
        {2, "HEART", ""},
        {3, "SKULL", ""},
        {4, "DUCK", ""}
    };

    for (int i = 0; i < 5; i++)
    {
        cout << moods[i].text;
        cout << endl;
    }
    
    return 1;
}

