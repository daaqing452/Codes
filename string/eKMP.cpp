/*
----------Introduce----------

Extend_KMP就是扩展KMP
对于每个后缀St[i..N]，求出其与原串的最大公共前缀A[i]。




-----------Process-----------

i	枚举第i个后缀St[i..N]
k	使得k+A[k]最大的位置k
MaxLen	k+A[k]-1的位置
j	i-k+1的位置


一开始暴力求解A[2]，同时k=2。
然后要求出A[i]，要根据最大的k+A[k]求出


Case #1:
┏━┳━┳━┳━┳━┳━━━━┳━┳━┳━┳━┳━┳━┳━┳━┳━━━┓
┃  ┃  ┃  ┃j ┃  ┃j+A[j]-1┃  ┃k ┃  ┃  ┃i ┃  ┃  ┃  ┃MaxLen┃
┗━┻━┻━┻━┻━┻━━━━┻━┻━┻━┻━┻━┻━┻━┻━┻━━━┛
此时可知St[1..j] = St[k..i]（根据k的匹配可得）
此时St[j..j+A[j]-1] = St[1..A[j]]，则St[1..A[j]] = St[i..i+A[j]-1]
可是St[j..j+A[j]] <> St[1..A[j]+1]了，如果i+A[j]-1<Len，则一定St[1..A[j]+1] <> St[i..i+A[j]]
因此，A[i] = A[j]


Case #2:
┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━━━━┳━┳━┳━┳━┳━━━┓
┃  ┃  ┃  ┃j ┃  ┃  ┃  ┃k ┃  ┃j+A[j]-1┃i ┃  ┃  ┃  ┃MaxLen┃
┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━━━━┻━┻━┻━┻━┻━━━┛
此时同Case #1，St[1..j] = St[k..i]
此时St[j..j+MaxLen-i] = St[i..MaxLen]
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


int	A[1000005];
char	St[1000005];


int	main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	
	scanf("%s",St+1);
	int	N=strlen(St+1),k;
	memset(A,0,sizeof(A));
	for (A[k=2]=0;St[A[2]+1]==St[A[2]+2];++A[2]);
	
	for (int i=3;i<=N;++i)
	{
		int	MaxLen=k+A[k]-1,j=i-k+1;
		if (i+A[j]-1<MaxLen) A[i]=A[j]; else
		{
			int	p=max(0,MaxLen-i+1);
			for (;St[i+p]==St[1+p];++p);
			A[i]=p; k=i;
		}
	}
	
	return 0;
}
