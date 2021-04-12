#include <iostream>
#include <deque>
using namespace std;

//20:00

int R,C,M;

typedef struct {
	int size;
	int direction;
	int speed;
}shark;

shark map[101][101];
shark temp[101][101];
int res;


//상하우좌

int dx[4] = {0 ,0 ,1, -1};
int dy[4] = { -1,1,0,0 };

int changeDirection(int d) {

	switch (d) {
	case 0: return 1;
		break;
	case 1: return 0;
		break;
	case 2: return 3;
		break;
	case 3: return 2;
		break;
	}
}


void catchshark(int T) {

	for (int i = 0; i < R; i++) {
		if (map[i][T].size > 0) {
			res += map[i][T].size;
			map[i][T] = { 0 ,0 ,0};
			return;
		}
	}

}

void moveshark() {
	
	int x,y, nx, ny,d;

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			temp[i][j] = { 0,0,0 };
		}
	}


	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {

			if (map[i][j].size < 1) {
				continue;
			}
			x = j;
			y = i;
			nx = j;
			ny = i;
			for (int k = 0; k < map[i][j].speed; k++) {
				d = map[i][j].direction;
				nx = x + dx[d];
				ny = y + dy[d];

				if (nx >= C || ny >= R || ny < 0 || nx < 0) {
					d = changeDirection(d);
					map[i][j].direction = d;
					nx = x + dx[d];
					ny = y + dy[d];
				}

				x = nx;
				y = ny;
			}
			if (map[i][j].size > temp[ny][nx].size)
				temp[ny][nx] = map[i][j];
		}
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			map[i][j] = temp[i][j];
		}
	}

}

int main() {
	
	cin >> R >> C >> M;
	
	int y, x, s, d, z;
	shark zz;
	for (int i = 1; i <= M; i++) {
		cin >> y >> x >> s >> d >> z;
		zz.direction = d-1;
		zz.size = z;
		if (d == 1 || d == 2) {
			zz.speed = s%((R-1)*2);
		}
		else {
			zz.speed = s % ((C - 1) * 2);
		}
		
		map[y-1][x-1] = zz;
	}
	
	
	int T = -1;

	while (T < C-1) {
		T++;
		catchshark(T);
		moveshark();
	}
	
	
	cout << res;
	
}