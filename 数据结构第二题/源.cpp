include<iostream>
#define MVNum 100 //最大顶点数
#define OK 1
using namespace std;
int visited[MVNum] = { 0 };
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
	cout << "请输入顶点值" << endl;
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

void BFS(ALGraph G, int v)
{
	SqQueue q;
	Dance d;
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
}

int main() {
	ALGraph G;
	CreateUDG(G);
	int v;
	cout << "请输出从那个节点开始";
	cin >> v;
	BFS(G, v);
	return 0;
}