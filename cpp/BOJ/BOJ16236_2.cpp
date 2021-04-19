#include <iostream>
#include <queue>
using namespace std;
//09"16' -> 10"15
int N, M;

int board[20][20];
int check[20][20];
struct SHARK {
	int y, x, size, count;
};

struct POS {
	int y, x, time;
};

SHARK baby;
int res = 0;
POS target_fish;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };

bool find() {
	
	target_fish.time = 400;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			check[i][j] = false;
		}
	}
	queue<POS> q;

	q.push({ baby.y,baby.x,0 });
	check[baby.y][baby.x] = true;

	while (!q.empty()) {

		POS cur = q.front();
		q.pop();
		if (cur.time > target_fish.time) {
			break;
		}

		//갱신
		else if (baby.size > board[cur.y][cur.x] && board[cur.y][cur.x] != 0) {

			if (cur.time < target_fish.time) {
				target_fish.y = cur.y;
				target_fish.x = cur.x;
				target_fish.time = cur.time;
			}

			else {
				if (cur.y < target_fish.y) {
					target_fish.y = cur.y;
					target_fish.x = cur.x;
				}
				else if (cur.y == target_fish.y) {
					if (cur.x < target_fish.x) {
						target_fish.y = cur.y;
						target_fish.x = cur.x;
					}
				}
			}
		}
			int ny, nx;
			for (int d = 0; d < 4; d++) {
				ny = cur.y + dy[d];
				nx = cur.x + dx[d];

				if (ny < 0 || nx < 0 || ny >= N || nx >= N) {
					continue;
				}
				if (board[ny][nx] > baby.size || check[ny][nx] == true) {
					continue;
				}

				check[ny][nx] = true;
				q.push({ ny,nx,cur.time + 1 });
			}





	}
	if (target_fish.time == 400)
		return false;

	return true;

}

void eat() {

	baby.y = target_fish.y;
	baby.x = target_fish.x;
	baby.count--;
	if (baby.count == 0) {
		baby.size++;
		baby.count = baby.size;
	}

	board[target_fish.y][target_fish.x] = 0;
	res += target_fish.time;
}

int main() {

	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
			if (board[i][j] == 9) {
				baby.y = i;
				baby.x = j;
				baby.size = 2;
				baby.count = 2;
				board[i][j] = 0;
			}
		}
	}

	
	while (1) {
		if (find()) {
			eat();
		}
		else {
			break;
		}

	}
	cout << res;
}