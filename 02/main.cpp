#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

typedef string S;
typedef int T;
typedef vector<T> Report;

Report parseReport(const S& s) {
    Report res;
    istringstream iss(s);
    T i;
    while (iss >> i) {
        res.push_back(i);
    }
    return res;
}

bool isSafe(const Report& report) {
    const int s = report.size();
    if (s < 2) {
        return true;
    }

    const bool inc = report[0] <= report[1];
    for (int i = 1; i < s; ++i) {
        const int d = inc ? (report[i] - report[i-1]) : (report[i-1] - report[i]);
        if (d < 1 || d > 3) {
            return false;
        }
    }

    return true;
}


bool isSafeDampened(const Report& report) {
    if (isSafe(report)) {
        return true;
    }

    const int s = report.size();
    Report report2;
    report2.reserve(s - 1);
    for (int i = 0; i < s; ++i) {
        report2.clear();
        for (int j = 0; j < s; ++j) {
            if (j != i) report2.push_back(report[j]);
        }
        if (isSafe(report2)) {
            return true;
        }
    }

    return false;
}

int main(int argc, char** argv)
{
    const bool part1 = (argc >= 2) && (argv[1] == S("1"));

    vector<Report> reports;
    S line;
    while (getline(cin, line)) {
        reports.push_back(parseReport(line));
    }

    if (part1) {
        cout << count_if(reports.begin(), reports.end(), isSafe) << endl;
    } else {
        cout << count_if(reports.begin(), reports.end(), isSafeDampened) << endl;
    }

    return 0;
}