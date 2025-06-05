/*
  邻接表、邻接矩阵输入格式均为(u, v, w)：
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
typedef int AdjMarix[MaxVnum][MaxVnum]; //矩阵类型
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
void PRIM_Marix(Graph_Marix G, int u); //prim 算法求最小生成树
void PrintMarix(Graph_Marix G); // 打印邻接矩阵


/*----------------邻接表操作-----------------*/
void CreateGraph_List(Graph_List &G); // 创建图
void PRIM_List(Graph_List G, int u); //prim 算法求最小生成树
void PrintList(Graph_List G); //打印邻接表




int main(){
	//邻接矩阵
	cout << "Input AdjMarix : " << endl;
	Graph_Marix G;
	CreateGraph_Marix(G); //建图
	PrintMarix(G); //打印
	cout << "MinSpanTree : " << endl;
	PRIM_Marix(G, 0); //prim最小生成树
	
	//邻接表
	cout << "Input AdjList : " << endl;
	Graph_List G1;
	CreateGraph_List(G1); //建图
	PrintList(G1); //打印
	cout << "MinSpanTree : " << endl;
	PRIM_List(G1, 0); //prim最小生成树

	return 0;
}

/*----------------邻接矩阵操作-----------------*/
void CreateGraph_Marix(Graph_Marix &G){
	cin >> G.vexnum >> G.arcnum; //输入顶点数、边数
	for(int i = 0; i < G.vexnum; ++ i) //初始化邻接矩阵
		for(int j = 0; j < G.vexnum; ++ j)
			G.arcs[i][j] = INF;
	for(int i = 0; i < G.arcnum; ++ i){ //输入邻接矩阵
		int u, v, w;
		cin >> u >> v >> w;
		G.arcs[u][v] = w; //无向图两次建边
		G.arcs[v][u] = w;
	}
}

void PRIM_Marix(Graph_Marix G, int u){
	struct{
		int adjvex; //结点
		int lowcost; //与生成树的最小距离
	}closedge[MaxVnum];
	closedge[u].lowcost = 0; //起点加入生成树，lowcost=0 表示已经加入生成树
	for(int i = 0; i < G.vexnum; ++ i) //初始化所有点与生成树的距离
		if(i != u) closedge[i] = {u, G.arcs[i][u]};
	for(int i = 1; i < G.vexnum; ++ i){ //遍历vexnum - 1次
		int t = INF, k = -1; //距离、顶点编号
		for(int j = 0; j < G.vexnum; ++ j) //找到不在生成树中的且与生成树距离最小的结点
			if(closedge[j].lowcost < t && closedge[j].lowcost)
				t = closedge[j].lowcost, k = j;
		if(t == INF) break; //找不到说明结点已经全部加入生成树
		cout << k << "<--->" << closedge[k].adjvex << endl;
		closedge[k].lowcost = 0; //否则加入生成树
		for(int j = 0; j < G.vexnum; ++ j) //更新其他顶点到生成树的距离
			if(G.arcs[j][k] < closedge[j].lowcost)
				closedge[j] = {k, G.arcs[j][k]};
	}
}

void PrintMarix(Graph_Marix G){
	cout << "AdjMarix : " << endl;
	for(int i = 0; i < G.vexnum; ++ i){
		for(int j = 0; j < G.vexnum; ++ j)
			if(G.arcs[i][j] == INF) cout << "INF" << ' ';
			else cout << G.arcs[i][j] << ' ';
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

void PRIM_List(Graph_List G, int u){
	struct{
		int adjvex;
		int lowcost;
	}closedge[MaxVnum];
	for(int i = 0; i < G.vexnum; ++ i) //初始化所有与生成树的距离为INF
		closedge[i].lowcost = INF;
	closedge[u].lowcost = 0; //起点加入生成树
	for(ArcNode* i = G.vertices[u].firstarc; i; i = i->nextarc) //更新邻接点到生成树的距离
		closedge[i->Adjvex] = {u, i->weight};
	for(int i = 1; i < G.vexnum; ++ i){ //遍历n-1次
		int t = INF, k = -1;
		for(int j = 0; j < G.vexnum; ++ j)
			if(t > closedge[j].lowcost && closedge[j].lowcost) //找到不在生成树中且生成树距离最小的结点
				t = closedge[j].lowcost, k = j;
		if(t == INF) break; //不存在，退出
		cout << k << "<--->" << closedge[k].adjvex << endl;
		closedge[k].lowcost = 0; //加入生成树
		for(ArcNode* j = G.vertices[k].firstarc; j; j = j->nextarc) //邻接点与生成树的距离
			if(j->weight < closedge[j->Adjvex].lowcost)
				closedge[j->Adjvex] = {k, j->weight};
	}
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

