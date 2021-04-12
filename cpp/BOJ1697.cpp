#include <iostream>
#include <queue>
using namespace std;



typedef struct subin {
	int cord, time;
};

bool visit[100001] = {false,};

int main() {

	int su, sister;
	cin >> su >> sister;
	
	queue<subin> qq;

	qq.push({ su, 0 });

	visit[su] = true;

	while (!qq.empty()) {

		int curCord = qq.front().cord;
		int time = qq.front().time;

		qq.pop();

		if (curCord == sister) {
			cout << time;
			return 0;
		}
		int newCord = curCord - 1;

		if (newCord >= 0 && newCord < 100001 && !visit[newCord]) {
			qq.push({ newCord, time + 1 });
			visit[newCord] = true;
		}

		newCord = curCord + 1;

		if (newCord >= 0 && newCord < 100001 && !visit[newCord]) {
			qq.push({ newCord, time + 1 });
			visit[newCord] = true;
		}

		newCord = curCord * 2;

		if (newCord >= 0 && newCord < 100001 && !visit[newCord]) {
			qq.push({ newCord, time + 1 });
			visit[newCord] = true;

		}
	}
}