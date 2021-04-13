#include <iostream>
#include <queue>
#include <string>
using namespace std;

int N, M, K;
int board[50][50];
int res = -1;

typedef struct point {
	int y, x, time;
	bool br;
};

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,-1,0,1 };
bool check[50][50] = { false, };

void bfs(int y, int x) {
	
	queue<pair<int, int>> q;

	q.push({ y,x });
	check[y][x] = true;

	while (!q.empty()) {
		int curx = q.front().second;
		int cury = q.front().first;
		q.pop();
		int newy, newx;
		for (int i = 0; i < 4; i++) {
			newy = cury + dy[i];
			newx = curx + dx[i];

			if (newy < 0 || newx<0 || newy >= N || newx >= M) {

				continue;
			}
			if(board[newy][newx] == 1 && check[newy][newx] == false){
				q.push({ newy,newx });
				check[newy][newx] = true;
			}

		}
	}
	

}

int main() {

	int T;

	cin >> T;

	while (T) {
		T--;
		

		//여까지 초기화 작업.
		cin >> M >> N >> K;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < M; x++) {
				board[y][x] = 0;
				check[y][x] = false;
			}
		}
		int r, c;
		int count = 0;
		for (int i = 0; i < K; i++) {
			

			cin >> r >> c;

			board[c][r] = 1;
		}

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < M; x++) {
				if (board[y][x] == 1 && check[y][x] == false) {
					bfs(y, x);
					count++;
				}
			}
		}
		cout << count;
		cout << "\n";

	}



}