void	Tarjan_cut(int u)
{
	s[u].low = s[u].dfn = ++ DFN;
	stk[++ STK] = u; s[u].in = 1;
	for (int i = ww[u]; i; i = w[i].next)
	{
		int	v = w[i].v;
		if (!s[v].dfn)
		{
			Tarjan_cut(v);
			s[u].low = min(s[u].low, s[v].low);
			if (s[v].low >= s[u].dfn) s[u].cut = 1;
			if (s[v].low > s[u].dfn) w[i].cut = 1;
		} else
		if (s[v].in) s[u].low = min(s[u].low, s[v].dfn);
	}
	if (s[u].low == s[u].dfn)
	for (++ BLOCK; stk[STK + 1] != u; -- STK)
	{
		int	v = stk[STK];
		s[v].in = 0;
		s[v].block = BLOCK;
	}
}
