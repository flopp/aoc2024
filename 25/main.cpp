#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef vector<int> V;

bool fits(const V& lock, const V& key) {
    for (int i = 0; i < 5; ++i) {
        if (lock[i] + key[i] > 5) {
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv)
{
    const bool part1 = (argc >= 2) && (argv[1] == string("1"));

    vector<V> locks, keys;

    string line;
    int step = 0;
    bool is_lock = false;
    V lock_key;
    while (cin >> line) {
        if (step == 0) {
            if (line.front() == '#') {
                is_lock = true;
                lock_key.assign(5, -1);
            } else {
                is_lock = false;
                lock_key.assign(5, 6);
            }
        }

        if (is_lock) {
            for (int i = 0; i < 5; ++i) {
                if (line[i] == '#') {
                    ++lock_key[i];
                }
            }
        } else {
            for (int i = 0; i < 5; ++i) {
                if (line[i] == '.') {
                    --lock_key[i];
                }
            }
        }

        ++step;
        if (step == 7) {
            step = 0;
            if (is_lock) {
                locks.push_back(lock_key);
            } else {
                keys.push_back(lock_key);
            }
        }
    }

    int count = 0;

    for (const auto& lock: locks) {
        for (const auto& key: keys) {
            if (fits(lock, key)) {
                ++count;
            }
        }
    }

    cout << count << endl;

    return 0;
}