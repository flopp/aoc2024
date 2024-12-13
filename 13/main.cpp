#include <iostream>
#include <regex>
#include <string>

using namespace std;


typedef long T;

T min_tokens_loop(T ax, T ay, T bx, T by, T px, T py) {
    for (T a = 0; a < 100; ++a) {
        const T x0 = a*ax;
        const T y0 = a*ay;
        for (T b = 0; b < 100; ++b) {
            const T x1 = b*bx;
            const T y1 = b*by;

            if (x0+x1 != px || y0+y1 != py) {
                continue;
            }
            return 3*a+b;
        }
    }
    return 0;
}

T min_tokens_calc(T ax, T ay, T bx, T by, T px, T py) {
    // a, b in N>=0
    // ax*a + bx*b = px 
    // ay*a + by*b = py

    // a = (px-bx*b)/ax
    // ay/ax*(px-bx*b) + by*b = py
    // px*ay/ax - b*bx*ay/ax + b*by = py
    // b = (py-px*ay/ax) / (by - bx*ay/ax)
    // b = (py*ax - px*ay) / (by*ax - bx*ay)

    T b0 = py*ax - px*ay;
    T b1 = by*ax - bx*ay;
    if ((b1 == 0) || ((b0 % b1) != 0)) {
        return 0;
    }
    T b = b0 / b1;
    if (b < 0) {
        return 0;
    }
    
    T a0 = px - bx*b;
    T a1 = ax;
    if ((a1 == 0) || ((a0 % a1) != 0)) {
        return 0;
    }
    T a = a0 / a1;
    if (a < 0) {
        return 0;
    }

    return 3*a + b;
}


int main(int argc, char** argv)
{
    const bool part1 = (argc >= 2) && (argv[1] == string("1"));

    const auto re_a_button = regex("^Button A: X\\+(\\d+), Y\\+(\\d+)$");
    const auto re_b_button = regex("^Button B: X\\+(\\d+), Y\\+(\\d+)$");
    const auto re_prize = regex("^Prize: X=(\\d+), Y=(\\d+)$");

    T total_tokens = 0;
    T ax, ay, bx, by, px, py;
    int i = 0;
    string line;
    smatch m;
    while (getline(cin, line)) {
        if (i == 0) {
            std::regex_match(line, m, re_a_button);
            ax = stoi(m[1].str());
            ay = stoi(m[2].str());
        } else if (i == 1) {
            std::regex_match(line, m, re_b_button);
            bx = stoi(m[1].str());
            by = stoi(m[2].str());
        } else if (i == 2) {
            std::regex_match(line, m, re_prize);
            px = stoi(m[1].str());
            py = stoi(m[2].str());

            if (!part1) {
                px += 10000000000000;
                py += 10000000000000;
            }

            total_tokens += min_tokens_calc(ax, ay, bx, by, px, py);
        } 
        i = (i + 1) % 4;
    }

    cout << total_tokens << endl;

    return 0;
}