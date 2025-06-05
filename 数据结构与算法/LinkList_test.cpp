#include <iostream>
using namespace std;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

//定义链表结点结构
typedef char ElemType;
typedef struct Lnode{
	ElemType data;
	struct Lnode *next;
}LNode,*LinkList;

Status InitList_L(LinkList &L);//初始化链表
int ListEmpty(LinkList L);//判断链表是否为空
Status DestroyList_L(LinkList &L);//链表的销毁
Status ClearList(LinkList &L);//清空链表
int ListLength(LinkList L);//求链表的长度
Status GetList(LinkList L, int i, ElemType &e);//按位序查找
//LNode *LocateElem_L(LinkList L, ElemType e);//按值查找返回地址
int LocateElem_L(LinkList L, ElemType e);//按值查找返回位序
Status ListInsert_L(LinkList &L, int i, ElemType e);//在第i个位置插入元素e
Status ListDelete_L(LinkList &L, int i, ElemType &e);//删除第i个元素
void CreatList_H(LinkList &L, int n);//建立长度为n的链表（头插法）
void CreatList_R(LinkList &L, int n);//建立长度为n的链表（尾插法）
Status ListInsert_R(LinkList &L, int n);//在链表尾部接入n个结点 
void DispList(LinkList L);//遍历并输出链表



int main(){
	LinkList L;
	InitList_L(L);
	cout<<"尾插链表长度(正序)：";
	int l;
	cin>>l;
	cout<<"输入字符数据(个数务必与长度一致)：";
	CreatList_R(L,l);
	DispList(L);
	cout<<endl<<"表长："<<ListLength(L)<<endl;
	cout<<"头插链表长度(倒序)：";
	cin>>l;
	cout<<"输入字符数据(个数务必与长度一致)：";
	CreatList_H(L,l);
	DispList(L);
	cout<<endl<<"表长："<<ListLength(L)<<endl;
	cout<<"输入接入的链表长度：";
	cin>>l;
	cout<<"输入字符数据(个数务必与长度一致)：";
	ListInsert_R(L,l);
	DispList(L);
	cout<<endl<<"表长："<<ListLength(L)<<endl;
	int i;
	ElemType e;
	cout<<"输入插入的位置和元素值：";
	cin>>i>>e;
	ListInsert_L(L,i,e);
	DispList(L);
	cout<<endl<<"表长："<<ListLength(L)<<endl;
	cout<<"输入删除元素的位置：";
	cin>>i;
	ListDelete_L(L,i,e);
	cout<<"被删元素："<<e<<endl;
	DispList(L);
	cout<<endl<<"表长："<<ListLength(L)<<endl;
	cout<<"输入查找元素的位置：";
	cin>>i;
	GetList(L,i,e);
	cout<<"查找元素："<<e<<endl;
	cout<<"输入查找元素的值：";
	cin>>e;
	cout<<"查找元素位序："<<LocateElem_L(L,e)<<endl<<endl;
	cout<<"清空链表中...";
	ClearList(L);
	cout<<endl<<"表长："<<ListLength(L)<<endl;
	cout<<"链表是否为空：";
	if(ListEmpty(L)) cout<<"是";
	else cout<<"否";
	cout<<"销毁链表中..."; //这一步无限循环，原因未知！！！！！！！未改进... 
	DestroyList_L(L);
	cout<<endl<<"表长："<<ListLength(L)<<endl;
	cout<<"链表是否为空：";
	if(ListEmpty(L)) cout<<"是";
	else cout<<"否";
		
	
	
	return 0;
};


