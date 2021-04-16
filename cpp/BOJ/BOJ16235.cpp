#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

int N, M, K;
deque<int> board[10][10];
int fir[10][10];
int A[10][10];
int dead[10][10];
//우측부터 시계방향
int dy[8] = { 0,1,1,1,0,-1,-1,-1 };
int dx[8] = { 1,1,0,-1,-1,-1,0,1 };


void spring() {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			int deadindex = -1;
			if (board[y][x].size()) {
				for (int i = 0; i < board[y][x].size(); i++) {
					if (board[y][x][i] <= fir[y][x]) {
						fir[y][x] -= board[y][x][i];
						board[y][x][i]++;
					}

					else {
						deadindex = i;
						break;
					}

				}
				if (deadindex != -1) {
					int ss = board[y][x].size();
					for (int i = ss - 1; i >= deadindex; i--) {
						dead[y][x] += board[y][x][i]/2;
						board[y][x].pop_back();
					}
				}
			}
		}
	}
}

void summer(){
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			fir[y][x] += dead[y][x];
			dead[y][x] = 0;
		}
	}
}
void fall() {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
	
			for (int i = 0; i < board[y][x].size(); i++) {
				if (board[y][x][i] % 5 == 0) {
					for (int d = 0; d < 8; d++) {
						int ny = y + dy[d];
						int nx = x + dx[d];

						if (ny < 0 || nx < 0 || ny >= N || nx >= N) {
							continue;
						}

						board[ny][nx].push_front(1);

					}
				}
			}
		
		}
	}
}
void winter() {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			fir[y][x] += A[y][x];
		}
	}
}

int main() {
	cin >> N >> M >> K;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> A[y][x];
			fir[y][x] = 5;
		}
	}

	int ty, tx, tage;
	for(int i = 0; i<M; i++){
		cin >> ty >> tx >> tage;
		ty--, tx--;
		board[ty][tx].push_front(tage);
	}

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			sort(board[y][x].begin(), board[y][x].end());
		}
	}

	while (K) {
		K--;
		spring();
		summer();
		fall();
		winter();
	}

	int res = 0;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			res += board[y][x].size();
		}
	}
	cout << res;
}
