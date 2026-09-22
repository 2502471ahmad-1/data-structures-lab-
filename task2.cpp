#include <iostream>

using namespace std;

int main() {
    int parking[4][5] = {
        {1, 0, 1, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 1, 0, 0, 0},
        {0, 1, 1, 0, 1}
    };

    int occupied = 0, empty = 0;

    cout << "Parking Layout:\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            cout << parking[i][j] << " ";
            if (parking[i][j] == 1) {
                occupied++;
            } else {
                empty++;
            }
        }
        cout << endl;
    }

    cout << "\nOccupied Spaces: " << occupied << endl;
    cout << "Empty Spaces: " << empty << endl;
    cout << "Total Capacity: " << 4 * 5 << endl;
    cout << "Occupancy Rate: " << (occupied / 20.0) * 100 << "%\n" << endl;

    int r, c;
    cout << "Enter Row (0-3): ";
    cin >> r;
    cout << "Enter Column (0-4): ";
    cin >> c;

    if (r >= 0 && r < 4 && c >= 0 && c < 5) {
        if (parking[r][c] == 1) {
            cout << "Space [" << r << "][" << c << "] is OCCUPIED." << endl;
        } else {
            cout << "Space [" << r << "][" << c << "] is AVAILABLE." << endl;
        }
    } else {
        cout << "Invalid index!" << endl;
    }

    return 0;
}