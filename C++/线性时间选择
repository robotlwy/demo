#include <iostream>


using namespace std;

int random(int low, int hight) {
//    srand((unsigned) time(NULL)); 有这个 random生成的随机数可能一直不变
    return low + (rand() % (hight - low + 1));
}

template<class type>
int partition(type arr[], int low, int hight) {
    type pivot = arr[low];
    while (low < hight) {
        while (low < hight && pivot <= arr[hight])
            hight--;
        arr[low] = arr[hight];
        while (low < hight && pivot >= arr[low])
            low++;
        arr[hight] = arr[low];
    }
    arr[low] = pivot;
    return low;
}

template<class type>
int randomizedPartition(type arr[], int low, int hight) {
    int i = random(low, hight);
    swap(arr[i], arr[low]);
    return partition(arr, low, hight);
}

template<class type>
//在一个无序的数组中，输出第k小的数
//自己写的
type randomizedSelect(type arr[], int low, int hight, int k) {
    if (low == hight)
        return arr[low];
    int pivot = randomizedPartition(arr, low, hight);
    if (pivot == k - 1)
        return arr[pivot];
    else if (pivot > k)
        return randomizedSelect(arr, low, pivot - 1, k);
    else if (pivot < k)
        return randomizedSelect(arr, pivot + 1, hight, k);
}

template<class type>
//书上的
type randomizedSelect2(type arr[], int low, int hight, int k) {
    if (low == hight)
        return arr[low];
    int pivot = randomizedPartition(arr, low, hight);
    int index = pivot - low + 1;
    if (k <= index) {
        return randomizedSelect2(arr, low, pivot, k);
    } else {
        return randomizedSelect2(arr, pivot + 1, hight, k - pivot);
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 116, 17};
    int k = sizeof(arr) / sizeof(arr[0]);
    cout << randomizedSelect2(arr, 0, k - 1, k) << endl;
}
