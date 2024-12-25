#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;


bool is_possible(const string& pattern, const vector<string>& towels, unordered_map<string, long>& cache) {
    if (pattern.empty()) {
        return true;
    }

    auto it = cache.find(pattern);
    if (it != cache.end()) {
        return (it->second == 1);
    }

    for (const auto& towel: towels) {
        if (pattern.starts_with(towel) && is_possible(pattern.substr(towel.size()), towels, cache)) {
            cache.insert_or_assign(pattern, 1);
            return true;
        }
    }

    cache.insert_or_assign(pattern, 0);
    return false;
}

long count_possibilities(const string& pattern, const vector<string>& towels, unordered_map<string, long>& cache) {
    if (pattern.empty()) {
        return 1;
    }

    auto it = cache.find(pattern);
    if (it != cache.end()) {
        return it->second;
    }

    long count = 0;
    for (const auto& towel: towels) {
        if (pattern.starts_with(towel)) {
            count += count_possibilities(pattern.substr(towel.size()), towels, cache);
        }
    }
    cache.insert_or_assign(pattern, count);
    
    return count;
}

int main(int argc, char** argv)
{
    const bool part1 = (argc >= 2) && (argv[1] == string("1"));

    long result = 0;
    vector<string> towels;
    unordered_map<string, long> cache;

    string line;
    while (getline(cin, line)) {
        if (towels.empty()) {
            for (size_t i = 0; true; /**/) {
                size_t j = line.find_first_of(',', i);
                if (j == string::npos) {
                    towels.push_back(line.substr(i));
                    break;
                } else {
                    towels.push_back(line.substr(i, j-i));
                    i = j+2;
                }
            }
        } else if (line.empty()) {
            //
        } else {
            if (part1) {
                if (is_possible(line, towels, cache)) {
                    ++result;
                }
            } else {
                result += count_possibilities(line, towels, cache);
            }
        }
    }

    cout << result << endl;
    return 0;
}