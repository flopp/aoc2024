#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print(vector<int>& files) {
    for (const auto& id: files) {
        if (id < 0) {
            cout << ".";
        } else {
            cout << id;
        }
    }
    cout << endl;
}

long checksum(const vector<int>& files) {
    long res = 0;
    const int size = files.size();
    for (int i = 0; i < size; ++i) {
        if (files[i] < 0) {
            continue;
        }
        res += i * files[i];
    }
    return res;
}

int main(int argc, char** argv)
{
    const bool part1 = (argc >= 2) && (argv[1] == string("1"));

    string line;
    getline(cin, line);

    vector<int> files;
    int id = 0;
    bool file = true;
    for (const auto& c: line) {
        const int n = c - '0';
        if (file) {
            for (int i = 0; i < n; ++i) {
                files.push_back(id);
            }
            ++id;
        } else {
            for (int i = 0; i < n; ++i) {
                files.push_back(-1);
            }
        }
        file = !file;
    }

    if (part1) {
        int i = 0;
        int j = files.size() - 1;
        while (i < j) {
            if (files[i] >= 0) {
                ++i;
            } else if (files[j] < 0) {
                --j;
            } else {
                swap(files[i], files[j]);
                --j;
                ++i;
            }
        }
    } else {
        int i = 0;
        int j = files.size() - 1;
        while (i < j) {
            if (files[i] >= 0) {
                ++i;
            } else if (files[j] < 0) {
                --j;
            } else {
                // determine file size
                const int id = files[j];
                int fileSize = 0;
                while (fileSize <= j && files[j-fileSize] == id) {
                    ++fileSize;
                }

                // find first "hole" of at least "fileSize" 
                int hole = i;
                int holeSize = 0;
                while (hole < j) {
                    if (files[hole] >= 0) {
                        holeSize = 0;
                        ++hole;
                    } else {
                        ++holeSize;
                        ++hole;
                        if (holeSize >= fileSize) {
                            break;
                        }
                    }
                }

                if (holeSize >= fileSize) {
                    // move file to hole
                    for (int k = 0; k < fileSize; ++k) {
                        swap(files[hole-holeSize+k], files[j]);
                        --j; 
                    }
                } else {
                    // skip file
                    j -= fileSize;
                }
            }
        }
    }

    cout << checksum(files) << endl;

    return 0;
}