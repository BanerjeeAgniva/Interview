#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int countBlocks(const set<int>& houses) {
    if (houses.empty()) return 0;

    int blocks = 1;
    auto it = houses.begin();
    int prev = *it;

    for (++it; it != houses.end(); ++it) {
        if (*it != prev + 1) {
            blocks++;
        }
        prev = *it;
    }
    return blocks;
}

vector<int> solve(vector<int>& v, vector<int>& q) {
    set<int> houses(v.begin(), v.end());  
    vector<int> results;

    for (int house : q) {
        if (houses.find(house) != houses.end()) {
            houses.erase(house);  
        }
        results.push_back(countBlocks(houses)); 
    }

    return results;
}

int main() {
    vector<int> v = {2, 4, 5, 6, 7};
    vector<int> q = {5, 6, 2};
    vector<int> answer = solve(v, q);
    for (int blocks : answer) {
        cout << blocks << " ";
    }
    cout << endl;
    return 0;
}
