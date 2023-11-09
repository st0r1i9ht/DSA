#include "DataStructure.h"
#include <stdio.h>

// ˳��ջ��ʾ
#define MAXSIZE 100
typedef struct
{
	SElemType* base; // ջ��ָ��
	SElemType* top; // ջ��ָ��
	int stacksize; // ջ�����������
}SqStack;

// ˳��ջ��ʼ��
Status InitStack(SqStack* S) // ����һ����ջ
{
	S->base = (SqStack*)malloc(MAXSIZE * sizeof(SqStack));
	if (!S->base)
		exit(OVERFLOW); // �洢����ʧ��
	S->top = S->base; // ջ��ָ�����ջ��ָ��
	S->stacksize = MAXSIZE;
	return OK;
}

// ˳��ջ�ж��Ƿ�Ϊ��
Status StackEmpty(SqStack S) // ��ջΪ�� ����TRUE ���򷵻�FALSE
{
	if (S.top == S.base)
		return TRUE;
	else
		return FALSE;
}

// ���˳��ջ
Status ClearStack(SqStack* S)
{
	if (S->base)
		S->top = S->base;
	return OK;
}

// ����˳��ջ
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

// ˳��ջ����ջ
Status Push(SqStack* S, SElemType e)
{
	if (S->top - S->base == S->stacksize)
		return ERROR;
	*S->top++ = e;
	return OK;
}

// ˳��ջ�ĳ�ջ
// ��ջ���� ��ɾ��S��ջ��Ԫ�� ��e������ֵ ������OK
// ���򷵻�ERROR
Status Pop(SqStack* S, SElemType* e)
{
	if (S->top == S->base)
		return ERROR;
	*e = *--S->top;
	return OK;
}

// ��ջ�Ķ���
// ֻ��������ͷ�����в���
typedef struct StackNode
{
	SElemType data;
	struct StackNode* next;
}StackNode, * LinkStack;

 //LinkStack S; ͷָ��

// ��ջ�ĳ�ʼ��
void InitStack_L(LinkStack S)
{
	// ����һ����ջ ջ��ָ����Ϊ��
	S = NULL;
	return OK;
}

// �ж���ջ�Ƿ�Ϊ��
Status StackEmpty_L(LinkStack S)
{
	if (S == NULL)
		return TRUE;
	else
		return FALSE;
}

// ��ջ����ջ
Status Push_L(LinkStack S, SElemType e)
{
	StackNode* p = (StackNode*)malloc(sizeof(StackNode));// �����½ڵ�p
	p->data = e; // ���½ڵ���������Ϊe
	p->next = S; // ���½ڵ����ջ��
	S = p; // �޸�ջ��ָ��
	return OK;
}

// ��ջ�ĳ�ջ
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

// ȡջ��Ԫ��
SElemType GetTop(LinkStack S)
{
	if (S != NULL)
		return S->data;
}

// ���е�˳���ʾ
#define MAXQSIZE 100//�����г���
typedef struct
{
	QElemType* base; // ��ʼ���Ķ�̬����洢�ռ�
	int front; // ͷָ��
	int rear; // βָ��
}SqQueue;

// ���еĳ�ʼ��
Status InitQueue(SqQueue* Q)
{
	Q->base = (QElemType*)malloc(MAXQSIZE * sizeof(QElemType)); // ��������ռ�
	if (!Q->base) // �洢����ʧ��
		exit(OVERFLOW);
	Q->front = Q->rear = 0; // ͷָ��βָ����Ϊ0 ����Ϊ��
	return OK;
}

// ����еĳ���
int QueueLength(SqQueue Q)
{
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

// �ж϶����Ƿ�Ϊ��
Status QueueEmpty(SqQueue Q)
{
	if (Q.front == Q.rear)
		TRUE;
	else
		FALSE;
}

// ѭ�����е�����㷨
// ʼ�տ�һ��λ�� �������ֶ����ӿ�
Status EnQueue(SqQueue* Q, QElemType e)
{
	if (Q->rear + 1 % MAXQSIZE == Q->front) // ����
		return ERROR;
	Q->base[Q->rear] = e; // ��Ԫ�ؼ����β
	Q->rear = (Q->rear + 1) % MAXSIZE; // ��βָ��+1
	return OK;
}

// ����
Status DeQueue(SqQueue* Q, QElemType* e)
{
	if (QueueEmpty(*Q)) // �ӿ� Q.front == Q.rear
		return ERROR;
	*e = Q->base[Q->front]; // �����ͷԪ��
	Q->front = (Q->front + 1) % MAXSIZE; // ��ͷָ�� + 1
	return OK;
}

// ȡ��ͷԪ��
SElemType GetHead(SqQueue Q)
{
	if (Q.front != Q.rear) // ���в�Ϊ��
		return Q.base[Q.front]; // ���ض�ͷָ��Ԫ�ص�ֵ ��ͷָ�벻��
}

// ���� �û��޷��������ö��еĳ��� ���˲���������
// �����е����Ͷ���
typedef struct Qnode
{
	QElemType data;
	struct Qnode* next;
}QNode, * QueuePtr;

typedef struct
{
	QueuePtr front; // ��ͷָ��
	QueuePtr rear; // ��βָ��
}LinkQueue;

// �����г�ʼ��
Status InitQueue(LinkQueue* Q)
{
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front)
		exit(OVERFLOW);
	Q->front->next = NULL;
	return OK;
}

// ����������
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

// ���
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

// ����
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

// �������еĶ�ͷԪ��
Status GetLHead(LinkQueue Q, QElemType* e)
{
	if (Q.front == Q.rear)
		return ERROR;
	*e = Q.front->next->data;
	return OK;
}