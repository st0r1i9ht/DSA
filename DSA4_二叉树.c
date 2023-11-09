#include <stdio.h>
#include "DataStructure.h"

// 二叉树的性质
// 性质1 在第i层上至多有2的i-1个结点
// 性质2 深度为k的二叉树至多有2的k-1个结点
// 性质3 叶子数n0 度为2的节点数n2 n0 = n2 + 1
// 完全二叉树特点
// 特点1 叶子只能分布在层次最大的两层上
// 特点2 对任意结点 如果其右子树的最大层次为i 则其左子树的最大层次为i或i - 1
// 性质4 具有n个结点的完全二叉树的深度为[log2n] + 1 []表示取底即向下取整
// 性质5 如果对一颗有n个结点的完全二叉树(深度为[log2n] + 1)的结点按层序编号(从第1层到第[log2n] + 1层 每层从左到右) 则对任一结点i (1 <= i <= n) 有
// 1. i = 1 则结点i是二叉树的根 无双亲 i > 1 则其双亲是结点[i/2]
// 2. 如果2i > n 则结点i为叶子结点 无左孩子 2i <=n 其左孩子是结点2i
// 3. 如果2i + 1 > n 则结点i无左孩子 2i + 1 <= n 其右孩子是结点2i + 1

//二叉树顺序存储表示
#define MAXTSIZE 100
typedef TElemType SqBiTree[MAXTSIZE];
SqBiTree bt;
// 比较浪费空间 适合满二叉树和完全二叉树

// 二叉树的链式存储结构
typedef struct BiNode
{
	TElemType data;
	struct BiNode* lchild, * rchild; // 左右孩子指针
}BiNode, * BiTree;
// 必有2n链域 除根结点外每个结点都有一个双亲 所以有n - 1个非空链域 空指针数目 = 2n - (n - 1) = n + 1

// 三叉链表
typedef struct TriTNode
{
	TElemType data;
	struct TriTNode* lchild, * parent, * rchild;
}TriTNode, * TriTree;

/*
 * 遍历二叉树算法
 * 先序遍历 根左右DLR
 * 中序遍历 LDR
 * 后序遍历 LRD
 * 前中 中后可还原二叉树 前后不可还原
 * 算法分析
 * 时间效率 O(n) 每个结点只访问一次
 * 空间效率 O(n) 栈占用的最大辅助空间
 */
// 先序遍历
Status PreOrderTraverse(BiTree T)
{
	if (T == NULL) return OK;
	else
	{
		visit(T); // 自定义遍历操作
		PreOrderTraverse(T->lchild); // 递归遍历左子树
		PreOrderTraverse(T->rchild); // 递归遍历右子树
	}
}

// 中序
Status InOrderTraverse(BiTree T)
{
	if (T == NULL) return OK;
	else
	{
		InOrderTraverse(T->lchild); // 递归遍历左子树
		visit(T);
		InOrderTraverse(T->rchild); // 递归遍历右子树
	}
}

// 后序
Status PostOrderTraverse(BiTree T)
{
	if (T == NULL) return OK;
	else
	{
		PostOrderTraverse(T->lchild); // 递归遍历左子树
		PostOrderTraverse(T->rchild); // 递归遍历右子树
		visit(T);
	}
}
// 从递归的角度看 三种算法是完全相同的 或者说访问路径是相同的 只是访问结点的实际不同
// 从出发点到终点的路径上每个结点经过3次
// 第1次经过时访问=先序 2=中 3=后

// 遍历二叉树的非递归算法 以中序遍历为例
typedef struct StackNode
{
	SElemType data;
	struct StackNode* next;
}StackNode, * LinkStack;

LinkStack S;

Status InOrderTraverse_LS(BiTree T)
{
	BiTree p, q;
	InitStack_L(S);
	p = T;
	while (p || !StackEmpty_L(S))
	{
		if (p)
		{
			Push_L(S, p);
			p = p->lchild;
		}
		else
		{
			Pop_L(S, q);
			visit(q);
			p = q->rchild;
		} 
	}// while
	return OK;
}

// 二叉树的层次遍历
// 使用队列实现
// 也可以使用栈实现但较麻烦 未演示
// 从根结点开始 从上到下 从左到右访问每一个结点 每个结点仅访问一次
/*
 * 根结点入队
 * 队列非空 出队一个元素 并入队左右孩子 循环操作
 */
typedef struct
{
	BiNode* data; // 存放队中元素
	int front, rear; // 队头和队尾指针
}SqQueue; // 顺序循环队列类型

void LevelOrder(BiNode* b)
{
	BiNode* p;
	SqQueue* qu;
	InitQueue(qu); // 初始化队列
	EnQueue(qu, b); // 根结点指针进入队列
	while (!QueueEmpty(qu)) // 队不为空 则循环
	{
		DeQueue(qu, p); // 出队结点p
		visit(p); // 访问结点p
		if (p->lchild != NULL) // 有左孩子时将其进队
			EnQueue(qu, p->lchild);
		if (p->rchild != NULL) // 有右孩子时将其进队
			EnQueue(qu, p->rchild);
	}
}