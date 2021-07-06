#include <iostream>
#include <queue>
#include <vector>
using namespace std;


int pick[9] = { 0, };
int prt[3];
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };

struct PLACE {
	int y, x, num;
};
struct POS {
	int y, x;
};
struct b {
	int y, x, time;
};
PLACE tile[9];
int board[20][20];
bool check[20][20];
POS start;
POS endpoint;
POS now;
int N;
int res = 987654321;

int bfs(int cy, int cx, int ny, int nx) {

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			check[y][x] = false;
		}
	}

	queue<b> q;

	q.push({ cy,cx,0 });
	check[cy][cx] = true;

	while (!q.empty()) {

		b cur = q.front();
		q.pop();
		if (cur.y == ny && cur.x == nx) {
			return cur.time;
		}

		for (int d = 0; d < 4; d++) {
			int nexty = cur.y + dy[d];
			int nextx = cur.x + dx[d];

			if (nexty < 0 || nextx < 0 || nexty >= N || nextx >= N) {
				continue;
			}

			if (board[nexty][nextx] == '#' || check[nexty][nextx] == true)
				continue;

			q.push({ nexty,nextx,cur.time + 1 });
			check[nexty][nextx] = true;

		}

	}


	return -1;
}

void play() {
	int ans = 0;
	POS now = start;
	int cy = start.y;
	int cx = start.x;
	int ny = tile[prt[0]].y;
	int nx = tile[prt[0]].x;
	int temp = bfs(cy,cx,ny,nx);
	if (temp == -1) {
		return;
	}
	ans += temp;

	cy = ny;
	cx = nx;
	ny = tile[prt[1]].y;
	nx = tile[prt[1]].x;

	temp = bfs(cy, cx, ny, nx);
	if (temp == -1) {
		return;
	}
	ans += temp;

	cy = ny;
	cx = nx;
	ny = tile[prt[2]].y;
	nx = tile[prt[2]].x;

	temp = bfs(cy, cx, ny, nx);
	if (temp == -1) {
		return;
	}
	ans += temp;

	cy = ny;
	cx = nx;
	ny = endpoint.y;
	nx = endpoint.x;

	temp = bfs(cy, cx, ny, nx);
	if (temp == -1) {
		return;
	}
	ans += temp;

	res = min(res, ans);
}

void dfs(int count) {

	if (count == 3) {
		int a = tile[prt[0]].num;
		int b = tile[prt[1]].num;
		int c = tile[prt[2]].num;

		if (a < b && b < c) {
			//이때만 돈다.
			play();
			//cout << a << " "<< b <<" " << c << endl;
		}

		return;
	}

	for (int i = 0; i < 9; i++) {
		if (pick[i] == 0 && tile[i].num > 0) {
			pick[i] = 1;
			prt[count] = i;
			dfs(count + 1);
			pick[i] = 0;
		}
	}

}

int main() {

	cin >> N;
	string s;
	for (int y = 0; y < N; y++) {
		cin >> s;
		for (int x = 0; x < N; x++) {
			board[y][x] = s[x];
			if (board[y][x] == 'S') {
				start.y = y;
				start.x = x;
			}
			else if (board[y][x] == 'E') {
				endpoint.y = y;
				endpoint.x = x;
			}
			if (board[y][x] >= '1' && board[y][x] <= '9') {
				tile[board[y][x] - 49] = { y,x,board[y][x] - 48 };
			}
		}
	}

	dfs(0);

	if (res == 987654321)
		res = -1;

	cout << res << "\n";
	return 0;
}