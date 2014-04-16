const	int	prime[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};

int64	Produc_Mult(int64 A, int64 B, int64 C)
{
	int64	ANS = 0, P = A;
	for (; B; B >>= 1)
	{
		if (B & 1) if ((ANS += P) >= C) ANS -= C;
		if ((P += P) >= C) P -= C;
	}
	return ANS;
}

int64	gcd(int64 A,int64 B)
{
	if (!B) return A; else return gcd(B, A % B);
}

int64	Pollar_Rho(int64 N)
{
	int64	x = rand() % N, y = x;
	for (int i = 2, k = 2; ; ++ i)
	{
		x = Produc_Mult(x, x, N);
		if (!x) x = N - 1; else -- x;
		if (x == y) return N;
		int64	GCD = gcd(N + y - x, N);
		if (GCD > 1 && GCD < N) return GCD;
		if (i == k) y = x, k += k;
	}
}

void	Find_Factor(int64 N)
{
	if (N == 1) return;
	if (Miller_Rabin(N)) { factor[++ FACTOR]=N; return; }
	int64	Q = N;
	for (; Q == N || Q == 1; ) Q = Pollard_Rho(N);
	Find_Factor(Q);
	Find_Factor(N / Q);
}
