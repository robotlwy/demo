#include <iostream>
#include <time.h>
#include <queue>
#include <string.h>
#include <cmath>

using namespace std;
//length 数组的长度
//left,low 所选数组的最左边
//right,hight 所选数组的最右边

//生成随机数
//生成的范围为[low，hight]
int random(int low, int hight) {
    srand((unsigned) time(NULL));
    return low + (rand() % (hight - low + 1));
}

// 冒泡排序
template<class type>
void maoPao1(type arr[], int length) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

//  冒泡排序优化
template<class type>
void maoPao2(type arr[], int length) {
    bool flag = true;
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - 1 - i; j++) {
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
void xuanZe(type arr[], int length) {
    int minIndex;
    for (int i = 0; i < length - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < length; j++)
            if (arr[minIndex] > arr[j])
                minIndex = j;
        swap(arr[minIndex], arr[i]);
    }
}

// 插入排序 假设第一个有序,然后将后面的插入到前面有序的数中
template<class type>
void chaRu(type arr[], int length) {
    for (int i = 1; i < length; i++) {
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

//归并排序 将一组无序的数组，不断分组，直到一组只有一个数，然后合并再排序，最后就是一个有序的数组
template<class type>
void merge(type a[], type b[], int left, int middle, int right) {
    int l = left, k = left, m = middle + 1;
    while (l <= middle && m <= right) {
        if (a[l] < a[m])
            b[k++] = a[l++];
        else
            b[k++] = b[m++];
    }
    while (l <= middle)
        b[k++] = a[l++];
    while (m <= right)
        b[k++] = a[m++];
    for (int i = left; i <= right; i++)
        a[i] = b[i];
}

template<class type>
void mergeSort(type a[], type b[], int left, int right) {
    if (left >= right) {
        return;
    }
    int middle = (left + right) / 2;
    mergeSort(a, b, left, middle);
    mergeSort(a, b, middle + 1, right);
    merge(a, b, left, middle, right);
}

//快速排序
template<class type>
//让小于arr[low]的在其左边，大于arr[low]的在其右边 最后arr[low]在的位置是正确的位置
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
//不断调用上面的函数 最后就可以有序
void quickSort(type arr[], int low, int hight) {
    if (low < hight) {
        type pivot = partition(arr, low, hight);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, hight);
    }
}

//随机快速排序
template<class type>
int randomizedPartition(type arr[], int low, int hight) {
    int i = random(low, hight);
    swap(arr[i], arr[low]);
    return partition(arr, low, hight);
}

template<class type>
void randomizedQuickSort(type arr[], int low, int hight) {
    if (low < hight) {
        type pivot = randomizedPartition(arr, low, hight);
        randomizedQuickSort(arr, low, pivot - 1);
        randomizedQuickSort(arr, pivot + 1, hight);;
    }
}

// 希尔排序（交换式）
template<class type>
void shellSort1(type arr[], int length) {
    for (int gap = length / 2; gap > 0; gap /= 2)//分组
        for (int i = gap; i < length; i++)
            for (int j = i - gap; j >= 0; j -= gap)
                if (arr[j] > arr[j + gap])
                    swap(arr[j], arr[j + gap]);
}

// 希尔排序（位移式）
void shellSort2(int arr[], int length) {
    for (int gap = length / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < length; i++) {//这里的i时对应的第二个元素
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

//堆排序
//大顶堆：arr[i]>=arr[2i+1]&&arr[i]>=arr[2i+2]
//小顶堆：arr[i]<=arr[2i+1]&&arr[i]<=arr[2i+2]
template<class type>
void heapAdjust(type arr[], int start, int end) {
    int dad = start;
    int son = 2 * start + 1;
    while (son <= end) {
        if (son < end && arr[son] < arr[son + 1])
            son++;
        if (arr[dad] > arr[son])
            return;
        else {
            swap(arr[dad], arr[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

template<class type>
void headSort(type arr[], int length) {
    for (int i = length / 2 - 1; i >= 0; i--)
        heapAdjust(arr, i, length - 1);
    for (int i = length - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapAdjust(arr, 0, i - 1);
    }
}



//基数排序
//自然数

//计算arr中最大数的位数
int maxBit(int arr[], int length) {
    int max = arr[0];
    for (int i = 1; i < length; i++) {
        if (max < arr[i])
            max = arr[i];
    }
    int t = 0;
    while (max > 0) {
        max /= 10;
        t++;
    }
    return t;
}

//自己写的
void radixSort(int arr[], int length) {
    queue<int> count[10];
    int num = 1, number;
    int maxArrLength = maxBit(arr, length);
    for (int i = 0; i < maxArrLength; i++) {
        for (int j = 0; j < length; j++) {
            number = arr[j] / num;
            count[number % 10].push(arr[j]);//将倒数i+1位数的同中放入数
        }
        num *= 10;
        int index = 0;
        for (int j = 0; j < 10; j++) {
            while (!count[j].empty()) {
                arr[index++] = count[j].front();
                count[j].pop();
            }
        }
    }
}

//别人的
void radixSort2(int arr[], int length) {
    int maxLength = maxBit(arr, length);
    int newArr[length], count[10];
    int power;
    for (int i = 0; i < maxLength; i++) {
        power = pow(10, i);
        memset(count, 0, sizeof(count));//初始化为0
        for (int j = 0; j < length; j++) {
            count[(arr[j] / power) % 10]++;
        }
        for (int j = 1; j < 10; j++) {
            count[j] += count[j - 1];//方便在newArr中加入相应位置的arr 记录了当前位数的位置
        }
        for (int j = length - 1; j >= 0; j--) {
            //从小到大排序 j从length-1开始因为后面的前一位比较大 当当前位数的数一样时，看前一位 将前一位大的放到相应桶中较大的位置 而count大的前一位大
            newArr[--count[(arr[j] / power) % 10]] = arr[j];
        }
        for (int j = 0; j < length; j++) {
            arr[j] = newArr[j];
        }
    }
}

//折半插入排序
template<class type>
void binInsertSort(type arr[], int length) {
    int left, right, middle,temp;
    for (int i = 1; i < length; i++) {
        if (arr[i] < arr[i - 1]) {
            left = 0;
            right = i - 1;
            temp=arr[i];
            while (left <= right) {
                middle = (left + right) / 2;
                if (arr[middle] > arr[i]) {
                    right = middle - 1;
                } else {
                    left = middle + 1;
                }
            }//left为有序数组中大于arr[i]的最小的一个
            for (int j = i; j > left; j--) {
                arr[j]=arr[j-1];
            }
            arr[left]=temp;
        }
    }
}
//桶排序

//计数排序
//只能给自然数排序
template<class type>
void printArr(type arr[], int length) {
    for (int i = 0; i < length; i++) {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

int main() {
    int arr[11] = {2, 1, 5, 23, 46, 567, 23, 45, 75, 23, 568};
    binInsertSort(arr, 11);
    printArr(arr, 11);
}
