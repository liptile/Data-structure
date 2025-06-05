/*
  邻接矩阵输入格式为：
  7 12
  0 0 1 0 0 0 0
  1 0 0 0 0 0 0
  0 1 0 0 0 1 0
  0 1 1 0 1 0 0
  0 1 0 0 0 0 0
  0 0 0 1 0 0 0
  0 0 0 1 1 1 0
  
  邻接表输入格式为：
  6 9
  0 1 20
  0 2 16
  1 4 13
  1 2 15
  1 5 28 
  5 4 12
  4 3 12
  2 3 14
  5 3 12
 */
#include <iostream>
#define OK 1
#define ERROR 0
#define INF 99999999
#define MaxVnum 100
using namespace std;

/*----------------邻接矩阵-----------------*/
typedef int VertexType; //顶点类型
typedef double AdjMarix[MaxVnum][MaxVnum]; //矩阵类型
typedef struct{
	VertexType vexs[MaxVnum]; //顶点向量（有什么用？）
	AdjMarix  arcs; //邻接矩阵
	int vexnum, arcnum; //顶点数与边数
}Graph_Marix;


/*-----------------邻接表-------------------*/
//表结点
typedef struct ArcNode{
	int Adjvex; //表头结点的邻接结点的编号
	int weight; //边的信息
	struct ArcNode* nextarc; //下一条边
}ArcNode;
//头结点
typedef struct{
	VertexType data; //头结点数据
	ArcNode* firstarc; //第一个表结点
}AdjList[MaxVnum]; //邻接表
//图类型
typedef struct{
	int vexnum, arcnum; //顶点数与边数
	AdjList vertices; //邻接表
	int kind; //图的类型标志
}Graph_List;


bool visited[MaxVnum];

/*----------------邻接矩阵操作-----------------*/
void CreateGraph_Marix(Graph_Marix &G); // 创建图
void DFSTraverse_Marix(Graph_Marix G); // 深度优先遍历
void DFS_Marix(Graph_Marix G, int v); // dfs
void PrintMarix(Graph_Marix G); // 打印邻接矩阵


/*----------------邻接表操作-----------------*/
void CreateGraph_List(Graph_List &G); // 创建图
void DFSTraverse_List(Graph_List G); // 深度优先遍历
void DFS_List(Graph_List G, int v); // dfs
void PrintList(Graph_List G); //打印邻接表

int main(){
	//邻接矩阵
	cout << "Input AdjMarix : " << endl;
	Graph_Marix G;
	CreateGraph_Marix(G); //建图
	cout << "DFS Order : ";
	DFSTraverse_Marix(G); //bfs
	
	//邻接表
	cout << "Input AdjList : " << endl;
	Graph_List G1;
	CreateGraph_List(G1); //建图
	PrintList(G1);
	cout << "DFS Order : ";
	DFSTraverse_List(G1); //bfs
	return 0;
}

/*----------------邻接矩阵操作-----------------*/
void CreateGraph_Marix(Graph_Marix &G){
	cin >> G.vexnum >> G.arcnum; //输入顶点数、边数
//	for(int i = 0; i < G.vexnum; ++ i) //初始化邻接矩阵
//		for(int j = 0; j < G.vexnum; ++ j)
//			G.arcs[i][j] = INF;
	for(int i = 0; i < G.vexnum; ++ i) //输入邻接矩阵
		for(int j = 0; j < G.vexnum; ++ j)
			cin >> G.arcs[i][j];
}

void DFSTraverse_Marix(Graph_Marix G){
	for(int i = 0; i < G.vexnum; ++ i) //初始化访问标记
		visited[i] = false;
	for(int i = 0; i < G.vexnum; ++ i) //防止不连通
		if(visited[i] == false) DFS_Marix(G, i);
	cout << endl;
}

void DFS_Marix(Graph_Marix G, int v){
	visited[v] = true; cout << v + 1 << ' '; //输出
	for(int i = 0; i < G.vexnum; ++ i) //dfs邻接点
		if(visited[i] == false && G.arcs[v][i])
			DFS_Marix(G, i);
}

void PrintMarix(Graph_Marix G){
	cout << "AdjMarix : " << endl;
	for(int i = 0; i < G.vexnum; ++ i){
		for(int j = 0; j < G.vexnum; ++ j)
			cout << G.arcs[i][j] << ' ';
		cout << endl;
	}
}



/*----------------邻接表操作-----------------*/
void CreateGraph_List(Graph_List &G){
	cin >> G.vexnum >> G.arcnum; //输入边数、顶点数
	for(int i = 0; i < G.vexnum; ++ i){ //初始化 每个头结点
		G.vertices[i].data = i;
		G.vertices[i].firstarc = NULL;
	}
	for(int i = 0; i < G.arcnum; ++ i){
		int u, v, w;
		cin >> u >> v >> w; //建边
		ArcNode* p = new ArcNode;
		p->Adjvex = v;
		p->weight = w;
		p->nextarc = G.vertices[u].firstarc; //插入邻接表
		G.vertices[u].firstarc = p;
		p = new ArcNode; //无向图建两次边
		p->Adjvex = u;
		p->weight = w;
		p->nextarc = G.vertices[v].firstarc;
		G.vertices[v].firstarc = p;
	}
}

void DFSTraverse_List(Graph_List G){
	for(int i = 0; i < G.vexnum; ++ i)
		visited[i] = false;
	for(int i = 0; i < G.vexnum; ++ i)
		if(visited[i] == false) DFS_List(G, i);
	cout << endl;
}

void DFS_List(Graph_List G, int v){
	visited[v] = true; cout << v << ' ';
	for(ArcNode* i = G.vertices[v].firstarc; i; i = i->nextarc)
		if(visited[i->Adjvex] == false) DFS_List(G, i->Adjvex);
}

void PrintList(Graph_List G){
	cout << "AdjList : " << endl;
	for(int i = 0; i < G.vexnum; ++ i){
		cout << i << " : ";
		for(ArcNode* j = G.vertices[i].firstarc; j; j = j->nextarc)
			cout << j->Adjvex << ' ';
		cout << endl;
	}
}

