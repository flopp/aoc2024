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

    XY n()  const { return XY{x, y-1}; }
    XY ne() const { return XY{x+1, y-1}; }
    XY e()  const { return XY{x+1, y}; }
    XY se() const { return XY{x+1, y+1}; }
    XY s()  const { return XY{x, y+1}; }
    XY sw() const { return XY{x-1, y+1}; }
    XY w()  const { return XY{x-1, y}; }
    XY nw() const { return XY{x-1, y-1}; }
    XY dir4(int d) const {
        if (d == 0) {return e();}
        if (d == 1) {return s();}
        if (d == 2) {return w();}
        if (d == 3) {return n();}
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
                // count border sides
                for (const auto& field: region) {
                    for (int d = 0; d < 4; ++d) {
                        const XY next = field.dir4(d);
                        if (grid[next.y][next.x] != c) {
                            ++fence;
                        }
                    }
                }
            } else {
                // count corners, because #sides = #corners
                for (const auto& field: region) {
                    XY n  = field.n();
                    XY ne = field.ne();
                    XY e  = field.e();
                    XY se = field.se();
                    XY s  = field.s();
                    XY sw = field.sw();
                    XY w  = field.w();
                    XY nw = field.nw();

                    bool xn  = grid[n.y][n.x] != c;
                    bool xne = grid[ne.y][ne.x] != c;
                    bool xe  = grid[e.y][e.x] != c;
                    bool xse = grid[se.y][se.x] != c;
                    bool xs  = grid[s.y][s.x] != c;
                    bool xsw = grid[sw.y][sw.x] != c;
                    bool xw  = grid[w.y][w.x] != c;
                    bool xnw = grid[nw.y][nw.x] != c;

                    // convex && concave corners
                    if ((xn && xw) || (xnw && !xn && !xw)) ++fence;
                    if ((xn && xe) || (xne && !xn && !xe)) ++fence;
                    if ((xs && xe) || (xse && !xs && !xe)) ++fence;
                    if ((xs && xw) || (xsw && !xs && !xw)) ++fence;
                }
            }
            totalPrice += region.size() * fence;
        }
    }

    cout << totalPrice << endl;

    return 0;
}