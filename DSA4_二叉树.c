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