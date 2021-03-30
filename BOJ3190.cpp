#include <iostream>
#include <deque>
#include <queue>
#include <vector>
using namespace std;

//각 우, 상, 좌, 하 순서
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,-1,0,1 };

int map[101][101] = { 0, };



int main() {
	//1 for apple
	//2 for snake's body
	//0 for empty space
	int N, K, L;

	cin >> N >> K;
	int curx = 1;
	int cury = 1;
	int y, x;
	for (int i = 0; i < K; i++) {
		cin >> y >> x;
		map[y][x] = 1;
	}

	cin >> L;

	int X;
	char C;

	queue <pair<int, char>> commands;
	deque <pair<int, int>> snake;

	int newx, newy;
	int d = 0;
	int time = 0;


	snake.push_back(make_pair(1, 1));
	//x,y순서

	for (int i = 0; i < L; i++) {
		cin >> X >> C;
		commands.push(make_pair(X, C));
	}

	int tailx, taily;

	while (1) {

		time++;

		newx = snake.front().first + dx[d];
		newy = snake.front().second + dy[d];


		//종료조건
		if (newx < 1 || newx > N || newy<1 || newy> N || map[newy][newx] == 2) {
			break;
		}

		//새로운 좌표가 1이다
		snake.push_front(make_pair(newx, newy));
		


		//새로운 좌표가 0이다.
		if (map[newy][newx] == 0) {
			//cout << "snakeLength: " << snake.size() << endl;
			//cout << "snaketail: " << " x: " << snake.back().first << " y: " << snake.back().second << endl;
			map[snake.back().second][snake.back().first] = 0;
			snake.pop_back();
		}

		map[newy][newx] = 2;

		//방향 전환.
		if (!commands.empty() && time == commands.front().first)
		{
			if (commands.front().second == 'L') {
				d = (d + 1) % 4;
			}
			else
				d = (d + 3) % 4;
			commands.pop();
		}

	}
	cout << time;

}
