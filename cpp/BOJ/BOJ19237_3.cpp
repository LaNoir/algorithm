#include <iostream>
#include <string.h>
using namespace std;
//16"20' 17"20
struct SHARK {
	int y, x, dir;
	int priority[4][4];
};

struct SMELL {
	int num, dur;
};

int N, M, K;

int board[20][20];
SMELL smell[20][20];
SHARK shark[401];
// 1, 2, 3, 4는 각각 위, 아래, 왼쪽, 오른쪽
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
int shark_count;
int res = 0;
void input() {

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> board[y][x];
			if (board[y][x] != 0) {
				shark[board[y][x]].y = y;
				shark[board[y][x]].x = x;
			}
		}
	}
	int a;
	for (int i = 1; i <= M; i++) {
		cin >> a;
		a--;
		shark[i].dir = a;
	}
	for (int i = 1; i <= M; i++) {
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				cin >> shark[i].priority[y][x];
				--shark[i].priority[y][x];
			}
		}
	}
}

void putSmell(){
	int y, x;
	for (int i = 1; i <= M; i++) {
		if (shark[i].y == -1)
			continue;
		y = shark[i].y;
		x = shark[i].x;
		smell[y][x].dur = K;
		smell[y][x].num = i;
	}
}

void reduceSmell() {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (smell[y][x].dur > 0) {
				smell[y][x].dur--;
				if (smell[y][x].dur == 0) {
					smell[y][x].num = 0;
				}
			}
		}
	}
}

void moveShark() {

	for (int i = 1; i <= M; i++) {
	
		if (shark[i].y == -1) {
			continue;
		}

		int cy, cx, cd;
		cy = shark[i].y;
		cx = shark[i].x;
		cd = shark[i].dir;
		int ny, nx, nd;
		bool flag = false;
		//냄새 없는데가 있는지 확인.
		for (int d = 0; d < 4; d++) {
			nd = shark[i].priority[cd][d];
			ny = cy + dy[nd];
			nx = cx + dx[nd];
			if (ny < 0 || nx < 0 || ny >= N || nx >= N) {
				continue;
			}
			if (smell[ny][nx].num == 0) {
				flag = true;
				break;
			}
		}

		if (flag == false) {
			for (int d = 0; d < 4; d++) {
				nd = shark[i].priority[cd][d];
				ny = cy + dy[nd];
				nx = cx + dx[nd];
				if (ny < 0 || nx < 0 || ny >= N || nx >= N) {
					continue;
				}
				if (smell[ny][nx].num == i) {
					break;
				}
			}
		}

		shark[i].x = nx;
		shark[i].y = ny;
		shark[i].dir = nd;

		if (i == 1) {
			board[cy][cx] = 0;
			board[ny][nx] = 1;
		}

		else {
			if (board[ny][nx] == 0) {
				board[cy][cx] = 0;
				board[ny][nx] = i;
			}
			else {
				shark[i].x = -1;
				shark[i].y = -1;
				shark[i].dir = -1;
				board[cy][cx] = 0;
				shark_count--;
			}
		}

	}

}

int solve() {

	shark_count = M;
	int time = 0;
	while (time <= 1000) {
		if (shark_count == 1) {
			return time;
		}
		time++;

		putSmell();
		//냄새 뿌리기
		
		moveShark();
		//상어 이동

		reduceSmell();
		//냄새 감소

	}

	return time;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M >> K;
	input();
	res = solve();

	if (res > 1000) {
		res = -1;
	}

	cout << res;
}