#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;


const	int	maxn = 50005;
struct	pii
{
	int	edg, cnt;
};
int	l[maxn], r[maxn], s[maxn], p[maxn], e[maxn], f[maxn], g[maxn];
int	que[maxn];
int	N, Q;


inline	int	h(int x)
{
	return 1 << x - 1;
}

inline	void	clear()
{
	l[0] = r[0] = s[0] = e[0] = f[0] = g[0] = p[0] = 0;
}

void	Renew(int x)
{
	clear();
	s[x] = s[l[x]] + s[r[x]] + 1;
	f[x] = f[l[x]] | f[r[x]];
	f[x] |= e[x];
}

void	Zig(int x)
{
	clear();
	int	y = p[x], z = p[y], b = l[x];
	p[b] = y; r[y] = b;
	p[y] = x; l[x] = y;
	p[x] = z;
	if (l[z] == y) l[z] = x;
	if (r[z] == y) r[z] = x;
	Renew(y); Renew(x);
}

void	Zag(int x)
{
	clear();
	int	y = p[x], z = p[y], b = r[x];
	p[b] = y; l[y] = b;
	p[y] = x; r[x] = y;
	p[x] = z;
	if (l[z] == y) l[z] = x;
	if (r[z] == y) r[z] = x;
	Renew(y); Renew(x);
}

bool	Root(int x)
{
	int	y = p[x];
	return !(l[y] == x || r[y] == x);
}

void	Updata(int u)
{
	if (!g[u]) return;
	e[l[u]] = f[l[u]] = g[l[u]] = g[u];
	e[r[u]] = f[r[u]] = g[r[u]] = g[u];
	g[u] = 0;
}

void	Splay(int x, int stop)
{
	clear();
	if (x == stop) return;
	
	int	QUE = 0, u = x;
	for (; !Root(u); u = p[u])
	{
		if (u == stop) break;
		que[++ QUE] = u;
	}
	que[++ QUE] = u;
	for (int i = QUE; i; -- i) Updata(que[i]);
	
	for (; !Root(x); )
	{
		int	y = p[x], z = p[y];
		if (Root(y) || y == stop || z == stop)
			if (l[y] == x) Zag(x); else Zig(x);
		else
			if (l[y] == x)
				if (l[z] == y) Zag(y), Zag(x); else Zag(x), Zig(x);
			else
				if (r[z] == y) Zig(y), Zig(x); else Zig(x), Zag(x);
		if (y == stop) break;
	}
}

void	Access(int u)
{
	for (int v = 0; u; u = p[u])
	{
		Splay(u, -1);
		r[u] = v;
		Renew(u);
		v = u;
	}
}

void	Link(int u, int v, int c)
{
	Access(v); Splay(v, -1);
	p[v] = u; e[v] = h(c);
	Renew(v); Renew(u);
	Access(v);
}

void	Cut(int u)
{
	Access(u); Splay(u, -1);
	p[l[u]] = 0; l[u] = 0; e[u] = 0;
	Renew(u);
}

void	Modify(int u, int v, int c)
{
	Access(u);
	for (; ; v = p[v])
	{
		if (u == v) break;
		Splay(v, -1);
		if (!p[v])
		{
			Splay(u, v);
			if (l[u] == v)
				e[u] = h(c), f[u] = h(c), e[r[v]] = h(c), f[r[v]] = h(c), g[r[v]] = h(c);
			else
				e[v] = h(c), f[v] = h(c), e[l[v]] = h(c), f[l[v]] = h(c), g[l[v]] = h(c);
			break;
		}
		e[v] = h(c); f[v] = h(c);
		e[l[v]] = h(c); f[l[v]] = h(c); g[l[v]] = h(c);
	}
}

pii	Search(int u, int v)
{
	Access(u);
	pii	R = {0, 0};
	for (; ; v = p[v])
	{
		if (u == v) break;
		Splay(v, -1);
		if (!p[v])
		{
			Splay(u, v);
			if (l[u] == v)
				R.edg += s[r[v]] + 1, R.cnt |= e[u], R.cnt |= f[r[v]];
			else
				R.edg += s[l[v]] + 1, R.cnt |= e[v], R.cnt |= f[l[v]];
			break;
		}
		R.edg += s[l[v]] + 1; R.cnt |= e[v]; R.cnt |= f[l[v]];
	}
	return R;
}

int	Findroot(int u)
{
	Access(u);
	Splay(u, -1);
	for (; l[u]; u = l[u]);
	return u;
}

int	Lca(int u, int v)
{
	if (u == v) return u;
	int	res;
	Access(u);
	for (int w = 0; v; v = p[v]) 
	{
		Splay(v, -1);
		if (!p[v]) res = v;
		r[v] = w;
		w = v;
	}
	return res;
}

int	main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	
	for (; scanf("%d%d", &N, &Q) != EOF; )
	{
		memset(l, 0, sizeof(l));
		memset(r, 0, sizeof(r));
		memset(f, 0, sizeof(f));
		memset(g, 0, sizeof(g));
		memset(p, 0, sizeof(p));
		
		for (int i = 1; i <= N; ++ i) scanf("%d", &p[i]);
		for (int i = 1; i <= N; ++ i)
		{
			scanf("%d", &e[i]);
			e[i] = f[i] = h(e[i]);
			s[i] = 1;
			if (!p[i]) e[i] = f[i] = 0;
		}
		
		for (int TYPE, c, s, t; Q --; )
		{
			scanf("%d", &TYPE);
			if (TYPE == 1)
			{
				scanf("%d%d%d", &s, &t, &c);
				if (Findroot(s) == Findroot(t))
				{
					int	x = Lca(s, t);
					if (x == s) continue;
				}
				Cut(s);
				Link(t, s, c);
			} else
			if (TYPE == 2)
			{
				scanf("%d%d%d", &s, &t, &c);
				if (s == t) continue;
				if (Findroot(s) != Findroot(t)) continue;
				Modify(s, t, c);
			} else
			if (TYPE == 3)
			{
				scanf("%d%d", &s, &t);
				if (s == t || Findroot(s) != Findroot(t))
				{
					puts("0 0");
					continue;
				}
				pii	R = Search(s, t);
				int	col = 0;
				for (int i = 1; i <= 30; ++ i)
					col += ((R.cnt & (1 << i - 1)) != 0);
				printf("%d %d\n", R.edg, col);
			}
		}
	}
	
	return 0;
}
