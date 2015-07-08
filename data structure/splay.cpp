#define SPL a
struct SPLTree {
	int	l, r, p, s, key;
};
inline void renew(int x);
inline void updata(int x);
inline void zig(int x);
inline void zag(int x);
inline void splay(int x);
inline void cut(int x);
inline int join(int p, int q);

inline void zig(int x) {
	int y = SPL[x].p, z = SPL[y].p, w = SPL[x].l;
	SPL[w].p = y; SPL[y].r = w;
	SPL[y].p = x; SPL[x].l = y;
	SPL[x].p = z;
	if (y == SPL[z].l) SPL[z].l = x;
	if (y == SPL[z].r) SPL[z].r = x;
//	renew(y); renew(x);
}

inline void zag(int x) {
	int y = SPL[x].p, z = SPL[y].p, w = SPL[x].r;
	SPL[w].p = y; SPL[y].l = w;
	SPL[y].p = x; SPL[x].r = y;
	SPL[x].p = z;
	if (y == SPL[z].l) SPL[z].l = x;
	if (y == SPL[z].r) SPL[z].r = x;
//	renew(y); renew(x);
}

inline void splay(int x) {
/*	int la = 0;
	for (int i = x; ; i = SPL[i].p) {
		que[++ la] = i;
		if (!SPL[i].p) break;
	}
	for (int i = la; i; -- i) updata(que[i]);	*/
	
	for (; SPL[x].p; ) {
		int	y = SPL[x].p, z = SPL[y].p;
		if (!z)
			if (x == SPL[y].l) zag(x); else zig(x);
		else
			if (x == SPL[y].l)
				if (y == SPL[z].l) zag(y), zag(x); else zag(x), zig(x);
			else
				if (y == SPL[z].r) zig(y), zig(x); else zig(x), zag(x);
	}
}

inline void cut(int x) {
	if (!x) return;
	int	y = SPL[x].p;
	if (x == SPL[y].l) SPL[y].l = 0; else SPL[y].r = 0;
	SPL[x].p = 0;
//	renew(y);
}

inline int join(int p, int q) {
	if (!p) return q;
	if (!q) return p;
	int	x = p;
	for (; SPL[x].r; x = SPL[x].r);// updata(x);
	splay(x);
	SPL[q].p = x; SPL[x].r = q;
//	renew(x);
	return x;
}
