#include <iostream>
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

    bool inBounds(int minX, int maxX, int minY, int maxY) const {
        return minX <= x && x <= maxX && minY <= y && y <= maxY;
    }
};

struct HashXY {
    size_t operator()(const XY& xy) const {
        return (size_t(xy.y) << 16) ^ size_t(xy.x);
   }
};

typedef unordered_set<XY, HashXY> SetXY;

void findSummits1(const vector<string>& grid, int w, int h, XY xy, SetXY& summits)
{
    const auto& c = grid[xy.y][xy.x];
    if (c == '9') {
        summits.insert(xy);
        return;
    } else if (c > '9') {
        return;
    }

    XY next;
    
    next = xy.left();
    if (next.inBounds(0, w-1, 0, h-1) && grid[next.y][next.x] == c+1) {
        findSummits1(grid, w, h, next, summits);
    }
    
    next = xy.right();
    if (next.inBounds(0, w-1, 0, h-1) && grid[next.y][next.x] == c+1) {
        findSummits1(grid, w, h, next, summits);
    }
    
    next = xy.up();
    if (next.inBounds(0, w-1, 0, h-1) && grid[next.y][next.x] == c+1) {
        findSummits1(grid, w, h, next, summits);
    }
    
    next = xy.down();
    if (next.inBounds(0, w-1, 0, h-1) && grid[next.y][next.x] == c+1) {
        findSummits1(grid, w, h, next, summits);
    }
}


int findSummits2(const vector<string>& grid, int w, int h, XY xy)
{
    const auto& c = grid[xy.y][xy.x];
    if (c == '9') {
        return 1;
    } else if (c > '9') {
        return 0;
    }

    int res = 0;
    XY next;
    
    next = xy.left();
    if (next.inBounds(0, w-1, 0, h-1) && grid[next.y][next.x] == c+1) {
        res += findSummits2(grid, w, h, next);
    }
    
    next = xy.right();
    if (next.inBounds(0, w-1, 0, h-1) && grid[next.y][next.x] == c+1) {
        res += findSummits2(grid, w, h, next);
    }
    
    next = xy.up();
    if (next.inBounds(0, w-1, 0, h-1) && grid[next.y][next.x] == c+1) {
        res += findSummits2(grid, w, h, next);
    }
    
    next = xy.down();
    if (next.inBounds(0, w-1, 0, h-1) && grid[next.y][next.x] == c+1) {
        res += findSummits2(grid, w, h, next);
    }

    return res;
}

int main(int argc, char** argv)
{
    const bool part1 = (argc >= 2) && (argv[1] == string("1"));

    vector<string> grid;
    string line;
    while (getline(cin, line)) {
        grid.push_back(line);
    }
    const int h = grid.size();
    const int w = grid.front().size();

    int scores = 0;

    if (part1) {
        SetXY summits;
        XY xy;
        for (xy.y = 0; xy.y < h; ++xy.y) {
            for (xy.x = 0; xy.x < w; ++xy.x) {
                if (grid[xy.y][xy.x] != '0') {
                    continue;
                }
                summits.clear();
                findSummits1(grid, w, h, xy, summits);
                scores += summits.size();
            }
        }
    } else {
        XY xy;
        for (xy.y = 0; xy.y < h; ++xy.y) {
            for (xy.x = 0; xy.x < w; ++xy.x) {
                if (grid[xy.y][xy.x] != '0') {
                    continue;
                }
                scores += findSummits2(grid, w, h, xy);
            }
        }
    }

    cout << scores << endl;

    return 0;
}