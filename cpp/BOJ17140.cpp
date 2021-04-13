#include <iostream>

using namespace std;

int r, c, k;
int res = 0;
int map[101][101];

int col_size = 3;
int row_size = 3;
int pre_col = 3;
int pre_row = 3;

void update_row(int y) {

	int bucket[101] = { 0, };

	for (int i = 1; i <= pre_col; i++) {
		bucket[map[y][i]] ++;
	}
	int size = 0;
	for (int i = 1; i <= 100; i++) {
		for (int j = 1; j <= 100; j++) {
			if (bucket[j] == i) {
				map[y][++size] = j;
				map[y][++size] = i;
			}
			if (size >= 100) {
				break;
			}
		}
		if (size >= 100) {
			break;
		}
	}

	for (int i = size + 1; i <= 100; i++) {
		map[y][i] = 0;
	}
	if (size > col_size)
		col_size = size;
}

void update_col(int x) {
	int bucket[101] = { 0, };

	for (int i = 1; i <= pre_row; i++) {
		bucket[map[i][x]] ++;
	}
	int size = 0;
	for (int i = 1; i <= 100; i++) {
		for (int j = 1; j <= 100; j++) {
			if (bucket[j] == i) {
				map[++size][x] = j;
				map[++size][x] = i;
			}
			if (size >= 100) {
				break;
			}
		}
		if (size >= 100) {
			break;
		}
	}

	for (int i = size + 1; i <= 100; i++) {
		map[i][x] = 0;
	}
	if (size > row_size)
		row_size = size;
}

void solve() {

	while (map[r][c] != k && res < 101) {
		if (row_size >= col_size) {
			pre_col = col_size;
			col_size = 0;
			for (int i = 1; i <= row_size; i++) {
				update_row(i);
			}
		}
		else{
			pre_row = row_size;
			row_size = 0;
			for (int i = 1; i <= col_size; i++) {
				update_col(i);
			}
		}
		res++;
	}

}


int main() {

	cin >> r >> c >> k;

	for (int i = 1; i < 4; i++) {
		for (int j = 1; j < 4; j++) {
			cin >> map[i][j];
		}
	}

	solve();

	if (res > 100) {
		res = -1;
	}

	cout << res;

}


