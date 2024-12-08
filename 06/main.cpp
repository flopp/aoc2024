#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef size_t T;

T encode(T d, T x, T y) {
    return (d << 16) | (x << 8) | y; 
}
void decode(T e, T& d, T& x, T& y) {
    d = 0xFF & (e >> 16);
    x = 0xFF & (e >> 8);
    y = 0xFF & e;
}

bool nextDXY(T d, T x, T y, T w, T h, T& dd, T& xx, T& yy) {
    switch (d) {
        case 0: // up
            if (y == 0) {
                return false;
            }
            xx = x;
            yy = y - 1;
            dd = 1;
            break;
        case 1: // right
            xx = x + 1;
            if (xx >= w) {
                return false;
            }
            yy = y;
            dd = 2;
            break;
        case 2: // down
            xx = x; 
            yy = y + 1;
            if (yy >= h) {
                return false;
            }
            dd = 3;
            break;
        case 3: // left
            if (x == 0) {
                return false;
            }
            xx = x - 1;
            yy = y;
            dd = 0;
            break;
    }
    return true;
}

bool simulate(T w, T h, const vector<bool>& wallsXY, T pos, vector<bool>& visitedXY, vector<bool>& visitedDXY)
{
    T d, x, y;
    T dd, xx, yy;
    T xy;

    decode(pos, d, x ,y);    
    visitedXY.assign(visitedXY.size(), false);
    visitedXY[encode(0, x, y)] = true;

    visitedDXY.assign(visitedDXY.size(), false);
    visitedDXY[pos] = true;

    while (true) {
        decode(pos, d, x, y);
        if (nextDXY(d, x, y, w, h, dd, xx, yy)) {
            xy = encode(0, xx, yy);
            if (wallsXY[xy]) {
                pos = encode(dd, x, y);
            } else {
                visitedXY[xy] = true;
                pos = encode(d, xx, yy);

            }

            // loop?
            if (visitedDXY[pos]) {
                return true;
            }
            visitedDXY[pos] = true;       
        } else {
            return false;
        }
    }
}

int main(int argc, char** argv)
{
    const bool part1 = (argc >= 2) && (argv[1] == string("1"));

    vector<string> grid;
    string line;
    while (getline(cin, line)) {
        grid.push_back(line);
    }

    const T w = grid[0].size();
    const T h = grid.size();
    assert(w <= 0xFF);
    assert(h <= 0xFF);

    T start = 0;
    vector<bool> wallsXY(0xFF*0xFF, false);
    for (T y = 0; y < h; ++y) {
        const auto& row = grid[y];
        for (T x = 0; x < w; ++x) {
            const auto& c = row[x];
            if (c == '^') {
                start = encode(0, x, y);
            } else if (c == '#') {
                wallsXY[encode(0, x, y)] = true;
            }
        }
    }

    vector<bool> visitedXY(0xFF*0xFF, false);
    vector<bool> visitedDXY(4*0xFF*0xFF, false);

    simulate(w, h, wallsXY, start, visitedXY, visitedDXY);
    if (part1) {
        T count = 0;
        for (const auto& v : visitedXY) {
            if (v) {
                ++count;
            }
        }
        cout << count << endl;
    } else {
        T count = 0;
        auto candidates = visitedXY;
        candidates[start] = false;
        for (T y = 0; y < h; ++y) {
            for (T x = 0; x < w; ++x) {
                T xy = encode(0, x, y);
                if (!candidates[xy]) {
                    continue;
                }

                wallsXY[xy] = true;
                if (simulate(w, h, wallsXY, start, visitedXY, visitedDXY)) {
                    ++count;
                }
                wallsXY[xy] = false; 
            }
        }

        cout << count << endl; 
    }

    return 0;
}