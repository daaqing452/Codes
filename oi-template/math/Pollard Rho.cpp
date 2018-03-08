const int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

Int64	producMult(Int64 A, Int64 B, Int64 C) {
	Int64 ANS = 0, P = A;
	for (; B; B >>= 1) {
		if (B & 1) if ((ANS += P) >= C) ANS -= C;
		if ((P += P) >= C) P -= C;
	}
	return ANS;
}

Int64 gcd(Int64 A,Int64 B) {
	if (!B) return A; else return gcd(B, A % B);
}

Int64 pollarRho(Int64 N) {
	Int64 x = rand() % N, y = x;
	for (int i = 2, k = 2; ; ++ i) {
		x = producMult(x, x, N);
		if (!x) x = N - 1; else -- x;
		if (x == y) return N;
		Int64 GCD = gcd(N + y - x, N);
		if (GCD > 1 && GCD < N) return GCD;
		if (i == k) y = x, k += k;
	}
}

void findFactor(Int64 N) {
	if (N == 1) return;
	if (Miller_Rabin(N)) { factor[++FACTOR] = N; return; }
	Int64 Q = N;
	for (; Q == N || Q == 1; ) Q = pollardRho(N);
	findFactor(Q);
	findFactor(N / Q);
}
