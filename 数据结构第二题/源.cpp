#include<iostream>
#define MVNum 100 //最大顶点数
#define OK 1
using namespace std;

typedef int Status;

typedef struct ArcNode {   //边结点
	int adjvex;
	struct ArcNode* nextarc;
}ArcNode;

typedef struct
{
	string name;
	string sex;
	string hobby;
	string branch;
	int id, age;
	char IsSingle;
	double height, weight;
	double workingTime;

}Dance;

typedef struct VNode {     //顶点信息
	Dance data;
	ArcNode* firstarc;
}VNode, AdjList[MVNum];

typedef struct {   //邻接表
	AdjList vertices;
	int vexnum, arcnum;
}ALGraph;

typedef struct
{
	Dance* base;
	int front, rear;
}SqQueue;

typedef struct
{
	Dance* base;
	Dance* top;
	int stacksize;
}SqStack;


Status InitQueue(SqQueue& q)
{
	q.base = new Dance[MVNum];
	if (!q.base)
		return 1;
	q.rear = q.front = 0;
	return OK;
}

Status EnQueue(SqQueue& q, Dance v)
{
	if ((q.rear + 1) % MVNum == q.front)
		return -1;
	q.base[q.rear] = v;
	q.rear = (q.rear + 1) % MVNum;

	return OK;
}

Status DeQueue(SqQueue& q, Dance& v)
{
	if (q.front == q.rear)
		return -1;
	v = q.base[q.front];
	q.front = (q.front + 1) % MVNum;
	return 1;
}

int Locate(ALGraph G, int id) {
	int i;
	for (i = 0; i < G.vexnum; i++)
	{
		if (G.vertices[i].data.id == id)
			return i;
	}
	return OK;
}

Dance CreatVNode()
{
	VNode* p = new VNode;
	cout << "请输入姓名:";
	cin >> p->data.name;

	cout << "请输入年龄:";
	cin >> p->data.age;

	cout << "请输入身高（cm）:";
	cin >> p->data.height;

	cout << "请输入体重（kg）:";
	cin >> p->data.weight;

	cout << "请输入id:";
	cin >> p->data.id;

	cout << "请输入性别:";
	cin >> p->data.sex;

	cout << "请输入您是什么类型的舞者:";
	cin >> p->data.branch;

	cout << "请输入爱好:";
	cin >> p->data.hobby;

	cout << "您是否单身:";
	cin >> p->data.IsSingle;

	cout << "请输入您的从业时间（月）:";
	cin >> p->data.workingTime;

	return p->data;
}

Status Display(Dance d)//输出一个
{
	cout << "姓名:" << d.name << endl;
	cout << "年龄:" << d.age << endl;
	cout << "性别:" << d.sex << endl;
	cout << "身高:" << d.height << endl;
	cout << "id:" << d.id << endl;
	cout << "体重:" << d.weight << endl;
	cout << "职业:" << d.branch << endl;
	cout << "从业时间:" << d.workingTime << endl;
	cout << "爱好:" << d.hobby << endl;
	cout << "是否单身:" << d.IsSingle << endl;
	cout << "-------------------------------------------------------" << endl;
	return 1;
}

Status CreateUDG(ALGraph& G) {
	int i, j, k;
	int id1, id2;
	ArcNode* p1, * p2;
	cout << "请输入总顶点数，总边数" << endl;
	cin >> G.vexnum >> G.arcnum;
	for (i = 0; i < G.vexnum; i++) {
		cout << "请输入第" << i + 1 << "个顶点数据" << endl;
		G.vertices[i].data = CreatVNode();
		G.vertices[i].firstarc = NULL;
	}
	cout << "输入一条边的两个顶点的id" << endl;
	for (k = 0; k < G.arcnum; k++) {
		cin >> id1 >> id2;
		i = Locate(G, id1);
		j = Locate(G, id2);
		p1 = new ArcNode;
		p1->adjvex = j;
		p1->nextarc = G.vertices[i].firstarc;
		G.vertices[i].firstarc = p1;
		p2 = new ArcNode;
		p2->adjvex = i;
		p2->nextarc = G.vertices[j].firstarc;
		G.vertices[j].firstarc = p2;
	}
	return OK;
}
int Isempty(SqQueue q)
{
	if (q.front == q.rear)
		return 1;
	return 0;
}


