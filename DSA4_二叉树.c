#include "DataStructure.h"

// ������������
// ����1 �ڵ�i����������2��i-1�����
// ����2 ���Ϊk�Ķ�����������2��k-1�����
// ����3 Ҷ����n0 ��Ϊ2�Ľڵ���n2 n0 = n2 + 1
// ��ȫ�������ص�
// �ص�1 Ҷ��ֻ�ֲܷ��ڲ������������
// �ص�2 �������� ������������������Ϊi �����������������Ϊi��i - 1
// ����4 ����n��������ȫ�����������Ϊ[log2n] + 1 []��ʾȡ�׼�����ȡ��
// ����5 �����һ����n��������ȫ������(���Ϊ[log2n] + 1)�Ľ�㰴������(�ӵ�1�㵽��[log2n] + 1�� ÿ�������) �����һ���i (1 <= i <= n) ��
// 1. i = 1 ����i�Ƕ������ĸ� ��˫�� i > 1 ����˫���ǽ��[i/2]
// 2. ���2i > n ����iΪҶ�ӽ�� ������ 2i <=n �������ǽ��2i
// 3. ���2i + 1 > n ����i������ 2i + 1 <= n ���Һ����ǽ��2i + 1

//������˳��洢��ʾ
#define MAXTSIZE 100
typedef TElemType SqBiTree[MAXTSIZE];
SqBiTree bt;
// �Ƚ��˷ѿռ� �ʺ�������������ȫ������

// ����������ʽ�洢�ṹ
typedef struct BiNode
{
	TElemType data;
	struct BiNode* lchild, * rchild; // ���Һ���ָ��
}BiNode, * BiTree;
// ����2n���� ���������ÿ����㶼��һ��˫�� ������n - 1���ǿ����� ��ָ����Ŀ = 2n - (n - 1) = n + 1

// ��������
typedef struct TriTNode
{
	TElemType data;
	struct TriTNode* lchild, * parent, * rchild;
}TriTNode, * TriTree;

/*
 * �����������㷨
 * ������� ������DLR
 * ������� LDR
 * ������� LRD
 * ǰ�� �к�ɻ�ԭ������ ǰ�󲻿ɻ�ԭ
 * �㷨����
 * ʱ��Ч�� O(n) ÿ�����ֻ����һ��
 * �ռ�Ч�� O(n) ջռ�õ�������ռ�
 */
// �������
Status PreOrderTraverse(BiTree T)
{
	if (T == NULL) return OK;
	else
	{
		visit(T); // �Զ����������
		PreOrderTraverse(T->lchild); // �ݹ����������
		PreOrderTraverse(T->rchild); // �ݹ����������
	}
}

// ����
Status InOrderTraverse(BiTree T)
{
	if (T == NULL) return OK;
	else
	{
		InOrderTraverse(T->lchild); // �ݹ����������
		visit(T);
		InOrderTraverse(T->rchild); // �ݹ����������
	}
}

// ����
Status PostOrderTraverse(BiTree T)
{
	if (T == NULL) return OK;
	else
	{
		PostOrderTraverse(T->lchild); // �ݹ����������
		PostOrderTraverse(T->rchild); // �ݹ����������
		visit(T);
	}
}
// �ӵݹ�ĽǶȿ� �����㷨����ȫ��ͬ�� ����˵����·������ͬ�� ֻ�Ƿ��ʽ���ʵ�ʲ�ͬ
// �ӳ����㵽�յ��·����ÿ����㾭��3��
// ��1�ξ���ʱ����=���� 2=�� 3=��

// �����������ķǵݹ��㷨 ���������Ϊ��
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

// �������Ĳ�α���
// ʹ�ö���ʵ��
// Ҳ����ʹ��ջʵ�ֵ����鷳 δ��ʾ
// �Ӹ���㿪ʼ ���ϵ��� �����ҷ���ÿһ����� ÿ����������һ��
/*
 * ��������
 * ���зǿ� ����һ��Ԫ�� ��������Һ��� ѭ������
 */
