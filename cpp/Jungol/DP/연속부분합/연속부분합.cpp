//연속 부분합
//dp사용,, D[i-1]+i 혹은 새로운 부분합 A[i]의 시작점
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
using namespace std;

#define LM 100005

int A[LM];
int d[LM];
int N;
int ans;
//A배열 대신 num하나만 써도 괜찮음
int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", A + i);
		d[i] = A[i];
		if (d[i - 1] > 0) {
			d[i] = d[i - 1] + A[i];
		}
		else d[i] = A[i];
		if (d[i] > ans) ans = d[i];
	}
	printf("%d", ans);
}