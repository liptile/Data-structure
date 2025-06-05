//模式串匹配算法(BF算法/KMP算法)
//在主串中寻找字串
#include <iostream>
using namespace std;
typedef int Status;
typedef struct{
	char *ch;
	int length;
}SqString;

//BF算法
/* 算法思路：1.从S的每一个字符开始依次与T的字符比较
			 2.将主串的pos个字符与模式串的第一个字符比较
			   1'.若相等,继续逐个比较后续字符
			   2'.若不等,从主串的下一个字符起重新与模式串的第一个字符比较
			 3.直到主串的一个连续子串序列与模式串相等,返回子序列的第一个字符的位置	 */
int Index_BF(SqString S, SqString T){
	int i = 0, j = 0;//指针
	while(i <= S.length && j <= T.length && S.length - i >= T.length){
		if(S.ch[i] == T.ch[j]){//所指字符相同则继续比较下一队
			i ++ ; j ++ ;
		}
		else{//不同则回溯
			i = i - j + 2;//i回溯到下一个
			j = 1;//j回溯到头字符
		}
	}
	if(j > T.length) return i - T.length;//匹配成功则返回第一个字符的下标
	else return 0;//匹配失败
}

//KMP算法
//在BF算法的基础上利用以匹配的信息,让i不回溯持续递增
//j回溯的位置用next[j]指示
//next[j]指示了S.ch[i] != T.ch[j]时j回溯的位置
//next[j]用递推求出
/* next[j]求法：设next[j] = t
			1.当Pj = Pt时则next[j + 1] = next[j] + 1
            2.当Pj != Pt时则循环将t = next[t],直到t = 0或满足1为止,当t = 0时next[j+1] = 1 */
void GetNext(SqString S, int next[]){
	int j = 1, t = 0;
	next[1] = 0;//特殊标记
	while(j < S.length){
		if(t == 0||S.ch[j] == S.ch[t]){//当前字符相等可以递推出下一位next的值
			next[j + 1] = t + 1; t ++ ; j ++ ;
		}
		else t = next[t];//不想等t回溯
	}
}
//next[j]算法的缺点：当当前比较的字符不同时,j = next[j],若跳转的所有ch[j] = ch[next[j]]
//则会重复比较相同的字符,直到j = 0或ch[j]!=ch[next[j]]时,因此浪费时间
/* next[j]改进的nextval[j]算法思路：
		  1.当j = 1时nextval[j] = 0,作为特殊标记
		  2.当j > 1时：
		        1'.若Pj!=Pnext[j]则nextval[j] = next[j]
		        2'.若Pj==Pnext[j]则nextval[j] = nextval[next[j]]  */  //递推
void GetNextval(SqString S, int nextval[]){
	int  j = 1, t = 0;
	nextval[1] = 0;
	while(j < S.length){
		if(t == 0||S.ch[j] == S.ch[t]){//有next[j + 1] = next[j] + 1 = t + 1
			if(S.ch[j + 1] != S.ch[t + 1])//Pj!=Pnext[j]
				nextval[j + 1] = t + 1;//nextval[j] = next[j]
			else nextval[j + 1] = nextval[t + 1];//若Pj==Pnext[j]则nextval[j] = nextval[next[j]]
			j ++ ; t ++ ;
		}
		else t = nextval[t];//t回溯
	}
}
/* KMP算法思路：1.当字符比较不同时,寻找当前字符之前的最长前后缀
			 2.j的下一次位置为最长前后缀长度加一,i的位置不变
			 3.定义next[j]数组存放j的下一次回溯的位置   */
int Index_KMP(SqString S, SqString T, int pos){//从pos位置开始匹配子串
	int i = pos, j = 1;
	while(i <= S.length && j <= T.length && S.length - i >= T.length){
		if(j == 0||S.ch[i] == T.ch[j]){//当前字符相等则继续比较下一对字符
			i ++ ; j ++ ;
		}
		else j = next[j];//当前字符不相等则j回溯
	}
	if(j > T.length) return i - T.length;//匹配成功返回子序列第一个字符的位置
	return 0;
}
