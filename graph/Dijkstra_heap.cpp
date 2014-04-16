#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <cctype>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>

#define sqr(x) ((x) * (x))
#define minn(x,y) (x=(y)<(x)?(y):(x))
#define maxx(x,y) (x=(y)>(x)?(y):(x))
#define pluss(x,y) (x+=(y),x%=mod)
#define secon second

using namespace std;

typedef	long long	int64;

struct	edge
{
	int	v, c, next;
};

edge	w[1 << 20];
int	dist[1 << 20], N, M, H, W = 0, h[1 << 20], p[1 << 20], ww[1 << 20];


void	heapUp(int u)
{
	for (int i = p[u], j; i >> 1; i = j)
	{
		j = i >> 1;
		if (dist[h[i]] >= dist[h[j]]) return;
		swap(p[h[i]], p[h[j]]);
		swap(h[i], h[j]);
	}
}

void	heapDeleteHead()
{
	h[1] = h[H --]; p[h[1]] = 1;
	for (int i = 1, j; i << 1 <= H; i = j)
	{
		j = i << 1;
		if (j < H && dist[h[j + 1]] < dist[h[j]]) ++ j;
		if (dist[h[i]] <= dist[h[j]]) return;
		swap(p[h[i]], p[h[j]]);
		swap(h[i], h[j]);
	}
}

int	main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	
	scanf("%d%d", &N, &M);
	for (int i = 1, u, v, c; i <= M; ++ i)
	{
		scanf("%d%d%d", &u, &v, &c);
		w[++ W].v = v; w[W].c = c; w[W].next = ww[u]; ww[u] = W;
	}
	
	memset(dist, 60, sizeof(dist)); dist[1] = 0;
	for (int i = 1; i <= N; ++ i) h[i] = p[i] = i;
	H = N;
	for (int times = 0; times < N; ++ times)
	{
		if (!H) break;
		int	u = h[1];
		heapDeleteHead();
		
		for (int i = ww[u]; i; i = w[i].next)
		{
			int	v = w[i].v;
			if (dist[v] <= dist[u] + w[i].c) continue;
			dist[v] = dist[u] + w[i].c;
			heapUp(v);
		}
	}
	
	for (int i = 1; i <= N; ++ i) printf("%d\n", dist[i]);
	
	return 0;
}
