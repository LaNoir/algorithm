#include <iostream>
#include <queue>
#include <string>
using namespace std;

int N, M, K;

//상하좌우
struct INFO {
	int sizes, dir;
};
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };

INFO board[100][100];
vector<INFO> temp[100][100];
int T, res;
void move() {

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			temp[y][x].clear();
		}
	}

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (board[y][x].sizes != 0) {
				INFO cur = board[y][x];
				int ny = y + dy[cur.dir];
				int nx = x + dx[cur.dir];
				int nd = cur.dir;
				int nsizes = cur.sizes;

				if (ny == 0 || ny == N - 1 || nx == 0 || nx == N - 1) {
					switch (nd)
					{
					case 0:
						nd = 1;
						break;
					case 1:
						nd = 0;
						break;
					case 2:
						nd = 3;
						break;
					case 3:
						nd = 2;
						break;
					}

					nsizes /= 2;

				}
				if (nsizes != 0) {
					temp[ny][nx].push_back({ nsizes,nd });
				}
			}
			
		}
	}
	//여기까지 temp에 다 저장됨.

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			int aa = temp[y][x].size();
			if (aa == 0){
				board[y][x].sizes = 0;
				board[y][x].dir = 0;
				continue;
			}
			else if (aa == 1) {
				board[y][x].sizes = temp[y][x][0].sizes;
				board[y][x].dir = temp[y][x][0].dir;
				continue;
			}
			else{
				int max_sizes = -1;
				int dir = 0;
				int sum = 0;

				for (int r = 0; r < aa; r++) {
					if (temp[y][x][r].sizes > max_sizes) {
						max_sizes = temp[y][x][r].sizes;
						dir = temp[y][x][r].dir;
					}

					sum += temp[y][x][r].sizes;

				}
				board[y][x].sizes = sum;
				board[y][x].dir = dir;
			}
		}
	}

}

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> T;


	for (int t = 0; t < T; t++) {
		cin >> N >> M >> K;
		res = 0;


		for (int i = 0; i < K; i++) {
			int y, x, sizes, d;
			cin >> y >> x >> sizes >> d;
			y, x, d--;
			board[y][x] = { sizes,d };
		}

		for (int i = 0; i < M; i++) {
			move();
		}


		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				res += board[y][x].sizes;
				board[y][x] = { 0,0 };
			}
		}
		cout << "#" << t + 1 << " " << res << "\n";
	}
	return 0;
}
