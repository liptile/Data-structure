//循环顺序队列特点先进先出,后进后出
//队空状态：front == rear
//队满状态：rear == MAXSQSIZE
//真溢出状态：front == 0;rear == MSAXQSIZE(队列已无空间)
//假溢出状态：front != 0;rear == MAXQSIZE(队列还有空间)
//解决假上溢：将队列假想为环形,当rear/front == MAXQSIZE时将rear/front置为0
//插入或删除元素后取余：front = (front + 1)%MAXQSIZE;
//少用一个元素空间,防止队空队满时状态一样
//新队空状态：front == rear
//新队满状态：(rear + 1)%MAXQSIZE == front
#include <iostream>
#define MAXQSIZE 100
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
using namespace std;
typedef int Status;
typedef int QElemType;
typedef struct{
	QElemType *base;//指针指向连续空间
	int front;//头指针(下标)
	int rear;//尾指针(下标)
}SqQueue;

Status InitQueue(SqQueue Q);//队列的初始化
int QueueLength(SqQueue Q);//求队列长度
Status EnQueue(SqQueue &Q, QElemType e);//循环队列入队
Status DeQueue(SqQueue &Q, QElemType &e);//循环队列出队
QElemType GetHead(SqQueue Q);//取队头元素

int main(){
	return 0;
}

Status InitQueue(SqQueue Q)		//队列的初始化
{
	Q.base = new QElemType[MAXQSIZE];//分配连续空间
	if(!Q.base) exit(EOVERFLOW);
	Q.front = Q.rear = 0;//队列置空
	return OK;
}
int QueueLength(SqQueue Q)		//求队列长度
{
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;//兼顾> < = 的三种情况
}
Status EnQueue(SqQueue &Q, QElemType e)		//循环队列入队
{
	if((Q.rear + 1) % MAXQSIZE == Q.front) return ERROR;//队满
	Q.base[Q.rear] = e;///赋值
	Q.rear = (Q.rear + 1) % MAXQSIZE;//加一或跳转
	return OK;
}
Status DeQueue(SqQueue &Q, QElemType &e)		//循环队列出队
{
	if(Q.front == Q.rear) return ERROR;
	e = Q.base[Q.front];//保留被删元素
	Q.front = (Q.front + 1) % MAXQSIZE;//加一或跳转
	return OK;
}
QElemType GetHead(SqQueue Q)		//取队头元素
{
	if(Q.front != Q.rear)
	return Q.base[Q.front];
}

