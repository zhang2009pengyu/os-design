#include <iostream>
#include <queue>
using namespace std;

typedef struct QNode {
	int name;
	int prio;
	int round;
	int cputime;
	int needtime;
	int count;
	char state;
	struct QNode *next;
}*QueuePtr;

struct LinkQueue
{
	QueuePtr front, rear; // 队头、队尾指针
};

void InitQueue(LinkQueue &Q)
{ // 构造一个空队列Q。
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode)); // 生成头结点
	if (!Q.front) // 生成头结点失败
		exit(OVERFLOW);
	Q.front->next = NULL; // 头结点的next域为空
}

void DestroyQueue(LinkQueue &Q)
{ // 销毁队列Q(无论空否均可)。
	while (Q.front) // Q.front不为空
	{
		Q.rear = Q.front->next; // Q.rear指向Q.front的下一个结点
		free(Q.front); // 释放Q.front所指结点
		Q.front = Q.rear; // Q.front指向Q.front的下一个结点
	}
}

void ClearQueue(LinkQueue &Q)
{ // 将队列Q清为空队列
	DestroyQueue(Q); // 销毁队列Q
	InitQueue(Q); // 重新构造空队列Q
}

bool QueueEmpty(LinkQueue Q)
{ // 若队列Q为空队列，则返回TRUE；否则返回FALSE
	if (Q.front->next == NULL)
		return true;
	else
		return false;
}

int QueueLength(LinkQueue Q)
{ // 求队列Q的长度
	int i = 0; // 计数器，初值为0
	QueuePtr p = Q.front; // p指向头结点
	while (Q.rear != p) // p所指不是尾结点
	{
		i++; // 计数器+1
		p = p->next; // p指向下一个结点
	}
	return i;
}

void GetHead(LinkQueue Q, QueuePtr e)
{ // 若队列Q不空，则用e返回Q的队头元素
	QueuePtr p;
	p = Q.front->next; // p指向队头结点
	e = p; // 将队头元素的值赋给e
}

void EnQueue(LinkQueue &Q, QueuePtr e)
{ // 插入元素e为队列Q的新的队尾元素。
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode)); // 动态生成新结点
	if (!p)
		exit(OVERFLOW); // 失败则退出
	p = e; // 将值e赋给新结点
	p->next = NULL; // 新结点的指针域为空
	Q.rear->next = p; // 原队尾结点的指针指向新结点
	Q.rear = p; // 尾指针指向新结点
}

void DeQueue(LinkQueue &Q, QueuePtr &e)
{ // 若队列Q不空，删除Q的队头元素，用e返回其值，
  // 并返回OK；否则返回ERROR。
	QueuePtr p;
	p = Q.front->next; // p指向队头结点
	 // 将队头元素的值赋给e
	e->name = p->name;
	e->cputime = p->cputime;
	e->needtime = p->needtime;
	Q.front->next = p->next; // 头结点指向下一个结点
	if (Q.rear == p) // 删除的是队尾结点
		Q.rear = Q.front; // 修改队尾指针指向头结点(空队列)
	free(p); // 释放队头结点
}

//时间片轮转
void process1(LinkQueue q1, LinkQueue q2, LinkQueue q3, int time) {
	int i = 0;
	int t = 0;
	if (QueueEmpty(q1)) {
		while (i < 10) {
			QueuePtr e = new QNode;
			DeQueue(q2, e);
			EnQueue(q1, e);
			i = i + 1;
		}
	}

	while (!QueueEmpty(q1)) {
		QueuePtr e = new QNode;
		DeQueue(q1, e);
		if (e->needtime > time) {
			e->needtime -= e->needtime - time;
			EnQueue(q1, e);
			t = t + time;
		}
		else {
			t = t + e->needtime;
			e->needtime = 0;
			cout << "已完成:" << e->name << ",等待时间为;" << t - e->cputime << "\n" << endl;
			EnQueue(q3, e);
			i = i - 1;
		}
		if (i < 10) {
			if (!QueueEmpty(q2)) {
				QueuePtr e = new QNode;
				DeQueue(q2, e);
				EnQueue(q1, e);
				i = i + 1;
			}
		}
	}
}

//FCFS
void process2(LinkQueue q1, LinkQueue q2, LinkQueue q3, int time) {
	int i = 0;
	int t = 0;
	while (!QueueEmpty(q2)) {
		if (QueueEmpty(q1)) {
			QueuePtr e = new QNode;
			DeQueue(q2, e);
			EnQueue(q1, e);
			i = i + 1;
		}

		QueuePtr e = new QNode;
		DeQueue(q1, e);
		t = t + e->cputime;
		cout << "已完成:" << e->name << ",等待时间为;" << t - e->cputime << "\n" << endl;
		EnQueue(q3, e);
	}
}

int main() {
	LinkQueue q1;
	LinkQueue q2;
	LinkQueue q3;
	InitQueue(q1);
	InitQueue(q2);
	InitQueue(q3);
	QueuePtr head = new QNode;
	head->name = 0;
	head->cputime = 1;
	head->needtime = 1;

	for (int i = 1; i < 20; i++) {
		QueuePtr e = new QNode;
		e->name = i;
		e->cputime = i + 1;
		e->needtime = i + 1;
		EnQueue(q2, e);
	}

	process2(q1, q2, q3, 10);
	getchar();
	return 0;
}


