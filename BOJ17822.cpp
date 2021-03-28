#include <iostream>
#include <string>
#include <math.h>
#include <deque>
using namespace std;

int N, M, T;

/*
(i, 1)은 (i, 2), (i, M)과 인접하다.
(i, M)은 (i, M-1), (i, 1)과 인접하다.
(i, j)는 (i, j-1), (i, j+1)과 인접하다. (2 ≤ j ≤ M-1)
(1, j)는 (2, j)와 인접하다.
(N, j)는 (N-1, j)와 인접하다.
(i, j)는 (i-1, j), (i+1, j)와 인접하다. (2 ≤ i ≤ N-1)
*/

deque<int> board[51];

int dx[4] = { 0,0, -1,1 };
int dy[4] = { -1,1, 0,0 };

void rotate(int p_num, int direction) {
	if (direction == 0) {
		board[p_num].push_front(board[p_num].back());
		board[p_num].pop_back();
	}
	else {
		board[p_num].push_back(board[p_num].front());
		board[p_num].pop_front();
	}
}

void solve(int p, int d, int k) {

	int f = p;

	//배수로 로테이션
	while (f <= N) {
		for(int i = 0; i<k; i++){
		rotate(f, d);
		}
		f += p;
	}

	bool is_update = false;
	bool check[51][50] = { false, };

	for (int y = 1; y <= N; y++) {
		for (int x = 0; x < M; x++) {
			for (int d = 0; d < 4; d++) {
				int ny = y + dy[d];
				int nx = (x + dx[d] + M) % M;
				if (ny<1 || ny>N) {
					continue;
				}
				if (board[y][x] != -1 && board[ny][nx] != -1 && board[y][x] == board[ny][nx]) {
					is_update = true;
					check[y][x] = true;
					check[ny][nx] = true;
				}
			}
		}
	}


	if (is_update) {
		for (int y = 1; y <= N; y++) {
			for (int x = 0; x < M; x++) {
				if (check[y][x] == true) {
					board[y][x] = -1;
				}
			}
		}
	}

	else {
		int sum = 0;
		int count = 0;
		for (int y = 1; y <= N; y++) {
			for (int x = 0; x < M; x++) {
				if (board[y][x] != -1) {
					sum += board[y][x];
					count++;
				}
			}
		}
		for (int y = 1; y <= N; y++) {
			for (int x = 0; x < M; x++) {
				if (board[y][x] != -1) {
					if (board[y][x] * count > sum) {
						board[y][x]--;
					}
					else if (board[y][x] * count < sum) {
						board[y][x] ++;
					}
				}
			}
		}
	}


}

int main() {
	cin >> N >> M >> T;

	for (int i = 1; i <= N; i++) {
		int t;
		for (int j = 0; j < M; j++) {
			cin >> t;
			board[i].push_back(t);
		}
	}

	int x, d, k;


	for (int i = 0; i < T; i++) {
		cin >> x >> d >> k;
		solve(x, d, k);
	}

	int res = 0;



	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j] != -1) {
				res += board[i][j];
			}
		}
	}

	cout << res;
}