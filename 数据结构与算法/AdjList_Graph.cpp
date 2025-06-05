//图的邻接表表示法
#include <iostream>
#define OK 1
#define ERROR 0
#define INF 99999999
#define MaxVnum 100
using namespace std;

/*
  邻接表：头结点+表结点
  头结点：顶点信息+第一个表结点
  表结点：邻接顶点编号+边信息+下一个表结点
 */
//表结点


typedef int VertexType; //顶点类型
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
}Graph;
Graph G;

int ve[MaxVnum], vl[MaxVnum]; // ve：事件最早发生时间  vl：事件最晚发生时间
int TopSort[MaxVnum], tp; // 拓扑排序数组
bool visited[MaxVnum]; //标记访问


void CreateGraph(Graph &G); // 创建图
int ToplogicalSort(Graph G); //拓扑排序
int Dealve(Graph G); //求解ve
int Dealvl(Graph G); //求解vl
void CriticalPath(Graph G); // 求解关键路径
void DFSTraverse(Graph G); // 深度优先遍历
void DFS(Graph G, int v); // dfs
void BFSTraverse(Graph G); // 广度优先遍历
void MinSpanTree_PRIM(Graph G, int u); //prim 算法求最小生成树


int main(){
	
	return 0;
}

void CreateGraph(Graph &G){
	cin >> G.vexnum >> G.arcnum; //输入顶点数与边数
	for(int i = 0; i < G.vexnum; ++ i){ //输入每个头结点信息
		cin >> G.vertices[i].data;
		G.vertices[i].firstarc = NULL;
	}
	for(int i = 0; i < G.arcnum; ++ i){ //建立每条边
		int u, v, w;
		ArcNode* p = new ArcNode;
		cin >> u >> v >> w;
		p->Adjvex = v; //有向图建一次，无向图建两次
		p->weight = w;
		p->nextarc = G.vertices[u].firstarc;
		G.vertices[u].firstarc = p;
	}
}

int ToplogicalSort(Graph G){
	int inDegree[G.vexnum] = {0}; //设置入度数组，存每个结点的入度
	for(int i = 0; i < G.vexnum; ++ i) //遍历邻接表
		for(ArcNode* j = G.vertices[i].firstarc; j; j = j->nextarc) //求出每个结点的入度并存储在数组中
			inDegree[j->Adjvex] ++ ;
	int count = 0; //计数
	int stk[MaxVnum], tt = 0; //栈
	for(int i = 0; i < G.vexnum; ++ i) //遍历所有结点，使入度为0的结点入栈
		if(!inDegree[i]) stk[ ++ tt] = i;
	while(tt){ //栈不为空
		int t = stk[tt -- ]; //出栈
		TopSort[ ++ tp] = t; //存入拓扑数组
		count ++ ; 
		for(ArcNode* i = G.vertices[t].firstarc; i; i = i->nextarc){ //所有邻接结点入度减一
			inDegree[i->Adjvex] -- ;
			if(!inDegree[i->Adjvex]) stk[ ++ tt] = i->Adjvex; //入度为0的结点入栈
		}
	}
	if(count < G.vexnum) return ERROR; //出栈结点数<总结点数 表示图中有环
	return OK;
}


int Dealve(Graph G){
	if(ToplogicalSort(G) == ERROR) return ERROR; //求出拓扑排序序列
	for(int i = 0; i < G.vexnum; ++ i) ve[i] = 0; //初始化ve
	for(int i = 1; i <= tp; ++ i){ //正序拓扑排序求ve
		int u = TopSort[i];
		for(ArcNode* j = G.vertices[u].firstarc; j; j = j->nextarc){
			int v = j->Adjvex, w = j->weight;
			if(ve[u] + w > ve[v]) ve[v] = ve[u] + w; //ve[v] = max(ve[v], ve[u] + <u, v>)
		}
	}
	return OK;
}

int Dealvl(Graph G){
	if(ToplogicalSort(G) == ERROR) return ERROR;
	for(int i = 0; i < G.vexnum; ++ i) vl[i] = ve[G.vexnum - 1]; //初始化vl
	for(int i = tp; i >= 1; i -- ){ //逆序拓扑排序求vl
		int u = TopSort[i];
		for(ArcNode* j = G.vertices[u].firstarc; j; j = j->nextarc){
			int v = j->Adjvex, w = j->weight;
			if(vl[u] < vl[v] - w) vl[u] = vl[v] - w; ////vl[u] = min(vl[u], vl[v] - <u, v>)
		}
	}
	return OK;
}

void CriticalPath(Graph G){
	for(int i = 0; i < G.vexnum; ++ i)
		for(ArcNode* j = G.vertices[i].firstarc; j; j = j->nextarc){
			int u = j->Adjvex, w = j->weight;
			if(ve[i] == vl[u] - w) cout << i << "--->" << u << endl;
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
	for(ArcNode* i = G.vertices[v].firstarc; i; i = i->nextarc)
		if(visited[i->Adjvex] == false)
			DFS(G, i->Adjvex);
}

void BFSTraverse(Graph G){
	int q[MaxVnum], hh = 1, tt = 0;
	for(int i = 0; i < G.vexnum; ++ i)
		visited[i] = false;
	for(int i = 0; i < G.vexnum; ++ i){
		if(visited[i] == false) 
			q[ ++ tt] = i, visited[i] = true;
		while(hh <= tt){
			int t = q[hh ++ ];
			cout << t << endl;
			for(ArcNode* j = G.vertices[t].firstarc; j; j = j->nextarc)
				if(visited[j->Adjvex] == false)
					q[ ++ tt] = j->Adjvex, visited[j->Adjvex] = true;
		}
	}
}

void MinSpanTree_PRIM(Graph G, int u){
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

