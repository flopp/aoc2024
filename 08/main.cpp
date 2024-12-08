#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct XY {
    int x, y;

    XY& operator+=(const XY& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    XY& operator-=(const XY& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    bool inBounds(int w, int h) const {
        return x>=0 && x<w && y>=0 && y<h;
    }
    int index(int w, int /*h*/) const {
        return x + w*y;
    }
};


int main(int argc, char** argv)
{
    const bool part1 = (argc >= 2) && (argv[1] == string("1"));

    vector<vector<XY>> antennas(256, vector<XY>());
    int w = 0;
    int h = 0;
    string line;
    while (getline(cin, line)) {
        w = line.size();
        for (int x = 0; x < w; ++x) {
            const auto c = line[x];
            if (c != '.') {
                antennas[c].push_back(XY{x, h});
            }
        }
        ++h;
    }

    vector<bool> antinodes(w * h, false);

    for (const auto& aa: antennas) {
        if (aa.size() < 2) {
            continue;
        }

        for (auto a = aa.begin(); a != aa.end(); ++a) {
            for (auto b = a+1; b != aa.end(); ++b) {
                XY d = *b; d -= *a;

                if (part1) {
                    XY antinode = *a;
                    antinode -= d;
                    if (antinode.inBounds(w, h)) {
                        antinodes[antinode.index(w, h)] = true;
                    }
                    
                    antinode = *b;
                    antinode += d;
                    if (antinode.inBounds(w, h)) {
                        antinodes[antinode.index(w, h)] = true;
                    }
                } else {
                    XY antinode = *a;
                    while (antinode.inBounds(w, h)) {
                        antinodes[antinode.index(w, h)] = true;
                        antinode -= d; 
                    }

                    antinode = *a;
                    while (antinode.inBounds(w, h)) {
                        antinodes[antinode.index(w, h)] = true;
                        antinode += d; 
                    }
                }
            }
        }
    }

    cout << count(antinodes.begin(), antinodes.end(), true) << endl;

    return 0;
}