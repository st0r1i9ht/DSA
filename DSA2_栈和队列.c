#include "DataStructure.h"
#include <stdio.h>

// 顺序栈表示
#define MAXSIZE 100
typedef struct
{
	SElemType* base; // 栈底指针
	SElemType* top; // 栈顶指针
	int stacksize; // 栈可用最大容量
}SqStack;

// 顺序栈初始化
Status InitStack(SqStack* S) // 构造一个空栈
{
	S->base = (SqStack*)malloc(MAXSIZE * sizeof(SqStack));
	if (!S->base)
		exit(OVERFLOW); // 存储分配失败
	S->top = S->base; // 栈顶指针等于栈底指针
	S->stacksize = MAXSIZE;
	return OK;
}

// 顺序栈判断是否为空
Status StackEmpty(SqStack S) // 若栈为空 返回TRUE 否则返回FALSE
{
	if (S.top == S.base)
		return TRUE;
	else
		return FALSE;
}

// 清空顺序栈
Status ClearStack(SqStack* S)
{
	if (S->base)
		S->top = S->base;
	return OK;
}

// 销毁顺序栈
Status DestroyStack(SqStack* S)
{
	if (S->base)
	{
		free(S->base);
		S->stacksize = 0;
		S->base = S->top = NULL;
	}
	return OK;
}

// 顺序栈的入栈
Status Push(SqStack* S, SElemType e)
{
	if (S->top - S->base == S->stacksize)
		return ERROR;
	*S->top++ = e;
	return OK;
}

// 顺序栈的出栈
// 若栈不空 则删除S的栈顶元素 用e返回其值 并返回OK
// 否则返回ERROR
Status Pop(SqStack* S, SElemType* e)
{
	if (S->top == S->base)
		return ERROR;
	*e = *--S->top;
	return OK;
}

// 链栈的定义
// 只能在链表头部进行操作
typedef struct StackNode
{
	SElemType data;
	struct StackNode* next;
}StackNode, * LinkStack;

 //LinkStack S; 头指针

// 链栈的初始化
void InitStack_L(LinkStack S)
{
	// 构造一个空栈 栈顶指针置为空
	S = NULL;
	return OK;
}

// 判断链栈是否为空
Status StackEmpty_L(LinkStack S)
{
	if (S == NULL)
		return TRUE;
	else
		return FALSE;
}

// 链栈的入栈
Status Push_L(LinkStack S, SElemType e)
{
	StackNode* p = (StackNode*)malloc(sizeof(StackNode));// 生成新节点p
	p->data = e; // 将新节点数据域置为e
	p->next = S; // 将新节点插入栈顶
	S = p; // 修改栈顶指针
	return OK;
}

// 链栈的出栈
Status Pop_L(LinkStack S, SElemType* e)
{
	if (S == NULL)
		return ERROR;
	*e = S->data;
	StackNode* p = (StackNode*)malloc(sizeof(StackNode));
	S = S->next;
	free(p);
	return OK;
}

// 取栈顶元素
SElemType GetTop(LinkStack S)
{
	if (S != NULL)
		return S->data;
}

// 队列的顺序表示
#define MAXQSIZE 100//最大队列长度
typedef struct
{
	QElemType* base; // 初始化的动态分配存储空间
	int front; // 头指针
	int rear; // 尾指针
}SqQueue;

// 队列的初始化
Status InitQueue(SqQueue* Q)
{
	Q->base = (QElemType*)malloc(MAXQSIZE * sizeof(QElemType)); // 分配数组空间
	if (!Q->base) // 存储分配失败
		exit(OVERFLOW);
	Q->front = Q->rear = 0; // 头指针尾指针置为0 队列为空
	return OK;
}

// 求队列的长度
int QueueLength(SqQueue Q)
{
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

// 判断队列是否为空
Status QueueEmpty(SqQueue Q)
{
	if (Q.front == Q.rear)
		TRUE;
	else
		FALSE;
}

// 循环队列的入队算法
// 始终空一个位置 便于区分队满队空
Status EnQueue(SqQueue* Q, QElemType e)
{
	if (Q->rear + 1 % MAXQSIZE == Q->front) // 队满
		return ERROR;
	Q->base[Q->rear] = e; // 新元素加入队尾
	Q->rear = (Q->rear + 1) % MAXSIZE; // 队尾指针+1
	return OK;
}

// 出队
Status DeQueue(SqQueue* Q, QElemType* e)
{
	if (QueueEmpty(*Q)) // 队空 Q.front == Q.rear
		return ERROR;
	*e = Q->base[Q->front]; // 保存队头元素
	Q->front = (Q->front + 1) % MAXSIZE; // 队头指针 + 1
	return OK;
}

// 取队头元素
SElemType GetHead(SqQueue Q)
{
	if (Q.front != Q.rear) // 队列不为空
		return Q.base[Q.front]; // 返回队头指针元素的值 队头指针不变
}

// 链队 用户无法估计所用队列的长度 则宜采用链队列
// 链队列的类型定义
typedef struct Qnode
{
	QElemType data;
	struct Qnode* next;
}QNode, * QueuePtr;

typedef struct
{
	QueuePtr front; // 队头指针
	QueuePtr rear; // 队尾指针
}LinkQueue;

// 链队列初始化
Status InitQueue(LinkQueue* Q)
{
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front)
		exit(OVERFLOW);
	Q->front->next = NULL;
	return OK;
}

// 销毁链队列
Status DestroyQueue(LinkQueue* Q)
{
	while (Q->front)
	{
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
	return OK;
}

// 入队
Status EnLQueue(LinkQueue* Q, QElemType e)
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
		exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
	return OK;
}

// 出队
Status DeLQueue(LinkQueue* Q, QElemType* e)
{
	if (Q->front == Q->rear)
		return ERROR;
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	p = Q->front->next;
	*e = p->data;
	Q->front->next = p->next;
	if (Q->rear == p)
		Q->rear = Q->front;
	free(p);
	return OK;
}

// 求链队列的队头元素
Status GetLHead(LinkQueue Q, QElemType* e)
{
	if (Q.front == Q.rear)
		return ERROR;
	*e = Q.front->next->data;
	return OK;
}