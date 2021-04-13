#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;


int main() {
	int a, n, m;
	long long dp[31][31] = { 0, };
	
		for (int i = 1; i < 31; i++) {
			dp[1][i] = i;
		}
		for (int i = 2; i < 31; i++) {
			for (int j = i; j < 31; j++) {
				for (int k = j - 1; k >= i; k--) {
					dp[i][j] += dp[i - 1][k];
				}
			}
		}
		cin >> a;

		for (int x = 0; x < a; x++) {
			cin >> n >> m;
			cout << dp[n][m] << endl;
		}
		return 0;
}