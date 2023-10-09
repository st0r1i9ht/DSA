#include "DataStructure.h"
#include <stdio.h>

// 串的顺序存储结构
#define MAXLEN 255
typedef struct
{
	char ch[MAXLEN + 1]; // 存储串的一维数组 只能是char
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

// 一维数组元素位置
// a 首地址
// L 元素所占空间
// LOC(i) = i * L + a

// 二维数组元素位置
// n 每行个数
// LOC(i, j) = (i * n + j) * L + a
#define elemtype char // 任意数据类型
typedef elemtype array[2][2];// 等价于下面的写法

typedef elemtype array1[2];
typedef array1 array2[2];

// 本/页/行/列
// a[m1][m2][m3] 各维元素个数的数量为m1, m2, m3
// LOC(i1, i2, i3) = a + (i1 * m2 * m3)前i1页总元素个数 + (i2 * m3)第i1页的前i2行总元素个数 + i

// 特殊矩阵的压缩存储
/*
 * 1. 对称矩阵
 * aij = aji
 * 占用n(n+1)/2空间
 * 元素存储位置
 * 二维数组在一维数组中的位置a[k]
 * k = i(i - 1)/2 + j
 * 2. 三角矩阵
 * 对角线以下或以上的元素全部为常数 不包括对角线
 * 存储方法
 * 重复元素c共享一个元素存储空间 共占用n(n+1)/2 + 1个元素空间
 * 下三角矩阵存储位置 i >= j: i(i - 1)/2 + j; i < j : n(n + 1)/2 + 1
 * 上三角矩阵存储位置 i <= j: (i - 1)(2n - i + 2)/2 + j - i + 1; i < j : n(n + 1)/2 + 1
 * 3. 对角矩阵
 * 对角线之外的元素全为0
 * 4. 稀疏矩阵
 * 设在m*n的矩阵中有t个非零元素 令σ = t / (m * n) 当σ <= 0.05时为稀疏矩阵
 * 三元组顺序法节约空间
 * {(i, j , value)}
 * 下标0的位置(总行数, 总列数, 非零元素总个数)
 * 优点 有序 便于进行依行顺序处理的矩阵运算
 * 缺点 不能随机存取
 * 十字矩阵法
 * 优点 灵活插入删除
 * 结点 i, j, value down同列下一元素 right同行下一元素 下一元素没有非零元素指针域置空
 * 头指针 row col 指向行列的首结点
 * 
 */