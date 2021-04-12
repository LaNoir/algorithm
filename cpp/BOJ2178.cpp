#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int N, M, T;

int h[100][100];
int check[100][100];
int res = 100000;

int dy[4] = { 0,0,-1,1 };
int dx[4] = { 1,-1,0,0 };

typedef struct cord {
	int y, x, time;
};
/*
void bfs() {

	if (y == N - 1 && x == M - 1) {
		res = min(res, count);
		return;
	}

	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (ny >= 0 && nx>=0 && ny<N && nx<M && check[ny][nx]==0) {
			check[ny][nx] = 1;
			dfs(ny, nx, count + 1);
			check[ny][nx] = 0;
		}
	}
	
}
*/
int main() {

	cin >> N >> M;
	string s;
	for (int i = 0; i < N; i++) {
		cin >> s;
		for (int j = 0; j < M; j++) {
			h[i][j] = s[j]-'0';
			if (s[j] == '0') {
				check[i][j] = 1;
			}
		}
	}

	check[0][0] = 1;

	queue<cord> c;

	c.push({ 0,0,1 });

	while (!c.empty()) {

		int x, y, nx, ny,tt;

		x = c.front().x;
		y = c.front().y;
		tt = c.front().time;

		if (x == M - 1 && y == N - 1) {
			cout << tt;
			break;
		}

		c.pop();
		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny >= 0 && nx >= 0 && ny < N && nx < M && check[ny][nx] == 0) {
				check[ny][nx] = 1;
				c.push({ ny,nx,tt + 1 });
			}
		}

	}

	return 0;
}