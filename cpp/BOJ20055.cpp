#include <iostream>
#include <deque>
using namespace std;

int N, K;
deque<int> belt;
deque<int> robots;
//10:33

void shiftBelt() {
	belt.push_front(belt.back());
	belt.pop_back();
	robots.push_front(robots.back());
	robots.pop_back();
}


int findzero(int NN) {
	int res = 0;
	for (int i = 0; i < NN; i++) {
		if (belt[i] < 1)
			res++;
	}
	return res;
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
		robots.push_back(0);
	}

	//	내구도가 0인 칸의 개수가 K개 이상이라면 과정을 종료한다.그렇지 않다면 1번으로 돌아간다.
	int turn = 0;
	while (1) {

		if (findzero(2 * N) >= K) //여기서 ==을 사용하면 시간초과가 난다!!!!!
			break;

		turn++;
		//벨트가 한 칸 회전한다.
		shiftBelt();
		//위의 로봇도 같이 돌아간다.



		//	가장 먼저 벨트에 올라간 로봇부터, 벨트가 회전하는 방향으로 한 칸 이동할 수 있다면 이동한다.만약 이동할 수 없다면 가만히 있는다.
		for (int i = N - 2; i >= 0; i--) {

			//내려가는 위치에 로봇이 있는 경우 로봇은 반드시 땅으로 내려가야 한다.
			if (robots[N - 1] == 1) {
				robots[N - 1] = 0;
			}

			//	로봇이 이동하기 위해서는 이동하려는 칸에 로봇이 없으며, 그 칸의 내구도가 1 이상 남아 있어야 한다.
			if (robots[i] == 1 && belt[i + 1] > 0 && robots[i + 1] == 0) {
				robots[i + 1] = 1;
				belt[i + 1]--;
				robots[i] = 0;
			}

		}
		//	올라가는 위치에 로봇이 없다면 로봇을 하나 올린다.
		if (robots[0] == 0 && belt[0] > 0) {
			robots[0] = 1;
			belt[0]--;
		}
	}
	cout << turn;
}