typedef struct
{
	BiNode* data; // ��Ŷ���Ԫ��
	int front, rear; // ��ͷ�Ͷ�βָ��
}SqQueue; // ˳��ѭ����������

void LevelOrder(BiNode* b)
{
	BiNode* p;
	SqQueue* qu;
	InitQueue(qu); // ��ʼ������
	EnQueue(qu, b); // �����ָ��������
	while (!QueueEmpty(qu)) // �Ӳ�Ϊ�� ��ѭ��
	{
		DeQueue(qu, p); // ���ӽ��p
		visit(p); // ���ʽ��p
		if (p->lchild != NULL) // ������ʱ�������
			EnQueue(qu, p->lchild);
		if (p->rchild != NULL) // ���Һ���ʱ�������
			EnQueue(qu, p->rchild);
	}
}

// ���������� DLR
Status CreateBiTree(BiTree T)
{
	char ch;
	if ((ch = getchar()) == "#")
		T = NULL;
	else
	{
		if (!(T = (BiNode*)malloc(sizeof(BiNode))))
			exit(OVERFLOW);
		T->data = ch;
		CreateBiTree(T->lchild); // ����������
		CreateBiTree(T->rchild); // ����������
	}
	return OK;
}

// ���ƶ�����
// ����ǿ��� �ݹ����
// ���������½��ռ� ���Ƹ��ڵ� �ݹ鸴����������
int Copy(BiTree T, BiTree NewT)
{
	if (T == NULL) // ��������0
	{
		NewT = (BiTree)malloc(sizeof(BiNode));
		return 0;
	}
	else
	{
		NewT = (BiTree)malloc(sizeof(BiNode));
		NewT->data = T->data;
		Copy(T->lchild, NewT->lchild);
		Copy(T->rchild, NewT->rchild);
	}
}

// ������������
// ����ǿ��� �����Ϊ0
// ���� �ݹ��������������ȼ�Ϊm, �ݹ��������������ȼ�Ϊn, �������������Ϊm��n�ϴ���+1
int Depth(BiTree T)
{
	if (T == NULL)
		return 0;
	else
	{
		int m = Depth(T->lchild);
		int n = Depth(T->rchild);
		if (m > n)
			return(m + 1);
		else
			return(n + 1);
	}
}

// ����������������
// ����ǿ��� �������Ϊ0
// ���� ������Ϊ�������Ľ����� + �������Ľ����� + 1 L+R+D
int NodeCount(BiTree T)
{
	if (T == NULL)
		return 0;
	else
		return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;
}

// �����������Ҷ������
// ����ǿ��� �������Ϊ0
// ���� ������Ϊ������������ + �������Ľ�����
int LeafCount(BiTree T)
{
	if (T == NULL)
		return 0; // ��������0
	if (T->lchild == NULL && T->rchild == NULL)
		return 1; // Ҷ�ӽ�㷵��1
	else return LeafCount(T->lchild) + LeafCount(T->rchild);
}

/* ����������
 * ���ĳ��������Ϊ�� ���յ�����ָ�����Ϊָ����ǰ��
 * ���ĳ�����Һ���Ϊ�� ���յ��Һ���ָ�����Ϊָ������
 * �ı�ָ���ָ���Ϊ���� �������Ķ�������Ϊ����������Threaded Binary Tree �ù��̳�Ϊ������
 * ltag/rtag = 0 lchild/rchildָ����/�Һ��� tag=1ָ��ǰ�����
 * ������ͷ��������������
 * ������������ʣ����β����ָ�������� ����һ��ͷ���
 * lt = 0 lcָ������ rt = 1 rcָ����������е����һ�����
 * ���������е�һ������lc�����һ������rcָ��ͷ���
 */
// �����������洢�ṹ
typedef struct BiThrNode
{
	TElemType data;
	int ltag, rtag;
	struct BiThrNode* lchild, * rchild;
}BiThrNode, * BiThrTree;