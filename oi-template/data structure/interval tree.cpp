/* interval tree */
inline	void	build(int p, int tl, int tr);
inline	void	cover(int p, int tl, int tr, int nl, int nr);
inline	int	search(int p, int tl, int tr, int nl, int nr);
/* interval tree */





//--------------------interval tree--------------------

inline	void	build(int p, int tl, int tr)
{
	if (tr - tl == 1)
	{
		/*****/
		return;
	}
	int	tm = tl + tr >> 1, x = p << 1, y = x ^ 1;
	build(x, tl, tm);
	build(y, tm, tr);
//	renew();
}

inline	void	cover(int p, int tl, int tr, int nl, int nr)
{
	if (tl == nl && tr == nr)
	{
		/*****/
//		updata(p, tr - tl > 1);
		return;
	}
//	updata(p, tr - tl > 1);
	int	tm = tl + tr >> 1, x = p << 1, y = x ^ 1;
	if (nr <= tm)	cover(x, tl, tm, nl, nr); else
	if (nl >= tm)	cover(y, tm, tr, nl, nr); else
			cover(x, tl, tm, nl, tm), cover(y, tm, tr, tm, nr);
//	renew();
}

inline	int	search(int p, int tl, int tr, int nl, int nr)
{
//	updata(p, tr - tl > 1);
	if (tl == nl && tr == nr) return 0/*****/;
	int	tm = tl + tr >> 1, x = p << 1, y = x ^ 1;
	if (nr <= tm)	return search(x, tl, tm, nl, nr); else
	if (nl >= tm)	return search(y, tm, tr, nl, nr); else
	{
		int	X = search(x, tl, tm, nl, tm);
		int	Y = search(y, tm, tr, tm, nr), Z;
//		renew(Z, X, Y);
		return Z;
	}
}

//--------------------interval tree--------------------
