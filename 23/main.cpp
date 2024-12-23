#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

struct Node;
typedef unordered_set<Node*> NodeSet;

struct Node {
    Node(const string& n): name{n} {}

    string name;
    NodeSet edges;
    bool mark{false};
    bool done{false};
};

void BronKerbosch1(NodeSet R, NodeSet P, NodeSet X, NodeSet& maxClique) {
    if (P.empty() && X.empty()) {
        if (R.size() > maxClique.size()) {
            maxClique = R;
        }
    }
    for (auto v = P.begin(); v != P.end(); /**/) {
        NodeSet R2 = R; R2.insert(*v);
        NodeSet P2;
        NodeSet X2;
        for (auto n: (*v)->edges) {
            if (P.find(n) != P.end()) P2.insert(n);
            if (X.find(n) != X.end()) X2.insert(n);
        }

        BronKerbosch1(R2, P2, X2, maxClique);

        X.insert(*v);
        v = P.erase(v);
    }
}

int main(int argc, char** argv)
{
    const bool part1 = (argc >= 2) && (argv[1] == string("1"));

    vector<Node*> nodes;
    unordered_map<string, Node*> nodeMap;

    string line;
    while (getline(cin, line)) {
        string s1 = line.substr(0, 2);
        string s2 = line.substr(3, 2);

        Node* n1;
        auto it1 = nodeMap.find(s1);
        if (it1 != nodeMap.end()) {
            n1 = it1->second;
        } else {
            n1 = new Node{s1};
            nodeMap[s1] = n1;
            nodes.push_back(n1);
        }

        Node* n2;
        auto it2 = nodeMap.find(s2);
        if (it2 != nodeMap.end()) {
            n2 = it2->second;
        } else {
            n2 = new Node{s2};
            nodeMap[s2] = n2;
            nodes.push_back(n2);
        }

        n1->edges.insert(n2);
        n2->edges.insert(n1);
    }

    if (part1) {
        // 3-cliques / triangles
        int count = 0;
        for (auto a: nodes) {
            if (a->done) continue;
            a->done = true;

            for (auto n: a->edges) {
                n->mark = !n->done;
            }

            for (auto b: a->edges) {
                if (!b->mark) continue;
                b->mark = false;
                for (auto c: b->edges) {
                    if (!c->mark) continue;

                    if (a->name.front() == 't' || b->name.front() == 't' || c->name.front() == 't') {
                        ++count;
                    }
                }
            }

            for (auto n: a->edges) {
                n->mark = false;
            }
        }
        cout << count << endl;
    } else {
        // max clique
        NodeSet R;
        NodeSet P{nodes.begin(), nodes.end()};
        NodeSet X;
        NodeSet maxClique;
        BronKerbosch1(R,P,X, maxClique);

        vector<string> ss;
        for (auto n: maxClique) {
            ss.push_back(n->name);
        }
        sort(ss.begin(), ss.end());

        bool first = true;
        for (auto n: ss) {
            if (!first) cout << ",";
            first = false;
            cout << n;
        }
        cout << endl;    
    }
    return 0;
}