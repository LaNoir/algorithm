#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M, F;
int map[20][20];

struct customer {
	int sy, sx;
	int ey, ex;
	int distance;
};

int taxi_y, taxi_x;

vector<customer> people;
int picked[1000];
int c_distance[400];

struct POS {
	int y, x, time;
};

int dy[4] = { 0,0,-1,1 };
int dx[4] = { -1,1,0,0 };

int getDistance(customer P) {

	bool visit[20][20] = {false,};

	queue<POS> q;

	q.push({ taxi_y, taxi_x, 0 });
	visit[taxi_y][taxi_x] = true;

	int endy = P.sy;
	int endx = P.sx;

	while (!q.empty()) {
		POS cur = q.front();
		q.pop();
		if (cur.y == endy && cur.x == endx) {
			return cur.time;
		}
		POS next;
		next.time = cur.time + 1;
		for (int d = 0; d < 4; d++) {
			next.y = cur.y + dy[d];
			next.x = cur.x + dx[d];

			if (next.x < 0 || next.y < 0 || next.x >= N || next.y >= N) {
				continue;
			}
			if (visit[next.y][next.x]==true || map[next.y][next.x] == 1) {
				continue;
			}

			visit[next.y][next.x] = true;
			q.push(next);
		}

	}
	// 갈 수 없다면 401 리턴
	return 400;
}

int arrive(int sy, int sx, int ey, int ex) {


	bool visit[20][20] = { false, };

	queue<POS> q;

	q.push({ sy, sx, 0 });
	visit[sy][sx] = true;

	int endy = ey;
	int endx = ex;

	while (!q.empty()) {
		POS cur = q.front();
		q.pop();
		if (cur.y == endy && cur.x == endx) {
			return cur.time;
		}
		POS next;
		next.time = cur.time + 1;
		for (int d = 0; d < 4; d++) {
			next.y = cur.y + dy[d];
			next.x = cur.x + dx[d];

			if (next.x < 0 || next.y < 0 || next.x >= N || next.y >= N) {
				continue;
			}
			if (visit[next.y][next.x] || map[next.y][next.x] == 1) {
				continue;
			}
			visit[next.y][next.x] = true;
			q.push(next);
		}

	}

	//갈 수 없다면 400
	return 400;
}

int main() {
	cin >> N >> M >> F;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
		}
	}

	cin >> taxi_y >> taxi_x;

	taxi_y--, taxi_x--;


	for (int i = 0; i < M; i++) {
		customer c;
		int sy, sx, ey, ex;
		cin >> sy >> sx >> ey >> ex;
		sy--, sx--, ey--, ex--;
		c.sy = sy;
		c.sx = sx;
		c.ey = ey;
		c.ex = ex;
		c.distance = arrive(sy, sx, ey, ex);
		if (c.distance == 400) {
			cout << -1;
			return 0;
		}
		people.push_back(c);
	}

	//입력 완료.

	for (int r = 0; r < M; r++) {
		for (int i = 0; i < M; i++) {
			if (picked[i] == 0)
				c_distance[i] = getDistance(people[i]);
		}

		int min_distance = 400;
		int min_index = 0;
		int min_y = 40;
		int min_x = 40;
		for (int i = 0; i < M; i++) {
			if (picked[i] == 1)
				continue;
			if (c_distance[i] < min_distance) {
				min_index = i;
				min_distance = c_distance[i];
				min_y = people[i].sy;
				min_x = people[i].sx;
			}
			else if (c_distance[i] == min_distance) {
				if (min_y > people[i].sy) {
					min_y = people[i].sy;
					min_x = people[i].sx;
					min_index = i;
				}
				else if (min_y == people[i].sy) {
					if (min_x > people[i].sx) {
						min_y = people[i].sy;
						min_x = people[i].sx;
						min_index = i;
					}

				}
			}
		}
		//여기까지 안보낸 사람중에, 거리와 행이 낮은 사람을 구했다.
		
		if (min_distance == 400) {
			cout << -1;
			return 0;
			//움직일수 있는게 없다? 리턴.
		}

		if (F < min_distance + people[min_index].distance) {
			cout << -1;
			return 0;
		}

		picked[min_index] = 1;
		taxi_x = people[min_index].ex;
		taxi_y = people[min_index].ey;

		F = F + people[min_index].distance;
		F -= min_distance;
		

	}
	

	cout << F;

}
