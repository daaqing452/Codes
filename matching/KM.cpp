int	hungary(int u)
{
	X[u] = 1;
	for (int i = 1; i <= N; ++ i)
	if(!Y[i] && lx[u] + ly[i] == maq[u][i])
	{
		Y[i] = 1;
		if(linky[i] == 0 || hungary(linky[i]))
		{
			linky[i] = u;
			return 1;
		}
	}
	return 0;
}

void	KM()
{
	memset(linky, 0, sizeof(linky));
	memset(lx, 0, sizeof(lx));
//	memset(lx, 60, sizeof(lx));
	memset(ly, 0, sizeof(ly));
	for (int i = 1; i <= N; ++ i)
	for (int j = 1; j <= N; ++ j)
		lx[i] = max(lx[i], maq[i][j]);
//		lx[i] = min(lx[i], maq[i][j]);

	for (int k = 1; k <= N; ++ k)
	for (; ; )
	{
		memset(X, 0, sizeof(X));
		memset(Y, 0, sizeof(Y));
		if (hungary(k)) break;

		int	d = 1 << 30;
//		d = -1 << 30;
		for (int i = 1; i <= N; ++ i) if (X[i])
		for (int j = 1; j <= N; ++ j) if (!Y[j])
			d = min(d, lx[i] + ly[j] - maq[i][j]);
//			d = max(d, lx[i] + ly[j] - maq[i][j]);

		for (int i = 1; i <= N; ++ i)
		{
			if (X[i]) lx[i] -= d;
			if (Y[i]) ly[i] += d;
		}
	}
}
