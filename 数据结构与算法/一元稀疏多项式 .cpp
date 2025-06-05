//一元稀疏多项式相加
//A(x) = 7+3x+9x^8+5x^17
//B(x) = 8x+22x^7-9x^8
//求C(x) = A(x)+B(x)并输出
#include <iostream>
#define OK 1
#define ERROR 0
using namespace std;
typedef int Status;


//链表类型定义
typedef struct{
	int coef;//系数
	int expn;//指数 
}ElemType;
typedef struct Lnode
{
    ElemType data;  //数据域
    struct Lnode *next;  //指针域
}LNode,*LinkList;

Status InitList_L(LinkList &L);//初始化链表
Status InsLinkList_H(LinkList &L, int n);//头插法插入n个结点
Status InsLinkList_R(LinkList &L, int n);//尾插法插入n个结点
int LengthList_L(LinkList L);//求链表长度
void DispList_L(LinkList L);//遍历并输出链表
void CreatPolyn(LinkList &L, int n);//多项式创建算法

int main(){
//    LinkList La,Lb,Lc;//头指针
//    int a,b;//记录表的长度
//    InitList_L(La);//初始化链表
//    InitList_L(Lb);
//    InitList_L(Lc);
//    cout<<"表A长度:";
//    cin>>a;
//    cout<<"表B长度:";
//    cin>>b;
//    cout<<"输入表A数据:";
//    InsLinkList_R(La,a);
//	cout<<"输入表B数据:"; 
//    InsLinkList_R(Lb,b);
//    cout<<"表A:";
//    DispList_L(La);
//    cout<<endl<<"表A长度:"<<LengthList_L(La);
//    cout<<endl<<"表B:";
//    DispList_L(Lb);
//    cout<<endl<<"表B长度:"<<LengthList_L(Lb);
	
	//多项式相加算法思路(之后补)
	//一.指针p1,p2初始化,分别指向Pa,Pb首元结点
	//二.p3指向和多项式的当前结点,初值为Pa/Pb的头结点
	//三.当指针p1和p2均为达到相应表尾时,则循环比较p1和p2所指结点对应的指数值(p1->expn与p2->expn)
	//有以下三种情况:
	/* 1.当p1->expn = p2->expn时,则将两个结点中的系数相加
		  1'若和不为0,则修改p1所指结点的系数值,同时删除p2所直结点
		  2'若和为0,则删除p1和p2所指结点
	   2.当p1->expn < p2->expn时,则应摘取p1所指结点插入到和多项式链表中
	  3.当p1->expn > p2->expn时,则应摘取p2所指结点插入到和多项式链表中 */
	//四.将非空多项式的剩余段插入到p3所指结点之后
	//五.释放Pb的头结点
	  
	

    

    return 0;
}

Status InitList_L(LinkList &L){  //初始化链表
    L = new LNode;//指针指向头结点
    if(L == NULL) return ERROR;
    L->next = NULL;//头结点指针域置空
    return OK;
}
Status InsLinkList_H(LinkList &L, int n){   //头插法插入n个结点
    if(L == NULL) return ERROR;
    LNode *p = NULL;//辅助指针
    for(int i = 0; i < n; i++){
        p = new LNode;//建立新结点
        cin>>p->data.coef;//输入数据
        cin>>p->data.expn;
        p->next = L->next;
        L->next = p;//插入新结点
    }
    return OK;
}
Status InsLinkList_R(LinkList &L, int n){     //尾插法插入n个结点
    if(L == NULL) return ERROR;
    LNode *p = NULL;//辅助指针
    LNode *R = L;//尾指针
    for(int i = 0; i < n; i++){
        p = new LNode;//建立新结点
        cin>>p->data.coef;//输入数据
        cin>>p->data.expn;
        p->next = R->next;
        R->next = p;//插入新结点
        R = p;//尾指针移向尾结点
    }
    return OK;
}
int LengthList_L(LinkList L){     //求链表长度
    LNode *p = L;//辅助指针
    int i = 0;//计数器
    while(p->next){ //p未指向尾结点
        p = p->next;//指针后移
        i++;//计数器加一
    }
    return i;
}
void DispList_L(LinkList L){    //遍历并输出链表
    LNode *p = L->next;//辅助指针
    while(p){
        cout<<p->data.coef<<","<<p->data.expn<<" ";
        p = p->next;
    }
}
void CreatPolyn(LinkList &L, int n)		//多项式创建算法
{
	LNode *p;//头指针
	LNode *s;//辅助指针
	LNode *pre;//前驱指针
	LNode *q;//后继指针
	p = new LNode;//建立头结点
	p->next = NULL;//指针域置空
	for(int i = 1; i <= n; i++){//插入n个结点并依次比较指数大小并排序
		s = new LNode;//建立新结点
		cin>>s->data.coef>>s->data.expn;//输入数据
		pre = p;//前驱指针初始化
		q = p->next;//后继指针初始化
		while(q&&q->data.expn < s->data.expn){//循链比较当前结点(后继指针结点)与新建结点的指数大小
			pre = q; q = q->next;//若当前结点比新建结点的指数小则前驱后继指针后移继续遍历
		}
		s->next = q;//若新建结点的指数更大则插入到后继指针之前
		pre->next = s;//前驱指针后移保证与后继指针相邻
		//此算法按照输入数据指数从小到大的顺序建立了一个链表
		//排序方法为边输入边排序
		//输入n个数据就要比较n次
		//采用while函数巧妙地避免了计数(后继指向空时即遍历比较完成)
	}
	
}
