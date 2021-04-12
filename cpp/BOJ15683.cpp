#include <iostream>
using namespace std;


typedef struct Cam {
	int y, x, type;
};

Cam camera[8];
int map[8][8];

int N, M;
int camCount = 0;
int res;

int rotatecount[5] = { 4,2,4,4,1 };

void fill_map(int dir, int y, int x) {

	dir = (dir) % 4;
	int ny, nx;
	//상하좌우
	switch (dir)
	{
	case 0:
		
		for (int i = x + 1; i < M; i++) {
			if (map[y][i] == 6)
				break;
			map[y][i] = -1;
		}
		
		break;
	case 1:
		for (int i = y - 1; i >= 0; i--) {
			if (map[i][x] == 6)
				break;
			map[i][x] = -1;
		}
		break;
	case 2:
		for (int i = x - 1; i >= 0; i--) {
			if (map[y][i] == 6)
				break;
			map[y][i] = -1;
		}
		break;
	case 3:
		for (int i = y + 1; i < N; i++) {
			if (map[i][x] == 6) {
				break;
			}
			map[i][x] = -1;
		}
		break;

	}

}

void solve(int c) {

	//종료 조건
	if (c == camCount) {
		int num = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (map[i][j] == 0) {
					num++;
				}
			}
		}
		res = min(res, num);
		return;
	}

	


	int type = camera[c].type;

	for( int dir = 0; dir<rotatecount[type]; dir++){
		int temp[8][8];


		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				temp[i][j] = map[i][j];
			}
		}
	switch (type)
	{
	case 0:
		fill_map(dir, camera[c].y, camera[c].x);
		break;
	case 1:
		fill_map(dir, camera[c].y, camera[c].x);
		fill_map(dir+2, camera[c].y, camera[c].x);
		break;
	case 2:
		fill_map(dir, camera[c].y, camera[c].x);
		fill_map(dir + 1, camera[c].y, camera[c].x);
		break;
	case 3:
		fill_map(dir, camera[c].y, camera[c].x);
		fill_map(dir + 1, camera[c].y, camera[c].x);
		fill_map(dir + 2, camera[c].y, camera[c].x);
		break;
	case 4:
		fill_map(dir, camera[c].y, camera[c].x);
		fill_map(dir + 1, camera[c].y, camera[c].x);
		fill_map(dir + 2, camera[c].y, camera[c].x);
		fill_map(dir + 3, camera[c].y, camera[c].x);

		break;

	default:
		break;
	}

	
	
	solve(c + 1);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			map[i][j] = temp[i][j];
		}
	}

	}
}




int main() {

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] != 0 && map[i][j] != 6) {
				camera[camCount].y = i;
				camera[camCount].x = j;
				camera[camCount].type = map[i][j] - 1;
				camCount++;
			}
		}
	}


	res = 65;

	solve(0);

	cout << res;

}