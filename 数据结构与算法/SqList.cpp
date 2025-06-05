#include <iostream>
using namespace std;
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1
#define OVWRFLOW -2
typedef int Status;

//顺序表结点结构定义
typedef char ElemType;//数据域
typedef struct sqlist{
	ElemType *elem;//数据域指针
	int size;//空间长度
	int length;//表长
}SqList;//顺序表结构

Status InitList(SqList &L, int s);//初始化顺序表
int ListLength(const SqList &L);//求线性表长度
Status LocateList(const SqList &L, const ElemType &e);//按值查找返回位置
Status GetElem(const SqList &L, int i, ElemType &e);//按位序查找
Status InsList(SqList &L, int i, const ElemType e);//在第i个位置插入e
Status DelList(SqList &L, int i, ElemType &e);//删除第i个元素并保存于e
Status DestroyList(SqList &L);//销毁顺序表
Status ClearList(SqList &L);//清空顺序表
bool EmptyList(const SqList &L);//检查顺序表是否为空
void DispList(const SqList &L);//遍历并输出表


Status InitList(SqList &L, int s)		//初始化顺序表
{
	L.elem = new ElemType[s];//为表分配空间
	if(L.elem == 0) return ERROR;
	L.size = s;//空间长度为s
	L.length = 0;//表长初始化为0
	return OK;
}
int ListLength(const SqList &L)		//求线性表长度
{
	return L.length;//直接返回表长
}
int LocateList(const SqList &L, const ElemType &e)		//按值查找返回位序
{
	if(L.length == 0) return ERROR;//表长为0不用查找
	for(int i = 0;i < L.length;i++){
		if(L.elem[i] == e) return i + 1;//依次检索
	}
	return ERROR;//未找到
}
Status GetElem(const SqList &L, int i, ElemType &e)		//按位序查找
{
	if(i < 1||i > L.length) return ERROR;//判断i位置是否合法
	e = L.elem[i - 1];//存入i位置的数据
	return OK;
}
Status InsList(SqList &L, int i, const ElemType e)		//在第i个位置插入e
{
	if(i < 1||i > L.length + 1) return ERROR;//判断i位置是否合法
	if(L.length == L.size){//表已满进行扩容 
		ElemType *temp = new ElemType[2*L.size];//空间长度增倍 
		for(int j = 0;j <= L.length - 1;j++){
			temp[j] = L.elem[j];//依次赋值 
		}
		delete L.elem;//释放原空间 
		L.elem = temp;//指向新空间 
		L.size = 2*L.size;//空间长度增倍 
	}
	for(int j = L.length - 1;j >= i - 1;j--){
		L.elem[j + 1] = L.elem[j];//从表尾到位置i的元素依次后移腾出位置i
	}
	L.elem[i - 1] = e;//将e插入位置i
	L.length++;//表长加一
	return OK;
}
Status DelList(SqList &L, int i, ElemType &e)		//删除第i个元素并保存于e
{
	if(i < 1||i > L.length) return ERROR;//判断位置i是否合法
	e = L.elem[i - 1];//将被删元素储存于e
	for(int j = i;j <= L.length - 1;j++){
		L.elem[j - 1] = L.elem[j];//将i+1到表尾位置的元素依次前移
	}
	L.length--;//表长减一
	return OK;
}
Status DestroyList(SqList &L)		//销毁顺序表
{
	if(L.elem == 0) return ERROR;//判断表是否存在
	delete L.elem;//释放空间
	L.size = 0;//空间长度置为0
	L.length = 0;//表长置为0
	return OK;	
}
Status ClearList(SqList &L)		//清空顺序表
{
	if(L.length == 0) return ERROR;//判断表是否为空
	L.length = 0;//表长置为0
	return OK;
}
bool EmptyList(const SqList &L)		//检查顺序表是否为空
{
	if(L.length == 0) return true;//表长为0即为空
	return false;
}
void DispList(const SqList &L)		//遍历并输出表
{
	for(int i = 0;i < L.length;i++){
		cout<<L.elem[i]<<" ";
	}
}
