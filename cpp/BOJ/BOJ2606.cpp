#include <iostream>
#include <queue>
using namespace std;

int N,M,V;
int board[1001][1001];
int tb[1001][1001];

int visited[1001];


int main() {

	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		a; b;
		board[a][b] = 1;
		board[b][a] = 1;
	}

	//bfs
	queue<int> b;

	b.push(1);
	visited[1] = 1;
	while (!b.empty()) {
		int r = b.front();
		b.pop();
		for (int i = 1; i <= N; i++) {
			if (board[r][i] == 1 && visited[i] == 0) {
				b.push(i);
				visited[i] = 1;
			}
		}

	}
	int c = 0;
	for (int i = 1; i <= N; i++) {
		if (visited[i] == 1)
			c++;
	}
	cout << c-1;
}