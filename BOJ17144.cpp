#include <iostream>
#include <deque>
using namespace std;

//20:00

int R, C, T;
int map[50][50];
int pluses[50][50];
int topstart, bottomstart;
//상좌하우
int dx[4] = { 0,-1,0,1 };
int dy[4] = { -1,0,1,0 };


void spreaddust() {



	int newy, newx;

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			pluses[i][j] = 0;
		}
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {

			if (map[i][j] < 0) {
				map[i][j] = -1;
			}

			int c = 0;
			for (int k = 0; k < 4; k++) {

				newy = i + dy[k];
				newx = j + dx[k];

				if (newy<0 || newy> R - 1 || newx<0 || newx> C - 1) {
					continue;
				}
				if (map[newy][newx] == -1) {
					continue;
				}
				int temp = map[i][j] / 5;
				c++;
				pluses[newy][newx] += temp;
			}
			map[i][j] -= map[i][j] / 5 * c;
		}
	}
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			map[i][j] += pluses[i][j];
		}
	}

}

void windblow() {
	
	//UP
	int temp=0;
	int ktemp = 0;
	temp = map[topstart][1];
	for (int i = 1; i < C - 1; i++) {

		ktemp = map[topstart][i+1];
		map[topstart][i + 1] = temp;
		temp = ktemp;
	}
	map[topstart][1] = 0;

	for (int i = topstart; i > 0; i--) {
		ktemp = map[i - 1][C - 1];
		map[i - 1][C - 1] = temp;
		temp = ktemp;
	}

	for (int i = C - 1; i > 0; i--) {
		ktemp = map[0][i - 1];
		map[0][i - 1] = temp;
		temp = ktemp;
	}

	for (int i = 0; i < topstart; i++) {
		ktemp = map[i + 1][0];
		map[i + 1][0] = temp;
		temp = ktemp;
	}
	map[topstart][0] = -1;

	//Down


	temp = 0;
	ktemp = 0;

	temp = map[bottomstart][1];

	for (int i = 1; i < C - 1; i++) {
		ktemp = map[bottomstart][i + 1];
		map[bottomstart][i + 1] = temp;
		temp = ktemp;
	}
	map[bottomstart][1] = 0;

	for (int i = bottomstart; i < R - 1; i++) {
		ktemp = map[i + 1][C - 1];
		map[i + 1][C - 1] = temp;
		temp = ktemp;
	}
	for (int i = C - 1; i > 0; i--) {
		ktemp = map[R - 1][i - 1];
		map[R - 1][i - 1] = temp;
		temp = ktemp;
	}

	for (int i = R - 1; i > bottomstart; i--) {
		ktemp = map[i - 1][0];
		map[i - 1][0] = temp;
		temp = ktemp;
	}
	map[bottomstart][0] = -1;
}

int main() {

	cin >> R >> C >> T;

	bool rrr = false;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> map[i][j];
			if (map[i][j] == -1)
				if (!rrr) {
					topstart = i;
					rrr = true;
				}
				else
					bottomstart = i;
		}
	}
	
	while (T > 0) {
		spreaddust();
		windblow();
		T--;
	}

	int res = 0;

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			res += map[i][j];
		}
	}
	
	cout << res+2;

}