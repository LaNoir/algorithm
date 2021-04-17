#include <iostream>
#include <queue>
#include <string>
using namespace std;

int N, W, H;

//상하좌우

int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
struct POS {
	int y, x;
};

int board[15][12];
int tboard[15][12];

bool check[15][12];

int pick[4] = { 0, };
int res = 250;
vector<int> line;

void init() {
	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 12; x++){
			board[y][x] = 0;
			check[y][x] = false;
		}
	}
}


void bfs(int row) {
	
	queue<POS> q;


	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 12; x++) {
			check[y][x] = false;
		}
	}

	int hity = -1;
	for (int i = 0; i < H; i++) {
		if (board[i][row] != 0) {
			hity = i;
			break;
		}
	}
	if (hity == -1) {
		return;
	}

	q.push({ hity,row });
	check[hity][row] = true;
	while (!q.empty()) {
		POS cur = q.front();
		POS next;
		q.pop();
		int brick = board[cur.y][cur.x];
		
			for (int d = 0; d < 4; d++) {
				for (int s = 1; s < brick; s++) {
				next.y = s * dy[d] + cur.y;
				next.x = s * dx[d] + cur.x;

				if (next.x < 0 || next.y<0 || next.x >= W || next.y>=H) {
					break;
				}

				if (check[next.y][next.x] == true) {
					continue;
				}

				q.push(next);
				check[next.y][next.x] = true;

			}
		}
	}

	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			if(check[y][x])
				board[y][x] = 0;
		}
	}
	
}

void down() {

	for (int x = 0; x < W; x++) {
		line.clear();
		for (int y = H-1; y >=0; y--) {
			if (board[y][x] != 0) {
				line.push_back(board[y][x]);
			}
		}

		while (line.size() < H) {
			line.push_back(0);
		}
		int k = 0;
		for (int y = H - 1; y >= 0; y--) {
			board[y][x] = line[k++];
		}
	}

}

void play() {

	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 12; x++) {
			tboard[y][x] = board[y][x];
		}
	}

	for (int i = 0; i < N; i++) {
	
		bfs(pick[i]);
		down();

	}
	int ans = 0;
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
		
			if (board[y][x] != 0) {
				ans++;
			}
		
		}
	}


	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 12; x++) {
			board[y][x] = tboard[y][x];
		}
	}
	res = min(ans, res);
}

void dfs(int count) {
	if (count == N) {
		play();
		
		return;
	}

	else {
		for (int i = 0; i < W; i++) {
			pick[count] = i;
			dfs(count + 1);
		}
	}
}

int main() {

	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{

		init();
		cin >> N >> W >> H;

		for (int y = 0; y < H; y++) {
			for (int x = 0; x < W; x++) {
				cin >> board[y][x];
			}
		}
		res = 250;

		dfs(0);

		cout << "#" << test_case << " " << res<<"\n";
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
	
}
