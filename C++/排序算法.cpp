#include <iostream>

using namespace std;

// 冒泡排序
template<class type>
void maoPao1(type arr[], type n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

//  冒泡排序优化
template<class type>
void maoPao2(type arr[], int n) {
    bool flag = true;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                flag = false;
            }
        }
        if (flag)
            break;
    }
}

// 选择排序
template<class type>
void xuanZe(type arr[], int n) {
    int minIndex;
    for (int i = 0; i < n - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < n; j++)
            if (arr[minIndex] > arr[j])
                minIndex = j;
        swap(arr[minIndex], arr[i]);
    }
}

// 插入排序 假设第一个有序,然后将后面的插入到前面有序的数中
template<class type>
void chaRu(type arr[], int n) {
    for (int i = 1; i < n; i++) {
        type insertVal = arr[i];
/*        int insertIndex = i - 1;
        while (insertIndex>=0 && arr[insertIndex] > insertVal){
            arr[insertIndex + 1]=arr[insertIndex];
            insertIndex--;
        }
        arr[insertIndex+1] = insertVal;*/
        int j = i;
        while (j-- && arr[j] > insertVal) {
            arr[j + 1] = arr[j];
        }
//  因为当要退出时会再执行一次j--,所以最后arr中要为j+1
        arr[j + 1] = insertVal;
    }
}

// 希尔排序（交换式）
template<class type>
void ShellSort(type arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2)
        for (int i = gap; i < n; i++)
            for (int j = i - gap; j >= 0; j -= gap)
                if (arr[j] > arr[j + gap])
                    swap(arr[j], arr[j + gap]);
}

// 希尔排序（位移式）
void ShellSort2(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {//这里的i时对应的第二个元素
            int j = i;
            int temp = arr[j];
            while (j - gap >= 0 && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

void BinInsertSort(int a[], int n) {
    int i, j, left, right;
    int temp;
    for (i = 1; i < n; i++) {

    }
}


int main() {
    int a[10] = {2, 3, 5, 23, 46, 567, 23, 45, 75, 23};
    chaRu(a, 10);
    for (int i = 0; i < 10; i++) {
        cout << a[i] << ' ';
    }
    cout << endl;
}
