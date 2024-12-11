#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

bool isOrdered(const vector<int>& update, const vector<set<int>>& orders) {
    for (auto a = update.cbegin(); a != update.cend(); ++a) {
        for (auto b = a+1; b != update.cend(); ++b) {
            const auto& o = orders[*b];
            if (o.find(*a) != o.end()) {
                return false;
            }
        }
    }

    return true;
}

void restoreOrder(vector<int>& update, const vector<set<int>>& orders) {
again:
    for (auto a = update.begin(); a != update.end(); ++a) {
        for (auto b = a+1; b != update.end(); ++b) {
            const auto& o = orders[*b];
            if (o.find(*a) != o.end()) {
                swap(*a, *b);
                goto again;
            }
        }
    }
}

int main(int argc, char** argv)
{
    const bool part1 = (argc >= 2) && (argv[1] == string("1"));

    int sum = 0;

    vector<set<int>> orders(100);
    string line;
    bool readingOrders = true;
    while (getline(cin, line)) {
        if (line == "") {
            readingOrders = false;
        } else if (readingOrders) {
            orders[stoi(line.substr(0, 2))].insert(stoi(line.substr(3, 2)));
        } else {
            const int size = (line.size()+1)/3;
            vector<int> update(size);
            for (int i = 0; i < size; ++i) {
                update[i] = stoi(line.substr(3*i, 2));
            }

            if (part1) {
                if (isOrdered(update, orders)) {
                    sum += update[size/2];
                }
            } else {
                if (!isOrdered(update, orders)) {
                    restoreOrder(update, orders);
                    sum += update[size/2];
                }
            }
        }
    }

    cout << sum << endl;

    return 0;
}