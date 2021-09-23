////이분탑색으로 문제를 해결하는 경우는 최적화문재를 결정문제로 바꿔서 생각하는 경우이다

#include <stdio.h>
#define LM 500005


int N, Q, arr[LM];

void input() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", arr + i);
    }
}


int binarySearch(int* A, int low, int high, int target) {
    int mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (A[mid] == target)
            return mid;
        if (A[mid] > target)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

int binarySearch_recur(int* A, int low, int high, int target) {
    int mid = (low + high) / 2;
    if (low > high)
        return -1;
    if (A[mid] == target) {
        return mid;
    }

    if (A[mid] > target)
        return binarySearch_recur(A, low, mid-1, target);
    else
        return binarySearch_recur(A, mid+1, high , target);


}

void process() {
    int i, tg;
    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        scanf("%d", &tg);
        int res = binarySearch_recur(arr, 0, N - 1, tg);
        printf("%d ", res);
    }
}


int main() {
    input();
    process();
    return 0;
}