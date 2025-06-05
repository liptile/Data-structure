#include <iostream>
#include <algorithm>
#define ERROR 0
#define OK 1;
using namespace std;


typedef char TElemType;
typedef int Status;
//二叉树的顺序存储
/*
	节点i的左二子为2i, 右儿子为2i + 1
*/

#define MAX_TREE_SIZE 100
typedef TElemType SqBiTree[MAX_TREE_SIZE];


//二叉树的链式动态存储
typedef struct BiTNode {
	TElemType data;
	struct BiTNode *Lchild, *Rchild;
} BiTNode, *BiTree;

//二叉树的链式静态存储
typedef struct BiTNode1 {
	TElemType data, Lchild, Rchild;
} BiTree1[MAX_TREE_SIZE];

//二叉树扩展为三叉树
typedef struct TriTNode {
	TElemType data;
	struct TriTNode *Rchild, *Lchild, *Parent;
} TriTNode, *TriTree;

//线索二叉树
typedef enum ? PointerTag {Link = 0, Thread = 1};

typedef struct BiThrNode {
	TElemType data;
	struct BiThrNode *Rchild, *Lchild;
	PointerTag Rtag, Ltag;
} BiThrTree;

/*
	二叉树的遍历：1、先序遍历 2、中序遍历 3、后序遍历
	此三种遍历均为深度优先遍历
	用链式存储结构实现的
*/
//先序遍历
void PreOrder(BiTree root) {
	if (root != NULL) {
		cout << root->data << endl;
		PreOrder(root->Lchild);
		PreOrder(root->Rchild);
	}
}

//中序遍历
void InOrder(BiTree root) {
	if (root != NULL) {
		InOrder(root->Lchild);
		cout << root->data << endl;
		InOrder(root->Rchild);
	}
}

//后序遍历
void PostOrder(BiTree root) {
	if (root != NULL) {
		PostOrder(root->Lchild);
		PostOrder(root->Rchild);
		cout << root->data << endl;
	}
}

/*
	二叉树遍历的应用：
		1.求二叉树的高度
		2.创建二叉树
		3.由两种序列还原二叉树（求解后序）
*/
//求二叉树的高度
int Height(BiTree root) {
	if (root == NULL)
		return 0;
	return max(Height(root->Lchild), Height(root->Rchild)) + 1;
}

//创建二叉树(中序遍历)
Status CreatBiTree(BiTree &root) {
	if (root != NULL) //root不为空，则清空
		delete root, root = NULL;
	TElemType ch;
	cin >> ch;
	if (ch == '#') //结束标志符
		root = NULL, return OK;
	root = new Bitree; //root 输入
	if (root == NULL)
		return ERROR;
	root->data = ch;
	CreatBiTree(root->Lchild); //递归左右子树
	CreatBiTree(root->Rchild);
	return OK;
}

//由先序和中序求解后序
/*
	preSeq[]: 先序序列
	inSeq[]: 中序序列
	pdx: 先序序列的起始下标
	idx: 中序序列的起始下标
	len: 序列长度（对应子树的先序序列与中序序列长度相等）
*/
void PreOrd(char preSeq[], char inSeq[], int pdx, int idx, int len) {
	if (len == 0)
		return ; //空序列直接返回
	int root = preSeq[pdx]; //先序序列的第一个元素为根
	int rdx = idx;
	while (inSeq[rdx] != root)
		rdx ++ ; //找到中序序列的根的下标
	int Llen = rdx - idx, Rlen = len - Llen - 1; //求出左右子树的序列长度
	PreOrd(preSeq, inSeq, pdx + 1, idx, Llen); //递归遍历左右子树
	PreOrd(preSeq, inSeq, pdx + 1 + Llen, rdx + 1, Rlen);
	cout << root->data << endl;//访问根元素
}

//遍历二叉树的非递归算法（栈模拟中序遍历）
void InOrder(BiTree root) {
	BiTree stk[MAX_TREE_SIZE] = {0}, tt = 0;
	stk[ ++ tt] = root; //初始根节点入栈
	while (tt) { //栈非空时循环
		while (stk[tt])
			stk[ ++ tt] = root->Lchild;//所有左节点入栈
		tt -- ;//弹出空节点
		if (tt) {
			BiTree p = stk[tt -- ];//弹出最后入栈的左节点
			cout << p->data << endl;//将该节点视为根节点访问
			stk[ ++ tt] = p->Rchild;//根节点右孩子入栈
		}
	}
}

