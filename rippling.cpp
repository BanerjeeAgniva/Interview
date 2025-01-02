
#include <iostream>
#include <string>
#include <deque>
using namespace std;

string lexicographicallySmallest(string s) {
    deque<char> t;
    string answer = "";

    for (char c : s) {
        t.push_back(c);
        // Check if moving the last character from t to answer is better
        while (!t.empty() && (answer.empty() || t.back() <= answer.back())) {
            answer += t.back();
            t.pop_back();
        }
    }

    // Append the remaining characters from t to the answer
    while (!t.empty()) {
        answer += t.back();
        t.pop_back();
    }

    return answer;
}

int main() {
    string s = "zyxw";
    string result = lexicographicallySmallest(s);
    cout << "Result: " << result << endl;
    return 0;
}
