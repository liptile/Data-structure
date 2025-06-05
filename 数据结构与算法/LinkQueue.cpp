//链式队列
//特点：有头结点,Q.front为头指针始终指向头结点
//链式存储结构不存在满的状态
//相当于先进先出特点的链表
#include <iostream>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXQSIZE 100
using namespace std;
typedef int Status;
typedef int QElemType;
typedef struct Qnode{
	QElemType data;//数据域
	struct Qnode *next;//指针域
}QNode, *QueuePtr;//链队列结点/指针
typedef struct{
	QueuePtr front;//队头指针
	QueuePtr rear;//队尾指针
}LinkQueue;//链队列的类型定义

Status InitQueue(LinkQueue &Q);//链队列的初始化
Status DestroyQueue(LinkQueue &Q);//销毁链队列
Status EnQueue(LinkQueue &Q, QElemType e);//将元素e入队
Status DeQueue(LinkQueue &Q, QElemType &e);//链队列出队
Status GetHead(LinkQueue Q, QElemType &e);//链队列求队头元素

int main(){
	return 0;
}

Status InitQueue(LinkQueue &Q)		//链队列的初始化
{
	Q.front = new QNode;//建立头结点
	if(Q.front == NULL) return ERROR;//分配失败
	Q.front->next = NULL;//头结点指针域置空
	Q.rear = Q.front;//头尾指针初始化
}
Status DestroyQueue(LinkQueue &Q)		//销毁链队列
{
	if(!Q.front) return OK;
	while(Q.front){//循环
		Q.rear = Q.front->next;
		delete Q.front;//指针后移
		Q.front = Q.rear;//释放空间
	}
	return OK;
}
Status EnQueue(LinkQueue &Q, QElemType e)		//将元素e入队
{
	QueuePtr p = NULL;//辅助指针
	p = new QNode;//建立新结点
	p->data = e;//数据域赋值
	p->next = NULL;//指针域置空
	Q.rear->next = p;//尾指针指向尾结点
	Q.rear = p;
	return OK;
}
Status DeQueue(LinkQueue &Q, QElemType &e)		//链队列出队
{
	if(Q.front == Q.rear) return ERROR;//链队列为空
	QueuePtr p = Q.front->next;//辅助指针
	e = p->data;//保留被删元素
	Q.front->next = p->next;
	if(Q.rear == p) Q.rear = Q.front;//只有一个元素时，特判
	delete p;//释放空间
	return OK;
}
Status GetHead(LinkQueue Q, QElemType &e)		//链队列求队头元素
{
	if(Q.front == Q.rear) return ERROR;//链队列为空
	e = Q.front->next->data;//将队头元素赋值给e
	return OK;
}
