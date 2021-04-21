//17"13'
#include <iostream>
#include <string.h>
using namespace std;

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };


struct CELL {
	int stauts; // 0 dead, , 1 unactiveated, 2 activated 
	int size, dur;
};

int res = 0;

CELL cell[350][350];
bool tcell[350][350];
int N, M, K;

void init() {
	for (int y = 0; y < 350; y++) {
		for (int x = 0; x < 350; x++) {
			cell[y][x] = { 0,0,0 };
		}
	}
}

void initTemp() {
	memset(tcell,false,sizeof(tcell));
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int test_case;
	int T;
	/*
	   아래의 freopen 함수는 input.txt 를 read only 형식으로 연 후,
	   앞으로 표준 입력(키보드) 대신 input.txt 파일로부터 읽어오겠다는 의미의 코드입니다.
	   //여러분이 작성한 코드를 테스트 할 때, 편의를 위해서 input.txt에 입력을 저장한 후,
	   freopen 함수를 이용하면 이후 cin 을 수행할 때 표준 입력 대신 파일로부터 입력을 받아올 수 있습니다.
	   따라서 테스트를 수행할 때에는 아래 주석을 지우고 이 함수를 사용하셔도 좋습니다.
	   freopen 함수를 사용하기 위해서는 #include <cstdio>, 혹은 #include <stdio.h> 가 필요합니다.
	   단, 채점을 위해 코드를 제출하실 때에는 반드시 freopen 함수를 지우거나 주석 처리 하셔야 합니다.
	*/
	//freopen("input.txt", "r", stdin);
	cin >> T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{
		init();
		cin >> N >> M >> K;
		int a;
		for (int i = 151; i < 151 + N; i++) {
			for (int j = 151; j < 151 + M; j++) {
				cin >> a;
				if (a != 0) {
					cell[i][j].stauts = 1;
					cell[i][j].dur = a;
					cell[i][j].size = a;
				}
			}
		}
		res = 0;
		for (int k = 0; k < K; k++) {
			initTemp();
			for (int y = 0; y < 350; y++) {
				for (int x = 0; x < 350; x++) {

					if (cell[y][x].stauts == 0) {
						continue;
					}

					else if (cell[y][x].stauts == 1 && tcell[y][x] == false) {
						cell[y][x].dur--;
						if (cell[y][x].dur == 0) {
							cell[y][x].stauts = 2;
							cell[y][x].dur = cell[y][x].size;
						}
					}

					else if (cell[y][x].stauts == 2) {

						int ny, nx;

						for (int d = 0; d < 4; d++) {
							ny = y + dy[d];
							nx = x + dx[d];

							if (cell[ny][nx].size == 0) {
								cell[ny][nx].dur = cell[y][x].size;
								cell[ny][nx].size = cell[y][x].size;
								cell[ny][nx].stauts = 1;
								tcell[ny][nx] = true;
							}

							else {
								//방금 번식함 + 나보다 사이즈 작은것
								if (cell[ny][nx].stauts == 1 && tcell[ny][nx] == true && cell[ny][nx].size < cell[y][x].size) {
									cell[ny][nx].dur = cell[y][x].size;
									cell[ny][nx].size = cell[y][x].size;
									cell[ny][nx].stauts = 1;
									tcell[ny][nx] = true;
								}
							}


						}
						cell[y][x].dur--;
						if (cell[y][x].dur == 0) {
							cell[y][x].stauts = 0;
						}

					}

				}
			}

		}

		for (int y = 0; y < 350; y++) {
			for (int x = 0; x < 350; x++) {
				if (cell[y][x].stauts != 0) {
					res++;
				}
			}
		}

		cout << "#" << test_case << " " << res << "\n";
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}