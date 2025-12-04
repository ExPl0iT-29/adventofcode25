// compile: g++ -std=c++17 -O2 no_bits_solution.cpp -o no_bits_solution
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>    // isspace
#include <utility>   // pair

using namespace std;

// Convert __int128 -> string
string to_string128(__int128 x) {
    if (x == 0) return "0";
    bool neg = false;
    if (x < 0) { neg = true; x = -x; }
    string s;
    while (x > 0) {
        int digit = (int)(x % 10);
        s.push_back(char('0' + digit));
        x /= 10;
    }
    if (neg) s.push_back('-');
    reverse(s.begin(), s.end());
    return s;
}

// Parse decimal string (no sign) into __int128 (assumes valid digits)
__int128 str_to_int128(const string &s) {
    __int128 r = 0;
    for (char c : s) {
        r = r * 10 + (__int128)(c - '0');
    }
    return r;
}

__int128 pow10_int(int k) {
    __int128 r = 1;
    while (k--) r *= 10;
    return r;
}

// Parse "A-B,C-D,..." into vector of pairs of __int128
vector<pair<__int128,__int128>> parse_ranges(const string &line) {
    vector<pair<__int128,__int128>> ranges;
    size_t i = 0, n = line.size();
    while (i < n) {
        size_t j = i;
        while (j < n && line[j] != '-') ++j;
        string a = line.substr(i, j - i);
        ++j; // skip '-'
        size_t k = j;
        while (k < n && line[k] != ',') ++k;
        string b = line.substr(j, k - j);
        ranges.emplace_back(str_to_int128(a), str_to_int128(b));
        i = (k < n ? k + 1 : k);
    }
    return ranges;
}

// Merge overlapping or adjacent ranges
vector<pair<__int128,__int128>> merge_ranges(vector<pair<__int128,__int128>> r) {
    vector<pair<__int128,__int128>> res;
    if (r.empty()) return res;
    sort(r.begin(), r.end(),
         [](const pair<__int128,__int128> &x, const pair<__int128,__int128> &y) {
             if (x.first != y.first) return x.first < y.first;
             return x.second < y.second;
         });
    res.push_back(r[0]);
    for (size_t i = 1; i < r.size(); ++i) {
        if (r[i].first <= res.back().second + 1) {
            if (r[i].second > res.back().second) res.back().second = r[i].second;
        } else {
            res.push_back(r[i]);
        }
    }
    return res;
}

int main() {
    // ====== paste your input here (single string of comma-separated ranges) ======
    string input_line =
        "989133-1014784,6948-9419,13116184-13153273,4444385428-4444484883,26218834-26376188,224020-287235,2893-3363,86253-115248,52-70,95740856-95777521,119-147,67634135-67733879,2481098640-2481196758,615473-638856,39577-47612,9444-12729,93-105,929862406-930001931,278-360,452131-487628,350918-426256,554-694,68482544-68516256,419357748-419520625,871-1072,27700-38891,26-45,908922-976419,647064-746366,9875192107-9875208883,3320910-3352143,1-19,373-500,4232151-4423599,1852-2355,850857-889946,4943-6078,74-92,4050-4876";
    // =============================================================================

    // remove whitespace
    string line;
    for (char c : input_line) if (!isspace((unsigned char)c)) line.push_back(c);
    if (line.empty()) {
        cout << "Sum of invalid IDs = 0\n";
        return 0;
    }

    vector<pair<__int128,__int128>> ranges = parse_ranges(line);
    vector<pair<__int128,__int128>> merged = merge_ranges(ranges);
    if (merged.empty()) {
        cout << "Sum of invalid IDs = 0\n";
        return 0;
    }

    // find max right endpoint
    __int128 maxR = 0;
    for (size_t i = 0; i < merged.size(); ++i) if (merged[i].second > maxR) maxR = merged[i].second;

    // compute digit length of maxR
    int Lmax = 0;
    for (__int128 t = maxR; t > 0; t /= 10) ++Lmax;

    __int128 total = 0;
    // k = length of the repeating block
    for (int k = 1; k <= Lmax / 2; ++k) {
        __int128 tenk = pow10_int(k);
        __int128 mult = tenk + 1;               // n = s * (10^k + 1)
        __int128 s_min_digits = (k == 1 ? 1 : pow10_int(k - 1));
        __int128 s_max_digits = tenk - 1;

        for (size_t i = 0; i < merged.size(); ++i) {
            __int128 A = merged[i].first;
            __int128 B = merged[i].second;
            __int128 s_low = (A + mult - 1) / mult; // ceil(A / mult)
            __int128 s_high = B / mult;             // floor(B / mult)

            __int128 p = s_low > s_min_digits ? s_low : s_min_digits;
            __int128 q = s_high < s_max_digits ? s_high : s_max_digits;
            if (p <= q) {
                __int128 count = q - p + 1;
                __int128 sum_s = (p + q) * count / 2; // arithmetic series
                total += mult * sum_s;
            }
        }
    }

    cout << "Sum of invalid IDs = " << to_string128(total) << "\n";
    return 0;
}
