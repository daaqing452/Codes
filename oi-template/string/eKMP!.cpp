/*
----------Introduce----------

对于每个i，求出以i为中点的最长回文串。




-----------Process-----------

i	枚举第i个后缀S[i..N]
k	使得k+A[k]最大的位置k
k'	k-A[k]的位置
MaxLen	k+A[k]的位置
j	k-(i-k)的位置，即i以k为对称轴对称过去的位置


一开始A[1]=1，k=1。
然后要求出A[i]，要根据最大的k+A[k]求出


Case #1:
┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━━━┓
┃k'┃  ┃  ┃  ┃j ┃  ┃  ┃k ┃  ┃  ┃i ┃  ┃  ┃  ┃MaxLen┃
┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━━━┛
明显S=[k..k'] = S[k..MaxLen]
若i+A[j] < MaxLen，j-A[j] > k'，于是S[k-A[k]..k+A[k]]就包含了S[j-A[j]..j+A[j]]
所以S[j+A[j]..j-A[j]] = S[i-A[j]..i+A[j]]，且A[j]不可能更大了
因为i和j在S[k-A[k]..k+A[k]]这段区间中是等价的
所以A[i] = A[j] 


Case #2:
┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━━━┓
┃k'┃  ┃  ┃  ┃j ┃  ┃  ┃k ┃  ┃  ┃i ┃  ┃  ┃  ┃MaxLen┃
┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━━━┛
同Case #1，S=[k..k'] = S[k..MaxLen]
若i+A[j] >= MaxLen，j-A[j] <= k'，同Case #1，A[i]至少 >= A[j]
但是MaxLen之后的部分一无所知，故由i+A[j]+1开始暴力匹配
求出A[i]后，必定i+A[i] >= MaxLen = k+A[k]，则k := i


Case #3:
┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━━━┳━┓
┃  ┃k'┃  ┃  ┃  ┃  ┃  ┃k ┃  ┃  ┃  ┃  ┃  ┃MaxLen┃i ┃
┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━━━┻━┛
此时k已经无能为力了，从i开始暴力匹配
求出A[i]后，必定i+A[i] >= i > MaxLen = k+A[k]，则k := i。


这样，总复杂度是O(N)的了。

*/


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int A[1000005];
char S[1000005];

int	main() {
	scanf("%s", S + 1);
	int	N = strlen(S + 1), k;
	memset(A, 0, sizeof(A));
	for (int i = 2, k = 1; i <= N; ++i) {
		int	maxLen = k + A[k], j = k - (i - k);
		if (i <= maxLen) A[i] = min(A[j], maxLen - i); else A[i] = 0;
		if (i + A[i] >= maxLen) {
			for (; S[i - A[i]] == S[i + A[i]]; ) ++A[i];
			--A[i]; k=i;
		}
	}
	return 0;
}
