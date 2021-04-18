

#include<iostream>
#include <vector>
using namespace std;
//21"57'

int N, X;
int board[21][21];
vector<int> line;
int res = 0;

bool check() {

	int space = 1;
	int prev = line[0];
	for (int i = 1; i < line.size(); i++) {

		if (abs(line[i] - prev) > 1) {
			return false;
		}

		if (line[i] > prev) {
			if (space < X) {
				return false;
			}
			else {
				space = 1;
				prev = line[i];
			}
		}
		else if (line[i] < prev) {
			if (space < 0)
				return false;
			space = -1 * X + 1;
			prev = line[i];
		}
		else {
			space++;
		}
	}

	if (space >= 0) {
		return true;
	}
	return false;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin >> T;
	
	for (test_case = 1; test_case <= T; ++test_case)
	{
		res = 0;
		cin >> N >> X;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				cin >> board[y][x];
			}
		}


		for (int y = 0; y < N; y++) {
			line.clear();
			for (int x = 0; x < N; x++) {
				line.push_back(board[y][x]);
			}
			if (check()) {
				res++;
			}
		}

		for (int x = 0; x < N; x++) {
			line.clear();
			for (int y = 0; y < N; y++) {
				line.push_back(board[y][x]);
			}
			if (check()) {
				res++;
			}
		}

		cout << "#" << test_case << " " << res << "\n";

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}