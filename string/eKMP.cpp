/*
----------Introduce----------

Extend_KMP就是扩展KMP
对于每个后缀S[i..N]，求出其与原串的最大公共前缀A[i]。




-----------Process-----------

i	枚举第i个后缀S[i..N]
k	使得k+A[k]最大的位置k
MaxLen	k+A[k]-1的位置
j	i-k+1的位置


一开始暴力求解A[2]，同时k=2。
然后要求出A[i]，要根据最大的k+A[k]求出


Case #1:
┏━┳━┳━┳━┳━┳━━━━┳━┳━┳━┳━┳━┳━┳━┳━┳━━━┓
┃  ┃  ┃  ┃j ┃  ┃j+A[j]-1┃  ┃k ┃  ┃  ┃i ┃  ┃  ┃  ┃MaxLen┃
┗━┻━┻━┻━┻━┻━━━━┻━┻━┻━┻━┻━┻━┻━┻━┻━━━┛
此时可知S[1..j] = S[k..i]（根据k的匹配可得）
此时S[j..j+A[j]-1] = S[1..A[j]]，则S[1..A[j]] = S[i..i+A[j]-1]
可是S[j..j+A[j]] <> S[1..A[j]+1]了，如果i+A[j]-1<Len，则一定S[1..A[j]+1] <> S[i..i+A[j]]
因此，A[i] = A[j]


Case #2:
┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━━━━┳━┳━┳━┳━┳━━━┓
┃  ┃  ┃  ┃j ┃  ┃  ┃  ┃k ┃  ┃j+A[j]-1┃i ┃  ┃  ┃  ┃MaxLen┃
┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━━━━┻━┻━┻━┻━┻━━━┛
此时同Case #1，S[1..j] = S[k..i]
此时S[j..j+MaxLen-i] = S[i..MaxLen]
但是MaxLen之后的部分一无所知，A[i]>=MaxLen-i+1，剩下的从MaxLen继续暴力匹配
求出A[i]后，必定i+A[i] > MaxLen = k+A[k]，则k := i


Case #3:
┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━━━┳━┓
┃  ┃  ┃  ┃j ┃  ┃  ┃  ┃k ┃  ┃  ┃  ┃  ┃  ┃MaxLen┃i ┃
┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━━━┻━┛
此时k已经无能为力了，从i开始暴力匹配
求出A[i]后，必定i+A[i] >= i > MaxLen = k+A[k]，则k := i


这样，总复杂度是O(N)的了。

*/


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

int A[1000005];
char S[1000005];

int	main() {
	scanf("%s", S + 1);
	int	N = strlen(S + 1), k;
	memset(A, 0, sizeof(A));
	for (A[k = 2] = 0; S[A[2] + 1] == S[A[2] + 2]; ++A[2]);
	for (int i = 3; i <= N; ++i) {
		int	maxLen = k + A[k] - 1, j = i - k + 1;
		if (i + A[j] - 1 < maxLen) A[i] = A[j]; else {
			int	p = max(0, maxLen - i + 1);
			for (; S[i + p] == S[1 + p]; ++p);
			A[i] = p; k = i;
		}
	}
	return 0;
}
