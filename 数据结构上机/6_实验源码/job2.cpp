#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

const int N = 110;
int cmp_count, swap_count; //记录比较，交换次数

// 函数声明
void Generate(const string &filename, int N);
void Readfile(const string &filename, int a[], int N);
int Partition(int a[], int l, int r);
void Qsort(int a[], int l, int r);
void PrintArray(int a[], int N);
bool cmp(int a, int b) {return a >= b;};

int main() {
	srand(time(0));
	const string filename = "intfile.dat";
	int a[N + 1];

	long long comparisons, swaps;
	high_resolution_clock::time_point start, end;
	duration<double> time_span;
	// 生成随机数并保存到文件
	Generate(filename, N);
	// 从文件读取整数
	Readfile(filename, a, N);
	
	cout << "初始数组： " << endl;
	PrintArray(a, N);
	
	//随机排列
	cout << "随机排列 ：" << endl;
	// 测量排序时间
	start = high_resolution_clock::now();
	Qsort(a, 0, N - 1);
	end = high_resolution_clock::now();
	time_span = duration_cast<duration<double>>(end - start);
	cout << endl;

	cout << "快速排序：" << endl;
	PrintArray(a, N);
	cout << "比较次数: " << cmp_count << endl;
	cout << "交换次数: " << swap_count << endl;
	cout << "排序时间: " << time_span.count() << endl;
	cout << endl;

	//正序排列
	cmp_count = swap_count = 0;
	cout << "正序排列：" << endl;
	start = high_resolution_clock::now();
	Qsort(a, 0, N - 1);
	end = high_resolution_clock::now();
	time_span = duration_cast<duration<double>>(end - start);
	
	cout << "快速排序：" << endl;
	PrintArray(a, N);
	cout << "比较次数: " << cmp_count << endl;
	cout << "交换次数: " << swap_count << endl;
	cout << "排序时间: " << time_span.count() << endl;
	cout << endl;
	
	//逆序排列
	cmp_count = swap_count = 0;
	sort(a + 1, a + N, cmp);
	cout << "逆序排列：" << endl;
	start = high_resolution_clock::now();
	Qsort(a, 0, N - 1);
	end = high_resolution_clock::now();
	time_span = duration_cast<duration<double>>(end - start);
	
	cout << "快速排序：" << endl;
	PrintArray(a, N);
	cout << "比较次数: " << cmp_count << endl;
	cout << "交换次数: " << swap_count << endl;
	cout << "排序时间: " << time_span.count() << endl;
	
	
	return 0;
}

// 生成随机整数并保存到文件
void Generate(const string &filename, int N) {
	ofstream file(filename);
	for (int i = 1; i <= N; ++i) {
		int number = rand() % 1001; // 生成0到1000之间的随机数
		file << number << "\n";
	}
}

// 从文件读取整数
void Readfile(const string &filename, int arr[], int N) {
	ifstream file(filename);
	for (int i = 1; i <= N; ++i) {
		file >> arr[i];
	}
}

int Partition(int a[], int l, int r) {
	int pivot = a[l]; // 选择左边界作为枢轴元素
	int i = l, j = r;
	
	while (i < j) {
		while (i < j && a[j] >= pivot) {
			--j;
			cmp_count ++;
		}
		if (i < j) {
			a[i] = a[j];
			swap_count ++;
			++i;
		}
		while (i < j && a[i] < pivot) {
			++i;
			cmp_count ++;
		}
		if (i < j) {
			a[j] = a[i];
			swap_count ++;
			--j;
		}
	}
	a[i] = pivot;
	return i;
}


void Qsort(int a[], int l, int r){
	if(l >= r) return ;
	int pivotloc = Partition(a, l, r);
	Qsort(a, l, pivotloc - 1); //左子序列快排
	Qsort(a, pivotloc + 1, r); //右子序列快排
}




// 打印数组
void PrintArray(int a[], int N) {
	for (int i = 1; i < N - 1; ++i) {
		cout << a[i] << ' ';
	}
	cout << endl;
}


