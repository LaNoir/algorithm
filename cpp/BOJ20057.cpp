#include <iostream>
#include <math.h>

// start at 07:27

using namespace std;
int N;
int map[500][500];

int d = 2;
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,-1,0,1 };

int tp[9] = { 5, 10, 10, 2, 2, 7, 7, 1, 1 };
//동북서남

int tsands[9];
//맨 마지막이 A를 나타낸다.
//앞방향 왼쪽 기준으로 정렬
int ddx[4][10] = {
	//   5, 10,10,2, 2, 7, 7  ,1  ,1 ,a
		{2, 1, 1, 0, 0, 0, 0, -1, -1 ,1},  //동쪽 
		{0, -1,1,-2, 2,-1, 1, -1, 1 , 0}, //북쪽
		{-2,-1,-1,0, 0, 0, 0, 1,  1, -1 }, //서
		{0, 1, -1, 2, -2, 1, -1, 1, -1, 0} //남
};

int ddy[4][10] = {
	//   5, 10,10,2, 2, 7, 7  ,1  ,1 ,a
		{0, -1, 1, -2, 2,-1,1,-1,1, 0}, //동
		{-2, -1, -1 ,0, 0, 0, 0, 1,1, -1}, //북
		{0 ,1, -1,2,-2,1,-1,1,-1,0}, //서
		{2, 1, 1, 0,0,0,0,-1,-1, 1} //남
};

//동북서남
int res ;

void tornado(int yy, int xx, int dd) {


	int sand = map[yy][xx];
	int tx, ty;

	if (sand == 0) {
		return;
	}

	for (int i = 0; i < 9; i++) {
		tsands[i] = (sand * tp[i]) / 100;
	}

	for (int i = 0; i < 9; i++) {
		tx = xx + ddx[dd][i];
		ty = yy + ddy[dd][i];

		if (tx<0 || tx>N - 1 || ty<0 || ty>N - 1) {
			res += tsands[i];
		}
		else {
			map[ty][tx] += tsands[i];
		}
		sand -= tsands[i];
	}

	tx = xx + ddx[d][9];
	ty = yy + ddy[d][9];

	if (tx<0 || tx>N - 1 || ty<0 || ty>N - 1) {
		res += sand;
	}

	else{
		map[ty][tx] += sand;
	}
}

int main() {

	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	int movecount = 0; //2가 되면 방향 전환 그리고 distance 1 증가.
	int distance = 1; //움직이는 거리

	int x = N/2;
	int y = N/2;
	int newx, newy;

	int changecounter = 0;

	while (1) {
		changecounter++;
			x = x + dx[d];
			y = y + dy[d];
			if (x<0 || x>N || y<0 || y>N) {
				cout << res;
				return 0;
			}

			tornado(y, x, d);

		if (changecounter == distance) {
			d = (d + 1) % 4;
			changecounter = 0;
			movecount++;
		}
		if (movecount == 2) {
			movecount = 0;
			distance++;
		}
	}

	return 0;
}