#pragma once

#include <stdio.h>
#include <stdlib.h>

// �����㷨���õ���Ԥ���峣��������
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
// Status �Ǻ��������� ��ֵ�Ǻ������״̬����
typedef int Status;

// ����Ԫ������
typedef char ElemType;
typedef char SElemType;
typedef char QElemType;
typedef char TElemType;

// ��������
// ջ�Ͷ���
Status InitStack(SqStack* S);
Status StackEmpty(SqStack S);
Status ClearStack(SqStack* S);
Status DestroyStack(SqStack* S);
Status Push(SqStack* S, SElemType e);
Status Pop(SqStack* S, SElemType* e);
void InitStack_L(LinkStack* S);
Status StackEmpty_L(LinkStack S);
Status Push_L(LinkStack S, SElemType e);
Status Pop_L(LinkStack S, SElemType* e);
SElemType GetTop(LinkStack S);
Status InitQueue(SqQueue* Q);
int QueueLength(SqQueue Q);
Status EnQueue(SqQueue* Q, QElemType e);
Status DeQueue(SqQueue* Q, QElemType* e);
SElemType GetHead(SqQueue Q);
Status QueueEmpty(SqQueue Q);