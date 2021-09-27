//연속 부분의 크기가 고정되어있다. 즉, sliding window를 사용하기 적합함.
//쿠폰은 초기부터 먹었다고 가정을 해버리고 간다. 


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string>
#include <map>
using namespace std;


//naive version O(N*K)
/*
#define LM 3005
int N, d, k, c, plen;
int sushi[LM * 11];
int ans;
struct Data {
	int id, cnt;
}plate[LM];

void pop(int id) {
	int i;
	for (i = 1; i <= plen; ++i) {
		if (plate[i].id == id) break;
	}
	plate[i].cnt--;
	if (plate[i].cnt == 0) {
		plate[i] = plate[plen];
		plen--;
	}
}

void push(int id) {
	int i;
	for (i = 1; i <= plen; ++i) {
		if (plate[i].id == id) break;
	}
	if (i > plen) plate[++plen] = { id,1 };
	else plate[i].cnt++;
	if (ans < plen) ans = plen;
}

int main() {
	//freopen("input.txt", "r", stdin);
	scanf("%d%d%d%d", &N,&d,&k,&c);
	int i;
	for (i = 0; i < N; i++)
		scanf("%d", sushi + i);
	for (i = 0; i < k; i++)
		sushi[N + i] = sushi[i];
	
	plate[++plen] = { c,1 }; //쿠폰 업데이트

	for (int i = 0; i < k; ++i) {
		push(sushi[i]);
	}
	for (int i = k; i < N + k; ++i) {
		pop(sushi[i - k]);
		push(sushi[i]);
	}

	printf("%d\n", ans);
}
*/

//나이브 버전에서는 각 스시 아이디를 찾는데 O(N)이 걸린다 이를 개선해보자 "map"을 이용해보자 -> 찾는데 O(log(k))
/*#define LM 3005
int N, d, k, c, plen;
int sushi[LM * 11];
int ans;

map<int, int> entry;

void pop(int id) {
	entry[id]--;
	if (entry[id] == 0) entry.erase(id);
}

void push(int id) {
	entry[id]++;
	if (ans < entry.size()) ans = entry.size();
}

int main() {
	//freopen("input.txt", "r", stdin);
	scanf("%d%d%d%d", &N, &d, &k, &c);
	int i;
	for (i = 0; i < N; i++)
		scanf("%d", sushi + i);
	for (i = 0; i < k; i++)
		sushi[N + i] = sushi[i];

	entry[c]++; //쿠폰 업데이트

	for (int i = 0; i < k; ++i) {
		push(sushi[i]);
	}
	for (int i = k; i < N + k; ++i) {
		pop(sushi[i - k]);
		push(sushi[i]);
	}

	printf("%d\n", ans);
}
*/

/*이제는 더 개선해보자!! 검색을 O(1)로 줄이는 방법이있다?!  스시 종류 자체가 최대 3000정도밖에 안되므로,, 정수 배열 entry를 만들어 해결하자*/

#define LM 3005
int N, d, k, c, plen;
int sushi[LM * 11];
int cnt[LM], uniqueCnt = 1, ans = 1;//쿠폰때문에 1로 시작

void pop(int id) {
	cnt[id]--;
		if (cnt[id] == 0) {
			plen--;
			uniqueCnt--;
		}
}

void push(int id) {
	cnt[id]++;
	if (cnt[id] == 1)
		uniqueCnt++;
	if (ans < uniqueCnt) {
		ans = uniqueCnt;
	}
}

int main() {
	//freopen("input.txt", "r", stdin);
	scanf("%d%d%d%d", &N, &d, &k, &c);
	cnt[c]++;//쿠폰 업데이트
	int i;
	for (i = 0; i < N; i++)
		scanf("%d", sushi + i);
	for (i = 0; i < k; i++)
		sushi[N + i] = sushi[i];

	

	for (int i = 0; i < k; ++i) {
		push(sushi[i]);
	}
	for (int i = k; i < N + k; ++i) {
		pop(sushi[i - k]);
		push(sushi[i]);
	}

	printf("%d\n", ans);
}
