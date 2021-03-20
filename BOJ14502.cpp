#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int m, n;
int temp[8][8];

int check[8][8] = { 0 };
int res=0;


//동서남북
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

void bfs() {
	int i, j, newx, newy, x, y;
	int spread[8][8];


	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			spread[i][j] = temp[i][j];
		}
	}
	queue<pair<int,int>> qq;

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			if (spread[i][j] == 2) {
				qq.push(make_pair(i, j));
			}
		}
	}

	while (!qq.empty()) {

		y = qq.front().first;
		x = qq.front().second;
		qq.pop();
	

		for (i = 0; i < 4; i++) {
			newx = x + dx[i];
			newy = y + dy[i];

			if (0<=newy && newy < n && 0 <= newx && newx<m) {
				if (spread[newy][newx] == 0)
				{
				spread[newy][newx] = 2;
				qq.push(make_pair(newy, newx));

			}
			}
		}

	}

	int tempres = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			if (spread[i][j] == 0) {
				tempres++;
			}
		}
	}

	res = max(res, tempres);

}


void walldfs(int cnt) {

	int i, j;
	if (cnt == 3) {

		bfs();
		return;
	}


	for ( i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {

			if (temp[i][j] == 0) {
				temp[i][j] = 1;
				walldfs(cnt + 1);
				temp[i][j] = 0;
			}
		}
	}
	
}

int main() {

	cin >> n >> m;
	int i, j, k,l;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			cin >> temp[i][j];
		}
	}

	for (i = 0; i < n; i++) 
	{

		for (j = 0; j < m; j++) 
		{

			if (temp[i][j] == 0) {

				
				
				temp[i][j] = 1;

				walldfs(1);
				temp[i][j] = 0;
			}
		}
	}

	cout << res;
	return 0;

}

