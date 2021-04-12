#include <iostream>

using namespace std;

//1열 점수.




int main() {

	int T;

	cin >> T;
	int c;
	float d;
	float v, f, p;
	while (T) {
		T--;
		cin >> c >> d;
		int res = 0;
		while (c) {
			c--;
			cin >> v >> f >> p;
			if (d / v <= f / p)
				res++;
		}
		cout << res << "\n";

	}

}