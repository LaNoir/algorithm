// 19"40'

#include <iostream>
#include <queue>
using namespace std;

int before = 0;
int res = 0;
int board[100][100];
int N, M;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };
bool cheese_left() {
	
	int count = 0;
	
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < M; x++) {
			if (board[y][x] == 1)
				count++;
		}
	}

	if (count != 0) {
		before = count;
		return true;
	}
	return false;
}

void melt() {
	bool check[100][100] = { false, };
	for (int y = 0; y < N; y++){
		for (int x = 0; x < M; x++) {
			for(int d = 0; d<4; d++){
				int ny = y + dy[d];
				int nx = x + dx[d];

				if (ny < 0 || nx < 0 || ny >= N || nx >= M) {
					continue;
				}

				if (board[ny][nx] == -1) {
					check[y][x] = 1;
				}

			}
		}
	}
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (check[y][x]) {
				board[y][x] = -1;
			}
		}
	}


}
struct POS {
	int y, x;
};
void spread_air() {
	bool check[100][100] = { false, };

	queue <POS> q;

	q.push({ 0,0 });

	while (!q.empty()) {
		POS cur = q.front();
		q.pop();
		board[cur.y][cur.x] = -1;
		for (int d = 0; d < 4; d++) {
			int ny = cur.y + dy[d];
			int nx = cur.x + dx[d];

			if (ny < 0 || nx < 0 || ny >= N || nx >= M) {
				continue;
			}

			if (check[ny][nx] == 1 || board[ny][nx] == 1) {
				continue;
			}
			q.push({ ny, nx });
			check[ny][nx] = 1;
		}

	}


}

int main() {

	cin >> N >> M;

	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < M; x++) {
			cin >> board[y][x];
		}
	}

	board[0][0] = -1;

	while (1) {
		spread_air();
		if (!cheese_left()) {
			break;
		}
		melt();
		res++;
	}
	
	cout << res<<"\n";
	cout << before;
}