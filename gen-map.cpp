#include <iostream>

using namespace std;

const int HEIGHT = 16;
const int WIDTH = 6;
const int MIN_LENGTH = 23;
const int MAX_LENGTH = 25;
const int LIMIT = 5000;
const int MAX_ANS = 10156140; // calculated

#define nextLast(last, dir) (((last << 2) & 15) | dir)
#define get(last, ind) ((last >> (ind << 1)) & 3)

const int UP = 0;
const int LEFT = 1;
const int RIGHT = 2;

int ans, curLen = 0;
string s = string(HEIGHT * WIDTH * 2, ' ');

string flip(string s) {
    for (int i = 0; i < HEIGHT; ++i) {
        int a = 2 * i * WIDTH;
        int b = 2 * ((i + 1) * WIDTH - 1);
        while (a < b) {
            swap(s[a], s[b]);
            a += 2;
            b -= 2;
        }
    }
    return s;
}

void printAns() {
    if (ans < LIMIT) {
        cout << s;
        ++ans;
    }
    if (ans < LIMIT) {
        cout << flip(s);
        ++ans;
    }
}

void gen(int row, int col, int last) {
    if (ans == LIMIT) {
        return;
    }

    // calculate bounds
    int minAddition = HEIGHT - row;
    int maxAddition = (HEIGHT - row) + (HEIGHT - row - 1) / 2 * (WIDTH - 1);
    if (get(last, 0) == UP) {
        maxAddition += max(row - 1, WIDTH - row - 1);
    } else if (get(last, 0) == LEFT) {
        maxAddition += row - 1;
    } else {
        maxAddition += WIDTH - row - 1;
    }
    if (curLen + maxAddition < MIN_LENGTH || curLen + minAddition > MAX_LENGTH) {
        // cut this branch
        return;
    }

    s[(row * WIDTH + col) * 2]++;
    ++curLen;
    if (row == HEIGHT - 1) {
        if (MIN_LENGTH <= curLen && curLen <= MAX_LENGTH) {
            printAns();
        }
        s[(row * WIDTH + col) * 2]--;
        --curLen;
        return;
    }
    // move up
    gen(row + 1, col, nextLast(last, UP));
    // move right
    if (col + 1 < WIDTH && get(last, 0) != LEFT && get(last, 1) != LEFT) {
        gen(row, col + 1, nextLast(last, RIGHT));
    }
    // move left
    if (col - 1 >= 0 && get(last, 0) != RIGHT && get(last, 1) != RIGHT) {
        gen(row, col - 1, nextLast(last, LEFT));
    }
    s[(row * WIDTH + col) * 2]--;
    --curLen;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    s.back() = '\n';
    for (int i = 0; i < HEIGHT * WIDTH; ++i) {
        s[2 * i] = '0';
    }

    cout << min(LIMIT, MAX_ANS) << '\n';
    for (int i = 0; i < 3; ++i) {
        s[2 * i]++;
        curLen = 1;
        gen(1, i, nextLast(UP, UP));
        s[2 * i]--;
        curLen = 0;
    }
}

/*
1 0 0 0 0 0
1 0 0 0 0 0
1 0 0 0 0 0
1 0 0 0 0 0
1 0 0 0 0 0
1 0 0 0 0 0
1 0 0 0 0 0
1 0 0 0 0 0
1 0 0 0 0 0
1 0 0 0 0 0
1 0 0 0 0 0
1 0 0 0 0 0
1 1 1 1 1 0
0 0 0 0 1 0
0 1 1 1 1 0
0 1 0 0 0 0
*/
