#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef long T;
typedef vector<T> EQ;
#define S2T stol

EQ splitEquation(const string& line)
{
    EQ v;
    size_t s = 0;
    size_t size = 0;
    for (size_t i = 0; i != line.size(); ++i) {
        if (isdigit(line[i])) {
            if (size > 0) {
                ++size;
            } else {
                s = i;
                size = 1;
            }
        } else if (size > 0) {
            v.push_back(S2T(line.substr(s, size)));
            size = 0;
        }
    }
    if (size > 0) {
        v.push_back(S2T(line.substr(s, size)));
    }
    return v;
}

bool rec1(const EQ& equation, T target, T current, size_t i) {
    if (current > target) {
        return false;
    }
    if (i == equation.size()) {
        return current == target;
    } 

    return
        rec1(equation, target, current + equation[i], i+1)
        ||
        rec1(equation, target, current * equation[i], i+1);
}

T concat(T a, T b) {
    T shift = 10;
    while (shift <= b) { shift *= 10; }
    return a * shift + b;
}

bool rec2(const EQ& equation, T target, T current, size_t i) {
    if (i == equation.size()) {
        return current == target;
    } 
    if (current > target) {
        return false;
    }

    return
        rec2(equation, target, concat(current, equation[i]), i+1)
        ||
        rec2(equation, target, current + equation[i], i+1)
        ||
        rec2(equation, target, current * equation[i], i+1);
}

bool checkEquation(bool part1, const EQ& equation) {
    size_t numOperands = equation.size() - 2;
    assert(numOperands >= 1);
    
    if (part1) {
        return rec1(equation, equation[0], equation[1], 2);
    }
    
    return rec2(equation, equation[0], equation[1], 2);
}

int main(int argc, char** argv)
{
    const bool part1 = (argc >= 2) && (argv[1] == string("1"));

    T total = 0;
    string line;
    while (getline(cin, line)) {
        const EQ eq = splitEquation(line);
        if (checkEquation(part1, eq)) {
            total += eq.front();
        }
    }
    cout << total << endl;

    return 0;
}