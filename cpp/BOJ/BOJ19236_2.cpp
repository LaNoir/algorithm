#include <iostream>
#include <queue>
#include <string>
using namespace std;

int N, W, H;

//↑, ↖, ←, ↙, ↓, ↘, →, ↗ 

int dx[8] = { 0,-1,-1,-1,0,1,1,1 };
int dy[8] = { -1,-1,0,1,1,1,0,-1 };

struct FISH {
	int y, x, d;
};


int res = 0;

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
	int cur = tboard[sharky][sharkx];

	int sharkd = tfish[cur].d;
	tfish[cur] = { -1,-1,-1 };
	sum = sum + cur + 1;
	res = max(res, sum);

	tboard[sharky][sharkx] = -1;

	//fish move

	for (int i = 0; i < 16; i++) {
		if (tfish[i].y == -1)
			continue;

		FISH s_fish = tfish[i];
		int ny = s_fish.y + dy[s_fish.d];
		int nx = s_fish.x + dx[s_fish.d];
		int nd = s_fish.d;
		while (ny < 0 || nx < 0 || ny>3 || nx>3 || (ny == sharky && nx == sharkx)) {
				nd = (nd + 1) % 8;
				ny = (s_fish.y + dy[nd]);
				nx = (s_fish.x + dx[nd]);
		}

		if (tboard[ny][nx] != -1) {
			int t = tboard[ny][nx];
			tfish[t].y = s_fish.y;
			tfish[t].x = s_fish.x;
			tfish[i].y = ny;
			tfish[i].x = nx;
			tfish[i].d = nd;

			tboard[s_fish.y][s_fish.x] = t;
			tboard[ny][nx] = i;
		}
		
		else {
			tfish[i].y = ny;
			tfish[i].x = nx;
			tfish[i].d = nd;
			tboard[s_fish.y][s_fish.x] = -1;
			tboard[ny][nx] = i;
		}

	}

	//shark move.
	for(int i = 1; i< 4; i++)
	{
		int nx = sharkx + dx[sharkd] * i;
		int ny = sharky + dy[sharkd] * i;		
		if (nx < 0 || ny < 0 || nx>3 || ny>3) {
			break;
		}
		if(tboard[ny][nx] != -1)
			dfs(tboard, tfish, ny, nx, sum);
	}
}

int main() {
	int a, b;
	int board[4][4];
	FISH fish[16];
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			cin >> a >> b;
			a--,b--;
			board[y][x] = a;
			fish[a] = { y,x,b };
		}
	}
	
	dfs(board, fish, 0, 0, 0);

	cout << res;
}
