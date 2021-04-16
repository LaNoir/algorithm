#include <iostream>
using namespace std;

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

struct SHARK {
	int y, x, d;
	int priority[4][4];
};

int N, M, K, res;
int board[20][20][3];

SHARK shark[400];

void solve() {
	int time = 0;
	int kill_shark = 0;

	while (time <= 1000) {
		++time;

		int new_board[20][20][3] = { 0, };

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				new_board[y][x][0] = board[y][x][0];
				new_board[y][x][2] = board[y][x][2];
				if (new_board[y][x][2] > 0) {
					new_board[y][x][2]--;
				}
				if (new_board[y][x][2] > 0) {
					new_board[y][x][1] = board[y][x][1];
				}
			}
		}


		//여기까지가 템프에 복사

		for (int i = 0; i < M; i++) {
			int cy = shark[i].y;
			int cx = shark[i].x;
			int cd = shark[i].d;

			if (cy == -1) {
				continue;
			}
			bool is_move = false;
			for (int d = 0; d < 4; d++) {
				int nd = shark[i].priority[cd][d];
				int ny = cy + dy[nd];
				int nx = cx + dx[nd];

				if (ny < 0 || nx < 0 || ny >= N || nx >= N) {
					continue;
				}
				//냄새가 있으면 통과.
				if (board[ny][nx][2] != 0) {
					continue;
				}
				is_move = true;

				new_board[cy][cx][0] = 0;

				if (new_board[ny][nx][0] == 0) {
					//상어가 죽지 않는 경우
					new_board[ny][nx][0] = i + 1;
					new_board[ny][nx][1] = i + 1;
					new_board[ny][nx][2] = K;

					shark[i].y = ny;
					shark[i].x = nx;
					shark[i].d = nd;

				}
				else {
					//상어가 있으면, 나중에 온 상어가 죽는다.
					kill_shark++;
					shark[i].y = -1;
				}
				break;
			}

			if (is_move == false) {

				for (int d = 0; d < 4; d++) {
					int nd = shark[i].priority[cd][d];
					int ny = cy + dy[nd];
					int nx = cx + dx[nd];

					if (ny < 0 || nx < 0 || ny >= N || nx >= N) {
						continue;
					}
					//냄새가 자기것이 아니면 통과.
					if (board[ny][nx][2] != 0 && board[ny][nx][1] != i + 1) {
						continue;
					}
					is_move = true;
					new_board[cy][cx][0] = 0;

					if (new_board[ny][nx][0] == 0) {
						//상어가 죽지 않는 경우
						new_board[ny][nx][0] = i + 1;
						new_board[ny][nx][1] = i + 1;
						new_board[ny][nx][2] = K;

						shark[i].y = ny;
						shark[i].x = nx;
						shark[i].d = nd;

					}
					else {
						//상어가 있으면, 나중에 온 상어가 죽는다.
						kill_shark++;
						shark[i].y = -1;
					}
					break;
				}
			}
		}
		
		
		if (kill_shark == M - 1) {
			break;
		}
	
		//재복사
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				for (int a = 0; a < 3; a++) {
					board[y][x][a] = new_board[y][x][a];
				}
			}
		}
	}

	if (time <= 1000) {
		res = time;
	}
}

int main() {
	
	cin >> N >> M >> K;
	for (int y = 0; y < N; y++) {
		for( int x = 0; x < N; x++)
		{
			cin >> board[y][x][0];
			if (board[y][x][0] != 0) {
				int shark_number = board[y][x][0] -1;
				shark[shark_number].y = y;
				shark[shark_number].x = x;
				board[y][x][1] = board[y][x][0];
				board[y][x][2] = K;
			}
		} 
	}

	for (int i = 0; i < M; i++) {
		cin >> shark[i].d;
		shark[i].d--;
	}

	for (int i = 0; i < M; i++) {
		for(int j = 0; j<4; j++){
		cin >> shark[i].priority[j][0] >> shark[i].priority[j][1]>> shark[i].priority[j][2]>> shark[i].priority[j][3];
		shark[i].priority[j][0]--, shark[i].priority[j][1]--, shark[i].priority[j][2]--, --shark[i].priority[j][3];
		}
	}

	res = -1;
	solve();
	cout << res;

	return 0;
}