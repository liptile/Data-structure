/*
  编译执行write_to_datatxt 可以生成随机记录文件data.txt
 */
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#define OK 1
#define ERROR 2
using namespace std;
const int N = 1e3;

//记录结构
typedef struct{
	string phone;
	string name;
	string address;
}Record;
/*-------------------------链地址法---------------------------*/
typedef Record ElemType;
typedef struct HashNode{
	ElemType data;  //数据域
	HashNode* next;  //指向下一个链表元素
}HashNode;
typedef HashNode* ChainHashTable[N]; //创建链哈希数组

void Init_ChainHashTable(ChainHashTable& HT); //初始化
void Insert_ChainHashTable(ChainHashTable &HT, ElemType key); //插入
void Traverse_ChainHashTable(ChainHashTable& HT); //遍历
HashNode* Search_ChainHashTable(ChainHashTable& HT, string key); //查找

/*-------------------------开放寻址法---------------------------*/
typedef Record LinearHashTable[N]; //线性探测哈希表

void Init_LinearHashTable(LinearHashTable& HT);
void Insert_LinearHashTable(LinearHashTable &HT, ElemType key);
void Traverse_LinearHashTable(LinearHashTable& HT);
int Search_LinearHashTable(LinearHashTable& HT, string key);
/*-------------------------------------------------------------*/
void loadRecords(const string &filename, vector<Record> &records); //读取文件内容并存入记录结构体
void printRecords(vector<Record>& records); //打印所有记录
int BKDRHash(string x); //字符串哈希函数

vector<Record> records; //存储读取的记录

//1.链地址头结点存不存元素
//2.线性探测表满时死循环
//3.表要初始化
int main(){
	loadRecords("data.txt", records);
	printRecords(records); //打印所有记录
	
	ChainHashTable CHT; 
	LinearHashTable LHT; 
	string phone, name;
	int pos = 0;
	HashNode *p = NULL;
	
	while(1){
		cout << "请选择建表方法：" << endl;
		cout << "1.链地址法" << endl;
		cout << "2.开放寻址法" << endl;
		int choice;
		cin >> choice;
		switch(choice){
		case 1:
			//链地址法
			
			Init_ChainHashTable(CHT); //初始化
			
			//cout << "test : " << BKDRHash("hhhdfkkkdddssss");
			for(auto re : records)
				Insert_ChainHashTable(CHT, re); //逐个记录插入
			
			Traverse_ChainHashTable(CHT); //输出链
			while(1){
				cout << "请输入要查找的姓名：";
				cin >> name;
				p = Search_ChainHashTable(CHT, name);
				if(!p){
					cout << "Not Exist" << endl;
					continue;
				}else cout << "Succeed" << endl;
				cout << "Phone : " << p->data.phone << ", Name : " << p->data.name << ", Address : " << p->data.address << endl; 
			}
			break;
		case 2:
			//线性探测法
			Init_LinearHashTable(LHT); //初始化
			for(auto re : records)
				Insert_LinearHashTable(LHT, re); //逐个记录插入
			Traverse_LinearHashTable(LHT); //输出
			while(1){
				cout << "请输入要查找的电话：";
				cin >> phone;
				pos = Search_LinearHashTable(LHT, phone);
				if(pos == -1){
					cout << "Not Exist" << endl;
					continue;
				}else cout << "Succeed" << endl;
				cout << "Phone : " << LHT[pos].phone << ", Name : " << LHT[pos].name << ", Address : " << LHT[pos].address << endl; 
			}
		}
	}


	return 0;
}

int BKDRHash(string x){
	int seed = 131;
	int hash = 0;
	for(auto s : x)
		hash = hash * seed + s;
	return (hash & 0x7FFFFFFF) % N;
}

/*-------------------------链地址法---------------------------*/
void Init_ChainHashTable(ChainHashTable& HT){
	for (int i = 0; i < N; ++ i) //初始化为空
		HT[i] = NULL;
}

void Insert_ChainHashTable(ChainHashTable &HT, ElemType key){
	int x = BKDRHash(key.name); //哈希函数求出数组的下标
	HashNode* p = new HashNode;
	p->data = key;  //将申请结点的数据域指向要插入的关键字
	p->next = HT[x]; //头插法
	HT[x] = p;
}

void Traverse_ChainHashTable(ChainHashTable& HT){
	for(int i = 0; i < N; ++ i){
		cout << i << " : ";
		HashNode* p = HT[i];
		//判断p是否为空
		while(p){
			cout << p->data.name << "-->";
			p = p->next; 
		}
		cout << "NULL" << endl;
	}
}

HashNode* Search_ChainHashTable(ChainHashTable& HT, string key){
	int x = BKDRHash(key);  //哈希函数求下标
	HashNode *p = HT[x];
	while (p != NULL && p->data.name != key) //p为空或者p的数据域与关键字相等时
		p = p->next;
	return p;
}


/*-------------------------开放寻址法---------------------------*/
void Init_LinearHashTable(LinearHashTable& HT){
	for(int i = 0; i < N; ++ i) HT[i].phone = "NULL";
}

void Insert_LinearHashTable(LinearHashTable &HT, ElemType key){
	int x = BKDRHash(key.phone);
	while(HT[x].phone != key.phone && HT[x].phone != "NULL") 
		x = (x + 1) % N;
	HT[x] = key;
}

void Traverse_LinearHashTable(LinearHashTable& HT){
	for(int i = 0; i < N; ++ i) cout << i << " : " << HT[i].phone << endl;
}

int Search_LinearHashTable(LinearHashTable& HT, string key){
	int x = BKDRHash(key);
	//cout << "x : " << x << endl;
	int cot = 0;
	while(HT[x].phone != key && HT[x].phone != "NULL"){
		x = (x + 1) % N;
		if(x == N - 1) cot ++ ;
		if(cot == 2) break; //防止表满时死循环
	}
	if(HT[x].phone != "NULL") return x;
	else return -1;
}

bool Delete_LinearHashTable(LinearHashTable &HT, ElemType key){
	int x = BKDRHash(key.name);
	while(HT[x].phone != key.phone && HT[x].phone != "NULL")
		x = (x + 1) % N;
	if(HT[x].phone != "NULL") HT[x].phone = "NULL";
	return true;
}

//取记录
void loadRecords(const string& filename, vector<Record>& records) {
	ifstream inFile(filename);
	if (!inFile) {
		cerr << "Error opening file!" << endl;
		return;
	}
	string line;
	while (getline(inFile, line)) {
		stringstream ss(line);
		Record record;
		ss >> record.phone >> record.name;
		getline(ss, record.address);
		record.address = record.address.substr(1);
		records.push_back(record);
	}
	inFile.close();
}
//打印记录
void printRecords(vector<Record>& records) {
	for (const auto& record : records) {
		cout << "Phone: " << record.phone << ", Name: " << record.name << ", Address: " << record.address << endl;
	}
}
