#include <iostream>

using namespace std;

int map[200][100];
int temp[100];
int N, L;
int res = 0;
int main() {

	cin >> N >> L;
	

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			map[N+j][i] = map[i][j];
		}
	}
	

	for (int i = 0; i < 2 * N; i++) {

		int count = 1;

		bool flag = true;
		
		for (int j = 1; j < N; j++) {
			if (map[i][j - 1] == map[i][j]) {
				count++;
			}
			else if (map[i][j - 1] + 1 == map[i][j] && count >= L) {
				count = 1;
			}
			else if (map[i][j - 1] - 1 == map[i][j] && count >= 0) {
				count = 1 - L;
			}
			else {
				flag = false;
				break;
			}
		}
		if (flag == true && count >= 0)
			res++;
	}
	cout << res;

}