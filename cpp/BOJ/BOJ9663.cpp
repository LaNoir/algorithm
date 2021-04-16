#include <iostream>

using namespace std;

int N;
int map[15][15];
int queen[15];
int res = 0;

bool verify(int level) {

	for (int i = 0; i < level; i++) {
		if (queen[i] == queen[level] || abs(queen[level] - queen[i]) == level - i)
			return false;
	}
	return true;
}

void dfs(int count) {
	
	if (count == N) {
		res++;
		return;
	}

	for (int i = 0; i < N; i++) {
		queen[count] = i;
		if (verify(count))
			dfs(count + 1);
	}

}

int main() {

	cin >> N;

	int b[15][15];

	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			b[i][j] = 0;
		}
	}

	dfs(0);


	cout << res;
	return 0;
}