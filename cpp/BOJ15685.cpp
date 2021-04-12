#include <iostream>
#include<vector>
using namespace std;

int map[101][101];
int x, y, d, g;
int res = 0;
//우상좌하
int T;
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,-1,0,1 };

int main() {

	cin >> T;

	while(T){
	T--;
	cin >> x >> y >> d >> g;
	vector<int> dragon;
	

	while (!dragon.empty())
		dragon.pop_back();



	dragon.push_back(d);


	for (int i = 0; i < g; i++) {

		for (int j = dragon.size() - 1; j >= 0; j--) {

			dragon.push_back((dragon[j] + 1) % 4);

		}

	}

	map[y][x] = 1;
	int newx, newy;
	for (int i = 0; i < dragon.size(); i++) {
		x = x + dx[dragon[i]];
		y = y + dy[dragon[i]];

		if (x < 0 || x>100 || y < 0 || y>100) {
			continue;
		}
		map[y][x] = 1;

	}
	}


	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (map[i][j] && map[i + 1][j] && map[i][j + 1] && map[i + 1][j + 1]) {
				res++;
			}
		}
	}

	cout << res;
}