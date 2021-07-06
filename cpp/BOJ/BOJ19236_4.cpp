//19"42' => 20"12

#include <iostream>
#include <string.h>
using namespace std;

//↑, ↖, ←, ↙, ↓, ↘, →, ↗
int dy[8] = { -1,-1,0,1,1,1,0,-1 };
int dx[8] = { 0,-1,-1,-1,0,1,1,1 };

int res = 0;

struct FISH {
	int y, x, d;
};

void dfs(int board[4][4], FISH fish[16], int sharky, int sharkx, int sum) {

	int tboard[4][4];
	FISH tfish[16];

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			tboard[y][x] = board[y][x];
		}
	}

	for (int i = 0; i < 16; i++) {
		tfish[i] = fish[i];
	}
	//eat
	
	sum = sum + tboard[sharky][sharkx] + 1;
	res = max(sum, res);

	int sharkd = tfish[tboard[sharky][sharkx]].d;

	tfish[tboard[sharky][sharkx]] = { -1,-1,-1 };
	tboard[sharky][sharkx] = -1;

	//fishmove
	int ny, nx, nd;
	int cy, cx, cd;

	for (int i = 0; i < 16; i++) {
		if (tfish[i].y == -1) {
			continue;
		}
		
		cy = tfish[i].y;
		cx = tfish[i].x;
		cd = tfish[i].d;

		ny = tfish[i].y + dy[cd];
		nx = tfish[i].x + dx[cd];
		nd = tfish[i].d;

    for(int d = 0; d<8; d++){

        if(ny >=0 && nx>=0 && ny<4 && nx<4 && (ny != sharky || nx != sharkx)){
            break;
        }
        nd = (nd + 1) % 8;
		ny = cy + dy[nd];
		nx = cx + dx[nd];
    }
		

		if (tboard[ny][nx] == -1) {
			tboard[cy][cx] = -1;
			tboard[ny][nx] = i;
			tfish[i] = { ny,nx,nd };
		}

		else {
			int target = tboard[ny][nx];
			tfish[target].y = cy;
			tfish[target].x = cx;
			tfish[i] = { ny,nx,nd };
			tboard[cy][cx] = target;
			tboard[ny][nx] = i;
		}

	}

	//sharkmove

	for (int i = 1; i < 4; i++) {

		ny = sharky + dy[sharkd] * i;
		nx = sharkx + dx[sharkd] * i;
		if (ny < 0 || nx < 0 || ny >= 4 || nx >= 4) {
			break;
		}
		if (tboard[ny][nx] != -1) {
			dfs(tboard, tfish, ny, nx, sum);
		}
	}

	return;
}

int main() {
	int a, b;
	FISH fish[16];
	int board[4][4];
	memset(board, 0, sizeof(board));
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			cin >> a >> b;
			a--, b--;
			fish[a] = { y,x,b };
			board[y][x] = a;
		}
	}

	dfs(board, fish, 0, 0, 0);

	cout << res;
}