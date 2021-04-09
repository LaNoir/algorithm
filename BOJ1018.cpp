#include <iostream>
#include <vector>
#include<queue>
using namespace std;

int N, M;

int res = 500;

char board[50][50];

const char whiteFirst[8][8] =
{
	{'W','B','W','B','W','B','W','B'},
	{'B','W','B','W','B','W','B','W'},
	{'W','B','W','B','W','B','W','B'},
	{'B','W','B','W','B','W','B','W'},
	{'W','B','W','B','W','B','W','B'},
	{'B','W','B','W','B','W','B','W'},
	{'W','B','W','B','W','B','W','B'},
	{'B','W','B','W','B','W','B','W'}
};

const char blackFirst[8][8] = {
	{'B','W','B','W','B','W','B','W'},
	{'W','B','W','B','W','B','W','B'},
	{'B','W','B','W','B','W','B','W'},
	{'W','B','W','B','W','B','W','B'},
	{'B','W','B','W','B','W','B','W'},
	{'W','B','W','B','W','B','W','B'},
	{'B','W','B','W','B','W','B','W'},
	{'W','B','W','B','W','B','W','B'}
};



void comparePlate(int y, int x) {

	char tempplate[8][8];

	for (int i = y; i < y + 8; i++) {
		for (int j = x; j < x + 8; j++) {
			tempplate[i-y][j-x] = board[i][j];
		}
	}
	

	int black=0, white=0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (tempplate[i][j] != blackFirst[i][j])
				black++;
			if (tempplate[i][j] != whiteFirst[i][j])
				white++;
		}
	}

	if (res > black) {
		res = black;
	}
	if (res > white) {
		res = white;
	}

}

int main() {
	cin >> N >>M;
	string a;
	for (int y = 0; y < N; y++) {
		cin >> a;
		for (int x = 0; x < M; x++)
		{
			board[y][x] = a[x];
		}
	}

	for (int y = 0; y < N - 7; y++) {

		for (int x = 0; x < M - 7; x++) {

			comparePlate(y, x);
		}
	}

	cout << res;

	return 0;
}