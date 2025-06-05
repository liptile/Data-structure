/*	1.线性表的合并
	La = (7,5,3,11)  Lb = (2,6,3)
	将La与Lb对接,且无重复元素

	2.有序表的合并
	La = (1,7,8)  Lb = (2,4,6,8,10,11)
	将La与Lb对接,且仍有序 	*/
#include <iostream>
using namespace std;
typedef int Status;
typedef int ElemType;
typedef struct{
	ElemType *elem;
	int length;
	int size;
}List, SqList;
int ListLength(SqList L);
Status GetElem(SqList, int i, ElemType &e);
Status LocateElem(SqList L, ElemType e);
Status ListInsert(SqList &L, int i, ElemType e);

//线性表合并
void Union(List &La, List Lb){
	ElemType e;
	int La_len = ListLength(La);//取表a长度
	int Lb_len = ListLength(Lb);//取表b长度
	for(int i = 1; i <= Lb_len; i ++ ){
		GetElem(Lb,i,e);//取表b元素存入e
		if(!LocateElem(La,e)) ListInsert(La,++La_len,e);//检查a中有无与e相同的元素,若无则插入a(避免了元素重复)
	}
}

//用顺序表合并有序表
/* 算法思路:1.创建空表Lc
			2.依次从La或Lb中摘取较小的结点插入在Lc的最后,直到某表为空
			3.继续将另一表剩余结点插入到Lc表的后面	*/
void MergeList_Sq(SqList La, SqList Lb, SqList &Lc){
	ElemType *Pa = La.elem;
	ElemType *Pb = Lb.elem;
	ElemType *Pc = Lc.elem;//指针Pa,Pb,Pc分别指向表中第一个元素
	Lc.length = La.length + Lb.length;//新表长度为两表之和
	Lc.elem = new ElemType[Lc.length];//为新表分配一个连续空间
	ElemType *Pa_last = La.elem + La.length - 1;
	ElemType *Pb_last = Lb.elem + Lb.length - 1;//Pa,Pb的尾指针指向表中最后一个元素
	while(Pa <= Pa_last && Pb <= Pb_last){//两表都没有遍历完则继续循环
		if(*Pa < *Pb) *Pc++ = *Pa++;//依次摘取表中值较小的结点接入Lc
		*Pc++ = *Pb++;
	}
	//循环的结束条件：
	//1.Pa <= Pa_last且Pb > Pb_last  
	//2.Pb <= Pb_last且Pa > Pa_last  
	//3.Pa > Pa_last且Pb > Pb_last
	while(Pa <= Pa_last) *Pc++ = *Pb++;//Lb到表尾,将La的剩余元素接入Lc
	while(Pb <= Pb_last) *Pc++ = *Pb++;//La到表尾,将Lb的剩余元素接入Lc
}


#include <iostream>
using namespace std;
typedef int ELemType;
typedef struct Lnode{
	ElemType data;
	struct Lnode *next;
}LNode,*LinkList;

//用链表合并有序表
/* 算法思路:1.创建一个新链表Lc,用Pc指向
			2.Lc的头结点为Lb/Lc的头结点
			3.Pa,Pb分别指向La,Lb的首元结点
			4.依次比较Pa,Pb所指向结点的值,将值较小的结点接入Lc
			5.Pc指向新结点,将所指结点值较小的指针后移
			6.当Pa/Pb为空时,将剩余元素接入Lc	*/
void MergeList(LinkList &La, LinkList &Lb, LinkList &Lc){
	LinkList Pa = La->next;
	LinkList Pb = Lb->next;//La,Lb指向首元结点
	LinkList Pc = La;//将La的头结点作为Lc的头结点
	while(Pa&&Pb){//当Pa,Pb非空时继续循环
		if(Pa->data < Pb->data){//将值较小的结点接入Lc
			Pc->next = Pa; Pc = Pa; Pa = Pa->next;//接入Lc后Pc指向新结点,Pa指针后移
		}
		else{
			Pc->next = Pb; Pc = Pb; Pb = Pb->next;//接入Lc后Pc指向新结点,Pb指针后移
		}
	}
	//循环的结束条件：
	//1.Pa == NULL且Pb != NULL
	//2.Pb == NULL且Pa != NULL
	//3.Pa == Pb == NULL
	if(!Pa) Pc->next = Pb;
	else Pc->next = Pa;//优化：Pc->next = Pa? Pa:Pb;
	delete Lb;
}

