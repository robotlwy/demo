#include <iostream>
using namespace std;

struct index{
    int i,j;
} result;
template <class type>
//当i（j）越界时，说明不存在比x小的元素（大于x的元素）
index binarySearchchange(type arr[],int left,int right,type x){
    int mid;
    if (left<=right){
        mid=(left+right)/2;
        if(x==arr[mid]){
            result.i=result.j=mid;
            return result;
        }else if(x>arr[mid]){
            return binarySearchchange(arr,mid+1,right,x);
        }else if(x<arr[mid]){
            return binarySearchchange(arr,left,mid-1,x);
        }
    }
    result.i=right;
    result.j=left;
    return result;
}
int main() {
    int arr[]={1,3,4,5,6,7,8,9};
    int length=sizeof (arr)/sizeof(arr[0]);
    int x=2;//搜索元素
    index re=binarySearchchange(arr,0,length-1,x);
    if(re.i==re.j)
        cout<<x<<"在数组的位置为："<<re.i<<endl;
    else{
        if(re.i==-1)
            cout<<"元素x:"<<x<<"不在数组中，数组中不存在小于x的元素，数组中大于"<<x<<"的最小元素位置为："<<re.j<<"，值为："<<arr[re.j]<<"。"<<endl;
        else if(re.j==length)
            cout<<"元素x:"<<x<<"不在数组中，数组中小于x的最大元素位置为："<<re.i<<"，值为："<<arr[re.i]<<"，数组中不存在大于x的元素。"<<endl;
        else
            cout<<"元素x:"<<x<<"不在数组中，数组中小于x的最大元素位置为："<<re.i<<"，值为："<<arr[re.i]<<"，数组中大于x的最小元素位置为："<<re.j<<"，值为："<<arr[re.j]<<"。"<<endl;
    }
}
