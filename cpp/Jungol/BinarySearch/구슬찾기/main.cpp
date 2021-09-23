/*
최적화 문제를 이진검색과 결정함수를 이용하여 해결한다.
parametaric search
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define LM 305

int M, N;
int A[LM];
int low, high, ans;

bool check(int mid) {
    int gcnt = 1; // 그룹 수;
    int sum = 0;
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
    return gcnt <= M;
}

void input() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", A + i);
        if (low < A[i]) low = A[i];
        high += A[i];
    }
}

void process() {
    while (low <= high) {
        int mid = (low + high) / 2;
        if (check(mid)) {
            ans = mid;
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
}

void output() {
    printf("%d\n", ans);
    int cnt = 0, sum = 0, cm = M;
    for (int i = 0; i <= N; ++i) {
        //그룹의 합이 제한을 넘는 경우이거나 그룹 수 제한에 걸린 경우
        if (sum + A[i] > ans || N - i < cm) {
            printf("%d ", cnt);
            cnt = sum = 0;
            cm--;
        }
        sum += A[i];
        cnt++;
    }
}


int main() {
    input();
    process();
    output();
    return 0;
}