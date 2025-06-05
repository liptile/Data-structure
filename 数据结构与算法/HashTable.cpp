
#include<iostream>
#define OK 1
#define ERROR 0
using namespace std;

#define ElemType int
const int N = 1e3;

/*-------------------------链地址法---------------------------*/
typedef struct HashNode{
	ElemType data;  //数据域
	HashNode* next;  //指向下一个链表元素
}HashNode;

typedef HashNode* ChainHashTable[N]; //创建链哈希数组

void Init_ChainHashTable(ChainHashTable& HT); //初始化
int Hash(ElemType x); //哈希
void Insert_ChainHashTable(ChainHashTable &HT, ElemType key); //插入
void Traverse_ChainHashTable(ChainHashTable& HT); //遍历
HashNode* Search_ChainHashTable(ChainHashTable& HT, ElemType key); //查找
bool Delete_ChainHashTable(ChainHashTable &HT, ElemType key); //删除

/*------------------------------------------------------------*/

/*-------------------------开放寻址法---------------------------*/
typedef int LinearHashTable[N]; //线性探测哈希表

void Init_LinearHashTable(LinearHashTable& HT);
int Hash(ElemType x);
void Insert_LinearHashTable(LinearHashTable &HT, ElemType key);
void Traverse_LinearHashTable(LinearHashTable& HT);
int Search_LinearHashTable(LinearHashTable& HT, ElemType key);
bool Delete_LinearHashTable(LinearHashTable &HT, ElemType key);

/*------------------------------------------------------------*/
int main(){
	return 0;
}


/*-------------------------链地址法---------------------------*/
void Init_ChainHashTable(ChainHashTable& HT){
	for (int i = 0; i < N; ++ i) //初始化为空
		HT[i] = NULL;
}

ElemType Hash(ElemType x){
	return x % N;
}

void Insert_ChainHashTable(ChainHashTable &HT, ElemType key){
	int x = Hash(key); //哈希函数求出数组的下标
	HashNode* p = new HashNode;
	p->data = key;  //将申请结点的数据域指向要插入的关键字
	p->next = HT[x]->next; //头插法
	HT[x]->next = p;
}

void Traverse_ChainHashTable(ChainHashTable& HT){
	for(int i = 0; i < N; ++ i){
		cout << i << " : ";
		HashNode* p = HT[i];
		//判断p是否为空
		while(p){
			cout << p->data << "-->";
			p = p->next; 
		}
		cout << "NULL" << endl;
	}
}

HashNode* Search_ChainHashTable(ChainHashTable& HT, ElemType key){
	int x = Hash(key);  //哈希函数求下标
	HashNode *p = HT[x];
	while (p != NULL && p->data != key) //p为空或者p的数据域与关键字相等时
		p = p->next;
	return p;
}

bool Delete_ChainHashTable(ChainHashTable &HT, ElemType key){
	HashNode *p = HT[Hash(key)];//p前驱，q后继
	HashNode *q = Search_ChainHashTable(HT, key);
	if(!q) return false; //不存在
	while(p->next->data != key) p = p->next; //指向前驱
	p->next = q->next;
	delete q;
	return true;
}

/*-------------------------开放寻址法---------------------------*/
void Init_LinearHashTable(LinearHashTable& HT){
	for(int i = 0; i < N; ++ i) HT[i] = 0;
}

int Hash(ElemType x);

void Insert_LinearHashTable(LinearHashTable &HT, ElemType key){
	int x = Hash(key);
	while(HT[x] != key && HT[x]) 
		x = (x + 1) % N;
	HT[x] = key;
}

void Traverse_LinearHashTable(LinearHashTable& HT){
	for(int i = 0; i < N; ++ i) cout << HT[i] << ' ';
	cout << endl;
}

int Search_LinearHashTable(LinearHashTable& HT, ElemType key){
	int x = Hash(key);
	while(HT[x] != key && HT[x])
		x = (x + 1) % N;
	if(HT[x]) return x;
	else return -1;
}

bool Delete_LinearHashTable(LinearHashTable &HT, ElemType key){
	int x = Hash(key);
	while(HT[x] != key && HT[x])
		x = (x + 1) % N;
	if(HT[x]) HT[x] = 0;
	return true;
}

