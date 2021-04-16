// 19"40'

#include <iostream>
#include <queue>
using namespace std;

int board[5];

bool check_sorted() {
	bool ans = true;
	for (int i = 0; i < 5; i++) {
		if (board[i] != i + 1)
			ans = false;
	}
	return ans;
}

int main() {

	for (int i = 0; i < 5; i++) {
		cin >> board[i];
	}

	while (1) {
		if (check_sorted()) {
			return 0;
		}
		int temp;
		bool is_update = false;
		for (int i = 0; i < 4; i++) {
			if (board[i] > board[i + 1]) {
				temp = board[i];
				board[i] = board[i + 1];
				board[i + 1] = temp;
				for (int i = 0; i < 5; i++) {
					cout << board[i] << " ";
				}
				cout << "\n";
			}
		}
		
	}
	return 0;
}