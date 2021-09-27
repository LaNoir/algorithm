/*
최적화 문제를 이진검색과 결정함수를 이용하여 해결한다.
parametaric search

케이스가 크기때문에, 이진탐색으로 풀어야만 한다.
100000 * 100000
ans = long long
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define LM 100005

typedef long long LL;

int K, N;
int A[LM];
LL low, high;
LL ans;

bool check(LL mid) {
    int gcnt = 1; // 그룹 수;
    LL sum = 0;
    for (int i = 0; i < N; i++) {
        //그룹의 합이 제한을 넘는 경우
        //새로운 그룹으로 분할
        if (sum + A[i] > mid) {
            sum = 0;
            gcnt++;
        }
        sum += A[i];

    }

    //각 그룹의 합을 mid이하로 제한할때
    //그룹수가 M이하인가?
    return gcnt <= K;
}

void input() {
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; i++) {
        scanf("%d", A + i);
        if (low < A[i]) low = A[i];
        high += A[i];
    }
}

void process() {
    while (low <= high) {
        LL mid = (low + high) / 2;
        if (check(mid)) {
            ans = mid;
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
}

void output(int idx, LL sum, int ck) {
    if (idx < 0) return;
    if (sum + A[idx] > low || idx < ck) {
        output(idx - 1, A[idx], ck - 1);
        printf("%d / ", A[idx]);
    }
    else {
        output(idx - 1, sum+A[idx], ck);
        printf("%d ", A[idx]);
    }
}


int main() {
    //freopen("input.txt", "r", stdin);
    input();
    process();
    output(N-1,0,K-1);
    return 0;
}