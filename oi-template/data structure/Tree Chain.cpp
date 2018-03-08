void BuildChain() {
	int fi, la;
	memset(visit, 0, sizeof(visit)); visit[1] = 1;
	que[la = 1] = 1;
	for (fi = 1; fi <= la; ++ fi) {
		int u = que[fi];
		for (int i = ww[u]; i; i = w[i].next) {
			int v = w[i].v;
			if (!visit[v]) continue;
			visit[v] = 1; father[v] = u;
			que[++ la] = v;
		}
	}
	for (int i = N; i; -- i) {
		int u = que[i];
		s[u] = 1;
		for (int j = ww[u]; j; j = w[j].next) s[u] += s[w[j].v];
	}
	
	c[++C].head = 1; c[C].len = 1;
	memset(clain, 0, sizeof(clain)); clain[1] = 1;
	for (int i = 1; i <= N; ++ i) {
		int u = que[i], maxs = 0, k = 0;
		for (j = ww[u]; j; j = w[j].next) if (w[j].v != father[u]) {
			int v = w[j].v;
			if (s[v] > maxs) { maxs = s[v]; k = v; }
		}
		if (k) {
			suc[u] = k;
			clain[k] = clain[u];
			++ c[clain[u]].len;
		}
		for (int j = ww[u]; j; j = w[j].next) if (w[j].v != father[u])
		if (w[j].v != k) {
			int v = w[j].v;
			clain[v] = ++ C; c[C].head = v; c[C].len = 1;
		}
	}
}
