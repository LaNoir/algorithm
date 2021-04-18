//20 20 -> 21 31
#include <iostream>

using namespace std;
//↑,  ↓,  ←,  →
int dx[8] = {0,0,-1,1 };
int dy[8] = {-1,1,0,0 };
int N, M, K;
struct SHARK {
	int y, x, dir;
	int priority[4][4];
};

struct SMELL {
	int n, time;
};

int res = 0;
int board[20][20];
SMELL smell[20][20];
SHARK shark[401];


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
	
	int d;
	for (int i = 1; i < M+1; i++) {
		cin >> d;
		shark[i].dir = d-1;
	}
	for (int k = 1; k < M + 1; k++) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cin >> d;
				shark[k].priority[i][j] = d-1;
			}
		}
	}
	//인풋 완료.

	int time = 0;
	int shark_count = M;
	while(time <= 1000){
		//한마리 남았으면 종료.
		if (shark_count == 1) {
			cout << time;
			return 0;
		}

		time++;

	//남은 냄새 줄이고, 현재 자리에 냄새 뿌리기

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				if (smell[y][x].time > 0) {
					smell[y][x].time--;
				}
			}
		}

		for (int i = 1; i < M+1; i++) {

			if (shark[i].y == -1) {
				continue;
			}
			else {
				smell[shark[i].y][shark[i].x] = { i,K };
			}
		}

	//이동과 내쫒기는 동시에 가능. 1부터 움직이면, 뒤에 온것은 내쫒아진다고 보면 됨.

		for (int i = 1; i < M + 1; i++) {
		
			SHARK cur = shark[i];

			int nd = cur.dir;
			int nx = cur.x;
			int ny = cur.y;

			if (ny == -1) {
				continue;
			}
			//냄새 없는 칸부터 탐색.
			bool nosmell = false;
			for (int d = 0; d < 4; d++) {
				nd = cur.priority[cur.dir][d];
				nx = cur.x + dx[nd];
				ny = cur.y + dy[nd];

				if (ny < 0 || nx < 0 || ny >= N || nx >= N) {
					continue;
				}

				if (smell[ny][nx].time == 0) {
					nosmell = true;
					break;
				}

			}

			if (nosmell == false) {
				for (int d = 0; d < 4; d++) {
					nd = cur.priority[cur.dir][d];
					nx = cur.x + dx[nd];
					ny = cur.y + dy[nd];

					if (ny < 0 || nx < 0 || ny >= N || nx >= N) {
						continue;
					}
					
					if (smell[ny][nx].n == i) {
						break;
					}

				}
			}


			if (i == 1) {
				int target = board[ny][nx];
				if (target != 0) {
					shark[target].y = -1;
					board[ny][nx] = 1;
					board[cur.y][cur.x] = 0;
					shark[1].y = ny;
					shark[1].x = nx;
					shark[1].dir = nd;
					shark_count--;
				}
				else {
					board[ny][nx] = 1;
					board[cur.y][cur.x] = 0;
					shark[1].y = ny;
					shark[1].x = nx;
					shark[1].dir = nd;
				}
			}

			else {
				int target = board[ny][nx];
				if (target != 0) {
					shark[i].y = -1;
					board[cur.y][cur.x] = 0;
					shark_count--;
				}
				else {
					board[ny][nx] = i;
					board[cur.y][cur.x] = 0;
					shark[i].y = ny;
					shark[i].x = nx;
					shark[i].dir = nd;
				}
			}
		
		}


	}

	cout << -1;
	return 0;
}