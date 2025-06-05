//顺序栈,特点后进先出
//栈空状态：S.top == S.base
//栈满状态：S.top - S.base == S.stacksize
//S.base为栈底指针始终不移动,为分配空间地址的起点
//S.top为栈顶指针入栈上移,出栈下移
//函数的数据通常用栈来存储(后调用的先返回)
#include <iostream>
#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1
#define MAXSIZE 100
typedef int Status;
using namespace std;

//顺序栈类型定义
typedef int SElemType;
typedef struct{
	SElemType *base;//栈底指针
	SElemType *top;//栈顶指针
	int stacksize;//栈最大容量
}SqStack;

Status InitStack(SqStack &S);//栈初始化
Status EmptyStack(SqStack S);//判断栈是否尾空
int LengthStack(SqStack S);//求栈长度
Status ClearStack(SqStack &S);//清空栈
Status DestoryStack(SqStack &S);//销毁栈
Status Push(SqStack &S, SElemType e);//入栈
Status Pop(SqStack &S, SElemType &e);//出栈


int main(){
	return 0;
}



Status InitStack(SqStack &S)		//栈初始化
{
	S.base = new SElemType[MAXSIZE];//分配内存空间
	if(S.base == NULL) return ERROR;//分配失败报错
	S.top = S.base;//栈置空
	S.stacksize = MAXSIZE;
	return OK;
}
Status EmptyStack(SqStack S)		//判断栈是否为空
{
	if(S.top == S.base) return TRUE;
	return FALSE;
}
int LengthStack(SqStack S)		//求栈长度
{
	return S.top - S.base;
}
Status ClearStack(SqStack &S)		//清空栈
{
	if(S.base) S.top = S.base;
	return OK;
}
Status DestoryStack(SqStack &S)		//销毁栈
{
	if(S.base){
		delete S.base;//销毁空间
		S.stacksize = 0;//容量置为0
		S.top = S.base = NULL;//指针置空
	}
	return OK;
}
Status Push(SqStack &S, SElemType e)		//入栈
{
	if((!S.base)||(S.top - S.base == S.stacksize)) return ERROR;//栈不存在或者栈满
	*S.top++ = e;//栈顶指针先赋值再上移
	return OK;
}
Status Pop(SqStack &S, SElemType &e)		//出栈
{
	if(!S.base||S.top == S.base) return ERROR;//栈不存在或栈空
	e = *(-- S.top);//先下移再保留被删元素
	return OK;
}
