#include "DataStructure.h"
#include <stdio.h>

// ����˳��洢�ṹ
#define MAXLEN 255
typedef struct
{
	char ch[MAXLEN + 1]; // �洢����һά���� ֻ����char
	int length; // ���ĵ�ǰ����
}SString;

// ������ʽ�洢�ṹ �����ṹ
#define CHUNKSIZE 80 // ��Ĵ�С�Զ���
typedef struct Chunk
{
	char ch[CHUNKSIZE];
	struct Chunk* next;
}Chunk;

typedef struct
{
	Chunk* head, * tail; // ����ͷָ���βָ��
	int curlen; // ���ĵ�ǰ����
}LString; // �ַ����Ŀ����ṹ

// BF�㷨
int Index_BF(SString S, SString T)
{
	int i = 1, j = 1;
	while (i <= S.length && j <= T.length)
	{
		if (S.ch[i] == T.ch[j]) // �������Ӵ�����ƥ����һ���ַ�
		{
			++i;
			++j;
		}
		else // ���� �Ӵ�ָ����� ���¿�ʼ��һ��ƥ��
		{
			i = i - j + 2; // (i - j + 1)�ص���һ��ƥ��ĵ�һ���ַ� + 1 ����һ���ַ���ʼƥ��
			j = 1;
		}
	}
	if (j >= T.length)
		return i - T.length; // ����ƥ��ĵ�һ���ַ��±�
	else 
		return 0; // ģʽƥ�䲻�ɹ�
}

// pos BF �Զ��忪ʼλ��
int Index_posBF(SString S, SString T, int pos)
{
	int i = pos, j = 1;
	while (i <= S.length && j <= T.length)
	{
		if (S.ch[i] == T.ch[j]) // �������Ӵ�����ƥ����һ���ַ�
		{
			++i;
			++j;
		}
		else // ���� �Ӵ�ָ����� ���¿�ʼ��һ��ƥ��
		{
			i = i - j + 2;
			j = 1;
		}
	}
	if (j >= T.length)
		return i - T.length; // ����ƥ��ĵ�һ���ַ��±�
	else
		return 0; // ģʽƥ�䲻�ɹ�
}
/*
 * BFʱ�临�Ӷ�
 * nΪ�������� mΪ�ִ�����
 * �ܱȽϴ���Ϊ
 * (n-m)*m+m=(n-m+1)*m
 * ��m<<n ��ʱ�临�Ӷ�ΪO(n*m)
 */

// KMP�㷨
// O(n+m)
// i������Ҫ���� jʹ��next�㷨���� ������Ч��
// next�����ֵֻ��Ҫ��һ��
int* next;// ģʽ�����ȴ�С��next����
void get_next(SString T, int* next)
{
	int i = 1;
	next[1] = 0;
	int j = 0;
	while (i < T.length)
	{
		if (j == 0 || T.ch[i] == T.ch[j])
		{
			++i;
			++j;
			next[i] = j;
		}
		else
			j = next[j];
	}
}

// ͨ��nextֵ��nextval �㷨������� ���ԭ��ͷ��� �õ�ʱ���д�͹���
void get_nextval(SString T, int* nextval[])
{
	int i = 1;
	nextval[1] = 0;
	int j = 0;
	while (i < T.length)
	{
		if (j == 0 || T.ch[i] == T.ch[j])
		{
			++i;
			++j;
			if (T.ch[i] != T.ch[j])
				nextval[i] = j;
			else
				nextval[i] = nextval[j];
		}
		else
			j = nextval[j];
	}
}

int Index_KMP(SString S, SString T, int pos)
{
	int i = pos, j = 1;
	while (i < S.length && j < T.length)
	{
		if (j == 0 || S.ch[i] == T.ch[j])
		{
			i++;
			j++;
		}
		else
			j = next[j]; // i���� j����
	}
	if (j > T.length)
		return i - T.length; // ƥ��ɹ�
	else
		return 0; // ���ز�ƥ���־
}

// һά����Ԫ��λ��
// a �׵�ַ
// L Ԫ����ռ�ռ�
// LOC(i) = i * L + a

// ��ά����Ԫ��λ��
// n ÿ�и���
// LOC(i, j) = (i * n + j) * L + a
#define elemtype char // ������������
typedef elemtype array[2][2];// �ȼ��������д��

typedef elemtype array1[2];
typedef array1 array2[2];

// ��/ҳ/��/��
// a[m1][m2][m3] ��άԪ�ظ���������Ϊm1, m2, m3
// LOC(i1, i2, i3) = a + (i1 * m2 * m3)ǰi1ҳ��Ԫ�ظ��� + (i2 * m3)��i1ҳ��ǰi2����Ԫ�ظ��� + i

// ��������ѹ���洢
/*
 * 1. �Գƾ���
 * aij = aji
 * ռ��n(n+1)/2�ռ�
 * Ԫ�ش洢λ��
 * ��ά������һά�����е�λ��a[k]
 * k = i(i - 1)/2 + j
 * 2. ���Ǿ���
 * �Խ������»����ϵ�Ԫ��ȫ��Ϊ���� �������Խ���
 * �洢����
 * �ظ�Ԫ��c����һ��Ԫ�ش洢�ռ� ��ռ��n(n+1)/2 + 1��Ԫ�ؿռ�
 * �����Ǿ���洢λ�� i >= j: i(i - 1)/2 + j; i < j : n(n + 1)/2 + 1
 * �����Ǿ���洢λ�� i <= j: (i - 1)(2n - i + 2)/2 + j - i + 1; i < j : n(n + 1)/2 + 1
 * 3. �ԽǾ���
 * �Խ���֮���Ԫ��ȫΪ0
 * 4. ϡ�����
 * ����m*n�ľ�������t������Ԫ�� ��� = t / (m * n) ���� <= 0.05ʱΪϡ�����
 * ��Ԫ��˳�򷨽�Լ�ռ�
 * {(i, j , value)}
 * �±�0��λ��(������, ������, ����Ԫ���ܸ���)
 * �ŵ� ���� ���ڽ�������˳����ľ�������
 * ȱ�� ���������ȡ
 * ʮ�־���
 * �ŵ� ������ɾ��
 * ��� i, j, value downͬ����һԪ�� rightͬ����һԪ�� ��һԪ��û�з���Ԫ��ָ�����ÿ�
 * ͷָ�� row col ָ�����е��׽��
 * 
 */