#include <iostream>
#include <array>
#include <set>

using namespace std;

const int HEIGHT = 16;
const int WIDTH = 6;
const int MIN_LENGTH = 23;
const int MAX_LENGTH = 25;

typedef array<array<int, WIDTH>, HEIGHT> gameMap;
bool valid;

gameMap inputMap() {
    gameMap m;
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            cin >> m[i][j];
            if (!(0 <= m[i][j] && m[i][j] <= 1)) {
                cerr << "Invalid cell code." << endl;
            }
        }
    }
    return m;
}

void printMap(const gameMap& m) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            cout << m[i][j] << ' ';
        }
        cout << endl;
    }
}

bool checkStartNEndRow(const array<int, WIDTH>& row) {
    int cnt = 0;
    for (int i = 0; i < WIDTH; ++i) {
        cnt += row[i];
    }
    return (cnt == 1);
}

bool checkSquare(const gameMap& m) {
    for (int i = 0; i < HEIGHT - 1; ++i) {
        for (int j = 0; j < WIDTH - 1; ++j) {
            if (m[i][j] + m[i + 1][j] + m[i][j + 1] + m[i + 1][j + 1] == 4) {
                return false;
            }
        }
    }
    return true;
}

bool validateMap(const gameMap& m) {
    bool valid = checkStartNEndRow(m[0]) && checkStartNEndRow(m[HEIGHT - 1]) && checkSquare(m);
    if (!valid) {
        return false;
    }

    // check exist path
    gameMap tmp = m;
    int x, y, len = 0;
    for (int j = 0; j < 6; ++j) {
        if (tmp[0][j] == 1) {
            len = 1;
            x = 0;
            y = j;
        }
    }
    tmp[x][y] = 0;

    while (x != HEIGHT - 1) {
        if (tmp[x + 1][y] == 1) { // up
            ++x;
        } else if (y > 0 && tmp[x][y - 1] == 1) { // left
            --y;
        } else if (y + 1 < WIDTH && tmp[x][y + 1] == 1) { // right
            ++y;
        } else { // can move
            cout << "Invalid map." << endl;
            return false;
        }
        ++len;
        tmp[x][y] = 0;
    }

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (tmp[i][j] != 0) { // have branch
                cout << "Path has branch." << endl;
                return false;
            }
        }
    }

    return (MIN_LENGTH <= len && len <= MAX_LENGTH); // check length
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int numMap;
    cin >> numMap;
    set<gameMap> maps;
    for (int i = 1; i <= numMap; ++i) {
        gameMap m = inputMap();
        if (!validateMap(m)) {
            continue;
        }
        if (maps.count(m)) {
            cout << "Duplicated map on line " << i << "." << endl;
            printMap(m);
        }
        maps.insert(m);
    }

    cout << "Number of valid map: " << maps.size() << "/" << numMap << endl;
}

