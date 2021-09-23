extern int orderCheck(int left, int right);

const int LM = (int)1e5+5;
int index[LM], trr[LM];

void mergeSort(int *arr, int low, int high) {
    // 1. base condition
    if (low >= high)
        return;

    // 2. 분할(divide);
    int mid = (low + high) / 2;

    // 3. 정복(conquer)
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);

    // 4. 결합(merge)
    int i = low; int j = mid + 1;

    for (int k = low; k <= high; k++) {
        if (j > high)
            trr[k] = arr[i++];
        else if (i > mid)
            trr[k] = arr[j++];
        else if (orderCheck(arr[i],arr[j]))
            trr[k] = arr[i++];
        else
            trr[k] = arr[j++];
    }

    for (int k = low; k <= high; ++k) {
        arr[k] = trr[k];
    }

}

void array_restore(int arrCount, int dat[]) {
    // 학생 번호는 배열의 인덱스이다
    // 학생 번호를 차례로 담은 배열을 나들고, 
    // 학생이 가진 수에 따라 학생 번호(인덱스)를 합병정렬한다.

    for (int i = 0; i < arrCount; i++) {
        index[i] = i;
    }
    mergeSort(index, 0, arrCount-1);

    for (int i = 0; i < arrCount; i++) {
        dat[index[i]] = i + 1;
    }

}