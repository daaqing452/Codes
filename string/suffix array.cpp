/* suffix array */
#define STR a
void	suffixsort();
/* suffix array */





//--------------------suffix array--------------------

void	suffixsort()
{
	int	T = max(N, 26);
	memset(top, 0, sizeof(top));
	for (int i = 1; i <= N; ++ i) top[rank[i] = a[i] + 1] ++;
	for (int i = 1; i <= T; ++ i) top[i] += top[i - 1];
	for (int i = 1; i <= N; ++ i) sa[top[rank[i]] --] = i;
	
	for (int L = 1; L < N; L <<= 1)
	{
		for (int i = 1; i <= N; ++ i)
	        {
			int	j = sa[i] - L;
			if (j <= 0) j += N;
			nsa[++ top[rank[j]]] = j;
	        }
	        top[1] = 0;
	        for (int i = 2, j = nrank[nsa[1]] = 1; i <= N; ++ i)
	        {
			if (rank[nsa[i]] != rank[nsa[i - 1]] || rank[nsa[i] + L] != rank[nsa[i - 1] + L]) top[++ j] = i - 1;
			nrank[nsa[i]] = j;
	        }
	        memcpy(rank, nrank, sizeof(rank));
	        memcpy(sa, nsa, sizeof(sa));
	        if (rank[sa[N]] == N) break;
	}
	
	for (int i = 1, p = 0; i <= N; ++ i)
	if (rank[i] == 1) h[rank[i]] = 0; else
	{
		p = max(0, p - 1);
		for (int j = sa[rank[i] - 1]; a[i + p] == a[j + p]; ++ p);
		h[rank[i]] = p;
	}
}

//--------------------suffix array--------------------
