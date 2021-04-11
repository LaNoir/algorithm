#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int board[50][50];
int N, M;

int res = 987654321;

int dy[4] = { 0,0,1,-1 };
int dx[4] = { 1,-1,0,0 };

typedef struct POS {
	int y, x, time;
};

vector<POS> virus;

int bfs(int pick[]) {

	queue<POS> qq;
	bool check[50][50] = {false, };

	for (int i = 0; i < M; i++) {
		qq.push(virus[pick[i]]);
		check[virus[pick[i]].y][virus[pick[i]].x] = 1;
	}
	int empty_count = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == 0) {
				empty_count++;
			}
		}
	}

	while (!qq.empty()) {
		POS cur = qq.front();
		qq.pop();
		if (board[cur.y][cur.x] == 0) {
			empty_count--;
		}
		if (empty_count == 0) {
			return cur.time;
		}
		POS newPos;
		newPos.time = cur.time+1;

		for (int d = 0; d < 4; d++) {
			newPos.x = cur.x + dx[d];
			newPos.y = cur.y + dy[d];
			if (newPos.x < 0 || newPos.x >= N || newPos.y < 0 || newPos.y >= N) {
				continue;
			}

			if (check[newPos.y][newPos.x] == 0 && board[newPos.y][newPos.x] != 1) {
				qq.push(newPos);
				check[newPos.y][newPos.x] = 1;
				
			}


		}

	}

	return 987654321;
}

void dfs(int last, int count, int pick[]) {

	if (count == M) {
		res = min(res, bfs(pick));
		return;
	}

	for (int i = last + 1; i < virus.size(); i++) {
		pick[count] = i;
		dfs(i, count + 1, pick);
	}

}

int main() {
	cin >> N >> M;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> board[y][x];
			if (board[y][x] == 2) {
				virus.push_back({ y,x,0 });
			}
		}
	}

	int pick[10] = { 0, };

	dfs(-1, 0, pick);

	if (res == 987654321) {
		cout << -1;
	}
	else {
		cout << res;
	}

}