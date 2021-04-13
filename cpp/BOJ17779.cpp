#include <iostream>

using namespace std;

/*
기준점 (x, y)와 경계의 길이 d1, d2를 정한다. (d1, d2 ≥ 1, 1 ≤ x < x+d1+d2 ≤ N, 1 ≤ y-d1 < y < y+d2 ≤ N)
다음 칸은 경계선이다.
(x, y), (x+1, y-1), ..., (x+d1, y-d1)
(x, y), (x+1, y+1), ..., (x+d2, y+d2)
(x+d1, y-d1), (x+d1+1, y-d1+1), ... (x+d1+d2, y-d1+d2)
(x+d2, y+d2), (x+d2+1, y+d2-1), ..., (x+d2+d1, y+d2-d1)
경계선과 경계선의 안에 포함되어있는 곳은 5번 선거구이다.
5번 선거구에 포함되지 않은 구역 (r, c)의 선거구 번호는 다음 기준을 따른다.
1번 선거구: 1 ≤ r < x+d1, 1 ≤ c ≤ y
2번 선거구: 1 ≤ r ≤ x+d2, y < c ≤ N
3번 선거구: x+d1 ≤ r ≤ N, 1 ≤ c < y-d1+d2
4번 선거구: x+d2 < r ≤ N, y-d1+d2 ≤ c ≤ N
*/

int n, sum = 0;
int map[21][21] = { 0, };


int solve(int x, int y, int d1, int d2) {
	int temp[21][21] = { 0, };
	temp[x][y] = 5;
	//(x, y), (x + 1, y - 1), ..., (x + d1, y - d1)
	//	(x + d2, y + d2), (x + d2 + 1, y + d2 - 1), ..., (x + d2 + d1, y + d2 - d1)

	for (int i = 1; i <= d1; i++) {
		temp[x + i][y - i] = 5;
		temp[x + d2 + i][y + d2 - i] = 5;
	}
	//	(x, y), (x + 1, y + 1), ..., (x + d2, y + d2)
	//	(x + d1, y - d1), (x + d1 + 1, y - d1 + 1), ... (x + d1 + d2, y - d1 + d2)
	for (int i = 1; i <= d2; i++) {
		temp[x + i][y + i] = 5;
		temp[x + d1 + i][y - d1 + i] = 5;
	}

	//5번 선거구에 포함되지 않은 구역(r, c)의 선거구 번호는 다음 기준을 따른다.
	//	1번 선거구 : 1 ≤ r < x + d1, 1 ≤ c ≤ y
	int aa = 0;
	for (int r = 1; r < x + d1; r++) {
		for (int c = 1; c <= y; c++) {
			if (temp[r][c] == 5) {
				break;
			}
			aa += map[r][c];
		}
	}
	//	2번 선거구 : 1 ≤ r ≤ x + d2, y < c ≤ N
	int bb = 0;
	for (int r = 1; r <= x + d2; r++) {
		for (int c = n; c > y; c--) {
			if (temp[r][c] == 5) {
				break;
			}
			bb += map[r][c];
		}
	}
	 
	//	3번 선거구 : x + d1 ≤ r ≤ N, 1 ≤ c < y - d1 + d2
	int cc = 0;

	for (int r = x + d1; r <= n; r++) {
		for (int c = 1; c < y - d1 + d2; c++) {
			if (temp[r][c] == 5) {
				break;
			}
			cc += map[r][c];
		}
	}
	
	//	4번 선거구 : x + d2 < r ≤ N, y - d1 + d2 ≤ c ≤ N
	int dd = 0;

	for (int r = x + d2+1; r <= n; r++) {
		for (int c = n; c >= y - d1 + d2; c--) {
			if (temp[r][c] == 5) {
				break;
			}
				dd += map[r][c];
		}
	}

	int ee =  sum - aa - bb - cc - dd;
	int max_val = max(aa, max(bb, max(cc, max(dd, ee))));
	int min_val = min(aa, min(bb, min(cc, min(dd, ee))));

	return (max_val - min_val);
}


int main() {
	cin >> n;

	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++)
		{
			cin >> map[x][y];
			sum += map[x][y];
		}
	}

	int res = 897654321;

	//(d1, d2 ≥ 1, 1 ≤ x < x+d1+d2 ≤ N, 1 ≤ y-d1 < y < y+d2 ≤ N)

	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++) {
			for (int d1 = 1; d1 <= n; d1++) {
				for (int d2 = 1; d2 <= n; d2++) {
					if (x + d1 + d2 >n) continue;
					if (1 > y - d1 ) continue;
					if (y + d2 > n) continue;
					res = min(res, solve(x, y, d1, d2));
				}
			}
		}
	}

	cout << res;

	return 0;
}