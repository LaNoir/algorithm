#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;


const int dy[8] = { -1,-1,0,1,1,1,0,-1 };
const int dx[8] = { 0,1,1,1,0,-1,-1,-1 };

int N, M, K;

struct FIREBALL {
	int y, x, m, s, d;
};

vector<FIREBALL> ball;
vector<int> map[50][50];


void move(){

	vector<int> new_map[50][50];

	for (int i = 0; i < ball.size(); i++) {
		int d = ball[i].d;
		int speed = ball[i].s % N;
		int ny = (ball[i].y + (dy[d] * speed) + N) % N;
		int nx = (ball[i].x + (dx[d] * speed) + N) % N;
		new_map[ny][nx].push_back(i);
		ball[i].x = nx;
		ball[i].y = ny;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j] = new_map[i][j];
		}
	}
}

void sum(){

	vector<FIREBALL> new_ball;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j].size() == 0) {
				continue;
			}
			if (map[i][j].size() == 1) {
				new_ball.push_back(ball[map[i][j][0]]);
				continue;
			}

			//한 칸에 두개이상인 경우!
			int f_sum = 0, f_speed = 0;
			bool odd = true, even = true;
			for (int k = 0; k < map[i][j].size(); k++) {
				f_sum += ball[map[i][j][k]].m;
				f_speed += ball[map[i][j][k]].s;

				int d = ball[map[i][j][k]].d;
				if (d % 2 == 0) {
					even = false;
				}
				else {
					odd = false;
				}
			}
			if (f_sum / 5 == 0) {
				continue;
			}

			int cur_sum = f_sum / 5;
			int cur_speed = f_speed / map[i][j].size();
				for (int a = 0; a < 4; a++) {
					if (odd || even) {
						new_ball.push_back({ i,j, cur_sum, cur_speed, a * 2 });
					}
					else {
						new_ball.push_back({ i,j, cur_sum, cur_speed, a * 2 +1});
					}
				}
			

		}
	}
	ball = new_ball;
}

int solve() {

	while (K) {
		K--;
		move();
		sum();
	}
	int res = 0;
	for (int i = 0; i < ball.size(); i++) {
		res += ball[i].m;
	}
	return res;
}

int main() {
	cin >> N >> M >> K;
	int y, x, m, s, d;

	for (int i = 0; i < M; i++) {
		cin >> y >> x >> m >> s >> d;
		y--;
		x--;
		ball.push_back({ y,x,m,s,d });
		map[y][x].push_back(i);
	}

	int res = solve();
	cout << res;

}