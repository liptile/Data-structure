#include <iostream>
using namespace std;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

//����������ṹ
typedef char ElemType;
typedef struct Lnode{
	ElemType data;
	struct Lnode *next;
}LNode,*LinkList;

Status InitList_L(LinkList &L);//��ʼ������
int ListEmpty(LinkList L);//�ж������Ƿ�Ϊ��
Status DestroyList_L(LinkList &L);//���������
Status ClearList(LinkList &L);//�������
int ListLength(LinkList L);//������ĳ���
Status GetList(LinkList L, int i, ElemType &e);//��λ�����
//LNode *LocateElem_L(LinkList L, ElemType e);//��ֵ���ҷ��ص�ַ
int LocateElem_L(LinkList L, ElemType e);//��ֵ���ҷ���λ��
Status ListInsert_L(LinkList &L, int i, ElemType e);//�ڵ�i��λ�ò���Ԫ��e
Status ListDelete_L(LinkList &L, int i, ElemType &e);//ɾ����i��Ԫ��
void CreatList_H(LinkList &L, int n);//��������Ϊn������ͷ�巨��
void CreatList_R(LinkList &L, int n);//��������Ϊn������β�巨��
Status ListInsert_R(LinkList &L, int n);//������β������n����� 
void DispList(LinkList L);//�������������



int main(){
	LinkList L;
	InitList_L(L);
	cout<<"β��������(����)��";
	int l;
	cin>>l;
	cout<<"�����ַ�����(��������볤��һ��)��";
	CreatList_R(L,l);
	DispList(L);
	cout<<endl<<"����"<<ListLength(L)<<endl;
	cout<<"ͷ��������(����)��";
	cin>>l;
	cout<<"�����ַ�����(��������볤��һ��)��";
	CreatList_H(L,l);
	DispList(L);
	cout<<endl<<"����"<<ListLength(L)<<endl;
	cout<<"�������������ȣ�";
	cin>>l;
	cout<<"�����ַ�����(��������볤��һ��)��";
	ListInsert_R(L,l);
	DispList(L);
	cout<<endl<<"����"<<ListLength(L)<<endl;
	int i;
	ElemType e;
	cout<<"��������λ�ú�Ԫ��ֵ��";
	cin>>i>>e;
	ListInsert_L(L,i,e);
	DispList(L);
	cout<<endl<<"����"<<ListLength(L)<<endl;
	cout<<"����ɾ��Ԫ�ص�λ�ã�";
	cin>>i;
	ListDelete_L(L,i,e);
	cout<<"��ɾԪ�أ�"<<e<<endl;
	DispList(L);
	cout<<endl<<"����"<<ListLength(L)<<endl;
	cout<<"�������Ԫ�ص�λ�ã�";
	cin>>i;
	GetList(L,i,e);
	cout<<"����Ԫ�أ�"<<e<<endl;
	cout<<"�������Ԫ�ص�ֵ��";
	cin>>e;
	cout<<"����Ԫ��λ��"<<LocateElem_L(L,e)<<endl<<endl;
	cout<<"���������...";
	ClearList(L);
	cout<<endl<<"����"<<ListLength(L)<<endl;
	cout<<"�����Ƿ�Ϊ�գ�";
	if(ListEmpty(L)) cout<<"��";
	else cout<<"��";
	cout<<"����������..."; //��һ������ѭ����ԭ��δ֪��������������δ�Ľ�... 
	DestroyList_L(L);
	cout<<endl<<"����"<<ListLength(L)<<endl;
	cout<<"�����Ƿ�Ϊ�գ�";
	if(ListEmpty(L)) cout<<"��";
	else cout<<"��";
		
	
	
	return 0;
};


