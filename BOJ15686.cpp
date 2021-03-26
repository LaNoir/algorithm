#include <iostream>
#include <vector>
using namespace std;

int N, M;
int map[50][50];
int temp[50][50];
bool visited[13];
vector<pair<int, int>> house, chikens;
int res = 987654;
// y, x순


void dfs(int idx, int count) {
	if (count == M) {

		int tres = 0;

		for (int i = 0; i < house.size(); i++)
		{
			int dist = 400;
			for (int j = 0; j < chikens.size(); j++) {
				if (visited[j]) {
					dist = min(dist, abs(house[i].first - chikens[j].first) + abs(house[i].second - chikens[j].second));
				}
			}
			tres += dist;

		}
		res = min(res, tres);
		return;
	}

	if (idx == chikens.size())
		return;

	visited[idx] = true;
	dfs(idx+1, count + 1);
	visited[idx] = false;
	dfs(idx + 1, count);

}

int main() {

	cin >> N >> M;
	int r, c;
	int tt;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> tt;
			if (tt == 1) {
				house.push_back({ i,j });
			}
			if (tt == 2) {
				chikens.push_back({ i,j });
			}
			map[i][j] = tt;
		}
	}

	dfs(0,0);

	cout << res;
	return 0;
}