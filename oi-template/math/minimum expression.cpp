int work(char st[],int len) {
	int	i = 0, j = 1, k = 0;
	while (k < len)
	if (st[(i + k) % len] == st[(j + k) % len]) ++ k; else {
		if (st[(i + k) % len] > st[(j + k) % len]) i += k + 1; else j += k + 1;
		if (i == j) ++ j;
		k = 0;
	}
	return (i % len < j % len ? i % len : j % len);
}
