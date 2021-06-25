#include <string>
#include <iostream>
#include <sstream>
using namespace std;

struct Mood {
    int index;
    string text;
    string icon;
    string callback;
};



int main() {
    Mood mood_happy;
    mood_happy.index = 1;
    mood_happy.icon = "B0000001010000001000101110";

    cout << mood_happy.icon;
    cout << endl;

    Mood moods[5] = {
        {0, "HAPPY", "", "goBeHappy"},
        {1, "SAD", "", "goBeSad"},
        {2, "HEART", "", "goBeLove"},
        {3, "SKULL", "", "goBeDead"},
        {4, "DUCK", "", "goBeDuck"}
    };

    for (int i = 0; i < 5; i++)
    {
        cout << moods[i].text;
        cout << " ";

        cout << moods[i].callback;
        cout << endl;
    }

    string test = moods[0].callback();
    cout << test;


    return 1;
}

int goBeHappy() {
    cout << "I am being happy";
    cout << endl;
    return 1;
}
