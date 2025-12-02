// run using --> ./day1_gold < day1/input.txt

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int pos = 50;
    long long ans = 0;
    string line;
    while (getline(cin, line)) {
        if (line.size() < 2) continue;
        char dir = line[0];
        unsigned long long ddiv = 0;
        int dmod = 0;
        for (size_t i = 1; i < line.size(); ++i) {
            char c = line[i];
            if (!isdigit((unsigned char)c)) break;
            int tmp = dmod * 10 + (c - '0');
            ddiv = ddiv * 10 + (tmp / 100);
            dmod = tmp % 100;
        }
        if (dir == 'R' || dir == 'r') {
            ans += (long long)ddiv + (pos + dmod) / 100;
            pos = (pos + dmod) % 100;
        } else {
            int offset = (100 - pos) % 100;
            ans += (long long)ddiv + (dmod + offset) / 100;
            pos = (pos - dmod) % 100;
            if (pos < 0) pos += 100;
        }
    }
    cout << ans << '\n';
    return 0;
}
