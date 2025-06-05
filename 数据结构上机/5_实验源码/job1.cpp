/*
  编译执行write_to_datafile.cpp 可以生成整数随机序列文件datafile
 */
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstring>
#define OK 1
#define ERROR 2
using namespace std;

const int M = 1e2; //序列最大长度
const int N = 1e3; //数据最大行数

//元素类型
typedef int ElemType;
typedef int KeyType;
//顺序存储
typedef struct{
	ElemType *elem;
	int length;
}SSTable;

SSTable ST;
char buf[N];
vector<char*> Data(M);

int Sq_Search(SSTable ST, KeyType key); //有序表上的顺序查找(单增)
int Binary_Search1(SSTable ST, KeyType key); //非递归折半查找/二分查找(单增)
int Binary_Search2(SSTable ST, int l, int r, KeyType key); //递归折半查找

int ChartoInt(string str, int a[]);//将字符串按空格拆分存入数组中

int main(){
	FILE* file = fopen("./datafile.txt", "r");
	int row = 0, n, x, m;
	while(fgets(buf, sizeof(buf), file) != NULL){
		cout << ++ row << " : " << buf << endl;
		Data[row] = strdup(buf);
		//cout << "data row : " << Data[row] << endl;
		//cout << "row : " << row << endl;
	}
	
	ST.elem = new ElemType[M];

	while(1){
		cout << "请输入要查找的行号："; cin >> n;
		//cout << "data n : " << Data[n] << endl;
		char* d = Data[n]; 
		cout << d << endl;
		
		ST.length = ChartoInt(d, ST.elem); //列号
		
		cout << "请输入要查找的数字："; cin >> x;
		
		//sort(ST.elem + 1, ST.elem + 1 + ST.length);
		
		int pos = Sq_Search(ST, x);
		cout << "顺序查找位置 : " << pos << endl;
		
		pos = Binary_Search2(ST, 1, ST.length, x);
		cout << "递归折半查找位置 : " << pos << endl;
		
		pos = Binary_Search1(ST, x);
		cout << "非递归折半查找位置 : " << pos << endl;
	}
	
	fclose(file);

	return 0;
}

int ChartoInt(string str, int a[]){
	istringstream iss(str);
	int n, i = 0;
	// 使用 istringstream 和提取运算符逐个提取数字
	while (iss >> n) a[++ i] = n;
	return i;
}

int Sq_Search(SSTable ST, KeyType key){
	int i = ST.length;
	ST.elem[0] = key;
	while(key < ST.elem[i]) i -- ;
	if(key == ST.elem[i])
		return i;
	return 0;
}

int Binary_Search1(SSTable ST, KeyType key){
	int low = 1, high = ST.length;
	while(low <= high){
		int mid = low + (high - low) >> 1; 
		if(ST.elem[mid] == key) return mid;
		if(ST.elem[mid] < key)
			low = mid + 1;
		else high = mid - 1;
	}
	return 0;
}

int Binary_Search2(SSTable ST, int l, int r, KeyType key){
	if(l >= r){
		if(ST.elem[l] == key) return l;
		else return 0;
	}
	int mid = l + r >> 1;
	if(ST.elem[mid] < key)
		return Binary_Search2(ST, mid + 1, r, key);
	else return Binary_Search2(ST, l, mid - 1, key);
}

//踩坑 ： 1.文件读取的是string，还要转化为int数组
//2.注意序列有序，无序则排序


