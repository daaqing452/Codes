/*
----------Introduce----------

����ÿ��i�������iΪ�е������Ĵ���




-----------Process-----------

i	ö�ٵ�i����׺St[i..N]
k	ʹ��k+A[k]����λ��k
k'	k-A[k]��λ��
MaxLen	k+A[k]��λ��
j	k-(i-k)��λ�ã���i��kΪ�Գ���Գƹ�ȥ��λ��


һ��ʼA[1]=1��k=1��
Ȼ��Ҫ���A[i]��Ҫ��������k+A[k]���


Case #1:
�����ש��ש��ש��ש��ש��ש��ש��ש��ש��ש��ש��ש��ש��ש�������
��k'��  ��  ��  ��j ��  ��  ��k ��  ��  ��i ��  ��  ��  ��MaxLen��
�����ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ�������
����St=[k..k'] = St[k..MaxLen]
��i+A[j] < MaxLen��j-A[j] > k'������St[k-A[k]..k+A[k]]�Ͱ�����St[j-A[j]..j+A[j]]
����St[j+A[j]..j-A[j]] = St[i-A[j]..i+A[j]]����A[j]�����ܸ�����
��Ϊi��j��St[k-A[k]..k+A[k]]����������ǵȼ۵�
����A[i] = A[j] 


Case #2:
�����ש��ש��ש��ש��ש��ש��ש��ש��ש��ש��ש��ש��ש��ש�������
��k'��  ��  ��  ��j ��  ��  ��k ��  ��  ��i ��  ��  ��  ��MaxLen��
�����ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ�������
ͬCase #1��St=[k..k'] = St[k..MaxLen]
��i+A[j] >= MaxLen��j-A[j] <= k'��ͬCase #1��A[i]���� >= A[j]
����MaxLen֮��Ĳ���һ����֪������i+A[j]+1��ʼ����ƥ��
���A[i]�󣬱ض�i+A[i] >= MaxLen = k+A[k]����k := i


Case #3:
�����ש��ש��ש��ש��ש��ש��ש��ש��ש��ש��ש��ש��ש������ש���
��  ��k'��  ��  ��  ��  ��  ��k ��  ��  ��  ��  ��  ��MaxLen��i ��
�����ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ������ߩ���
��ʱk�Ѿ�����Ϊ���ˣ���i��ʼ����ƥ��
���A[i]�󣬱ض�i+A[i] >= i > MaxLen = k+A[k]����k := i��


�������ܸ��Ӷ���O(N)���ˡ�

*/


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;


int		A[1000005];
char		St[1000005];


int	main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	
	scanf("%s",St+1);
	int	N=strlen(St+1),k;
	memset(A,0,sizeof(A));
	for (int i=2,k=1;i<=N;++i)
	{
		int	MaxLen=k+A[k],j=k-(i-k);
		if (i<=MaxLen) A[i]=min(A[j],MaxLen-i); else A[i]=0;
		if (i+A[i]>=MaxLen)
		{
			for (;St[i-A[i]]==St[i+A[i]];) ++A[i];
			--A[i]; k=i;
		}
	}
	
	return 0;
}
