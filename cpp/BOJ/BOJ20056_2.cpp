#include <iostream>
#include <vector>
#include <deque>
using namespace std;
//22 38

int N, M, K;
struct FIREBALL {
	int d, m;
	long long s;
};

vector<FIREBALL> board[50][50];

int dy[8] = { -1,-1,0,1,1,1,0,-1 };
int dx[8] = { 0,1,1,1,0,-1,-1,-1 };

void move() {
	vector<FIREBALL> tboard[50][50];

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			int rec = board[y][x].size();
			for (int i = 0; i < rec; i++) {
				FIREBALL cur = board[y][x][i];
				int ny, nx;
				ny = ((dy[cur.d] * (cur.s % N)) + y + N) % N;
				nx = ((dx[cur.d] * (cur.s % N)) + x + N) % N;
				tboard[ny][nx].push_back(cur);
			}
		}
	}

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			board[y][x] = tboard[y][x];
		}
	}

}

void split() {
	vector<FIREBALL> tboard[50][50];

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {

			bool odd = false;
			bool even = false;
			int sum = 0, speed = 0;
			int count = 0;

			int rec = board[y][x].size();
			if (rec < 2) {
				tboard[y][x] = board[y][x];
				continue;
			}
			for (int i = 0; i < rec; i++) {
				FIREBALL cur = board[y][x][i];
				if (cur.d % 2 == 0) {
					even = true;
				}
				else {
					odd = true;
				}

				sum += cur.m;
				speed += cur.s;
				count++;
			}
			sum /= 5;
			speed /= count;
			if (sum == 0) {
				continue;
			}
			FIREBALL temp;
			if (odd && even) {
				for (int a = 1; a < 8; a += 2) {
					temp.m = sum;
					temp.s = speed;
					temp.d = a;
					tboard[y][x].push_back(temp);
				}
			}
			else {
				for (int a = 0; a < 8; a += 2) {
					temp.m = sum;
					temp.s = speed;
					temp.d = a;
					tboard[y][x].push_back(temp);
				}
			}

		}
	}

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			board[y][x] = tboard[y][x];
		}
	}
}

int main() {
	cin >> N >> M >> K;
	int r, c, m, s, d;
	FIREBALL temp;
	for (int i = 0; i < M; i++) {
		cin >> r >> c >> m >> s >> d;
		temp.d = d;
		temp.s = s;
		temp.m = m;
		board[r - 1][c - 1].push_back(temp);
	}

	while (K) {
		K--;
		move();
		split();
	}

	int res = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			for (int i = 0; i < board[y][x].size(); i++) {
				res += board[y][x][i].m;
			}
		}
	}
	cout << res;
	return 0;
}