#include <iostream>
#include <queue>
#include <math.h>
using namespace std;

int N = 12;
int M = 6;

char board[12][6];

int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };

struct POS {
	int y, x;
};

bool bfs(int y , int x) {
	bool check[12][6] = { false, };
	int count = 1;
	queue<POS> q;
	q.push({ y,x });
	check[y][x] = true;
	char color = board[y][x];
	if (board[y][x] == '.') {
		return false;
	}
	while (!q.empty()) {

		int cy = q.front().y;
		int cx = q.front().x;
		q.pop();

		for (int d = 0; d < 4; d++) {
			int ny = cy + dy[d];
			int nx = cx + dx[d];

			if (ny < 0 || nx < 0 || ny >= N || nx >= M) {
				continue;
			}

			if (board[ny][nx] == color && check[ny][nx] == false) {
				q.push({ ny,nx });
				check[ny][nx] = true;
				count++;
			}
		}
	}

	if (count >= 4) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (check[i][j] == true) {
					board[i][j] = '.';
				}
			}
		}
		return true;
	}
	return false;
}

void drop() {
	
	for (int x = 0; x < M; x++) {
		vector<char> t;
		for (int y = N-1; y >=0 ; y--) {
			if (board[y][x] != '.')
				t.push_back(board[y][x]);
		}

		while (t.size() < N) {
			t.push_back('.');
		}
		int k = 0;
		for (int y = N - 1; y >= 0; y--) {
			board[y][x] = t[k++];
		}
	}

}

int main() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
		}
	}
	int res = 0;

	/*bfs(11, 0);
	drop();

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << board[i][j];
		}
		cout << endl;
	}
	*/
	while (1) {
		bool isboom = false;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < M; x++) {
				if (bfs(y,x)) {
					isboom = true;
				}
			}
		}
		drop();
		if (isboom) {
			res += 1;
		}
		else {
			break;
		}
	}
	
	cout << res;
}