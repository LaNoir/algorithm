#include <iostream>
#include <queue>
#include <string>
using namespace std;

int N, M;
int board[1000][1000];
int res = -1;

typedef struct point {
	int y, x, time;
	bool br;
};

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,-1,0,1 };
bool check[1000][1000][2] = { 0, };

int bfs() {
	queue<point> q;

	
	q.push({ 0,0,0,0 });
	check[0][0][0] = 1;
	check[0][0][1] = 1;
	while (!q.empty()) {
		int curx = q.front().x;
		int cury = q.front().y;
		int curt = q.front().time;
		int curb = q.front().br;
		q.pop();
		int newy, newx;
		

		if (curx == M - 1 && cury == N - 1)
			return curt+1;

		for (int i = 0; i < 4; i++) {
			newy = cury + dy[i];
			newx = curx + dx[i];
			if (newy<0 || newx<0 || newy>=N || newx>=M )
				continue;

			if (check[newy][newx][1] == 0 && board[newy][newx] == 1 && curb == 0) {
				q.push({ newy,newx,curt + 1, 1 });
				check[newy][newx][1] = 1;
			}

			if (check[newy][newx][curb] == 0 && board[newy][newx] == 0) {
				q.push({ newy,newx, curt + 1, curb });
				check[newy][newx][curb] = 1;
			}
			
		}

	}

	return -1;
}

int main() {

	cin >> N >> M;
	string s;
	for (int y = 0; y < N; y++) {
		cin >> s;
		for (int x = 0; x < M; x++) {
			board[y][x] = s[x]-'0';
		}
	}


	res = max(res, bfs());
	

	cout << res;

}