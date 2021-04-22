#include <iostream>
#include <string.h>
#include <queue>
#include <math.h>
using namespace std;
//18"55' -> 19"30'
int board[500][500];
int N;
// 5,10,10,7,7,2,2,1,1 a 순서로 
int per[9] = { 5,10,10,7,7,2,2,1,1 };

//좌, 하 ,우, 상
int dy[4][10] = {
	//좌
	{0,1,-1,1,-1,2,-2,1,-1,0},
	//하
	{2,1,1,0,0,0,0,-1,-1,1},
	//우
	{0,1,-1,1,-1,2,-2,1,-1,0},
	//상
	{-2,-1,-1,0,0,0,0,1,1,-1}
};

int dx[4][10] = {
	//좌
	{-2,-1,-1,0,0,0,0,1,1,-1},
	//하
	{0,-1,1,-1,1,-2,2,-1,1,0},
	//우
	{2,1,1,0,0,0,0,-1,-1,1},
	//상
	{0,-1,1,-1,1,-2,2,-1,1,0}
};

int res = 0;

int d = 0;
int diry[4] = { 0,1,0,-1 };
int dirx[4] = { -1,0,1,0 };

void sandmove(int y, int x) {

	int origin = board[y][x];
	int ny, nx;
	for (int i = 0; i < 9; i++) {
		ny = y + dy[d][i];
		nx = x + dx[d][i];

		if (ny < 0 || nx < 0 || ny >= N || nx >= N) {
			res += board[y][x] * per[i] / 100;
			origin -= board[y][x] * per[i] / 100;
		}

		else {
			board[ny][nx] += board[y][x] * per[i] / 100;
			origin -= board[y][x] * per[i] / 100;
		}

	}



	ny = y + dy[d][9];
	nx = x + dx[d][9];

	if (ny < 0 || nx < 0 || ny >= N || nx >= N) {
		res += origin;
	}

	else {
		board[ny][nx] += origin;
	}

	board[y][x] = 0;

	
}


void solve(int sy, int sx) {

	int move_length = 1;
	int movecount = 2;

	while (1) {
		int l = move_length;

		for (int i = 0; i < l; i++) {
			if (sy == 0 && sx == 0) {
				return;
			}
			sy = sy + diry[d];
			sx = sx + dirx[d];

			sandmove(sy, sx);
		}

		d = (d + 1) % 4;
		movecount--;
		if (movecount == 0) {
			movecount = 2;
			move_length++;
		}

	}

}

int main() {
	cin >> N;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> board[y][x];
		}
	}

	solve(N/2,N/2);
	
	cout << res;
}