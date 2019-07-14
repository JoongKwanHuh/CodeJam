#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define MAXN 60
#define TRUE  1
#define FALSE 0

int A[MAXN];
int A2[MAXN];
int A2Cnt[MAXN];
int newn;

vector <long long> MemCnt[MAXN];
vector <int> MemSum[MAXN];

long long CountOdd(int aSum, int aSize, int aIdx);
bool CheckOdd(int aSum);

int main()
{
	int i, j, k, n, T;
	long long Result;
	scanf("%d", &T);
	for (i = 0; i < T; i++)
	{
		scanf("%d", &n);
		for (j = 0; j < n; j++)
		{
			scanf("%d", &A[j]);
			A2Cnt[j] = 0;
		}
		Result = 0LL;
		sort(A, A + n);
		A2[0] = A[0];
		A2Cnt[0] = 1;
		newn = 1;
		for (j = 1; j < n; j++)
		{
			if (A2[newn - 1] == A[j])
			{
				A2Cnt[newn - 1]++;
			}
			else
			{
				A2Cnt[newn]++;
				A2[newn++] = A[j];
			}
		}
		for (k = 0; k < newn; k++)
		{
			MemCnt[k].clear();
			MemSum[k].clear();
		}

		if (A2[0] == 0)
		{
			Result = CountOdd(0, newn, 0) * (long long)(A2Cnt[0]+1);

		}
		else
		{
			for (k = 0; k <= A2Cnt[0]; k++)
				Result += CountOdd(A2[0] * k, newn, 0);
		}

		printf("%lld\n", Result);

	}
	return 0;
}

long long CountOdd(int aSum, int aSize, int aIdx)
{
	long long re = 0LL;
	long long tmp;
	int i, j;
	if (aIdx+1 == aSize)
	{
		if (CheckOdd(aSum))
			return 1LL;
		else
			return 0LL;
	}
	else
	{
		for (i = 0; i <= A2Cnt[aIdx + 1]; i++)
		{
			int p = find(MemSum[aIdx+1].begin(), MemSum[aIdx+1].end(), aSum+A2[aIdx+1]*i) - MemSum[aIdx+1].begin();
			if (p < MemSum[aIdx + 1].size())
			{
				re += MemCnt[aIdx+1][p];
			}
			else
			{
				MemSum[aIdx + 1].push_back(aSum + A2[aIdx + 1] * i);
				MemCnt[aIdx + 1].push_back(CountOdd(aSum + A2[aIdx + 1] * i, aSize, aIdx + 1));
				re += MemCnt[aIdx+1][MemCnt[aIdx+1].size()-1];
			}
//			printf("aSum = %d, aIdx = %d, i = %d, re = %lld\n", aSum, aIdx, i, re);
		}
		return re;
	}
}

bool CheckOdd(int aSum)
{
	int S = 0;
	int remain = aSum;
	while (remain)
	{
		if (remain % 2)
			S++;
		remain = (int)(remain / 10);
	}
	if (S % 2)
		return TRUE;
	else
		return FALSE;
}