Status InitList_L(LinkList &L)		//��ʼ������
{
	L = new LNode;//L = (LNode*)malloc(sizeof(LNode));Ϊͷ������ռ� 
	L->next = NULL;//ͷ���ָ����NULL
	return OK;
}
int ListEmpty(LinkList L)		//�ж������Ƿ�Ϊ��
{
	if(L->next == NULL) return 1;//if(L->next)ͷ���ָ��Ϊ����Ϊ�ձ�
	return 0;
}
Status DestroyList_L(LinkList &L)		//���������
{
	LNode *p;//����ָ��
	p = L;//p��ͷ��㿪ʼ 
	while(p){//p��Ϊ��˵������Դ��ڣ�����ɾ��
		p = p->next;//pָ�����
		delete L;//�ͷ�L
		L = p;//L����
	}
//	while(p){
//		p = L;
//		L = L->next;
//		delete p;
//	}�Ż�
	//if(L == p == NULL) return OK;//ȷ��������
	if(p == NULL) return OK;
}
Status ClearList(LinkList &L)		//�������
{
	if(L->next == NULL) return ERROR;
	LinkList p,q;//��������ָ��
	p = L->next;
//	q = p;//��ʼ��p��q
	while(p){
		q = p->next;//q������
		delete p;//�ͷ�p
		p = q;//p������
	}
	//if(p == q == NULL) return OK;
	if(p == NULL) return OK;
}
int ListLength(LinkList L)		//������ĳ���
{
	LNode *p = L->next;// ����ָ��
	int i = 0;//��ʼ��������
	while(p){
		p = p->next;//p������
		i++;//��������һ
	}
	return i;
}
Status GetList(LinkList L, int i, ElemType &e)		//��λ����ҷ���ֵ
{
	LNode *p = L;//����ָ��
	int j = 0;//��ʼ��������
	while(p&&j < i){//����λ��Ϸ�
		p = p->next;//pָ�����
		j++;//��������һ
	}
	if(!p||i < 0/*j > i*/) return ERROR;//���λ���Ƿ�Ϸ�
	e = p->data;//����Ԫ��ֵ
	return OK;
}
//LNode* LocateElem_L(LinkList L, ElemType e)		//��ֵ���ҷ��ص�ַ
//{
//	LNode *p = L;//����ָ��
//	while(p&&p->data != e){//δ��������δ�ҵ�ֵ
//		p = p->next;
//	}
//	return p;//��pΪ�շ��ؿգ���p�ǿշ��ص�ַ	
//}
int LocateElem_L(LinkList L, ElemType e)		//��ֵ���ҷ���λ��
{
	LNode *p = L;//����ָ��
	int j = 0;//��ʼ��������
	while(p&&p->data != e){//ѭ������
		p = p->next;//p������
		j++;//��������һ
	}
	if(!p) return 0;//δ�ҵ�ֵ����0
	return j;//�ҵ�����1
}
Status ListInsert_L(LinkList &L,int i, ElemType e)		//�ڵ�i��λ�ò���Ԫ��e
{
	LNode *p = L;
	LNode *q;//����ָ��
	int j = 0;//��ʼ��������
	for(int j = 0;j < i - 1;j++){
		p = p->next;//pָ��i-1λ��
	}
//	while(p&&j < i - 1){
//		p = p->next;
//		j++;
//	}�Ż�
	if(i < 1||!p) return ERROR;//iλ�ò��Ϸ�
	q = new LNode;//�����½��
	q->data = e;//�洢ֵ
	q->next = p->next;
	p->next = q;//����½��
	return OK;
}
Status ListDelete_L(LinkList &L,int i, ElemType &e)		//ɾ����i��Ԫ��
{
	LNode *p = L;
	LNode *q;//����ָ��
	for(int j = 0;j < i - 1;j++){
		p = p->next;//pָ��i-1λ��
	}
//	while(p->next&&j < i - 1){
//		p = p->next;
//	}�Ż�
	if(i < 1||!p->next) return ERROR;//���iλ���Ƿ�Ϸ�
	q = p->next;//qָ��iλ��
	e = q->data;//���汻ɾԪ�ص�ֵ
	p->next = q->next;
	delete q;//ɾ��i���
	return OK;
}
void CreatList_H(LinkList &L,int n)		//��������Ϊn������ͷ�巨��
{
	LNode *p = NULL;//����ָ��
	L->next = NULL;
	int j = 0;//��ʼ��������
	for(j = 0;j < n;j++){
		p = new LNode;//�����½��
		cin>>p->data;//��������
		p->next = L->next;
		L->next = p;//�����½��
	}
	p->next = NULL;
}
void CreatList_R(LinkList &L,int n)		//��������Ϊn������β�巨��
{
	LNode *R = L;//βָ��
	LNode *p;//����ָ��
	L->next = NULL;  
	int j = 0;//��ʼ��������
	for(j = 0;j < n;j++){
		p = new LNode;//�����½��
		cin>>p->data;//��������
		p->next = R->next;
		R->next = p;//�����½��
		R = p;//����Rָ��β���
	}
	R->next = NULL;
}
Status ListInsert_R(LinkList &L, int n){		//������β����n����� 
	LNode *R = L;//βָ�� 
	LNode *p = NULL; 
	int j = 0;//��ʼ��������
	while(R->next){
		R = R->next;//βָ����Ƶ�β��� 
	}
	for(j = 0;j < n;j++){
		p = new LNode;//�����½�� 
		p->next = NULL;//ָ�����ÿ� 
		cin>>p->data;//�������� 
		R->next = p;//�����½�� 
		R = p;//βָ����Ƶ�β��� 
	}
	return OK; 
}
void DispList(LinkList L){
	LNode *p = L->next;//����ָ��
	while(p){
		cout<<p->data<<" ";//�������
		p = p->next;//ָ�����
	}
}
