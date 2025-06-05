#include <iostream>
using namespace std;
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1
#define OVWRFLOW -2
typedef int Status;

//˳�����ṹ����
typedef char ElemType;//������
typedef struct sqlist{
	ElemType *elem;//������ָ��
	int size;//�ռ䳤��
	int length;//��
}SqList;//˳���ṹ

Status InitList(SqList &L, int s);//��ʼ��˳���
int ListLength(const SqList &L);//�����Ա���
Status LocateList(const SqList &L, const ElemType &e);//��ֵ���ҷ���λ��
Status GetElem(const SqList &L, int i, ElemType &e);//��λ�����
Status InsList(SqList &L, int i, const ElemType e);//�ڵ�i��λ�ò���e
Status DelList(SqList &L, int i, ElemType &e);//ɾ����i��Ԫ�ز�������e
Status DestroyList(SqList &L);//����˳���
Status ClearList(SqList &L);//���˳���
bool EmptyList(const SqList &L);//���˳����Ƿ�Ϊ��
void DispList(const SqList &L);//�����������

int main(){
	SqList L;
	int s,i = 1;
	char c;
	ElemType e;
	cout<<"�����ռ䳤��:";
	cin>>s; 
	InitList(L,s);
	cout<<"�����ַ�����:";
	while(1){
		scanf(" %c",&c);
		if(c == '&') break;
		InsList(L,i++,c);
	}
	DispList(L); 
	cout<<endl<<"����"<<ListLength(L)<<endl;
	cout<<"����ɾ��Ԫ��λ�ã�";
	cin>>i;
	while(!DelList(L,i,e)){
		cout<<"����ɾ��Ԫ��λ�ã�";
		cin>>i;
	}
	cout<<"��ɾԪ�أ�"<<e<<endl;
	DispList(L);
	cout<<endl<<"����"<<ListLength(L); 
	cout<<endl<<"�����ȡ��Ԫ��ֵ��";
	cin>>e;
	while(!LocateList(L,e)){
		cout<<"�����ȡ��Ԫ��ֵ��";
		cin>>e;	
	}
	cout<<"����λ�ã�"<<LocateList(L,e);
	cout<<endl<<"�����ȡ��Ԫ��λ�ã�";
	cin>>i;
	while(!GetElem(L,i,e)){
		cout<<"�����ȡ��Ԫ��λ�ã�";
		cin>>i;
	}
	cout<<"����ֵ��"<<e<<endl;
	cout<<endl<<"���˳�����..."<<endl;
	ClearList(L);
	cout<<"����"<<ListLength(L)<<endl;
	cout<<"���Ƿ�Ϊ�գ�";
	if(EmptyList(L)) cout<<"��"<<endl;
	else cout<<"��";
	cout<<"����˳�����..."<<endl;
	DestroyList(L);
	cout<<"��ռ䳤�ȣ�"<<L.size; 
	

	
	return 0;
}

Status InitList(SqList &L, int s)		//��ʼ��˳���
{
	L.elem = new ElemType[s];//Ϊ�����ռ�
	if(L.elem == 0) return ERROR;
	L.size = s;//�ռ䳤��Ϊs
	L.length = 0;//����ʼ��Ϊ0
	return OK;
}
int ListLength(const SqList &L)		//�����Ա���
{
	return L.length;//ֱ�ӷ��ر�
}
int LocateList(const SqList &L, const ElemType &e)		//��ֵ���ҷ���λ��
{
	if(L.length == 0) return ERROR;//��Ϊ0���ò���
	for(int i = 0;i < L.length;i++){
		if(L.elem[i] == e) return i + 1;//���μ���
	}
	return ERROR;//δ�ҵ�
}
Status GetElem(const SqList &L, int i, ElemType &e)		//��λ�����
{
	if(i < 1||i > L.length) return ERROR;//�ж�iλ���Ƿ�Ϸ�
	e = L.elem[i - 1];//����iλ�õ�����
	return OK;
}
Status InsList(SqList &L, int i, const ElemType e)		//�ڵ�i��λ�ò���e
{
	if(i < 1||i > L.length + 1) return ERROR;//�ж�iλ���Ƿ�Ϸ�
	if(L.length == L.size){//�������������� 
		ElemType *temp = new ElemType[2*L.size];//�ռ䳤������ 
		for(int j = 0;j <= L.length - 1;j++){
			temp[j] = L.elem[j];//���θ�ֵ 
		}
		delete L.elem;//�ͷ�ԭ�ռ� 
		L.elem = temp;//ָ���¿ռ� 
		L.size = 2*L.size;//�ռ䳤������ 
	}
	for(int j = L.length - 1;j >= i - 1;j--){
		L.elem[j + 1] = L.elem[j];//�ӱ�β��λ��i��Ԫ�����κ����ڳ�λ��i
	}
	L.elem[i - 1] = e;//��e����λ��i
	L.length++;//����һ
	return OK;
}
Status DelList(SqList &L, int i, ElemType &e)		//ɾ����i��Ԫ�ز�������e
{
	if(i < 1||i > L.length) return ERROR;//�ж�λ��i�Ƿ�Ϸ�
	e = L.elem[i - 1];//����ɾԪ�ش�����e
	for(int j = i;j <= L.length - 1;j++){
		L.elem[j - 1] = L.elem[j];//��i+1����βλ�õ�Ԫ������ǰ��
	}
	L.length--;//����һ
	return OK;
}
Status DestroyList(SqList &L)		//����˳���
{
	if(L.elem == 0) return ERROR;//�жϱ��Ƿ����
	delete L.elem;//�ͷſռ�
	L.size = 0;//�ռ䳤����Ϊ0
	L.length = 0;//����Ϊ0
	return OK;	
}
Status ClearList(SqList &L)		//���˳���
{
	if(L.length == 0) return ERROR;//�жϱ��Ƿ�Ϊ��
	L.length = 0;//����Ϊ0
	return OK;
}
bool EmptyList(const SqList &L)		//���˳����Ƿ�Ϊ��
{
	if(L.length == 0) return true;//��Ϊ0��Ϊ��
	return false;
}
void DispList(const SqList &L)		//�����������
{
	for(int i = 0;i < L.length;i++){
		cout<<L.elem[i]<<" ";
	}
}

