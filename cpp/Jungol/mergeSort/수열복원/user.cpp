extern int orderCheck(int left, int right);

const int LM = (int)1e5+5;
int index[LM], trr[LM];

void mergeSort(int *arr, int low, int high) {
    // 1. base condition
    if (low >= high)
        return;

    // 2. ����(divide);
    int mid = (low + high) / 2;

    // 3. ����(conquer)
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);

    // 4. ����(merge)
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
    // �л� ��ȣ�� �迭�� �ε����̴�
    // �л� ��ȣ�� ���ʷ� ���� �迭�� �����, 
    // �л��� ���� ���� ���� �л� ��ȣ(�ε���)�� �պ������Ѵ�.

    for (int i = 0; i < arrCount; i++) {
        index[i] = i;
    }
    mergeSort(index, 0, arrCount-1);

    for (int i = 0; i < arrCount; i++) {
        dat[index[i]] = i + 1;
    }

}