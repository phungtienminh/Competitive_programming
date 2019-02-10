#include <bits/stdc++.h>

using namespace std;

struct Box {
    int id, hours, minutes, seconds, ms, houre, minutee, seconde, me;
    vector <string> vec;

    Box (int id = 0, int hours = 0, int minutes = 0, int seconds = 0, int ms = 0,
         int houre = 0, int minutee = 0, int seconde = 0, int me = 0,
         vector <string> vec = {}): id(id), hours(hours), minutes(minutes), seconds(seconds), ms(ms), houre(houre),
                                    minutee(minutee), seconde(seconde), me(me), vec(vec) {}
};

int T;
bool canDo = true;
vector <Box> boxes;

void display (Box box) {
    cout << box.id << "\n";
    if (box.hours < 10) cout << "0"; cout << box.hours << ":";
    if (box.minutes < 10) cout << "0"; cout << box.minutes << ":";
    if (box.seconds < 10) cout << "0"; cout << box.seconds << ",";
    if (box.ms < 10) cout << "00";
    else if (box.ms < 100) cout << "0";
    cout << box.ms;
    cout << " --> ";

    if (box.houre < 10) cout << "0"; cout << box.houre << ":";
    if (box.minutee < 10) cout << "0"; cout << box.minutee << ":";
    if (box.seconde < 10) cout << "0"; cout << box.seconde << ",";
    if (box.me < 10) cout << "00";
    else if (box.me < 100) cout << "0";
    cout << box.me;
    cout << "\n";
    for (auto data: box.vec) cout << data << "\n";
}

Box modify (Box nbox) {
    Box box = nbox;
    box.ms += T;
    if (box.ms >= 0) {
        box.seconds += box.ms / 1000;
        box.ms %= 1000;
        box.minutes += box.seconds / 60;
        box.seconds %= 60;
        box.hours += box.minutes / 60;
        box.minutes %= 60;
    }
    else {
        int val = (abs(box.ms) + 999) / 1000;
        box.seconds -= val; box.ms += val * 1000;
        if (box.seconds < 0) {
            val = (abs(box.seconds) + 59) / 60;
            box.minutes -= val; box.seconds += val * 60;
            if (box.minutes < 0) {
                val = (abs(box.minutes) + 59) / 60;
                box.hours -= val; box.minutes += val * 60;
            }
        }
    }

    box.me += T;
    if (box.me >= 0) {
        box.seconde += box.me / 1000;
        box.me %= 1000;
        box.minutee += box.seconde / 60;
        box.seconde %= 60;
        box.houre += box.minutee / 60;
        box.minutee %= 60;
    }
    else {
        int val = (abs(box.me) + 999) / 1000;
        box.seconde -= val; box.me += val * 1000;
        if (box.seconde < 0) {
            val = (abs(box.seconde) + 59) / 60;
            box.minutee -= val; box.seconde += val * 60;
            if (box.minutee < 0) {
                val = (abs(box.minutee) + 59) / 60;
                box.houre -= val; box.minutee += val * 60;
            }
        }
    }

    return box;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (canDo) {
        int id; cin >> id;
        string times; getline(cin, times); getline(cin, times);
        vector <string> subtitles;
        string s;
        while (getline(cin, s)) {
            if (s.length() == 0) break;
            if (s == "#") {
                canDo = false;
                cin >> T;
                break;
            }

            subtitles.push_back(s);
        }

        int cur = 0, hours = -1, minute = -1, second = -1, ms = -1, houre = -1, minutee = -1, seconde = -1, me = -1;
        for (int i = 0; i < times.length(); i++) {
            if (times[i] == '>') {
                i++;
                houre = hours; minutee = minute; seconde = second; me = ms;
                hours = minute = second = ms = -1;
                continue;
            }

            if (times[i] < '0' || times[i] > '9') {
                if (hours == -1) hours = cur;
                else if (minute == -1) minute = cur;
                else if (second == -1) second = cur;
                else if (ms == -1) ms = cur;
                cur = 0;
                continue;
            }

            cur = cur * 10 + (times[i] - '0');
            if (i + 1 == times.length()) {
                if (hours == -1) hours = cur;
                else if (minute == -1) minute = cur;
                else if (second == -1) second = cur;
                else if (ms == -1) ms = cur;
                cur = 0;
                continue;
            }
        }

        boxes.push_back(Box(id, houre, minutee, seconde, me, hours, minute, second, ms, subtitles));
    }

    for (auto &box: boxes) box = modify(box);

    bool First = true;
    for (auto box: boxes) {
        if (!First) cout << "\n";
        First = false;
        display(box);
    }

    cout << "#";
    return 0;
}
/*
624
00:43:30,566 --> 00:43:32,108
Howdy do, ladies?

625
00:43:32,276 --> 00:43:33,943
Name of Pete.

626
00:43:47,124 --> 00:43:48,082
Ain't you gonna
introduce us, Pete?
#
-500
*/
