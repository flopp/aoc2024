#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

typedef long T;

T next(T v) {
    v = (v ^ (v << 6)) & 0xFFFFFF;
    v = (v ^ (v >> 5)) & 0xFFFFFF;
    v = (v ^ (v << 11)) & 0xFFFFFF;
    return v;
}

T value (T d0, T d1, T d2, T d3) {
    return d0 + 20 * (d1+10) + 400 * (d2+10) + 8000 * (d3+10); 
}

int main(int argc, char** argv)
{
    const bool part1 = (argc >= 2) && (argv[1] == string("1"));

    if (part1) {
        T sum = 0;
        T init;    
        while (cin >> init) {
            T v = init;
            for (int i = 0; i < 2000; ++i) {
                v = next(v);
            }
            sum += v;
        }
        cout << sum << endl;
    } else {
        unordered_map<T,T> total_prices, prices;        
        T init;
        while (cin >> init) {
            prices.clear();
            T v = init;
            T v0, v1, v2, v3, v4 = init % 10;
            for (int i = 0; i < 2000; ++i) {
                v = next(v);

                v0 = v1;
                v1 = v2;
                v2 = v3;
                v3 = v4;
                v4 = v % 10;

                if (i >= 3) {
                    T vv = value(v1-v0, v2-v1, v3-v2, v4-v3);
                    if (prices.find(vv) == prices.end()) {
                        prices[vv] = v4;
                    }
                }
            }

            for (const auto& [key, value]: prices) {
                total_prices[key] += value;
            }
        }

        T max_price = -1;
        for (const auto& [key, value]: total_prices) {
            if (value > max_price) {
                max_price = value;
            }
        }
        cout << max_price << endl;
    }

    return 0;
}