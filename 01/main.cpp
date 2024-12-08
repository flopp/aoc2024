#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef int T;
typedef vector<T> V;

int main(int argc, char** argv)
{
    const bool part1 = (argc >= 2) && (argv[1] == string("1"));

    V left, right;
    T a, b;
    while (cin >> a >> b) {
        left.push_back(a);
        right.push_back(b);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    T result = 0;
    if (part1) {
        for (size_t i = 0; i < left.size(); ++i) {
            const T& a = left[i];
            const T& b = right[i];
            if (a <= b) {
                result += (b - a);
            } else {
                result += (a - b);
            }
        }
    } else {
        auto it = right.begin();
        for (const auto& a: left) {
            while (it != right.end() && a > *it) {
                ++it;
            }
            if (it != right.end() && a == *it) {
                T count = 0;
                for (auto it2 = it; it2 != right.end() && *it2 == a; ++it2) {
                    ++count;
                }
                result += a * count;
            }
        }
    }
    cout << result << endl;

    return 0;
}