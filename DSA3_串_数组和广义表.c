#include "DataStructure.h"
#include <stdio.h>

// ����˳��洢�ṹ
#define MAXLEN 255
typedef struct
{
	char ch[MAXLEN + 1]; // �洢����һά����
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