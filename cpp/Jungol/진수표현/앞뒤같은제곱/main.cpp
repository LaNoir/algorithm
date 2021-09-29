//N을 B진수로 표현. N과 N2을 B진수로  출력해라
//진수B가 들어옴. N은 1~300까지.
//N은 회문이 아니어도 되나, N2은 아니어도 됨

#include <string>
#include <stdio.h>
using namespace std;


int B;
char N[20], P[20];
int pcnt, ncnt;

void reverse(char* s, int i, int j) {
	for (; i < j; ++i, --j) {
		char ch = s[i];
		s[i] = s[j];
		s[j] = ch;
	}
}

void dToB(int d, char*ret, int&i) {
	for (; d; i++) {
		int r = d % B;
		d = d / B;
		ret[i] = r + 48 + (r > 9)*7;
	}
	ret[i] = 0;
	reverse(ret, 0, i - 1);
}


int dToB2(int d, char* ret) {
	if (d <= 0) return 0;
	int idx = dToB2(d / B, ret);
	int r = d % B;
	ret[idx] = r + 48 + (r > 9) * 7;
	return idx + 1;
}

bool isPalindrome(char* s, int i, int j) {
	for (; i < j && s[i] == s[j]; ++i, --j);
		return i >= j;
}


int main() {
	
	scanf("%d", &B);
	for (int i = 1; i <= 300; ++i) {
		//ncnt = pcnt = 0;
		pcnt = dToB2(i * i, P);
		P[pcnt] = 0;
		//dToB(i * i,P,pcnt);
		if (isPalindrome(P, 0, pcnt - 1)) {
			//dToB(i, N, ncnt);
			ncnt = dToB2(i, N);
			N[ncnt] = 0;
			printf("%s %s\n", N, P);
		}
	}
	return 0;

}