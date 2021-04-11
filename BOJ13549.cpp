#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int N, M;
int res = 100001;

bool check[100001] = {false,};



int main() {

	cin >> N >> M;

	deque<pair<int,int>> q;

	q.push_back({ N,0 });

	while (!q.empty()) {
		pair<int,int> cur = q.front();
		check[cur.first] = true;
		if (cur.first == M) {
			cout << cur.second;
			return 0;
		}

		q.pop_front();

		if(cur.first*2<100002 && check[cur.first*2] == false)
		q.push_front({cur.first * 2, cur.second});

		int next;
		next = cur.first + 1;

		if (next<0 || next>100000){}
			

		else if (check[next] == true){}
			

		else {
		q.push_back({ next, cur.second+1 });
		}
		next = cur.first - 1;


		if (next < 0 || next>100000) {}


		else if (check[next] == true) {}


		else {
			q.push_back({ next, cur.second + 1 });
		}

		
	}
	return 0;
}