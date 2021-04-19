#include <iostream>
#include <queue>
#include <vector>
using namespace std;
//10"17 -> 10"28'

// ↑, ↖, ←, ↙, ↓, ↘, →, ↗ 
int dy[8] = { -1,-1,0,1,1,1,0,-1 };
int dx[8] = { 0,-1,-1,-1,0,1,1,1 };

int N;

int typepriority[8][8];
int K, C;
int board[100][4] = { 0, };

struct COMMAND {
	int k, c;
};

vector<COMMAND> com;
int trial[100];

int res = 0;


void put(int row, int nn) {
	for (int i = N - 1; i >= 0; i--) {
		if (board[i][row] == 0) {
			board[i][row] = nn;
			return;
		}
	}
}

int bomb() {
	int ans = 0;

	for (int i = N - 1; i >= 0; i--) {
	
		if (board[i][0] && board[i][1] && board[i][2] && board[i][3]) {
			ans++;
			board[i][0] = 0;
			board[i][1] = 0;
			board[i][2] = 0;
			board[i][3] = 0;
		}
	
	}
	

	return ans;
}
vector<int> line;
void drop() {

	for (int j = 0; j < 4; j++) {
		line.clear();
		for (int i = N-1; i >= 0; i--) {
			if (board[i][j] != 0) {
				line.push_back(board[i][j]);
			}
		}

		while (line.size() < N) {
			line.push_back(0);
		}
		int k = 0;
		for (int i = N-1; i >=0; i--) {
			board[i][j] = line[k++];
		}

	}
}
void move() {
	int tboard[100][4] = { 0, };

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 4; j++) {
		
			if (board[i][j] != 0) {
				int ny, nx;
				for (int d = 0; d < 8; d++) {
					ny = i + dy[typepriority[board[i][j] - 1][d]];
					nx = j + dx[typepriority[board[i][j] - 1][d]];

					if (ny < 0 || nx < 0 || ny >= N || nx >= 4) {
						continue;
					}
					
					if(tboard[ny][nx] == 0 || (tboard[ny][nx] > board[i][j])){
						tboard[ny][nx] = board[i][j];
					}
					break;
				}
			}
		
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 4; j++) {
			board[i][j] = tboard[i][j];
		}
	}

}
void play() {
	int ans = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 4; j++) {
			board[i][j] = 0;
		}
	}

	for (int i = 0; i < N; i++) {

		put(trial[i], com[i].k);
		
		while (1) {
			int a = bomb();
			if(a != 0) {
				ans += a;
				drop();
			}
			else {
				break;
			}
		}

		move();
		drop();
		while (1) {
			int a = bomb();
			if (a != 0) {
				ans += a;
				drop();
			}
			else {
				break;
			}
		}

	}
	res = max(res, ans);
}

void dfs(int count) {

	if (count == N) {
		/*for (int i = 0; i < N; i++) {
			cout << trial[i] << " ";
		}*/
		play();
		return;
	}

	if (com[count].c == -1) {
		for (int i = 0; i < 4; i++) {
			trial[count] = i;
			dfs(count + 1);
		}
	}
	else {
		trial[count] = com[count].c;
		dfs(count + 1);
	}

}

int main() {
	cin >> N;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cin >> typepriority[i][j];
			typepriority[i][j]--;
		}
	}
	for (int i = 0; i < N; i++) {
		cin >> K >> C;
		//방향 볼때는 -1하자.
		com.push_back({ K,--C });
	}


	dfs(0);
	cout << res;
}