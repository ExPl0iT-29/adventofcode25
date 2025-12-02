// run using --> ./day1 < day1/input.txt

#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int pos = 50;
    long long count = 0;
    string line;

    while (getline(cin, line)) {
        if (line.empty()) continue;
        char dir = line[0];
        int d = 0;                 // we only need distance mod 100
        for (size_t i = 1; i < line.size(); ++i) {
            if (isdigit((unsigned char)line[i])) {
                d = (d * 10 + (line[i] - '0')) % 100;
            }
        }
        if (dir == 'R') pos = (pos + d) % 100;
        else             pos = (pos - d + 100) % 100;

        if (pos == 0) ++count;
    }

    cout << count << '\n';
    return 0;
}


