const int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

Int64 producMult(Int64 A,Int64 B,Int64 C) {
	Int64 ANS = 0, P = A;
	for (; B; B >>= 1) {
		if (B & 1) if ((ANS += P) >= C) ANS -= C;
		if ((P += P) >= C) P -= C;
	}
	return ANS;
}

Int64 producExp(Int64 A,Int64 B,Int64 C) {
	Int64 ANS = 1, P = A;
	for (; B; B >>= 1) {
		if (B & 1) ANS = producMult(ANS, P, C);
		P = producMult(P, P, C);
	}
	return ANS;
}

bool witness(Int64 A, Int64 N) {
	if (N == 1) return 1;
	Int64 TIMES = 0, NN = N - 1;
	for (; !(NN & 1); NN >>= 1) ++ TIMES;
	Int64 X, Y = producExp(A, NN, N), Z;
	for (; TIMES--; )
	{
		Z = producMult(Y, Y, N); X = Y; Y = Z;
		if (Y == 1 && X != 1 && X != N - 1) return 0;
	}
	if (Y != 1) return 0;
	return 1;
}

bool millerRabin(Int64 N)
{
	for (int i = 0; i < 15; ++ i) if (N == prime[i]) return 1;
	for (int i = 0; i < 15; ++ i)
		if (!witness(prime[i], N)) return 0;
	return 1;
}
