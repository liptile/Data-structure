//链栈头指针指向栈顶
//无头结点
//空栈相当于头指针指向空
//不存在栈满情况
//空栈状态：S = NULL
#include <iostream>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef int SElemType;
typedef struct Snode{
	SElemType data;
	struct Snode *next;
}SNode,*LinkStack;

Status InitStack(LinkStack &S);//链栈的初始化
Status StackEmpty(LinkStack S);//判断链栈是否为空
Status Push(LinkStack &S, SElemType e);//链栈的入栈
Status Pop(LinkStack &S, SElemType &e);//链栈的出栈
SElemType GetTop(LinkStack S);//取栈顶元素

int mian(){
	return 0;
}

Status InitStack(LinkStack &S)	//链栈的初始化
{
	S = NULL;
	return OK;
}
Status StackEmpty(LinkStack S)		//判断链栈是否为空
{
	if(!S) return TRUE;
	return FALSE;
}
Status Push(LinkStack &S, SElemType e)		//链栈的入栈
{
	LinkStack p = new SNode;//指针指向新结点
	p->data = e;//数据域赋值
	p->next = S;//指针域赋值
	S = p;//S指向栈顶
	return OK;
}
Status Pop(LinkStack &S, SElemType &e)		//链栈的出栈
{
	if(!S) return ERROR;
	LinkStack p = S;//辅助指针指向栈顶
	e = S->data;//保留被删元素
	S = S->next;//S下移
	delete p;//释放栈顶
	return OK;
}
SElemType GetTop(LinkStack S)		//取栈顶元素
{
	if(S) return S->data;
}
