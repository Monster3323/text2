#include<iostream>
#include<string.h> 
#define MVNum 100 //��󶥵���
#define OK 1
using namespace std;
int visited[MVNum] = { 0 };
typedef int Status;

typedef struct ArcNode {   //�߽��
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

typedef struct VNode {     //������Ϣ
	Dance data;
	ArcNode* firstarc;
}VNode, AdjList[MVNum];

typedef struct {   //�ڽӱ�
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
	cout << "����������:";
	cin >> p->data.name;

	cout << "����������:";
	cin >> p->data.age;

	cout << "��������ߣ�cm��:";
	cin >> p->data.height;

	cout << "���������أ�kg��:";
	cin >> p->data.weight;

	cout << "������id:";
	cin >> p->data.id;

	cout << "�������Ա�:";
	cin >> p->data.sex;

	cout << "����������ʲô���͵�����:";
	cin >> p->data.branch;

	cout << "�����밮��:";
	cin >> p->data.hobby;

	cout << "���Ƿ���:";
	cin >> p->data.IsSingle;

	cout << "���������Ĵ�ҵʱ�䣨�£�:";
	cin >> p->data.workingTime;

	return p->data;
}

Status Display(Dance d)//���һ��
{
	cout << "����:" << d.name << endl;
	cout << "����:" << d.age << endl;
	cout << "�Ա�:" << d.sex << endl;
	cout << "���:" << d.height << endl;
	cout << "id:" << d.id << endl;
	cout << "����:" << d.weight << endl;
	cout << "ְҵ:" << d.branch << endl;
	cout << "��ҵʱ��:" << d.workingTime << endl;
	cout << "����:" << d.hobby << endl;
	cout << "�Ƿ���:" << d.IsSingle << endl;
	cout << "-------------------------------------------------------" << endl;
	return 1;
}

Status CreateUDG(ALGraph& G) {
	int i, j, k;
	int id1, id2;
	ArcNode* p1, * p2;
	cout << "�������ܶ��������ܱ���" << endl;
	cin >> G.vexnum >> G.arcnum;
	for (i = 0; i < G.vexnum; i++) {
		cout << "�������" << i + 1 << "����������" << endl;
		G.vertices[i].data = CreatVNode();
		G.vertices[i].firstarc = NULL;
	}
	cout << "����һ���ߵ����������id" << endl;
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

Status Search(ALGraph G, int id)
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
		cout << "��ͼ���κ������޷�����" << endl;
		return 0;
	}
	SqQueue q;
	Dance d;
	int v, j;
	int visited[MVNum] = { 0 };
	cout << "������Ҫ��ʼ�����ĳ�ʼ�ڵ�id��" << endl;
	cin >> v;
	while (j = Search(G, v) == 0)
	{
		cout << "û�д˽ڵ㣬���������룺" << endl;
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

void DFS(ALGraph G, int v)
{
	int w;
	ArcNode* p;
	Display(G.vertices[v].data);
	visited[v] = 1;
	p = G.vertices[v].firstarc;
	while (p != NULL)
	{
		w = p->adjvex;
		if (!visited[w])
			DFS(G, w);
		p = p->nextarc;
	}

}

void menu()
{
	cout << "            Danceͼ�ṹ���ݴ������" << endl;
	cout << "1.����Fishͼ" << endl;
	cout << "2.������ȱ����ķ�ʽ��ӡ���е�Fish;" << endl;
	cout << "3.���չ�ȱ����ķ�ʽ��ӡ���е�Fish��" << endl;
	cout << "4.�˳���" << endl;
	cout << "���������ѡ��1-7����" << endl;
}


int main() {
	ALGraph G;
	G.vexnum = 0;
	int i, k = 0;
	while (true)
	{
		menu();
		cout << "--------------------------------------------------------" << endl;
		cin >> i;
		switch (i)
		{
		case 1:
		{
			ALGraph G1;
			CreateUDG(G1);
			G = G1;
		} break;
		case 2:
		{
			if (G.vexnum == 0)
			{
				cout << "��ͼ���κ������޷�����" << endl;
				break;
			}
			cout << "������Ҫ��ʼ�����ĳ�ʼ�ڵ�id��" << endl;
			int v;
			cin >> v;
			while (int j = Search(G, v) == 0)
			{
				cout << "û�д˽ڵ㣬���������룺" << endl;
				cin >> v;
			}
			DFS(G, Locate(G, v));
			memset(visited, 0, sizeof(visited));
		} break;
		case 3:BFS(G); break;
		case 4:return 1; break;
		}
	}
	return 0;
}