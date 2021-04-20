//17"13'
#include <iostream>
using namespace std;
//↑, ↖, ←, ↙, ↓, ↘, →, ↗

int dy[8] = { -1,-1,0,1,1,1,0,-1 };
int dx[8] = { 0,-1,-1,-1,0,1,1,1 };


struct FISH {
	int y, x, d;
};

int res = 0;

void solve(int board[4][4], FISH fish[16], int shark_y, int shark_x, int sum) {

	int tboard[4][4];
	FISH tfish[16];

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			tboard[y][x] = board[y][x];
		}
	}
	for (int y = 0; y < 16; y++) {
		tfish[y] = fish[y];
	}

	//eat
	sum = sum + tboard[shark_y][shark_x] + 1;
	res = max(sum, res);
	int shark_d = tfish[board[shark_y][shark_x]].d;
	tfish[board[shark_y][shark_x]] = { -1 ,-1, - 1 };
	tboard[shark_y][shark_x] = -1;

	//fish move
	
	for (int i = 0; i < 16; i++) {
		if (tfish[i].y == -1) {
			continue;
		}

		int cy = tfish[i].y;
		int cx = tfish[i].x;
		int cd = tfish[i].d;

		int ny, nx, nd;
		ny = cy + dy[cd];
		nx = cx + dx[cd];
		nd = cd;

		while (ny < 0 || nx < 0 || ny >= 4 || nx >= 4 || (ny == shark_y && nx == shark_x)) {
			nd = (nd + 1) % 8;
			ny = cy + dy[nd];
			nx = cx + dx[nd];
		}

		int target = tboard[ny][nx];
		tfish[i] = { ny,nx,nd };

		if (target != -1){
			tfish[target].y = cy;
			tfish[target].x = cx;
			tboard[cy][cx] = target;
			tboard[ny][nx] = i;

		}

		else{
			tboard[ny][nx] = i;
			tboard[cy][cx] = -1;

		}
	}

	//shark move

	int cy = shark_y;
	int cx = shark_x;
	int cd = shark_d;
	int ny, nx, nd;
	for (int i = 1; i <= 4; i++) {
		ny = cy + dy[cd]*i;
		nx = cx + dx[cd]*i;
		if (ny < 0 || nx < 0 || ny >= 4 || nx >= 4)
			break;

		if (tboard[ny][nx] != -1) {
			solve(tboard, tfish, ny, nx, sum);
		}

	}

}

int main() {
	int a, b;

	
	int board[4][4];
	FISH fish[16];

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			cin >> a >> b;
			a--, b--;
			board[y][x] = a;
			fish[a] = { y,x,b };
		}
	}

	
	solve(board, fish, 0, 0, 0);

	cout << res;

	return 0;
}