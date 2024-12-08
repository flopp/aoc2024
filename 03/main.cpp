#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
    const bool part1 = (argc >= 2) && (argv[1] == string("1"));

    regex re_mult("(mul\\(\\d\\d?\\d?,\\d\\d?\\d?\\))");
    regex re_mult_do_dont("(mul\\(\\d\\d?\\d?,\\d\\d?\\d?\\))|(do\\(\\))|(don't\\(\\))");
    regex re_mult2("mul\\((\\d\\d?\\d?),(\\d\\d?\\d?)\\)");
    smatch res;

    int sum = 0;
    bool enabled = true;
    auto it_end = sregex_iterator();
    string line;
    while (getline(cin, line)) {
        if (part1) {
            auto it_begin = sregex_iterator(line.begin(), line.end(), re_mult);
            for (auto i = it_begin; i != it_end; ++i) {
                const string m = i->str();
                regex_match(m, res, re_mult2);
                sum += stoi(res[1].str()) * stoi(res[2].str());
            }
        } else {
            auto it_begin = sregex_iterator(line.begin(), line.end(), re_mult_do_dont);
            for (auto i = it_begin; i != it_end; ++i) {
                const string m = i->str();
                if (m == "do()") {
                    enabled = true;
                } else if (m == "don't()") {
                    enabled = false;
                } else if (enabled) {
                    regex_match(m, res, re_mult2);
                    sum += stoi(res[1].str()) * stoi(res[2].str());
                }
            }
        }
    }

    cout << sum << endl;

    return 0;
}