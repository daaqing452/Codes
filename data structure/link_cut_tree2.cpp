#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;


const	int	maxn = 20005;
int	l[maxn], r[maxn], p[maxn], c[maxn], f[maxn][2], b[maxn], que[maxn];
char	st[9];
int	N, Q;


void	Renew(int x)
{
	f[x][0] = f[l[x]][0] + f[r[x]][0];
	f[x][1] = f[l[x]][1] + f[r[x]][1];
	f[x][c[x]] ++;
}

void	Updata(int x)
{
	if (!b[x]) return;
	b[l[x]] ^= 1; b[r[x]] ^= 1;
	swap(l[x], r[x]);
	b[x] = 0;
}

bool	Root(int x)
{
	int	y = p[x];
	if (!y) return 1;
	if (l[y] != x && r[y] != x) return 1;
	return 0;
}

void	Zig(int x)
{
	int	y = p[x], z = p[y], w = l[x];
	p[w] = y; r[y] = w;
	p[y] = x; l[x] = y;
	p[x] = z;
	if (l[z] == y) l[z] = x;
	if (r[z] == y) r[z] = x;
	Renew(y);
	Renew(x);
}

void	Zag(int x)
{
	int	y = p[x], z = p[y], w = r[x];
	p[w] = y; l[y] = w;
	p[y] = x; r[x] = y;
	p[x] = z;
	if (l[z] == y) l[z] = x;
	if (r[z] == y) r[z] = x;
	Renew(y);
	Renew(x);
}

void	Splay(int x)
{
	int	m = 0;
	for (int i = x; ; i = p[i])
	{
		que[++ m] = i;
		if (Root(i)) break;
	}
	for (int i = m; i; -- i) Updata(que[i]);
	
	for (; !Root(x); )
	{
		int	y = p[x], z = p[y];
		if (Root(y))
			if (l[y] == x) Zag(x); else Zig(x);
		else
			if (l[y] == x)
				if (l[z] == y) Zag(y), Zag(x); else Zag(x), Zig(x);
			else
				if (r[z] == y) Zig(y), Zig(x); else Zig(x), Zag(x);
	}
}

void	Access(int x)
{
	for (int y = 0; x; x = p[x])
	{
		Splay(x);
		r[x] = y;
		Renew(x);
		y = x;
	}
}

int	GetRoot(int x)
{
	Access(x);
	Splay(x);
	for (; ; x = l[x]) if (!l[x]) return x;
}

int	GetLca(int w, int x)
{
	if (w == x) return w;
	if (GetRoot(w) != GetRoot(x)) return -1;
	Access(w);
	for (int y = 0; x; x = p[x])
	{
		Splay(x);
		r[x] = y;
		Renew(x);
		if (!p[x]) return x;
		y = x;
	}
}

int	main()
{
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
	
	scanf("%d%d", &N, &Q);
	for (int i = 1; i <= N; ++ i)
	{
		scanf("%s", st);
		c[i] = (st[0] == 'W');
		Renew(i);
	}
	
	for (int q = 1, u, v; q <= Q; ++ q)
	{
		scanf("%s", st);
		if (!strcmp(st, "add"))
		{
			scanf("%d%d", &u, &v);
			int	lca = GetLca(u, v);
			if (lca != -1) continue;
			Access(v); Splay(v);
			r[v] = l[v]; l[v] = 0; b[r[v]] ^= 1;
			p[v] = u;
		} else
		if (!strcmp(st, "del"))
		{
			scanf("%d%d", &u, &v);
			int	lca = GetLca(u, v);
			if (lca == -1) continue;
			Access(u); Splay(v);
			if (p[v] == u && !l[v]) { p[v] = 0; continue; }
			Access(v); Splay(u);
			if (p[u] == v && !l[u]) { p[u] = 0; continue; }
			//printf("ERROR on %d\n", q);
		} else
		if (!strcmp(st, "set"))
		{
			scanf("%d%s", &u, &st);
			Access(u); Splay(u);
			c[u] = (st[0] == 'W');
			Renew(u);
		} else
		if (!strcmp(st, "query"))
		{
			scanf("%d%d", &u, &v);
			int	lca = GetLca(u, v);
			if (lca == -1) { puts("-1"); continue; }
			
			int	ret[2] = {0, 0};
			if (u != lca)
			{
				Access(u); Splay(u);
				int	x = l[u];
				p[x] = 0;
				Splay(lca);
				ret[0] += f[r[lca]][0];
				ret[1] += f[r[lca]][1];
				Splay(x);
				p[x] = u;
				
				ret[c[u]] ++;
			}
			if (v != lca)
			{
				Access(v); Splay(v);
				int	x = l[v];
				p[x] = 0;
				Splay(lca);
				ret[0] += f[r[lca]][0];
				ret[1] += f[r[lca]][1];
				Splay(x);
				p[x] = v;
				
				ret[c[v]] ++;
			}
			ret[c[lca]] ++;
			printf("%d %d\n", ret[0], ret[1]);
		} else
			printf("ERROR on %d\n", q);
	}
	
	return 0;
}
