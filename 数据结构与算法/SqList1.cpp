#include <iostream>
using namespace std;
#define OK 1;
#define ERROR 0;
#define FALSE 0;
#define TRUE 1;
#define OVERFLOW -2;
#define INFEASIBLE -1;
typedef int Status;

Status InitList(SqList &L, int s);//初始化顺序表
int ListLength(const SqList &L);//求线性表长度
Status LocateList(const SqList &L, const ElemType &e);//按值查找
bool GetData(const SqList &L, int i, const ElemType &e);//按位序查找
bool InsList(SqList &L, int i, const ElemType e);//在第i个位置插入e
bool DelList(SqList &L, int i, ElemType e);//删除第i个元素并保存于e
bool DestroyList(SqList &L);//销毁顺序表
bool ClearList(SqList &L);//清空顺序表
bool EmptyList(const SqList &L);//检查顺序表是否为空
void DispList(const SqList &L);//遍历并输出表 

//定义顺序表结构
typedef struct{
	char name[8];
	int score;
}ElemType;
typedef struct{
	ElemType *data;
	int size;
	int length;
}SqList;


Status InitList(SqList &L, int s){		//初始化顺序表
	L.data = new ElemType[50];
	if(L.data == 0) return ERROR;
	L.size = s;
	L.length = 0;
	return OK; 
}
int ListLength(const SqList &L){		//求线性表长度
	if(L.data == 0) return ERROR;
	return L.length;
}
int LocateList(const SqList &L, const ElemType &e){		//按值查找
	if(L.data == 0) return ERROR;
	for(int i = 0;i < L.length;i++){
		if(L.data[i] == e) return i+1;
	}
	return FALSE;
}
int GetData(const SqList &L, int i, const ElemType &e){		//按位序查找
	if(L.data == 0) return ERROR;
	e = L.data[i-1];
	return OK;
}
Status InsList(SqList &L, int i, const ElemType e){		//在第i个位置插入e
	if(L.data == 0) return ERROR;
	if(i < 1||i > L.length + 1) return ERROR;
	if(L.length = L.size) return OVERFLOW;
//	if(L.length = L.size){
//		ElemType *temp = new ElemType[2*L.size];
//		for(int i = 0;i <= L.length-1;i++){
//			temp[i] = L.data[i];
//		}
//		delete L.data;
//		L.data = temp;
//		L.size = L.size*2;	
//	}
	for(int j = L.length-1;j >= i-1;j--){
		L.data[j+1] = L.data[j];
	}
	L.data[i-1] = e;
	L.length++;
	return OK;
}
Status DelList(SqList &L, int i, ElemType e){		//删除第i个元素并保存于e
	if(L.data == 0) return ERROR;
	if(i < 1||i > L.length) return ERROR;
	L.data[i - 1] = e;
	for(int j = i;j < L.length - 1;j++){
		L.data[j - 1] = L.data[j];
	}
	L.length--;
	return OK;
}
Ststus DestroyList(SqList &L){		//销毁顺序表
	if(L.data == 0) return ERROR;
	delete L.data;
	L.size = 0;
	L.length = 0;
	return OK;
}
bool ClearList(SqList &L){		//清空顺序表
	if(L.data == 0) return ERROR;
	L.length = 0;
	return OK;
}
bool EmptyList(const SqList &L){		//检查顺序表是否为空
	if(L.data == 0) return ERROR;
	if(L.length == 0) return TRUE;
	return FALSE;
}
void DispList(const SqList &L){		//遍历并输出表 
	for(int i = 0;i < L.length;i++){
		cout<<L.data[i]<<" ";
	}
}
