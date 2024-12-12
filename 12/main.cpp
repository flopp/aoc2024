#include <iostream>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

struct XY {
    int x, y;
    bool operator==(const XY& other) const {
        return x == other.x && y == other.y;
    }

    XY left() const { return XY{x-1, y}; }
    XY right() const { return XY{x+1, y}; }
    XY up() const { return XY{x, y-1}; }
    XY down() const { return XY{x, y+1}; }
    XY dir4(int d) const {
        if (d == 0) {return right();}
        if (d == 1) {return down();}
        if (d == 2) {return left();}
        if (d == 3) {return up();}
        return *this;
    }

    bool inBounds(int minX, int maxX, int minY, int maxY) const {
        return minX <= x && x <= maxX && minY <= y && y <= maxY;
    }
};

struct HashXY {
    size_t operator()(const XY& xy) const {
        return (size_t(xy.y) << 16) ^ size_t(xy.x);
   }
};

int main(int argc, char** argv)
{
    const bool part1 = (argc >= 2) && (argv[1] == string("1"));

    vector<string> lines;
    string line;
    while (getline(cin, line)) {
        lines.push_back(line);
    }

    // add a . border to avoid bounds checking
    int h = 2 + lines.size();
    int w = 2 + lines.front().size();
    vector<string> grid;
    grid.reserve(h);
    grid.push_back(string(w, '.'));
    for (int y = 0; y < h-2; ++y) {
        grid.push_back("." + lines[y] + ".");
    }
    grid.push_back(string(w, '.'));

    int totalPrice = 0;

    stack<XY> pending;
    unordered_set<XY, HashXY> region;
    auto markGrid = grid;
    XY xy;
    for (xy.y = 1; xy.y < h-1; ++xy.y) {
        for (xy.x = 1; xy.x < w-1; ++xy.x) {
            const auto c = markGrid[xy.y][xy.x];
            if (c == '.') {
                continue;
            }

            // explore region starting at xy
            // collect in "region", mark visited as '.' in markGrid
            region.clear();
            region.insert(xy);
            markGrid[xy.y][xy.x] = '.';
            pending.push(xy);
            while (!pending.empty()) {
                const XY field = pending.top();
                pending.pop();
                for (int d = 0; d < 4; ++d) {
                    const XY next = field.dir4(d);
                    if (markGrid[next.y][next.x] == c) {
                        region.insert(next);
                        markGrid[next.y][next.x] = '.';
                        pending.push(next);
                    }
                }
            }

            // determine fence length
            int fence = 0;
            if (part1) {
                for (const auto& field: region) {
                    for (int d = 0; d < 4; ++d) {
                        const XY next = field.dir4(d);
                        if (grid[next.y][next.x] != c) {
                            ++fence;
                        }
                    }
                }
            } else {
            
            }
            totalPrice += region.size() * fence;;
        }
    }

    cout << totalPrice << endl;

    return 0;
}