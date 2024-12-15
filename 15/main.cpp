#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct XY {
    int x{0}, y{0};

    bool operator==(const XY& other) const {
        return x == other.x && y == other.y;
    }

    XY& operator+=(const XY& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    XY operator+(const XY& other) const {
        XY res = *this;
        return res += other;
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

bool pushBox(vector<string>& grid, const XY& pos, const XY& dir) {
    switch (grid[pos.y][pos.x]) {
        case '.': return true;
        case '#': return false;
    }

    XY next = pos + dir;
    if (pushBox(grid, next, dir)) {
        swap(grid[next.y][next.x], grid[pos.y][pos.x]);
        return true;
    }

    return false;
}


bool pushBox_part2(vector<string>& grid, const set<int>& xs, int y, int dy) {
    if (xs.empty()) {
        return true;
    }

    set<int> xs2;
    for (const auto& x: xs) {
        const auto& c = grid[y][x];
        if (c == '#') {
            return false;
        } 
        if (c == '[') {
            xs2.insert(x);
            xs2.insert(x+1);
        } else if (c == ']') {
            xs2.insert(x);
            xs2.insert(x-1);
        }
    }

    if (pushBox_part2(grid, xs2, y+dy, dy)) {
        for (const auto& x: xs2) {
            swap(grid[y][x], grid[y+dy][x]);
        }
        return true;
    }

    return false;
}

int main(int argc, char** argv)
{
    const bool part1 = (argc >= 2) && (argv[1] == string("1"));

    XY robot;    
    vector<string> grid;
    string moves;

    // read input
    bool readGrid = true;
    string line;
    while (getline(cin, line)) {
        if (line.empty()) {
            readGrid = false;
        } else if (readGrid) {
            string row;
            for (size_t x = 0; x < line.size(); ++x) {
                switch (line[x]) {
                    case '#':
                        if (part1) {
                            row += "#";
                        } else {
                            row += "##";
                        }
                        break;
                    case '.':
                        if (part1) {
                            row += ".";
                        } else {
                            row += "..";
                        }
                        break;
                    case 'O':
                        if (part1) {
                            row += "O";
                        } else {
                            row += "[]";
                        }
                        break;
                    case '@':
                        if (part1) {
                            row += ".";
                            robot.x = x;
                        } else {
                            row += "..";
                            robot.x = 2 * x;
                        }
                        robot.y = grid.size();
                        break;
                }
            }
            grid.push_back(row);
        } else {
            moves += line;
        }
    }

    // move
    for (const auto& m: moves) {
        XY dir;
        switch (m) {
            case '^': dir = dir.n(); break;
            case '>': dir = dir.e(); break;
            case 'v': dir = dir.s(); break;
            case '<': dir = dir.w(); break;
            default: continue;
        }

        if (part1) {
            if (pushBox(grid, robot+dir, dir)) {
                robot += dir;
            }
        } else {
            if (dir.y == 0) {
                if (pushBox(grid, robot+dir, dir)) {
                   robot += dir;
                }
            } else {
                set<int> xs;
                xs.insert(robot.x);
                if (pushBox_part2(grid, xs, robot.y+dir.y, dir.y)) {
                    robot += dir;
                }    
            }
        }
    }

    // evaluate
    int value = 0;
    int y = 0;
    for (const auto& row: grid) {
        int x = 0;
        for (const auto& cell: row) {
            if ((cell == 'O') || (cell == '[')) {
                value += 100 * y + x;
            }
            ++x;
        }
        ++y;
    }
    cout << value << endl;

    return 0;
}