Status InitStack(SqStack& S)
{
	S.base = new Dance[MVNum];
	if (!S.base)
		return 0;
	S.top = S.base;
	S.stacksize = 100;
	return 1;
}


Status Push(SqStack& S, Dance v)
{
	if (S.top - S.base == S.stacksize)
		return 0;
	*S.top++ = v;
	return 1;
}

Status Pop(SqStack& S, Dance& v)
{
	if (S.top == S.base)
		return 0;
	v = *--S.top;
	return 1;
}


Status IsemptyStack(SqStack S)
{
	if (S.base == S.top)
		return 1;
	return 0;
}

Status Search(ALGraph G,int id)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vertices[i].data.id == id)
			return 1;
	}
	return 0;
}

Status BFS(ALGraph G)
{
	if (G.vexnum == 0)
	{
		cout << "该图无任何数据无法遍历" << endl;
		return 0;
	}
	SqQueue q;
	Dance d;
	int v,j;
	int visited[MVNum] = { 0 };
	cout << "请输入要开始遍历的初始节点id：" << endl;
	cin >> v;
	while(j=Search(G, v) == 0)
	{
		cout << "没有此节点，请重新输入：" << endl;
		cin >> v;
	}
	v = Locate(G, v);
	InitQueue(q);
	EnQueue(q, G.vertices[v].data);
	visited[v] = 1;
	ArcNode* p;
	while (!Isempty(q))
	{

		DeQueue(q, d);
		v = Locate(G, d.id);
		p = G.vertices[v].firstarc;
		Display(G.vertices[v].data);
		while (p && visited[p->adjvex] != 1)
		{
			v = p->adjvex;
			EnQueue(q, G.vertices[v].data);
			visited[v] = 1;
			p = p->nextarc;
		}
	}
	return 1;
}

Status BDF(ALGraph G)
{
	if (G.vexnum == 0)
	{
		cout << "该图无任何数据无法遍历" << endl;
		return 0;
	}
	SqStack q;
	Dance d;
	int v,j;
	int visited[MVNum] = { 0 };
	cout << "请输入要开始遍历的初始节点id：" << endl;
	cin >> v;
	while (j = Search(G, v) == 0)
	{
		cout << "没有此节点，请重新输入：" << endl;
		cin >> v;
	}
	v = Locate(G, v);
	InitStack(q);
	Push(q, G.vertices[v].data);
	visited[v] = 1;
	ArcNode* p;
	while (!IsemptyStack(q))
	{

		Pop(q, d);
		v = Locate(G, d.id);
		p = G.vertices[v].firstarc;
		Display(G.vertices[v].data);
		while (p && visited[p->adjvex] != 1)
		{
			v = p->adjvex;
			Push(q, G.vertices[v].data);
			visited[v] = 1;
			p = p->nextarc;
		}
	}
	return 1;
}

void menu()
{
	cout << "            Dance图结构数据处理程序" << endl;
	cout << "1.创建Fish图" << endl;
	cout << "2.按照深度遍历的方式打印所有的Fish;" << endl;
	cout << "3.按照广度遍历的方式打印所有的Fish；" << endl;
	cout << "4.退出。" << endl;
	cout << "请输入你的选择（1-7）：" << endl;
}

int main() {
	ALGraph G;
	G.vexnum = 0;
	int i;
	while (true)
	{
		menu();
		cout << "--------------------------------------------------------"<<endl;
		cin >> i;
		switch (i)
		{
		case 1:CreateUDG(G); break;
		case 2:BDF(G); break;
		case 3:BFS(G); break;
		case 4:return 1; break;
		}
	}
	return 0;
}