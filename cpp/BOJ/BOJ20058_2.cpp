#include <iostream>
#include <string.h>
#include <queue>
#include <math.h>
using namespace std;
//17"20, 18"03'
int board[64][64];
int tboard[64][64];
int N, Q, L;

bool visited[64][64];
int dy[4] = { 0,0,-1,1 };
int dx[4] = { 1,-1,0,0 };
void rotate(int level) {
	memset(tboard, 0, sizeof(tboard));

	int rr = pow(2, level);
	queue<int> v;
	for (int y = 0; y < N; y += rr) {
		for (int x = 0; x < N; x += rr) {


			for(int a = y; a<y+rr; a++){
				for (int k = x; k < x+rr; k++) {
					v.push(board[a][k]);
				}
			}
			for (int r = x + rr - 1; r >= x; r--) {
				for (int c = y ; c < y + rr; c++) {
					board[c][r] = v.front();
					v.pop();
				}
			}


		}
	}

}

void melt() {
	int ny, nx;
	memset(tboard, 0, sizeof(tboard));
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			int cc = 0;
			for (int d = 0; d < 4; d++) {
				ny = y + dy[d];
				nx = x + dx[d];
				if (ny < 0 || nx < 0 || ny >= N || nx >= N) {
					continue;
				}
				if (board[ny][nx] != 0) {
					cc++;
				}
			}
			if (cc < 3) {
				tboard[y][x] = 1;
			}
		}
	}

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (tboard[y][x] == 1 && board[y][x] > 0) {
				board[y][x]--;
			}
		}
	}

}

int bfs(int y, int x) {

	queue<pair<int, int>> q;

	q.push({ y,x });
	visited[y][x] = true;
	int ans = 0;
	while (!q.empty()) {
		int cury = q.front().first;
		int curx = q.front().second;
		ans++;
		q.pop();
		int ny, nx;
		for (int d = 0; d < 4; d++) {
			ny = cury + dy[d];
			nx = curx + dx[d];

			if (ny < 0 || nx < 0 || ny >= N || nx >= N) {
				continue;
			}
			if (visited[ny][nx]==true || board[ny][nx] == 0)
				continue;

			q.push({ ny,nx });
			visited[ny][nx] = true;
		}
	}

	return ans;
}

int main() {

	cin >> N >> Q;
	N = pow(2, N);

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> board[y][x];
		}
	}

	for (int i = 0; i < Q; i++) {
		cin >> L;
		rotate(L);
		
		melt();
	}


	int sum = 0;
	int b = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			sum += board[y][x];
			if(visited[y][x] == false && board[y][x] != 0){
				b = max(b, bfs(y, x));
			}
		}
	}
	
	cout << sum << "\n" << b;
	
}