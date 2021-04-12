#include <string>
#include <iostream>
using namespace std;

int N;
char board[50][50];
int res = 0;


void check() {
   

    char temp = 'M';
    int count = 1;
    for (int y = 0; y < N; y++) {
        char temp = 'M';

        for (int x = 0; x < N; x++) {
     
            if (temp == board[y][x]) {
                count++;
            }

            else {
                res = max(count, res);
                temp = board[y][x];
                count = 1;
            }
        
        }
        res = max(count, res);
        count = 1;

    }

    count = 1;
    for (int x = 0; x < N; x++) {
        temp = 'M';

        for (int y = 0; y < N; y++) {
            if (temp == board[y][x]) {
                count++;
            }

            else {
                res = max(count, res);
                temp = board[y][x];
                count = 1;
            }

        }
        res = max(count, res);
        count = 1;

    }
    

}

int main(int argc, char const* argv[]) {
    cin >> N;
    string s;
    for (int y = 0; y < N; y++)
    {
        cin >> s;
        for (int x = 0; x < N; x++) {
            board[y][x] = s[x];
        }
    }

    int down_x, down_y, right_x, right_y;

    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            down_y = y + 1;
            right_x = x + 1;
            
            if (down_y < N) {
                int temp = board[down_y][x];
                board[down_y][x] = board[y][x];
                board[y][x] = temp;

                check();

                board[y][x] = board[down_y][x];
                board[down_y][x] = temp;
            }

            if (right_x < N) {
                int temp = board[y][right_x];
                board[y][right_x] = board[y][x];
                board[y][x] = temp;

                check();

                board[y][x] = board[y][right_x];
                board[y][right_x] = temp;
            }
        
        }
    }

    cout << res;

    return 0;
}