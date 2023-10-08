#include "DataStructure.h"
#include <stdio.h>

// 串的顺序存储结构
#define MAXLEN 255
typedef struct
{
	char ch[MAXLEN + 1]; // 存储串的一维数组
	int length; // 串的当前长度
}SString;

// 串的链式存储结构 块链结构
#define CHUNKSIZE 80 // 块的大小自定义
typedef struct Chunk
{
	char ch[CHUNKSIZE];
	struct Chunk* next;
}Chunk;

typedef struct
{
	Chunk* head, * tail; // 串的头指针和尾指针
	int curlen; // 串的当前长度
}LString; // 字符串的块链结构

// BF算法
int Index_BF(SString S, SString T)
{
	int i = 1, j = 1;
	while (i <= S.length && j <= T.length)
	{
		if (S.ch[i] == T.ch[j]) // 主串和子串依次匹配下一个字符
		{
			++i;
			++j;
		}
		else // 主串 子串指针回溯 重新开始下一次匹配
		{
			i = i - j + 2; // (i - j + 1)回到上一次匹配的第一个字符 + 1 从下一个字符开始匹配
			j = 1;
		}
	}
	if (j >= T.length)
		return i - T.length; // 返回匹配的第一个字符下标
	else 
		return 0; // 模式匹配不成功
}

// pos BF 自定义开始位置
int Index_posBF(SString S, SString T, int pos)
{
	int i = pos, j = 1;
	while (i <= S.length && j <= T.length)
	{
		if (S.ch[i] == T.ch[j]) // 主串和子串依次匹配下一个字符
		{
			++i;
			++j;
		}
		else // 主串 子串指针回溯 重新开始下一次匹配
		{
			i = i - j + 2;
			j = 1;
		}
	}
	if (j >= T.length)
		return i - T.length; // 返回匹配的第一个字符下标
	else
		return 0; // 模式匹配不成功
}
/*
 * BF时间复杂度
 * n为主串长度 m为字串长度
 * 总比较次数为
 * (n-m)*m+m=(n-m+1)*m
 * 若m<<n 则时间复杂度为O(n*m)
 */

// KMP算法
// O(n+m)
// i不再需要回溯 j使用next算法回溯 大幅提高效率
// next数组的值只需要求一次
int* next;// 模式串长度大小的next数组
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

// 通过next值求nextval 算法很难理解 理解原理和方法 用的时候会写就够了
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
			j = next[j]; // i不变 j后退
	}
	if (j > T.length)
		return i - T.length; // 匹配成功
	else
		return 0; // 返回不匹配标志
}