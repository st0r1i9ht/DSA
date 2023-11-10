#pragma once

#include <stdio.h>
#include <stdlib.h>

// 操作算法中用到的预定义常量和类型
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
// Status 是函数的类型 其值是函数结果状态代码
typedef int Status;

// 数据元素类型
typedef char ElemType;
typedef char SElemType;
typedef char QElemType;
typedef char TElemType;

// 函数声明
// 栈和队列
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