#include <iostream>
#include <vector>
#include<queue>
using namespace std;

int N, M;

int tomatos[1000][1000];
bool check[1000][1000] = { false, };
int res = 0;

struct tomato {
	int y, x, date;
};

queue<tomato> mature;

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,-1,0,1 };

int bfs() {

	while (!mature.empty()) {
	
		int y = mature.front().y;
		int x = mature.front().x;
		int date = mature.front().date;
		mature.pop();
		if (date > res)
			res = date;

		for (int i = 0; i < 4; i++) {

			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= M || tomatos[ny][nx] == -1 || check[ny][nx] == true)
				continue;

			if(tomatos[ny][nx] == 0){
				mature.push({ ny,nx,date + 1 });
				check[ny][nx] = true;
				tomatos[ny][nx] = 1;
			}
		}

	
	}

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++)
		{
			if (check[y][x] == false && tomatos[y][x] != -1)
				return -1;
		}
	}

	return res;
}

int main() {
	cin >> M >> N;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++)
		{
			cin >> tomatos[y][x];
			if(tomatos[y][x] == 1){
				check[y][x] = true;
				mature.push({ y,x,0 });
			}
		}
	}


	cout << bfs();

	return 0;
}