#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
    const bool part1 = (argc >= 2) && (argv[1] == string("1"));

    vector<string> grid;
    string line;
    while (getline(cin, line)) {
        grid.push_back(line);
    }

    const int w = grid.front().size();
    const int h = grid.size();

    int count = 0;

    if (part1) {
        const string needle = "XMAS";
        for (int d = 0; d < 8; ++d) {
            int dx = 0;
            int dy = 0;
            switch (d) {
                case 0:
                    dx = 1;
                    break;
                case 1:
                    dx = 1;
                    dy = 1;
                    break;
                case 2:
                    dy = 1;
                    break;
                case 3:
                    dx = -1;
                    dy = 1;
                    break;
                case 4:
                    dx = -1;
                    break;
                case 5:
                    dx = -1;
                    dy = -1;
                    break;
                case 6:
                    dy = -1;
                    break;
                case 7:
                    dx = 1;
                    dy = -1;
                    break;
            }
            for (int y = 0; y < h; ++y) {
                for (int x = 0; x < w; ++x) {
                    int xx = x;
                    int yy = y;
                    bool ok = true;
                    for (const auto& c: needle) {
                        if (xx < 0 || xx >= w || yy < 0 || yy >= h || grid[yy][xx] != c) {
                            ok = false;
                            break;
                        }
                        xx += dx;
                        yy += dy;
                    }
                    if (ok) {
                        ++count;
                    }
                }
            }
        }
    } else {
        for (int y = 1; y+1 < h; ++y) {
            for (int x = 1; x+1 < w; ++x) {
                if (grid[y][x] != 'A') {
                    continue;
                }

                const char& a0 = grid[y-1][x-1];
                const char& a1 = grid[y+1][x+1];
                if (!(a0 == 'M' && a1 == 'S') && !(a0 == 'S' && a1 == 'M')) {
                    continue;
                }
                
                const char& b0 = grid[y-1][x+1];
                const char& b1 = grid[y+1][x-1];
                if (!(b0 == 'M' && b1 == 'S') && !(b0 == 'S' && b1 == 'M')) {
                    continue;
                }

                ++count;
            }
        }
    }

    cout << count << endl;

    return 0;
}