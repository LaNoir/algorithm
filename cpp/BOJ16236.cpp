#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

int board[20][20];
int N;

struct shark {
	int y, x, size, count;
};

struct POS {
	int y, x, time;
};

shark baby;
POS fish;
int res = 0;

int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };

bool find() {
	bool check[20][20] = { false, };
	queue<POS> q;
	q.push({ baby.y,baby.x,0 });
	check[baby.y][baby.x] = true;

	fish.time = 400;

	while (!q.empty()) {
		POS cur = q.front();
		q.pop();
		
		if (cur.time > fish.time) {
			break;
		}

		if (board[cur.y][cur.x] != 0 && board[cur.y][cur.x] < baby.size) {

			if (cur.time < fish.time) {
				fish.x = cur.x;
				fish.y = cur.y;
				fish.time = cur.time;
			}

			else{
				if (cur.y < fish.y) {
					fish.x = cur.x;
					fish.y = cur.y;
				}
				else if (cur.y == fish.y) {
					if (cur.x < fish.x) {
						fish.x = cur.x;
					}
				}
			}	
		}

		POS next;
		next.time = cur.time + 1;
		for (int d = 0; d < 4; d++) {
			next.x = cur.x + dx[d];
			next.y = cur.y + dy[d];

			if (next.x < 0 || next.y < 0 || next.x >= N || next.y >= N) {
				continue;
			}
			if (check[next.y][next.x] == 1 || board[next.y][next.x] > baby.size) {
				continue;
			}

			q.push(next);
			check[next.y][next.x] = true;
		}

	}

	if (fish.time == 400)
		return false;
	else
		return true;
}

void eat() {
	res += fish.time;
	board[baby.y][baby.x] = 0;
	board[fish.y][fish.x] = 0;

	baby.y = fish.y;
	baby.x = fish.x;
	baby.count--;

	if (baby.count == 0) {
		baby.size++;
		baby.count = baby.size;
	}

}

int main() {

	cin >> N;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> board[y][x];
			if (board[y][x] == 9) {
				baby.x = x;
				baby.y = y;
				baby.size = 2;
				baby.count = 2;
				board[y][x] = 0;
			}
		}
	}

	while (1) {
		if (find()) {
			eat();
		}
		else {
			cout << res;
			break;
		}

	}

	return 0;
}