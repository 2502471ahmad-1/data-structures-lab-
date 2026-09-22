#include <iostream>
#include <string>

using namespace std;

int main() {
    int marks[6][4] = {
        {85, 90, 78, 92},
        {70, 65, 80, 75},
        {88, 92, 95, 91},
        {60, 72, 68, 80},
        {95, 88, 84, 89},
        {78, 82, 89, 87}
    };
    string subjects[4] = {"English", "Math", "Programming", "AI"};

    cout << "Student\tEng\tMath\tProg\tAI\n";
    for (int i = 0; i < 6; i++) {
        cout << "S" << i + 1 << "\t";
        for (int j = 0; j < 4; j++) {
            cout << marks[i][j] << "\t";
        }
        cout << endl;
    }

    int maxTotal = -1;
    int topStudent = 0;

    cout << "\nStudent Totals and Averages:\n";
    for (int i = 0; i < 6; i++) {
        int total = 0;
        for (int j = 0; j < 4; j++) {
            total += marks[i][j];
        }
        double avg = total / 4.0;
        cout << "Student " << i + 1 << " - Total: " << total << ", Avg: " << avg << endl;

        if (total > maxTotal) {
            maxTotal = total;
            topStudent = i + 1;
        }
    }

    cout << "\nHighest Marks in Each Subject:\n";
    for (int j = 0; j < 4; j++) {
        int highest = marks[0][j];
        for (int i = 1; i < 6; i++) {
            if (marks[i][j] > highest) {
                highest = marks[i][j];
            }
        }
        cout << subjects[j] << ": " << highest << endl;
    }

    cout << "\nTop Student: Student " << topStudent << " with Total Marks: " << maxTotal << endl;

    return 0;
}