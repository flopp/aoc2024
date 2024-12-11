#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

typedef long T;

bool evenSplit(T s, T& s0, T& s1) {
    T ss = s;
    
    int n = 0;
    while (ss != 0) {
        ss /= 10;
        ++n;
    }
    if ((n % 2) != 0) {
        return false;
    }

    T powerOf10 = 1;
    n >>= 1;
    for (int i = 0; i<n; ++i) {
        powerOf10 *= 10;
    }

    s0 = s / powerOf10;
    s1 = s % powerOf10;
    return true;
}

typedef unordered_map<T, T> M;

int main(int argc, char** argv)
{
    const bool part1 = (argc >= 2) && (argv[1] == string("1"));
    
    // engraving -> count
    M stones;
    T s;
    while (cin >> s) {
        ++stones[s];
    }

    const int loops = part1 ? 25 : 75;

    M stones2;
    T s0, s1;
    for (int loop = 0; loop < loops; ++loop) {
        stones2.clear();
        for (const auto& [s, count]: stones) {
            if (s == 0) {
                stones2[1] += count;
            } else if (evenSplit(s, s0, s1)) {
                stones2[s0] += count;
                stones2[s1] += count;
            } else {
                stones2[2024 * s] += count;
            }
        }
        swap(stones, stones2);
    }

    T sum = 0;
    for (const auto& [s, count]: stones) {
        sum += count;
    }
    cout << sum << endl;    

    return 0;
}