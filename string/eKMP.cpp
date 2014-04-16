/*
----------Introduce----------

Extend_KMP������չKMP
����ÿ����׺St[i..N]���������ԭ������󹫹�ǰ׺A[i]��




-----------Process-----------

i	ö�ٵ�i����׺St[i..N]
k	ʹ��k+A[k]����λ��k
MaxLen	k+A[k]-1��λ��
j	i-k+1��λ��


һ��ʼ�������A[2]��ͬʱk=2��
Ȼ��Ҫ���A[i]��Ҫ��������k+A[k]���


Case #1:
�����ש��ש��ש��ש��ש��������ש��ש��ש��ש��ש��ש��ש��ש��ש�������
��  ��  ��  ��j ��  ��j+A[j]-1��  ��k ��  ��  ��i ��  ��  ��  ��MaxLen��
�����ߩ��ߩ��ߩ��ߩ��ߩ��������ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ�������
��ʱ��֪St[1..j] = St[k..i]������k��ƥ��ɵã�
��ʱSt[j..j+A[j]-1] = St[1..A[j]]����St[1..A[j]] = St[i..i+A[j]-1]
����St[j..j+A[j]] <> St[1..A[j]+1]�ˣ����i+A[j]-1<Len����һ��St[1..A[j]+1] <> St[i..i+A[j]]
��ˣ�A[i] = A[j]


Case #2:
�����ש��ש��ש��ש��ש��ש��ש��ש��ש��������ש��ש��ש��ש��ש�������
��  ��  ��  ��j ��  ��  ��  ��k ��  ��j+A[j]-1��i ��  ��  ��  ��MaxLen��
�����ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��������ߩ��ߩ��ߩ��ߩ��ߩ�������
��ʱͬCase #1��St[1..j] = St[k..i]
��ʱSt[j..j+MaxLen-i] = St[i..MaxLen]
����MaxLen֮��Ĳ���һ����֪��A[i]>=MaxLen-i+1��ʣ�µĴ�MaxLen��������ƥ��
���A[i]�󣬱ض�i+A[i] > MaxLen = k+A[k]����k := i


Case #3:
�����ש��ש��ש��ש��ש��ש��ש��ש��ש��ש��ש��ש��ש������ש���
��  ��  ��  ��j ��  ��  ��  ��k ��  ��  ��  ��  ��  ��MaxLen��i ��
�����ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ������ߩ���
��ʱk�Ѿ�����Ϊ���ˣ���i��ʼ����ƥ��
���A[i]�󣬱ض�i+A[i] >= i > MaxLen = k+A[k]����k := i


�������ܸ��Ӷ���O(N)���ˡ�

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
