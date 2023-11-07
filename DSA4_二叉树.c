#include <stdio.h>
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