#include <cmath>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

struct XY {
    int x, y;
    bool operator==(const XY& other) const {
        return x == other.x && y == other.y;
    }

    XY& operator+=(const XY& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    float dist(const XY& other) const {
        float dx = x - other.x;
        float dy = y - other.y;
        return sqrt(dx*dx + dy*dy);
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

void display(const vector<XY>& ps, int w, int h) {
    vector<bool> grid(w*h, false);

    for (const auto& p: ps) {
        grid[p.x+w*p.y] = true;
    }

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (grid[x+w*y]) {
                cout << "#";
            } else {
                cout << ".";
            }
        }
        cout << endl;
    }
}

float centroidDist(const vector<XY>& ps) {
    XY c{0, 0};
    for (const auto& p: ps) {
        c += p;
    }
    
    c.x /= ps.size();
    c.y /= ps.size();

    float dist_sum = 0;
    for (const auto& p: ps) {
        dist_sum += c.dist(p);
    }
    return dist_sum / ps.size();
}

int main(int argc, char** argv)
{
    const bool part1 = (argc >= 2) && (argv[1] == string("1"));
    const int w = (argc >= 3) ? stoi(argv[2]) : 0;
    const int h = (argc >= 4) ? stoi(argv[3]) : 0;

    const auto re = regex("^p=(-?\\d+),(-?\\d+) v=(-?\\d+),(-?\\d+)$");
    vector<XY> ps, vs;
    string line;
    while (getline(cin, line)) {
        smatch m;
        if (regex_match(line, m, re)) {
            ps.push_back(XY{stoi(m[1]), stoi(m[2])});
            vs.push_back(XY{stoi(m[3]), stoi(m[4])});
        } else {
            cerr << "BAD LINE <" << line << ">" << endl;
            return 0; 
        }
    }

    if (part1) {
        const int iterations = 100;
        vector<XY> p2s;
        for (int i = 0; i < ps.size(); ++i) {
            const auto& p = ps[i];
            const auto& v = vs[i];
            XY xy{((p.x+iterations*v.x)%w+w)%w, ((p.y+iterations*v.y)%h+h)%h};
            if  (xy.x < 0 || xy.y < 0) {
                return 0;
            }
            p2s.push_back(xy);
        }

        int nw = 0;
        int ne = 0;
        int sw = 0;
        int se = 0;
        int w2 = w/2;
        int h2 = h/2;

        for (const auto& p: p2s) {
            if (p.y < h2) {
                if (p.x < w2) {
                    ++nw;
                } else if(p.x> w2) {
                    ++ne;
                }
            } else if (p.y > h2) {
                if (p.x < w2) {
                    ++sw;
                } else if(p.x> w2) {
                    ++se;
                }
            }
        }

        cout << (nw*ne*sw*se) << endl;
    } else {
        // try to minimize the average dist to the centroid
        float min_dist = -1;
        for (int loop = 0; true; ++loop) {
            float d = centroidDist(ps);
            if (min_dist < 0 || d < min_dist) {
                min_dist = d;
                cout << "LOOP " << loop << endl;
                display(ps, w, h);
            }

            for (int i = 0; i < ps.size(); ++i) {
                auto& p = ps[i];
                const auto& v = vs[i];
                p.x = (p.x + v.x + w) % w;
                p.y = (p.y + v.y + h) % h;
            }
        }        
    }
 
    return 0;
}