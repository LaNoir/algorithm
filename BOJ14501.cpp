#include <iostream>
#include <vector>
using namespace std;

int n;
int dp[16];

int main() {
	int t[16];
	int p[16];
	int res = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> t[i];
		cin >> p[i];
	}

	for (int i = 0; i < n; i++) {
		if(i+t[i] <= n){
			dp[i+t[i]] = max(dp[i + t[i]], dp[i] + p[i]);
			res = max(dp[i+t[i]], res);
		}
		if(i+1 <= n){
			dp[i + 1] = max(dp[i + 1], dp[i]);
			res = max(dp[i + t[i]], res);
		}
	}

	
	cout << res;
	return 0;
}

