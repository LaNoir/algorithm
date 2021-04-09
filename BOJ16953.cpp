#include <iostream>
#include <vector>
#include<queue>
using namespace std;

long long N, M;
int res = 987654321;

void dfs(int count, long long num) {
	if (num == M) {
		res = min(res, count);
	}

	if (num > M)
		return;
	
	dfs(count + 1, num * 2);

	dfs(count + 1, (num * 10) + 1);
}

int main() {
	cin >> N >>M;
	
	dfs(1, N);

	if (res == 987654321)
		res = -1;

	cout << res;

}