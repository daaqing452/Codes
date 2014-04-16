/* sbt */
#define SBT a
#define key key
struct	SBTTree
{
	int	l, r, s, key;
};
inline	void	renew(int x);
inline	void	leftrotate(int &x);
inline	void	righrotate(int &x);
inline	void	maintain(int &x, bool fl);
inline	void	insert(int &x, int n);
inline	void	delett(int &x, int n);
inline	int	findkth(int x, int k);
/* sbt */





//--------------------sbt--------------------



inline	void	leftrotate(int &x)
{
	int	y = SBT[x].r; SBT[x].r = SBT[y].l; SBT[y].l = x;
	SBT[y].s = SBT[x].s;
	SBT[x].s = SBT[SBT[x].l].s + SBT[SBT[x].r].s + 1;
//	renew(x); renew(y);
	x = y;
}

inline	void	righrotate(int &x)
{
	int	y = SBT[x].l; SBT[x].l = SBT[y].r; SBT[y].r = x;
	SBT[y].s = SBT[x].s;
	SBT[x].s = SBT[SBT[x].l].s + SBT[SBT[x].r].s + 1;
//	renew(x); renew(y);
	x = y;
}

inline	void	maintain(int &x, bool fl)
{
	if (!fl)
		if (SBT[SBT[SBT[x].l].l].s > SBT[SBT[x].r].s)	righrotate(x); else
		if (SBT[SBT[SBT[x].l].r].s > SBT[SBT[x].r].s)	leftrotate(SBT[x].l), righrotate(x); else
								return;
	else
		if (SBT[SBT[SBT[x].r].r].s > SBT[SBT[x].l].s)	leftrotate(x); else
		if (SBT[SBT[SBT[x].r].l].s > SBT[SBT[x].l].s)	righrotate(SBT[x].r), leftrotate(x); else
								return;
	maintain(SBT[x].l, 0);
	maintain(SBT[x].r, 1);
	maintain(x, 0);
	maintain(x, 1);
}

inline	void	insert(int &x, int n)
{
	if (!x)
	{
		SBT[n].l = SBT[n].r = 0; SBT[n].s = 1;
		x = n;
		return;
	}
	++ SBT[x].s;
	if (SBT[n].key < SBT[x].key)	insert(SBT[x].l, n); else
					insert(SBT[x].r, n);
//	renew(x);
	maintain(x, SBT[n].key >= SBT[x].key);
}

inline	void	delett(int &x, int n)
{
//	if (!x) return;
	if (x == n)
	{
		if (!SBT[x].l || !SBT[x].r)
		{
			x = SBT[x].l + SBT[x].r;
			return;
		}
		righrotate(x); -- SBT[x].s;
		delett(SBT[x].r, n);
//		renew(x);
		return;
	}
	-- SBT[x].s;
	if (SBT[n].key < SBT[x].key)	delett(SBT[x].l, n); else
					delett(SBT[x].r, n);
//	renew(x);
}

inline	int	findkth(int x, int k)
{
	if (k < 1 || k > SBT[x].s) return -1;
	for (; ; )
	if (k == SBT[SBT[x].l].s + 1)	return x; else
	if (k <= SBT[SBT[x].l].s)	x = SBT[x].l; else
					k -= SBT[SBT[x].l].s + 1, x = SBT[x].r;
}

//--------------------sbt--------------------
