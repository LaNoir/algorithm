#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int N, T;

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0 ,-1,0,1 };


//  위 아래  앞 뒤 좌 우 순서.
char cube[6][3][3] = {
	{{'w','w','w'},{'w','w','w'},{'w','w','w'}},
	{{'y','y','y'},{'y','y','y'},{'y','y','y'}},
	{{'r','r','r'},{'r','r','r'},{'r','r','r'}},
	{{'o','o','o'},{'o','o','o'},{'o','o','o'}},
	{{'g','g','g'},{'g','g','g'},{'g','g','g'}},
	{{'b','b','b'},{'b','b','b'},{'b','b','b'}}
};

char temp[6][3][3] = {
	{{'w','w','w'},{'w','w','w'},{'w','w','w'}},
	{{'y','y','y'},{'y','y','y'},{'y','y','y'}},
	{{'r','r','r'},{'r','r','r'},{'r','r','r'}},
	{{'o','o','o'},{'o','o','o'},{'o','o','o'}},
	{{'g','g','g'},{'g','g','g'},{'g','g','g'}},
	{{'b','b','b'},{'b','b','b'},{'b','b','b'}}
};


void rotate(char m, char d)
{
	int itself = 0;
	char tcube[6][3][3];

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				tcube[i][j][k] = cube[i][j][k];
			}
		}
	}

	switch (m)
	{
	case 'U':
		itself = 0;
		if (d == '+') {
	
			//앞 바꾸기
			for (int i = 0; i < 3; i++) {
				cube[2][0][i] = tcube[5][0][i];
			}
			//뒤 바꾸기
			for (int i = 0; i < 3; i++) {
				cube[3][0][i] = tcube[4][0][i];
			}
			//왼쪽 바꾸기
			for (int i = 0; i < 3; i++) {
				cube[4][0][i] = tcube[2][0][i];
			}
			//오른쪽 바꾸기

			for (int i = 0; i < 3; i++) {
				cube[5][0][i] = tcube[3][0][i];
			}
		}
		else {

			for (int i = 0; i < 3; i++) {
				cube[5][0][i] = tcube[2][0][i];
			}
			//뒤 바꾸기
			for (int i = 0; i < 3; i++) {
				cube[4][0][i] = tcube[3][0][i];
			}
			//왼쪽 바꾸기
			for (int i = 0; i < 3; i++) {
				cube[2][0][i] = tcube[4][0][i];
			}
			//오른쪽 바꾸기
			for (int i = 0; i < 3; i++) {
				cube[3][0][i] = tcube[5][0][i];
			}
		}
		break;
	case 'D':
		itself = 1;

		if (d == '+') {
			for (int i = 0; i < 3; i++) {
				cube[5][2][i] = tcube[2][2][i];
			}
			//뒤 바꾸기
			for (int i = 0; i < 3; i++) {
				cube[4][2][i] = tcube[3][2][i];
			}
			//왼쪽 바꾸기
			for (int i = 0; i < 3; i++) {
				cube[2][2][i] = tcube[4][2][i];
			}
			//오른쪽 바꾸기
			for (int i = 0; i < 3; i++) {
				cube[3][2][i] = tcube[5][2][i];
			}
			
		}
		else {

			//앞 바꾸기
			for (int i = 0; i < 3; i++) {
				cube[2][2][i] = tcube[5][2][i];
			}
			//뒤 바꾸기
			for (int i = 0; i < 3; i++) {
				cube[3][2][i] = tcube[4][2][i];
			}
			//왼쪽 바꾸기
			for (int i = 0; i < 3; i++) {
				cube[4][2][i] = tcube[2][2][i];
			}
			//오른쪽 바꾸기
			for (int i = 0; i < 3; i++) {
				cube[5][2][i] = tcube[3][2][i];
			}
			
		}
		break;

	case 'F':
		itself = 2;
		//상하 앞뒤 좌우
		if (d == '+') {
			for (int i = 0; i < 3; i++) {
				cube[4][i][2] = tcube[1][0][i];
				cube[1][0][i] = tcube[5][2 - i][0];
				cube[5][2 - i][0] = tcube[0][2][2 - i];
				cube[0][2][2 - i] = tcube[4][i][2];;
			}
		}

		else {
			for (int i = 0; i < 3; i++) {
				cube[4][i][2] = tcube[0][2][2 - i];
				cube[0][2][2 - i] = tcube[5][2 - i][0];
				cube[5][2 - i][0] = tcube[1][0][i];
				cube[1][0][i] = tcube[4][i][2];
			}
		}
		break;
	case 'B':
		itself =3;
		if (d == '+') {
			for (int i = 0; i < 3; i++) {
				cube[4][i][0] = tcube[0][0][2 - i];
				cube[0][0][2 - i] = tcube[5][2 - i][2];
				cube[5][2 - i][2] = tcube[1][2][i];
				cube[1][2][i] = tcube[4][i][0];
			}
		}

		else {
			for (int i = 0; i < 3; i++) {
				cube[4][i][0] = tcube[1][2][i];
				cube[1][2][i] = tcube[5][2 - i][2];
				cube[5][2 - i][2] = tcube[0][0][2 - i];
				cube[0][0][2 - i] = tcube[4][i][0];
			}
		}
		break;

	case 'L':

		//상하앞뒤좌우
		itself = 4;
		if (d == '+') {
			for (int i = 0; i < 3; i++) {
				cube[2][i][0] = tcube[0][i][0];
			}
			for (int i = 0; i < 3; i++) {
				cube[1][i][0] = tcube[2][i][0];
			}
			for (int i = 0; i < 3; i++) {
				cube[3][2-i][2] = tcube[1][i][0];
			}
			for (int i = 0; i < 3; i++) {
				cube[0][i][0] = tcube[3][2 - i][2];
			}
		}
		else {
			for (int i = 0; i < 3; i++) {
				cube[0][i][0] = tcube[2][i][0];
			}
			for (int i = 0; i < 3; i++) {
				cube[2][i][0] = tcube[1][i][0];
			}
			for (int i = 0; i < 3; i++) {
				cube[1][i][0] = tcube[3][2 - i][2];
			}
			for (int i = 0; i < 3; i++) {
				//******************************
				cube[3][2-i][2] = tcube[0][i][0];
			}
		}
		break;
	case 'R':
		itself = 5;
		if (d == '+') {
			for (int i = 0; i < 3; i++) {
				cube[0][i][2] = tcube[2][i][2];
			}
			for (int i = 0; i < 3; i++) {
				cube[2][i][2] = tcube[1][i][2];
			}
			for (int i = 0; i < 3; i++) {
				cube[1][i][2] = tcube[3][2-i][0];
			}
			for (int i = 0; i < 3; i++) {
				cube[3][2-i][0] = tcube[0][i][2];
			}
		}
		else {
			for (int i = 0; i < 3; i++) {
				cube[2][i][2] = tcube[0][i][2];
			}
			for (int i = 0; i < 3; i++) {
				cube[1][i][2] = tcube[2][i][2];
			}
			for (int i = 0; i < 3; i++) {
				cube[3][2-i][0] = tcube[1][i][2];
			}
			for (int i = 0; i < 3; i++) {
				cube[0][i][2] = tcube[3][2 - i][0];
			}
			
		}
		break;

	}

	if (d == '+')
	{
		cube[itself][0][0] = tcube[itself][2][0];
		cube[itself][0][1] = tcube[itself][1][0];
		cube[itself][0][2] = tcube[itself][0][0];
		cube[itself][1][0] = tcube[itself][2][1];
		cube[itself][1][2] = tcube[itself][0][1];
		cube[itself][2][0] = tcube[itself][2][2];
		cube[itself][2][1] = tcube[itself][1][2];
		cube[itself][2][2] = tcube[itself][0][2];
	}
	if (d == '-') {
		cube[itself][0][0] = tcube[itself][0][2];
		cube[itself][0][1] = tcube[itself][1][2];
		cube[itself][0][2] = tcube[itself][2][2];
		cube[itself][1][0] = tcube[itself][0][1];
		cube[itself][1][2] = tcube[itself][2][1];
		cube[itself][2][0] = tcube[itself][0][0];
		cube[itself][2][1] = tcube[itself][1][0];
		cube[itself][2][2] = tcube[itself][2][0];
	}


}
int main() {

	cin >> N;
	string s;
	for (int i = 0; i < N; i++) {
		cin >> T;
		for (int j = 0; j < T; j++) {
			cin >> s;
			rotate(s[0], s[1]);
		}

		for (int k = 0; k < 3; k++) {
			for (int r = 0; r < 3; r++) {
				cout << cube[0][k][r];
			}
			cout << "\n";
		}

		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					cube[i][j][k] = temp[i][j][k];
				}
			}
		}

	}
	
	
	/*
	rotate('U', '+');
	rotate('L', '+');
	
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {

				cout << cube[i][j][k];
			}
			cout << endl;
		}
		cout << endl;
	}

	*/
}