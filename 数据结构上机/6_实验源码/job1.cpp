#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 110;
void Generate(const string &filename, int N);
void Readfile(const string &filename, int arr[], int N);
void BubbleSort(int a[], int n); // 冒泡排序
void SelectSort(int a[], int n); //选择排序
void InsertSort(int a[], int n); //插入排序

int main(){
	srand(time(0));
	const string filename = "intfile.dat";
	int a[N];
	//int a_copy[N];
	// 生成随机数并保存到文件
	Generate(filename, N);
	// 从文件读取整数
	Readfile(filename, a, N);
	
	cout << "初始数组： " << endl;
	for(int i = 1; i < N; i ++ )
		cout << a[i] << ' ';
	cout << endl;
	
	int choice = 0;
	cout << "1 : 冒泡排序" << endl;
	cout << "2 : 选择排序" << endl;
	cout << "3 : 插入排序" << endl;
	cin >> choice;
	switch (choice) {
	case 1:
		BubbleSort(a, N - 1);
		cout << "冒泡排序 : " << endl;
		for(int i = 1; i < N; i ++ )
			cout << a[i] << ' ';
		cout << endl;
		break;
	case 2:
		SelectSort(a, N - 1);
		cout << "选择排序 : " << endl;
		for(int i = 1; i < N; i ++ )
			cout << a[i] << ' ';
		cout << endl;
		break;
	default:
		InsertSort(a, N - 1);
		cout << "插入排序 : " << endl;
		for(int i = 1; i < N; i ++ )
			cout << a[i] << ' ';
		cout << endl;
		break;
	}

	
	
	
	return 0;
}


// 生成随机整数并保存到文件
void Generate(const string &filename, int N) {
	ofstream file(filename);
	for (int i = 1; i < N; ++i) {
		int number = rand() % 1000 + 1;
		file << number << "\n";
	}
}

// 从文件读取整数
void Readfile(const string &filename, int arr[], int N) {
	ifstream file(filename);
	for (int i = 1; i < N; ++i) {
		file >> arr[i];
	}
}


void BubbleSort(int a[], int n){
	for(int i = 1, swapTag = 1; i < n && swapTag; ++ i){
		swapTag = 0;
		for(int j = 1; j < n - i + 1; ++ j)
			if(a[j] > a[j + 1]){
				swap(a[j], a[j + 1]);
				swapTag = 1;
		}
	}
}

void SelectSort(int a[], int n){
	for(int i = 1; i < n; ++ i){
		int min_index = i; //最小元素下标
		for(int k = i + 1; k <= n; k ++ )
			if(a[k] < a[min_index])
				min_index = k;
		if(min_index != i) swap(a[i], a[min_index]);
	}
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

