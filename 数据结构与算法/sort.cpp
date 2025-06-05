#include <iostream>
//#include "Sqlist.cpp"
using namespace std;

#define MAXSIZE 10000
typedef int Keytype;
typedef char InfoType;
typedef struct{
	Keytype key;
	InfoType otherinfo;
}RedType;

void BubbleSort(int a[], int n); // 冒泡排序
//快排
int Partition(int a[], int l, int r);
void Qsort(int a[], int l, int r);
//堆排序
void HeapSort(int a[], int n);
void HeapAdjust(int a[], int s, int n);

void SelectSort(int a[], int n); //选择排序
void InsertSort(int a[], int n); //插入排序
void ShellInsert(int a[], int n, int dk);// 希尔排序 dk为增量

int main(){
	
	return 0;
}

void BubbleSort(int a[], int n){
	for(int i = 1, swapTag = 1; i < n && swapTag; ++ i){
		swapTag = 0;
		for(int j = 1; j < n - i + 1; ++ j)
			if(a[j] > a[j + 1]){
				a[0] = a[j];
				a[j] = a[j + 1];
				a[j + 1] = a[0];
				swapTag = 1;
		}
	}
}

void SelectSort(int a[], int n){
	for(int i = 1; i < n; ++ i){
		int min_index = 1; //最小元素下标
		for(int k = i + 1; k <= n; k ++ )
			if(a[k] < a[min_index])
				min_index = k;
		if(min_index != i) swap(a[i], a[min_index]);
	}
}
//快排
int Partition(int a[], int l, int r){
	a[0] = a[l]; 
	int pivot = a[0], i = l, j = r;
	while(i < j){
		while(i < j && a[j] >= pivot) j -- ; //从后往前扫描
		a[i] = a[j];
		while(i < j && a[i] < pivot) i ++ ; //从前往后
		a[j] = a[i];
	}
	a[i] = a[0];
	return i;
}
void Qsort(int a[], int l, int r){
	if(l >= r) return ;
	int pivotloc = Partition(a, l, r);
	Qsort(a, l, pivotloc - 1); //左子序列快排
	Qsort(a, pivotloc + 1, r); //右子序列快排
}


void InsertSort(int a[], int n){
	for(int i = 2; i <= n; i ++ ){
		if(a[i] < a[i - 1]){ //递增序列，小于说明需要插入
			a[0] = a[i]; //将哨兵设置为将要插入的元素
			//a[i] = a[i - 1];
			int j = 0;
			for(j = i - 1; a[0] < a[j]; j -- )
				a[j + 1] = a[j];
			a[j + 1] = a[0];
		}
	}
}
void ShellInsert(int a[], int n, int dk){
	for(int i = dk + 1; i <= n; i ++ )
		if(a[i] < a[i - 1]){
			a[0] = a[i];
			int j = 0;
			for(j = i - dk; j && a[0] < a[j]; j -= dk)
				a[j + dk] = a[j];
			a[j + dk] = a[0];
	}
}


void HeapSort(int a[], int n){
	for(int i = n / 2; i > 0; i -- ){
		//swap(a[i], a[1]); //交换堆顶与最后一个元素
		HeapAdjust(a, 1, i - 1); //调整
	}
//	for(int i = n; i > 1; -- i){
//		swap(a[1], a[i]);
//		HeapAdjust(a, 1, i - 1);
//	}
}
void HeapAdjust(int a[], int s, int m){
	for(int j = 2 * s; j <= m; j*= 2){
		if(j < m && a[j] > a[j + 1]) ++ j; //j为较小孩子的下标
		if(a[s] < a[j]) break;
		swap(a[s], a[j]); 
		s = j;
	}
}
