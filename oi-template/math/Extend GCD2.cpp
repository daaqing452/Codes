N - 1
  ¦²	(A + B * i) / C
i = 0

inline int exGCD2(int N, int A, int B, int C) {
	if (!N || !C) return 0;
	int	T = A / C * N + B / C * (N - 1) * N / 2;
	A %= C; B %= C;
	return T + exGCD2((A + B * N) / C, (A + B * N) % C, C, B);
}