Status InitList_L(LinkList &L)		//初始化链表
{
	L = new LNode;//L = (LNode*)malloc(sizeof(LNode));为头结点分配空间 
	L->next = NULL;//头结点指针置NULL
	return OK;
}
int ListEmpty(LinkList L)		//判断链表是否为空
{
	if(L->next == NULL) return 1;//if(L->next)头结点指针为空则为空表
	return 0;
}
Status DestroyList_L(LinkList &L)		//链表的销毁
{
	LNode *p;//辅助指针
	p = L;//p从头结点开始 
	while(p){//p不为空说明结点仍存在，继续删除
		p = p->next;//p指针后移
		delete L;//释放L
		L = p;//L后移
	}
//	while(p){
//		p = L;
//		L = L->next;
//		delete p;
//	}优化
	//if(L == p == NULL) return OK;//确认已销毁
	if(p == NULL) return OK;
}
Status ClearList(LinkList &L)		//清空链表
{
	if(L->next == NULL) return ERROR;
	LinkList p,q;//建立辅助指针
	p = L->next;
//	q = p;//初始化p和q
	while(p){
		q = p->next;//q往后移
		delete p;//释放p
		p = q;//p往后移
	}
	//if(p == q == NULL) return OK;
	if(p == NULL) return OK;
}
int ListLength(LinkList L)		//求链表的长度
{
	LNode *p = L->next;// 辅助指针
	int i = 0;//初始化计数器
	while(p){
		p = p->next;//p往后移
		i++;//计数器加一
	}
	return i;
}
Status GetList(LinkList L, int i, ElemType &e)		//按位序查找返回值
{
	LNode *p = L;//辅助指针
	int j = 0;//初始化计数器
	while(p&&j < i){//查找位序合法
		p = p->next;//p指针后移
		j++;//计数器加一
	}
	if(!p||i < 0/*j > i*/) return ERROR;//检查位置是否合法
	e = p->data;//返回元素值
	return OK;
}
//LNode* LocateElem_L(LinkList L, ElemType e)		//按值查找返回地址
//{
//	LNode *p = L;//辅助指针
//	while(p&&p->data != e){//未查找完且未找到值
//		p = p->next;
//	}
//	return p;//若p为空返回空，若p非空返回地址	
//}
int LocateElem_L(LinkList L, ElemType e)		//按值查找返回位序
{
	LNode *p = L;//辅助指针
	int j = 0;//初始化计数器
	while(p&&p->data != e){//循环条件
		p = p->next;//p往后移
		j++;//计数器加一
	}
	if(!p) return 0;//未找到值返回0
	return j;//找到返回1
}
Status ListInsert_L(LinkList &L,int i, ElemType e)		//在第i个位置插入元素e
{
	LNode *p = L;
	LNode *q;//辅助指针
	int j = 0;//初始化计数器
	for(int j = 0;j < i - 1;j++){
		p = p->next;//p指向i-1位置
	}
//	while(p&&j < i - 1){
//		p = p->next;
//		j++;
//	}优化
	if(i < 1||!p) return ERROR;//i位置不合法
	q = new LNode;//建立新结点
	q->data = e;//存储值
	q->next = p->next;
	p->next = q;//添加新结点
	return OK;
}
Status ListDelete_L(LinkList &L,int i, ElemType &e)		//删除第i个元素
{
	LNode *p = L;
	LNode *q;//辅助指针
	for(int j = 0;j < i - 1;j++){
		p = p->next;//p指向i-1位置
	}
//	while(p->next&&j < i - 1){
//		p = p->next;
//	}优化
	if(i < 1||!p->next) return ERROR;//检查i位置是否合法
	q = p->next;//q指向i位置
	e = q->data;//保存被删元素的值
	p->next = q->next;
	delete q;//删除i结点
	return OK;
}
void CreatList_H(LinkList &L,int n)		//建立长度为n的链表（头插法）
{
	LNode *p = NULL;//辅助指针
	L->next = NULL;
	int j = 0;//初始化计数器
	for(j = 0;j < n;j++){
		p = new LNode;//建立新结点
		cin>>p->data;//读入数据
		p->next = L->next;
		L->next = p;//插入新结点
	}
	p->next = NULL;
}
void CreatList_R(LinkList &L,int n)		//建立长度为n的链表（尾插法）
{
	LNode *R = L;//尾指针
	LNode *p;//辅助指针
	L->next = NULL;  
	int j = 0;//初始化计数器
	for(j = 0;j < n;j++){
		p = new LNode;//建立新结点
		cin>>p->data;//读入数据
		p->next = R->next;
		R->next = p;//插入新结点
		R = p;//调整R指向尾结点
	}
	R->next = NULL;
}
Status ListInsert_R(LinkList &L, int n){		//在链表尾接入n个结点 
	LNode *R = L;//尾指针 
	LNode *p = NULL; 
	int j = 0;//初始化计数器
	while(R->next){
		R = R->next;//尾指针后移到尾结点 
	}
	for(j = 0;j < n;j++){
		p = new LNode;//建立新结点 
		p->next = NULL;//指针域置空 
		cin>>p->data;//读入数据 
		R->next = p;//接入新结点 
		R = p;//尾指针后移到尾结点 
	}
	return OK; 
}
void DispList(LinkList L){
	LNode *p = L->next;//辅助指针
	while(p){
		cout<<p->data<<" ";//输出数据
		p = p->next;//指针后移
	}
}
