#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

int n, m, map[500][500],result;
bool check[500][500];

int dx[4] = { 1, -1, 0, 0 }; //동서남북
int dy[4] = { 0, 0, 1, -1 };

bool isProPerCord(int r, int c) {
	if (r < 0 || r > n-1 ||c<0||c>m-1){
		return false;
	}

	return true;
}

void dfs(int i,int j,int sum, int depth) {
	if (depth >= 4) {
		result = max(sum, result);
		return;
	}

	for (int k = 0; k < 4; k++) {
		int newi, newj;
		newi = i + dx[k];
		newj = j + dy[k];
		if (isProPerCord(newi, newj)) {
			if (!check[newi][newj]) {
				check[newi][newj] = true;
				dfs(newi, newj, sum+map[newi][newj], depth + 1);
				check[newi][newj] = false;

			}
		}
	}

}

void findchulgu(int i, int j) {
	//동서남북
	int ewsn[4] = { 0, };
	int temp = 0;
	for (int k = 0; k < 4; k++) {
		int newi = i + dx[k];
		int newj = j + dy[k];
		if (isProPerCord(newi, newj))
			ewsn[k] = 1;
	}

	//ㅗ
	if (ewsn[0] && ewsn[1] && ewsn[3]) {
		temp = map[i][j] + map[i + dx[0]][j + dy[0]] + map[i + dx[1]][j + dy[1]] + map[i + dx[3]][j + dy[3]];
		result = max(result, temp);
		temp = 0;
	}

	//ㅜ
	if (ewsn[0] && ewsn[1] && ewsn[2]) {
		temp = map[i][j] + map[i + dx[0]][j + dy[0]] + map[i + dx[1]][j + dy[1]] + map[i + dx[2]][j + dy[2]];
		result = max(result, temp);
		temp = 0;
	}

	if (ewsn[0] && ewsn[3] && ewsn[2]) {
		temp = map[i][j] + map[i + dx[0]][j + dy[0]] + map[i + dx[3]][j + dy[3]] + map[i + dx[2]][j + dy[2]];
		result = max(result, temp);
		temp = 0;
	}

	if (ewsn[3] && ewsn[1] && ewsn[2]) {
		temp = map[i][j] + map[i + dx[1]][j + dy[1]] + map[i + dx[3]][j + dy[3]] + map[i + dx[2]][j + dy[2]];
		result = max(result, temp);
		temp = 0;
	}

}

int main() {

	int i,j;

	cin.tie(0);

	cin >> n >> m;

	for (i = 0; i < n; i++) {
		for(j=0; j<m; j++){
			cin >> map[i][j];
		}
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			check[i][j] = true;
			dfs(i, j, map[i][j], 1);
			check[i][j] = false;

			findchulgu(i, j);

		}
	}

	cout << result;

}

