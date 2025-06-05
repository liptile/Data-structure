//һԪ����ʽ���ʵ��
//pa(x) = 10+5x-4x^2+3x^3+2x^4
//pb(x) = -3+8x+4x^2-5x^4+7x^5-2x^6
#include <iostream>
#define OK 1
#define ERROR 0
using namespace std;
typedef int Status;


//˳���ʵ��һԪϡ�����ʽ
typedef int ElemType;
typedef struct Lnode{
    ElemType *data;
    int size;
    int length;
}SqList;

Status InitList_Sq(SqList &L, int s);
Status InsList_Sq(SqList &L, int n);
void DispList_Sq(SqList L);
int LengthList_Sq(SqList L);

int main(){
    SqList La,Lb,Lc;
    int a,b;//��La,Lb�����ָ��a,b
    int n;//���ѭ���Ĵ�����Ϊa,b�е���Сֵ��
    InitList_Sq(La,10);
    InitList_Sq(Lb,10);
    InitList_Sq(Lc,10);//ΪLa,Lb,Lc���䳤10�������ռ�,��Ԫ��
    cout<<"����La���ָ��:";
    cin>>a;
    cout<<"����Lb���ָ��:";
    cin>>b;
    cout<<"��La���������ϵ��:";
    InsList_Sq(La,++a);
    cout<<"��Lb���������ϵ��:";
    InsList_Sq(Lb,++b);//��La,Lb�в���Ԫ��
    cout<<"La��";
    DispList_Sq(La);
    cout<<endl<<"La����"<<LengthList_Sq(La)<<endl;
    cout<<endl<<"Lb��";
    DispList_Sq(Lb);
    cout<<endl<<"Lb����"<<LengthList_Sq(Lb)<<endl;
    n = a<b? a:b;
    for(int i = 0; i < n; i++){
        Lc.data[i] = La.data[i] + Lb.data[i];
    }
    if(a > b){
        for(int i = b; i < a; i++){
            Lc.data[i] = La.data[i];
        }
        Lc.length = a;
    }
    else{
        for(int i = a; i < b; i++){
            Lc.data[i] = Lb.data[i];
        }
		Lc.length = b; 
    }
    cout<<endl<<"Lc��";
	DispList_Sq(Lc);
	cout<<endl<<"Lc����"<<LengthList_Sq(Lc)<<endl; 
    return 0;
}

Status InitList_Sq(SqList &L, int s){     //��ʼ��˳���
    L.data = new ElemType[s];//dataָ��s���ȵ������ռ�
    if(L.data == NULL) return ERROR;//����ռ�ʧ��
    L.size = s;//�ռ䳤��
    L.length = 0;//Ԫ�س���
    return OK;//�ɹ�
}
Status InsList_Sq(SqList &L, int n){     //����Ԫ��
    if(L.data == NULL) return ERROR;
    for(int i = 0; i < n; i++){
         cin>>L.data[i];//����n��Ԫ��,Ԫ������Ϊdata��ָ��ElemType��int����
    }
    L.length = n;
    return OK;
}
void DispList_Sq(SqList L){
    for(int i = 0; i < L.length; i++){
        cout<<L.data[i]<<" ";//����������� 
    }
}
int LengthList_Sq(SqList L){
	return L.length;//���ر� 
}
