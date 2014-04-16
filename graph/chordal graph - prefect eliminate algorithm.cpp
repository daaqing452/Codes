/*
��ͼ��ͼ�����⻷�еĵ�����֮�䶼�б�

1	һ��ʼ���е��dfn������0
2	ÿ����dfn���ĵ�i������У���¼i�ڶ����е�λ��rank��������i�бߵĵ��dfn��+1
3	�ظ�2��ֱ�����е㶼�ڶ�����
4	ÿ��ö�ٶ����еĵ�i���ҳ���i�бߵĵ�ĵ㼯S����S���ҳ�rank���ĵ�j
5	��S'=S-{j}����j�뼯��S'�еĵ������ж��Ƿ��бߣ����j��S'�е�ĳ��û�бߣ����ͼ������ͼ
6	�ظ�4~5��ֱ��ö�������ж����е�

����2	����������dfn��ͬ�ĵ�����������������ɾ����O(1)
����5	�ж�����֮����û�бߣ����ù�ϣ

���Ӷ�	O(����+����)
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

const	int	f_Mod=12347, g_Mod=98763;
const	int	MAXN = 100005;
const	int	z[2][3] = {
				{1023456791LL, 1012345679LL, f_Mod},
				{1097654321LL, 1098765431LL, g_Mod}
			  };
struct	EDGE { int v, next; } w[MAXN<<1];
int	ww[MAXN], dfn[MAXN], rank[MAXN], f[f_Mod+1], g[g_Mod+1];
int	start[MAXN], pre[MAXN], next[MAXN], que[MAXN], quf[MAXN];
int	TEST, N, M, W;

int	GetHash(int u, int v, int lgr)
{
	return (((long long)u * z[lgr][0]) + ((long long)v * z[lgr][1])) % z[lgr][2];
}

void	AddLink(int i, int d)
{
	next[i] = start[d];
	start[d] = i;
	pre[next[i]] = i;
}

void	DeleteLink(int i, int d)
{
	next[pre[i]] = next[i];
	pre[next[i]] = pre[i];
	if (start[d] == i) start[d] = next[i];
	pre[i] = next[i] = 0;
}

int	main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	for (scanf("%d", &TEST); TEST--; )
	{
		memset(ww, 0, sizeof(ww)); W=0;
		memset(start, 0, sizeof(start));
		memset(rank, 0, sizeof(rank));
		memset(f, 0, sizeof(f));
		memset(g, 0, sizeof(g));
		
		scanf("%d%d", &N, &M);
		for (int i = 1, u, v; i <= M; ++i)
		{
			scanf("%d%d", &u, &v);
			w[++W].v = v; w[W].next = ww[u]; ww[u] = W;
			w[++W].v = u; w[W].next = ww[v]; ww[v] = W;
			f[GetHash(u, v, 0)] = f[GetHash(v, u, 0)] = 1;
			g[GetHash(u, v, 1)] = g[GetHash(v, u, 1)] = 1;
		}
		
		for (int i = 1; i <= N; ++i) AddLink(i, dfn[i] = 0);
		for (int k = 1, j = 0; k <= N; ++k)
		{
			for (; !start[j]; --j);
			int	u = que[k] = start[j];
			rank[u] = k;
			DeleteLink(u, dfn[u]);
			for (int i = ww[u]; i; i = w[i].next)
			{
				int	v = w[i].v;
				if (rank[v]) continue;
				DeleteLink(v, dfn[v]);
				AddLink(v, ++dfn[v]);
				j = max(j, dfn[v]);
			}
		}
		
		bool	Chordal = 1;
		for (int k = 1; k <= N && Chordal; ++k)
		{
			int	u = que[k], n = 0;
			for (int i = ww[u]; i; i = w[i].next)
			{
				int	v = w[i].v;
				if (rank[v] > rank[u]) continue;
				quf[++n] = v;
			}
			int	s = 1;
			for (int i = 2; i <= n; ++i)
				if (rank[quf[i]] > rank[quf[s]]) s = i;
			swap(quf[s], quf[n]);
			for (int i = 1; i < n && Chordal; ++i)
				Chordal &= (f[GetHash(quf[i], quf[n], 0)] && g[GetHash(quf[i], quf[n], 1)]);
		}
		
		if (Chordal) puts("��ͼ"); else puts("����ͼ");
	}
	
	return 0;
}
