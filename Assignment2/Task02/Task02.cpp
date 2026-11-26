#include <iostream>
#include <vector>
using namespace std;

int& markAt(int marks[], int index) {
    return marks[index];
}

// SAFE: returns a reference to an element that belongs to the caller.
int& highestMark(int marks[], int size) {
    int best = 0;
    for (int i = 1; i < size; ++i) {
        if (marks[i] > marks[best]) best = i;
    }
    return marks[best];
}

// DANGEROUS EXAMPLE (do not use):
// int& invalidReference() {
//     int local = 50;
//     return local; // dangling reference: local is destroyed on return
// }

int highestMarkIndex(const vector<int>& marks) {
    if (marks.empty()) return -1;
    int best = 0;
    for (int i = 1; i < static_cast<int>(marks.size()); ++i) {
        if (marks[i] > marks[best]) best = i;
    }
    return best;
}

int main() {
    int marks[5] = {72, 88, 91, 67, 84};

    cout << "Original marks: ";
    for (int mark : marks) cout << mark << ' ';
    cout << '\n';

    markAt(marks, 1) = 95;
    cout << "After moderation: ";
    for (int mark : marks) cout << mark << ' ';
    cout << '\n';

    highestMark(marks, 5) = 100;
    cout << "After updating highest mark: ";
    for (int mark : marks) cout << mark << ' ';
    cout << '\n';

    const vector<int> scores = {60, 75, 89, 81};
    int index = highestMarkIndex(scores);
    if (index != -1)
        cout << "Highest score: " << scores[index]
             << " at index " << index << '\n';

    vector<int> values = {10, 20, 30};
    int savedIndex = 1;
    values.push_back(40); // an index remains meaningful after reallocation
    cout << "Value at saved index after push_back: "
         << values[savedIndex] << '\n';

    cout << "A reference to a local variable must never be returned.\n";
    return 0;
}