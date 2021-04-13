#include <iostream>
#include <queue>
#include <string>
using namespace std;

int V,E;
vector<int> board[20001];
int check[20001] = { false, };
int colors[20001] = { false, };
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,-1,0,1 };

bool isCycle = false;

void init() {
	for (int i = 0; i <= 20000; i++) {
		board[i].clear();
		check[i] = false;
		colors[i] = false;
		isCycle = false;
	}
}

void dfs(int start) {
	check[start] = true;

	for (int i = 0; i < board[start].size(); i++) {
		int node = board[start][i];

		if (check[node] == 0) {
			colors[node] = !colors[start];
			dfs(node);
		}
		else if (colors[node] == colors[start]) {
			isCycle = true;
			return;
		}

	}
}

int main() {

	int T;

	cin >> T;

	while (T) {
		T--;

		cin >> V >> E;
		init();
		int start, end;

		for (int y = 0; y < E; y++) {
			cin >> start >> end;
			board[start].push_back(end);
			board[end].push_back(start);
		}

		for (int i = 1; i < V; i++) {
			if (check[i] == 0)
				dfs(i);
		}

		isCycle ? cout << "NO\n" : cout << "YES\n";

	}


}