//图的邻接矩阵表示法
#include <iostream>
#define OK 1
#define ERROR 0
#define INF 99999999
#define MaxVnum 50  //最大节点数
using namespace std;
bool visited[MaxVnum]; //dfs标记用
/*
  数组（邻接矩阵）表示法
  vexnum:顶点数  arcnum:边数
  图结构：1.顶点向量 2.邻接矩阵 3.顶点数与边数
 */
typedef int VertexType; //顶点类型
typedef double AdjMarix[MaxVnum][MaxVnum]; //矩阵类型
typedef struct{
	VertexType vexs[MaxVnum]; //顶点向量（有什么用？）
	AdjMarix  arcs; //邻接矩阵
	int vexnum, arcnum; //顶点数与边数
}Graph;
Graph G;

void CreateGraph(Graph &G); //创建图
void DFSTraverse(Graph G); // 深度优先遍历
void DFS(Graph G, int v); // dfs
void BFSTraverse(Graph G); // 广度优先遍历
void MinSpanTree_PRIM(Graph G, int u); //prim 算法求最小生成树
int ToplogicalSort(Graph G); //拓扑排序


int main(){
	
	return 0;
}

void CreateGraph(Graph &G){
	cin >> G.vexnum >> G.arcnum; //输入顶点数与边数
	for(int i = 0; i < G.vexnum; ++ i) //输入每个顶点信息
		cin >> G.vexs[i];
	for(int i = 0; i < G.vexnum; ++ i) //初始化邻接矩阵
		for(int j = 0; j < G.vexnum; ++ j)
			G.arcs[i][j] = INF;
	for(int i = 0; i < G.arcnum; ++ i){ //输入每个边的权值
		int u, v, w;
		cin >> u >> v >> w;
		G.arcs[u][v] = w;
	}
}

void DFSTraverse(Graph G){
	for(int i = 0; i < G.vexnum; ++ i)
		visited[i] = false;
	for(int i = 0; i < G.vexnum; ++ i)
		if(visited[i] == false) DFS(G, i);
}

void DFS(Graph G, int v){
	visited[v] = true; cout << v << endl;
	for(int i = 0; i < G.vexnum; ++ i)
		if(G.arcs[v][i] != INF && visited[i] == false)
			DFS(G, i);
}

void BFSTraverse(Graph G){
	for(int i = 0; i < G.vexnum; ++ i) //初始化
		visited[i] = false;
	int q[MaxVnum], hh = 1, tt; //定义队列
	for(int i = 0; i < G.vexnum; ++ i){ //遍历所有结点防止不连通
		if(visited[i] == false) //入队一个结点
			q[ ++ tt] = i, visited[i] = true;
		while(hh <= tt){ //队列非空循环
			int t = q[hh ++ ]; cout << t << endl; //出队
			for(int i = 0; i < G.vexnum; ++ i) //邻接点入队
				if(G.arcs[t][i] != INF && visited[i] == false)
					q[ ++ tt] = i, visited[i] = true;
		}
	}
}

void MinSpanTree_PRIM(Graph G, int u){
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


