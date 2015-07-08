for (int i = 1; i < N; ++ i)
{
	for (int j = i; j <= N; ++ j) if (a[j][i] != 0) break;
	for (int k = i; k <= N + 1; ++ k) swap(a[i][k], a[j][k]);
	for (int j = i + 1; j <= N; ++j)
	{
		int	t = a[j][i] / a[i][i];
		for (int k = i; k <= N + 1; ++ k) a[j][k] -= a[i][k] * t;
	}
}
for (int i = N; i; -- i)
{
	int	t = a[i][N + 1];
	for (int j = N; j > i; -- j) t -= ans[j] * a[i][j];
	ans[i] = t / a[i][i];
}
