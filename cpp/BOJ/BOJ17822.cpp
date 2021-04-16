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

int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };


void move(int f, int direction) {

	if (direction == 0) {
		board[f].push_front(board[f].back());
		board[f].pop_back();
	}

	else {
		board[f].push_back(board[f].front());
		board[f].pop_front();
	}
}

void solve(int f, int d, int k) {

	int pick = f - 1 ;

	//무브 완료

	while (pick < N) {

		for (int i = 0; i < k; i++) {
			move(pick, d);
		}

		pick = pick + f;
	}

	// 값 찾기

	bool isUpdate = false;
	bool check[50][50] = { false, };
	int nx, ny, nd;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			for(int l = 0; l<4; l++){
				nx = (j + dx[l] +M)%M;
				ny = i + dy[l];
				if (ny < 0 || ny >= N) {
					continue;
				}

				if (board[ny][nx] != -1 && board[i][j] != -1 && board[i][j] == board[ny][nx]) {
					check[i][j] = true;
					check[ny][nx] = true;
					isUpdate = true;
				}

			}
		}
	}

	if(isUpdate){

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (check[i][j] == true) {
				board[i][j] = -1;
			}
		}
	}
	}

	else {
		int sum=0, count=0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (board[i][j] != -1) {
					sum += board[i][j];
					count++;
				}
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (board[i][j] != -1) {
					if (board[i][j] * count > sum) {
						board[i][j] --;
					}
					else if (board[i][j] * count < sum) {
						board[i][j] ++;
					}
				}
			}
		}
	}

}


int main() {

	cin >> N >> M >> T;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			int t;
			cin >> t;
			board[y].push_back(t);
		}
	}

	int a, b, c;
	while (T > 0) {
	
		cin >> a >> b >> c;

		solve(a,b,c);

		T--;
	}
	int res = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			
			if (board[y][x] != -1)
			{
				res += board[y][x];
			}
		}
	}

	cout << res;
}