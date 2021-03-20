#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int M,N;
int x, y;

int k;
int map[20][20];
int dx[4] = { 1,-1,0,0 }; //동서북남
int dy[4] = { 0,0,-1,1 };

typedef struct {
	int top, right, left, behind, front, below;
}plane;
int r, c;
int main() {

	cin >> N >> M;
	cin >> r >> c;
	cin >> k;

	y = r;
	x = c;

	plane dice;
	dice.top = 0;
	dice.right = 0;
	dice.left = 0;
	dice.behind = 0;
	dice.front = 0;
	dice.below = 0;

	plane newdice;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	map[y][x] = 0;
	int order;
	int newx, newy;
	for (int i = 0; i < k; i++) {

		cin >> order;
		newx = x + dx[order - 1];
		newy = y + dy[order - 1];

		if (newx >= 0 && newx < M && newy >= 0 && newy < N) {

			newdice.top = dice.top;
			newdice.right = dice.right;
			newdice.left = dice.left;
			newdice.behind = dice.behind;
			newdice.front = dice.front;
			newdice.below = dice.below;

			switch (order) {
				//동
			case 1:
				dice.top = newdice.right;
				dice.right = newdice.below;
				dice.left = newdice.top;
				dice.behind = newdice.behind;
				dice.front = newdice.front;
				dice.below = newdice.left;

				break;
				//서
			case 2:
				dice.top = newdice.left;
				dice.right = newdice.top;
				dice.left = newdice.below;
				dice.behind = newdice.behind;
				dice.front = newdice.front;
				dice.below = newdice.right;
				break;
				//북
			case 3:
				dice.top = newdice.behind;
				dice.right = newdice.right;
				dice.left = newdice.left;
				dice.behind = newdice.below;
				dice.front = newdice.top;
				dice.below = newdice.front;
				break;
				//남
			case 4:
				dice.top = newdice.front;
				dice.right = newdice.right;
				dice.left = newdice.left;
				dice.behind = newdice.top;
				dice.front = newdice.below;
				dice.below = newdice.behind;
				break;
			default:
				break;
			}

			if (map[newy][newx] == 0) {
				map[newy][newx] = dice.below;
			}
			else {
				dice.below = map[newy][newx];
				map[newy][newx] = 0;
			}
			cout << dice.top <<endl;
			x = newx;
			y = newy;
		}
		
	}

}