//非递归简化版
void InOrder(BiTree root) {
	BiTree stk[MAX_TREE_SIZE], tt = 0;
	BiTree p = root;
	while (tt || p) { //栈非空或p非空节点时循环
		if (p)
			stk[ ++ tt] = p, p = p->Lchild;//左节点不空则循环入栈
		else {
			p = stk[tt -- ];//左节点为空，则栈顶元素可视为根
			cout << p->data << endl;//访问根
			stk[ ++ tt] = p->Rchild;//根的右子树入栈（递归右子树）
		}
	}
}

//二叉树的层序遍历
//用队列实现
void bfs(BiTree root) {
	if (root == NULL)
		return ;
	BiTree q[MAX_TREE_SIZE], hh = 1, tt = 0;
	q[ ++ tt] = root;
	while (hh <= tt) {
		BiTree p = q[hh ++ ];
		cout << p->data << endl;
		q[ ++ tt] = p->Lchild;
		q[ ++ tt] = p->Rchild;
	}
}

//中序线索树的建立------略（不会0）
//后序线索树的建立------略


//二叉树与树的转换

//树的存储结构
/*
	1.双亲表示法：数组存双亲
	2.孩子表示法：数组+链表（链表存该节点的所有孩子）
	3.孩子兄弟表示法：一个指针指向第一个孩子，另一个指针指向下一个兄弟
*/
//双亲表示法
typedef struct {
	TElemType data;
	int parent;
} PTNode;

typedef struct {
	PTNode nodes[MAX_TREE_SIZE];
	int root, n;
} PTree;

//孩子表示法
int h[N], e[N], ne[N], idx = 1;

//孩子兄弟表示法
typedef struct CSNode {
	TElemType data;
	struct CSNode *firstchild, *nextsibling;
} *CSTNode;

//树的遍历：1.先根遍历 2.中根遍历 3.后根遍历
//对树的先根遍历等同于对转化为的二叉树的先序遍历
//森林的先根遍历等同于对转化为的二叉树的先序遍历


//哈夫曼树节点结构
typedef char **HuffmanCode;
typedef struct {
	TElemType ch;
	unsigned int weight;
	unsigned int parent, lchild, rchild;
} HTNode, *HuffmanTree;

//哈夫曼编码
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int n) {
	if (n <= 1)
		return ;
	int m = 2 * n - 1;
	HT = new HTNode[m + 1]; //从一开始共2n - 1个结点
	for (int i = 1; i <= n; ++ i) { //初始化huffmantree
		HT[i].weight = w[i];
		HT[i].ch = c[i];
		HT[i].parent = HT[i].lchild = HT[i].rchild = 0;
	}
	//构造huffmantree
	for (int i = n + 1; i <= m; ++ i) {
		////选取parent为0且weight最小的两个节点
		int s1 = 0, s2 = 0;
		for (int j = 1; j <= i - 1; j ++ ) {
			if (!s1 || !s2 && !HT[j].parent) {
				if (!s1 || HT[s1].weight > HT[j].weight)
					s1 = j;
				if (s1 != j && (!s2 || HT[s2].weight > HT[j].weight))
					s2 = j;
			}
		}
		//select(HT, i - 1, s1, s2); //选取parent为0且weight最小的两个节点
		HT[s1].parent = i;
		HT[s2].parent = i; //将两节点的父节点指定为i
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	HC = (char **)malloc((n + 1) * sizeof(char *));
	char *cd = (char *)malloc(n * sizeof(char));
	cd[n - 1] = '\0';
	for (int i = 1; i <= n; ++ i) {
		int st = n - 1;
		for (int c = i, f = HT[i].parent; f; c = f, f = HT[f].parent) {
			if (HT[f].lchild == c)
				cd[--st] = '0';
			else
				cd[--st] = '1';
		}
		HC[i] = new char[n - st];
		strcpy(HC[i], &cd[st]);
	}
	delete[] cd;
}

//哈夫曼解码
void Decoding(HuffmanTree HT, int m, char *buff) {
	int p = m;
	//assert(m > 0);
	while (*buff != '\0') {
		if (*buff == '0')
			p = HT[p].lchild;
		else
			p = HT[p].rchild;
	}
	if (!HT[p].lchild && !HT[p].rchild) {
		cout << HT[p].ch;
		p = m;
	}
	buff ++ ;
}



int main() {
	BiTree root = new BiTNode;
	root->data = 'a';
	return 0;
}