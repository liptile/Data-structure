#include <iostream>

#define OK 1
#define ERROR 2

using namespace std;

//顺序表
typedef int KeyType;
typedef char OtherInfoType;
//元素类型
typedef struct{
	KeyType key;
	OtherInfoType info;
}ElemType;
//顺序存储
typedef struct{
	ElemType *elem;
	int length;
}SSTable;


int Seq_Search(SSTable ST, KeyType key); //无序表上的顺序查找
int Sq_Search(SSTable ST, KeyType key); //有序表上的顺序查找(单增)
int Binary_Search(SSTable ST, KeyType key); //折半查找/二分查找(单增)
//分块查找

int main(){
	
	return 0;
}

int Seq_Search(SSTable ST, KeyType key){
	int i = ST.length;
	ST.elem[0].key = key; //监视哨
	while(ST.elem[i].key != key) i -- ;
	return i;
}

int Sq_Search(SSTable ST, KeyType key){
	int i = ST.length;
	ST.elem[0].key = key; //监视哨
	while(ST.elem[i].key > key) i -- ;
	if(ST.elem[i].key == key) return i;
	return 0;
}

int Binary_Search(SSTable ST, KeyType key){
	int low = 1, high = ST.length; //定义查找区间
	while(low <= high){
		int mid = low + (high - low) >> 1;
		if(ST.elem[mid].key == key) return mid; //找到返回
		if(ST.elem[mid].key < key) low = mid + 1; //后半区间查找
		else high = mid - 1; //前半区间查找
	}
	return 0;
}

