const	int	prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

int64	Produc_Mult(int64 A,int64 B,int64 C)
{
	int64	ANS = 0, P = A;
	for (; B; B >>= 1)
	{
		if (B & 1) if ((ANS += P) >= C) ANS -= C;
		if ((P += P) >= C) P -= C;
	}
	return ANS;
}

int64	Produc_Exp(int64 A,int64 B,int64 C)
{
	int64	ANS = 1, P = A;
	for (; B; B >>= 1)
	{
		if (B & 1) ANS = Produc_Mult(ANS, P, C);
		P = Produc_Mult(P, P, C);
	}
	return ANS;
}

bool	Witness(int64 A, int64 N)
{
	if (N == 1) return 1;
	int64	TIMES = 0, NN = N - 1;
	for (; !(NN & 1); NN >>= 1) ++ TIMES;
	int64	X, Y = Produc_Exp(A, NN, N), Z;
	for (; TIMES--; )
	{
		Z = Produc_Mult(Y, Y, N); X = Y; Y = Z;
		if (Y == 1 && X != 1 && X != N - 1) return 0;
	}
	if (Y != 1) return 0;
	return 1;
}

bool	Miller_Rabin(int64 N)
{
	for (int i = 0; i < 15; ++ i) if (N == prime[i]) return 1;
	for (int i = 0; i < 15; ++ i)
		if (!Witness(prime[i], N)) return 0;
	return 1;
}
