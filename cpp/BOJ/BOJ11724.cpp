#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M;

int map[1000][1000];

bool check[1000] = {false,};

void bfs(int start) {
	queue<int> q;
	q.push(start);
	check[start] = 1;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < N; i++) {
			if (map[cur][i] == 1) {
				if (check[i] == 0)
					q.push(i);
					check[i] = 1;
			}
		}
	}
}

int main() {

	cin >> N >> M;

	int s, e;

	for (int i = 0; i < M; i++) {
		cin >> s >> e;
		e--, s--;
		map[s][e] = 1;
		map[e][s] = 1;
	}

	int ans = 0;

	for (int i = 0; i < N; i++) {
		if(check[i] == 0){
			bfs(i);
			ans++;
		}
	}
	cout << ans;
}