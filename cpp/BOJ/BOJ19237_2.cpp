//21"19'

#include <iostream>
using namespace std;

int board[20][20];
int tboard[20][20];
//상하좌우
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
struct SMELL {
	int num, dur;
};
struct SHARK {
	int y, x, d;
	int priority[4][4];
};
int shark_count = 0;
int N, M, K;
SHARK shark[401];
int res = 0;

SMELL smell[20][20];

void reduce_smell() {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (smell[y][x].dur > 0) {
				smell[y][x].dur--;
			}
		}
	}
}

void put_smell() {
	for (int i = 1; i <= M; i++) {
		if (shark[i].y != -1) {
			smell[shark[i].y][shark[i].x] = { i,K };
		}
	}
}

void solve() {

	int time = 0;

	while (time <= 1000) {
		

		if (shark_count == 1) {
			res = time;
			return;
		}
		time++;


	//냄새 감소.
	reduce_smell();

	//냄새 뿌리기.
	put_smell();

	//이동
	
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			tboard[y][x] = 0;
		}
	}

	for (int i = 1; i <= M; i++) {
		int cy = shark[i].y;
		int cx = shark[i].x;
		int cd = shark[i].d;
		int ny, nx, nd;

		bool flag = false;
		if (cy == -1) {
			continue;
		}
		for (int d = 0; d < 4; d++) {
			ny = cy + dy[shark[i].priority[cd][d]];
			nx = cx + dx[shark[i].priority[cd][d]];
			nd = shark[i].priority[cd][d];
			if (ny < 0 || nx < 0 || ny >= N || nx >= N) {
				continue;
			}

			if (smell[ny][nx].dur == 0) {
				shark[i].y = ny;
				shark[i].x = nx;
				shark[i].d = nd;
				flag = true;
				break;
			}

		}

		if (flag == false) {
			for (int d = 0; d < 4; d++) {
				ny = cy + dy[shark[i].priority[cd][d]];
				nx = cx + dx[shark[i].priority[cd][d]];
				nd = shark[i].priority[cd][d];
				if (ny < 0 || nx < 0 || ny >= N || nx >= N) {
					continue;
				}

				if (smell[ny][nx].num == i) {
					shark[i].y = ny;
					shark[i].x = nx;
					shark[i].d = nd;
					break;
				}
			}
		}

		if (i==1) {
			tboard[ny][nx] = 1;
		}
		else{
			if (tboard[ny][nx] != 0) {
				shark_count--;
				shark[i].y = -1;
			}
			else {
				tboard[ny][nx] = i;
				tboard[cy][cx] = 0;
			}
		}
		
	}

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			board[y][x] = tboard[y][x];
		}
	}

	}
	res = time;
	return;
}

int main() {
	cin >> N >> M >> K;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> board[y][x];
			if (board[y][x] != 0) {
				shark[board[y][x]].y = y;
				shark[board[y][x]].x = x;
			}
		}
	}

	for (int i = 1; i <= M; i++) {
		cin >> shark[i].d;
		shark[i].d--;
	}

	for (int i = 1; i <= M; i++) {
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				cin >> shark[i].priority[y][x];
				shark[i].priority[y][x]--;
			}
		}
	}

	shark_count = M;
	
	solve();
	if (res == 1001) {
		res = -1;
	}
	cout << res;
}