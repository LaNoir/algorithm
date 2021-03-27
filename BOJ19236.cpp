#include <iostream>
#include <string>
#include <math.h>
#include <deque>
using namespace std;

int dx[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };

typedef struct FISH {
	int x, y;
	int dir;
};


int res=0;


void solve(int board[4][4], FISH fish[16], int sharky, int sharkx, int sum) {
	int t_board[4][4];
	FISH t_fish[16];

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			t_board[i][j] = board[i][j];
		}
	}

	for (int i = 0; i < 16; i++) {
		t_fish[i] = fish[i];
	}

	//eat
	int cur_fish = t_board[sharky][sharkx];
	int sharkd = t_fish[cur_fish].dir;
	t_fish[cur_fish].y = -1;
	t_fish[cur_fish].x = -1;
	t_fish[cur_fish].dir = -1;
	sum = sum + cur_fish + 1;
	res = max(res, sum);

	t_board[sharky][sharkx] = -1;

	//fish move

	
	for (int i = 0; i < 16; i++) {
		if (t_fish[i].x == -1) {
			continue;
		}

		int cx = t_fish[i].x;
		int cy = t_fish[i].y;
		int cd = t_fish[i].dir;

		int ny = cy + dy[cd];
		int nx = cx + dx[cd];
		int nd = cd;

		while (ny < 0 || nx < 0 || ny>3 || nx>3 || (ny == sharky && nx == sharkx)) {
			nd = (nd + 1) % 8;
			ny = cy + dy[nd];
			nx = cx + dx[nd];
		}

		if (t_board[ny][nx] != -1) {
			int target = t_board[ny][nx];
			t_fish[target].y = cy;
			t_fish[target].x = cx;
			t_fish[i].y = ny;
			t_fish[i].x = nx;
			t_fish[i].dir = nd;

			t_board[cy][cx] = target;
			t_board[ny][nx] = i;
		}

		else {
			t_fish[i].y = ny;
			t_fish[i].x = nx;
			t_fish[i].dir = nd;
			t_board[cy][cx] = -1;
			t_board[ny][nx] = i;
		}

	}


	//shark move

	for (int i = 1; i < 4; i++) {
		

		int nx = sharkx + dx[sharkd] * i;
		int ny = sharky + dy[sharkd] * i;

		if (nx < 0 || ny < 0 || nx>3 || ny>3 ) {
			break;
		}
		if(t_board[ny][nx] != -1) {
			solve(t_board, t_fish, ny, nx, sum);
		}

	}

}

int main() {

	int board[4][4];
	FISH fish[16];

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			board[i][j] = a;
			fish[a].x = j;
			fish[a].y = i;
			fish[a].dir = b;
		}
	}

	solve(board, fish, 0, 0, 0);
	cout << res;
}