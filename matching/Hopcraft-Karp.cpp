bool	build()
{
	int	tail = 0;
	bool	yes = 0;
	memset(distx, 0, sizeof(distx));
	memset(disty, 0, sizeof(disty));
	for (int i = 1; i <= N; ++ i) if (!linkx[i]) que[++ tail] = i;
	for (int head = 1; head <= tail; ++ head)
	{
		int	u = que[head];
		for (int i = ww[u]; i; i = w[i].next)
		{
			int	v = w[i].v;
			if (disty[v]) continue;
			disty[v] = distx[u] + 1;
			if(!linky[v])
				yes = 1;
			else
				distx[linky[v]] = disty[v] + 1, que[++ tail] = linky[v];
		}
	}
	return yes;
}

bool	find(int u)
{
	for (int i = ww[u]; i; i = w[i].next)
	{
		int	v = w[i].v;
		if (disty[v] != distx[u] + 1) continue;
		if (!disty[v]) continue;
		disty[v] = 0;
		if(!linky[v] || find(linky[v]))
		{
			linky[v] = u; linkx[u] = v;
			return 1;
		}
	}
	return 0;
}
