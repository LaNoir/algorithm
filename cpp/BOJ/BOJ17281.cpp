
#include <iostream>
#include <queue>
#include <string>
using namespace std;

int player[50][9];
int res = 0;
bool selected[9] = { false, };
int ening;
int play(int tasun[]) {

	int idx = 0;
	int score = 0;
	int Base[3] = { 0, };
	int nowplayer;
	for (int i = 0; i < ening; i++) {
		int out = 0;
		while (1) {
			int playing = player[i][tasun[idx]];
			if (playing == 0) {
				out++;
			}
			else if (playing == 1) {
				if (Base[2] == 1) {
					score++;
				}
				Base[2] = Base[1];
				Base[1] = Base[0];
				Base[0] = 1;
			}
			else if (playing == 2) {
				if (Base[2] == 1) {
					score++;
				}
				if (Base[1] == 1) {
					score++;
				}

				Base[2] = Base[0];
				Base[1] = 1;
				Base[0] = 0;
				//2루타
			}
			else if (playing == 3) {
				if (Base[2] == 1) {
					score++;
				}
				if (Base[1] == 1) {
					score++;
				}
				if (Base[0] == 1) {
					score++;
				}
				Base[2] = 1;
				Base[1] = 0;
				Base[0] = 0;
				//3루타
			}
			else if (playing == 4) {
				if (Base[2] == 1) {
					score++;
				}
				if (Base[1] == 1) {
					score++;
				}
				if (Base[0] == 1) {
					score++;
				}
				score++;
				Base[2] = 0;
				Base[1] = 0;
				Base[0] = 0;
				//홈런
			}

			idx = (idx + 1) % 9;

			if (out >= 3) {
				Base[2] = 0;
				Base[1] = 0;
				Base[0] = 0;	
				break;
			}

		}

	}
	return score;
}
int cnt = 0;
void dfs(int count, int tasun[]) {
	
	if (count == 9) {
		res = max(res, play(tasun));
		return;
	}

	for (int i = 0; i < 9; i++) {
		if (selected[i] == true) continue;
		selected[i] = true;
		tasun[i] = count;
		dfs(count + 1, tasun);
		selected[i] = false;
	}

}

int main() {

	cin >> ening;

	for (int i = 0; i < ening; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> player[i][j];
		}
	}
	
	
	selected[3] = true;

	int tasun[9] = { 0, };
	tasun[3] = 0;

	dfs(1, tasun);
	cout << res;
}
