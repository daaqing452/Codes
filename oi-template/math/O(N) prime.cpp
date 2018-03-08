memset(next, 0, sizeof(next));
for (int i = 2; i <= N; ++ i)
{
	if (!next[i]) prime[++ PRIME] = i, next[i] = i;
	for (int j = 1; j <= PRIME && i * prime[j] <= N; ++ j)
	{
		next[i * prime[j]] = prime[j];
		if (i % prime[j] == 0) break;
	}
}
