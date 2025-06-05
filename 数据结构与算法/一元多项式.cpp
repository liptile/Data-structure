//一元多项式相加实现
//pa(x) = 10+5x-4x^2+3x^3+2x^4
//pb(x) = -3+8x+4x^2-5x^4+7x^5-2x^6
#include <iostream>
#define OK 1
#define ERROR 0
using namespace std;
typedef int Status;


//顺序表实现一元稀疏多项式
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
    int a,b;//表La,Lb的最大指数a,b
    int n;//相加循环的次数（为a,b中的最小值）
    InitList_Sq(La,10);
    InitList_Sq(Lb,10);
    InitList_Sq(Lc,10);//为La,Lb,Lc分配长10的连续空间,无元素
    cout<<"输入La最大指数:";
    cin>>a;
    cout<<"输入Lb最大指数:";
    cin>>b;
    cout<<"向La中输入各项系数:";
    InsList_Sq(La,++a);
    cout<<"向Lb中输入各项系数:";
    InsList_Sq(Lb,++b);//向La,Lb中插入元素
    cout<<"La：";
    DispList_Sq(La);
    cout<<endl<<"La表长："<<LengthList_Sq(La)<<endl;
    cout<<endl<<"Lb：";
    DispList_Sq(Lb);
    cout<<endl<<"Lb表长："<<LengthList_Sq(Lb)<<endl;
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
    cout<<endl<<"Lc：";
	DispList_Sq(Lc);
	cout<<endl<<"Lc表长："<<LengthList_Sq(Lc)<<endl; 
    return 0;
}

Status InitList_Sq(SqList &L, int s){     //初始化顺序表
    L.data = new ElemType[s];//data指向s长度的连续空间
    if(L.data == NULL) return ERROR;//分配空间失败
    L.size = s;//空间长度
    L.length = 0;//元素长度
    return OK;//成功
}
Status InsList_Sq(SqList &L, int n){     //插入元素
    if(L.data == NULL) return ERROR;
    for(int i = 0; i < n; i++){
         cin>>L.data[i];//插入n个元素,元素类型为data所指的ElemType（int）型
    }
    L.length = n;
    return OK;
}
void DispList_Sq(SqList L){
    for(int i = 0; i < L.length; i++){
        cout<<L.data[i]<<" ";//遍历并输出表 
    }
}
int LengthList_Sq(SqList L){
	return L.length;//返回表长 
}
