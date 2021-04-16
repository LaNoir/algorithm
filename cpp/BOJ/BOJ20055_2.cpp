#include <iostream>
#include <deque>
using namespace std;

int N, K;
deque<int> belt;
deque<bool> robots;
//10:33

void shiftBelt() {
	belt.push_front(belt.back());
	belt.pop_back();
	robots.push_front(robots.back());
	robots.pop_back();
	robots[N - 1] = false;
}


int findzero() {
	int res = 0;
	for (int i = 0; i < 2 * N; i++) {
		if (belt[i] < 1)
			res++;
	}
	return res;
}

void move() {
	for (int i = N - 2; i >= 0; i--) {
		if (robots[i] && belt[i + 1] > 0 && !robots[i + 1]) {
			robots[i + 1] = true;
			belt[i + 1]--;
			robots[i] = false;
		}
	}
	robots[N - 1] = false;
}

void put_robot()
{
	if (!robots[0] && belt[0] > 0) {
		robots[0] = true;
		belt[0]--;
	}
}

int main() {
	scanf("%d", &N);
	scanf("%d", &K);
	int zero = 0;
	int a;

	for (int i = 0; i < 2 * N; i++) {
		scanf("%d", &a);
		belt.push_back(a);
	}
	for (int i = 0; i < N; i++) {
		robots.push_back(false);
	}
	//	내구도가 0인 칸의 개수가 K개 이상이라면 과정을 종료한다.그렇지 않다면 1번으로 돌아간다.
	int turn = 1;
	while (1) {

		//rotate
		shiftBelt();

		//move
		move();

		//put
		put_robot();

		//check

		if (findzero() >= K) {
			cout << turn;
			return 0;
			break;
		}
		turn++;


	}
	return 0;
}