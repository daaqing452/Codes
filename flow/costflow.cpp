inline void addedge(int u, int v, int c, int q);
inline int mcmf();



inline void addedge(int u, int v, int c, int q) {
	w[++ W].v = v; w[W].c = c; w[W].q = q;  w[W].next = ww[u]; ww[u] = W;
	w[++ W].v = u; w[W].c = 0; w[W].q = -q; w[W].next = ww[v]; ww[v] = W;
}

inline int mcmf() {
	int mincost = 0;
	for (int la; ; ) {
		memset(dist, 60, sizeof(dist));
//		memset(dist, -60, sizeof(dist));
		memset(visit, 0, sizeof(visit));	
		dist[s] = 0; visit[s] = 1; que[la = 1] = s;
		for (int fi = 1; fi <= la; ++ fi) {
			int u = que[fi];
			for (int i = ww[u]; i; i = w[i].next) if (w[i].c) {
				int	v = w[i].v;
				if (dist[v] <= dist[u] + w[i].q) continue;
//				if (dist[v] >= dist[u] + w[i].q) continue;
				dist[v] = dist[u] + w[i].q; stq[v] = i;
				if (visit[v]) continue;
				visit[v] = 1; que[++ la] = v;
			}
			visit[u] = 0;
		}
		if (dist[t] > 1 << 29) break;
//		if (dist[t] <= 0) break;
//		if (dist[t] < -1 << 29) break;
		int	flow = 1 << 30;
		for (int i = t; i != s; i = w[stq[i] ^ 1].v) flow = min(flow, w[stq[i]].c);
		for (int i = t; i != s; i = w[stq[i] ^ 1].v) w[stq[i]].c -= flow, w[stq[i] ^ 1].c += flow;
		mincost += dist[t] * flow;
	}
	return mincost;
}