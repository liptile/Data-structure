#include <iostream>
#define OK 1
#define ERROR 0
using namespace std;

typedef int Status;
//二叉排序树的存储结构
typedef int KeyType;
typedef char OtherInfoType;
typedef struct{
	KeyType key;
	OtherInfoType info;
}ElemType;

//二叉链表存储
typedef struct BiTNode{
	ElemType data;
	struct BiTNode *lchild,  *rchild;
}BiTNode,  *BiTree;

BiTree SearchBST(BiTree T,  KeyType key); //递归查找关键字为key的结点
Status InsertBST(BiTree &T,  ElemType e); //插入元素e
Status DeleteBST(BiTree &T,  KeyType key); // 删除关键字为key的结点
void DeleteNode(BiTree &T); //删除结点操作

int main(){
	
	return 0;
}

BiTree SearchBST(BiTree T,  KeyType key){
	if(!T) return NULL; //没有找到
	else if(T->data.key == key) return T; //找到就返回
	else if(key < T->data.key) //关键字小于根节点
		return SearchBST(T->lchild,  key); //左子树上找
	else return SearchBST(T->rchild,  key); //否则右子树上找
}
Status InsertBST(BiTree &T,  ElemType e){
	BiTNode *p = T,  *father = NULL;
	while(p && p->data.key != e.key){
		father = p; //记录找到结点的父节点
		if(e.key > p->data.key) p = p->rchild; //小于就找右子树
		else p = p->lchild; //大于就找左子树
	}
	if(p) return false; //找到就不插入
	BiTNode *s = new BiTNode; //新建结点存关键字
	s->data = e;
	s->lchild = s->rchild = NULL;
	if(father == NULL) T = s; //树为空树s就是根节点
	else if(e.key > father->data.key) //否则根据大小将s插入
		father->rchild = s;
	else father->lchild =s;
}
Status DeleteBST(BiTree &T,  KeyType key){
	if(!T) return false; //空树
	if(key == T->data.key){ //找到
		DeleteNode(T); //删除
		return true;
	}else if(key < T->data.key) 
		return DeleteBST(T->lchild, key); //小于就找左子树
	else return DeleteBST(T->rchild, key); //大于找右子树
}
void DeleteNode(BiTree &p){
	BiTNode *q = NULL,  *s = NULL;
	if(!p->rchild){ //被删结点右子树为空
		q = p; p = p->lchild; free(q); //q指向其左子树
	}else if(!p->lchild){ //左子树空
		q = p; p = p->rchild; free(q); //q指向其右子树
	}else{ //左右子树均非空
		q = p; s = p->lchild;
		while(s->rchild) q = s,  s = s->rchild; //s指向p前驱
		p->data = s->data;
		if(q != p) q->rchild = s->lchild; //重接
		else q->lchild = s->lchild;
		free(s);
	}
}
