#include <iostream>
#include <deque>
#include <string>
#include <vector>
using namespace std;

deque<int> one, two, three, four;
int T;

void rotate(int num, int dir) {


	switch (num)
	{
	case 1:
		if (dir == 1) {
			one.push_front(one.back());
			one.pop_back();
		}
		else {
			one.push_back(one.front());
			one.pop_front();
		}
		break;

	case 2:
		if (dir == 1) {
		two.push_front(two.back());
		two.pop_back();
		}
		else {
			two.push_back(two.front());
			two.pop_front();
		}
		break;

	case 3:
		if (dir == 1) {
			three.push_front(three.back());
			three.pop_back();
		}
		else {
			three.push_back(three.front());
			three.pop_front();
		}
		break;

	case 4:
		if (dir == 1) {
			four.push_front(four.back());
			four.pop_back();
		}
		else {
			four.push_back(four.front());
			four.pop_front();
		}
		break;
	case 0:
		return;
		break;
	}
	
}

void rotateAll(int num, int dir) {

	pair<int, int> r[5];

	for (int i = 0; i < 5; i++) {
		r[i] = { 0,0 };
	}

	int temp;

	if (num == 1) {
		r[1] = { 1,1 };
		if (one[2] != two[6]) {
			r[2] = { 1,-1 };
			if (two[2] != three[6]) {
				r[3] = { 1,1 };
				if (three[2] != four[6]) {
					r[4] = { 1,-1 };
				}
			}
		}

	}

	else if (num == 2) {
		r[2] = { 1,1 };
		if (two[6] != one[2]) {
			r[1] = { 1,-1 };
		}
		if (two[2] != three[6]) {
			r[3] = { 1,-1 };
			if (three[2] != four[6]) {
				r[4] = { 1,1 };
			}
		}
	}

	else if (num == 3) {
		r[3] = { 1,1 };
		if (three[2] != four[6]) {
			r[4] = { 1,-1 };
		}

		if (three[6] != two[2]) {
			r[2] = { 1,-1 };
			if (two[6] != one[2]) {
				r[1] = { 1,1 };
			}
		}
	}

	else {
		r[4] = { 1,1 };
		if (four[6] != three[2]) {
			r[3] = { 1,-1 };
			if (three[6] != two[2]) {
				r[2] = { 1,1 };
				if (two[6] != one[2])
					r[1] = { 1,-1 };
			}
		}
	}



	for (int i = 1; i < 5; i++) {
			if (r[i].first == 1) {
				rotate(i, dir * r[i].second);
		}
	}
}


int main() {

	string temp;
		cin >> temp;
		for (int i = 0; i < 8; i++) {
			one.push_back(temp[i]-'0');
		}
		cin >> temp;

		for (int i = 0; i < 8; i++) {
			two.push_back(temp[i]-'0');
		}
		cin >> temp;

		for (int i = 0; i < 8; i++) {
			three.push_back(temp[i]-'0');
		}
		cin >> temp;

		for (int i = 0; i < 8; i++) {
			four.push_back(temp[i]-'0');
		}

	cin >> T;

	int n, d;
	for (int i = 0; i < T; i++) {
		cin >> n >> d;
		rotateAll(n, d);
	}
	
	int res = 0;

	res += (one.front());
	res += (two.front()) * 2;
	res += (three.front()) * 4;
	res += (four.front()) * 8;

	
	cout << res;
	
}