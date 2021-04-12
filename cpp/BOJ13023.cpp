#include <iostream>
#include <vector>
using namespace std;

int N, M;

bool visit[2000];
vector<int> friends[2000];

int res = 0;

void dfs(int start, int count) {

	if (count >= 4) {
		res = 1;
		return;
	}
	if (res == 1)
		return;

	visit[start] = true;


	for (int i = 0; i < friends[start].size(); i++) {
		if(!visit[friends[start][i]])
			dfs(friends[start][i], count + 1);
	}

	visit[start] = false;

}

int main() {
	cin >> N >> M;
	int start, end;
	for (int i = 0; i < M; i++) {
		cin >> start >> end;
		friends[start].push_back(end);
		friends[end].push_back(start);
	}

	for (int i = 0; i < N; i++) {
		if (res == 1)
			break;
		dfs(i, 0);
	}

	
	cout << res;
}