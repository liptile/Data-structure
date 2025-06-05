//下标从都零开始
//顺序串(字符串)
//以字符数组为存储空间,串尾为'/0'
//任何顺序存储结构都有定长存储结构和变长存储结构
#include <iostream>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 255
typedef int Status;
using namespace std;
//定长存储结构
//typedef struct{
//	char ch[MAXSIZE + 1];//定长数组最后一位存储'\0'
//	int length;//记录元素个数
//}SqString;
//变长存储结构
typedef struct{
	char *ch;//指向字符数组的指针
	int length;//记录元数个数
}SqString;
SqString S;
//S.ch = new char[MAXSIZE + 1];
//当length == MAXSIZE时数组已满,可以扩容
/*  char *temp = new char[MAXSIZE*2];
	for(int i = 0; i <= S.length + 1; i ++ ){
	    temp[i] = S.ch[i];
   }
	delete S.ch;
    S.ch = temp;		*/
Status StrInit(SqString &S);//初始化串
Status StrAssin(SqString &S, char *ch);//将ch字符串赋值于串S
int StrLength(SqString S);//取串长度
int StrCompare(SqString S1, SqString S2);//串比较
Status Concat(SqString &S, SqString S1, SqString S2);//串链接
Status GetSubString(SqString &S, SqString S1, int pos, int len);//求S1中pos位置长len的子串
Status ClearString(SqString &S);//清空串
int Index_BF(SqString S, SqString T, int pos);//模式串暴力匹配
int Index_KMP(SqString S, SqString T, int pos);//模式串kmp算法
int Index_PriKMP(SqString S, SqString T, int pos);//改良kmp算法

int main(){
	
	SqString S; StrInit(S);
	SqString T; StrInit(T);
	SqString Q; StrInit(Q);
	SqString P; StrInit(P);
	//T.ch = "jifsdlf";
	char ch1[8] = {'j','f','s','e','g','s','e'};
	char ch2[8] = {'j','f','d','e','g','s','e'};
	char ch3[8] = {'g','s'};
	char ch4[25] = {'a','b','c','a','a','b','b','a','b','c','a','b','a','a','c','b','a','c','b','a'};
	char ch5[40] = {'a','b','c','a','a','b','b','a','c','a','b','a','a','b','c','a','a','b','b','a','b','c','a','b','a','a','c','b','a','c','b','a'};
	
	StrAssin(S, ch5);
	cout << S.ch << ' ' << S.length << endl;
	
	StrAssin(T, ch4);
	cout << T.ch << ' ' << T.length << endl;
//	
//	cout << StrLength(S) << endl;
//	
//	if(StrCompare(S, T) == 0) cout << '=' << endl;
//	else if(StrCompare(S, T) == 1) cout << '<' << endl;
//	else cout << '>' << endl;
//	
//	Concat(Q, S, T);
//	cout << Q.ch << ' ' << Q.length << endl;
//	
//	GetSubString(P, S, 2, 5);
//	cout << P.ch << ' ' << P.length << endl;
	
	cout << Index_PriKMP(S, T, 0) << endl;
	return 0;
}

Status StrInit(SqString &S){
	S.ch = NULL;
	S.length = 0;
	return OK;
}

Status StrAssin(SqString &S, char *ch)		//将ch字符串赋值于串S
{
	if(S.ch) delete S.ch;//释放串空间
	S.length = 0;//清空串长度
	int len = 0;//记录串长度
	while(ch[len]) len ++;//ch[i]不为空时长度加一
	if(!len) return ERROR;//ch为空串

	S.ch = new char[len + 1];//分配连续数组空间
	for(int i = len; i >= 0; i --){
		S.ch[i] = ch[i];//循环赋值
	}
	S.length = len;//串长度赋值
	return OK;
}

int StrLength(SqString S)		//取串长度
{
	return S.length;
}

int StrCompare(SqString S1, SqString S2)		//串比较
{
	for(int i = 0; i < S1.length && i < S2.length; i ++ ){
		if(S1.ch[i] != S2.ch[i]) 
			return S1.ch[i] - S2.ch[i];
	}
	return S1.length - S2.length;
}

Status Concat(SqString &S, SqString S1, SqString S2)	//串链接,将S1与S2链接存入S
{
	if(S.ch){//将串S置空
		delete S.ch; S.ch = NULL; S.length = 0;
	}
	S.ch = new char[S2.length + S1.length + 1];//分配新空间
	if(!S.ch) return ERROR;//分配失败
	S.length = S1.length + S2.length;//长度赋值
	
	for(int i = 0; i <= S1.length + S2.length; ++ i)
		if(i <= S1.length - 1) S.ch[i] = S1.ch[i];
		else S.ch[i] = S2.ch[i - S1.length];
	return OK;
}

Status GetSubString(SqString &S, SqString S1, int pos, int len)	//求S1中pos位置长len的子串
{
	if(pos < 0||pos >= S1.length||len < 0||len > S1.length - pos) return ERROR;//位置不合法
	if(S.ch){//将串S置空
		delete S.ch; S.ch = NULL; S.length = 0;
	}
	if(!len){//字串长度为0
		S.ch = NULL; S.length = 0; return OK;
	}
	else{
		S.ch = new char[len + 1];//分配空间
		int i = pos, j = 0;
		while(i < pos + len){//从pos开始赋值
			S.ch[j] = S1.ch[i]; i ++ ; j ++ ;
		}
		S.ch[j] = '\0';//最后一位为'\0'
		S.length = len;//长度赋值
		return OK;
	}
}

Status ClearString(SqString &S)		//清空串
{
	if(S.ch){
		delete S.ch; S.ch = NULL; S.length = 0;
	}
	return OK;
}

int Index_BF(SqString S, SqString T, int pos){
	if(pos < 0 || pos >= S.length) return -1;
	int i = pos, j = 0;
	while(i < S.length && j < T.length){
		if(S.ch[i] == T.ch[j]) i ++ , j ++ ;
		else i = i - j + 1, j = 0;
	}
	if(j >= T.length) return i - j;
	return -1;
}

int Index_KMP(SqString S, SqString T, int pos){
	if(pos < 0 || pos >= S.length) return -1;
	int next[T.length];
	next[0] = -1;
	int i = 0, j = -1;
	while(i < T.length){
		if(j == -1 || T.ch[i] == T.ch[j]) i ++ , j ++ , next[i] = j;
		else j = next[j];
	}
//
//	for(int i = 0; i < T.length; ++ i) cout << i << ' ' << next[i] << endl;
//	cout << endl;
	i = pos, j = 0;
	while(i < S.length && j < T.length){
		if(j == -1 || S.ch[i] == T.ch[j]) i ++ , j ++ ;
		else j = next[j];
	}
	if(j >= T.length) return i - j;
}

int Index_PriKMP(SqString S, SqString T, int pos){
	if(pos < 0 || pos >= S.length) return -1;
	int nextval[T.length];
	nextval[0] = -1;
	int i = 0, j = -1;
	while(i < T.length){
		if(j == -1 || T.ch[i] == T.ch[j]){
			i ++ , j ++ ;
			if(T.ch[i] != T.ch[j]) nextval[i] = j;
			else nextval[i] = nextval[j];
		}else j = nextval[j];
	}
//	for(int i = 0; i < T.length; ++ i) cout << i << ' ' << nextval[i] << endl;
//	cout << endl;
	
	i = pos - 1, j = -1;
	while(i < S.length && j < T.length){
		if(j == -1 || S.ch[i] == T.ch[j]) i ++ , j ++ ;
		else j = nextval[j];
	}
	if(j >= T.length) return i - j;
	return -1;
}

