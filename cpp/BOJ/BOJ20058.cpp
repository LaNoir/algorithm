#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

int board[64][64];
int temp[64][64];
bool check[64][64] = { false, };
bool ismelt[64][64];
int N, Q;
int dy[4] = { 0,0,1,-1 };
int dx[4] = { 1,-1,0,0 };

void rotate(int L) {
	
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			temp[y][x] = 0;
		}
	}

	int level = pow(2, L);
	queue<int> q;
	for (int y = 0; y < N; y += level ) {
		for (int x = 0; x < N; x += level) {
			for (int k = y; k < y + level; k++) {
				for (int r = x; r < x + level; r++) {
					q.push(board[k][r]);
				}
			}
			for (int k = x + level-1; k >= x; k--) {
				for (int r = y; r < y + level; r++) {
					temp[r][k] = q.front();
					q.pop();
				}
			}
		}
	}

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			board[y][x] = temp[y][x];
		}
	}
}

void melt() {

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			ismelt[y][x] = false;
		}
	}

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			int c = 0;
			for (int d = 0; d < 4; d++) {
				int ny = y + dy[d];
				int nx = x + dx[d];

				if (nx < 0 || ny < 0 || nx >= N || ny >= N) {
					continue;
				}

				if (board[ny][nx] > 0) {
					c++;
				}

			}
			if (c < 3 && board[y][x] > 0) {
				ismelt[y][x] = true;
			}
		}
	}
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (ismelt[y][x])
				board[y][x] -= 1;
		}
	}
}

int bfs(int y, int x) {

	queue<pair<int, int>> q;

	q.push({ y,x });
	check[y][x] = true;

	if (board[y][x] == 0) {
		return 0;
	}

	int sum = 0;

	while (!q.empty()) {

		int cury = q.front().first;
		int curx = q.front().second;

		q.pop();

		sum += 1;

		for (int d = 0; d < 4; d++) {
			int ny = cury + dy[d];
			int nx = curx + dx[d];

			if (nx < 0 || ny < 0 || nx >= N || ny >= N) {
				continue;
			}
		
			if (board[ny][nx] == 0 || check[ny][nx] == true)
				continue;

			q.push({ ny,nx });
			check[ny][nx] = true;
		}
	}

	return sum;
}

int main() {

	cin >> N >> Q;

	N = pow(2, N);

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> board[y][x];
		}
	}
	int L = 0;
	for (int T = 0; T < Q; T++) {
		cin >> L;

		rotate(L);
		melt();
	}
	int sum = 0;
	

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			sum += board[y][x];
		}
	}
	int res = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (check[y][x] == false) {
				res = max(res,bfs(y, x));
			}
		}
	}

	cout << sum << "\n" << res;
	
	return 0;
}