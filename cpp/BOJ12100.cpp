#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
#include <queue>
using namespace std;

int N;
int map[20][20];
int res;


//idx = 0, 그냥 그자리에 넣음,
//idx == q와 같음 둘이 더하고 idx증가
//idx 다름 idx증가하고, 값 그자리에 넣음

void move(int direction) {

	queue<int> q;



	switch (direction) {
		//왼쪽..	
		case 0: 


		for (int i = 0; i < N; i++) {

			for (int j = 0; j < N; j++) {
				if (map[i][j] != 0) {
					q.push(map[i][j]);
				}
				map[i][j] = 0;

			}

			int idx = 0;

			while (!q.empty()) {


				int data = q.front();
				q.pop();

					if (map[i][idx] == 0) {
						map[i][idx] = data;
					}
					else if (map[i][idx] == data) {
						map[i][idx] += data;
						idx++;
					}
					else {
						idx++;
						map[i][idx] = data;
					}
				}
			
		
		}
		
		break;

		//오른쪽 --> 위에서 아래로 가면서 N-1 -> 0까지 순서대로 채운다.
		case 1:
			for (int i = 0; i < N; i++) {
				for (int j = N - 1; j >= 0; j--) {
					if (map[i][j] != 0) {
						q.push(map[i][j]);
						map[i][j] = 0;
					}
				}

				int idx = N-1;

				while (!q.empty()) {

					int data = q.front();
					q.pop();

						if (map[i][idx] == 0) {
							map[i][idx] = data;
						}
						else if (map[i][idx] == data) {
							map[i][idx] += data;
							idx--;
						}
						else {
							idx--;
							map[i][idx] = data;
						}
					
				}


			}
		break;



		case 2:

			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (map[j][i] != 0) {
						q.push(map[j][i]);
						map[j][i] = 0;
					}
				}
			

			int idx = 0;

			while (!q.empty()) {

				int data = q.front();
				q.pop();

				if (map[idx][i] == 0) {
					map[idx][i] = data;
				}
				else if (map[idx][i] == data) {
					map[idx][i] *= 2;
					idx++;
				}
				else {
					idx++;
					map[idx][i] = data;
				}

			}
			}
		break;
		case 3:

			for (int i = 0; i < N; i++) {
				for (int j = N-1; j >= 0; j--) {
					if (map[j][i] != 0) {
						q.push(map[j][i]);
						map[j][i] = 0;
					}
				}


				int idx = N-1;

				while (!q.empty()) {

					int data = q.front();
					q.pop();

					if (map[idx][i] == 0) {
						map[idx][i] = data;
					}
					else if (map[idx][i] == data) {
						map[idx][i] *= 2;
						idx--;
					}
					else {
						idx--;
						map[idx][i] = data;
					}

				}
			}
		break;
	}
}

void dfs(int count) {
	int cmap[20][20];

	if (count == 5) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				res = max(res, map[i][j]);
		}
		return;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cmap[i][j] = map[i][j];
	}

	for (int i = 0; i < 4; i++) {
		move(i);
		dfs(count + 1);
	
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				map[i][j] = cmap[i][j];
		}
	}
}

int main() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		for(int j =0;j<N; j++)
		cin >> map[i][j];
	}



	dfs(0);
	
	cout << res;

	return  0;
}